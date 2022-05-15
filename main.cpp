#include <iostream>
#include <vector>
#include <algorithm>

const int V = 7;

void findCutVerticesWithDfs(std::vector<int> adj[], int u, bool visited[],
	int disc_time[], int low_value[], int& time, int parent,
	bool is_cut_vertice[])
{
	// to find chidren in DFS
	int children = 0;

	// Make current node as visited.
	visited[u] = true;

	//initialize discover time and low value.
	disc_time[u] = low_value[u] = ++time;

	// Go through all vertices adjacent to this
	for (auto v : adj[u]) {
		if (!visited[v]) {
			children++;
			findCutVerticesWithDfs(adj, v, visited, disc_time, low_value, time, u, is_cut_vertice);

			low_value[u] = std::min(low_value[u], low_value[v]);

			if (parent != -1 && low_value[v] >= disc_time[u])
				is_cut_vertice[u] = true;
		}

		// Update low value of u if it forms a back trace.
		else if (v != parent)
			low_value[u] = std::min(low_value[u], disc_time[v]);
	}

	// If u is root of DFS tree and has two or more children.
	if (parent == -1 && children > 1)
		is_cut_vertice[u] = true;
}

//add an edge
void addEdge(std::vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

int main()
{
	while (true)
	{
		std::cout << "The graph supports " << V << " Vertices, to change it please change V = " << V << " in the source code and compile\n";
		std::vector<int> adjacent[V];
		std::cout << "Enter Number of edges present in the graph\n";
		int number_of_edges;
		std::cin >> number_of_edges;
		std::cout << "Enter the edges ex: 0 2\n";
		int u, v;
		for (int i = 0; i < number_of_edges; i++)
		{
			std::cin >> u;
			std::cin >> v;
			addEdge(adjacent, u, v);
		}

		int discovery_time[V] = { 0 };
		int low_value[V];
		bool visited[V] = { false };
		bool is_cut_vertice[V] = { false };
		int time = 0, parent = -1;

		findCutVerticesWithDfs(adjacent, 0, visited, discovery_time, low_value,
			time, parent, is_cut_vertice);

		std::cout << "Cut vertices in the graph are \n";
		// Printing the cut vertices
		bool cut_vertices_present = false;
		for (int u = 0; u < V; u++)
		{
			if (is_cut_vertice[u] == true)
			{
				cut_vertices_present = true;
				std::cout << u << " ";
			}
		}

		if (cut_vertices_present == false)
			std::cout << "No Cut Vertices Present Hurray!!\n";

		char next;
		std::cout << "\n\n..............................................................................\n\n";
		std::cout << "Press q to quit or any other key to repeat\n";
		std::cin >> next;

		if (next == 'q')
			break;
		else
			continue;
	}

	return 0;
}
