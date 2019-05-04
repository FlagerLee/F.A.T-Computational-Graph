main: main.cpp Node.cpp build_tree.cpp evaluation.cpp CG_debug.cpp
	g++ -O2 -o main -std=c++14 main.cpp Node.cpp build_tree.cpp evaluation.cpp CG_debug.cpp