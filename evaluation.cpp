#include "Node.h"
#include "CG_debug.h"
#include "build_tree.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>

double get_value ( Node* N ) //必须确保N指向的是Var类或Placeholder类或Constant类或Var_Constant类
{
    std::string s = N -> get_name () ;
    if ( s == "Var" )
    {
        Var* v = dynamic_cast < Var* > ( N ) ;
        return v -> value ;
    }
    else if ( s == "Placeholder" )
    {
        Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
        return p -> value ;
    }
    else if ( s == "Constant" )
    {
        Constant* c = dynamic_cast < Constant* > ( N ) ;
        return c -> value ;
    }
    else if ( s == "Var_Constant" )
    {
        Var_Constant* vc = dynamic_cast < Var_Constant* > ( N ) ;
        return vc -> value ;
    }
    throw_error ( 12 , s ) ;
    return 0.0 ;
}

bool eval ( double v , Node* N ) //必须确保N指向的是Var类或Placeholder类
{
    std::string s = N -> get_name () ;
    if ( s == "Var" )
    {
        Var* var = dynamic_cast < Var* > ( N ) ;
        var -> value = v ;
        return true ;
    }
    if ( s == "Placeholder" )
    {
        Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
        p -> value = v ;
        return true ;
    }
    throw_error ( 6 ) ;
    return false ;
}

std::string get_var_name ( Node* N )
{
    std::string name = N -> get_name () ;
    if ( name == "Placeholder" )
    {
        Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
        return p -> var_name ;
    }
    if ( name == "Var" )
    {
        Var* var = dynamic_cast < Var* > ( N ) ;
        return var -> var_name ;
    }
    if ( name == "Constant" )
    {
        Constant* c = dynamic_cast < Constant* > ( N ) ;
        return c -> var_name ;
    }
    if ( name == "Var_Constant" )
    {
        Var_Constant* vc = dynamic_cast < Var_Constant* > ( N ) ;
        return vc -> var_name ;
    }
    throw_error ( 10 ) ;
    return "" ;
}

bool Compute ( std::string s , std::map < std::string , Node* > Var_map , std::vector < double > setanswer , double& answer ) //输入一个字符串s,将其计算出来
{
    std::stringstream in ( s ) ;
    std::string buf ;
    std::vector < std::string > vec ;
    while ( in >> buf ) vec.push_back ( buf ) ;
    if ( vec.size() == 0 )
    {
        throw_error ( 10 ) ;
        return false ;
    }
    if ( vec [ 0 ] == "SETCONSTANT" )
    {
        if ( vec.size () < 3 )
        {
            throw_error ( 10 ) ;
            return false ;
        }
        if ( Var_map.find ( vec [ 1 ] ) == Var_map.end() )
        {
            throw_error ( 11 , vec [ 1 ] ) ;
            return false ;
        }
        
        double v = stod ( vec [ 2 ] ) ;
        //此处本想try-catch，但由于不知道atof但错误返回就没有实现
        if ( Var_map [ vec [ 1 ] ] -> get_name () != "Var_Constant" )
        {
            throw_error ( 13 ) ;
            return false ;
        }
        Var_Constant* vc = dynamic_cast < Var_Constant* > ( Var_map [ vec [ 1 ] ] ) ;
        vc -> set ( v ) ;
        return false ;
    }
    else if ( vec [ 0 ] == "SETANSWER" )
    {
        if ( vec.size() < 3 )
        {
            throw_error ( 10 ) ;
            return false ;
        }
        if ( Var_map.find ( vec [ 1 ] ) == Var_map.end() )
        {
            throw_error ( 11 , vec [ 1 ] ) ;
            return false ;
        }
        Var_Constant* vc = dynamic_cast < Var_Constant* > ( Var_map [ vec [ 1 ] ] ) ;
        int i = stoi ( vec [ 2 ] ) ;
        vc -> set ( setanswer [ i - 1 ] ) ;
        return false ;
    }
    else if ( vec [ 0 ] == "EVAL" )
    {
        if ( Var_map.find(vec [ 1 ] ) == Var_map.end() )
        {
            throw_error ( 11 , vec [ 1 ] ) ;
            return false ;
        }
        int Placeholder_number = stoi ( vec [ 2 ] ) ;
        if ( Placeholder_number * 2 + 3 > vec.size() )
        {
            throw_error ( 10 ) ;
            return false ;
        }
        for ( int i = 1 ; i <= Placeholder_number ; i ++ )
        {
            std::string name = vec [ 2 + ( 2 * i ) - 1 ] ;
            if ( Var_map.find ( name ) == Var_map.end() )
            {
                throw_error ( 11 , vec [ 2 + ( 2 * i ) - 1 ] ) ;
                return false ;
            }
            Node* &N = Var_map [ name ] ;
            std::string type_name = N -> get_name () ;
            if ( type_name != "Placeholder" )
            {
                throw_error ( 14 ) ;
                return false ;
            }
            double v = stod ( vec [ 2 + ( 2 * i ) ] ) ;
            eval ( v , N ) ;
            Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
            p -> have_value = true ;
        }
        bool is_legal = true ;
        answer = com ( Var_map [ vec [ 1 ] ] , is_legal ) ;
        init ( Var_map [ vec [ 1 ] ] ) ;
        return is_legal ;
    }
    throw_error ( 10 ) ;
    return false ;
}

