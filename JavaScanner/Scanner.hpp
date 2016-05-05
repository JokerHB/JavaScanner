//
//  Scanner.hpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/5/2.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include <stdio.h>
#include <vector>
#include <string>

#include "SpecialBuffer.hpp"
#include "Token.hpp"
#include "PublicDefine.h"

enum NumType {
    Dec,
    Hex,
    Oct
};

class Scanner {
public:
    Scanner(string filePath);
    
//  MARK: -begin scanning, return the error word id, if all right return -1
    int scan();
    
//  MARK: -get the detail error by error word id
    string getError(int wordID);
    
//  MARK: -write all tokens into the file
    int write(string filePath);
    
//  MARK: -all tokens
    vector<Token> tokens;
    
private:
//  MARK: -reset the buffer
    void resetBuffer(int control);
    
//  MARK: -specila buffer
    SpecailBuffer buffer;
    
//  MARK: -judge the number
    bool isNumber(char ch, NumType type = Dec);
    
//  MARK: -add new token
    void addToken(int& linenumber, int& wordofline, char* wordBuffer);

//  MARK: -new line, reset the line num and word of the line
    void setNewLine(int& linenumber, int& wordofline);
    
//  MARK: -push a char into the wordBuffer;
    void pushBuffer(char ch);
    
//  MARK: -word waitting for recognize
    char wordBuffer[MAX_WORD_LEN];
    
//  MARK: -pointer of the current word buffer
    int pWrodBuffer;
};

#endif /* Scanner_hpp */
