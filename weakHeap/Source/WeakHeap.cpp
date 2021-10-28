#include <iostream>
#include <ctime>
#include <fstream>

#include <chrono>

#include "WeakHeap.h"



WeakHeap::WeakHeap(){

}



bool WeakHeap::isWeakHeap(){

    size_t position = 0;
    bool flag = 0;

    for(size_t i = 0; i < arr.size(); i++){
        position = i * 2 + 1;
        if(arr[i] < arr[position] && position < arr.size()){
            flag = 1;
            break;
        }
    }

    if(arr.size() % 2){
        binSize = (arr.size() / 2) + 1;
    }else{
        binSize = (arr.size() / 2);
    }
    
    BIN.resize(arr.size());

    if(flag){
        return false;
    }else{
        return true;
    }
}



void WeakHeap::createWeakHeap(){

    int digit = 0;

    for(int i = arr.size() - 1; i >= 0; i--){

        digit = i;

        while(digit){   
            if((digit) % 2){
                digit = digit / 2;
                break;
            }else{
                digit = digit / 2;
            }
        }
        
        if(arr[i] > arr[digit]){
            if(i < binSize){
                BIN[i] = !BIN[i];
            }
            std::swap(arr[i], arr[digit]);
        }
    }
}



void WeakHeap::sortArr(){

    if(arr.size() < 2){
        exit(1);
    }

    clock_t t = clock();

    //std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    if(!isWeakHeap()){
        createWeakHeap();
    }

    size_t countNotSortArr = arr.size() - 1;
    size_t position = 1;

    std::vector<int> forLambdaArr = arr;
    std::vector<bool> forLambdaBIN = BIN;

    while(countNotSortArr){
        std::swap(forLambdaArr[0], forLambdaArr[countNotSortArr]);
        countNotSortArr--;

        auto PR = [&forLambdaArr, &forLambdaBIN, &countNotSortArr](size_t position, auto &&PR){

            if(position > countNotSortArr){
                return;
            }
            size_t newPosition = (position * 2) + forLambdaBIN[position];

            PR(newPosition, PR);
            if(forLambdaArr[position] > forLambdaArr[0]){
                std::swap(forLambdaArr[position], forLambdaArr[0]);
                forLambdaBIN[position] = !forLambdaBIN[position];
            }
        };

        PR(position, PR);
    }

    arr = forLambdaArr;

    double a = difftime(clock(), t);

    std::ofstream ft("result.txt", std::ios_base::app);

    //std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); //конец измерений
    //std::chrono::duration<double>a = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin); //подсчет разницы во времени

    ft << arr.size() << ' ';
    ft << a * 20 << '\n';
    //ft << a.count() * 10'000'000 << '\n';

    ft.close();

}