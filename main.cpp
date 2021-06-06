#include <iostream>
#include <vector>
#include <random>
#include <chrono>

void merge(std::vector<int>& v, size_t start, size_t middle, size_t end){
    std::vector<int> leftArray(middle - start + 1);
    std::vector<int> rightArray(end - middle);
    size_t leftIt {}, rightIt {}, currentIt {start};

    for(size_t i = 0; i < leftArray.size(); i++)
        leftArray[i] = v[start + i];

    for (size_t i = 0; i < rightArray.size(); ++i)
        rightArray[i] = v[middle + 1 + i];

    while(leftIt < leftArray.size() && rightIt < rightArray.size()){
        if(leftArray[leftIt] <= rightArray[rightIt]){
            v[currentIt] = leftArray[leftIt];
            leftIt++;
        } else {
            v[currentIt] = rightArray[rightIt];
            rightIt++;
        }
        currentIt++;
    }

    while(leftIt < leftArray.size())
        v[currentIt++] = leftArray[leftIt++];

    while(rightIt < rightArray.size())
        v[currentIt++] = rightArray[rightIt++];
}

void mergeSort(std::vector<int>& v, size_t start, size_t end){
    int middle{};
    if(start < end){
        middle = (start + end) / 2;
        mergeSort(v, start, middle);
        mergeSort(v, middle + 1, end);
        merge(v, start, middle, end);
    }
}

int main(){
    using namespace std::chrono;

    std::vector<int> v;

    std::random_device rd;
    std::uniform_int_distribution<>ud(0, 10000);

    for(size_t i = 0; i < 100000; i++){
        v.emplace_back(ud(rd));
    }

    high_resolution_clock::time_point start, end;

    // for(const auto& e : v)
    //     std::cout << e << ' ';
    // std::cout << '\n';

    start = high_resolution_clock::now();
    mergeSort(v, 0, 99999);
    end = high_resolution_clock::now();

    // for(const auto& e : v)
    //     std::cout << e << ' ';
    // std::cout << '\n';

    std::cout << "Merge sort 100000 elements: " << duration_cast<duration<double>>(end - start).count() << " seconds." << std::endl;
    return 0;
}
