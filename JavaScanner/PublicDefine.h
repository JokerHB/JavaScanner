//
//  PublicDefien.h
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#ifndef PublicDefien_h
#define PublicDefien_h

#define BUFFER_SIZE         512
#define BUFFER_HALF_SIZE    256
#define BUFFER_NUM          2

#define MAX_WORD_LEN        256

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

#endif /* PublicDefien_h */
