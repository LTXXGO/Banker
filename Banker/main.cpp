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
    char select = 'Y';
    while (select == 'Y' || select == 'y') {
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
        if (request(process, resource)) {
            cout << "分配成功。" << endl;
        } else {
            cout << "分配失败。" << endl;
        }
        cout << "继续分配？(Y/N): ";
        cin >> select;
    }
    return 0;
}
