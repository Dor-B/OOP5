#include <iostream>
#include "Utilities.h"
#include "Printer.h"

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
//    typedef X<> x;
    typedef List<Int<1>, Int<2>, Int<3>> l1;
    typedef List<Int<3>, Int<2>, Int<1>> l2;
    typedef typename ListsAdd<l1, l2>::list sum;
    Printer<sum>::print(cout);
//    static_assert(List<int>)
    return 0;
}