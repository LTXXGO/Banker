//
//  main.cpp
//  Banker
//
//  Created by LTXX on 2019/5/26.
//  Copyright © 2019 LTXX. All rights reserved.
//

#include <iostream>
#include "Process.h"
#include "Banker.h"
using namespace std;

int main() {
    printCurrentStatusTable();
    safetyCheck();
    while (1) {
        int process;
        Resource resource;

        cout << "输入请求资源的进程下标(如0表示P0): ";
        cin >> process;
        cout << "输入请求资源的数量: " << endl;
        cout << "A: ";
        cin >> resource.A;
        cout << "B: ";
        cin >> resource.B;
        cout << "C: ";
        cin >> resource.C;
        
        if (request(process, resource))
        {
            cout << "分配成功。" << endl;
        } else {
            cout << "分配失败。" << endl;
        }
        
        cout << "继续分配？(Y/N): ";
        char select;
        cin >> select;
        if (select == 'N' || select == 'n') {
            break;
        } else if (select == 'Y' || select == 'y') {
            continue;
        } else {
            exit(-1);
        }
    }
    return 0;
}
