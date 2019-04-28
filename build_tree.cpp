//
//  main.cpp
//  big_work_build_tree
//
//  Created by T on 2019/4/27.
//  Copyright © 2019年 T. All rights reserved.
//
//  To ensure that no one can recognize who we are, I changed the creator's name.     -F
//

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include"Function.h"
using namespace std;
Node* create_calculator(string s, int & count_arg) //后者是此运算符的参数个数
{
    Node* N;
    if(s=="+"||s=="-"||s=="*"||s=="/") //|| "Print" || ...
    {
        //Unary_Operator* una = new Unary_Operator ( s )
        
        count_arg = 1;
    }
    // Binary/...
    return N;
}
inline int priority ( std::string c )
{
    int pri = 0;
    if(c=="+")pri = 1;
    if(c=="-")pri = 1;
    if(c=="*")pri = 2;
    if(c=="/")pri = 2;
    return pri;
}
Node* connect(std::vector<string> vec, int head, int tail)
{
    Node* N;
    if(head==tail)
    {
        N = Var_map[vec[head]];
    }
    else
    {
        int count_bracket = 0;
        int position_least_priority = -1;
        int least_priority = 10000;//别搞出10000个运算符就好。。
        int count_arg;//运算符数
        for(int i = 0; i<vec.size(); i++ )
        {
            if(vec[i]=="("){count_bracket++;}
            else if(vec[i]==")"){count_bracket--;}
            else if(int x = priority(vec[i])&&!count_bracket)//有优先度，是运算符，且在括号外面
            {
                if(x<=least_priority) //相同优先度就取最右的（左结合）
                {
                    least_priority = x;
                    position_least_priority = i;
                }
            }
        }
        if(position_least_priority<0)//整个式子被括号括起来
        {
            N = connect(vec, head+1, tail-1);
        }
        else
        {
           N =  create_calculator(vec[position_least_priority], count_arg);//后者会被修改
            switch (count_arg) {
                case 1:
                    N->add_next(connect(vec, position_least_priority+1, tail));
                    break;
                    
                default:
                    N->add_next(connect(vec, head, position_least_priority-1));
                    N->add_next(connect(vec, position_least_priority+1, tail));
                    break;
            }
        }
    }
    return N;
}
