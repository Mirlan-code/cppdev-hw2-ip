#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>


using namespace std;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
vector<string> Split(const string &str, char d) {
    vector<string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while (stop != string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void PrintIp(const vector<string>& ip) {
    cout << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3] << endl;
}

int main(int, char const **) {
    try {
        vector<vector<string>> ip_pool;

        for (string line; getline(cin, line);) {
            vector<string> v = Split(line, '\t');
            ip_pool.push_back(Split(v.at(0), '.'));
        }

        sort(ip_pool.rbegin(), ip_pool.rend(), [](const vector<string>& a, const vector<string>& b) -> bool {
            vector<int> aInt = {stoi(a[0]), stoi(a[1]), stoi(a[2]), stoi(a[3])};
            vector<int> bInt = {stoi(b[0]), stoi(b[1]), stoi(b[2]), stoi(b[3])};
            return tie(aInt[0], aInt[1], aInt[2], aInt[3]) < tie(bInt[0], bInt[1], bInt[2], bInt[3]);
        });

        for (auto ip : ip_pool) {
            PrintIp(ip);
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output

        vector<vector<string>> filtered;
        copy_if(ip_pool.begin(), ip_pool.end(), back_inserter(filtered), [](const vector<string>& a) {
           return a[0] == "1";
        });
        for (auto i : filtered) {
            PrintIp(i);
        }
        filtered.clear();



        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        copy_if(ip_pool.begin(), ip_pool.end(), back_inserter(filtered), [](const vector<string>& a) {
            return a[0] == "46" && a[1] == "70";
        });
        for (auto i : filtered) {
            PrintIp(i);
        }
        filtered.clear();

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        copy_if(ip_pool.begin(), ip_pool.end(), back_inserter(filtered), [](const vector<string>& a) {
            return any_of(a.begin(), a.end(), [](const string& part){
                return part == "46";
            });
        });
        for (auto i : filtered) {
            PrintIp(i);
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
    }
    catch (const exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
