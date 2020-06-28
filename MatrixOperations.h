//
// Created by Dor on 6/28/2020.
//

#ifndef OOP5_MATRIXOPERATIONS_H
#define OOP5_MATRIXOPERATIONS_H

#include "Utilities.h"

template <typename Mat1, typename Mat2>
struct Add{
    typedef typename Mat1::next nextMat1Rows;
    typedef typename Mat2::next nextMat2Rows;

    typedef typename Mat1::head firstMat1Row;
    typedef typename Mat2::head firstMat2Row;

    typedef typename ListsAdd<firstMat1Row, firstMat2Row>::list firstRow;

    typedef typename Add<nextMat1Rows, nextMat2Rows>::result BellowRows;

    typedef typename PrependList<firstRow, BellowRows>::list result;
};

template <typename Row1, typename Row2>
struct Add<List<Row1>, List<Row2>>{
    typedef typename ListsAdd<Row1, Row2>::list firstRow;
    typedef List<firstRow> result;
};

/**
 * | --x1-- |   |     |    | x1*M |
 * | --x2-- | * |  M  | =  | x2*M |
 * | --x3-- |   |     |    | x3*M |
 */

template <typename Row, typename MatTranspose>
struct MultRowByMatTranspose{

};

template <typename Row, typename RowOfMat>
struct MultRowByMatTranspose<Row, List<RowOfMat>{

};

#endif //OOP5_MATRIXOPERATIONS_H
