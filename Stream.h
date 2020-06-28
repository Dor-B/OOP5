//
// Created by Dor on 6/28/2020.
//

#ifndef OOP5_STREAM_H
#define OOP5_STREAM_H

#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>

using std::vector;
using std::map;
using std::function;
using std::remove_if;
using std::transform;
using std::unique_copy;
using std::accumulate;

using std::cout;
using std::endl;

template <typename ElemType>
class Stream;

template <typename ElemType>
class FilterStream;

template <typename ElemType>
class DistinctStream;

template <typename OldType, typename NewType>
class MapStream;

template <typename ElemType>
class SortedStream;

template <typename ElemType>
class Stream{
public:
    std::function<vector<ElemType*>()> compute;
public:
    template <typename Container>
    static Stream of(Container& container){
        return Stream<ElemType>(
        [container]() -> vector<ElemType*> {
            return vector<ElemType*>(container.begin(), container.end());
        });
    }

//    template <typename KeyType>
//    static Stream of(map<KeyType, ElemType>& container){
//        return Stream<ElemType>([container]() -> vector<ElemType*> {
//            vector <ElemType> v;
//            for(typename map<KeyType, ElemType>::iterator it = container.begin(); it != container.end(); ++it ) {
//                v.push_back( it->second );
//            }
//            return v;
//        });
//    }

    template<typename Container>
    Container collect(){
        vector<ElemType*> v = compute();
        return Container(v.begin(), v.end());
    }

    void forEach(function<void(const ElemType*)> forFunc){
        vector<ElemType*> v = compute();
        for(auto p: v){
            forFunc(p);
        }
    }

    const ElemType* reduce(const ElemType* initial,  function<ElemType*(const ElemType*, const ElemType*)> reduceFunc){
        vector<ElemType*> v = compute();
        return std::accumulate(v.begin(), v.end(), initial, reduceFunc);
    }

    int count(){
        return compute().size();
    }

    bool anyMatch(function<bool(const ElemType*)> anyFunc){
        vector<ElemType*> v = compute();
        return std::any_of(v.begin(), v.end(), anyFunc);
    }

    bool allMatch(function<bool(const ElemType*)> anyFunc){
        vector<ElemType*> v = compute();
        return std::all_of(v.begin(), v.end(), anyFunc);
    }

    const ElemType* findFirst(function<bool(const ElemType*)> findFunc){
        vector<ElemType*> v = compute();
        auto it = std::find(v.begin(), v.end(), findFunc);
        return it != v.end() ? *it : nullptr;
    }

    Stream filter(std::function<bool(const ElemType*)> filterFunc){
        return FilterStream<ElemType>(*this, filterFunc);
    }

    template <typename NewType>
    Stream<NewType> map(std::function<NewType*(const ElemType*)> mapFunc){
        return MapStream<ElemType, NewType>(*this, mapFunc);
    }

    Stream distinct(function<bool(const ElemType*, const ElemType*)> distinctFunc){
        return DistinctStream<ElemType>(*this, distinctFunc);
    }

    Stream distinct(){
        return distinct([](const ElemType* a, const ElemType* b){return a==b;});
    }

    Stream sorted(std::function<bool( ElemType*,  ElemType*)> sortingFunc = ([](ElemType* e1, ElemType* e2)->bool{return *e1<*e2;}) ){
        return SortedStream<ElemType>(*this, sortingFunc);
    }

    Stream() = default;
private:
    Stream(std::function<vector<ElemType*>()> compute): compute(compute){};
};

template <typename ElemType>
class FilterStream: public Stream<ElemType> {
public:
    FilterStream(Stream<ElemType>& oldStream, std::function<bool(const ElemType*)> filterFunc)
    : Stream<ElemType>(){
        this->compute = [oldStream, filterFunc]()-> vector<ElemType*>{
            vector<ElemType*> old = oldStream.compute();
            vector<ElemType*> newV;
            std::copy_if (old.begin(), old.end(), std::back_inserter(newV), filterFunc);
            return newV;
        };
    }
};

template <typename OldType, typename NewType>
class MapStream: public Stream<NewType> {
public:
    MapStream(Stream<OldType>& oldStream, std::function<NewType*(const OldType*)> mapFunc): Stream<NewType>(){
        this->compute = [oldStream, mapFunc]() -> vector<NewType*>{
            vector<OldType*> old = oldStream.compute();
            vector<NewType*> newV;
//            for(auto p:old){
//                cout << *p << endl;
//            }
//            cout << "----------" << endl;
            transform(old.begin(), old.end(), std::back_inserter(newV), mapFunc);
            return newV;
        };
    }
};

template <typename ElemType>
class DistinctStream: public Stream<ElemType> {
public:
    DistinctStream(Stream<ElemType>& oldStream, function<bool(const ElemType*, const ElemType*)> distinctFunc): Stream<ElemType>(){
        this->compute = [oldStream, distinctFunc]() -> vector<ElemType*>{
            vector<ElemType*> old = oldStream.compute();
            vector<ElemType*> newV;
            std::unique_copy(old.begin(), old.end(), std::back_inserter(newV), distinctFunc);
            return newV;
        };
    }
};

template <typename ElemType>
class SortedStream: public Stream<ElemType> {
public:
    SortedStream(Stream<ElemType>& oldStream, std::function<bool( ElemType*, ElemType*)> sortFunc)
            : Stream<ElemType>(){
        this->compute = [oldStream, sortFunc]()-> vector<ElemType*>{
            vector<ElemType*> old = oldStream.compute();
            vector<ElemType*> newV;
            for (int i=0; i<old.size(); i++)
                newV.push_back(old[i]);
            std::sort (newV.begin(), newV.end(), sortFunc);
            return newV;
        };
    }
};

#endif //OOP5_STREAM_H
