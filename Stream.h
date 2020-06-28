//
// Created by Dor on 6/28/2020.
//

#ifndef OOP5_STREAM_H
#define OOP5_STREAM_H

#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using std::vector;
using std::map;
using std::function;
using std::remove_if;
using std::transform;

using std::cout;
using std::endl;

template <typename ElemType>
class Stream;

template <typename ElemType>
class FilterStream;

template <typename OldType, typename NewType>
class MapStream;

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

    Stream filter(std::function<bool(const ElemType*)> filterFunc){
        return FilterStream<ElemType>(*this, filterFunc);
    }

    template <typename NewType>
    Stream<NewType> map(std::function<NewType*(const ElemType*)> mapFunc){
        return MapStream<ElemType, NewType>(*this, mapFunc);
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

#endif //OOP5_STREAM_H
