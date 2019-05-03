#include "Node.h"
#include "CG_debug.h"
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

bool Compute ( std::string s )

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
            double v = una -> cal ( una -> cal_name , v0 , is_legal );
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
