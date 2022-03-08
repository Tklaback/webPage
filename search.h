#ifndef SEARCH_H
#define SEARCH_H

#include "pawns.h"

bool search(std::vector<Choice>& vec, Choice &target){
    for (int idx=0;idx<vec.size();idx++){
        if (vec[idx].getTo() == target.getTo() && vec[idx].getPosition() == target.getPosition() && vec[idx].round == target.round){
            cout << target.getPosition().first << " HAS BEEN FOUND!" << endl;
            return true;
        }
    }
    return false;
}

#endif