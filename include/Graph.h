#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
///Iranyitatlan graf
struct Vertex
{
    Vertex* first;
    Vertex* second;
    int data;
    Vertex(int d)
    :data(d){}
};
class Graph
{
    /*
    1.V csucsok halmaza
    2.E elek halmaza
    3.E-t V-beli elemekbol allo rendezetlen parok halmaza
    */
    public:
        Graph();
        ~Graph();

    private:
};

#endif // GRAPH_H
