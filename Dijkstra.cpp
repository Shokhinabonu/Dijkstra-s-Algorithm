
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <iostream>
#include <climits>
#include <cassert>

#define INF (unsigned)!((int)0)

using namespace std;

// this is dijkstra's shortest path algorithm
// TIME COMPLEXITY: it seems that the time complexity is O(n^2)
// sincr there seem to be loops within the main loop.
int dijkstra(const GraphNode start, const GraphNode end, const Graph *g)
{
	BetterPriorityQueue q;
	Graph graphD = *g;

	// this stores all the given nodes
	vector<GraphNode *> nodes = graphD.GetNodes(); // Graph--->O(n)
	bool isEnd = false;

	// populate the queue with the DNodes with INT_MAX pri
	for (size_t i = 0; i < nodes.size(); i++) // O(n)
	{
		DNode cur;
		cur.node = nodes.at(i);
		cur.pri = INT_MAX;
		q.push(cur);
	}

	// updates the start value's pri with zero
	DNode startD;
	GraphNode gn = start;
	startD.node = &gn;
	startD.pri = 0;
	q.Update(startD); // BPQ--->O(n)

	// loop through the given list of nodes
	while (!isEnd) // O(n)
	{
		DNode cur;
		cur = q.top();
		int curPri = cur.pri;

		if (cur.node->key == end.key)
		{
			cout << "DNODE " << q.DnodeToString(q.top()) << endl;
			isEnd = true;
			return curPri;
		}
		// loop through the given list of edges
		vector<GraphEdge *> edges = graphD.GetEdgesFrom(*cur.node);
		for (GraphEdge *ed : edges) // O(n)
		{
			DNode currEdge;
			currEdge.node = ed->to;
			currEdge.pri = ed->weight + curPri;
			q.Update(currEdge);
		}
		cout << "DNODE " << q.DnodeToString(q.top()) << endl;
		q.pop();
	}

	return 0;
}

int DijkstraTest()
{
	cout << "Testing Dijkstra Algorithm..." << endl;

	// Test 1: graph from assignment
	Graph *g = new Graph();

	GraphNode a = g->AddNode(1);
	GraphNode b = g->AddNode(2);
	GraphNode c = g->AddNode(3);
	GraphNode d = g->AddNode(4);
	GraphNode e = g->AddNode(5);
	GraphNode f = g->AddNode(6);

	g->AddEdge(a, b, 7);
	g->AddEdge(b, a, 7);
	g->AddEdge(a, c, 9);
	g->AddEdge(c, a, 9);
	g->AddEdge(a, f, 14);
	g->AddEdge(f, a, 14);

	g->AddEdge(b, c, 10);
	g->AddEdge(c, b, 10);
	g->AddEdge(b, d, 15);
	g->AddEdge(d, b, 15);

	g->AddEdge(c, f, 2);
	g->AddEdge(f, c, 2);
	g->AddEdge(c, d, 11);
	g->AddEdge(d, c, 11);

	g->AddEdge(f, e, 9);
	g->AddEdge(e, f, 9);

	g->AddEdge(d, e, 6);
	g->AddEdge(e, d, 6);

	cout << g->ToString() << endl;

	int ans = dijkstra(g->GetNode(1), g->GetNode(5), g);
	assert(ans == 20);

	delete g;

	// Test 2
	g = new Graph();

	a = g->AddNode(1);
	b = g->AddNode(2);
	c = g->AddNode(3);
	d = g->AddNode(4);
	e = g->AddNode(5);
	f = g->AddNode(6);

	g->AddEdge(a, b, 3);
	g->AddEdge(b, a, 3);
	g->AddEdge(a, c, 2);
	g->AddEdge(c, a, 2);
	g->AddEdge(a, f, 15);
	g->AddEdge(f, a, 15);

	g->AddEdge(b, c, 4);
	g->AddEdge(c, b, 4);
	g->AddEdge(b, d, 6);
	g->AddEdge(d, b, 6);

	g->AddEdge(c, f, 9);
	g->AddEdge(f, c, 9);
	g->AddEdge(c, d, 13);
	g->AddEdge(d, c, 13);

	g->AddEdge(f, e, 1);
	g->AddEdge(e, f, 1);

	g->AddEdge(d, e, 20);
	g->AddEdge(e, d, 20);

	cout << g->ToString() << endl;

	int ans2 = dijkstra(g->GetNode(1), g->GetNode(5), g);
	assert(ans2 == 12);

	delete g;

	cout << "Testing Dijkstra Algorithm" << endl;
	return ans2;
}

int main()
{

	int ans = DijkstraTest();
	cout << "ans: " << ans << endl;
	assert(ans == 12);

	return 0;
}
