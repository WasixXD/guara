#ifndef CABLE_HPP
#define CABLE_HPP

#include <memory>
#include "Packets.hpp"

extern "C" {
    #include <raylib.h>
}


class Device;

// not a huge fan of this cable interface
// like, this can simplify the way to send the packages
// but things get very messy when things neeed to be accessed by outsiders
class Cable {
    public:
        Device* conn;

        uint32_t connMac();

        void setConn(Device *n);

        void draw(Vector2 to); 

        void sendArp(Arp a);
};


#endif