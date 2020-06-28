#include <iostream>
//#include "MatrixOperations.h"
//#include "Printer.h"
#include "Stream.h"
#include <functional>
using namespace std;
class A{};
int main() {
    int array[10] = { 1, 2, 3, 2, 4, 6, 5, 7, 8, 9 };
    std::vector<int*> intPointerVector;
    for(int i = 0 ; i < 10 ; i++) intPointerVector.push_back(array + i);

//    Stream<int> s = Stream<int>::of(intPointerVector).filter([](const int* val) { return (*val) > 2; });
    auto s = Stream<int>::of(intPointerVector).map<int>([](const int* val){ return new int(-*val); })
            .filter([](const int* val) { return (*val) < -2; });
    for(auto p : s.compute()){
        cout << *p << endl;
    }
//    std::cout << "Hello, World!" << std::endl;
////    typedef X<> x;
//    typedef List<Int<1>, Int<2>, Int<3>> l1;
//    typedef List<
//            List<Int<1>, Int<2>, Int<3>>,
//            List<Int<0>, Int<1>, Int<0>>,
//            List<Int<0>, Int<1>, Int<0>>
//            > m1;
//    typedef List<
//            List<Int<3>, Int<2>, Int<1>>,
//            List<Int<1>, Int<0>, Int<1>>
//            > m2;
//    typedef typename Multiply<m2, m1>::result res;
//    Printer<res>::print(cout);
//    static_assert(List<int>)
    return 0;
}