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
#include "Scanner.hpp"
#include "Token.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
//    SpecailBuffer spb("/Users/joker/Desktop/BITMiniCC.java");
//    char ch;
//    
//    while((ch = spb.getNextChar()) != -1) {
//        cout<<ch;
//    }
    
//    cout<<"finished"<<endl;
//    
//    for (int i = 0;i < 50;i ++) {
//        cout<<KEYWORDS[i] <<" "<<i <<endl;
//    }
    
    Scanner scan("/Users/joker/Desktop/BITMiniCC.java");
    
    scan.scan();
    
    for (int i = 0; i < scan.tokens.size(); i ++) {
        cout<<scan.tokens[i].toString()<<endl;
    }
    
    return 0;
}
