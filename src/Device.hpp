#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <inttypes.h>
#include <vector>
#include "Packets.hpp"

class Cable;

extern "C" {
    #include <raylib.h>
}

class Device {


    public:
        const char *name;
        float x;
        float y; 
        // MAC SHOULD BE 64 bits and then we just use the first 48?
        uint32_t MAC_ADDRESS;
        Color color;
        std::vector<Cable*> cables;

        Device(const char *n, float x, float y, uint32_t m, Color c):
             name(n), x(x), y(y), MAC_ADDRESS(m), color(c) { }
        virtual void draw() {}
        virtual bool checkMouseCollision(Vector2 mousePos) {
            return checkMouseCollision(mousePos);
        }

        virtual void receiveArp(Arp a) {};

};


#endif