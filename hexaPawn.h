#ifndef SANDBOX_H
#define SANDBOX_H
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


vector<int> parseString(const string &s){
    vector<int> arr;
    istringstream iss(s);
    string x;
    while (getline(iss, x, ' ')){
        arr.push_back(stoi(x));
    }
    return arr;
}

void print(int arr[3][3]){
    for (unsigned row=0;row<3;row++){
        for (unsigned col=0;col<3;col++){
            cout << arr[row][col] << "   ";
        }
        cout << '\n' << endl;
    }
}


#endif
