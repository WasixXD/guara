#ifndef UTILS_HPP
#define UTILS_HPP

#include <inttypes.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace utils {
    std::string pp_ip(uint32_t ip) {
        std::string tmp;
        while(ip > 0) {
            tmp += std::to_string(ip & 0x000000ff) + ".";
            ip >>= 8;
        }
        tmp.pop_back();
        return tmp;
    }

    std::string pp_mac(uint32_t mac) {
        std::string tmp;
        while(mac > 0) {
            std::stringstream ss;
            ss << std::hex << std::setw(2) << std::setfill('0') << (mac & 0x000000ff);
            tmp += ss.str() + ":";
            mac >>= 8;
        }
        tmp.pop_back();
        return tmp;
    }



}


#endif