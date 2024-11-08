#include "Cable.hpp"
#include "Device.hpp"

void Cable::setRight(Device *n) {
    this->right = n;
}

void Cable::setLeft(Device *n) {
    this->left = n;
}

void Cable::draw() {
    DrawLineV(Vector2{this->left->x, this->left->y}, Vector2{this->right->x, this->right->y}, BLACK);
}