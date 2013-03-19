//
//  main.cpp
//  myGrep
//
//  Created by Виталий Давыдов on 17.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <iostream>
#include <vector>

#define STRI string::iterator

using namespace std;

class IWAnaliser {
    string stringToAnalise;
    string pattern;
    vector<string> strings;
public:
    IWAnaliser() {
        stringToAnalise = "jsnewfds";
        pattern = "abc";
    }
    
    IWAnaliser(char *str, char *usersPattern) {
        string s(str);
        string s1(usersPattern);
        
        stringToAnalise = s;
        pattern = s1;
    }
    
    bool findPatternInStrings() {
        
    }
};

int main(int argc, const char * argv[])
{
    IWAnaliser a;
    a.findPatternInStrings();
    
    return 0;
}

