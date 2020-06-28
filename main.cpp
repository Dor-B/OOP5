#include <iostream>
#include "MatrixOperations.h"
#include "Printer.h"

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
//    typedef X<> x;
    typedef List<Int<1>, Int<2>, Int<3>> l1;
    typedef List<
            List<Int<1>, Int<2>, Int<3>>,
            List<Int<0>, Int<1>, Int<0>>,
            List<Int<0>, Int<1>, Int<0>>
            > m1;
    typedef List<
            List<Int<3>, Int<2>, Int<1>>,
            List<Int<1>, Int<0>, Int<1>>
            > m2;
    typedef typename Multiply<m2, m1>::result res;
    Printer<res>::print(cout);
//    static_assert(List<int>)
    return 0;
}