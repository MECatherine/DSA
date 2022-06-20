#include <cstdio>
#include "temperature.h"
#include "temperature_lib.c"
///#include <iostream>
///using namespace std;

typedef long long LONG;

#define PointPosi Point*
#define BinNodePosi BinNode*
#define CAPACITY 50000

int MAX(int a, int b) { return (a > b) ? a : b; }


template <typename T> class Vector {
private:
	T* data;
	int _cap, _size;
public:
	Vector() {
		_cap = CAPACITY;
		data = new T[_cap];
		_size = 0;
	}

	int size() { return _size; }

	T back() { return (_size > 0) ? data[_size - 1] : NULL; }

	T &operator[] (int const x) {
		return data[x];
	}

	void push_back(T const& e) { data[_size++] = e; }

	// Find the element no less than target number
	int find(T const& e, int lo, int hi) {
		if (e < data[lo] || !_size) return -1;
		while (lo < hi) {
			int mi = (lo + hi) >> 1;
			(e <= data[mi]) ? hi = mi : lo = mi + 1;
		}

		return lo;
	}

	~Vector() {
		delete[] data;
		_cap = 0;
		_size = 0;
	}

};

typedef struct Point {
	int _x, _y;
	LONG _temp;

	Point() { _x = _y = _temp = 0; }
	Point(int x, int y, int t) : _x(x), _y(y), _temp((LONG)t) {}
} Point;

// See if point a is smaller than point b
bool lt(Point a, Point b) {
	return (a._x == b._x) ? a._y < b._y : a._x < b._x;
}

Point pt[CAPACITY];

void merge(int lo, int mi, int hi) {
	PointPosi A = pt + lo;
	int lb = mi - lo;
	PointPosi B = new Point[lb];
	//for (int i = 0; i < lb; B[i] = A[i++]);
	for (int i = 0; i < lb; i++) B[i] = A[i];

	int lc = hi - mi;
	PointPosi C = pt + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
		if ( (j < lb) && ( !(k < lc) || lt(B[j], C[k]) ) ) A[i++] = B[j++];
		if ( (k < lc) && ( !(j < lb) || lt(C[k], B[j]) ) ) A[i++] = C[k++];
	}
	delete[] B;
}

void mergeSort(int lo, int hi) {
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}


struct BinNode {
	int x;
	int index;
	Vector<int> y_v;
	Vector<LONG> temp_v;

	BinNodePosi parent;
	BinNodePosi lc;
	BinNodePosi rc;
};

Vector<BinNodePosi> XNode;
BinNodePosi BinTree = new BinNode();


void buildTree(BinNodePosi p, Vector<BinNodePosi> v, int lo, int hi) {
	if (lo >= hi) return;
	int mi = (lo + hi) >> 1;
	p = v[mi];
	buildTree(p->lc, v, lo, mi);
	buildTree(p->rc, v, mi + 1, hi);
}

/*
BinNodePosi buildTree(BinNodePosi p, Vector<BinNodePosi> v, int lo, int hi) {
	
	//////
	printf("\nlo: %d, hi: %d\n", lo, hi);
	//////

	if (hi - lo == 1)	return v[lo];
	if (lo == hi) {
		//////
		printf("\nInsert NULL point\n");
		return NULL;
	}
	int mi = (lo + hi) >> 1;


	//////
	printf("\nnow mi = %d\n", mi);
	//////

	BinNodePosi bn = v[mi];

	//////
	printf("\nInsert node X: %d\n", bn->x);
	cout << bn;

	//////

	bn->parent = p;

	bn->lc = buildTree(bn, v, lo, mi);

	//////
	printf("\nDone left child tree\n");
	printf("\nNow node is %d, mi = %d, hi = %d\n", bn->x, mi, hi);
	cout << bn;
	printf("\nStart right child tree\n");
	//////

	bn->rc = buildTree(bn, v, mi + 1, hi);

	//////
	printf("\nDone right child tree\n");
	//////

	return v[mi];
	
}
*/

