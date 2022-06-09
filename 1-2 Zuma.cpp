//
//
//  
//
//
//

#include <iostream>
using namespace std;
#define BeadPosi Bead*

// using BeadPosi = Bead*;

const int MAX_NUM = 1e4;
const int MAX_LENGTH = 1e4;

char* seq = new char[MAX_LENGTH];

struct Bead {
    char data;
    BeadPosi pred;
    BeadPosi succ;
    Bead() {}
    Bead(char c, BeadPosi p = NULL, BeadPosi s = NULL) : data(c), pred(p), succ(s) {}
    BeadPosi insertBefore(char c);
    BeadPosi insertAfter(char c);
};

BeadPosi Bead::insertBefore(char c) {
    BeadPosi x = new Bead(c, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

BeadPosi Bead::insertAfter(char c) {
    BeadPosi x = new Bead(c, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}


class BeadList {
private:
    int _size;
    BeadPosi header;
    BeadPosi trailer;
public:
    
    BeadList()
    {
        init();
        _size = 0;
    }
    BeadList(char* initial, int length)
    {
        init();
        _size = length;
        BeadPosi curr = header;
        for (int i = 0; i < length; i++)
            curr = curr->insertAfter(initial[i]);
    }
    void init() {
        header = new Bead;
        trailer = new Bead;
        header->succ = trailer;
        header->pred = NULL;
        trailer->pred = header;
        trailer->succ = NULL;
    }
    BeadPosi removeRange(BeadPosi p, BeadPosi s, int n);
    BeadPosi elimAdjacent(BeadPosi curr);
    void insertAt(int k, char c);
    void printBead() {
        if (_size == 0) printf("-\n");
        else {
            BeadPosi b = header->succ;
            for (int i = 0; i < _size; i++) {
                printf("%c", b->data);
                b = b->succ;
            }
            printf("\n");
        }
    }
};

BeadPosi BeadList::removeRange(BeadPosi p, BeadPosi s, int n) {
    BeadPosi h = p->succ;
    BeadPosi t = s->pred;
    p->succ = s;
    s->pred = p;
    while (h != t) {
        h = h->succ;
        delete h->pred;
    }
    _size -= n;
    return p;
}

BeadPosi BeadList::elimAdjacent(BeadPosi curr) {
    char c = curr->data;
    BeadPosi head = curr;
    while (head->data == c) head = head->pred;
    BeadPosi tail = head->succ;
    int count = 0;
    while (tail->data == c) {
        count++;
        tail = tail->succ;
    }
    
    if (count >= 3) {
        head = removeRange(head, tail, count);
        return head;
    }
    else return header;
}

void BeadList::insertAt(int k, char c) {
    BeadPosi b = header->succ;
    while (0 < k--) b = b->succ;
    b = b->insertBefore(c);
    _size++;
    while (b != header) b = elimAdjacent(b);
    printBead();
}

int main() {
    int n, length = 0;
    scanf("%s", seq);
    while (seq[length] != '\0') length++;
    if (seq[0] == '-' || seq[0] == ' ') length = 0;
    
    BeadList beads = (length > 0) ? BeadList(seq, length) : BeadList();
    
    scanf("%d", &n);
    
    int k; char E;
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &k, &E);
        beads.insertAt(k, E);
    }
    return 0;
}
