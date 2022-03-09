#include <iostream>
#include <stdlib.h>
#include "hexaPawn.h"
#include "search.h"


using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

class Victory{
    friend class Person;
    friend class Computer;
    bool compWin = false;
    bool personWin = false;
    public:
        bool youWin(){
            if (personWin == true){
                return true;
            }
            return false;
        }
        bool computerWins(){
            if (compWin == true){
                return true;
            }
            return false;
        }
        void reset(){
            compWin = false;
            personWin = false;
        }
};

class Player{
    protected:
        // virtual bool validateMove(const vector<int> &from, const vector<int> &to)=0;
        unsigned players;
        ChessBoard *board;
        // virtual void movePiece(const string &from, const string &to)=0;
    public:
        Player(): players(3){}
};

class Person: public Player{
    std::pair<int, int> validMoves[3] = {std::make_pair<int,int>(-1,-1), 
    std::make_pair<int,int>(-1,0), std::make_pair<int,int>(-1,1)};
    Victory *status;
    PersonPawns ogPawns;
    public:
        void setBoard(){
            for (unsigned col=0;col< 3;col++){
                board->arr[2][col] = 1;
            }
        }
        Person(ChessBoard &obj, Victory &status){
            this->status = &status;
            board = &obj;
            setBoard();
        }
        bool validateMove(const vector<int> &from, const vector<int> &to);
        void movePiece(const string &from, const string &to);
};

void Person::movePiece(const string &from, const string &to){
    if (!ogPawns.canMove(validMoves, board)){
        status->compWin = true;
        return;
    }
    vector<int> fromNums = parseString(from);
    vector<int> toNums = parseString(to);
    if (validateMove(fromNums, toNums)){
        ogPawns.changePawn(fromNums, toNums);
        board->arr[toNums[0]][toNums[1]] = board->arr[fromNums[0]][fromNums[1]];
        board->arr[fromNums[0]][fromNums[1]] = 0;
        if (toNums[0] == 0){
            status->personWin = true;
        }
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
    Choice makeChoice();
    std::pair<int, int> validMoves[3] = {std::make_pair<int,int>(1,-1), 
    std::make_pair<int,int>(1,0), std::make_pair<int,int>(1,1)};
    Pawns og;
    Victory *status;
    std::vector<Choice> temp;
    public:
        void setBoard(){
            og.reset();
            for (unsigned col=0;col< 3;col++){
                board->arr[0][col] = 2;
            }
        }
        Computer(ChessBoard &obj, Victory &status){
            this->status = &status;
            board = &obj;
            setBoard();
        }
    bool validateMove(const std::pair<int, int> &from, const std::pair<int, int> &to);
    void movePiece();
};

std::vector<Choice> failure;

Choice Computer::makeChoice(){
    if (!temp.empty()){
        if (status->personWin == true){
            cout << "INSERTING" << endl;
            failure.push_back(temp.back());
            temp.pop_back();
            Choice none;
            return none;
        }
    }
    for (int pawn=0;pawn<og.pawns.size();pawn++){
        for (int move=0;move<3;move++){ //size of validMoves
            // cout << og.pawns[pawn].first << " " << og.pawns[pawn].second << endl;
            if (validateMove(og.pawns[pawn], validMoves[move])){
                Choice choice(og.pawns[pawn], validMoves[move], board->numMoves);
                if (search(failure, choice) != true){
                    cout << "NOT IN FAILURE" << endl;
                    og.pawns[pawn].first += validMoves[move].first;
                    og.pawns[pawn].second += validMoves[move].second;
                    temp.push_back(choice);
                    return choice;
                }
            }
        }
    }
    Choice none;
    return none;
}

void Computer::movePiece(){
    if (!og.canMove(validMoves, board)){
        status->personWin = true;
    }
    Choice fromTo = makeChoice();
    if (fromTo.round != 0){
        std::pair<int, int> current = fromTo.getPosition();
        std::pair<int, int> to = fromTo.getTo();

        board->arr[current.first + to.first][current.second+to.second] = 2;
        board->arr[current.first][current.second] = 0;
        if (current.first + to.first == 2)status->compWin = true;
    }
    
}

bool Computer::validateMove(const std::pair<int, int> &from, const std::pair<int, int> &to){
    bool isValid = false;
    if (board->arr[from.first][from.second] != 2)return isValid;
    std::pair<int, int> newTo(from.first + to.first, from.second + to.second);
    if ((newTo.first <= 2 && newTo.first >= 0) && (newTo.second <= 2 && newTo.second >= 0)){
        if (to.second != 0){
            if (board->arr[newTo.first][newTo.second] == 1)isValid = true;
        }
        else{
            if (board->arr[newTo.first][newTo.second] == 0)isValid = true;
        }
        
    }
    return isValid;
}

int main(){
    Victory winner;
    ChessBoard myBoard;
    Person me(myBoard, winner);
    Computer comp(myBoard, winner);
    string from, to;
    print(myBoard.arr);
    cout << "Enter FROM position (i.e. 0 0): ";
    std::getline(cin, from);
    while (from != ""){
        cout << "\nEnter TO position (i.e. 1 0): ";
        std::getline(cin, to);
        me.movePiece(from, to);
        myBoard.numMoves++;
        comp.movePiece();
        if (winner.youWin() == true){
            string y_n;
            cout << "You won! Continue? (y/n): " << endl;
            std::getline(cin, y_n);
            if (y_n == "y"){
                me.setBoard();
                comp.setBoard();
                winner.reset();
                main();
            }
            return 1;
        }
        else if (winner.computerWins() == true){
            string y_n;
            cout << "Computer Wins, Continue? (y/n): " << endl;
            std::getline(cin, y_n);
            if (y_n == "y"){
                me.setBoard();
                comp.setBoard();
                winner.reset();
                main();
            }
            return 1;
        }
        myBoard.numMoves++;
        print(myBoard.arr);
        cout << "\nEnter FROM position (i.e. 0 0): ";
        std::getline(cin, from);
    }
}

