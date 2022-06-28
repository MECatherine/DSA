#include <cstdio>
//#include <iostream>
//using namespace std;

#define MAX_N 4000000
#define MAX_TASK 2000000
#define MAX_P 2E32
#define LENGTH 8

#define Parent(i) ( (i - 1) >> 1 )
#define LChild(i) ( 1 + (i << 1) )
#define RChild(i) ( (1 + i) << 1 )


struct Task {
	long long priority;
	char name[LENGTH];
/*
	Task(int p, char s[]) {
		priority = p;
		int i = 0;
		while (i < LENGTH) {
			name[i] = s[i];
			if (s[i++] == '\0') break;
		}
	}
	*/
	bool valid()  { return (priority * 2 < MAX_P); }
	void update() { priority *= 2; }
	void print() {
		/*int i = 0;
		while(name[i] != '\0') printf("%s", name[i++]);
		printf("\n");
		*/
		printf("%s\n", name);
	}

};

bool lt(Task a, Task b) {
	if (a.priority != b.priority) return (a.priority < b.priority);
	char* ca = a.name;
	char* cb = b.name;
	int la = 0, lb = 0;
	while(ca[la] != '\0') la++;
    while(cb[lb] != '\0') lb++;
	/*
	int count_a = 0, count_b = 0;
	while(ca[la] != '\0') {
		count_a += ca[la] - '0';
		la++;
	}
	while(cb[lb] != '\0') {
		count_b += cb[lb] - '0';
		lb++;
	}
	return count_a < count_b;
	*/
	
	for (int i = 0; (i < la) && (i < lb); i++) {
		if (ca[i] != cb[i]) return ca[i] < cb[i];
	}
	return (la < lb);
	


}

template <typename T> class Vector {
private:
	T* _elem;
	int _size;
public:
	Vector() {
		_size = 0;
		_elem = new T[MAX_N];
	}
	~Vector() { 
		_size = 0;
		delete[] _elem;
	}

	T &operator[](int i) { return _elem[i]; }

	bool empty() { return (_size == 0); }

	void heapify(int n) {
		//////
		//cout << "Initialize a heap" << endl;
		//////
		int i = Parent(n - 1);
		while (i >= 0) {
			//cout << "i = " << i << endl;
			percolateDown(i);
			i--;
		}
		//////
		//cout << "Done a heap" << endl;
		//////
	}

	bool hasLChild(int i) { return ( LChild(i) < _size); }
	bool hasRChild(int i) { return ( RChild(i) < _size); }

	int findP(int i) {
		int result = i;
		if (hasLChild(i)) result = lt(_elem[result], _elem[LChild(i)]) ? result : LChild(i);
		if (hasRChild(i)) result = lt(_elem[result], _elem[RChild(i)]) ? result : RChild(i);
		return result;
	}

	void swap(int x, int y) {
		//////
		//cout << "exchange " << x << " and " << y << endl;
		//////
		T u = _elem[x];
		_elem[x] = _elem[y];
		_elem[y] = u;
	}

	void percolateUp(int i) {
		while (i > 0) {
			int j = Parent(i);
			if (lt(_elem[i], _elem[j])) {
				swap(i, j);
				i = j;
			}
			else break;
		}
	}

	void percolateDown(int i) {
		while (i < _size) {
			int j = findP(i);
			//////
			//cout << endl << "For i = " << i << " , " << j << " is larger" << endl;
			//////
			if (j == i) break;
			swap(i, j);
			i = j;
		}
	}

	void insert(T e) {
		_elem[_size++] = e;
		// percolateUp(_size - 1);
	}

	T remove() {
		//////
		//cout << "remove the top " << endl;
		//////
		T e = _elem[0];
		//////
		//cout << "old p is " << e.priority << endl;
		//cout << "new p is " << e.priority * 2 << endl;
		////// 
		if (!e.valid()) swap(0, --_size);
		else _elem[0].update();

		//////
		//cout << endl << "Renew the heap" << endl;
		//////
		percolateDown(0);
		return e;
	}


};



Vector<Task> TaskHeap;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	char str[LENGTH];
	int p;

	for (int i = 0; i < n; i++) {
		Task t;
		scanf("%lld %s", &t.priority, t.name);
		TaskHeap.insert(t);
	}
	TaskHeap.heapify(n);
	while (m > 0) {
		if (TaskHeap.empty()) break;
		Task t = TaskHeap.remove();
		t.print();
		//if(!t.valid()) break;
		m--;
	}
	return 0;

}