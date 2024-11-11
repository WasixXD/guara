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
        Device* left;
        Device* right;

        void setRight(Device *n); 

        void setLeft(Device *n);

        void draw(); 

        void sendArpLeft(Arp a);
        void sendArpRight(Arp a);
};


#endif