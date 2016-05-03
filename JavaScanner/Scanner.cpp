//
//  Scanner.cpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/5/2.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#include "Scanner.hpp"

enum STATE {
    Init,
    Keywords,
    Char,
    EscapedChar,
    EndOfChar,
    TermOfChar,
    Error
};

Scanner::Scanner(string filePath): buffer(filePath) {
    resetBuffer(1);
}

int Scanner::scan() {
    char ch = '\0';
    STATE state = Init;
    int linenumber = 1;
    int wordofline = 1;
    
    while ((ch = buffer.getNextChar()) != -1) {
        switch (state) {
            case Init:
                if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || ch == '$' || ch == '_') {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = Keywords;
                } else {
                    switch (ch) {
                        case '\'':
                            state = Char;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                    }
                }
                break;
                
            case Keywords: // keywords & terminal
                if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || ch == '$' || ch == '_' || (ch <= '9' && ch >= '0')) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = Keywords;
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                }
                break;
            
            case Char: // char
                if (ch == '\\') { // escaped character
                    state = EscapedChar;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = EndOfChar;
                    wordBuffer[pWrodBuffer ++] = ch;
                }
                break;
                
            case EscapedChar:
                if (ch == '\'' || ch == '\\' || ch == 'r' || ch == 'n' || ch == 'f' || ch == 't' || ch == 'b') {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = EndOfChar;
                } else {
                    state = Error;
                }
                break;
                
            case EndOfChar:
                if (ch == '\'') {
                    state = TermOfChar;
                    wordBuffer[pWrodBuffer ++ ] = ch;
                } else {
                    state = Error;
                }
                break;
                
            case TermOfChar:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                break;
                
            case Error:
                state = Init;
                buffer.backSpace();
                cout<<linenumber<<" " <<wordofline<<" " <<"error"<<endl;
                exit(1);
                break;
        }
    }
    
    return -1;
}

void Scanner::resetBuffer(int control) {
    if (control == 0) {
        memset(wordBuffer, 0, MAX_WORD_LEN * sizeof(char));
    }
    else if (control == 1) {
        memset(wordBuffer, 0, MAX_WORD_LEN * sizeof(char));
        pWrodBuffer = 0;
    }
}

void Scanner::addToken(int& linenumber, int& wordofline, char* wordBuffer) {
    buffer.backSpace();
    wordBuffer[pWrodBuffer] = '\0';
    Token keyword(linenumber, wordofline++, wordBuffer);
    tokens.push_back(keyword);
    resetBuffer(1);
}