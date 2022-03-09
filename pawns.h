#ifndef PAWNS_H
#define PAWNS_H
#include <map>
#include <utility>
#include <vector>

using std::pair;

class ChessBoard{
    public:
        int numMoves = 1;
        int arr[3][3] = {0,0,0,0,0,0,0,0,0};
        
        
};

class Pawns{
   public: 
    std::vector<std::pair<int, int> > pawns;
    void reset(){
        pawns.clear();
        pawns.push_back(std::pair<int, int>(0,0));
        pawns.push_back(std::pair<int, int>(0,1));
        pawns.push_back(std::pair<int, int>(0,2));
    }
    Pawns() {
        reset();
    }
    bool canMove(std::pair<int, int> arr[3], ChessBoard *board);
};
bool Pawns::canMove(std::pair<int, int> arr[3], ChessBoard *board){
    for (int pawn=0;pawn<3;pawn++){
        for (int move=0;move<3;move++){
            std::pair<int, int> newTo(pawns[pawn].first + arr[move].first, pawns[pawn].second + arr[move].second);
            if ((newTo.first <= 2 && newTo.first >= 0) && (newTo.second <= 2 && newTo.second >= 0)){
                // cout << newTo.first << " " << newTo.second << endl;
                if (arr[move].second != 0){
                    if (board->arr[newTo.first][newTo.second] == 1)return true;
                }
                else{
                    if (board->arr[newTo.first][newTo.second] == 0)return true;
                }
            }
        }   
    }
    return false;
    
}

class Choice{
    pair<int, int> chosenPosition;
    pair<int, int> whereTo;
    public:
        int round;
        Choice() : round(0){}
        Choice(pair<int, int> choice, pair<int, int> where, int num) : 
        chosenPosition(choice), whereTo(where), round(num){}
        pair<int, int> getPosition(){return chosenPosition;}
        pair<int, int> getTo(){return whereTo;}
        bool operator==(const Choice& other){
            if (chosenPosition == other.chosenPosition && whereTo == other.whereTo && round == other.round){
                return true;
            }
            return false;
        }
};

class PersonPawns{
   public: 
    std::vector<std::pair<int, int> > pawns;
    void reset(){
        pawns.clear();
        pawns.push_back(std::pair<int, int>(2,0));
        pawns.push_back(std::pair<int, int>(2,1));
        pawns.push_back(std::pair<int, int>(2,2));
    }
    void changePawn(const vector<int> &from, const vector<int> &to){
        for (int pawn=0;pawn<3;pawn++){
            std::pair<int, int> testPair = pawns[pawn];
            if (testPair.first == from[0] && testPair.second == from[1]){
                pawns[pawn].first = to[0];
                pawns[pawn].second = to[1];
            }
        }
    }
    PersonPawns() {
        reset();
    }
    bool canMove(std::pair<int, int> arr[3], ChessBoard *board);
};
bool PersonPawns::canMove(std::pair<int, int> arr[3], ChessBoard *board){
    for (int pawn=0;pawn<3;pawn++){
        for (int move=0;move<3;move++){
            std::pair<int, int> newTo(pawns[pawn].first + arr[move].first, pawns[pawn].second + arr[move].second);
            cout << newTo.first << " " << newTo.second << endl;
            if ((newTo.first <= 2 && newTo.first >= 0) && (newTo.second <= 2 && newTo.second >= 0)){
                if (arr[move].second != 0){
                    if (board->arr[newTo.first][newTo.second] == 2)return true;
                }
                else{
                    if (board->arr[newTo.first][newTo.second] == 0)return true;
                }
            }
        }   
    }
    return false;
    
}

#endif