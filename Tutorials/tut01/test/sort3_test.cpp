#include <string>
#include "catch2/catch.hpp"
#include "../source/sort3.cpp"
//void sort_three(int &num1, int &num2, int &num3);
//void sort_three(std::string str1, std::string str2, std::string str3);
TEST_CASE("sort3 for integers normal case") {
    int num1 = 5;
    int num2 = 4;
    int num3 = 9;
    sort_three(num1, num2, num3);
    CHECK(num1 == 4);
    CHECK(num2 == 5);
    CHECK(num3 == 9);
    CHECK(num1 <= num2);
    CHECK(num2 <= num3);
}

TEST_CASE("sort3 for integers repeated value") {
    int num1 = 5;
    int num2 = 9;
    int num3 = 5;
    sort_three(num1, num2, num3);
    CHECK(num1 == 5);
    CHECK(num2 == 5);
    CHECK(num3 == 9);
    CHECK(num1 <= num2);
    CHECK(num2 <= num3);
}

TEST_CASE("sort3 for negative integers") {
    int num1 = -5;
    int num2 = 9;
    int num3 = 5;
    sort_three(num1, num2, num3);
    CHECK(num1 == -5);
    CHECK(num2 == 5);
    CHECK(num3 == 9);
    CHECK(num1 <= num2);
    CHECK(num2 <= num3);
}

TEST_CASE("sort3 for integers all repeated value") {
    int num1 = 5;
    int num2 = 5;
    int num3 = 5;
    sort_three(num1, num2, num3);
    CHECK(num1 == 5);
    CHECK(num2 == 5);
    CHECK(num3 == 5);
    CHECK(num1 <= num2);
    CHECK(num2 <= num3);
}

TEST_CASE("sort3 for std::string, base case") {
    std::string str1 = "chello";
    std::string str2 = "bhello";
    std::string str3 = "ahello";
    sort_three(str1, str2,  str3);
    CHECK(str1 == "ahello");
    CHECK(str2 == "bhello");
    CHECK(str3 == "chello");
}

TEST_CASE("sort3 for std::string, different sized strings") {
    std::string str1 = "a";
    std::string str2 = "abc";
    std::string str3 = "aabc";
    sort_three(str1, str2,  str3);
    CHECK(str1 == "a");
    CHECK(str2 == "aabc");
    CHECK(str3 == "abc");
}

TEST_CASE("sort3 for std::string, adding numbers + special characters, ascii checkers") {
    std::string str1 = "1a";
    std::string str2 = "!a";
    std::string str3 = ">a";
    sort_three(str1, str2,  str3);
    CHECK(str1 == "!a");
    CHECK(str2 == "1a");
    CHECK(str3 == ">a");
}

TEST_CASE("sort3 for std::string, capitals vs no capitals ") {
    std::string str1 = "A";
    std::string str2 = "a";
    std::string str3 = "aB";
    sort_three(str1, str2,  str3);
    CHECK(str1 == "A");
    CHECK(str2 == "a");
    CHECK(str3 == "aB");
}
