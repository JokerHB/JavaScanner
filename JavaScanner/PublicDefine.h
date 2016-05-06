//
//  PublicDefien.h
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#ifndef PublicDefien_h
#define PublicDefien_h

// buffer define
#define BUFFER_SIZE         512
#define BUFFER_HALF_SIZE    256
#define BUFFER_NUM          2

//word len
#define MAX_WORD_LEN        256

typedef unsigned int uInt;

const char KEYWORDS[50][20] = {
    "abstract",     "boolean",  "break",        "byte",         "case",         "catch",
    "char",         "class",    "const",        "continue",     "default",      "do",
    "double",       "else",     "extends",      "false",        "final",        "finally",
    "float",        "for",      "goto",         "if",           "implements",   "import",
    "instanceof",   "int",      "interface",    "long",         "native",       "new",      "null",
    "package",      "private",  "protected",    "public",       "return",       "short",
    "static",       "super",    "switch",       "synchronized", "this",         "throw",    "throws",
    "transient",   "true",      "try",          "void",         "volatile",     "while"
};

// number type
enum NumType {
    Dec,
    Hex,
    Oct
};

// dfa state
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
    Operator_Plus,
    Operator_Plus_Plus,
    Operator_Plus_Equal,
    Operator_Plus_Judge,
    Operator_Minus,
    Operator_Minus_Minus,
    Operator_Minus_Equal,
    Operator_Minus_Judge,
    Operator_Multiply,
    Operator_Multiply_Equal,
    Operator_Mod,
    Operator_Mod_Equal,
    Operator_Eauql,
    Operator_Eauql_Equal,
    Operator_Xor,
    Operator_Xor_Equal,
    Operator_Not,
    Operator_And,
    Operator_And_And,
    Operator_And_Equal,
    Operator_Large,
    Operator_Large_Equal,
    Operator_Large_Large,
    Operator_Large_Large_Large,
    Operator_Small,
    Operator_Small_Equal,
    Operator_Small_Small,
    Operator_Small_Small_Small,
    Operator_Or,
    Operator_Or_Or,
    Operator_Or_Equal,
    Operator_Exclamation,
    Operator_Exclamation_Equal,
    Operator_Ques,
    Operator_Ques_End,
    Error
};

#endif /* PublicDefien_h */
