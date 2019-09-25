#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int id;
	int C;
	int M;
	int E;
	int A;
}a[2005];

int f[1000000];
int A[1000000];
int E[1000000];
int C[1000000];
int M[1000000];

int comA(node & t1, node & t2) {
	return t1.A > t2.A;
}

int comC(node & t1, node & t2) {
	return t1.C > t2.C;
}

int comM(node & t1, node & t2) {
	return t1.M > t2.M;
}

int comE(node & t1, node & t2) {
	return t1.E > t2.E;
}

int main() {
	int n,m;
	cin >> n >> m;
	for (int i=0;i<n;i++) {
		cin >> a[i].id >> a[i].C >> a[i].M >> a[i].E;
		a[i].A = (a[i].C + a[i].M + a[i].E) / 3;
		f[a[i].id] = 1;
	}
	sort(a,a+n,comA);
	A[a[0].id] = 1;
	for (int i=1;i<n;i++) {
		if (a[i].A == a[i-1].A) {
			A[a[i].id] = A[a[i-1].id];
		}
		else {
			A[a[i].id] = i+1;
		}
	}
	sort(a,a+n,comC);
	C[a[0].id] = 1;
	for (int i=1;i<n;i++) {
		if (a[i].C == a[i-1].C) {
			C[a[i].id] = C[a[i-1].id];
		}
		else {
			C[a[i].id] = i+1;
		}
	}
	sort(a,a+n,comM);
	M[a[0].id] = 1;
	for (int i=1;i<n;i++) {
		if (a[i].M == a[i-1].M) {
			M[a[i].id] = M[a[i-1].id];
		}
		else {
			M[a[i].id] = i+1;
		}
	}
	sort(a,a+n,comE);
	E[a[0].id] = 1;
	for (int i=1;i<n;i++) {
		if (a[i].E == a[i-1].E) {
			E[a[i].id] = E[a[i-1].id];
		}
		else {
			E[a[i].id] = i+1;
		}
	}
	int id;
	while (m--) {
		cin >> id;
		if (!f[id]) {
			cout << "N/A" << endl;
		}
		else {
			if (A[id] <= C[id] && A[id] <= M[id] && A[id] <= E[id]) {
				cout << A[id] << " A\n";
			}
			else if (C[id] <= A[id] && C[id] <= M[id] && C[id] <= E[id]) {
				cout << C[id] << " C\n";
			}
			else if (M[id] <= C[id] && M[id] <= A[id] && M[id] <= E[id]) {
				cout << M[id] << " M\n";
			}
			else if (E[id] <= C[id] && E[id] <= M[id] && E[id] <= A[id]) {
				cout << E[id] << " E\n";
			}
		}
	}
	return 0;
}
