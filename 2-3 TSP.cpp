#include <iostream>
#define MAX_INT 1e6
#define max(a, b)  ((a > b) ? a : b)
using namespace std;

int n, m, maxDepth = 0;

///*** Push vertex with 0 indegree ***///
int* stack;
int _size = 0;

void push(int const& e) { stack[_size++] = e; }
int pop() { return stack[--_size]; }

struct Vertex {
	int index;
	Vertex* succ = nullptr;
};

struct Graph {
	int inDegree, depth = 0;
	Vertex* first = nullptr;
};

Graph* g;

void topoSort() {
	for (int i = 0; i < n; i++) {
		if (!g[i].inDegree) push(i);
	}

	while(_size) {
		int v = pop();

		for (Vertex* p = g[v].first; p; p = p->succ) {
			
			// Update depth of current vertex
			g[p->index].depth = max((g[v].depth + 1), g[p->index].depth);
			
			// Update max depth of all
			maxDepth = max(maxDepth, g[p->index].depth);

			if (!(--g[p->index].inDegree)) push(p->index);
		}
	}
}



int main() {
	scanf("%d%d", &n, &m);

	g = new Graph[n];
	stack = new int[n];
	
	int v, u;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &v, &u);
		v--; u--;
		
		Vertex* x = new Vertex;
		x->index = u;
		x->succ = g[v].first;
		g[v].first = x;
		g[u].inDegree++;
	}
	topoSort();
	delete[] g;
	delete[] stack;
	printf("%d", maxDepth + 1);
	return 0;
}
