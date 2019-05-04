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
    
    /**********语法检查**********/

    double v ;
    if ( vec.size() >= 3 )
    {
        try
        {
            v = stod ( vec [ 2 ] ) ;
        }
        catch ( std::invalid_argument& )
        {
            throw_error ( 10 ) ;
            return ;
        }
        catch ( std::out_of_range& )
        {
            throw_error ( 17 ) ;
            return ;
        }
    }

    /**********end**********/

    /**********创建Placeholder结点**********/

    if ( vec [ 1 ] == "P" )
    {
        if ( Var_map.find ( vec [ 0 ] ) != Var_map.end() )
        {
            throw_error ( 19 ) ;
            return ;
        } 
        Node* N = new Placeholder ( vec [ 0 ] ) ;
        Var_map [ vec [ 0 ] ] = N ;
        return ;
    }

    /**********end**********/

    /**********创建Constant结点**********/

    if ( vec [ 1 ] == "C" )
    {
        if ( vec.size () < 3 )
        {
            throw_error ( 10 ) ;
            return ;
        }
        if ( Var_map.find ( vec [ 0 ] ) != Var_map.end() )
        {
            throw_error ( 19 ) ;
            return ;
        }
        Node* N = new Constant ( vec [ 0 ] , v ) ;
        Var_map [ vec [ 0 ] ] = N ;
        return ;
    }

    /**********end**********/

    /**********创建Variable结点**********/

    if ( vec [ 1 ] == "V" )
    {
        if ( vec.size () < 3 )
        {
            throw_error ( 10 ) ;
            return ;
        }
        if ( Var_map.find ( vec [ 0 ] ) != Var_map.end() ) 
        {
            throw_error ( 19 ) ;
            return ;
        }
        Node* N = new Var_Constant ( vec [ 0 ] , v ) ;
        Var_map [ vec [ 0 ] ] = N ;
        return ;
    }

    /**********end**********/

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
    else if(s=="+"||s=="-"||s=="*"||s=="/"||s=="<"||s==">"||s=="<="||s==">="||s=="==") //|| "Print" || ...
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
    else
    {
        puts ( "continue" ) ;
        throw "No match operator" ;
    }
    return N;
}
inline int priority ( std::string c )
{
    if ( c == "<" ) return 1 ;
    if ( c == ">" ) return 1 ;
    if ( c == "<=" ) return 1 ;
    if ( c == ">=" ) return 1 ;
    if ( c == "==" ) return 1 ;
    if(c=="+") return 2 ;
    if(c=="-") return 2 ;
    if(c=="*") return 3 ;
    if(c=="/") return 3 ;
    if ( c == "SIN" ) return 4 ;
    if ( c == "LOG" ) return 4 ;
    if ( c == "EXP" ) return 4 ;
    if ( c == "SIGMOID" ) return 4 ;
    if ( c == "TANH" ) return 4 ;
    if ( c == "PRINT" ) return 5 ;
    if ( c == "COND" ) return 5 ;
    return 0 ;
}
void init(Node* N)
{
    std::string s = N->get_name();
    if( s == "Var" )
    {
        Var* v = dynamic_cast < Var* > ( N ) ;
        v->have_value = false;
    }
    else if ( s == "Placeholder" )
    {
        Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
        p -> have_value = false ;
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
    if ( iter != Var_map.end() && iter -> second -> get_name () != "Var" )
    {
        throw_error ( 19 ) ;
        return ;
    }
    Node* node = new Var(vec[0]); //確定是Var類型
    if ( vec.size () < 2 || vec [ 1 ] != "=" )
    {
        throw_error ( 10 ) ;
        return ;
    }
    bool is_legal = true ;
    Node* N = connect ( vec , Var_map , 2 , vec.size() - 1 , is_legal ) ;
    if ( !is_legal )
    {
        std::cout << "Connect failed\n" ;
        return ;
    }
    node->add_next(N); //＊
    Var_map [ vec [ 0 ] ] = node ;
}
Node* connect(std::vector<string> vec , std::map<std::string , Node*> Var_map , int head , int tail , bool& is_legal )
{
    //std::cout << head << " " << tail << "\n" ;
    Node* N;
    if ( head > tail ) //你能触发这个错误算你赢
                       //行吧打脸了，刚写完这个注释我就触发了这个错误。
    {
        is_legal = false ;
        throw_error ( 0 ) ;
        return N ;
    }
    if(head==tail)
    {
        if ( Var_map.find ( vec [ head ] ) != Var_map.end() ) N = Var_map [ vec [ head ] ] ;
        else
        {
            is_legal = false ;
            throw_error ( 7 , vec [ head ] ) ;
            return N ;
        }
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
            //std::cout << position_least_priority << "\n" ;
            if(vec[i]=="("){count_bracket++;}
            else if(vec[i]==")"){count_bracket--;}
            else if(priority(vec[i])&&!count_bracket)//有优先度，是运算符，且在括号外面
            {
                int x = priority ( vec [ i ] ) ;
                if(x<=least_priority) //相同优先度就取最右的（左结合）
                {
                    least_priority = x;
                    position_least_priority = i;
                }
            }
        }
        if(position_least_priority<0)//整个式子被括号括起来
        {
            if ( vec [ head ] != "(" || vec [ tail ] != ")" )
            {
                throw_error ( 10 ) ;
                is_legal = false ;
                return N ;
            }
            N = connect(vec, Var_map, head+1, tail-1 , is_legal );
            if ( !is_legal ) return N ;
        }
        else
        {
            try
            {
                N =  create_calculator(vec[position_least_priority], count_arg);//后者会被修改
            }
            catch ( const char* s ) 
            {
                throw_error ( 5 ) ;
                is_legal = false ;
                return N ;
            }
            switch (count_arg) {
                case 1:
                {
                    Node* n = connect ( vec , Var_map , position_least_priority + 1 , tail , is_legal ) ;
                    if ( !is_legal ) return N ;
                    N->add_next(n);
                    break;
                }
                    
                case 2:
                {
                    Node* n1 = connect ( vec , Var_map , head , position_least_priority - 1 , is_legal ) ;
                    if ( !is_legal ) return N ;
                    Node* n2 = connect ( vec , Var_map , position_least_priority + 1 , tail , is_legal ) ;
                    if ( !is_legal ) return N ;
                    N -> add_next ( n1 ) ; N -> add_next ( n2 ) ;
                    break;
                }
                
                case 3:
                {
                    N->add_next(Var_map[vec[3]]);
                    N->add_next(Var_map[vec[4]]);
                    N->add_next(Var_map[vec[5]]);
                    break;
                }
                    
            }
        }
    }
    return N;
}