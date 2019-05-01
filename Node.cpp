#include <string>

#include <cmath>
#include <iostream>
#include <cstdio>
#include "Node.h"

using namespace std ;


//Node类

void Node::add_next ( Node* N ) { Node::next.push_back ( N ) ; }
void Node::del ()
{
    int len = next.size () ;
    for ( int i = 0 ; i < len ; i ++ ) delete next [ i ] ;
    vector < Node* > ().swap ( next ) ;
}
std::string Node::get_name () { return "Node" ; }
std::string Var::get_name () { return "Var" ; }
std::string Placeholder::get_name () { return "Placeholder" ; }
std::string Var_Constant::get_name () { return "Var_Constant" ; }
std::string Constant::get_name () { return "Constant" ; }
std::string Calculator::get_name () { return "Calculator" ; }
std::string Unary_Operator::get_name () { return "Unary_Operator" ; }
std::string Binary_Operator::get_name () { return "Binary_Operator" ; }
std::string Ternary_Operator::get_name () { return "Ternary_Operator" ; }

//#end#

//Calculator类

template <typename _Tp_>
double Calculator::get_value ( _Tp_ T )
{
    if ( T.name == "var" || T.name == "placeholder" || T.name == "constant" || T.name == "var_constant" ) return T.value ;
    else std::cout << "Error: " << T.name << "does not have value\n" ;
}

template <typename _Tp_>
void Calculator::eval ( double v , _Tp_ T )
{
    if ( T.name == "var" || T.name == "placeholder" || T.name == "var_constant" ) T.value = v ;
    else std::cout << "Error: You cannot evaluate a " << T.name << "\n" ;
}

double Unary_Operator::cal ( string s , double v , bool& is_legal )
{
    if ( s == "SIN" ) return sin ( v ) ;
    else if ( s == "EXP" ) return exp ( v ) ;
    else if ( s == "TANH" ) return ( exp ( v ) - exp ( -v ) ) / ( exp ( v ) + exp ( -v ) ) ;
    else if ( s == "SIGMOID" ) return 1.0 / ( 1.0 + exp ( -v ) ) ;
    else if ( s == "LOG" )
    {
        if ( v > 0 ) return log ( v ) ;
        else { is_legal = false ; cout << "Error: LOG operator's input must be positive\n" ; return 0.0 ; }
    }
    else if ( s == "PRINT" )
    {
        cout << "Print Operator: " << s << "=" << v << "\n" ;
        return v ;
    }
    return 0.0 ;
}

double Binary_Operator::cal ( string s , double v1 , double v2 , bool& is_legal )
{
    switch ( s [ 0 ] )
    {
        case '+' : return v1 + v2 ;
        case '-' : return v1 - v2 ;
        case '*' : return v1 * v2 ;
        case '/' :
        {
            if ( v2 == 0 )
            {
                is_legal = false ;
                cout << "ERROR: Division by zero\n" ;
                return 0.0 ;
            }
            else return v1 / v2 ;
        }
        case '<' :
        {
            if ( s.length() == 1 )
            {
                if ( v1 < v2 ) return 1.0 ;
                else return 0.0 ;
            }
            else if ( s [ 1 ] == '=' )
            {
                if ( v1 <= v2 ) return 1.0 ;
                else return 0.0 ;
            }
        }
        case '>' :
        {
            if ( s.length() == 1 )
            {
                if ( v1 > v2 ) return 1.0 ;
                else return 0.0 ;
            }
            else if ( s [ 1 ] == '-' )
            {
                if ( v1 >= v2 ) return 1.0 ;
                else return 0.0 ;
            }
        }
        case '=' :
        {
            if ( s.length() == 1 )
            {
                is_legal = false ;
                cout << "Error: Cannot evaluate in an expression\n" ;
                return 0.0 ;
            }
            else
            {
                if ( v1 == v2 ) return 1.0 ;
                else return 0.0 ;
            }
        }
        default :
        {
            is_legal = false ;
            cout << "Error: No matching operators for '" << s << "'\n" ;
            return 0.0 ;
        }
    }
    return 0.0 ;
}

double Ternary_Operator::cal ( string s , double v1 , double v2 , double v3 , bool& is_legal )
{
    if ( s == "COND" )
    {
        return v1 ? v2 : v3 ;
    }
    else
    {
        is_legal = false ;
        cout << " Error: No matching operators for '" << s << "'\n" ;
        return 0.0 ;
    }
    return 0.0 ;
}

//#end#
