#include <cstdio>

#define MAX_INT 10001
#define ListNodePosi ListNode*


struct ListNode {
	int data;
	ListNodePosi pred;
	ListNodePosi succ;

	ListNode(int const& e = 0, ListNodePosi p = NULL, ListNodePosi s = NULL) : data(e), pred(p), succ(s) {}
};

class List {
private:
	int _size;
	ListNodePosi header;
	ListNodePosi trailer;
public:
	List() {
		header = new ListNode;
		trailer = new ListNode;
		header->succ = trailer;
		header->pred = NULL;
		trailer->pred = header;
		trailer->succ = NULL;
		_size = 0;
	}
	
	void enqueue(int const& e) {
		ListNodePosi curr = new ListNode(e, trailer->pred, trailer);
		trailer->pred->succ = curr;
		trailer->pred = curr;
		_size++;
	}

	int dequeue() {
		if (_size <= 0) return 0;
		int e = header->succ->data;
		header->succ = header->succ->succ;
		header->succ->pred = header;
		_size--;
		return e;
	}

	bool isEmpty() { return (_size == 0); }

};


struct Vertex {
	int index;
	int band;
	List nbr;

};


List Q = List();
Vertex* g;


int BFS(int n = MAX_INT) {
	int lastBand = -1, i = 1;
	while (i < n) {
		if (g[i].band) i++;
		else {
			Q.enqueue(i);
			g[i].band = -lastBand;			
			while (!Q.isEmpty()) {
				int x = Q.dequeue();
				lastBand = g[x].band;

				while (!g[x].nbr.isEmpty()) {
					int u = g[x].nbr.dequeue();
					if (g[u].band == lastBand) return -1;
					if (!g[u].band) {
						Q.enqueue(u);
						g[u].band = -lastBand;

					}
				}

			}
		}
	}
	return 1;
}


int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	g = new Vertex[n + 1];
	for (int i = 1; i <= n; i++) {
		g[i].index = i;
		g[i].band = 0;
		g[i].nbr = List();
	}

	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		g[u].nbr.enqueue(v);
		g[v].nbr.enqueue(u);
	}

	printf("%d", BFS(n + 1));
	return 0;

}