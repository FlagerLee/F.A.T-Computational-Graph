#include "Node.h"
#include <string>

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
    return false ;
}