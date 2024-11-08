#ifndef CABLE_HPP
#define CABLE_HPP

#include <memory>

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
};


#endif