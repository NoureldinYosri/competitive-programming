#ifdef INPROGRESS
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include "my_math.h"
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

bool cond(int x) {
	string s = to_string(x);
	s = s.substr(1) + s[0];
	int y;
	sscanf(s.c_str(),"%d",&y);
	return y%x == 0;
}

bool is_simple(int x) {
	string s = to_string(x);
	sort(all(s));
	return unique(all(s)) - s.begin() == 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	ll ans = 142857 + 285714;
	int ds = 9*10/2;
	ll coef = 11 + 111 + 1111;
	for(int l = 5;l < 100;l++){
		coef += 11111;
		coef %= 100000;
	}
	ans += coef * ds;
	ans %= 100*1000;
	cout << ans << endl;
	return 0;
}
#endif
