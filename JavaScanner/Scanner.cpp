//
//  Scanner.cpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/5/2.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#include "Scanner.hpp"

Scanner::Scanner(string filePath): buffer(filePath) {
    resetBuffer(1);
}

int Scanner::scan() {
    char ch = '\0';
    STATE state = Init;
    int linenumber = 1;
    int wordofline = 1;
    
    while ((ch = buffer.getNextChar()) != -1 && ch != '\0') {
        switch (state) {
            case Init:
                if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || ch == '$' || ch == '_') {
                    pushBuffer(ch);
                    state = Keywords;
                } else if (isNumber(ch) && ch != '0') {
                    state = ConstValue_Int;
                    pushBuffer(ch);
                } else {
                    switch (ch) {
                        case '\'':
                            state = Char;
                            pushBuffer(ch);
                            break;
                            
                        case '\"':
                            state = String;
                            pushBuffer(ch);
                            break;
                            
                        case '{':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case '}':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case '[':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case ']':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case '(':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case ')':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case ',':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case '.':
                            state = Separator_Fork;
                            pushBuffer(ch);
                            break;
                            
                        case ';':
                            state = Separator;
                            pushBuffer(ch);
                            break;
                            
                        case '/':
                            state = Backslash;
                            pushBuffer(ch);
                            break;
                            
                        case '\n':
                            state = Init;
                            setNewLine(linenumber, wordofline);
                            resetBuffer(1);
                            break;
                            
                        case '0':
                            state = ConstValue;
                            pushBuffer(ch);
                            break;
                            
                        case '+':
                            state = Operator_Plus;
                            pushBuffer(ch);
                            break;
                        
                        case '-':
                            state = Operator_Minus;
                            pushBuffer(ch);
                            break;
                            
                        case '*':
                            state = Operator_Multiply;
                            pushBuffer(ch);
                            break;
                            
                        case '%':
                            state = Operator_Mod;
                            pushBuffer(ch);
                            break;
                            
                        case '=':
                            state = Operator_Eauql;
                            pushBuffer(ch);
                            break;
                            
                        case '~':
                            state = Operator_Not;
                            pushBuffer(ch);
                            break;
                            
                        case '>':
                            state = Operator_Large;
                            pushBuffer(ch);
                            break;
                            
                        case '<':
                            state = Operator_Small;
                            pushBuffer(ch);
                            break;
                            
                        case '&':
                            state = Operator_And;
                            pushBuffer(ch);
                            break;
                            
                        case '|':
                            state = Operator_Or;
                            pushBuffer(ch);
                            break;
                            
                        case '^':
                            state = Operator_Xor;
                            pushBuffer(ch);
                            break;
                            
                        case '!':
                            state = Operator_Exclamation;
                            pushBuffer(ch);
                            break;
                            
                        case '?':
                            state = Operator_Ques;
                            pushBuffer(ch);
                            break;
                            
                        case '@':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        case ':':
                            state = Operator_Ques_End;
                            pushBuffer(ch);
                            break;
                            
                        case ' ':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        case '\b':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        case '\f':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        case '\r':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        case '\t':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        case '#':
                            state = Init;
                            resetBuffer(1);
                            break;
                            
                        default:
                            state = Error;
                            break;
                    }
                }
                break;
                
            case Keywords: // keywords & terminal
                if ((ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a') || ch == '$' || ch == '_' || (ch <= '9' && ch >= '0')) {
                    pushBuffer(ch);
                    state = Keywords;
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                }
                break;
            
            case Char: // char
                if (ch == '\\') { // escaped character
                    state = EscapedChar;
                    pushBuffer(ch);
                } else {
                    state = EndOfChar;
                    pushBuffer(ch);
                }
                break;
                
            case EscapedChar:
                if (ch == '\'' || ch == '\\' || ch == 'r' || ch == 'n' || ch == 'f' || ch == 't' || ch == 'b') {
                    pushBuffer(ch);
                    state = EndOfChar;
                } else if (isNumber(ch, Oct)) {
                    pushBuffer(ch);
                    state = OctalNumber_1;
                } else if (ch == 'u') {
                    pushBuffer(ch);
                    state = Hexadecimal_1;
                } else {
                    state = Error;
                }
                break;
            
            case OctalNumber_1:
                if (isNumber(ch, Oct)) {
                    pushBuffer(ch);
                    state = OctalNumber_2;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case OctalNumber_2:
                if (isNumber(ch, Oct)) {
                    pushBuffer(ch);
                    state = EndOfChar;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_1:
                if (isNumber(ch, Hex)) {
                    pushBuffer(ch);
                    state = Hexadecimal_2;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_2:
                if (isNumber(ch, Hex)) {
                    pushBuffer(ch);
                    state = Hexadecimal_3;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_3:
                if (isNumber(ch, Hex)) {
                    pushBuffer(ch);
                    state = Hexadecimal_4;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case Hexadecimal_4:
                if (isNumber(ch, Hex)) {
                    pushBuffer(ch);
                    state = EndOfChar;
                } else {
                    buffer.backSpace();
                    state = EndOfChar;
                }
                break;
                
            case EndOfChar:
                if (ch == '\'') {
                    state = TermOfChar;
                    wordBuffer[pWordBuffer ++ ] = ch;
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
                    pushBuffer(ch);
                } else if (ch == '\\') {
                    state = EscapStr;
                    pushBuffer(ch);
                } else {
                    state = String;
                    pushBuffer(ch);
                }
                break;
                
            case EscapStr:
                state = String;
                pushBuffer(ch);
                break;
                
            case EndOfStr:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                break;
                
            case Separator:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Separator_Fork:
                if (isNumber(ch)) {
                    state = ConstValue_Float;
                    pushBuffer(ch);
                } else {
                    state = Separator;
                    buffer.backSpace();
                }
                break;
                
            case Backslash:
                if (ch == '=') {
                    state = Operator_Div_Equal;
                    pushBuffer(ch);
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
                //wordofline-- -reg;
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
                    pushBuffer(ch);
                } else if(isNumber(ch)) {
                    state = ConstValue_Int;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                }
                break;
                
            case ConstValue_Int:
                if (ch == 'l' || ch == 'L' || ch == 'f' || ch == 'F') {
                    state = ConstValue_Int_End;
                    buffer.backSpace();
                } else if (isNumber(ch)) {
                    state = ConstValue_Int;
                    pushBuffer(ch);
                } else if (ch == 'e' || ch == 'E') {
                    state = ConstValue_Pow;
                    pushBuffer(ch);
                } else if (ch == '.') {
                    state = ConstValue_Float;
                    pushBuffer(ch);
                } else {
                    state = ConstValue_Int_End;
                    buffer.backSpace();
                }
                break;
                
            case ConstValue_Int_Hex:
                if (isNumber(ch, Hex)) {
                    state = ConstValue_Int_Hex;
                    pushBuffer(ch);
                } else {
                    state = ConstValue_Int_Hex_End;
                    buffer.backSpace();
                }
                break;
               
            case ConstValue_Int_Hex_End:
                if (ch == 'l' || ch == 'L') {
                    state = Init;
                    pushBuffer(ch);
                    addToken(linenumber, wordofline, wordBuffer, 0x107);
                    //wordofline -- -reg;
                    buffer.getNextChar();
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer, 0x107);
                    //wordofline -- -reg;
                }
                break;
                
            case ConstValue_Int_End:
                if (ch == 'l' || ch == 'L' || ch == 'f' || ch == 'F') {
                    state = Init;
                    pushBuffer(ch);
                    int type = 0;
                    if (ch == 'l' || ch == 'L') {
                        type = 0x107;
                    } else {
                        type = 0x108;
                    }
                    addToken(linenumber, wordofline, wordBuffer, type);
                    //wordofline -- -reg;
                    buffer.getNextChar();
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer, 0x107);
                    //wordofline -- -reg;
                }
                break;
                
            case ConstValue_Float: // \.\d+
                if (isNumber(ch)) {
                    state = ConstValue_Float;
                    pushBuffer(ch);
                } else {
                    state = ConstValue_Float_End;
                    buffer.backSpace();
                }
                break;
                
            case ConstValue_Float_End:
                if (ch == 'f' || ch == 'F') {
                    state = Init;
                    pushBuffer(ch);
                    addToken(linenumber, wordofline, wordBuffer, 0x108);
                    //wordofline -- -reg;
                    buffer.getNextChar();
                } else if (ch == 'e' || ch == 'E') {
                    state = ConstValue_Pow;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer, 0x108);
                    //wordofline -- -reg;
                }
                break;

            case ConstValue_Pow: // e\d
                if (isNumber(ch)) {
                    state = ConstValue_Pow;
                    pushBuffer(ch);
                } else {
                    state = ConstValue_Pow_End;
                    buffer.backSpace();
                }
                break;
                
            case ConstValue_Pow_End: {
                char _ch = wordBuffer[pWordBuffer - 1];
                
                if (isNumber(_ch)) {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer, 0x108);
                } else {
                    state = Error;
                }
                
                break;
            }
                
            case Operator_Plus:
                if (ch == '+') {
                    state = Operator_Plus_Plus;
                    pushBuffer(ch);
                } else if (ch == '=') {
                    state = Operator_Plus_Equal;
                    pushBuffer(ch);
                } else {
                    state = Operator_Plus_Judge;
                    buffer.backSpace();
                }
                break;
                
            case Operator_Plus_Plus:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Plus_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Plus_Judge:
                buffer.backSpace();
                buffer.backSpace();
                buffer.backSpace();
                ch = buffer.getNextChar();
                resetBuffer(1);
                if(!isNumber(ch)) {  // plus
                    Token keyword(linenumber, wordofline++, "+");
                    tokens.push_back(keyword);
                    //wordofline -- -reg;
                } else { // positive
                    pushBuffer('+');
                }
                ch = buffer.getNextChar();
                state = Init;
                break;
                
            case Operator_Minus:
                if (ch == '-') {
                    state = Operator_Minus_Minus;
                    pushBuffer(ch);
                } else if (ch == '=') {
                    state = Operator_Minus_Equal;
                    pushBuffer(ch);
                } else {
                    state = Operator_Minus_Judge;
                    buffer.backSpace();
                }
                break;
                
            case Operator_Minus_Minus:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Minus_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                break;
                
            case Operator_Minus_Judge:
                buffer.backSpace();
                buffer.backSpace();
                buffer.backSpace();
                ch = buffer.getNextChar();
                resetBuffer(1);
                if(!isNumber(ch)) {  // minux
                    Token keyword(linenumber, wordofline++, "-");
                    tokens.push_back(keyword);
                    //wordofline -- -reg;
                } else { // ngitive
                    pushBuffer('-');
                }
                ch = buffer.getNextChar();
                state = Init;
                break;
                
            case Operator_Multiply:
                if (ch == '=') {
                    state = Operator_Multiply_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Multiply_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline-- -reg;
                break;
                
            case Operator_Mod:
                if (ch == '=') {
                    state = Operator_Mod_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Mod_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Eauql:
                if (ch == '=') {
                    state = Operator_Eauql_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Eauql_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Not:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_And:
                if (ch == '&') {
                    state = Operator_And_And;
                    pushBuffer(ch);
                } else if (ch == '=') {
                    state = Operator_And_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_And_And:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_And_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Xor:
                if (ch == '=') {
                    state = Operator_Xor_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Xor_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Or:
                if (ch == '|') {
                    state = Operator_Or_Or;
                    pushBuffer(ch);
                } else if (ch == '=') {
                    state = Operator_Or_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Or_Or:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Or_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Large:
                if (ch == '=') {
                    state = Operator_Large_Equal;
                    pushBuffer(ch);
                } else if (ch == '>') {
                    state = Operator_Large_Large;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Large_Large:
                if (ch == '=') { // >>=
                    state = Operator_Large_Equal;
                    pushBuffer(ch);
                } else if (ch == '>') { // >>>
                    state = Operator_Large_Large_Large;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Large_Large_Large:
                if (ch == '=') { // >>>=
                    state = Operator_Large_Equal;
                    pushBuffer(ch);
                } else { // >>>
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Large_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Small:
                if (ch == '=') {
                    state = Operator_Small_Equal;
                    pushBuffer(ch);
                } else if (ch == '<') {
                    state = Operator_Small_Small;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Small_Small:
                if (ch == '=') { // <<=
                    state = Operator_Small_Equal;
                    pushBuffer(ch);
                } else if (ch == '<') { // <<<
                    state = Operator_Small_Small_Small;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Small_Small_Small:
                if (ch == '=') { // <<<=
                    state = Operator_Small_Equal;
                    pushBuffer(ch);
                } else { // <<<
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Small_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Exclamation:
                if (ch == '=') {
                    state = Operator_Exclamation_Equal;
                    pushBuffer(ch);
                } else {
                    state = Init;
                    addToken(linenumber, wordofline, wordBuffer);
                    //wordofline -- -reg;
                }
                break;
                
            case Operator_Exclamation_Equal:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Ques:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Operator_Ques_End:
                state = Init;
                addToken(linenumber, wordofline, wordBuffer);
                //wordofline -- -reg;
                break;
                
            case Error:
                state = Init;
                buffer.backSpace();
                wordBuffer[pWordBuffer] = '\0';
                cout<<"-error: line_"<<linenumber<<" no_" <<wordofline<<" "<<wordBuffer<<endl;
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
        pWordBuffer = 0;
    }
}

void Scanner::addToken(int& linenumber, int& wordofline, char* wordBuffer, int type) {
    buffer.backSpace();
    wordBuffer[pWordBuffer] = '\0';
    Token keyword(linenumber, wordofline++, wordBuffer, type);
    tokens.push_back(keyword);
    resetBuffer(1);
    sumOfword ++;
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
    wordBuffer[pWordBuffer ++] = ch;
}

int Scanner::write(string filePath) {
    
    
    return 0;
}