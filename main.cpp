#include "matrix.h"
#include "timer.h"
#include <iomanip>
#include <iostream>
#include <ctime>


std::ostream& operator<<(std::ostream& os, const timespec &diff)
{
    os << diff.tv_sec << "." << std::setfill('0') << std::setw(9) << diff.tv_nsec << " s";
    return os;
}


template <class T, unsigned rows, unsigned cols>
std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols> &obj)
{
    for (unsigned i = 0; i < obj.Rows(); ++i)
    {
        for (unsigned j = 0; j < obj.Cols(); ++j)
        {
            os << obj(i, j) << '\t';
        }
        os << '\n';
    }
    return os;
}


int main(void)
{
    const int TIMES_RUN = 10;
    Matrix<float, 512, 512> A(RandFill), B(RandFill), C;

    /*
    A(0, 0) = 1,  A(0, 1) = 2,  A(0, 2) = 3,  A(0, 3) = 4;
    A(1, 0) = 5,  A(1, 1) = 6,  A(1, 2) = 7,  A(1, 3) = 8;
    A(2, 0) = 9,  A(2, 1) = 10, A(2, 2) = 11, A(2, 3) = 12;
    A(3, 0) = 13, A(3, 1) = 14, A(3, 2) = 15, A(3, 3) = 16;

    B(0, 0) = 1,  B(0, 1) = 2,  B(0, 2) = 3,  B(0, 3) = 4;
    B(1, 0) = 5,  B(1, 1) = 6,  B(1, 2) = 7,  B(1, 3) = 8;
    B(2, 0) = 9,  B(2, 1) = 10, B(2, 2) = 11, B(2, 3) = 12;
    B(3, 0) = 13, B(3, 1) = 14, B(3, 2) = 15, B(3, 3) = 16;
    */

    Timer timer;
    timer.Start();

    for (int i = 0; i < TIMES_RUN; ++i)
    {
        MultiplyNaive(&C, A, B);
    }

    timespec diff = timer.Stop();

    std::cout << "Using naive algorithm for matrix multiplication." << std::endl;
    std::cout << "Total time: " << diff << "\n\n";

    C.ZeroAll();
    timer.Start();

    for (int i = 0; i < TIMES_RUN; ++i)
    {
        MultiplyOuterProduct(&C, A, B);
    }

    diff = timer.Stop();

    std::cout << "Using outer product approach for matrix multiplication." << std::endl;
    std::cout << "Total time: " << diff << "\n\n";

    C.ZeroAll();
    const unsigned BLOCK_DIM = 16;
    timer.Start();

    for (int i = 0; i < TIMES_RUN; ++i)
    {
        MultiplyBlocked<BLOCK_DIM, BLOCK_DIM, BLOCK_DIM>(&C, A, B);
    }

    diff = timer.Stop();

    std::cout << "Using multiply by block algorithm for matrix multiplication." << std::endl;
    std::cout << "Total time: " << diff << std::endl;

    return 0;
}
