#ifndef __COMPUTATIONALGRAPH_EVALUATION_H__
#define __COMPUTATIONALGRAPH_EVALUATION_H__

#include "Node.h"

double get_value ( Node* N ) ;
bool eval ( double v , Node* N ) ;

double compute ( Node* N , bool& is_legal ) ;

#endif
