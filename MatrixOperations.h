//
// Created by Dor on 6/28/2020.
//

#ifndef OOP5_MATRIXOPERATIONS_H
#define OOP5_MATRIXOPERATIONS_H

#include "Utilities.h"
#include "Transpose.h"

template <typename Mat1, typename Mat2>
struct Add{
    static_assert(Mat1::size == Mat2::size, "Not the same rows number!");
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
    typedef typename MatTranspose::next nextMatCols;

    typedef typename MatTranspose::head firstMatCol;

    typedef typename VectorMult<Row, firstMatCol>::res scalar;

    typedef typename MultRowByMatTranspose<Row, nextMatCols>::res RowResTail;

    typedef typename PrependList<scalar, RowResTail >::list res;
};

template <typename Row, typename RowOfMat>
struct MultRowByMatTranspose<Row, List<RowOfMat>>{
    typedef typename VectorMult<Row, RowOfMat>::res scalar;
    typedef List<scalar> res;
};

template <typename Mat1, typename Mat2Transpose>
struct _Multiply{
    typedef typename Mat1::head firstMat1Row;
    typedef typename Mat1::next nextMat1Row;

    typedef typename MultRowByMatTranspose<firstMat1Row, Mat2Transpose>::res firstRow;

    typedef typename _Multiply<nextMat1Row, Mat2Transpose>::result BellowRows;

    typedef typename PrependList<firstRow, BellowRows>::list result;
};

template <typename Row1, typename Mat2>
struct _Multiply<List<Row1>, Mat2>{
    typedef typename MultRowByMatTranspose<Row1, Mat2>::res firstRow;
    typedef List<firstRow> result;
};

template <typename Mat1, typename Mat2>
struct Multiply {
    typedef typename Transpose<Mat2>::matrix Mat2T;
    typedef typename _Multiply<Mat1, Mat2T>::result result;
};

#endif //OOP5_MATRIXOPERATIONS_H
