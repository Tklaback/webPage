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
        std::pair<int, int> validCMoves[3] = {std::make_pair<int,int>(1,-1), 
        std::make_pair<int,int>(1,0), std::make_pair<int,int>(1,1)};
        std::pair<int, int> validPMoves[3] = {std::make_pair<int,int>(-1,-1), 
        std::make_pair<int,int>(-1,0), std::make_pair<int,int>(-1,1)};
        // virtual void movePiece(const string &from, const string &to)=0;
    public:
        Player(): players(3){}
};

class Person: public Player{
    Victory *status;
    Pawns *og;
    PersonPawns *ogPawns;
    public:
        void setBoard(){
            for (unsigned col=0;col< 3;col++){
                board->arr[2][col] = 1;
            }
        }
        Person(ChessBoard &obj, Victory &status, Pawns &og, PersonPawns &ogPawns){
            this->og = &og;
            this->ogPawns = &ogPawns;
            this->status = &status;
            board = &obj;
            setBoard();
        }
        bool validateMove(const vector<int> &from, const vector<int> &to);
        void movePiece(const string &from, const string &to);
};

void Person::movePiece(const string &from, const string &to){
    vector<int> fromNums = parseString(from);
    vector<int> toNums = parseString(to);
    if (validateMove(fromNums, toNums)){
        ogPawns->changePawn(fromNums, toNums);
        board->arr[toNums[0]][toNums[1]] = board->arr[fromNums[0]][fromNums[1]];
        board->arr[fromNums[0]][fromNums[1]] = 0;
        if (toNums[0] == 0){
            status->personWin = true;
        }
    }
    if (!og->canMove(validCMoves, board)){
        status->personWin = true;
        return;
    }
}

bool Person::validateMove(const vector<int> &from, const vector<int> &to){
    bool isValid = false;
    if (board->arr[from[0]][from[1]] != 1)return isValid;
    int first, second;
    for (unsigned move=0;move<3;move++){
        first = validPMoves[move].first;
        second = validPMoves[move].second;
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
    Victory *status;
    Pawns *og;
    PersonPawns *ogPawns;
    std::vector<Choice> temp;
    public:
        void setBoard(){
            og->reset();
            for (unsigned col=0;col< 3;col++){
                board->arr[0][col] = 2;
            }
        }
        Computer(ChessBoard &obj, Victory &status, Pawns &og, PersonPawns &ogPawns){
            this->og = &og;
            this->ogPawns = &ogPawns;
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
    for (int pawn=0;pawn<og->pawns.size();pawn++){
        for (int move=0;move<3;move++){ //size of validMoves
            if (validateMove(og->pawns[pawn], validCMoves[move])){
                Choice choice(og->pawns[pawn], validCMoves[move], board->numMoves);
                if (search(failure, choice) != true){
                    og->pawns[pawn].first += validCMoves[move].first;
                    og->pawns[pawn].second += validCMoves[move].second;
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
    Choice fromTo = makeChoice();
    if (fromTo.round != 0){
        std::pair<int, int> current = fromTo.getPosition();
        std::pair<int, int> to = fromTo.getTo();

        board->arr[current.first + to.first][current.second+to.second] = 2;
        board->arr[current.first][current.second] = 0;
        if (current.first + to.first == 2)status->compWin = true;
    }
    if (!(ogPawns->canMove(validPMoves, board))){
        status->compWin = true;
        return;
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
    Pawns og;
    PersonPawns ogPawns;
    Person me(myBoard, winner, og, ogPawns);
    Computer comp(myBoard, winner, og, ogPawns);
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
        myBoard.numMoves++;
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
        print(myBoard.arr);
        cout << "\nEnter FROM position (i.e. 0 0): ";
        std::getline(cin, from);
    }
}

