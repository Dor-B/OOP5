//
// Created by Dor on 6/28/2020.
//

#ifndef OOP5_UTILITIES_H
#define OOP5_UTILITIES_H

#include "ListT.h"
template <int x>
struct Int{
    static constexpr int value = x;
};

template<typename T>
struct GetFirst {};

template<typename T>
struct GetNext {};

template<typename... TT>
struct List {
    static constexpr int size = sizeof...(TT);
    typedef typename GetFirst<List<TT...>>::head head;
    typedef typename GetNext<List<TT...>>::next next;
};



template<typename T, typename... TT>
struct GetFirst< List<T, TT... > > {
    typedef T head;
};

template<typename T, typename... TT>
struct GetNext< List<T, TT... > > {
    typedef List<TT...> next;
};

template<typename T, typename U>
struct PrependList {};

template<typename T, typename... TT>
struct PrependList<T, List<TT... > > {
    typedef List<T, TT... > list;
};

template<int n, typename ... TT>
struct ListGet {};

template <typename T, typename ... TT>
struct ListGet<0, List<T, TT...>>{
    typedef typename List<T, TT...>::head value;
};

template<int n,typename T, typename... TT>
struct ListGet<n, List<T, TT... > > {
    typedef typename ListGet<n-1, List<TT...>>::value value;
};

template<int n, typename ToAdd ,typename T, typename ... TT>
struct ListSet {};

template <typename ToAdd, typename T, typename ... TT>
struct ListSet<0,ToAdd , List<T, TT...>>{
    typedef typename PrependList<ToAdd, List<TT...>>::list list;
};

template<int n, typename ToAdd, typename T, typename... TT>
struct ListSet<n, ToAdd,  List<T, TT... > > {
    typedef typename ListSet<n-1, ToAdd, List<TT...>>::list AddAfterList;
    typedef typename PrependList<T,  AddAfterList>::list list;
};

//template<typename Row1 ,typename Row2>
//struct ListsAdd {};

template<typename Row1 ,typename Row2>
struct ListsAdd{
    static_assert(Row1::size == Row2::size, "Not the same list size!");
    typedef typename Row1::head first1;
    typedef typename Row2::head first2;
    typedef typename Row1::next tail1;
    typedef typename Row2::next tail2;
    typedef typename ListsAdd<tail1, tail2 >::list AddNext;
    typedef List<Int<first1::value + first2::value>, AddNext> list;
};

template<typename Val1, typename Val2>
struct ListsAdd<List<Val1>, List<Val2>>{
    typedef List<Int<Val1::value + Val2::value>> list;
};

template<typename Row1 ,typename Row2>
struct VectorMult{
    static_assert(Row1::size == Row2::size, "Not the same list size!");
    typedef typename Row1::head first1;
    typedef typename Row2::head first2;
    typedef typename Row1::next tail1;
    typedef typename Row2::next tail2;
    typedef typename VectorMult<tail1, tail2>::res MultAndAddNext;
    typedef Int<first1::value * first2::value + MultAndAddNext::value> res;
};

template<typename Val1, typename Val2>
struct VectorMult<List<Val1>, List<Val2>>{
    typedef Int<Val1::value * Val2::value> res;
};
#endif //OOP5_UTILITIES_H
