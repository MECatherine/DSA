#include <iostream>
using namespace std;
#define LightPosi LightHouse*

const int MAX_N = 4e6 + 10;
const int MAX_XY = 1e8 + 10;

struct LightHouse {
    int x, y;
    LightHouse(int a = 1, int b = 1) : x(a), y(b) {}
};

class HouseSet{
private:
    int _size;
    LightPosi _elem;
public:
    HouseSet(int s = MAX_XY) {
        _elem = new LightHouse[s];
        _size = s;
    }
    ~HouseSet() {
        delete _elem;
        _size = 0;
    }
    void insertAt(int n, int a, int b) {
        _elem[n] = LightHouse(a, b);
    }
    void mergeSortByX(int lo, int hi);
    void mergeByX(int lo, int mi, int hi);
    
    long invInside(int lo, int hi);
    long invBetween(int lo, int mi, int hi);
    
    long ordInside(int lo, int hi);
    long ordBetween(int lo, int mi, int hi);
};


void HouseSet::mergeSortByX(int lo, int hi) {
    if (hi - lo < 2) return;
    int mi = (lo + hi) >> 1;
    mergeSortByX(lo, mi);
    mergeSortByX(mi, hi);
    mergeByX(lo, mi, hi);
}

void HouseSet::mergeByX(int lo, int mi, int hi) {
    int i = 0;
    LightPosi A = _elem + lo;
    int j = 0, lb = mi - lo;
    LightPosi B = new LightHouse[lb];
    for (int i = 0; i < lb; i++) B[i] = A[i];
    int k = 0, lc = hi - mi;
    LightPosi C = _elem + mi;
    while (j < lb && k < lc)
        A[i++] = (B[j].x <= C[k].x) ? B[j++] : C[k++];
    while (j < lb)
        A[i++] = B[j++];
    delete [] B;
}

long HouseSet::invInside(int lo, int hi) {
    if (hi - lo < 2) return 0;
    int mi = (lo + hi) >> 1;
    return invInside(lo, mi) + invInside(mi, hi) + invBetween(lo, mi, hi);
}

long HouseSet::invBetween(int lo, int mi, int hi) {
    long invCount = 0;
    int i = 0;
    LightPosi A = _elem + lo;
    int j = 0, lb = mi - lo;
    LightPosi B = new LightHouse[lb];
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    int k = 0, lc = hi - mi;
    LightPosi C = _elem + mi;
    
    while (j < lb && k < lc) {
        invCount += (B[j].y > C[k].y) ? (lb - j) : 0;
        A[i++] = (B[j].y <= C[k].y) ? B[j++] : C[k++];
        
    }
    while (j < lb)
        A[i++] = B[j++];
    return invCount;
}

long HouseSet::ordInside(int lo, int hi) {
    if (hi - lo < 2) return 0;
    int mi = (lo + hi) >> 1;
    return ordInside(lo, mi) + ordInside(mi, hi) + ordBetween(lo, mi, hi);
}

long HouseSet::ordBetween(int lo, int mi, int hi) {
    long ordCount = 0;
    int i = 0;
    LightPosi A = _elem + lo;
    int j = 0, lb = mi - lo;
    LightPosi B = new LightHouse[lb];
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    int k = 0, lc = hi - mi;
    LightPosi C = _elem + mi;
    
    while (j < lb && k < lc) {
        ordCount += (B[j].y < C[k].y) ? (lc - k) : 0;
        A[i++] = (B[j].y <= C[k].y) ? B[j++] : C[k++];
        
    }
    while (j < lb)
        A[i++] = B[j++];
    return ordCount;
}



int main() {
    int n;
    scanf("%d", &n);
    HouseSet s = HouseSet(n);
    int a, b;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a, &b);
        s.insertAt(i, a, b);
    }
    s.mergeSortByX(0, n);
    printf("%ld\n", s.ordInside(0, n));
    return 0;
}