double com( Node* N , bool& is_legal )
{
    int len=N->next.size();
    if(len==0)
    {
        std::string name = N -> get_name() ;
        if ( name == "Placeholder" )
        {
            Placeholder* p = dynamic_cast < Placeholder* > ( N ) ;
            if ( p -> have_value ) return get_value ( N ) ;
            else
            {
                is_legal = false ;
                throw_error ( 2 ) ;
                return 0.0 ;
            }
        }
        else
        {
            return get_value ( N ) ;
        }
    }
    else if(len==1)
    {
        std::string name = N -> get_name() ;
        if ( name == "Var" )
        {
            Var* var = dynamic_cast < Var* > ( N ) ;
            if ( var -> have_value ) return get_value ( N ) ;
            else
            {
                double v = com ( N -> next[0] , is_legal ) ;
                if ( !is_legal ) return 0.0 ;
                if ( eval ( v , N ) ) return v ;
                else //此处其实已经保证了eval的是var结点，不会进入此else分支。但我就是想写这个else。。。
                {
                    is_legal = false ;
                    return 0.0 ;
                }
            }
        }
        else
        {
            Unary_Operator* una = dynamic_cast < Unary_Operator* > ( N ) ;
            double v0 = com ( N -> next[0] , is_legal ) ;
            if ( !is_legal ) return 0.0 ;
            double v ;
            if ( una -> cal_name == "PRINT" )
            {
                Node* n = una -> next [ 0 ] ;
                std::string next_name = n -> get_name () ;
                if ( next_name == "Placeholder" )
                {
                    Placeholder* p = dynamic_cast < Placeholder* > ( n ) ;
                    if ( ! ( p -> is_Printed ) )
                    {
                        v = una -> cal ( una -> cal_name , v0 , is_legal , get_var_name ( N -> next [ 0 ] ) ) ;
                        p -> is_Printed = true ;
                    }
                    else v = v0 ;
                }
                else if ( next_name == "Var" )
                {
                    Var* var = dynamic_cast < Var* > ( n ) ;
                    if ( ! ( var -> is_Printed ) )
                    {
                        v = una -> cal ( una -> cal_name , v0 , is_legal , get_var_name ( N -> next [ 0 ] ) ) ;
                        var -> is_Printed = true ;
                    }
                    else v = v0 ;
                }
                else if ( next_name == "Constant" )
                {
                    Constant* c = dynamic_cast < Constant* > ( n ) ;
                    if ( ! ( c -> is_Printed ) ) 
                    {
                        v = una -> cal ( una -> cal_name , v0 , is_legal , get_var_name ( N -> next [ 0 ] ) ) ;
                        c -> is_Printed = true ;
                    }
                    else v = v0 ;
                }
                else if ( next_name == "Var_Constant" )
                {
                    Var_Constant* vc = dynamic_cast < Var_Constant* > ( n ) ;
                    if ( ! ( vc -> is_Printed ) )
                    {
                        v = una -> cal ( una -> cal_name , v0 , is_legal , get_var_name ( N -> next [ 0 ] ) ) ;
                        vc -> is_Printed = true ;
                    }
                    else v = v0 ;
                }
            }
            else v = una -> cal ( una -> cal_name , v0 , is_legal ) ;
            if ( !is_legal ) return 0.0 ;
            return v ;
        }
    }
    else if(len==2)
    {
        Binary_Operator* bin = dynamic_cast < Binary_Operator* > ( N ) ;
        double v1 = com ( N -> next[0] , is_legal ) ;
        if ( !is_legal ) return 0.0 ;
        double v2 = com ( N -> next[1] , is_legal ) ;
        if ( !is_legal ) return 0.0 ;
        double v = bin -> cal ( bin->cal_name , v1 , v2 , is_legal );
        if ( !is_legal ) return 0.0 ;
        return v ;
    }
    else if(len==3)
    {
        Ternary_Operator* ter = dynamic_cast < Ternary_Operator* > ( N ) ;
        double v1 = com ( N -> next[0] , is_legal ) ;
        if ( !is_legal ) return 0.0 ;
        double v2 = com ( N -> next[1] , is_legal ) ;
        if ( !is_legal ) return 0.0 ;
        double v3 = com ( N -> next[2] , is_legal ) ;
        if ( !is_legal ) return 0.0 ;
        double v = ter -> cal ( ter->cal_name , v1 , v2 , v3 , is_legal );
        return v ;
    }
    else
    {
        throw_error ( 8 ) ;
        is_legal = false ;
        return 0.0 ;
    }
}