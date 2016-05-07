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
    if (argc == 3) {
        Scanner scan(argv[1]);
        
        scan.scan();
        
        for (int i = 0; i < scan.tokens.size(); i ++) {
            cout<<scan.tokens[i].toString()<<endl;
        }
        
        scan.write(argv[2]);
    } else {
        Scanner scan("./Test-Lexcial.java");
        
        scan.scan();
        
        for (int i = 0; i < scan.tokens.size(); i ++) {
            cout<<scan.tokens[i].toString()<<endl;
        }
        
        scan.write("./scanner_output.txt");
    }
    
    return 0;
}
