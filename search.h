#ifndef SEARCH_H
#define SEARCH_H

#include "pawns.h"

bool search(std::vector<Choice>& vec, Choice &target){
    for (int idx=0;idx<vec.size();idx++){
        if (vec[idx] == target){
            cout << target.getPosition().first << " HAS BEEN FOUND!" << endl;
            return true;
        }
    }
    return false;
}

#endif