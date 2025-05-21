#include <typeList.cpp>

int main() {
    using namespace tlist;

    using MyList = typeList<int, double, char>;

    static_assert(size<MyList>::value == 3);

    static_assert(std::is_same_v<typeAt<0, MyList>::type, int>);
    static_assert(std::is_same_v<typeAt<1, MyList>::type, double>);
    static_assert(std::is_same_v<typeAt<2, MyList>::type, char>);

    static_assert(contains<int, MyList>::value);
    static_assert(!contains<float, MyList>::value);

    static_assert(indexOf<int, MyList>::value == 0);
    static_assert(indexOf<char, MyList>::value == 2);

    using FrontAdded = pushFront<bool, MyList>::type;
    static_assert(std::is_same_v<typeAt<0, FrontAdded>::type, bool>);
    static_assert(size<FrontAdded>::value == 4);

    using BackAdded = pushBack<long, MyList>::type;
    static_assert(std::is_same_v<typeAt<3, BackAdded>::type, long>);
    static_assert(size<BackAdded>::value == 4);
}