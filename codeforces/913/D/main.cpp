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

const int MAXN = 200*1000 + 10;
int A[MAXN],W[MAXN],ord[MAXN],n,T;

struct DS{
	set<pi> S;
	ll sum;
	DS() {
		sum = 0;
		S = set<pi>();
	}
	void insert(int idx,int val) {
		sum += val;
		S.insert(mp(val,idx));
	}
	void insert(int idx,int val,int t_siz,int T) {
		insert(idx,val);
		while(sz(S) > t_siz || sum > T) {
			sum -= S.rbegin()->xx;
			S.erase(*S.rbegin());
		}
	}
	int getSize(){
		return sz(S);
	}
	void clear(){
		S.clear();
		sum = 0;
	}
};

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&T);
	loop(i,n) scanf("%d %d",A + i,W + i),ord[i] = i;
	sort(ord,ord + n,[](const int & a,const int & b) {
		return A[a] < A[b];
	});

	int ans = 0;
	DS ds;
	for(int i = n-1;i >= 0;i--) {
		int j = ord[i];
		ds.insert(j,W[j],A[j],T);
		ans = max(ans,ds.getSize());
	}
	printf("%d\n%d\n",ans,ans);
	ds.clear();
	for(int i = n-1;i >= 0;i--) {
		int j = ord[i];
		ds.insert(j,W[j],A[j],T);
		if(ds.getSize() == ans) {
			for(auto p : ds.S)
				printf("%d ",p.yy+1);
			return 0;
		}
	}

	return 0;
}
