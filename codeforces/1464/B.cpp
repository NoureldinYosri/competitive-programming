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

string s;
ll x, y;
vi pos;
int cnt[1 << 20][3];
int n;
 
ll solve(){
	int ctr[3] = {0, 0, 0};
	pos.clear();
	ll base = 0, running = 0;
	for(int i = 0; i < n; i++){
		if(s[i] == '0') {
			ctr[0]++;
			base += y*ctr[1];
			running += y*ctr[2];
		}
		if(s[i] == '1') {
			ctr[1]++;
			base += x*ctr[0];
		}
		if(s[i] == '?') {
			pos.push_back(i);
			ctr[2]++;
			running += x*ctr[0];
		}
		loop(j, 3) cnt[i][j] = ctr[j];
	}
	
//	cerr << s << " " << x << " " << y << " ... " << base << endl;
	ll ret = running;
//	cerr << "\t" << running + base << endl;

	for(int i : pos){
		running -= x*(cnt[i][0] + cnt[i][2] - 1);
		running -= y*(ctr[0] - cnt[i][0]);
		
		running += y*cnt[i][1];
		running += x*(ctr[1] + ctr[2] - cnt[i][1] - cnt[i][2]);

		ret = min(ret, running);
//		cerr << "\t" << i << " " << running << endl;
	}
	return ret + base;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> s >> x >> y;
	n = sz(s);
	ll ans = solve();
	reverse(all(s));
	swap(x, y);
	ans = min(ans, solve());
	cout << ans << endl;
	return 0;
}
