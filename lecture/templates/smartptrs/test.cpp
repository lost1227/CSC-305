#include <iostream>


class ABC {
public:
    ABC() { std::cout << "ABC()" << std::endl; }
    ABC(const ABC &other) { std::cout << "ABC(other)" << std::endl; }
    
    const ABC &operator=(const ABC &other) { std::cout << "operator=" << std::endl; return other;}
};

int main() {
    ABC a1;
    ABC a2(a1);
    ABC a3 {a1};
    ABC a4 = a1;
}
