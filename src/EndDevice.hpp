#ifndef ENDDEVICE_HPP
#define ENDDEVICE_HPP

#include "Device.hpp"
#include "Packets.hpp"
#include "Cable.hpp"
#include "utils.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <chrono>
#include <cstdio>


class EndDevice : public Device {

    uint32_t IP_ADDRESS;
    int radius;

    std::unordered_map<uint32_t, uint32_t> arp_table;

    public: 
        EndDevice(const char *n, float x, float y, uint32_t m, Color c) : Device(n, x, y, m, c) { 
            this->radius = 20;
        }   

        void setIP(uint32_t ip) {
            this->IP_ADDRESS = ip;
        }

        void setRandomIp() {
            std::random_device rd;
            std::mt19937 gen(rd());
            
            std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

            this->IP_ADDRESS = dist(gen);

            printf("[%s] %s IP: %s \n", utils::pp_mac(this->MAC_ADDRESS).c_str(), this->name, utils::pp_ip(this->IP_ADDRESS).c_str());
        }

        uint32_t getIP() {
            return this->IP_ADDRESS;
        }


        void draw() override {
            DrawCircleV(Vector2{this->x, this->y}, this->radius, this->color);
            DrawText(this->name, this->x, this->y, 10, BLACK);
        }

        bool checkMouseCollision(Vector2 mousePos) override {
            return CheckCollisionPointCircle(mousePos, Vector2{this->x, this->y},this->radius);
        }

        bool arp_lookup(uint32_t target_ip) {
            return this->arp_table.contains(target_ip);
        }

        uint32_t get_mac(uint32_t target_ip) {
            auto it = this->arp_table.find(target_ip);
            if (it != this->arp_table.end()) {
                return it->second;
            }
            return -1;
        }

        void set_arp(uint32_t target_ip, uint32_t target_mac) {
            this->arp_table.insert(std::make_pair(target_ip, target_mac));
        }

        // that's actually not that bad because 
        // the number of cables is never going to be too large
        int findCableMac(uint32_t mac) {
            for(int i = 0; i < this->cables.size(); i++) {
                if(this->cables[i]->conn->MAC_ADDRESS == mac) return i;
            }
            return -1;
        }

        void receiveArp(Arp a) override {
         
            if(!this->arp_lookup(a.target_ip)) this->set_arp(a.sender_ip, a.sender_mac);

            if(a.request) {
                // send ARP to the one who sended the package
                Arp response(this->MAC_ADDRESS, this->IP_ADDRESS, a.sender_mac, a.sender_ip);
                int position = findCableMac(a.SRC_MAC);

                response.request = false;
                response.set_dst_mac(a.sender_mac);
                response.set_src_mac(this->MAC_ADDRESS); 
                this->cables[position]->sendArp(response);
                return;
            }
        }

        void receiveICMP(ICMP i) override {
            // request
            // just send a response
            if(i.type == 8 && i.code == 0) {
                ICMP packet(i.SRC_MAC, this->MAC_ADDRESS);

                packet.pby++;
                packet.type = 0;
                packet.code = 0;
                
                this->cables[0]->sendICMP(packet);
            }

            // response
            // the packet is back
            if(i.type == 0 && i.code == 0) {
                auto now = std::chrono::system_clock::now();
                auto latency = std::chrono::duration_cast<std::chrono::milliseconds>(now - i.timestamp).count();
                printf("[%s] RECEIVED ECHO REPLY :LATENCY=%ldms HOPS=%d\n", utils::pp_mac(this->MAC_ADDRESS).c_str(), latency, i.pby);
            }
        }
        
        void ping(uint32_t target_ip) {
            printf("[%s] WANTS TO PING %s\n", utils::pp_ip(this->IP_ADDRESS).c_str(), utils::pp_ip(target_ip).c_str()); 
            // Check arp table
            if(!this->arp_lookup(target_ip)) {
                // prepare arp request
                Arp a(this->MAC_ADDRESS, this->IP_ADDRESS, 0xffff, target_ip);
                a.set_src_mac(this->MAC_ADDRESS);

                // send arp to all conected cables (broadcast)
                // PCs usually just have one connection
                for(Cable *c : this->cables) { 
                    c->sendArp(a);
                }
            }
            // right now we already have the MAC AND IP of the 
            // device we want to ping

            // prepare icmp request
            uint32_t target_mac = this->get_mac(target_ip);
            ICMP packet(target_mac, this->MAC_ADDRESS);

            packet.type = 8;
            packet.code = 0;
            packet.checksum = sizeof(packet);
            packet.timestamp = std::chrono::system_clock::now();

            // send icmp request
            Cable *c = this->cables[0];
            for(int i = 0; i < 4; i++) {
                c->sendICMP(packet);
            }
        }
};

#endif