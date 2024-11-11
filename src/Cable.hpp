#ifndef CABLE_HPP
#define CABLE_HPP

#include <memory>
#include "Packets.hpp"

extern "C" {
    #include <raylib.h>
}


class Device;

class Cable {
    public:
        Device* conn;


        void setConn(Device *n);

        void draw(Vector2 to); 

        void sendArp(Arp a);
};


#endif