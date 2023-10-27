//  Created by Kai N. Alcayde on 7/12/21.
//
#include "OnlineDating.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
int main() {


    OnlineDating first;
    OnlineDating second;
    second.makeMatch("One", "Person", 1);
    OnlineDating third;
    first.makeMatch("Anthony", "Davis", 39);
    first.noMatches();
    first.howManyMatches();
    first.makeMatch("Kai", "Alcayde", 12);
    first.transformMatch("Kai", "Alcayde", 41);
    first.makeOrTransform("Anthony", "Cor", 1);
    first.blockPreviousMatch("Anthony","Cor");
    first.someoneAmongMatches("Kai", "Alcayde");
    int i = 1;
    first.lookAtMatches("Kai", "Alcayde", i);
    string f;
    string l;
    first.confirmMatch(1, f, l, i);
    first.tradeMatches(second);
    
    mergeMatches(first, second, third);
    authenticateMatches("One", "Person", first, third);

//            first.makeMatch("Lebron", "James", 23);
//            first.makeMatch("Kyle", "Kuzma", 7);

    first.lookAtMatches("Anthony", "Davis", i);
    cout << first.howManyMatches();
//
//
//    for (int n = 0; n < first.howManyMatches(); n++)
//     {
//     string prim;
//     string last;
//     int val;
//     first.confirmMatch (n, prim, last, val);
//     cout << prim << " " << last << " " << val << endl;
//     }
//
    cout <<i ;




    return 0;
}
