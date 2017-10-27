#include "stdafx.h"

void test_spatial_locality()
{
    const int M = 100, N = 10000;
    int arr[M][N];

    uint64_t start = SttGetTickCount();
    for (int i = 0; i < 10000; ++i)
    {
        int sum = 0;
        for (int m = 0; m < M; ++m)
        {
            for (int n = 0; n < N; ++n)
            {
                sum += arr[m][n];
            }
        }
    }

    cout << "locality cost " << SttGetTickCount() - start << "ms" << endl;

    start = SttGetTickCount();
    for (int i = 0; i < 10000; ++i)
    {
        int sum = 0;
        for (int n = 0; n < N; ++n)
        {
            for (int m = 0; m < M; ++m)
            {
                sum += arr[m][n];
            }
        }
    }

    cout << "pool locality cost " << SttGetTickCount() - start << "ms" << endl;

}

int main(int argc, char **argv)
{
    test_spatial_locality();

    return 0;
}
