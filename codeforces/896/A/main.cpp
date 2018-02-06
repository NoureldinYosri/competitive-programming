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

string s0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
string pat = "What are you doing while sending \"$\"? Are you busy? Will you send \"$\"?";
vl f;

void init(){
	f.pb(sz(s0));
	while(f.back() < 1e18)
		f.pb(f.back()*2 + sz(pat) - 2);
}

string pref = "What are you doing while sending ";

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	init();
	int q; scanf("%d",&q);
	while(q--) {
		int n; ll k;
		scanf("%d %lld",&n,&k);
		while(n >= sz(f) && k > sz*pref)) {
			k -= sz(pref);
			n--;
		}
		if(n >= sz(f)) {
			assert(k <= sz(pref));
			assert(k > 0);
			putchar(pref[k-1])
		}
		else {

		}
	}
	return 0;
}
