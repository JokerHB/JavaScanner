//
//  SpecialBuffer.hpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#ifndef _SpecialBuffer_hpp
#define _SpecialBuffer_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "PublicDefine.h"

using namespace std;

class SpecailBuffer {
public:
//  MARK: -init the buffer
    SpecailBuffer(string filePath);
    ~SpecailBuffer();
    
//  MARK: -get the char form the buffer
    char getNextChar();
    
private:
//  MARK: -reset the current buffer
    void resetBuffer(int bufId);
    
//  MARK: -full the buffer form file
    int fillBuffer(int bufid);
    
//  MARK: -buffer define
    char buffer[BUFFER_NUM][BUFFER_SIZE];
    
//  MARK: -buffer point
    int pBuffer[BUFFER_NUM];
    
//  MARK: -buffer flag, indicate first/second buffer
    int bufferFlag;
    
//  MARK: -input file stream
    ifstream in;
};

#endif /* _SpecialBuffer_hpp */
