#ifdef DONE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "my_math.h"
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

vi cnts {1,4,24,192,2304,46080};
vi dice {0,4,6 ,8 ,12   ,20};

double P[6][46080 + 1];

vd mul(vd A,vd B) {
	int n = sz(A),m = sz(B);
	int nm = min(n + m,46080 + 1);
	vd C(nm,0);
	for(int i = 0;i < n;i++)
		for(int j = 0;j < m && i+j < nm;j++)
			C[i + j] += A[i]*B[j];
	return C;
}

vd add(vd A,vd B){
	int N = max(sz(A),sz(B));
	A.resize(N,0);
	B.resize(N,0);
	vd C(N,0);
	for(int i = 0;i < N;i++)
		C[i] = A[i] + B[i];
	return C;
}

vd mul(vd A,double c) {
	vd B(sz(A),0);
	for(int i = 0;i < sz(A);i++)
		B[i] = A[i]*c;
	return B;
}

vd EXP(vd A,int p) {
	if(p == 0) return vd(1,1);
	vd B(1,1);
	for(;p > 1;p >>= 1) {
		if(p & 1) B = mul(A,B);
		B = mul(B,B);
	}
	return mul(A,B);
}

double compute(int n,int s,int d) {
	vd A(d+1,1.0/d);
	A[0] = 0;
	return EXP(A,n)[s];
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	P[0][1] = 1;
	for(int lev = 1;lev < 6;lev++){
		vd A(dice[lev]+1,1.0/dice[lev]);
		A[0] = 0;
		vd B(1,1),C(1,0);
		for(int prv = 1;prv <= cnts[lev-1];prv++) {
			B = mul(A,B);
			C = add(C,mul(B,P[lev-1][prv]));
		}
		for(int v = 0;v < sz(C);v++)
			P[lev][v] = C[v];
		print(C,double);
	}

	double u = 0;
	double var = 0;
	for(int v = 1;v <= 46080;v++){
		u += v*P[5][v];
		var += pow(v,2.0) * P[5][v];
	}
	var -= u*u;
	cout << fixed << setprecision(4) << var << endl;

	return 0;
}
#endif
