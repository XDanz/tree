//
// Created by danter on 2017-04-10.
//
#include <string>
#include <iostream>

void f(std::initializer_list<int> list) {
    for(auto &elem  : list) {
        std::cout << " " << elem;
    }
    std::cout << std::endl;
    // the empty list
}
int
main(int argc, char **argv)
{
    f({1,2});

    f({23,345,4567,56789});
    f({}); // the empty list

    //f{1,2};
// error : function call () missing
}
