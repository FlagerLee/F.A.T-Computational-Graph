//
//  main.cpp
//  big_work_build_tree
//
//  Created by Kevin Tung on 2019/5/3.
//  Copyright © 2019年 Kevin Tung. All rights reserved.
//
#include <iostream>
#include "Node.h"
#include "build_tree.h"
#include "CG_debug.h"
#include "evaluation.h"
using namespace std;
int main()
{
    int n,m,q;
    string buffer;
    map<string,Node*> my_map;
    vector<int> set_answer_value;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        getline(cin,buffer);
    }
    cin>>m;
    for(int i=0; i<m; i++)
    {
        getline(cin,buffer);
        build_tree(buffer, my_map);
    }
    cin>>q;
    for(int i=0;i<q;i++)
    {
        getline(cin,buffer);
        double answer;
        if(Compute(buffer,my_map,answer,set_answer_value))
        {
            set_answer_value.push_back(answer);
            cout<<answer<<endl;
        }
    }

}
