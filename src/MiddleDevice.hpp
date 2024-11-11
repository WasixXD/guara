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

    void receiveArp(Arp a) override {
        // TODO: SET UP MAC TABLE
        for(Cable *c : this->cables) {
            // dont send the package to the sender
            a.set_src_mac(this->MAC_ADDRESS);
            if(c->conn->MAC_ADDRESS != a.sender_mac) c->sendArp(a);
        }
    }
};

#endif