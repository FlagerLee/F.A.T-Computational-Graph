#include <iostream>
#include <string>

void throw_error ( int v , std::string s )
{
    switch ( v )
    {
        case 0 : //一般这个错误是只要不乱搞就不会出现的。如果出现了，那就代表我也不知道哪里出了问题。
        {
            std::cout << "ERROR: Unknown type error\n" ;
            break ;
        }
        case 1 :
        {
            std::cout << "ERROR: Division by zero\n" ;
            break ;
        }
        case 2 :
        {
            std::cout << "ERROR: Placeholder missing\n" ;
            break ;
        }
        case 3 :
        {
            std::cout << "ERROR: No matching operator for '" << s << "'\n" ;
            break ;
        }
        case 4 :
        {
            std::cout << "ERROR: LOG operator's input must be positive\n" ;
            break ;
        }
        case 5 :
        {
            std::cout << "ERROR: No matching operators\n" ;
            break ;
        }
        case 6 :
        {
            std::cout << "ERROR: Cannot evaluate a non-Placeholder or a non-Var type node\n" ;
            break ;
        }
        case 7 :
        {
            std::cout << "ERROR: Cannot find node called '" << s << "'\n" ;
            break ;
        }
        case 8 :
        {
            std::cout << "ERROR: Cannot compute. Please check if you have added new operators. " ;
            break ;
        }
        case 9 :
        {
            std::cout << "ERROR: Unknown operator type\n" ;
            break ;
        }
        case 10 :
        {
            std::cout << "ERROR: illegal expression\n" ;
            break ;
        }
        case 11 :
        {
            std::cout << "ERROR: Non-existent node '" << s << "'\n" ;
            break ;
        }
        case 12 :
        {
            std::cout << "ERROR: Type '" << s << "' does not have value\n" ;
            break ;
        }
        case 13 :
        {
            std::cout << "ERROR: Cannot use 'SETCONSTANT' to a non-Var_Constant node\n" ;
            break ;
        }
        case 14 :
        {
            std::cout << "ERROR: Cannot evaluate a non-Placeholder node\n" ;
            break ;
        }
        case 15 :
        {
            std::cout << "ERROR: Unknown node type\n" ;
            break ;
        }
        case 16 :
        {
            std::cout << "ERROR: Please enter the number of Placeholders\n" ;
            break ;
        }
        case 17 :
        {
            std::cout << "ERROR: OUT OF RANGE!\n" ;
            break ;
        }
        case 19 :
        {
            std::cout << "ERROR: Node redefined\n" ;
            break ;
        }
        default :
        {
            std::cout << "Unknown type error! Please check if you give function 'throw_error' correct parameters\n" ;
            break ;
        }
    }
}