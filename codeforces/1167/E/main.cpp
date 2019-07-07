#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
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

int A[1 << 20];
int n,x;
int B[1 << 20];

void getB(){
	set<int> S;
	for(int i = 1;i <= x;i++)
		B[i] = x+1;
	loop(i,n) {
		int y = A[i];
		auto ptr = S.upper_bound(y);
		if(ptr != S.end())
			B[y] = min(B[y],*ptr);
		S.insert(y);
	}
}
bool valid(int l,int r) {
	int prv = 0;
	loop(i,n) {
		if(l <= A[i] && A[i] <= r) continue;
		if(A[i] < prv) return 0;
		prv = A[i];
	}
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&x);
	loop(i,n) scanf("%d",A + i);

	getB();
	ll ans = 0;
	for(int l = 1;l <= x;l++){
		if(!valid(l,x)) {
			cerr << l << ": None " << B[l] << endl;
			break;
		}
		int s = l,e = x;
		while(s < e) {
			int m = (s + e) >> 1;
			if(valid(l,m)) e = m;
			else s = m+1;
		}
		cerr << l << " " << s << " " << B[l] << endl;
		ans += x-s+1;
	}
	cout << ans << endl;
	return 0;
}
