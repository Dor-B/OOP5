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

/// declaration hack
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
    /// special of for maps, uses values only
    template <typename KeyType, typename DataType>
    static Stream<DataType> of(map<KeyType, DataType*>& container){
        return getInstance<DataType>([container]() -> vector<DataType*> {
            vector <DataType*> v;
            for(auto& it : container) {
                v.push_back( it.second );
            }
            return v;
        });
    }

    template <typename Container>
    static Stream<ElemType> of(Container& container){
        return Stream<ElemType>(
        [container]() -> vector<ElemType*> {
            return vector<ElemType*>(container.begin(), container.end());
        });
    }

    template<typename Container>
    Container collect(){
        vector<ElemType*> v = compute();
        return Container(v.begin(), v.end());
    }

    void forEach(function<void(ElemType*)> forFunc){
        vector<ElemType*> v = compute();
        for(auto p: v){
            forFunc(p);
        }
    }

    const ElemType* reduce(const ElemType* initial,  function<ElemType*(const ElemType*, const ElemType*)> reduceFunc){
        vector<ElemType*> v = compute();
        // fold as described by pdf
        bool isFirst = true;
        for(auto elem :v){
            if(isFirst)
                initial = reduceFunc(initial, elem);
            else
                initial = reduceFunc(elem, initial);
            isFirst = false;
        }
        return initial;
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
        return distinct([](const ElemType* a, const ElemType* b){return *a==*b;});
    }

    Stream sorted(std::function<bool( ElemType*,  ElemType*)> sortingFunc = ([](ElemType* e1, ElemType* e2)->bool{return *e1<*e2;}) ){
        return SortedStream<ElemType>(*this, sortingFunc);
    }

    Stream() = default;
private:
    /// create Stream of ElemType
    Stream(std::function<vector<ElemType*>()> compute): compute(compute){};

    /// create Stream of generic type
    template <typename NewType>
    static Stream<NewType> getInstance(std::function<vector<NewType*>()> compute){
        Stream<NewType> s = Stream<NewType>();
        s.compute = compute;
        return s;
    }
};

/// class for lazy updating computing function according to filter
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
/// class for lazy updating computing function according to map
template <typename OldType, typename NewType>
class MapStream: public Stream<NewType> {
public:
    MapStream(Stream<OldType>& oldStream, std::function<NewType*(const OldType*)> mapFunc): Stream<NewType>(){
        this->compute = [oldStream, mapFunc]() -> vector<NewType*>{
            vector<OldType*> old = oldStream.compute();
            vector<NewType*> newV;
            transform(old.begin(), old.end(), std::back_inserter(newV), mapFunc);
            return newV;
        };
    }
};
/// class for lazy updating computing function according to distinct
template <typename ElemType>
class DistinctStream: public Stream<ElemType> {
public:
    DistinctStream(Stream<ElemType>& oldStream, function<bool(const ElemType*, const ElemType*)> distinctFunc): Stream<ElemType>(){
        this->compute = [oldStream, distinctFunc]() -> vector<ElemType*>{
            vector<ElemType*> old = oldStream.compute();
            vector<ElemType*> newV(old);
            /// remove duplicates (remains undefined)
            auto end = std::unique(newV.begin(), newV.end(), distinctFunc);
            /// remove undefineds
            newV.resize(std::distance(newV.begin(), end));
            return newV;
        };
    }
};
/// class for lazy updating computing function according to sorted
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
