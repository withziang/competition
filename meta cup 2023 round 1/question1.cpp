#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
#include <limits>
#include <map>
#include <sstream>
#include <cmath>
#include <deque>
#include <utility>
#include <functional>
#include <fstream>
        
using namespace std;

long double solution(int a, vector <long int> elf){

    if (a ==5){

        return max(((long double)elf[4]+(long double)elf[3])*0.5  -  ((long double)elf[2] + (long double)elf[0])*0.5, ((long double)elf[4]+(long double)elf[2])*0.5- ((long double)elf[1] + (long double)elf[0])*0.5 );
    }else{
        return ((long double)elf[elf.size()-1] + (long double)elf[elf.size()-2])*0.5 -  ((long double) elf[1]+(long double) elf[0])*0.5;

    }

}

main(){

    //automatically create output file txt, change input file direction, change output file location if needed

    string sourceFileName(__FILE__);
    string base = sourceFileName.substr(sourceFileName.find_last_of("\\") + 1, sourceFileName.find_last_of(".") - sourceFileName.find_last_of("\\") - 1);


    const char* filePathin = R"(C:\Users\ziang\Downloads\here_comes_santa_claus_input.txt)";                                                                              //change here
    ifstream inputFile(filePathin);
    if (!inputFile.is_open()) {
        cerr << "Error input" << endl;
        return 1;
    }
    const char* filePathout = R"(C:\code\sublime text\meta cup 2023 round 1\)";                                                                                           //change here
    ofstream outputFile(filePathout + base + ".txt");
    if (!outputFile.is_open()) {
        cerr << "Error output" << endl;
        return 1;
    }




   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    vector <long int> input;
    int number;

    int cases;
    inputFile >> cases;


    long int x;

    int count = 1;

    while (count <= cases){
        inputFile >> number;

        for(int i=1; i<=number;i++){
            inputFile >> x;
            input.push_back(x);         
        }
        sort(input.begin(), input.end());
        outputFile << "Case #" << count << ": " << solution(number, input) << endl;


        input.clear();
        count ++;
    }




    inputFile.close();
    outputFile.close();

}