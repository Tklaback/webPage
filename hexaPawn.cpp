#include <iostream>
#include <stdlib.h>
#include "hexaPawn.h"
#include <vector>
#include "graph.h"
#include <utility>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

class ChessBoard{
    public:
        int arr[3][3] = {0,0,0,0,0,0,0,0,0};
        
};

//FIXME: only validates the person's move
//bool ChessBoard::validateMove(const vector<int> &from, const vector<int> &to){
//    bool flag = false;
//    if (arr[from[0]][from[1]] != 1)return false;
//
//    return true;
//}


class Player{
    protected:
        virtual bool validateMove(const vector<int> &from, const vector<int> &to)=0;
        unsigned players;
        ChessBoard *board;
        virtual void movePiece(const string &from, const string &to)=0;
    public:
        Player(): players(3){}
};

class Person: public Player{
    std::pair<int, int> validMoves[3] = {std::make_pair<int,int>(-1,-1), 
    std::make_pair<int,int>(-1,0), std::make_pair<int,int>(-1,1)};
    public:
        Person(ChessBoard &obj){
            board = &obj;
            for (unsigned col=0;col< 3;col++){
                board->arr[2][col] = 1;
            }
        }
        bool validateMove(const vector<int> &from, const vector<int> &to);
        void movePiece(const string &from, const string &to);
};

void Person::movePiece(const string &from, const string &to){
    vector<int> fromNums = parseString(from);
    vector<int> toNums = parseString(to);
    if (validateMove(fromNums, toNums)){
        board->arr[toNums[0]][toNums[1]] = board->arr[fromNums[0]][fromNums[1]];
        board->arr[fromNums[0]][fromNums[1]] = 0;
    }
}

bool Person::validateMove(const vector<int> &from, const vector<int> &to){
    bool isValid = false;
    if (board->arr[from[0]][from[1]] != 1)return isValid;
    int first, second;
    for (unsigned move=0;move<3;move++){
        first = validMoves[move].first;
        second = validMoves[move].second;
        if (from[0] + first == to[0] && from[1] + second == to[1]){
            if ((to[0] <= 2 && to[0] >= 0) && (to[1] <= 2 && to[1] >= 0)){
                if (second != 0){
                    if (board->arr[to[0]][to[1]] == 2)isValid = true;
                }
                else{
                    if (board->arr[to[0]][to[1]] == 0)isValid = true;
                }
                
            }
        }
    }
    return isValid;
}


class Computer: public Player{
    static std::pair<int, int> makeChoice();
    std::pair<int, int> validMoves[3] = {std::make_pair<int,int>(1,-1), 
    std::make_pair<int,int>(1,0), std::make_pair<int,int>(1,1)};
    public:
        Computer(ChessBoard &obj){
            board = &obj;
            for (unsigned col=0;col< 3;col++){
                board->arr[0][col] = 2;
            }
        }
    bool validateMove(const vector<int> &from, const vector<int> &to);
    void movePiece(const string &from, const string &to);
};
std::pair<int, int> Computer::makeChoice(){
    srand(time(NULL));
    int myNum = rand() % 3;
    return validMoves[myNum];
}

void Computer::movePiece(const string &from, const string &to){
    makeChoice();
}

bool Computer::validateMove(const vector<int> &from, const vector<int> &to){
    bool isValid = false;
    if (board->arr[from[0]][from[1]] != 2)return isValid;
    int first, second;
    for (unsigned move=0;move<3;move++){
        first = validMoves[move].first;
        second = validMoves[move].second;
        if (from[0] + first == to[0] && from[1] + second == to[1]){
            if ((to[0] <= 2 && to[0] >= 0) && (to[1] <= 2 && to[1] >= 0)){
                if (second != 0){
                    if (board->arr[to[0]][to[1]] == 1)isValid = true;
                }
                else{
                    if (board->arr[to[0]][to[1]] == 0)isValid = true;
                }
                
            }
        }
    }
    return isValid;
}


int main(){
    ChessBoard myBoard;
    Person me(myBoard);
    Computer comp(myBoard);
    string from, to;
    print(myBoard.arr);
    cout << "Enter FROM position (i.e. 0 0): ";
    std::getline(cin, from);
    while (from != ""){
        cout << "\nEnter TO position (i.e. 1 0): ";
        std::getline(cin, to);
        me.movePiece(from, to);
        comp.movePiece(from, to);
        print(myBoard.arr);
        cout << "\nEnter FROM position (i.e. 0 0): ";
        std::getline(cin, from);
    }
    
    
    
    
}

