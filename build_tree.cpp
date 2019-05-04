#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "build_tree.h"
#include "CG_debug.h"
using namespace std;

void build_var ( string s , map < string , Node* >& Var_map )
{
    stringstream in ( s ) ;
    vector < string > vec ;
    string buffer ;
    while ( in >> buffer ) vec.push_back ( buffer ) ;
    if ( vec [ 1 ] == "P" )
    {
        Node* N = new Placeholder ( vec [ 0 ] ) ;
        Var_map [ vec [ 0 ] ] = N ;
        return ;
    }
    if ( vec [ 1 ] == "C" )
    {
        Node* N = new Constant ( vec [ 0 ] , stod ( vec [ 2 ] ) ) ;
        Var_map [ vec [ 0 ] ] = N ;
        return ;
    }
    if ( vec [ 1 ] == "V" )
    {
        Node* N = new Var_Constant ( vec [ 0 ] , stod ( vec [ 2 ] ) ) ;
        Var_map [ vec [ 0 ] ] = N ;
        return ;
    }
    throw_error ( 15 ) ;
    return ;
}

Node* create_calculator(string s, int & count_arg) //后者是此运算符的参数个数
{
    Node* N ;
    if ( s == "PRINT" || s == "SIN" || s == "LOG" || s == "EXP" || s == "SIGMOID" || s == "TANH" )
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
inline int priority ( std::string c )
{
    if(c=="+") return 1 ;
    if(c=="-") return 1 ;
    if(c=="*") return 2 ;
    if(c=="/") return 2 ;
    if ( c == "SIN" ) return 3 ;
    if ( c == "LOG" ) return 3 ;
    if ( c == "EXP" ) return 3 ;
    if ( c == "SIGMOID" ) return 3 ;
    if ( c == "TANH" ) return 3 ;
    if ( c == "PRINT" ) return 4 ;
    return 0 ;
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
void init(Node* N)
{
    std::string s = N->get_name();
    if( s == "Var" )
    {
        Var* v = dynamic_cast < Var* > ( N ) ;
        v->have_value = false;
        v->is_Printed = false;
    }
    else if ( s == "Placeholder" )
    {
        Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
        p -> have_value = false ;
        p -> is_Printed = false ;
    }
    else if ( s == "Constant" )
    {
        Constant* c = dynamic_cast < Constant* > ( N ) ;
        c -> is_Printed = false ;
    }
    else if ( s == "Var_Constant" )
    {
        Var_Constant* vc = dynamic_cast < Var_Constant* > ( N ) ;
        vc -> is_Printed = false ;
    }
    int size = N->next.size();
    for(int i=0;i<size;i++)
    {
        init ( N -> next [ i ] );
    }
}

void build_tree(string s, std::map < std::string , Node* >& Var_map )   // 要有單純string版本的初始化
//已經確定了第一節為變量名、第二節為 "="
{
    stringstream is(s);
    string buf;
    vector<string> vec;
    while(is>>buf)vec.push_back(buf);
    std::map < std::string , Node* >::iterator iter = Var_map.find ( vec [ 0 ] ) ;
    if ( iter != Var_map.end() ) delete_tree ( Var_map [ vec [ 0 ] ] ) ;
    Node* node = new Var(vec[0]); //確定是Var類型
    if ( vec.size () < 2 || vec [ 1 ] != "=" )
    {
        throw_error ( 10 ) ;
        return ;
    }
    node->add_next(connect(vec, Var_map , 2, vec.size()-1)); //＊
    Var_map [ vec [ 0 ] ] = node ;
}
Node* connect(std::vector<string> vec , std::map<std::string , Node*> Var_map , int head , int tail)
{
   // std::cout << head << " " << tail << "\n" ;
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
        //std::cout << vec [ head ] << "\n" ;
        for(int i = head; i<=tail; i++ )
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
            N = connect(vec, Var_map, head+1, tail-1);
        }
        else
        {
            N =  create_calculator(vec[position_least_priority], count_arg);//后者会被修改
            switch (count_arg) {
                case 1:
                    N->add_next(connect(vec, Var_map, position_least_priority+1, tail));
                    break;
                    
                case 2:
                    N->add_next(connect(vec, Var_map, head, position_least_priority-1));
                    N->add_next(connect(vec, Var_map, position_least_priority+1, tail));
                    break;
                
                case 3:
                    
            }
        }
    }
    return N;
}