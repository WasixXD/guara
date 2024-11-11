#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <stdio.h>
#include <inttypes.h>

class EthernetFrame {

    public: 
        uint32_t DST_MAC;
        uint32_t SRC_MAC;

        EthernetFrame(uint32_t d, uint32_t s): DST_MAC(d), SRC_MAC(s) {}

        void set_dst_mac(uint32_t tmp) {
            this->DST_MAC = tmp;
        }

        void set_src_mac(uint32_t tmp) {
            this->SRC_MAC = tmp;
        }
};

class Arp : public EthernetFrame {
    public:
        uint32_t sender_mac;
        uint32_t sender_ip;

        uint32_t target_mac;
        uint32_t target_ip;

        bool request;
        Arp(uint32_t sm, uint32_t si, uint32_t tm ,uint32_t ti) : EthernetFrame(0xffff, 0xffff) {
            this->sender_mac = sm; 
            this->sender_ip = si;

            this->target_mac = tm;
            this->target_ip = ti;
            this->request = true;
        }
};


#endif