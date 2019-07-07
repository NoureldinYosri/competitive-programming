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

int n,K;
int C[1 << 20],D[1 << 20];

int getContrib(int j,int *V,vi & ST,vi & O){
	int prv = ST.empty() ? -1 : ST.back();
	int len = j - prv;
	auto ptr = lower_bound(all(O),j);
	int otherMax = 1 << 29;
	int *V2 = (V == C) ? D : C;
	if(ptr != O.end()) otherMax = V2[*ptr];
	cerr << V[j] << " vs " << otherMax << endl;
	int res = 0;
	if(abs(otherMax-V[j]) <= K) res = len;
	return res;
}
void insert(int i,int *V,vi & ST,vi & O,int & ctr) {
	while(!ST.empty() && V[i] >= V[ST.back()]) {
		int j = ST.back();
		ST.pop_back();
		int tmp = getContrib(j,V,ST,O);
		cerr << "removing " << j << " -> " << tmp << endl;
		ctr -= tmp;
		cerr << "new ctr = " << ctr << endl;
	}
	int tmp = getContrib(i,V,ST,O);
	ctr += tmp;
	cerr << "tmp = " << tmp << endl;
	ST.push_back(i);
}

int solve(){
	vi A,B;
	int ans = 0,ctr = 0;
	loop(j,n) {
		insert(j,C,A,B,ctr);
		cerr << ctr << endl;
		insert(j,D,B,A,ctr);
		ans = max(ans,ctr);
		print(A,int);
		print(B,int);
		cerr << ctr << endl;
		cerr << endl;
	}
	return ans;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d %d",&n,&K);
		loop(i,n) scanf("%d",C + i);
		loop(i,n) scanf("%d",D + i);
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}
