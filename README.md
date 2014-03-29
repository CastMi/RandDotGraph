RandDotGraph
============

RandDotGraph is a program to generate a random directed graph in the graph description language DOT.

Command Line Arguments
--------------

Example:  ./RandDotGraph VerticesNumber [EdgesNumber]

VerticesNumber
	(required) Specifies the number of vertices for the graph that we are going to create.

EdgesNumber
	(optional) Specifies the number of edges for the graph that we are going to create.
	If EdgesNumber is missed, 0 is used.

Output
--------------

The output will be in the file named RandomGraph.txt.

Compiling
--------------

To compile the program, simply do:

	gcc RandDotGraph.c -lm

Argument Checking
--------------

Since a graph with no vertices is still part of the language, a number of vertices equal to zero is still allowable.
Therefore the following checks are performed:

- EdgesNumber >= 0
- VerticesNumber >= 0
- VerticesNumber <= EdgesNumber<sup>2</sup>

Debug
--------------

If you want to edit/expand/improve this code, there are already some useful assert to help in debugging.
To use them:

	gcc -DDEBUG=1 RandDotGraph.c -lm
