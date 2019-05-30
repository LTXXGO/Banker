//
//  Process.h
//  Banker
//
//  Created by LTXX on 2019/5/30.
//  Copyright © 2019 LTXX. All rights reserved.
//

#ifndef Process_h
#define Process_h

// 进程数量
#define NumberOfProcesses 5

struct Resource{
    int A;
    int B;
    int C;
};

//记录安全序列
int safe[NumberOfProcesses];

//最大需求矩阵
Resource Max[NumberOfProcesses] =
{
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

//已分配资源数矩阵
Resource Allocation[NumberOfProcesses] =
{
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

//需求矩阵
Resource Need[NumberOfProcesses] =
{
    {7, 4, 3},
    {1, 2, 2},
    {6, 0, 0},
    {0, 1, 1},
    {4, 3, 1}
};

Resource Available = {3, 3, 2};
Resource Work;
bool Finish[NumberOfProcesses] = {false, false, false, false, false};

#endif /* Process_h */
