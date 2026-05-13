#include <iostream>
#include <map>
#include <string>
#include <set>

class Person{
    friend std::ostream &operator<<(std::ostream &os, const Person &p);
    std::string name;
    int age;
public:
    Person() : name{"Unknown"}, age{0} {}
    Person(std::string name, int age)
        : name{name}, age{age}{}

    bool operator<(const Person &rhs) const {
        return this->age < rhs.age;
    }

    bool operator==(const Person &rhs) const {
        return (this-> name == rhs.name && this->age == rhs.age);
    }
};

std::ostream &operator<<(std::ostream &os, const Person &p){
    os << p.name << ":" << p.age;
    return os;
}

void display(const std::map<std::string, std::set<int>> &m){
    std::cout << "[ ";
    for(const auto &element: m){
        std::cout << element.first << ": [ ";
        for(const auto &set_element: element.second)
            std::cout << set_element << " ";
        std::cout << "] ";
    }
    std::cout << "]" << std::endl;
}

template<typename T1, typename T2>
void display(const std::map<T1, T2> &l){
    std::cout << "[ ";
    for(const auto &i: l)
        std::cout << i.first << ":" << i.second << " ";
    std::cout << "]" << std::endl;
}

void test1(){
    std::cout << "\nTest1 =============================================" << std::endl;

    std::map<std::string, int> m {
        {"Larry", 3},
        {"Moe", 1},
        {"Curly", 2}
    };

    display(m);

    m.insert(std::pair<std::string, int>("Anna", 10));
    display(m);

    m.insert(std::make_pair("Joe", 5));
    display(m);

    m["Frank"] = 18;
    display(m);

    m["Frank"] +=10;
    display(m);

    m.erase("Frank");
    display(m);

    std::cout << "Count for Joe: " << m.count("Joe") << std::endl;
    std::cout << "Conut for Frank: " << m.count("Frank") << std::endl;

    auto it = m.find("Larry");
    if(it != m.end())
        std::cout << "Found: " << it->first << " : " << it->second << std::endl; 

    m.clear();
    display(m);
}

void test2(){
    std::cout << "\nTest2 =============================================" << std::endl;

    std::map<std::string, std::set<int>> grades{
        {"Larry", {100, 90}},
        {"Moe", {94}},
        {"Curly", {80, 90, 100}}
    };

    display(grades);

    grades["Larry"].insert(95);
    display(grades);

    auto it = grades.find("Moe");
    if(it != grades.end())
        it->second.insert(1000);
    display(grades);
}

int main (){
    
    test1();
    test2(); 
    
    return 0;
}