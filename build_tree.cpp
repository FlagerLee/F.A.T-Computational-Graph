//
//  main.cpp
//  big_work_build_tree
//
//  Created by Kevin Tung on 2019/4/27.
//  Copyright © 2019年 Kevin Tung. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "build_tree.h"
#include<sstream>
using namespace std;
void build_tree(string s);
Node* connect(std::vector<string> vec, int head, int tail);
Node* create_calculator(string s, int & count_arg);
inline int priority (std::string c);
Node* create_calculator(string s, int & count_arg) //后者是此运算符的参数个数
{
    Node* N ;
    if ( s == "Print" || s == "SIN" || s == "LOG" || s == "EXP" || s == "SIGMOID" || s == "TANH" )
    {
        N = new Unary_Operator ( s ) ;
        count_arg = 1 ;
    }
    else if(s=="+"||s=="-"||s=="*"||s=="/") //|| "Print" || ...
    {
        //Unary_Operator* una = new Unary_Operator ( s )
        N = new Binary_Operator ( s ) ;
        count_arg = 2 ;
    }
    else if ( s == "COND" )
    {
        N = new Ternary_Operator ( s ) ;
        count_arg = 3 ;
    }
    // Binary/...
    return N;
}
void build_tree(string s)   // 要有單純string版本的初始化
                                        //已經確定了第一節為變量名、第二節為 "="
{
    stringstream is(s);
    string buf;
    vector<string> vec;
    while(is>>buf)vec.push_back(buf);
    
    if(!Var_map.count(vec[0]))
    {
        delete_tree(Var_map[vec[0]]);
    }
    
    Var* node = new Var(vec[0]); //確定是Var類型
    node->add_next(connect(vec, 2, vec.size()-1)); //＊
    return;
}
void delete_tree ( Node* N )
{
    int len = N -> next.size() ;
    for ( int i = len - 1 ; i >=0 ; i -- )
    {
        std::string s = N -> next [ i ] -> get_name() ;
        if ( s == "Placeholder" || s == "Constant" || s == "Var" || s == "Var_Constant" ) continue ;
        else delete_tree ( N -> next [ i ] ) ;
            delete ( N -> next [ i ] ) ;
    }
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
                    
                case 2:
                    N->add_next(connect(vec, head, position_least_priority-1));
                    N->add_next(connect(vec, position_least_priority+1, tail));
                    break;
            }
        }
    }
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

void init(Node* N)
{
    std::string s = N->get_name;
    if(s=="var"||s=="placeholder")
    {
        N->have_value = false;
        N->is_Printed = false;
    }
    int size = N->next.size();
    for(int i=0;i<size;i++)
    {
        init ( N -> next [ i ] );
    }
}
















