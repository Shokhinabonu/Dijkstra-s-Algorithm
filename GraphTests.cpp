#include "Graph.h"
#include <iostream>
#include <cassert>

using namespace std;

void TestAddNode()
{
	cout << "Testing AddNode..." << endl;
	Graph g = Graph();
	GraphNode gn1 = g.AddNode(15);

	assert(gn1.key == 15);
	assert(g.NodesToString() == "[(15)]");
	assert(g.ToString() == "15 | \n");

	g.AddNode(12);

	assert(g.NodesToString() == "[(15), (12)]");
	assert(g.ToString() == "15 | \n12 | \n");

	g.AddNode(9);
	assert(g.NodesToString() == "[(15), (12), (9)]");
	assert(g.ToString() == "15 | \n12 | \n9 | \n");

	try
	{
		g.AddNode(12);
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}

	try
	{
		g.AddNode(12);
		g.AddNode(15);
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}
	cout << "PASSED!" << endl
		 << endl;
}

void TestAddEdge()
{
	cout << "Testing AddEdge..." << endl;
	Graph g = Graph();
	GraphNode gn1 = g.AddNode(15);

	assert(g.NodesToString() == "[(15)]");
	assert(g.ToString() == "15 | \n");

	GraphNode gn2 = g.AddNode(12);

	assert(g.NodesToString() == "[(15), (12)]");
	assert(g.ToString() == "15 | \n12 | \n");

	GraphNode gn3 = g.AddNode(9);
	assert(g.NodesToString() == "[(15), (12), (9)]");
	assert(g.ToString() == "15 | \n12 | \n9 | \n");

	g.AddEdge(gn1, gn3, 2);
	assert(g.NodesToString() == "[(15), (12), (9)]");
	assert(g.ToString() == "15 | [(15)->(9) w:2]\n12 | \n9 | \n");

	g.AddEdge(gn3, gn2);
	g.AddEdge(gn1, gn2, 8);

	assert(g.NodesToString() == "[(15), (12), (9)]");
	assert(g.ToString() == "15 | [(15)->(9) w:2], [(15)->(12) w:8]\n12 | \n9 | [(9)->(12) w:0]\n");

	cout << "PASSED!" << endl
		 << endl;
}

void TestDestructor()
{
	cout << "Testing Destructor..." << endl;
	Graph *g = new Graph();

	GraphNode three = g->AddNode(3);
	GraphNode five = g->AddNode(5);
	g->AddEdge(three, five, 15);

	delete g;

	Graph g2 = Graph();
	GraphNode twelve = g2.AddNode(12);
	g2.AddNode(11);
	assert(twelve.key == 12);

	cout << "NO ERRORS.  Use valgrind to check!" << endl
		 << endl;
}

void TestGetEdges()
{
	cout << "Testing GetEdges..." << endl;
	Graph g = Graph();
	GraphNode gn1 = g.AddNode(15);
	GraphNode gn2 = g.AddNode(12);
	GraphNode gn3 = g.AddNode(9);

	g.AddEdge(gn1, gn3, 2);
	g.AddEdge(gn3, gn2);
	g.AddEdge(gn1, gn2, 8);

	const vector<GraphEdge *> edges = g.GetEdgesFrom(gn1);

	string st = g.GraphEdgeToString(*edges.at(0));
	assert(st == "[(15)->(9) w:2]");

	string st1 = g.GraphEdgeToString(*edges.at(0));
	assert(st1 == "[(15)->(9) w:2]");
	cout << "PASSED" << endl;
}

void TestNodeAt()
{
	cout << "Testing NodeAt..." << endl;

	Graph g = Graph();
	g.AddNode(15);
	GraphNode gn2 = g.AddNode(12);
	g.AddNode(9);
	GraphNode result = g.GetNode(12);
	assert(result.key == gn2.key);

	try
	{
		GraphNode ans = g.GetNode(1);
		cout << "Node with key 1 should not exist, but your graph returned: " << Graph::GraphNodeToString(ans) << endl;
		assert(false);
	}
	catch (const invalid_argument &e)
	{
	}

	result = g.GetNode(12);
	assert(result.key == 12);

	cout << "PASSED!" << endl
		 << endl;
}

void TestGraphNodeToString()
{
	cout << "Testing GraphNodeToString..." << endl;

	Graph g = Graph();
	GraphNode gn1 = g.AddNode(12);
	GraphNode gn2 = g.AddNode(33);
	GraphNode gn3 = g.AddNode(1);

	assert(g.GraphNodeToString(gn1) == "12");
	assert(g.GraphNodeToString(gn2) == "33");
	assert(g.GraphNodeToString(gn3) == "1");

	cout << "PASSED!" << endl
		 << endl;
}

void TestGraphEdgeToString()
{
	cout << "Testing GraphEdgeToString..." << endl;

	Graph g = Graph();
	GraphNode gn1 = g.AddNode(12);
	GraphNode gn2 = g.AddNode(33);
	GraphEdge ge = g.AddEdge(gn1, gn2, 8);

	assert(g.GraphEdgeToString(ge) == "[(12)->(33) w:8]");

	cout << "PASSED!" << endl
		 << endl;
}

void TestGetNodes()
{
	cout << "Testing GetNodes..." << endl;

	Graph g = Graph();
	g.AddNode(15);
	g.AddNode(12);
	g.AddNode(9);

	const vector<GraphNode *> nodes = g.GetNodes();

	GraphNode ans = *nodes.at(0);
	string st = g.GraphNodeToString(ans);
	assert(st == "15");

	GraphNode ans1 = *nodes.at(1);
	string st1 = g.GraphNodeToString(ans1);
	assert(st1 == "12");

	GraphNode ans2 = *nodes.at(2);
	string st2 = g.GraphNodeToString(ans2);
	assert(st2 == "9");

	cout << "PASSED!" << endl
		 << endl;
}

void TestIsPresent()
{
	cout << "Testing IsPresent..." << endl;

	Graph g = Graph();
	GraphNode gn1 = g.AddNode(15);
	GraphNode gn2 = g.AddNode(12);
	GraphNode gn3 = g.AddNode(9);
	GraphNode gn4;
	gn4.key = 99;
	assert(g.IsPresent(gn1) == true);
	assert(g.IsPresent(gn2) == true);
	assert(g.IsPresent(gn3) == true);
	assert(g.IsPresent(gn4) == false);

	assert(g.IsPresent(gn1.key) == true);
	assert(g.IsPresent(gn2.key) == true);
	assert(g.IsPresent(gn4.key) == false);
	cout << "PASSED!" << endl
		 << endl;
}

int main()
{

	TestAddNode();
	TestAddEdge();
	TestDestructor();
	TestGetEdges();
	TestNodeAt();
	TestGraphNodeToString();
	TestGraphEdgeToString();
	TestGetNodes();
	TestIsPresent();

	cout
		<< "ALL TESTS PASSED!" << endl;
	return 0;
}
