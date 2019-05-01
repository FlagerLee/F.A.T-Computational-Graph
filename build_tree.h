#ifndef __COMPUTATIONALGRAPH_BUILD_TREE_H__
#define __COMPUTATIONALGRAPH_BUILD_TREE_H__

#include <string>
#include <map>
#include <vector>
#include "Node.h"

inline int priority ( std::string c ) ;

Node* create_calculator ( std::string s , int& count_arg ) ;

void init ( Node* N ) ;

void delete_tree ( Node* N ) ;

Var* build_tree( std::string s, std::map < std::string , Node* > Var_map ) ;

Node* connect ( std::vector<std::string> s , std::map<std::string , Node*> Var_map , int head , int tail ) ;

#endif
