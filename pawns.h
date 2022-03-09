#ifndef PAWNS_H
#define PAWNS_H
#include <map>
#include <utility>
#include <vector>
#include <array>

using std::pair;
using std::array;

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
            if (board->arr[pawns[pawn].first][pawns[pawn].second] == 2){
                if ((newTo.first <= 2 && newTo.first >= 0) && (newTo.second <= 2 && newTo.second >= 0)){
                    if (arr[move].second != 0){
                        if (board->arr[newTo.first][newTo.second] == 1)return true;
                    }
                    else{
                        if (board->arr[newTo.first][newTo.second] == 0)return true;
                    }
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
        vector<vector<int> > pawns;
    void reset(){
        pawns.clear();
        for (int p=0;p<3;p++){
            vector<int> temp;
            temp.push_back(2);
            temp.push_back(p);
            pawns.push_back(temp);
        }
    }

    void changePawn(const vector<int> &from, const vector<int> &to){
        for (int pawn=0;pawn<3;pawn++){
            if (pawns[pawn][0] == from[0] && pawns[pawn][1] == from[1]){
                cout << "CHANGING!" << endl;
                pawns[pawn][0] = to[0];
                pawns[pawn][1] = to[1];
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
            std::pair<int, int> newTo(pawns[pawn][0] + arr[move].first, pawns[pawn][1] + arr[move].second);
            if (board->arr[pawns[pawn][0]][pawns[pawn][1]] == 1){
                if ((newTo.first <= 2 && newTo.first >= 0) && (newTo.second <= 2 && newTo.second >= 0)){
                    cout << newTo.first << newTo.second << endl;;
                    if (arr[move].second != 0){
                        cout << "here? " << endl;
                        if (board->arr[newTo.first][newTo.second] == 2)return true;
                    }
                    else{
                        cout << arr[move].first << " " << arr[move].second << endl;
                        cout << "or here?" << endl;
                        if (board->arr[newTo.first][newTo.second] == 0)return true;
                    }
                }
            }
        }   
    }
    return false;
}

#endif