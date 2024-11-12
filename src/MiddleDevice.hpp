#ifndef MIDDLEDEVICE_HPP
#define MIDDLEDEVICE_HPP

#include "Device.hpp"
#include "Packets.hpp"
#include "Cable.hpp"
#include <unordered_map>

class MiddleDevice : public Device
{

    float width;
    float height;
    std::unordered_map<uint32_t, int> mac_table;

public:
    MiddleDevice(const char *n, float x, float y, uint32_t m, Color c) : Device(n, x, y, m, c) {
        this->width = 35.f;
        this->height = 35.f;
    }

    void draw() override {
        DrawRectangleV(Vector2{this->x, this->y}, Vector2{this->width, this->height}, this->color);
        DrawText(this->name, this->x, this->y, 10, BLACK);
    }
    bool checkMouseCollision(Vector2 mousePos) override {
        return CheckCollisionPointRec(mousePos, Rectangle{ this->x, this->y, this->width, this->height });
    }
    bool mac_lookup(uint32_t target_mac) {
        return this->mac_table.contains(target_mac);
    }

    int get_mac_pos(uint32_t target_mac) {
        return this->mac_table.at(target_mac);
    }

    // don't like this
    void set_mac(uint32_t new_mac) {
        for(int i = 0; i < this->cables.size(); i++) {
            if(this->cables[i]->connMac() == new_mac) {
                this->mac_table.insert(std::make_pair(new_mac, i));
            }
        }
    }

    void receiveArp(Arp a) override {
        
        if(!this->mac_lookup(a.sender_mac)) {
            this->set_mac(a.sender_mac);
        }

        // broadcast
        if(a.target_mac == 0xffff) {
            for(Cable *c : this->cables) {
                a.set_src_mac(this->MAC_ADDRESS);
                // dont send the package to the sender
                if(c->conn->MAC_ADDRESS != a.sender_mac) c->sendArp(a);
            }
            return;
        }


        // unicast
        int mac_position = this->get_mac_pos(a.target_mac);
        this->cables[mac_position]->sendArp(a);
         
    }
};

#endif