#include <iostream>
#include <stdlib.h>
#include "sandbox.h"
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

class ChessBoard{
    public:
        bool validateMove(const vector<int> &from, const vector<int> &to);
        int arr[3][3] = {0,0,0,0,0,0,0,0,0};
        
};

//FIXME: only validates the person's move
bool ChessBoard::validateMove(const vector<int> &from, const vector<int> &to){
    bool flag = false;
    if (arr[from[0]][from[1]] != 1)return false;
    return true;
}


class Player{
    protected:
        unsigned players;
        ChessBoard *board;
        virtual void movePiece(const string &from, const string &to)=0;
public:
    Player(): players(3){}
};

class Person: public Player{
    public:
        Person(ChessBoard &obj){
            board = &obj;
            for (unsigned col=0;col< 3;col++){
                board->arr[2][col] = 1;
            }
        }
    void movePiece(const string &from, const string &to);
};

void Person::movePiece(const string &from, const string &to){
    vector<int> fromNums = parseString(from);
    vector<int> toNums = parseString(to);
    if (board->validateMove(fromNums, toNums)){
        board->arr[toNums[0]][toNums[1]] = board->arr[fromNums[0]][fromNums[1]];
        board->arr[fromNums[0]][fromNums[1]] = 0;
    }
        
    
}

class Computer: public Player{
    public:
        Computer(ChessBoard &obj){
            board = &obj;
            for (unsigned col=0;col< 3;col++){
                board->arr[0][col] = 2;
            }
        }
    void movePiece(const string &from, const string &to){}
};


int main(){
    ChessBoard myBoard;
    Person me(myBoard);
    Computer comp(myBoard);
    string from, to;
    cout << "Enter FROM position (i.e. 0 0): ";
    std::getline(cin, from);
    while (from != ""){
        cout << "\nEnter TO position (i.e. 1 0): ";
        std::getline(cin, to);
        me.movePiece(from, to);
        cout << "\nEnter FROM position (i.e. 0 0): ";
        std::getline(cin, from);
    }
    
    print(myBoard.arr);
    
    
    
}

