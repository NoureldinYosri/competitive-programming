#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

using row = bitset<256>;
using matrix = vector<row>;

void spit(matrix & A){
	int n = sz(A);
	loop(i, n) {
		loop(j, n) cerr << A[i].test(j) << " ";
		cerr << " | " << A[i].test(n);
		cerr << endl;
	}
	cerr << endl;	
}

vi people;

void gauss(matrix & A){
	spit(A);
	int n = A.size();
	vi C(n, -1);
	for(int p = 0, r = 0; p < n; p++){
		int t = r;
		while(t < n && !A[t].test(p)) t++;
		if(t == n) continue;
		if(t != r) {
			swap(A[r], A[t]);
		}
		for(int i = r + 1; i < n; i++)
				if(A[i].test(p))
					A[i] ^= A[r];
		C[r] = p;
		r++;		
		spit(A);
	}
	spit(A);

	for(int r = n-1; r >= 0; r--){
		if(C[r] == -1) continue;
		int p = C[r];
		for(int i = r-1; i >= 0; i--)
			if(A[i].test(p))
				A[i] ^= A[r];
	}
	spit(A);

	loop(i, n) if(A[i].test(n)) people.push_back(i);
}

bool check(matrix & B){
	row S;
	for(int x : people) S ^= B[x];
	return (int)S.count() == sz(B);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n;
	scanf("%d", &n);
	matrix A(n), B(n);
	vi ord(n);
	iota(all(ord), 0);
	loop(i, n){
		int x;
		while(scanf("%d", &x) == 1){
			if(x == -1) break;
			B[i].set(x - 1);
		}
	}
/*	sort(all(ord), [&B](const int & a, const int &b){
		return B[a].count() > B[b].count();
	});*/
	loop(i, n){
		loop(j, n) if(B[ord[i]].test(j))
			A[j].set(i);
	}
	loop(i, n) A[i].set(n);
	gauss(A);
	for(int & x : people) x = ord[x];
	sort(all(people));
	if(check(B)){
		for(int x : people) printf("%d ", x + 1);
		puts("");
	} else {
		puts("No solution");
	}
	return 0;
}
