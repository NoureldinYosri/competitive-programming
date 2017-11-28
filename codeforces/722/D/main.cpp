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

const int MAX = 50000;



int A[MAX],n;
vi ans;

bool valid(int threshold){
	ans.clear();
	set<int> S;
	loop(i,n) {
		int x = A[i];
		while(x > threshold) x >>= 1;
		while(S.find(x) != S.end()) x >>= 1;
		if(!x) return 0;
		S.insert(x);
		ans.pb(x);
	}
	return 1;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		int x; scanf("%d",&x);
		A[i] = x;
	}
	ll s = 1,e = INT_MAX;
	while(s < e){
		int threshold = (s + e ) >> 1;
		if(valid(threshold)) e = threshold;
		else s = threshold + 1;
	}
	valid(s);
	for(int x : ans) printf("%d ",x);

	return 0;
}
