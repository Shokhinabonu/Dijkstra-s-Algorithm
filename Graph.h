#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct GraphNode
{
	unsigned long long int key;
};

struct GraphEdge
{
	// These are pointers, so they could allow the user to change the edge's to and from
	// directly in main().  This could create invalid or incoherent graphs.  So
	// we use "const" keyword to prevent user from doing this.
	const GraphNode *from;
	const GraphNode *to;
	unsigned int weight;
};

class Graph
{

public:
	Graph();
	Graph(const Graph &a); // we need a parameter
	~Graph();

	GraphNode AddNode(unsigned long long int key = 0);
	GraphEdge AddEdge(GraphNode gn1, GraphNode gn2, unsigned int weight = 0);

	string ToString() const;	  // entire graph
	string NodesToString() const; // all nodes
								  // not used in this program, so it's not necessary to implement
								  // string EdgesToString() const; // all edges

	// // Use the following two methods to implement ToString() and NodesToString()
	static string GraphNodeToString(GraphNode gn);
	static string GraphEdgeToString(GraphEdge ge);

	const vector<GraphEdge *> GetEdgesFrom(GraphNode gn) const;
	const vector<GraphNode *> GetNodes() const;

	bool IsPresent(GraphNode gn) const;
	bool IsPresent(unsigned long long int key) const;
	GraphNode GetNode(unsigned long long int key) const;

	size_t Size() const;  // num edges
	size_t Order() const; // num nodes

private:
	vector<vector<GraphEdge>> adjMatrix;
	vector<GraphNode> nodesOrdered; 
	bool isVecEmpty(vector<GraphEdge> ge);
	int numOfValidEdges(int idx) const;
	int nodeExists(unsigned long long int key) const;
};

#endif
