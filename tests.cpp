#include "ip_filter.h"
#include <gtest/gtest.h>

using namespace std;

TEST(TestsIpStruct, TestStructFilling) {
    string s = "1.10.2.255";
    Ip ip1{s};
    ASSERT_TRUE(ip1.Ip_[0] == 1);
    ASSERT_TRUE(ip1.Ip_[1] == 10);
    ASSERT_TRUE(ip1.Ip_[2] == 2);
    ASSERT_TRUE(ip1.Ip_[3] == 255);
}

TEST(TestsIpStruct, TestLess) {
    string ipStr1 = "1.10.2.2", ipStr2 = "1.2.2.2";
    Ip ip1{ipStr1};
    Ip ip2{ipStr2};
    ASSERT_TRUE(ip2 < ip1);
}

TEST(TestsSplit, TestSplitNormal) {
    string s = "1.2.3.4";
    vector<string> res{"1", "2", "3", "4"};
    ASSERT_EQ(split(s, '.'), res);
}

TEST(TestsSplit, TestSplitWithDifferentDelimiters) {
    string s = "1,111!22- 12.12312.2.3:44.4,2,123";
    vector<string> res{"1,111!22- 12", "12312", "2", "3:44", "4,2,123"};
    ASSERT_EQ(split(s, '.'), res);
}
