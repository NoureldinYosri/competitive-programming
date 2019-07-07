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

int n;
ll L,R,A[1 << 20];

ll brute_force(){
	ll ans = 0;
	vector<pair<ll,ll>> V;
	loop(i,n) for(int j = i+1;j < n;j++) {
		ll a = A[i],b = A[j];
		ll l = abs(a - b) + 1,r = a + b - 1;
		l = max(l,L);
		r = min(r,R);
		if(l > r) continue;
		V.push_back(mp(l,r));
	}
	sort(all(V));
	ll s = 0,e = -1;
	for(auto p : V) {
		if(p.xx <= e)
			e = max(e,p.yy);
		else {
			ans += e-s+1;
			s = p.xx;
			e = p.yy;
		}
	}
	ans += e-s+1;
	return ans;
}

ll solve(){
	sort(A,A + n);
	ll ans = 0;
	vector<pair<ll,ll>> V;

	return ans;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %lld %lld",&n,&L,&R);
	loop(i,n) scanf("%lld",A + i);
	cout << brute_force() << endl;
	return 0;
}
