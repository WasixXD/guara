#ifndef ENDDEVICE_HPP
#define ENDDEVICE_HPP

#include "Device.hpp"
#include <vector>
#include <random>

class EndDevice : public Device {

    uint32_t IP_ADDRESS;
    int radius;

    public: 
        EndDevice(const char *n, float x, float y, uint32_t m, Color c) : Device(n, x, y, m, c) { 
            this->radius = 20;
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


        void draw() override {
            DrawCircleV(Vector2{this->x, this->y}, this->radius, this->color);
            DrawText(this->name, this->x, this->y, 10, BLACK);
        }

        bool checkMouseCollision(Vector2 mousePos) override {
            return CheckCollisionPointCircle(mousePos, Vector2{this->x, this->y},this->radius);
        }
};

#endif