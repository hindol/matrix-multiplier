#ifndef MATRIX_H
#define MATRIX_H


#include <cstdlib>
#include <iostream>
#include <stdexcept>


enum InitType { ZeroFill, RandFill };


template <class T, unsigned rows, unsigned cols>
class Matrix
{
public:
    typedef T           value_type;
    typedef unsigned    size_type;

    Matrix(InitType initType = ZeroFill)
    {
        if (initType == ZeroFill) ZeroAll();
        else if (initType == RandFill) RandAll();
    }

    void ZeroAll()
    {
        for (unsigned i = 0; i < rows; ++i)
        {
            for (unsigned j = 0; j < cols; ++j)
            {
                elem[i][j] = 0;
            }
        }
    }

    void RandAll()
    {
        srand(time(0L));
        for (unsigned i = 0; i < rows; ++i)
        {
            for (unsigned j = 0; j < cols; ++j)
            {
                elem[i][j] = rand();
            }
        }
    }

    // Accessor
    inline const value_type &operator ()(size_type row, size_type col) const
    {
        if (!(row < rows) || !(col < cols)) { throw std::out_of_range("Out of bound access!"); }
        return elem[row][col];
    }

    // Accessor + modifier
    inline value_type &operator ()(size_type row, size_type col)
    {
        return const_cast<T &>( // Throw away the constness
                    static_cast<const Matrix *>(this)->operator ()(row, col) // Call the const version
                    );
    }

private:
    value_type elem[rows][cols];
};


template <class T, unsigned rowsLhs, unsigned common, unsigned colsRhs>
void MultiplyNaive(Matrix<T, rowsLhs, colsRhs> *const res,
                   const Matrix<T, rowsLhs, common> &lhs,
                   const Matrix<T, common, colsRhs> &rhs)
{
    /* Naive way of multiplying matrices. */
    for (unsigned i = 0; i < rowsLhs; ++i)
    {
        for (unsigned j = 0; j < colsRhs; ++j)
        {
            for (unsigned k = 0; k < common; ++k)
            {
                (*res)(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
}


template <class T, unsigned rowsLhs, unsigned common, unsigned colsRhs>
void MultiplyOuterProduct(Matrix<T, rowsLhs, colsRhs> *const res,
                          const Matrix<T, rowsLhs, common> &lhs,
                          const Matrix<T, common, colsRhs> &rhs)
{
    /* Outer product. */
    for (unsigned k = 0; k < common; ++k)
    {
        for (unsigned i = 0; i < rowsLhs; ++i)
        {
            for (unsigned j = 0; j < colsRhs; ++j)
            {
                (*res)(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
}


/**
 * P = Block height of lhs
 * Q = Block width of lhs = Block height of rhs
 * R = Block width of rhs
 */
template <unsigned P, unsigned Q, unsigned R,
          class T, unsigned rowsLhs, unsigned common, unsigned colsRhs>
void MultiplyBlocked(Matrix<T, rowsLhs, colsRhs> *const res,
                     Matrix<T, rowsLhs, common> lhs,
                     Matrix<T, common, colsRhs> rhs)
{
    /* Matrix multiplication by blocks. */
    const unsigned COUNT_X = (rowsLhs - 1) / P + 1;
    const unsigned COUNT_Y = (colsRhs - 1) / R + 1;
    const unsigned COUNT_Z = (common - 1) / Q + 1;

    for (unsigned x = 0; x < COUNT_X; ++x)
    {
        for (unsigned y = 0; y < COUNT_Y; ++y)
        {
            for (unsigned z = 0; z < COUNT_Z; ++z)
            {
                for (unsigned i = P * x, endI = std::min(P * (x + 1), rowsLhs); i < endI; ++i)
                {
                    for (unsigned j = R * y, endJ = std::min(R * (y + 1), colsRhs); j < endJ; ++j)
                    {
                        for (unsigned k = Q * z, endK = std::min(Q * (z + 1), common); k < endK; ++k)
                        {
                            (*res)(i, j) += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
            }
        }
    }
}


#endif // MATRIX_H
