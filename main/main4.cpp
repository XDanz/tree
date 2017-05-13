//
// Created by danter on 2017-04-10.
//
#include <string>
#include <iostream>

struct X {
    X(std::initializer_list<int>) {
        std::cout << "initializer_list" << std::endl;
    }
    X() {
        std::cout << "X()" << std::endl;
    }
    X(int) {
        std::cout << "X(int)" << std::endl;
    }
};

int
main(int argc, char **argv)
{
    X x0 {}; // empty list: default constructor or initializer-list constructor? (the default constructor)
    X x1 {1}; // one integer: an int argument or a list of one element? (the initializer-list constructor)
    X x2 (1);
}
