#ifndef UTILS_HPP
#define UTILS_HPP

#include <inttypes.h>
#include <iostream>
#include <string>

namespace utils {
    std::string pp_ip(uint32_t ip) {
        std::string tmp;
        while(ip > 0) {
            tmp += std::to_string(ip & 0x000000ff) + ".";
            ip >>= 8;
        }
        tmp[tmp.size() - 1] = '\0';
        return tmp;
    }

}


#endif