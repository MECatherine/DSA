#include <iostream>
using namespace std;



class TrainStack {
private:
	int _size;
	int* _elem;
	int _capacity;
public:
	TrainStack(int n = 0) {
		_capacity = n;
		_elem = new int[n]; 
		_size = 0;
	}
	~TrainStack() {
		delete _elem;
	}

	int size() { return _size; }
	bool empty() { return _size == 0; }
	bool full() { return _size == _capacity; }

	void setMax(int m) { _capacity = m; }
	void push(int const& e) { _elem[_size++] = e; }
	void init() {
		for (int i = 0; i < _capacity; i++)
			push(_capacity - i);
	}

	int pop() {
		if (_size <= 0) return 0;
		else {
			int e = _elem[_size - 1];
			_elem[_size - 1] = 0;
			_size--;
			return e;
		}
	}

	void printpush(int const& e) {
		push(e);
		printf("push\n");
	}

	int printpop() {
		printf("pop\n");
		return pop();
	}


	int top() { return _elem[_size - 1]; }

};

int main() {
	int n, m, e;
	scanf("%d%d", &n, &m);
	TrainStack A = TrainStack(n);
	A.init();
	int* B = new int[n];
	TrainStack S = TrainStack(m);

	for (int i = 0; i < n; i++) 
		scanf("%d", &B[i]);
	
	// Dispatching

	int i = 0, j = 0; bool feasible = true;
	short* oprt = new short[2 * n];

	while (!A.empty()) {
		if (S.top() == B[i]) {
			S.pop();
			oprt[j++] = 1;
			if (++i >= n) break;
		}
		else if (S.full()) {
			feasible = false;
			break;
		}
		else {
			S.push(A.pop());
			oprt[j++] = 0;
		}

	}

	while (!S.empty()) {
		if (S.pop() == B[i++]) oprt[j++] = 1;
		else {
			feasible = false;
			break;
		}
	}


	if (!feasible)  {
		printf("No\n");
		return 0;
	}

	for (int i = 0; i < n * 2; i++) {
		if (oprt[i] == 0) printf("push\n");
		else printf("pop\n");
	}

	return 0;

}
