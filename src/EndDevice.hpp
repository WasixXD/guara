#ifndef ENDDEVICE_HPP
#define ENDDEVICE_HPP

#include "Device.hpp"
#include "Packets.hpp"
#include "Cable.hpp"
#include <stdio.h>
#include <vector>
#include <random>
#include <unordered_map>


class EndDevice : public Device {

    uint32_t IP_ADDRESS;
    int radius;

    std::unordered_map<uint32_t, uint32_t> arp_table;

    public: 
        EndDevice(const char *n, float x, float y, uint32_t m, Color c) : Device(n, x, y, m, c) { 
            this->radius = 20;
            printf("[%u] %s IP: %u \n", this->MAC_ADDRESS, this->name, this->IP_ADDRESS);
        }   

        void setIP(uint32_t ip) {
            this->IP_ADDRESS = ip;
        }

        void setRandomIp() {
            std::random_device rd;
            std::mt19937 gen(rd());
            
            std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

            this->IP_ADDRESS = dist(gen);
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

        void set_arp(uint32_t target_ip, uint32_t target_mac) {
            this->arp_table.insert(std::make_pair(target_ip, target_mac));
        }

        // :(
        int findCableMac(uint32_t mac) {
            for(int i = 0; i < this->cables.size(); i++) {
                if(this->cables[i]->conn->MAC_ADDRESS == mac) return i;
            }
            return -1;
        }

        void receiveArp(Arp a) override {
            printf("[%u] WHO HAS THE MAC OF %u? SAYS %u\n", this->MAC_ADDRESS, a.target_ip, a.sender_mac);

            // check if the package is to ourselfs
            if(a.target_ip == this->IP_ADDRESS && a.request) {
                Arp response(this->MAC_ADDRESS, this->IP_ADDRESS, this->MAC_ADDRESS, a.sender_ip);
                int position = findCableMac(a.SRC_MAC);

                response.request = false;
                response.set_dst_mac(a.sender_mac);
                response.set_src_mac(this->MAC_ADDRESS); 
                this->cables[position]->sendArp(response);

            }

        }
        
        void ping(uint32_t target_ip) {
            // Check arp table
            if(!this->arp_lookup(target_ip)) {
                // send arp request
                Arp a(this->MAC_ADDRESS, this->IP_ADDRESS, 0xffff, target_ip);

                // send arp to all conected cables
                for(Cable *c : this->cables) {
                    c->sendArp(a);
                }
            }


            // receive arp response
            // send icmp request
            // receive icmp resposne

            printf("[IP: %u] WANTS TO PING %u\n", this->IP_ADDRESS, target_ip);
        }
};

#endif