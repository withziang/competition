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

//other idea, put black in every .




vector <vector <pair<int,int>>> groups; //group => member(x,y)

vector <pair<int,int>> beenThere;

vector <pair<int,int>> temp;

//find groups, find air holes of each group, or

vector <pair<int,int>> dotBeenthere;

int countAirHoles(vector <vector<char>> chessBoard, vector <pair<int,int>> group){
    dotBeenthere.clear();
    int count = 0;

    for (auto a: group){ // a is pair
        //left
        if (0 <= (a.second-1) && chessBoard[a.first][a.second-1] == '.' && find(dotBeenthere.begin(), dotBeenthere.end(), make_pair(a.first,a.second-1)) == dotBeenthere.end()){
            count++;
            dotBeenthere.push_back(make_pair(a.first,a.second-1));
        }
        //right
        if ((a.second+1) < chessBoard[0].size() && chessBoard[a.first][a.second+1] == '.'&& find(dotBeenthere.begin(), dotBeenthere.end(), make_pair(a.first,a.second+1)) == dotBeenthere.end()){
            count++;
            dotBeenthere.push_back(make_pair(a.first,a.second+1));
        }
        //top
        if (0 <= (a.first-1) && chessBoard[a.first-1][a.second] == '.'&& find(dotBeenthere.begin(), dotBeenthere.end(), make_pair(a.first-1,a.second)) == dotBeenthere.end()){
            count++;
            dotBeenthere.push_back(make_pair(a.first-1,a.second));
        }
        //buttom
        if ((a.first+1) < chessBoard.size() && chessBoard[a.first+1][a.second] == '.'&& find(dotBeenthere.begin(), dotBeenthere.end(), make_pair(a.first+1,a.second)) == dotBeenthere.end()){
            count++;
            dotBeenthere.push_back(make_pair(a.first+1,a.second));
        }
    }

    return count;

}

void addGroup(vector <vector<char>> chessBoard, int i, int j){
    //left
    if (0 <= (j-1) && chessBoard[i][j-1] =='W'&& (find(beenThere.begin(), beenThere.end(), make_pair(i,j-1)) ==beenThere.end())){
        temp.push_back(make_pair(i,j-1));
        beenThere.push_back(make_pair(i,j-1));
        addGroup(chessBoard,i,j-1);
    }
    //right
    if ((j+1) < chessBoard[0].size()&& chessBoard[i][j+1] =='W'&&(find(beenThere.begin(), beenThere.end(), make_pair(i,j+1)) ==beenThere.end())){
        temp.push_back(make_pair(i,j+1));
        beenThere.push_back(make_pair(i,j+1));
        addGroup(chessBoard,i,j+1);
    }
    //top
    if (0 <= (i-1)&& chessBoard[i-1][j] =='W'&&(find(beenThere.begin(), beenThere.end(), make_pair(i-1,j)) ==beenThere.end())){
        temp.push_back(make_pair(i-1,j));
        beenThere.push_back(make_pair(i-1,j));
        addGroup(chessBoard,i-1,j);
    }
    //buttom
    if ((i+1) < chessBoard.size()&& chessBoard[i+1][j] =='W'&&(find(beenThere.begin(), beenThere.end(), make_pair(i+1,j)) ==beenThere.end())){
        temp.push_back(make_pair(i+1,j));
        beenThere.push_back(make_pair(i+1,j));
        addGroup(chessBoard,i+1,j);
    }

}

void formGroups(vector <vector<char>> chessBoard){
    for (int i = 0; i< chessBoard.size();i++){
        for (int j =0;j< chessBoard[0].size();j++){
            if (chessBoard[i][j] == 'W' && (find(beenThere.begin(), beenThere.end(), make_pair(i,j)) ==beenThere.end() )){
                beenThere.push_back(make_pair(i,j));
                temp.push_back(make_pair(i,j));
                addGroup(chessBoard,i,j);

                groups.push_back(temp);
                temp.clear();
            }
        }
    }
}

bool canCapture(vector <vector<char>> chessBoard){
    formGroups(chessBoard);

/*
    for (auto a: groups){
        for (auto b:a){
            cout << b.first << " " << b.second << "     " ;
        }
        cout << endl;
    }
*/
    for (auto a: groups){
        int airhole = countAirHoles(chessBoard,a);
        bool can = (airhole < 2) ? true: false;
        if (can) return true;
    }
    return false;

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

   int row, column;

   vector <vector<char>> chessBoard; //row,column


   
    for(int x = 1; x <= numberOfCase; x++ ) {
        inputFile >> row >> column;

        for (int i = 0; i < row;i++){
            vector <char> eachrow;
            for (int j = 0; j< column;j++){
                char mychar;
                inputFile >> mychar;
                eachrow.push_back(mychar);
            }
            chessBoard.push_back(eachrow);
        }

        string output = (canCapture(chessBoard)) ? "YES" : "NO";


        outputFile << "Case #" << x << ": " << output << endl;
        chessBoard.clear();
        groups.clear();
        beenThere.clear();

    }
    

    inputFile.close();
    outputFile.close();

}