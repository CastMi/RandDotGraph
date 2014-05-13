RandDotGraph
============

RandDotGraph is a program to generate random graphs in the graph description
language DOT.

Brief introduction
--------------

The goal of this program is not only to give the possibility to create a graph
easily, but also to release highly reusable code and therefore to keep an eye on
security, ease of debug and ease of use.
I am working on this during my spare time. If you find this code useful or if
you want to give me any suggestion or whatever, feel free to contact me: It
will encourage me. Please, let me know when you find any problems.

----------------------
Features
----------------------

Support for:

        Directed graph
        Undirected graph
        Graph without self loop

Command Line Arguments
--------------

Example:  ./RandDotGraph -v VerticesNumber [-t Type] [-e EdgesNumber]

VerticesNumber
        (required) Specifies the number of vertices for the graph that we are
                   going to create.

Type
        (optional) Specifies the type of the edges for the graph.
                   It can be directed or undirected.

EdgesNumber
        (optional) Specifies the number of edges for the graph that we are going
                   to create.
                   If EdgesNumber is missed, 0 is used.

Output
--------------

The output will be in the file named RandomGraph.txt.

Argument Checking
--------------

Since a graph with no vertices is still part of the language, a number of
vertices equal to zero is still allowable.
Therefore the following checks are performed:

- EdgesNumber >= 0
- VerticesNumber >= 0
- Check whether the parameters are correct with respect to the type of the graph

Debug
--------------

If you want to edit/expand/improve this code, there are already some useful
assert to help in the debugging phase.
This is the gcc command line argument to active them:

        gcc RandDotGraph.c -DDEBUG=1
