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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

char S[1 << 20];
int n;
int len[1 << 20];
int R[1 << 20];
vi children[1 << 20];


pair<int,pi> solve(int root) {
//	cout << root << " " << children[root].size() << endl;
	if(children[root].empty()) return mp(1,pi(root,root));

	pair<int,pi> best (children[root].size(),pi(root,root));
	for(int l : children[root]) {
		auto tmp = solve(l);
		tmp.first += sz(children[root]) - 1;
		best = max(best,tmp);
	}
	if(root != n) {
		for(int l : children[root]) {
			int r = R[l];
			pi p (l,r);
			int tmp = sz(children[l]) + 2;
			pair<int,pi> aux(tmp,pi(l,r));
			best = max(best,aux);
		}
	}
	cout << root << ": " << best << endl;
	return best;
}

pair<int,pi> solve(){
	vi ST;
	loop(i,n){
		char c = S[i];
		if(c == '(') ST.push_back(i);
		else {
			assert(!ST.empty());
			int l = ST.back(); ST.pop_back();
			R[l] = i;
			len[l] = i-l+1;
			int p = ST.empty() ? n : ST.back();
			children[p].push_back(l);
		}
	}
	len[n] = n;
	auto ans = solve(n);
	cout << ans << endl;
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	scanf("%s",S);
	int s = 0;
	loop(i,n) {
		if(S[i] == '(') s++;
		else s--;
	}
	if(s != 0) {
		cout << "0\n1 1" << endl;
		return 0;
	}
	vector<int> V;
	int k = 0;
	loop(i,n) {
		char c = S[i];
		if(c == '(') {
			V.push_back(i);
			continue;
		}
		if(V.empty()){
			k = i+1;
			continue;
		}
		V.pop_back();
	}
	rotate(S,S + k,S + n);

	pair<int,pi> ans = solve();
	pi p = ans.second;
	int res = ans.first;
	p.first = ((p.first + k)%n + n)%n + 1;
	p.second = ((p.second + k)%n + n)%n + 1;
	cout << res << endl;
	cout << p.first << " " << p.second << endl;
	return 0;
}
