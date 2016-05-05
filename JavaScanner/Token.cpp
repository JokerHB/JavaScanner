//
//  Token.cpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#include "Token.hpp"

Token::Token(int _linenum, int _no, char* _attribute) {
    linenum = _linenum;
    no = _no;
    
    strcpy(attribute, _attribute);
    
    type = typeCheck();
}

int Token::typeCheck() {
    if ((strcmp("true", attribute) == 0) || (strcmp("false", attribute) == 0)) {
        return 0x105;
    }
    
    if (attribute[0] == '\'') {
        return 0x106;
    }
    
    if (attribute[0] == '\"') {
        return 0x109;
    }
    
    if ((strcmp(attribute, "{") == 0) || (strcmp(attribute, "}")) == 0) {
        return 0x121;
    }
    
    if ((strcmp(attribute, "(") == 0) || (strcmp(attribute, ")")) == 0) {
        return 0x11d;
    }
    
    if ((strcmp(attribute, "[") == 0) || (strcmp(attribute, "]")) == 0) {
        return 0x11d;
    }
    
    if ((strcmp(attribute, ".") == 0)) {
        return 0x11d;
    }
    
    if ((strcmp(attribute, ",") == 0)) {
        return 0x120;
    }
    
    if ((strcmp(attribute, ";") == 0)) {
        return 0x122;
    }
    
    for (int i = 0;i < 50;i ++) {
        if (strcmp(KEYWORDS[i], attribute) == 0) {
            return 0x103;
        }
    }
    
    return 0x104;
}

string Token::toString() {
    char buffer[2 * MAX_WORD_LEN];
    char* typeGBK;
    
    switch (type) {
        case 0x103:
            typeGBK = "关键字";
            break;
        case 0x104:
            typeGBK = "标识符";
            break;
        case 0x105:
            typeGBK = "布尔型";
            break;
        case 0x106:
            typeGBK = "字符型";
            break;
        case 0x109:
            typeGBK = "字符串型";
            break;
        case 0x11d:
            typeGBK = "界限符";
            break;
        case 0x120:
            typeGBK = "界限符";
            break;
        case 0x121:
            typeGBK = "界限符";
            break;
        case 0x122:
            typeGBK = "界限符";
            break;
        case 0x101:
            typeGBK = "错误的单词";
            break;
        default:
            typeGBK = "NULL";
            break;
    }
    
    sprintf(buffer, "[%d,%d] %0x <%s> %s\n", linenum, no, type, typeGBK, attribute);
    
    return string(buffer);
}