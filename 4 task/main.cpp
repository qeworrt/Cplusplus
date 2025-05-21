#include <mixins.cpp>

int main() {
    Number one{1};
    Number two{2};
    Number three{3};
    Number four{4};

    assert(one >= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);

    std::cout << "Count: " << counter<Number>::count() << std::endl;
    Number five{5};
    std::cout << "Count: " << counter<Number>::count() << std::endl;


    return 0;
}
