#include "Set.h"
#include <iostream>

int main() {
    Set s1;
    for (int i = 0; i < 15; ++i)
        s1.add(i);

    std::cout << "Set s1: ";
    s1.print();

    Set s2;
    s2.add(5);
    s2.add(6);
    s2.add(100);

    std::cout << "Set s2: ";
    s2.print();

    Set s3 = s1.unionWith(s2);
    std::cout << "Union: ";
    s3.print();

    Set s4 = s1.intersectWith(s2);
    std::cout << "Intersection: ";
    s4.print();

    return 0;
}
