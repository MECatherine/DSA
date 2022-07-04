#include <cstdio>
#include <cstring>

//#include <iostream>
//using namespace std;

#define MAX_INT 100001

char* s1 = new char[MAX_INT];
char* s2 = new char[MAX_INT];

int equalLength(char* ca, char* cb) {
	int la = (int) strlen(ca);
	int lb = (int) strlen(cb);
	/*
	int la = 0, lb = 0;
	while(ca[la] != '\0') la++;
	while(cb[lb] != '\0') lb++;
	*/

	//////
	//cout << "Done computing length " << la << endl;
	//////

	if (la != lb) return 0;
	return la; 
}

char* addToEnd(char* c, int n) {
	int l = n * 2;
	char* doubleC = new char[l];
	for (int i = 0; i < l; i++) {
		doubleC[i] = c[i % n];
	}

	//////
	//cout << "Done doubling pattern " << doubleC << endl;
	//////
	
	return doubleC;
}

int* buildNext(char* P, int m) {
	int* N = new int[m];
	int t = N[0] = -1;
	int j = 0;

	//////
	//cout << "Building table... start cycle" << endl;
	//////

	while (j < m - 1) {
		if (t < 0 || P[j] == P[t]) {
			j++; 
			t++;
			N[j] = (P[j] != P[t] ? t : N[t]);
		}
		else t = N[t];
	}

	//////
	//cout << "Done creating next table" << endl;
	//////

	return N;
}

bool match(char* T, char* P, int m) {
	//////
	//cout << "Ready to build table" << endl;
	//////
	int* next = buildNext(P, m);
	int n = m * 2;
	int i = 0, j = 0;

	while(j < m && i < n) {
		if (j < 0 || T[i] == P[j]) {
			i++;
			j++;
		}
		else j = next[j];
	}
	delete[] next;
	return ((i - j) >= 0 && (i - j) <= m);
}

/*
bool cycle(char* c1, char* c2) {
	
	int l = equalLength(c1, c2);
	if (!l) {
		return false;
	}
	char* t = addToEnd(c1, l);

	return match(t, c2, l);
}
*/

int main() {
	bool result;
	char* text;
	while(scanf("%s %s", s1, s2) != EOF) {
		int l = equalLength(s1, s2);
		if (!l) printf("NO\n");
		else {
			text = addToEnd(s1, l);
			result = match(text, s2, l);
			if (result) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}