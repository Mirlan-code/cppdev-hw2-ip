#include "ip_filter.h"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

void PrintIp(const vector<int>& ip) {
    cout << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3] << endl;
}

int main(int, char const **) {
    try {
        vector<vector<int>> ipPool;

        for (string line; getline(cin, line);) {
            vector<string> v = Split(Split(line, '\t').at(0), '.');
            vector<int> ip;
            for (const auto& i : v) {
                ip.push_back(stoi(i));
            }
            ipPool.push_back(ip);
        }

        auto res = GetFinalResult(ipPool);
        for (auto ip : res) {
            PrintIp(ip);
        }
    }
    catch (const exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
