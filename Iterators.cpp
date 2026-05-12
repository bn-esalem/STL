#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>


void display(const std::vector<int> &vec){
    std::cout << "[ ";
    for(auto const &i: vec){
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
}

void test1(){
    std::cout << "\n===============================================" << std::endl;
    std::vector<int> nums1{1, 2, 3, 4, 5};
    auto it = nums1.begin();  // "it" is an object but it acts like a pointer
    std::cout << *it << std::endl;

    it++;
    std::cout << *it << std::endl;

    it +=2;
    std::cout << *it << std::endl;

    it -=2;
    std::cout << *it << std::endl;

    it = nums1.end() -1;
    std::cout << *it << std::endl;
}

void test2(){
    std::cout << "\n===================================================" << std::endl;

    std::vector<int> nums2 {1, 2, 3, 4, 5};

    std::vector<int>::iterator it2 = nums2.begin();
    while(it2 != nums2.end()){
        std::cout << *it2 << std::endl;
        it2++;
    }

    it2 = nums2.begin();
    while (it2 != nums2.end())
    {
        *it2 = 0;
        it2++;
    }

    display(nums2);    
}

void test3(){
    std::vector<int> vec {1, 2, 3, 4, 5};
    auto it1 = vec.rbegin();   // rbegin() reverse iterator over vector of ints starts at 5
    while(it1 != vec.rend()){
        std::cout << *it1 << std::endl;
        it1++;
    }

    // const reverse iterator over a list
    std::list<std::string> names {"Larry", "Moe", "Curly"};
    auto it2 = names.crbegin();
    std::cout << *it2 << std::endl;
    it2++;
    std::cout << *it2 << std::endl;

    //Iterators over map
    std::map<std::string, std::string> favorites{
        {"Frank", "C++"},
        {"Bill", "Java"},
        {"James", "Haskell"}
    };

    auto it3 = favorites.begin();
    while (it3 != favorites.end())
    {
        std::cout << it3->first << ": " << it3->second << std::endl;
        it3++;
    } 
}

// iterate over a subset of a container
void test4(){
    std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto start = vec.begin() + 2;
    auto finish = vec.end() - 3;

    while(start != finish){
        std::cout << *start << std::endl;
        start++;
    }
}

int main (){

    //test1();
    //test2();
    //test3();
    test4();

    return 0;
}