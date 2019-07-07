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

int mod = 1000000007;
int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b) {
	return (a*1LL*b)%mod;
}
int n; ll x,y;
vp V;
int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %lld %lld",&n,&x,&y);
	int ans = 0;
	loop(i,n) {
		int l,r; scanf("%d %d",&l,&r);
		V.push_back(mp(l,-1));
		V.push_back(mp(r,1));
		ans = add(ans,mul(r-l,y));
	}
	sort(all(V));
	multiset<int> ended;
	for(auto p : V) {
		if(p.yy == 1) ended.insert(p.xx);
		else {
			if(ended.empty()) {
				ans = add(ans,x);
			}
			else {
				int t = *ended.rbegin();
				if((p.xx - t)*y < x){
					ended.erase(ended.find(t));
					ans = add(ans,mul(y,p.xx - t));
				}
				else ans = add(ans,x);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
