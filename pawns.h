#ifndef PAWNS_H
#define PAWNS_H
#include <map>
#include <utility>
#include <vector>

using std::pair;

class Pawns{
   public: 
    std::vector<std::pair<int, int> > pawns;
    Pawns() {
        pawns.push_back(std::pair<int, int>(0,0));
        pawns.push_back(std::pair<int, int>(0,1));
        pawns.push_back(std::pair<int, int>(0,2));
    }
};

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

#endif