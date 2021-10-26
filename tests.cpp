#define BOOST_TEST_MODULE test_version

#include "ip_filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(testSplit)
{
    std::string ip = "46.161.56.106";
    auto res = Split(ip, '.');
    BOOST_CHECK(res.size() == 4);
    BOOST_CHECK(res[0] == "46" && res[1] == "161" && res[2] == "56" && res[3] == "106");
}

BOOST_AUTO_TEST_CASE(testFinalResult)
{
    std::vector<std::vector<int>> ipPool;
    ipPool.push_back({1, 2, 3, 46});
    auto res = GetFinalResult(ipPool);
    std::vector<std::vector<int>> checkRes = {{1, 2, 3, 46}, {1, 2, 3, 46}, {1, 2, 3, 46}, };

    BOOST_CHECK(res.size() == checkRes.size());
    for (size_t i = 0; i < checkRes.size(); i++) {
        BOOST_CHECK(res[i].size() == 4);
        for (int j = 0; j < 4; j++) {
            BOOST_CHECK(res[i][j] == checkRes[i][j]);
        }
    }
}

}