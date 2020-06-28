//
// Created by Dor on 6/28/2020.
//

#ifndef OOP5_STREAM_H
#define OOP5_STREAM_H

#include <vector>
#include <map>

using std::vector, std::map;
template <typename ElemType>
class Stream{
    vector<ElemType> initialVector;
public:
    template <typename Container>
    static Stream of(Container& container){
        return Stream(vector<ElemType>(container.begin(), container.end()));
    }

//    template <typename KeyType>
//    static Stream of<map<KeyType, ElemType>> (map<KeyType, ElemType>& container){
//        return Stream(vector<ElemType>(container.begin()))
//    }
private:
    Stream(vector<ElemType> initialVector): initialVector(initialVector){};
};

#endif //OOP5_STREAM_H
