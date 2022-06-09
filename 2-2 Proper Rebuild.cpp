#include <iostream>
using namespace std;
#define MAXINT 4e6

#define BinNodePosi BinNode*


struct BinNode {
	int data;
	BinNodePosi parent;
	BinNodePosi lc;
	BinNodePosi rc;
	int height;

	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0){}
	BinNode(int e, BinNodePosi p = NULL, BinNodePosi lc = NULL, BinNodePosi rc = NULL, int h = 0):
		data(e), parent(p), lc(lc), rc(rc), height(h) {}

	BinNodePosi insertAsLC(int const&);
	BinNodePosi insertAsRC(int const&);
	bool HasLChild() { return (!(lc == NULL)); }
	bool HasRChild() { return (!(rc == NULL)); }
};

BinNodePosi BinNode::insertAsLC(int const& e) {
	return lc = new BinNode(e, this);
}

BinNodePosi BinNode::insertAsRC(int const& e) {
	return rc = new BinNode(e, this);
}


template <typename T> class Stack {
private:
	T* _elem;
	int _size;
public:
	Stack(int n = MAXINT) {
		_elem = new T[n];
		_size = 0;
	}
	~Stack() {
		delete [] _elem;
		_size = 0;
	}

	bool empty() { return _size == 0; }
	int size() { return _size; }
	void push( T p ) {
		_elem[_size] = p;
		_size++;
	}

	T pop() {
		if (_size <= 0) return NULL;
		BinNodePosi p = _elem[_size - 1];
		_elem[_size - 1] = NULL;
		_size--;
		return p;
	}
};


void static goAlongVine(BinNodePosi x, Stack<BinNodePosi> &S) {
	while (x) {
		S.push(x);
		x = x->lc;
	}
}

void printInOrder(BinNodePosi x, int n) {
	if (n == 0) return;
	Stack<BinNodePosi> S = Stack<BinNodePosi>(n);
	while (true) {
		goAlongVine(x, S);
		if (S.empty()) break;
		x = S.pop();
		printf("%d ", x->data);
		x = x->rc;
	}
}

class BinTree
{
private:
	int _size;
	BinNodePosi _root;

public:
	BinTree(int n = 0) : _size(n), _root(NULL) {}
	~BinTree() { if (0 < _size ) delete( _root); }

	int size() const{ return _size; }
	bool empty() const{ return !_root; }
	BinNodePosi root() const{ return _root; }
	BinNodePosi insertAsRoot(int const&);

	void inOrder() { printInOrder(_root, _size); }
};


BinNodePosi BinTree::insertAsRoot(int const& e) {
	_root = new BinNode(e);
	return _root;
}


int main() {
	int n;
	scanf("%d", &n);
	BinTree bt = BinTree(n);

	int* pre = new int[n];
	int* post = new int[n];
	int* full = new int[2 * n + 1];

	for (int i = 0; i < n; i++) scanf("%d", &pre[i]);

	for (int i = 0; i < n; i++) scanf("%d", &post[i]);

	int pre_count = 0, post_count = 0;

	BinNodePosi current =  bt.insertAsRoot(pre[pre_count++]);
/////////
	///cout << "insert " << current->data << "as root" << endl;

/////////
	///cout << "preorder\tpostorder\t" << endl;

	while(true) {	
////////
		////cout << pre_count << '\t' << post_count << '\t' << endl;

		while (pre[pre_count] != post[post_count]) {           ////1	
			if (current->HasLChild()) {
				current = current->insertAsRC(pre[pre_count++]);
/////////
				///cout << "		1 insert " << current->data << " as lc" << endl;
				///cout << pre_count << '\t' << post_count << '\t' << endl;
			}


			else {
				current = current->insertAsLC(pre[pre_count++]); 
/////////
				///cout << "		2 insert " << current->data << " as lc" << endl;
				///cout << pre_count << '\t' << post_count << '\t' << endl;
			}  
		}


		if (current->HasLChild()) {
			current = current->insertAsRC(pre[pre_count++]);
/////////
			///cout << "		3 insert " << current->data << " as rc" << endl;
			///cout << pre_count << '\t' << post_count << '\t' << endl;
		}


		else {
			current->insertAsLC(pre[pre_count++]); 
			post_count++;
/////////
			///cout << "		4 insert " << current->data << " as lc" << endl;
			///cout << pre_count << '\t' << post_count << '\t' << endl;
		} 

		if (pre_count >= n || post_count >= n) break;
/*
		current->insertAsLC(pre[pre_count++]);
/////////
		cout << "		3 insert " << current->lc->data << " as lc of" << current->data<< endl;
		cout << pre_count << '\t' << post_count << '\t' << endl;

		post_count++;										   ////4
		current = current->insertAsRC(pre[pre_count++]);
/////////
		cout << "		4 insert " << current->data << " as rc" << endl;
		cout << pre_count << '\t' << post_count << '\t' << endl;
*/

		while (current->data == post[post_count]) {	   ////6
			current = current->parent;						   ////7
			post_count++;
/////////
			///cout << "	whether parent" << endl;
			///cout << pre_count << '\t' << post_count << '\t' << endl;
		}
	}
	//if (bt.root() != current) bt = BinTree();
/////////

	///cout << "	current data: " << current->data << endl;
	///cout << pre_count << '\t' << post_count << '\t' << endl;

	bt.inOrder();
	return 0;
}
