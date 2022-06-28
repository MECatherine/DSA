#include <cstdio>
/*
#include <cstring>
#include <iostream>
using namespace std;
*/


#define LENGTH 8
#define MAX_INT 40321

static const int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040};

int* transformBackA(const int origin[]) {
	int* a = new int[LENGTH];
	for (int i = 0; i < LENGTH; i++) {
		a[i] = origin[LENGTH - 1 - i];
	}
	return a;
}

int* transformBackB(const int origin[]) {
	int* b = new int[LENGTH];
	b[0] = origin[1];
	b[1] = origin[2];
	b[2] = origin[3];
	b[3] = origin[0];
	b[4] = origin[7];
	b[5] = origin[4];
	b[6] = origin[5];
	b[7] = origin[6];
	return b;
}

int* transformBackC(const int origin[]) {
	int* c = new int[LENGTH];
	c[0] = origin[0];
	c[1] = origin[2];
	c[2] = origin[5];
	c[3] = origin[3];
	c[4] = origin[4];
	c[5] = origin[6];
	c[6] = origin[1];
	c[7] = origin[7];
	return c;
}

int hashCode(const int a[]) {
	int sum = 0;
	int count = 0;
	for (int i = 0; i < LENGTH; i++) {
		for (int j = i + 1; j < LENGTH; j++) {
			if (a[i] > a[j]) count++;
		}
		sum += count * factorial[LENGTH - i - 1];
		count = 0;
	}
	return sum;
}

struct Node {
	int* num;
	int step;
	bool find;

	Node() {
		num = new int[LENGTH];
		step = -1;
		find = false;
	}
};

Node List[MAX_INT];

struct Queue {
	int* _elem;
	int start, end;
	int size;

	Queue(int n = MAX_INT) {
		_elem = new int[n];
		start = 0;
		end = 0;
	}

	void enqueue(int e) { 
		_elem[end] = e; 
		end = (end + 1) % MAX_INT;
	}

	int dequeue() {
		int e = _elem[start];
		start = (start + 1) % MAX_INT;
		return e;
	}

	bool empty() { return start == end; }

};

Queue Q = Queue(MAX_INT);
int size = 0;

static int count_acc = 0;
static int false_acc = 0;


void checkAndUpdate(int s[], int p) {

	int n = hashCode(s);
	//////
	//cout << "check for " << n << endl;
	//////

	if (!List[n].find) {
		List[n].num = s;
		List[n].step = List[p].step + 1;
		List[n].find = true;
		Q.enqueue(n);

		//////
		count_acc++;
		//cout << "Enqueue " << n << endl;
		//////
	}
	else {
		if (List[n].step > List[p].step + 1) {
			List[n].step = List[p].step + 1;
			Q.enqueue(n);
			//////
			//count_acc++;
			//cout << "Again enqueue " << n << endl;
			//////

		}
		for (int i = 0; i < LENGTH; i++) {
			if (s[i] != List[n].num[i]) {
				false_acc++;
				break;
			}
		}
	}
}


void BFS() {
	int start[LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7};
	int* middle = new int[LENGTH];
	int* a = new int[LENGTH];
	int* b = new int[LENGTH];
	int* c = new int[LENGTH];

	int h = hashCode(start);
	List[h].num = start;
	List[h].step = 0;
	List[h].find = true;
	Q.enqueue(h);
	//////
	count_acc++;
	//////
	//cout << h << endl;

	while (!Q.empty()) {
		h = Q.dequeue();

		//////
		//cout << "Get " << h << " out" << endl;
		//////

		middle = List[h].num;
		/*
		for (int i = 0; i < 8; i++) {
			cout << middle[i] << endl;
		}
		*/
		a = transformBackA(middle);
		b = transformBackB(middle);
		c = transformBackC(middle);

		checkAndUpdate(a, h);
		checkAndUpdate(b, h);
		checkAndUpdate(c, h);
	}

	//cout << count_acc << endl;
}

int search(const int c[]) {
	int h = hashCode(c);
	return List[h].step;
}


int* state = new int[LENGTH];
int main() {
	int n, s;
	scanf("%d", &n);
	BFS();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < LENGTH; j++) {
			scanf("%d", &state[j]);
			state[j]--;
		}
		s = search(state);
		printf("%d\n", s);
	}
}