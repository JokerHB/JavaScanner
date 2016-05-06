//
//  Token.hpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <cstring>

#include "PublicDefine.h"

using namespace std;

class Token {
public:
    //  MARK: -line number
    int linenum;
    
//  MARK: -the number of the word in line
    int no;
    
//  MARK: -type of word
    int type;
    
//  MARK: -attribute
    char attribute[MAX_WORD_LEN];
    
//  MARK: -init the word
    Token(int _linenum, int _no, char* _attribute, int _type = 0);
    
//  MARK: -check the word
    int typeCheck();
    
//  AMRK: -to string for output
    string toString();
    
private:
//  MARK: -judge the number
    bool isNumber(char ch, NumType type = Dec);
};

#endif /* Token_hpp */
