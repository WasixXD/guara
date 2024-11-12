#include "Cable.hpp"
#include "Device.hpp"
#include "Packets.hpp"

void Cable::draw(Vector2 to) {
    DrawLineV(to, Vector2{this->conn->x, this->conn->y}, BLACK);
}

uint32_t Cable::connMac() {
    if(this->conn != nullptr) {
        return this->conn->MAC_ADDRESS;
    }
    return -1;
}

void Cable::setConn(Device *d) {
    this->conn = d;
}

void Cable::sendArp(Arp a) {
    this->conn->receiveArp(a);
}