void buildBinTree(int n) {
	//////
	///printf("\nReady to sort\n");
	//////
	mergeSort(0, n);
	//////
	///printf("\nDone sorting\n");
	//////
	Point curr_p = pt[0];
	int curr_x = curr_p._x;
	BinNodePosi curr_N = new BinNode();
	curr_N->x = curr_x;

	int count = 0;
	curr_N->y_v.push_back(curr_p._y);
	curr_N->temp_v.push_back(curr_p._temp);
	curr_N->index = count++;

	for (int i = 1; i < n; i++) {
		curr_p = pt[i];
		if (curr_x == curr_p._x) {
			curr_N->y_v.push_back(curr_p._y);
			curr_N->temp_v.push_back(curr_p._temp);
		}
		else {
			XNode.push_back(curr_N);
			curr_N = new BinNode();
			curr_x = curr_p._x;
			curr_N->x = curr_x;
			curr_N->y_v.push_back(curr_p._y);
			curr_N->temp_v.push_back(curr_p._temp);
			curr_N->index = count++;
		}
	}
	if (XNode.back()->x != curr_x) XNode.push_back(curr_N);

	//////
	///printf("\nDone X nodes\n");
	//////

	int size = XNode.size();

	///for (int i = 0; i < size; i++) cout << "Address of " << i << " is " << XNode[i] << endl;

	//////
	///printf("\nReady to construct tree\n");
	//////
	int mi = size >> 1;
	BinTree = XNode[mi];
	///cout << endl << "Address of root is " << BinTree;
	buildTree(BinTree, XNode, 0, size);
	//////
	///printf("\nDone constructing tree\n");
	//////
}

// Find node next to target X node
BinNodePosi searchIn(BinNodePosi v, const int& e, BinNodePosi hot) {
	if (!v) return hot;
	if (e == v->x) return v;
	hot = v;
	return searchIn( ( (e < v->x) ? v->lc : v->rc ), e, hot);
}

int getTemp(int x1, int y1, int x2, int y2) {
	LONG t = 0;
	int count = 0;
	int start = searchIn(BinTree, x1, NULL)->index;
	if( XNode[start]->x < x1 ) start++;

	int end = searchIn(BinTree, x2, NULL)->index;
	if( XNode[end]->x <= x2 ) end++;

	Vector<int> y;
	Vector<LONG> temp;
	int s;

	for (int i = start; i < end; i++) {
		y = XNode[i]->y_v;
		s = y.size();
		if (!s) break;

		int j = y.find(y1, 0, s);
		j = MAX(0, j);

		temp = XNode[i]->temp_v;
		while (j < s) {
			if (y[j] > y2) break;
			t += temp[j];
			count++;
			j++;
		}
	}

	return (count > 0) ? (int)(t / count) : 0;
}

/*
class BinTree {
private:
	int _size;
	BinNodePosi _root;

public:
	BinTree();
	BinNodePosi insertAsRoot(BinNodePosi r);
	BinNodePosi insert(BinNodePosi r);

	void inOrder(BinNodePosi start, BinNodePosi end, int y1, int y2) {}


};
*/

/*
struct StationNode {
	LONG x, y;
	int temp;
	StPosi parent;
	StPosi lc, rc;
	StPosi succ;
	StationNode(int a, int b, int t, StPosi p = NULL, StPosi l = NULL, StPosi r = NULL) : 
		x(a), y(b), temp(t), parent(p), lc(l), rc(r) {}
};
*/



int main() {
	//////
	///printf("\nReady to get number \n");
	//////
	int n = GetNumOfStation();
	
	/*
	if (n == 0) {
		int x1, y1, x2, y2;
		while (GetQuery(&x1, &y1, &x2, &y2)) {
			Response(0);
			printf("0\n");
		}
	}
	*/
	int x, y;
	int temp;

	for (int i = 0; i < n; i++) {
		//////
		///printf("\nReady to get info of %d\n", i);
		//////
		GetStationInfo(i, &x, &y, &temp);

		pt[i] = Point(x, y, temp);
	}

	//////
	///printf("\nDone get info\n");
	//////
	mergeSort(0, n);
	buildBinTree(n);

	int x1, y1, x2, y2;
	

	while (GetQuery(&x1, &y1, &x2, &y2)) {
		int t = getTemp(x1, y1, x2, y2);
		Response(t);
	}
	
	return 0;
}