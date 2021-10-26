#include "ip_filter.h"

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
    vector <string> r;

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

vector<vector<int>> GetFinalResult(vector<vector<int>>& ipPool) {
    vector<vector<int>> res;

    sort(ipPool.rbegin(), ipPool.rend(), [](const vector<int>& a, const vector<int>& b) -> bool {
        return tie(a[0], a[1], a[2], a[3]) < tie(b[0], b[1], b[2], b[3]);
    });

    for (auto ip : ipPool) {
        res.push_back(ip);
    }

    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first byte and output

    vector<vector<int>> filtered;
    copy_if(ipPool.begin(), ipPool.end(), back_inserter(filtered), [](const vector<int>& a) {
        return a[0] == 1;
    });
    for (auto ip : filtered) {
      res.push_back(ip);
    }
    filtered.clear();



    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)

    copy_if(ipPool.begin(), ipPool.end(), back_inserter(filtered), [](const vector<int>& a) {
        return a[0] == 46 && a[1] == 70;
    });
    for (auto ip : filtered) {
        res.push_back(ip);
    }
    filtered.clear();

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    // TODO filter by any byte and output
    // ip = filter_any(46)
    copy_if(ipPool.begin(), ipPool.end(), back_inserter(filtered), [](const vector<int>& a) {
        return any_of(a.begin(), a.end(), [](const int& part){
            return part == 46;
        });
    });
    for (auto ip : filtered) {
        res.push_back(ip);
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

    return res;
}