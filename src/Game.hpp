#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include "EndDevice.hpp"
#include "MiddleDevice.hpp"
#include "Cable.hpp"
#include <vector>

extern "C" {
    #include <raylib.h>
}

class Game {
    private:
        int width;
        int height;
        const char *text;
        bool running = false;

        std::vector<Device*> devices;

        bool cable_clicked = false;
        Cable *c = nullptr;

        Device *mock = nullptr;


        uint32_t target_ip;
        EndDevice *sender = nullptr;

        void destroy() {
            this->running = false;
        }

    public: 
        Game(int w, int h, const char *t): width(w), height(h), text(t) {
            InitWindow(w, h, t);
            this->running = true;
        }

        ~Game() {
            CloseWindow();
        }

        bool isWindowOpen() {
            return this->running;
        }


        void addEndDevice() {
            // remove this?
            std::random_device rd;
            std::mt19937 gen(rd());
            
            std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

            Vector2 mousePos = GetMousePosition();
            EndDevice *tmp = new EndDevice("PC", mousePos.x, mousePos.y, dist(gen), RED);
            tmp->setRandomIp();
            this->devices.push_back(tmp);
        }

        void addMiddleDevice() {
            Vector2 mousePos = GetMousePosition();
            MiddleDevice *tmp = new MiddleDevice("Switch", mousePos.x, mousePos.y, 0xACAD, BLUE);
            this->devices.push_back(tmp);
        }

        void handleButtonPressed() {
            switch (GetKeyPressed()) {
                case KEY_Q: 
                    this->destroy();
                    break;

                case KEY_A: 
                    this->addEndDevice();
                    break;
                
                case KEY_S:
                    this->addMiddleDevice();
                    break;

                case KEY_C:

                    // Ugly
                    // get first device
                    if(!this->cable_clicked) {
                        c = new Cable();
                        for(Device *d : this->devices) {
                            if(d->checkMouseCollision(GetMousePosition())) {
                                this->cable_clicked = true;
                                this->mock = d;
                                return;
                            }
                        }
                    }
                    // get second device
                    for(Device *d : this->devices) {
                        if(d->checkMouseCollision(GetMousePosition())) {
                            // set the connection of the 2nd to the 1st
                            c->setConn(this->mock);
                            d->cables.push_back(c);

                            // set the connection of the 1st to the 2nd
                            Cable *tmp = new Cable(); 
                            tmp->setConn(d);
                            this->mock->cables.push_back(tmp);

                        }
                    }
                    this->cable_clicked = false;
                    break;

                case KEY_V: 

                    if(sender == nullptr) {
                        for(Device *d : this->devices) {
                            if(d->checkMouseCollision(GetMousePosition())) {
                                EndDevice *c = dynamic_cast<EndDevice*>(d);
                                if(c == nullptr) return;
                                
                                this->sender = c;
                                return;
                            }
                        }
                    }
                    for(Device *d : this->devices) {
                        if(d->checkMouseCollision(GetMousePosition())) {
                            EndDevice *c = dynamic_cast<EndDevice*>(d);
                            if(c == nullptr) return;

                            this->target_ip = c->getIP();
                        }
                    }

                    this->sender->ping(this->target_ip);
                    this->sender = nullptr;

                    break;
                default:
                    return;
                    break;
            }
        }

        void drawDevices() {
            for(Device *d : this->devices) {
                d->draw();

                for(Cable *c : d->cables) {
                    c->draw(Vector2{ d->x, d->y });
                }
            }
        }

       


        void mainLoop() {
            while(this->isWindowOpen()) {
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    this->handleButtonPressed();
                    this->drawDevices();
                EndDrawing();
            }
        }
};


#endif