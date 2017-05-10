#include <iostream>

class A {
public:
    A(const std::initializer_list<std::string>& list) {
        for (auto s: list)
            std::cout << "s:" << s << std::endl;
    }
};

int main() {
    std::cout << "Hello, World! cp barn hur mår du" << std::endl;
    std::string h  = "h";
    std::string j = "j";
    A a  = {"h", "j"};

    return 0;

}
