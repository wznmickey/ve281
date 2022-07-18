#include<iostream>
#include<list>
#include<vector>
#include<climits>

#define INF INT_MAX

using namespace std;

class ShortestP2P {
public:
    ShortestP2P() {}

    /**
     * read the graph from a vector, the graph is connected and you don't need to consider negative edges.
     *
     * @param vertex_number: the number of vertices in the graph
     * @param edges: a vector representing the edges in the undirected graph,
     *               each element of it is a vector containing three integers,
     *               the first two integers are the two vertices of an edge,
     *               the third integer is the length of the edge
     */

    void setGraph(int vertex_number, vector<vector<int> *> *edges) {
        //TODO: implement this function
    }

    /**
     * input: two vertices A and B
     * @param A
     * @param B
     * @return a vector, which contains all the vertices in the shortest path (including A and B)
     */
    vector<int> *distance(unsigned int A, unsigned int B) {
        //TODO: implement this function
    };

private:
    // internal data and functions.

};
