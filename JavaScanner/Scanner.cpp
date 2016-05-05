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
    OctalNumber_1,
    OctalNumber_2,
    Hexadecimal_1,
    Hexadecimal_2,
    Hexadecimal_3,
    Hexadecimal_4,
    EscapedChar,
    EndOfChar,
    TermOfChar,
    String,
    EscapStr,
    EndOfStr,
    Separator,
    Separator_Fork,
    Backslash,
    Operator_Div_Equal,
    Single_Line_Comments,
    Multipl_Line_Comments,
    Multipl_Line_Comments_Pre_End,
    ConstValue,
    ConstValue_Int,
    ConstValue_Int_Hex,
    ConstValue_Int_Hex_End,
    ConstValue_Int_End,
    ConstValue_Pow,
    ConstValue_Pow_End,
    ConstValue_Float,
    ConstValue_Float_End,
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
                } else if (isNumber(ch) && ch != '0') {
                    state = ConstValue_Int;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    switch (ch) {
                        case '\'':
                            state = Char;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '\"':
                            state = String;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '{':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '}':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '[':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case ']':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '(':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case ')':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case ',':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '.':
                            state = Separator_Fork;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case ';':
                            state = Separator;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '/':
                            state = Backslash;
                            wordBuffer[pWrodBuffer ++] = ch;
                            break;
                            
                        case '\n':
                            state = Init;
                            setNewLine(linenumber, wordofline);
                            resetBuffer(1);
                            break;
                            
                        case '0':
                            state = ConstValue;
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
                } else if (isNumber(ch, Oct)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = OctalNumber_1;
                } else if (ch == 'u') {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = Hexadecimal_1;
                } else {
                    state = Error;
                }
                break;
            
            case OctalNumber_1:
                if (isNumber(ch, Oct)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = OctalNumber_2;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case OctalNumber_2:
                if (isNumber(ch, Oct)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = EndOfChar;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_1:
                if (isNumber(ch, Hex)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = Hexadecimal_2;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_2:
                if (isNumber(ch, Hex)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = Hexadecimal_3;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_3:
                if (isNumber(ch, Hex)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = Hexadecimal_4;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_4:
                if (isNumber(ch, Hex)) {
                    wordBuffer[pWrodBuffer ++] = ch;
                    state = EndOfChar;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
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
                
            case String:
                if (ch == '\"') {
                    state = EndOfStr;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else if (ch == '\\') {
                    state = EscapStr;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = String;
                    wordBuffer[pWrodBuffer ++] = ch;
                }
                break;
                
            case EscapStr:
                state = String;
                wordBuffer[pWrodBuffer ++] = ch;
                break;
                
            case EndOfStr:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                break;
                
            case Separator:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                wordofline --;
                break;
                
            case Separator_Fork:
                if (isNumber(ch)) {
                    state = ConstValue_Float;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = Separator;
                    buffer.backSpace();
                }
                break;
                
            case Backslash:
                if (ch == '=') {
                    state = Operator_Div_Equal;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else if (ch == '/') {
                    state = Single_Line_Comments;
                } else if (ch == '*') {
                    state = Multipl_Line_Comments;
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline ++;
                }
                break;
                
            case Operator_Div_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                wordofline--;
                break;
                
            case Single_Line_Comments:
                if (ch == '\n') {
                    setNewLine(linenumber, wordofline);
                    state = Init;
                    resetBuffer(1);
                } else {
                    state = Single_Line_Comments;
                }
                break;
                
            case Multipl_Line_Comments:
                if (ch == '*') {
                    state = Multipl_Line_Comments_Pre_End;
                } else if (ch == '\n') {
                    state = Multipl_Line_Comments;
                    setNewLine(linenumber, wordofline);
                } else {
                    state = Multipl_Line_Comments;
                }
                break;
                
            case Multipl_Line_Comments_Pre_End:
                if (ch == '/') {
                    state = Init;
                    resetBuffer(1);
                } else if (ch == '\n') {
                    state = Multipl_Line_Comments;
                    setNewLine(linenumber, wordofline);
                } else {
                    state = Multipl_Line_Comments;
                }
                break;
                
            case ConstValue: // 0
                if (ch == 'x' || ch == 'X') {
                    state = ConstValue_Int_Hex;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = ConstValue_Int;
                    wordBuffer[pWrodBuffer ++] = ch;
                }
                break;
                
            case ConstValue_Int:
                if (ch == 'l' || ch == 'L' || ch == 'f' || ch == 'F') {
                    state = ConstValue_Int_End;
                    buffer.backSpace();
                } else if (isNumber(ch)) {
                    state = ConstValue_Int;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else if (ch == 'e' || ch == 'E') {
                    state = ConstValue_Pow;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else if (ch == '.') {
                    state = ConstValue_Float;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = ConstValue_Int_End;
                    buffer.backSpace();
                }
                break;
                
            case ConstValue_Int_Hex:
                if (isNumber(ch, Hex)) {
                    state = ConstValue_Int_Hex;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = ConstValue_Int_Hex_End;
                    buffer.backSpace();
                }
                break;
               
            case ConstValue_Int_Hex_End:
                if (ch == 'l' || ch == 'L') {
                    state = Init;
                    pushBuffer(ch);
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline --;
                    buffer.getNextChar();
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline --;
                }
                break;
                
            case ConstValue_Int_End:
                if (ch == 'l' || ch == 'L' || ch == 'f' || ch == 'F') {
                    state = Init;
                    wordBuffer[pWrodBuffer ++] = ch;
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline --;
                    buffer.getNextChar();
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline --;
                }
                break;
                
            case ConstValue_Float: // \.\d+
                if (isNumber(ch)) {
                    state = ConstValue_Float;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = ConstValue_Float_End;
                    buffer.backSpace();
                }
                break;
                
            case ConstValue_Float_End:
                if (ch == 'f' || ch == 'F') {
                    state = Init;
                    wordBuffer[pWrodBuffer ++] = ch;
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline --;
                    buffer.getNextChar();
                } else if (ch == 'e' || ch == 'E') {
                    state = ConstValue_Pow;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    wordofline --;
                }
                break;

            case ConstValue_Pow: // e\d
                if (isNumber(ch)) {
                    state = ConstValue_Pow;
                    wordBuffer[pWrodBuffer ++] = ch;
                } else {
                    state = ConstValue_Pow_End;
                    buffer.backSpace();
                }
                break;
                
            case ConstValue_Pow_End:
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

bool Scanner::isNumber(char ch, NumType type) {
    switch (type) {
        case Oct:
            return (ch <= '7' && ch >= '0');
            break;
        
        case Hex:
            return (ch <= '9' && ch >= '0') || (ch <= 'f' && ch >= 'a') || (ch <= 'F' && ch >= 'A');
            break;
            
        default:
            return ch <= '9' && ch >= '0';
            break;
    }
}

void Scanner::setNewLine(int& linenumber, int& wordofline) {
    linenumber ++;
    wordofline = 1;
}

void Scanner::pushBuffer(char ch) {
    wordBuffer[pWrodBuffer ++]  = ch;
}