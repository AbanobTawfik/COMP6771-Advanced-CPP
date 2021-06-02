#include <iostream>
// the main benefit is that this method avoids buffer overflow entirely by abstracting away the concept of a char
// array that can be potentially corrupted with extra input including commands, which get run/corrupt memory
// we get a safe and easy to use abstraction of string this way.
int main() {
    std::string buffer;
    std::getline(std::cin, buffer);
    std::cout << buffer << "\n";
	return 0;
}