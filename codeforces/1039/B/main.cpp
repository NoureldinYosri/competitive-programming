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

ll n;
int k;

bool read(){
	string s;
	cin >> s;
	return s == "Yes";
}

void write(ll s,ll e) {
	cout << s << " " << e << endl;
}

bool ask(ll s,ll e) {
	write(s,e);
	return read();
}

void solve(ll s,ll e) {
	s = max(s,1LL);
	e = min(e,n);
	if(s == e) {
		ask(s,e);
		return;
	}
	ll len = e-s+1;
	ll width = 4*k+1;
	if(len > width) {
		int m = s + (e-s)/2;
		if(ask(s,m)) return solve(s-k,m+k);
		else return solve(m-k,e+k);
	}
	else {

	}
}

int main(int argc,char **argv){
	cin >> n >> k;
	solve(1,n);
	return 0;
}
