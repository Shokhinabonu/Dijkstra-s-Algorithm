#include "Graph.h"
#include <iostream>
#include <string>

// Tim helped me to realize that storing GraphEdges instead of int in my vector of vectors
// would be more optimal. Then I discovered that it would be hard to update an element at a partic index of the vector
// so he suggested to store the index and the node in something-> I decided to use a hashMap since I have expereince
// using it for the last homework
Graph::Graph()
{
}

Graph::~Graph()
{
}

Graph::Graph(const Graph &a)
{
    adjMatrix = a.adjMatrix;
    nodesOrdered = a.nodesOrdered;
}

GraphNode Graph::AddNode(unsigned long long int key)
{
    if (IsPresent(key))
    {
        throw invalid_argument("Caught an exception");
    }

    // creates a new GraphNode and ads it to the nodesOrdered vector
    // and push back an empty vector to the matrix
    GraphNode gn = GraphNode();
    gn.key = key;

    vector<GraphEdge> vec;
    adjMatrix.push_back(vec);
    nodesOrdered.push_back(gn);

    return gn;
}

GraphEdge Graph::AddEdge(GraphNode gn1, GraphNode gn2, unsigned int weight)
{

    if (!IsPresent(gn1) || !IsPresent(gn2))
    {
        throw invalid_argument("Caught an exception");
    }

    int indx1 = nodeExists(gn1.key);
    int indx2 = nodeExists(gn2.key);
    size_t size = adjMatrix.at(indx1).size();

    // declares null GraphEdge
    GraphEdge geNull;
    geNull.from = NULL;
    geNull.to = NULL;
    geNull.weight = 0;

    // creates a new GraphEdge with the given GraphNodes and weight
    GraphEdge ge;
    ge.from = &nodesOrdered.at(indx1);
    ge.to = &nodesOrdered.at(indx2);
    ge.weight = weight;

    // fills up the vector with null pointers and adds the new GraphEdge at a correct location
    if (size < gn2.key)
    {
        for (long long unsigned int i = 1; i < (gn2.key - size); i++)
        {
            adjMatrix.at(indx1).push_back(geNull);
        }

        adjMatrix.at(indx1).push_back(ge);
    }
    else
    {
        adjMatrix.at(indx1).at(indx2) = ge;
    }

    return ge;
}

string Graph::GraphNodeToString(GraphNode gn)
{
    string st = to_string(gn.key);
    return st;
}

string Graph::GraphEdgeToString(GraphEdge ge)
{
    string st = "[(" + GraphNodeToString(*ge.from) + ")->(" + GraphNodeToString(*ge.to) + ") w:" + to_string(ge.weight) + "]";
    return st;
}

int Graph::numOfValidEdges(int idx) const
{
    GraphEdge ge;
    int num = 0;

    for (size_t j = 0; j < adjMatrix.at(idx).size(); j++)
    {
        ge = adjMatrix.at(idx).at(j);

        if (ge.from != NULL)
        {
            num++;
        }
    }

    return num;
}

string Graph::ToString() const
{
    GraphEdge ge;
    int num = 0;
    string st = "";

    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        st += to_string(nodesOrdered.at(i).key) + " | ";
        if (adjMatrix.at(i).size() > 0)
        {
            num = numOfValidEdges(i);
            for (size_t j = 0; j < adjMatrix.at(i).size(); j++)
            {
                ge = adjMatrix.at(i).at(j);

                if (ge.from != NULL)
                {
                    st += GraphEdgeToString(ge);
                    if (num != 1)
                    {
                        st += ", ";
                    }
                    num--;
                }
            }
        }

        st += "\n";
    }
    return st;
}

string Graph::NodesToString() const
{
    string st = "";
    st += "[";
    for (size_t i = 0; i < nodesOrdered.size(); i++)
    {
        if (i == nodesOrdered.size() - 1)
        {
            st += "(" + to_string(nodesOrdered.at(i).key) + ")";
        }
        else
        {
            st += "(" + to_string(nodesOrdered.at(i).key) + "), ";
        }
    }
    st += "]";

    return st;
}

const vector<GraphEdge *> Graph::GetEdgesFrom(GraphNode gn) const
{
    vector<GraphEdge *> vecGePoint;
    int i = nodeExists(gn.key);

    for (size_t j = 0; j < adjMatrix.at(i).size(); j++)
    {
        if (adjMatrix.at(i).at(j).from != NULL)
        {
            const GraphEdge *gnn = &adjMatrix.at(i).at(j);
            GraphEdge *gn = const_cast<GraphEdge *>(gnn);
            vecGePoint.push_back(gn);
        }
    }
    return vecGePoint;
}

const vector<GraphNode *> Graph::GetNodes() const
{
    vector<GraphNode *> list;
    for (size_t i = 0; i < nodesOrdered.size(); i++)
    {
        const GraphNode *gnn = &nodesOrdered.at(i);
        GraphNode *gn = const_cast<GraphNode *>(gnn);
        list.push_back(gn);
    }
    return list;
}

int Graph::nodeExists(unsigned long long int key) const
{
    for (size_t i = 0; i < nodesOrdered.size(); i++)
    {
        if (nodesOrdered.at(i).key == key)
        {
            return i;
        }
    }
    return -1;
}

bool Graph::IsPresent(GraphNode gn) const
{
    if (nodeExists(gn.key) != -1)
    {
        return true;
    }

    return false;
}

bool Graph::IsPresent(unsigned long long int key) const
{

    if (nodeExists(key) != -1)
    {
        return true;
    }

    return false;
}

GraphNode Graph::GetNode(unsigned long long int key) const
{
    GraphNode gn;
    gn.key = 0;
    for (GraphNode gn : nodesOrdered)
    {
        if (gn.key == key)
        {
            return gn;
        }
    }
    throw invalid_argument("Caught an exception");
    return gn;
}

size_t Graph::Size() const
{
    size_t size = 0;
    GraphEdge ge;
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        if (adjMatrix.at(i).size() > 0)
        {
            for (size_t j = 0; j < adjMatrix.at(i).size(); j++)
            {
                ge = adjMatrix.at(i).at(j);
                if (ge.from != NULL)
                {
                    size++;
                }
            }
        }
    }
    return size;
}
size_t Graph::Order() const
{
    size_t i = adjMatrix.size();
    return i;
}
