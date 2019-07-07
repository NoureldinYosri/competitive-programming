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

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	ll a,b,ab; cin >> a >> b >> ab;
	ll ans = 2*ab;
	if(a) ans = max(ans,1LL);
	if(b) ans = max(ans,1LL);
	if(a&&b) ans = max(ans,2LL);
	if(a>1 && b) ans = max(ans,3LL);
	if(b>1 && a) ans = max(ans,3LL);
	ll len = 2*ab;
	if(b) len++;
	if(a) len++;
	ans = max(ans,len);
	len = 2*ab + 2*min(a,b);
	ll m = min(a,b);
	a -= m;
	b -= m;
	if(a) len++;
	if(b) len++;
	ans = max(ans,len);
	cout << ans << endl;
	return 0;
}
