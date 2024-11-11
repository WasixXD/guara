#ifndef MIDDLEDEVICE_HPP
#define MIDDLEDEVICE_HPP

#include "Device.hpp"
#include "Packets.hpp"
#include "Cable.hpp"

class MiddleDevice : public Device
{

    float width;
    float height;

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

        printf("[%u] ARP HIT THE SWITCH\n", this->MAC_ADDRESS);
        for(Cable *c : this->cables) {
            // dont send the package to ourselfs neither the sender
            if(c->left->MAC_ADDRESS != this->MAC_ADDRESS && c->left->MAC_ADDRESS != a.sender_mac) c->sendArpLeft(a);
            if(c->right->MAC_ADDRESS != this->MAC_ADDRESS && c->right->MAC_ADDRESS != a.sender_mac) c->sendArpRight(a);
        }
    }
};

#endif