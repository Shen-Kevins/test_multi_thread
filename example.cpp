#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <cmath>
#include "ThreadPool.h"

int main()
{
    
    //int thread_num = 64;
    int max = (int)std::pow(10,9);
    ThreadPool pool(256);
    for(int num = 1; num <= 256; num *= 2){
        //ThreadPool pool(256);
        std::vector<std::future<int>> results;
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num; ++i)
        {
            results.emplace_back(
                pool.enqueue([i, num, max] {
                    int ress = 0;
		    for(int jj = 0; jj < 3; jj++)
                        for(int j = i; j < max; j+= num)
                            ress += j;
                    return ress;
                }));
        }
        int res = 0;
        for(auto &&result : results)
        {
            res += result.get();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto timeinterval = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        // pool.~ThreadPool();
        std::cout <<"The CPU time with "+std::to_string(num)+" thread:" << timeinterval.count()<<"\t";
        std::cout <<"The result is:" << res << std::endl;
    }
    
    return 0;
}
