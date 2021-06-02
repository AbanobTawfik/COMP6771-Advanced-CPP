#include <iostream>
// declarations
void swap_int(int &num1, int &num2);
void swap_string(std::string &str1, std::string &str2);
void sort_three(int &num1, int &num2, int &num3);
void sort_three(std::string &str1, std::string &str2, std::string &str3);

//int main() {
//    int num1;
//    int num2;
//    int num3;
//    auto err_mssg = "Something went wrong while reading an integer, bailing...\n";
//    std::cout << "Please enter three objects: ";
//    if(not (std::cin >> num1)){
//        std::cerr << err_mssg;
//        return 1;
//    }
//    if(not (std::cin >> num2)){
//        std::cerr << err_mssg;
//        return 1;
//    }
//    if(not (std::cin >> num3)){
//        std::cerr << err_mssg;
//        return 1;
//    }
//    sort_three(num1, num2, num3);
//    std::cout << num1 << "-" << num2 << "-" << num3 << "\n";
//
//}

void sort_three(int &num1, int &num2, int &num3){
    if(num1 > num3){
        swap_int(num1, num3);
    }

    if(num1 > num2){
        swap_int(num1, num2);
    }

    if(num2 > num3){
        swap_int(num2, num3);
    }
}

void sort_three(std::string &str1, std::string &str2, std::string &str3){
    if(str1.compare(str3) > 0){
        swap_string(str1, str3);
    }
    if(str1.compare(str2) > 0){
        swap_string(str1, str2);
    }
    if(str2.compare(str3) > 0){
        swap_string(str2, str3);
    }
}

void swap_int(int &num1, int &num2){
    auto tmp = num1;
    num1 = num2;
    num2 = tmp;
}

void swap_string(std::string &str1, std::string &str2){
    auto tmp = str1;
    str1 = str2;
    str2 = tmp;
}