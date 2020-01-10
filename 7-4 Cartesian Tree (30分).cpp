#include<iostream>
#include<algorithm>
#include<string>
#include<set>
#include<queue>
using namespace std;

int a[35];
int n;
struct node {
	struct node* lnode;
	struct node* rnode;
	int data;
};
typedef struct node* tree;

int findMin(int l, int r) {
	int minv=a[l];
	int minp=l;
	for (int i=l;i<=r;i++) {
		if (minv>a[i]) {
			minv = a[i];
			minp=i;
		}
	}
	return minp;
}

tree solve(int l,int r) {
	int root = findMin(l,r);
	tree tr = (tree)malloc(sizeof(struct node));
	tr->data = a[root];
	if (l==r) {
		tr->lnode=NULL;
		tr->rnode=NULL;
		return tr;
	}
	if (root-1>=l){
        tr->lnode = solve(l, root-1);
	}
    else{
        tr->lnode=NULL;
    }
    if (root+1<=r){
        tr->rnode = solve(root+1, r);
    }
    else {
        tr->rnode=NULL;
    }
	return tr;
}

void intra(tree t) {
    if (t==NULL) return;
	intra(t->lnode);
	cout << t->data << " ";
	intra(t->rnode);
}

void bfs(tree t) {
	int cnt=0;
	queue<tree> que;
	que.push(t);
	while (!que.empty()) {
		tree tmp = que.front();
		que.pop();
		printf("%d",tmp->data);
		cnt++;
		if (cnt<n) {
			printf(" ");
		}
		else {
			printf("\n");
		}
		if (tmp->lnode!=NULL) {
			que.push(tmp->lnode);
		}
		if (tmp->rnode!=NULL) {
			que.push(tmp->rnode);
		}
	}
}

int main() {
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	tree t = solve(0,n-1);
	bfs(t);
	return 0;
}

