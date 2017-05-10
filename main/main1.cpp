//
// Created by danter on 2017-04-10.
//
#include <string>
#include <iostream>
#include <tree.h>

int
main(int argc, char **argv)
{
    std::string s0 = {"C1"};
    std::string s1 = {"C2"};

    Tree t = {"C0", {"C", "C1", "s3"}};
    Tree::Iterator it = t.begin();
    for  (it; it != t.end(); it++)
        std::cout << *it << std::endl;


    //t.print();
 // todo::
}
