#include "teams.h"

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct node{
	int lst;
	node *l,*r;
};

vi L,R;

void init(int N, int A[], int B[]) {
	L = vi{A,A + N};
	R = vi{B,B + N};
}

int can(int M, int K[]) {
	sort(K,K + M);

	return 0;
}
