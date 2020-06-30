#include <iostream>
//#include "MatrixOperations.h"
//#include "Printer.h"
#include "Stream.h"
#include <functional>
using namespace std;
class A{};
int main() {
    int N = 10;
    int array[N] = {9,9,7,7,7,8,1,2,3,4 };
    std::vector<int*> intPointerVector;
    for(int i = 0 ; i < N; i++) intPointerVector.push_back(array + i);

//    Stream<int> s = Stream<int>::of(intPointerVector).filter([](const int* val) { return (*val) > 2; });
    auto s = Stream<int>::of(intPointerVector).map<int>([](const int* val){ return new int(-*val); })
            .filter([](const int* val) { return (*val) < -1; })
            .distinct()
            .sorted();
    for(auto p : s.collect<vector<int*>>()){
        cout << *p << endl;
    }
    int x = 0;
    cout << *s.reduce(&x, [](const int* a,const int*b){ return new int(*a + *b);})<< endl;
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