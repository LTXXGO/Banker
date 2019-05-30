//
//  main.cpp
//  Banker
//
//  Created by LTXX on 2019/5/26.
//  Copyright © 2019 LTXX. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Process.h"
using namespace std;

//试探分配
void tryAllocate(int process, Resource resource)
{
    Available.A -= resource.A;
    Available.B -= resource.B;
    Available.C -= resource.C;
    
    Allocation[process].A += resource.A;
    Allocation[process].B += resource.B;
    Allocation[process].C += resource.C;
    
    Need[process].A -= resource.A;
    Need[process].B -= resource.B;
    Need[process].C -= resource.C;
}

//若试探分配后进入不安全状态，将分配回滚
void rollBack(int process, Resource resource)
{
    Available.A += resource.A;
    Available.B += resource.B;
    Available.C += resource.C;
    
    Allocation[process].A -= resource.A;
    Allocation[process].B -= resource.B;
    Allocation[process].C -= resource.C;
    
    Need[process].A += resource.A;
    Need[process].B += resource.B;
    Need[process].C += resource.C;
}

//安全性检查
bool safeCheck()
{
    Resource Work = Available;
    bool Finish[NumberOfProcesses] = {false, false, false, false, false};
    int j = 0;
    
    for (int i = 0; i < NumberOfProcesses; i++) {
        //是否已检查过
        if (Finish[i] == false) {
            //是否有足够的资源分配给该进程
            if (Need[i].A <= Work.A && Need[i].B <= Work.B && Need[i].C <= Work.C) {
                // 有则使其执行完成，并将已分配给该进程的资源全部回收
                Work.A += Allocation[i].A;
                Work.B += Allocation[i].B;
                Work.C += Allocation[i].C;
                Finish[i] = true;
                safe[j] = i;
                j += 1;
                i = -1;//重新进行遍历
            }
        }
    }
    // 如果所有进程的 Finish 向量都为 true 则处于安全状态，否则为不安全状态
    for (int i = 0; i < NumberOfProcesses; i++) {
        if (Finish[i] == false) {
            return false;
        }
    }
    return true;
}

//资源分配请求
bool request(int process, Resource resource) {
    // request 向量需小于Need矩阵中对应的向量
    if(resource.A <= Need[process].A && resource.B <= Need[process].B && resource.C <= Need[process].C) {
        // request 向量需小于Available向量
        if(resource.A <= Available.A && resource.B <= Available.B && resource.C <= Available.C) {
            // 试探分配
            tryAllocate(process,resource);
            // 安全检查, 如果安全则完成本次请求
            if(safeCheck()) {
                return true;
            } else {
                // 否则将试探分配资源回滚
                cout << "安全性检查失败。原因：系统将进入不安全状态，可能引起死锁。" << endl;
                rollBack(process, resource);
            }
        } else {
            cout << "安全性检查失败。原因：请求向量大于可利用资源向量。" << endl;
        }
    } else {
        cout << "安全性检查失败。原因：请求向量大于需求向量。" << endl;
    }
    return false;
}

//输出资源分配表
void printCurrentStatusTable()
{
    cout << "当前时刻资源分配情况: " << endl;
    cout << "+--------------------------------------------------------+" << endl;
    cout << "|       |    Max    |Allocation |    Need   | Available  |" << endl;
    cout << "|Process|-----------+-----------+-----------+------------|" << endl;
    cout << "|       | A   B   C | A   B   C | A   B   C | A   B   C  |" << endl;
    cout << "|-------+-----------+-----------+-----------+------------|" << endl;
    
    printf( "| P0    | %d   %d   %d | %d   %d   %d | %d   %d   %d | %d   %d   %d  |\n", Max[0].A,Max[0].B,Max[0].C,Allocation[0].A,Allocation[0].B,Allocation[0].C,Need[0].A,Need[0].B,Need[0].C,Available.A,Available.B,Available.C);
    cout << "|-------+-----------+-----------+-----------+------------|" << endl;
    
    for (int i = 1; i < NumberOfProcesses; i++) {
        printf( "| P%d    | %d   %d   %d | %d   %d   %d | %d   %d   %d |            |\n",
               i,
               Max[i].A, Max[i].B, Max[i].C,
               Allocation[i].A, Allocation[i].B, Allocation[i].C,
               Need[i].A, Need[i].B, Need[i].C);
        cout << "|-------+-----------+-----------+-----------+------------|" << endl;
    }
    cout << endl;
}

int main() {
    printCurrentStatusTable();
    if (safeCheck()) {
        printf("当前系统处于安全状态。\n");
        printf("安全序列是{ P%d, P%d, P%d, P%d, P%d }。\n", safe[0], safe[1], safe[2], safe[3], safe[4]);
    } else {
        printf("当前系统处于不安全状态。\n");
        exit(-1);
    }
    
    char ch;
    do {
        int process;
        Resource resource;
        printCurrentStatusTable();
        printf("请依次输入请求分配的进程和对三类资源的请求数量：");
        cin >> process >> resource.A >> resource.B >> resource.C;
        if (request(process, resource))
        {
            printf("分配成功。\n");
            printf("安全序列是{P%d,P%d,P%d,P%d,P%d}。\n",safe[0],safe[1],safe[2],safe[3],safe[4]);
        } else {
            cout << "分配失败。" << endl;
        }
        printf("是否继续分配？(Y/N):");
        cin >> ch;
    } while (ch == 'Y' || ch == 'y');

over:
    printf("执行完毕。");
    return 0;
}
