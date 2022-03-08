#ifndef SEARCH_H
#define SEARCH_H

#include "pawns.h"

int find(std::vector<Choice>& vec, Choice &target){
    for (int idx=0;idx<vec.size();idx++){
        if (vec[idx] == target){
            return idx;
        }
    }
    return -1;
}

#endif