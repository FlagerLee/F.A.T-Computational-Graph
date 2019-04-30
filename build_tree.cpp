//  main.cpp
	//  big_work_build_tree
	//
	//  Created by T on 2019/4/27.
	//  Copyright © 2019年 T. All rights reserved.
	//
	//  To ensure that no one can recognize who we are, I changed the creator's name.     -F
	//  Created by Kevin Tung on 2019/4/27.
	//  Copyright © 2019年 Kevin Tung. All rights reserved.
	//
	
	#include <iostream>
	#include <vector>
	#include <string>
	#include "Node.h"
	#include"Function.h"
	#include<sstream>
	using namespace std;
	void build_tree(string s);
	Node* connect(std::vector<string> vec, int head, int tail);
	Node* create_calculator(string s, int & count_arg);
	inline int priority ( std::string c );
	Node* create_calculator(string s, int & count_arg) //后者是此运算符的参数个数
	{
	    Node* N;
	    if(s=="+"||s=="-"||s=="*"||s=="/") //|| "Print" || ...
	    if(s=="+"||s=="-"||s=="*"||s=="/")
	    {
	        //Unary_Operator* una = new Unary_Operator ( s )
	
	
	        count_arg = 1;
	    }
	    // Binary/...
	    return N;
	}
	inline int priority ( std::string c )
	void build_tree(string s)   // 要有單純string版本的初始化
	                                        //已經確定了第一節為變量名、第二節為 "="
	{
	    int pri = 0;
	    if(c=="+")pri = 1;
	    if(c=="-")pri = 1;
	    if(c=="*")pri = 2;
	    if(c=="/")pri = 2;
	    return pri;
	    stringstream is(s);
	    string buf;
	    vector<string> vec;
	    while(is>>buf)vec.push_back(buf);
	    Var* node = new Var(vec[0]); //確定是Var類型
	    node->add_next(connect(vec, 2, vec.size()-1)); //＊
	    return;
	}
	Node* connect(std::vector<string> vec, int head, int tail)
	{
 @@ -73,7 +77,7 @@ Node* connect(std::vector<string> vec, int head, int tail)
	                    N->add_next(connect(vec, position_least_priority+1, tail));
	                    break;
	
	                default:
	                case 2:
	                    N->add_next(connect(vec, head, position_least_priority-1));
	                    N->add_next(connect(vec, position_least_priority+1, tail));
	                    break;
 @@ -82,3 +86,29 @@ Node* connect(std::vector<string> vec, int head, int tail)
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
	
