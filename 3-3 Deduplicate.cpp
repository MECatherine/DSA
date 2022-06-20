#include <cstdio>

#define MAX_LENGTH 41
#define MAX_INT 600089
#define NodePosi Node*


struct Node
{
	char name[MAX_LENGTH];
	bool dup;
	NodePosi next;

	Node(char s[]) {
		int length = 0;
		while (s[length] != '\0') length++;
		for (int i = 0; i < length; i++) name[i] = s[i];

		dup = false;
		next = NULL;
	}
};

bool equal(char a[], char b[]) {
	int la = 0, lb = 0;
	while (a[la] != '\0') la++;
	while (b[lb] != '\0') lb++;

	if (la != lb) return false;
	for (int i = 0; i < la; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

int code(char s[]) {
	int length = 0;
	unsigned long h = 0;
	while (s[length] != '\0') length++;
	for (int i = 0; i < length; i++) {
		h = ( h << 5 ) | ( h >> 27 );
		h += s[i] - 'a';
	}
	return (int) (h % MAX_INT);
}

char nomination[MAX_LENGTH];
NodePosi table[MAX_INT];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%s", nomination);
		int c = code(nomination);

		NodePosi curr = table[c];

		if (!curr) table[c] = new Node(nomination);
		else {
			while (curr) {
				if (equal(nomination, curr->name)) {
					if (!curr->dup) {
						printf("%s\n", nomination);
						curr->dup = true;
					}
					break;
				}
				if (!curr->next) {
					curr->next = new Node(nomination);
					break;
				}
				curr = curr->next;
			}
		}

	}
	return 0;
}