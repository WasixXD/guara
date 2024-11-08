#include <stdio.h>
#include "Game.hpp"


int main(void) {
    
    Game g(800, 400, "Guará - Simulador de redes");
    g.mainLoop();
    
    return 0;
}