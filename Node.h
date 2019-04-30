#ifndef ___COMPUTATIONALGRAPH__NODE_H___
#define ___COMPUTATIONALGRAPH__NODE_H___

/* 此处注释在开发完成后删掉
 * 在此段注释下方添加头文件
 * 由于由一个Node类派生出多个类型，故需要着重注意不同类之间的冲突问题
 * 注意切片！
 * 以及可以考虑在开发完成的时候加入自己的代号标识一下这一部分是由谁完成的
 * 同时也不至于违规被人认出来是谁开发的这一段程序
 * （好了我bb完了没事了
**/

#include <vector>
#include <string>

/* Base: class Node
 * 由于计算图基于树的数据结构，将结点作为基类
 * 变量、常数等所有可被视为节点的结构均基于Node类开发
 * Node类中只需完成树的结构，结点具体作用在继承类里完成
 * 要求：一个Node结点只需保存其后继结点。考虑到COND函数的存在，单个Node结点至少保存三个后继结点
 *      考虑到可扩展性，可以只实现固定的3个结点，剩余的结点以vector形式储存，方便新加入结点
**/

class Node
{
    private:
    std::vector < Node* > next ; //树的后继结点
    protected:
    void del () ; //派生类析构用：删除vector
    friend void build_tree ( std::string exp ) ;
    public:
    void add_next ( Node* N ) ;
    Node () {}
    ~Node () { del() ; }
} ;

/* Derive: class Placeholder
 * 占位符结点：由基类Node继承而来，表示占位符
**/ 

class Placeholder : public Node
{
    private:
    double value ;
    protected:
    public:
    bool is_Printed ;
    bool have_value ;
    const std::string name = "placeholder" ;
    Placeholder ( double v = 0.0 ) : value ( v ) { have_value = false ; is_Printed = false ; }
} ;

/* Derive: class Constant
 * 常数结点：由基类Node继承而来，表示不可改变的常数
**/

class Constant : public Node
{
    private:
    double value ;
    protected:
    public:
    const std::string name = "constant" ;
    Constant ( double v = 0.0 ) : value ( v ) {}
} ;

/* Derive: class Var
 * 变量结点
**/

class Var : public Node
{
    private:
    std::string var_name ; //变量名
    double value ; //当前数据下变量的值
    protected:
    friend void eval ( double v ) ;
    public:
    bool is_Printed ;
    bool have_value ;
    const std::string name = "var" ;
    Var ( std::string s , double v = 0.0 ) : var_name ( s ) , value ( v ) { have_value = false ; is_Printed = false ; }
} ;

/* Derive: class Var_Constant
 * 可变常数结点：由基类Node继承而来，表示可以改变数值的常数结点
**/

class Var_Constant : public Node
{
    private:
    double value ;
    protected:
    public:
    void set ( double v ) { value = v ; }
    const std::string name = "var_constant" ;
    Var_Constant ( double v ) : value ( v ) {}
} ;

/* Derive: class Caculator
 * 运算符结点：由基类Node继承而来，表示运算符，如加减乘除
**/

class Calculator : public Node
{
    private:
    friend class Placeholder ;
    friend class Constant ;
    friend class Var ;
    friend class Var_Constant ;
    protected:
    template <typename _Tp_> double get_value ( _Tp_ T ) ;
    template <typename _Tp_> void eval ( double v , _Tp_ T ) ;
    public:
    const std::string name = "calculator" ;
    Calculator () {}
} ;

/* Derive: Unary_operator
 * 单目运算符结点
**/

class Unary_Operator : public Calculator //单目运算符
{
    private:
    std::string cal_name ; //运算符名称
    protected:
    public:
    const std::string name = "unary_operator" ;
    Unary_Operator ( std::string s ) : cal_name ( s ) {}

    double cal ( std::string s , double v , bool& is_legal ) ;
} ;

class Binary_Operator : public Calculator //双目运算符
{
    private:
    std::string cal_name ;
    protected:
    public:
    const std::string name = "binary_operator" ;
    Binary_Operator ( std::string s ) : cal_name ( s ) {}

    double cal ( std::string s , double v1 , double v2 , bool& is_legal ) ;
} ;

class Ternary_Operator : public Calculator //三目运算符
{
    private:
    std::string cal_name ;
    protected:
    public:
    const std::string name = "ternary_operator" ;
    Ternary_Operator ( std::string s ) : cal_name ( s ) {}

    double cal ( std::string s , double v1 , double v2 , double v3 , bool& is_legal ) ;
} ;

#endif
