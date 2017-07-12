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
#define popcnt(x) __builtin_popcount(x)
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

string bin(ll n){
	if(n == 0) return "0";
	string ret ;
	while(n){
		ret += (n & 1) + '0';
		n >>= 1;
	}
	reverse(all(ret));
	return ret;
}

int solve(ll lim){
	if(lim == -1) return 0;
	string s = bin(lim);
	int ret = 0;
	for(int lenA = 1;lenA <= sz(s);lenA++){
		for(int lenB = 0;lenB <= sz(s) - lenA;lenB++){
			deque<string> dq(sz(s),"0");
			string T [2] = {string(lenA,'1'),string(lenB,'0')};
			int cur = 0,siz = 0;
			for(;siz + sz(T[cur]) <= sz(s);cur ^= 1){
				loop(i,sz(T[cur])) dq.pop_front();
				dq.pb(T[cur]);
				string aux;
				for(string t : dq) aux += t;
				assert(sz(aux) == sz(s));
				if(aux > s) break;
				siz += sz(T[cur]);
				if(siz < lenA + lenB) continue;
				ret++;
				//cerr << aux << " " << lenA << " " << lenB << endl;
				if(lenB == 0) break;
			}
		}
	}
	return ret;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	ll A,B; cin >> A >> B;
	cout << solve(B) - solve(A - 1) << endl;
	return 0;
}
