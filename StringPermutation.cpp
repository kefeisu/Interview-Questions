//
//  StringPermuatition.c
//  
//
//  Created by KeFei on 2017-05-27.
//
//

#include <string>
#include <iostream>

using namespace std;

/* Question:
 * Given a string, print out all persumations of it
 */

void swap(string &s, int i, int j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void printPermutations(int i, string s) {
    if ( i == s.length() - 1) { cout << s << endl; return; }
     for (int j = i; j < s.length(); ++j) {
         swap(s,i,j);
         printPermutations(i+1, s);
         swap(s,i,j);
    }
}

int main(void){
    string s;
    cout << "Please enter a String: ";
    cin >> s;
    cout << "Printing all permutations:" << endl;
    printPermutations(0,s);
}



