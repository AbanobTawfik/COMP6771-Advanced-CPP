#include <iostream>

int main() {
    int input1;
    int input2;
    auto err_mssg = "Something went wrong while reading an integer, bailing...\n";
    std::cout << "Please enter two numbers: ";
    if(not (std::cin >> input1)){
        std::cerr << err_mssg;
        return 1;
    }
    if(not (std::cin >> input2)){
        std::cerr << err_mssg;
        return 1;
    }
    std::cout << "sum: " << input1+input2 << "\n";
	return 0;
}