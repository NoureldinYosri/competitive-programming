#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

void work(vi & A, int p){
	int n = A.size();
	vi B(n, 0);
	for(int i = 0; i < n; i++) {
		int x = A[i];
		int l = ((i - 1)%n + n)%n;
		int r = (i + 1)%n;
		int lv = x >> 1;
		if(i == p) lv = 0;
		int rv = x - lv;
		B[l] += lv;
		B[r] += rv;
	}
	A.swap(B);
}

int main(){
	int n = rand()%5 + 4;
	int m = (rand()%5)*2;
	int p = rand()%n;
	cout << n << " " << m << endl;
	cerr << "p = " << p << endl;
	vi A(n, m);
	int ctr = 0;
	while(1) {
		char c; int x; scanf(" %c %d", &c, &x);
		if(c == '!') {
			assert(x == p + 1);
			return 0;
		}
		ctr++;
		assert(ctr <= 1000);
		cout << A[x - 1] << endl;
		work(A, p);
		for(int v : A) cerr << v << " ";
			cerr << endl;
	}
}