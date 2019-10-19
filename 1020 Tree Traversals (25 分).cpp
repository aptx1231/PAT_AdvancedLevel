#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct node * tree;
struct node {
	tree lchild;
	tree rchild;
	int value;
};

int post[35];
int mid[35];

tree solve(int postl, int postr, int midl, int midr, int n) {
	if (n == 0) {
		return NULL;
	}
	int ro = post[postr];
	int i;
	for (i=midl;i<=midr;i++) {
		if (mid[i] == ro) {
			break;
		}
	}
	int L = i-midl;
	int R = midr-i;
	tree t = (tree)malloc(sizeof(struct node));
	t->lchild = solve(postl, postl+L-1, midl, i-1, L);
	t->rchild = solve(postl+L, postr-1, i+1, midr, R);
	t->value = ro;
	return t;
}

void travel(tree t) {
	if (t != NULL) {
		cout << t->value << "\n";
		travel(t->lchild);
		travel(t->rchild); 
	}		
}

void level_travel(tree t, int n) {
	int cnt = 0;
	queue<tree> que;
	if (t != NULL) {
		que.push(t);
	}
	while (!que.empty()) {
		tree t2 = que.front();
		que.pop();
		cnt++;
		cout << t2->value;
		if (cnt < n) {
			cout << " ";
		}
		if (t2->lchild != NULL) {
			que.push(t2->lchild);
		}
		if (t2->rchild != NULL) {
			que.push(t2->rchild);
		}
	}		
}

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> post[i];
	}
	for (int i=0;i<n;i++) {
		cin >> mid[i];
	}
	tree root = solve(0, n-1, 0, n-1, n);
	//travel(root);
	level_travel(root, n);
	return 0;
}
