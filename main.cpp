#include "ip_filter.h"

#include <string>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const Ip& ip) {
    os << ip.Ip_[0] << '.' << ip.Ip_[1] << '.' << ip.Ip_[2] << '.' << ip.Ip_[3];
    return os;
}

int main() {
    try {
        vector<Ip> ipPool;

        for(string line; getline(cin, line);) {
            vector<string> v = split(line, '\t');
            ipPool.push_back(Ip(v.at(0)));
        }

        sort(ipPool.rbegin(), ipPool.rend());

        for(const auto& ip : ipPool) {
            cout << ip << endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        vector<Ip> filtered;
        copy_if(ipPool.begin(), ipPool.end(), back_inserter(filtered), [](const Ip& a) {
            return a.Ip_[0] == 1;
        });
        for(const auto& ip : filtered) {
            cout << ip << endl;
        }
        filtered.clear();

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        copy_if(ipPool.begin(), ipPool.end(), back_inserter(filtered), [](const Ip& a) {
            return a.Ip_[0] == 46 && a.Ip_[1] == 70;
        });
        for(const auto& ip : filtered) {
            cout << ip << endl;
        }
        filtered.clear();

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        copy_if(ipPool.begin(), ipPool.end(), back_inserter(filtered), [](const Ip& a) {
            return a.Ip_[0] == 46 || a.Ip_[1] == 46 || a.Ip_[2] == 46 || a.Ip_[3] == 46;
        });
        for(const auto& ip : filtered) {
            cout << ip << endl;
        }
        filtered.clear();

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    } catch(const exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
