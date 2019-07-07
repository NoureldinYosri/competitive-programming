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

const int MAX = 1024;
int R,C,B;
int P[MAX],S[MAX],M[MAX];
ll V[MAX];

bool can(ll t) {
	loop(i,C) {
		V[i] = max(t - P[i],0LL)/S[i];
		V[i] = min(V[i],M[i] + 0LL);
	}
	sort(V,V + C);
	reverse(V,V + C);
	ll cnt = 0;
	loop(i,R) cnt += V[i];
	return cnt >= B;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d %d %d",&R,&B,&C);
		loop(i,C) scanf("%d %d %d",M+i,S+i,P+i);
		ll s = 0,e = LLONG_MAX;
		while(s < e) {
			ll m = s + (e-s)/2;
			if(can(m)) e = m;
			else s = m+1;
		}
		printf("Case #%d: %lld\n",t,s);
	}
	return 0;
}
