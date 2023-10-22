#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <list>
#include <limits>
#include <map>
#include <cmath>
#include <deque>
#include <utility>
#include <functional>
#include <fstream>
        
using namespace std;

bool listSame(vector <int> list1,vector <int> list2){
	bool x = true;
	for (int i=0;i< list1.size();i++){
		if(list1[i] != list2[i])return false;
	}
	return true;
}

bool isMeta(vector <int> list){
	//inverse
	vector <int> listA(list.begin(), list.begin() + list.size()/2);
	vector <int> listB(list.begin() + list.size()/2, list.end());
	

	//the first
	
	for (int i =0; i< listA.size()/2;i++){
		if (listA >= listB) return false;
	}

	//the second
	for (int i =listA.size()/2 + (list.size()%2 !=0); i< listA.size();i++){
		if (listA < listB) return false;
	}

	reverse(listB.begin(), listB.end());
	//inverse
	bool inverse = listSame(listA, listB );
	return inverse;
}

        
int solution(vector <int> listA){
	int time = 0;
    

    while (time < listA.size() ){
    	if (isMeta(listA)) return time;

    	int x = listA[0];
    	listA.push_back(x);
    	listA.erase(listA.begin());
    	time ++;
    }
    return -1;


}

int main(){

    //automatically create output file txt, change input file direction, change output file location if needed

    string sourceFileName(__FILE__);
    string base = sourceFileName.substr(sourceFileName.find_last_of("\\") + 1, sourceFileName.find_last_of(".") - sourceFileName.find_last_of("\\") - 1);


    const char* filePathin = R"(C:\code\sublime text\meta cup 2023 round 2\input.txt)";                                                                              //change here
    ifstream inputFile(filePathin);
    if (!inputFile.is_open()) {
        cerr << "Error input" << endl;
        return 1;
    }
    const char* filePathout = R"(C:\code\sublime text\meta cup 2023 round 2\)";                                                                                           //change here
    ofstream outputFile(filePathout + base + ".txt");
    if (!outputFile.is_open()) {
        cerr << "Error output" << endl;
        return 1;
    }




   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   int numberOfCase;
   inputFile >> numberOfCase;

   int N;
 	vector <int> listA,listB;



    for(int x = 1; x <= numberOfCase; x++ ) {

    	inputFile >> N;
    	for (int i = 0; i< N;i++){
    		int a;
    		inputFile >> a;
    		listA.push_back(a);
    	}
    	for (int i = 0; i< N;i++){
    		int a;
    		inputFile >> a;
    		listB.push_back(a);
    	}
    	vector <int> newlist;
    	merge(listA.begin(), listA.end(),listB.begin(), listB.end(),newlist.begin());

        outputFile << "Case #" << x << ": " << solution(listA)<< endl;
        listA.clear();
        listB.clear();
 
    }


    inputFile.close();
    outputFile.close();

}