#ifndef CABLE_HPP
#define CABLE_HPP

#include "Device.hpp"
#include <memory>

extern "C" {
    #include <raylib.h>
}

class Cable {
    public:
        std::unique_ptr<Device> left;
        std::unique_ptr<Device> right;

        void setRight(Device *n) {
            this->right.reset(n);
        }

        void setLeft(Device *n) {
            this->left.reset(n);
        }

        void draw() {
            DrawLineV(Vector2{this->left->x, this->left->y}, Vector2{this->right->x, this->right->y}, BLACK);
        }
};


#endif