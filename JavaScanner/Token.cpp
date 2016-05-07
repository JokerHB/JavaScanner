//
//  Token.cpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#include "Token.hpp"

Token::Token(int _linenum, int _no, char* _attribute, int _type) {
    linenum = _linenum;
    no = _no;
    
    strcpy(attribute, _attribute);
    
    if (_type == 0) {
        type = typeCheck();
    } else {
        type = _type;
    }
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
    
    if (strcmp(attribute, ":") == 0 || strcmp(attribute, "?") == 0) {
        return 0x111;
    }
    
    if (strcmp(attribute, "||") == 0) {
        return 0x112;
    }
    
    if (strcmp(attribute, "&&") == 0) {
        return 0x113;
    }

    if (strcmp(attribute, "|") == 0) {
        return 0x114;
    }
    
    if (strcmp(attribute, "^") == 0) {
        return 0x115;
    }
    
    if (strcmp(attribute, "&") == 0) {
        return 0x116;
    }
    
    if (strcmp(attribute, "==") == 0 || strcmp(attribute, "!=") == 0) {
        return 0x117;
    }
    
    if (strcmp(attribute, ">") == 0 || strcmp(attribute, "<") == 0 || strcmp(attribute, "<=") == 0 || strcmp(attribute, ">=") == 0) {
        return 0x118;
    }
    
    if (strcmp(attribute, ">>>") == 0 || strcmp(attribute, "<<") == 0 || strcmp(attribute, ">>") == 0) {
        return 0x119;
    }
    
    if (strcmp(attribute, "+") == 0 || strcmp(attribute, "-") == 0) {
        return 0x11a;
    }
    
    if (strcmp(attribute, "%") == 0 || strcmp(attribute, "*") == 0 || strcmp(attribute, "/") == 0) {
        return 0x11b;
    }
    
    if (strcmp(attribute, "++") == 0 || strcmp(attribute, "--") == 0 || strcmp(attribute, "+") == 0 || strcmp(attribute, "+") == 0 || strcmp(attribute, "-") == 0 || strcmp(attribute, "!") == 0 || strcmp(attribute, "~") == 0) {
        return 0x11c;
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
        case 0x107:
            typeGBK = "整型";
            break;
        case 0x108:
            typeGBK = "浮点型";
            break;
        case 0x109:
            typeGBK = "字符串型";
            break;
        case 0x110:
            typeGBK = "运算赋值";
            break;
        case 0x111:
            typeGBK = "条件运算符";
            break;
        case 0x112:
            typeGBK = "逻辑或运算符";
            break;
        case 0x113:
            typeGBK = "逻辑与运算符";
            break;
        case 0x114:
            typeGBK = "算术或运算符";
            break;
        case 0x115:
            typeGBK = "算术异或运算符";
            break;
        case 0x116:
            typeGBK = "算术与运算符";
            break;
        case 0x117:
            typeGBK = "等于/不等于运算符";
            break;
        case 0x118:
            typeGBK = "比较运算符";
            break;
        case 0x119:
            typeGBK = "移位运算符";
            break;
        case 0x11a:
            typeGBK = "加/减运算符";
            break;
        case 0x11b:
            typeGBK = "乘/除/模运算符";
            break;
        case 0x11c:
            typeGBK = "自增/自减运算符";
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
    
    sprintf(buffer, "[%d : %d]    %0x     <%s>     %s\n", linenum, no, type, typeGBK, attribute);
    
    return string(buffer);
}

bool Token::isNumber(char ch, NumType type) {
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