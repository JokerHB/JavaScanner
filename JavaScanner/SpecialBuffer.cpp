//
//  SpecialBuffer.cpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#include "SpecialBuffer.hpp"

SpecailBuffer::SpecailBuffer(string filePath) {
//  MARK: -open the file
    in.open(filePath, ifstream::in);
    
//  MARK: -check the file
    if (!in.failbit) {
        cout << "can not open the file" << filePath <<endl;
        exit(1);
    }
    
//  MARK: -prepare for the buffer
    resetBuffer(0);
    resetBuffer(1);
    bufferFlag = 0;
    
    if (fillBuffer(bufferFlag) != 1) {
        exit(1);
    }
    
    cout<<"specail buffer is ready"<<endl;
}

SpecailBuffer::~SpecailBuffer() {
    cout<<"buffer exit"<<endl;
    in.close();
}

void SpecailBuffer::resetBuffer(int bufid) {
    memset(buffer[bufid], 0, BUFFER_SIZE * sizeof(char));
    pBuffer[bufid] = 0;
}

int SpecailBuffer::fillBuffer(int bufid) {
    resetBuffer(bufid);
    
    if (in.good()) {
        try {
            in.read(buffer[bufid], BUFFER_SIZE);
        } catch(...) {
            cout<<"can not read from the buffer"<<endl;
            resetBuffer(bufid);
            return -1;
        }
    } else {
        return -1;
    }
    
    return 1;
}

char SpecailBuffer::getNextChar() {
//  MARK: -check the buffer
    if (pBuffer[bufferFlag] == BUFFER_SIZE) {
        bufferFlag ++;
        bufferFlag %= BUFFER_NUM;
        if (fillBuffer(bufferFlag) == -1) {
            return (char)(-1);
        }
    }
    
    return buffer[bufferFlag][pBuffer[bufferFlag] ++];
    
}

void SpecailBuffer::backSpace() {
    pBuffer[bufferFlag] --;

    pBuffer[bufferFlag] = pBuffer[bufferFlag] <= 0 ? 0 : pBuffer[bufferFlag];
}