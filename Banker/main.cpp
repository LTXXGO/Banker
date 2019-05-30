//
//  main.cpp
//  Banker
//
//  Created by LTXX on 2019/5/26.
//  Copyright © 2019 LTXX. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Martix.h"
using namespace std;

const int numberOfProcesses = 5;
const int numberOfResource = 3;

vector<int> Available(numberOfResource);
Martix<int> Max(numberOfProcesses, numberOfResource);
Martix<int> Allocation(numberOfProcesses, numberOfResource);
Martix<int> Need(numberOfProcesses, numberOfResource);

Martix<int> Request(numberOfProcesses, numberOfResource);

// MARK: - 银行家算法
void Banker(int i, int j) {
    if (Request.elem[i][j] <= Need.elem[i][j]) {
        if (Request.elem[i][j] <= Available[j]) {
            cout << "系统试探将资源分配给进程 P[i]" << endl;
            Available[j] = Available[j] - Request.elem[i][j];
            Allocation.elem[i][j] = Allocation.elem[i][j] + Request.elem[i][j];
            Need.elem[i][j] = Need.elem[i][j] - Request.elem[i][j];
        } else {
            cout << "i = " << i << ", j = " << j << endl;
            cout << "尚无足够资源, 需要等待" << endl;
        }
    } else {
        cout << "出错, 所需资源已超过所宣布的最大值" << endl;
        exit(-1);
    }
    // 执行安全性算法, 若分配后系统安全, 则将资源正式分配给进程 P[i] , 否则恢复原状态, 让进程 P[i] 等待
}

// MARK: - 安全性算法
bool securityCheck(int j) {
    vector<int> Work(Available.size());
    vector<bool> Finish(numberOfProcesses, false);
    for (int i = 0; i < numberOfProcesses; i += 1) {
        if (Finish[i] == false && Need.elem[i][j] <= Work[j]) {
            Work[j] = Work[j] + Allocation.elem[i][j];
            Finish[i] = true;
        }
    }
    for (int i = 0; i < numberOfProcesses; i += 1) {
        if(Finish[i] == false) {
            return false;
        }
    }
    return true;
}

int main() {
    
    return 0;
}
