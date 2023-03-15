void MoreDijkstraTests(){
	cout << "Deep Testing Dijkstra Algorithm..." << endl;

	// Test 2: same graph from assignment, different query
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
	
	
	//cout << g->ToString() << endl;
	
	
	// test 2, start from b, go to f
	int ans = dijkstra(b, f, g);
	//cout << "answer: " << ans << endl;
	assert(ans == 12);

	delete g;


	// Test 3, different graph
	g = new Graph();

	a = g->AddNode('0');
	b = g->AddNode('1');
	c = g->AddNode('2');
	d = g->AddNode('3');
	e = g->AddNode('4');
	f = g->AddNode('5');
	GraphNode nodeG = g->AddNode('6');
	GraphNode h = g->AddNode('7');
	GraphNode i = g->AddNode('8');

	g->AddEdge(a, b, 4);
	g->AddEdge(b, a, 4);
	g->AddEdge(a, h, 8);
	g->AddEdge(h, a, 8);

	g->AddEdge(b, h, 11);
	g->AddEdge(h, b, 11);
	g->AddEdge(b, c, 8);
	g->AddEdge(c, b, 8);

	g->AddEdge(c, d, 7);
	g->AddEdge(d, c, 7);
	g->AddEdge(c, f, 4);
	g->AddEdge(f, c, 4);
	g->AddEdge(c, i, 2);
	g->AddEdge(i, c, 2);

	g->AddEdge(d, f, 14);
	g->AddEdge(f, d, 14);
	g->AddEdge(d, e, 9);
	g->AddEdge(e, d, 9);

	g->AddEdge(e, f, 10);
	g->AddEdge(f, e, 10);

	g->AddEdge(f, nodeG, 2);
	g->AddEdge(nodeG, f, 2);

	g->AddEdge(nodeG, i, 6);
	g->AddEdge(i, nodeG, 6);
	g->AddEdge(nodeG, h, 1);
	g->AddEdge(h, nodeG, 1);

	g->AddEdge(h, i, 7);
	g->AddEdge(i, h, 7);


	// test 3a
	ans = dijkstra(a, e, g);
	assert(ans == 21);


	// test 3b
	ans = dijkstra(e, a, g);
	assert(ans == 21);

	// test 3c
	ans = dijkstra(a, i, g);
	assert(ans == 14);

	// test 3d
	ans = dijkstra(nodeG, h, g);
	assert(ans == 1);

	// test 3e
	ans = dijkstra(d, d, g);
	assert(ans == 0);

	// test 3f
	ans = dijkstra(d, h, g);
	assert(ans == 14);

	delete g;


	// Test 4, destination node is a valid node object, but
	// it is not present in the graph g
	g = new Graph();

	a = g->AddNode('a');
	// b is not in the graph
	ans = dijkstra(a, b, g);
	assert(ans == INT_MAX);
	//check if the queue is empty while loop should stop when the queue is empty


	delete g;
	

	cout << "ALL TESTS PASSED!" << endl;
}