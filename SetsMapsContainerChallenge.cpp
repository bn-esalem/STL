#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>


void display_word(const std::map<std::string, int> &words){
    
    std::cout << std::setw(15) << std::left << "Word" << "Count" << std::endl;
    std::cout << "====================================" << std::endl;
    for(auto pair: words)
        std::cout << std::setw(15) << std::left << pair.first << pair.second << std::endl;
}


void display_word(const std::map<std::string, std::set<int>> &words){
    
    std::cout << std::setw(15) << std::left << "Word" << "Occurences" << std::endl;
    std::cout << "=====================================================" << std::endl;
    for(auto pair: words){
        std::cout << std::setw(15) << std::left << pair.first << std::left << "[ ";
        for(auto i: pair.second)
            std::cout << i << " ";
        std::cout << "]" << std::endl;
    }
}

std::string clean_string(const std::string &s) {
    std::string result;
    for (unsigned char c: s) {
        c = std::toupper(c);
        // isalnum() keeps only letters and digits and remove everything else
        //if (std::isalnum(c))
        if(std::isalpha(c))
            result += c;
    }
    return result;
}

void part1(){

    std::map<std::string, int> words;
    std::string line;
    std::string word;

    std::ifstream in_file {"Words.txt"};

    if(in_file){

        while(std::getline(in_file, line)){
            std::stringstream ss(line);   // split the line into "words" using white space
            while(ss >> word){
                word = clean_string(word);
                if(!word.empty())
                    words[word]++;
            }
        }

        in_file.close();
        display_word(words);

    }else
        std::cerr << "Error opening input file" << std::endl;
}

void part2(){
    
    std::map<std::string, std::set<int>> words;
    std::string line;
    std::string word;

    std::ifstream in_file {"Words.txt"};

    if(in_file){
        int line_number{0};
        while(std::getline(in_file, line)){
            line_number ++;
            std::stringstream ss(line);
            while(ss >> word)
            {
                word = clean_string(word);
                if(!word.empty())
                    words[word].insert(line_number);
            }
        }

        in_file.close();
        display_word(words);

    }else
        std::cerr << "Error opening input file" << std::endl;
}

int main (){

    part1();
    part2();
    
    return 0;
}