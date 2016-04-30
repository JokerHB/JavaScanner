//
//  main.cpp
//  JavaScanner
//
//  Created by 靳洪博 on 16/4/30.
//  Copyright © 2016年 靳洪博. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <vector>

#include "SpecialBuffer.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    SpecailBuffer spb("/Users/joker/Desktop/BITMiniCC.java");
    char ch;
    
    while((ch = spb.getNextChar()) != -1) {
        cout<<ch;
    }
    
    cout<<"finished"<<endl;
    
    return 0;
}
