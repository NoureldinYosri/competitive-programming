#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
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
const double PI = acos(-1);
using namespace std;

int n;
int A[1 << 20];
int B[1 << 20],m;
int C[1 << 20];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int K;
	scanf("%d %d",&n,&K);
	loop(i,n) scanf("%d",A + i),B[i] = A[i];
	sort(A,A + n);
	loop(i,n) B[i] = A[i];
	m = unique(B,B + n) - B;
	if(m > 2) {
		puts("-1");
		return 0;
	}
	if(m == 2) {
		vi X[2];
		loop(i,n)
			X[A[i] != A[0]].pb(A[i]);
		if(abs(sz(X[0]) - sz(X[1])) > 1) {
			puts("-1");
			return 0;
		}
		if(sz(X[0]) < sz(X[1])) X[0].swap(X[1]);
		int x = X[0].back(),y = X[1].back();
		loop(i,n) {
			B[i] = x;
			swap(x,y);
		}
		copy(B,B + n,A);
	}
	loop(i,n-1)
		if((A[i] ^ A[i + 1]) != K) {
			puts("-1");
			return 0;
		}
	loop(i,n) printf("%d%c",A[i]," \n"[i==n-1]);
	return 0;
}
