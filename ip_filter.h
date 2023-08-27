#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char d);

struct Ip {
    explicit Ip(const std::string& v);

    bool operator<(const Ip& other) const;

    std::vector<u_int16_t> Ip_;
};

