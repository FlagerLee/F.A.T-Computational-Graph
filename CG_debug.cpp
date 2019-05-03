#include <iostream>
#include <string>

void throw_error ( int v , std::string s = "" )
{
    switch ( v )
    {
        case 1 :
        {
            std::cout << "Error: Division by zero\n" ;
            break ;
        }
        case 2 :
        {
            std::cout << "Error: Placeholder missing\n" ;
            break ;
        }
        case 3 :
        {
            std::cout << "Error: No matching operator for '" << s << "'\n" ;
            break ;
        }
        case 4 :
        {
            std::cout << "Error: LOG operator's input must be positive\n" ;
            break ;
        }
        case 5 :
        {
            std::cout << "Error: Cannot evaluate in an expression\n" ;
            break ;
        }
        case 6 :
        {
            std::cout << "Error: Cannot evaluate a non-Placeholder or a non-Var type node\n" ;
            break ;
        }
        case 7 :
        {
            std::cout << "Error: Cannot define a variate by itself\n"
            break ;
        }
        case 8 :
        {
            std::cout << "Error: Cannot compute. Please check if you have added new operators. "
            break ;
        }
        case 9 :
        {
            std::cout << "Error: Unknown operator type\n" ;
            break ;
        }
        default :
        {
            std::cout << "Unknown type error! Please check if you give function 'throw_error' correct parameters\n" ;
            break ;
        }
    }
}
