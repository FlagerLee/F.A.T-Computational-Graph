#ifndef __COMPUTATIONALGRAPH_DEBUG_H__
#define __COMPUTATIONALGRAPH_DEBUG_H__

#include <string>

void throw_error ( int v , std::string s = "" ) ;

/* throw_error : 抛出错误
 * 1. division by 0
 * 2. placeholder missing
 * 3. No matching operators for s 
 * 4. LOG's input must be positive
 * 5. Cannot evaluate in an expression
 * 6. Cannot evaluate a non-Placeholder or a non-Var type node
 * 7. Cannot evaluate a var by itself
 * 8. Cannot compute
 * 9. leaf node must be placeholder/constant/var_constant
*/

#endif
