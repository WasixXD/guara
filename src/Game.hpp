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
        std::vector<Cable*> cables;

        bool cable_clicked = false;
        Cable *c;

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
            Vector2 mousePos = GetMousePosition();
            EndDevice *tmp = new EndDevice("PC", mousePos.x, mousePos.y, 0xCAFE, RED);
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
                                c->setLeft(d);
                                d->cables.push_back(c);
                                return;
                            }
                        }
                    }
                    // get second device
                    for(Device *d : this->devices) {
                        if(d->checkMouseCollision(GetMousePosition())) {
                            c->setRight(d);
                            d->cables.push_back(c);
                        }
                    }

                    this->cables.push_back(c);
                    this->cable_clicked = false;
                    break;

                case KEY_V: 

                    break;
                default:
                    return;
                    break;
            }
        }

        void drawDevices() {
            for(Device *d : this->devices) {
                d->draw();
            }
        }

        void drawCables() {
            for(Cable *c : this->cables) {
                c->draw();
            }
        }


        void mainLoop() {
            while(this->isWindowOpen()) {
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    this->handleButtonPressed();
                    this->drawDevices();
                    this->drawCables();
                EndDrawing();
            }
        }
};


#endif