#include "comp6771/euclidean_vector.hpp"
#include <iostream>
#include <vector>
#include <chrono>
//  Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
    auto a = comp6771::euclidean_vector(6);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 200; j++) {
            if(j == 199){
                (void)j;
            }
            for (int k = 0; k < 200; k++) {
                a[0] = j;
                a[1] = k;
                a[2] = j;
                a[3] = k;
                a[4] = j;
                a[5] = k;

                comp6771::euclidean_norm(a);
            }
        }
        std::cout << comp6771::cache.size() << "\n";
        //std::cout << i << "\n";
    }

    //std::cout << comp6771::euclidean_norm(a) << "\n";
}
