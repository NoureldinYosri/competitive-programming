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

int n, m, k;

string path;

void create(int i, int j){
	if(i && j) {
		path.pb('U');
		path.pb('D');
	}
	if(j+1 < m) {
		path.pb('R');
		create(i, j+1);
	}
	if(j) {
		path.pb('L');
		return;
	}
	if(i+1 < n){
		path.pb('D');
		create(i+1, 0);
	}
	if(i) path.pb('U');
}

vector<pair<int, string>> res;

void compress(){
	for(int i = 0;i < sz(path);){
		string tmp;
		while(i < sz(path) && sz(tmp) < 3)
			tmp.pb(path[i++]);
		if(!res.empty() && res.back().second == tmp) res.back().first++;
		else res.emplace_back(1, tmp);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> m >> k;
	create(0, 0);
	if(sz(path) < k) puts("NO");
	else {
		puts("YES");
		path = path.substr(0, k);
		compress();
		printf("%d\n", sz(res));
		assert(sz(res) <= 3000);
		loop(i, sz(res)) printf("%d %s\n", res[i].first, res[i].second.c_str());
	}
	return 0;
}
