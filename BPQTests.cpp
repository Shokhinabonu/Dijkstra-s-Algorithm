

#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <cassert>

using namespace std;

void ContainsTest()
{
	cout << "Testing Contains Helper Method..." << endl;
	Graph g = Graph();
	BetterPriorityQueue q;
	GraphNode a = g.AddNode(1);
	g.AddNode(2);
	g.AddNode(3);
	g.AddNode(4);
	g.AddNode(5);
	g.AddNode(6);
	vector<GraphNode *> nodes = g.GetNodes();
	for (size_t i = 0; i < nodes.size(); i++)
	{
		DNode cur;
		cur.node = nodes.at(i);
		// cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node-> key << endl;
		q.push(cur);
		// cout << "size: " << q.size() << endl;
	}
	// 1st test
	DNode positive;
	positive.node = &a;
	assert(q.Contains(positive) == true);
	// 2nd test
	DNode negative;
	assert(q.Contains(negative) == false);
	// 3rd test
	assert(q.Contains(positive) == true);
	cout << "PASSED!" << endl;
}

void UpdateTest()
{
	cout << "Testing Update Helper Method..." << endl;
	Graph g = Graph();
	BetterPriorityQueue q;
	g.AddNode(1);
	g.AddNode(2);
	g.AddNode(3);
	g.AddNode(4);
	GraphNode five = g.AddNode(5);
	GraphNode six = g.AddNode(6);
	const vector<GraphNode *> nodes = g.GetNodes();
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
		DNode cur;
		cur.pri = i;
		cur.node = nodes.at(i);
		// cout << "inserting cur.pri: " << cur.pri << "  node: " << cur.node->key << endl;
		q.push(cur); 
	}

	// cout << "q before: " << queue_to_string(q) << endl;
	//  Test 1: update a node with pri 0 (normal case)
	DNode positive;
	positive.node = &six;
	positive.pri = 0;
	// cout << "q before: " << q.ToString() << endl; 
	assert(q.Update(positive) == true);
	// cout << "q after: " << q.ToString() << endl;
	string soln1 = "[(6, pri: 0), (1, pri: 0), (2, pri: 1), (3, pri: 2), (4, pri: 3), (5, pri: 4)]";
	string soln2 = "[(1, pri: 0), (2, pri: 1), (6, pri: 0), (4, pri: 3), (5, pri: 4), (3, pri: 2)]"; 

	 // Test 2: attempt to update with an empty / undefined input
	DNode negative;
	assert(q.Update(negative) == false);
	// cout << "q after after: " << q.ToString() << endl;
	assert(q.ToString() == soln1 || q.ToString() == soln2);

	 // Test 3: update a node with a larger priority
	  // It must behave this way (ignoring larger priorities)
	  // for compatibility with Dijkstra's algorithm
	DNode negative2;
	negative2.node = &five;
	negative2.pri = 80;
	assert(q.Update(negative2) == false);
	// cout << "q after after after: " << q.ToString() << endl;

	// WRONG: "[(a: 0), (b: 1), (f: 0), (d: 3), (e: 80), (c: 2)]";
	// some students might have a slightly different order
	// please ensure the output is a valid priorityqueue as
	// implemented by a binary heap
	
	// assert(q.ToString() == soln1 || q.ToString() == soln2);
	cout << "PASSED!" << endl;
}

int main()
{

	ContainsTest();
	UpdateTest();

	cout << "ALL TESTS PASSED!!" << endl;

	return 0;
}
