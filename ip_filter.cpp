#include "ip_filter.h"

#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &str, char d) {
    vector<string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

Ip::Ip(const string& v) {
    vector<string> ip = split(v, '.');
    for (const auto& ip_part : ip) {
        Ip_.push_back(stoul(ip_part));
    }
}

bool Ip::operator<(const Ip& other) const {
    return Ip_ < other.Ip_;
}