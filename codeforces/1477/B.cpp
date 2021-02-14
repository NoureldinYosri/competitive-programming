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

char txt[1 << 20], patt[1 << 20];
int n, m;
struct quanta{
	int l, cnt, val;
};

map<int, quanta> info;

bool isMatch(int a, int b){
	if(max(a, b) == 2) return true;
	return a == b;
}

bool check(int l, int r, int c){
	auto ptr = info.lower_bound(l);
	for(; ptr != info.end() && ptr->second.l <= r; ptr++){
		auto q = ptr->second;
		if(isMatch(q.val, c)) continue;
		int need = min(r, ptr->first) - max(l, q.l) + 1;
		if(need > q.cnt) return false;
	}
	return true;
}

int getLen(int s, int e){
	return e-s+1;
}

void change(int l, int r, int c){
	while(true){
		auto ptr = info.lower_bound(l);
		if(ptr == info.end()) break;
		auto q = ptr->second;
		int s = q.l, e = ptr->first;
		if(s > r) break;
		if(s <= l && r <= e){
			info.erase(ptr);
			info[l - 1] = quanta({s, , q.val});
			info[e] = quanta({r + 1, , q.val});
			break;
		}
		if(l <= s) {
			if(e <= r){
				info.erase(ptr);
			} else {
				info.erase(ptr);
				int need = min(r, ptr->first) - max(l, q.l) + 1;
				need *= !isMatch(q.val, c);
				assert(need <= q.cnt);
				q.cnt -= need;
				q.l = r + 1;
				q.cnt = min(q.cnt, getLen(q.l, e));
				info[e] = q;
			}
		} else {
			int need = min(r, ptr->first) - max(l, q.l) + 1;
			need *= !isMatch(q.val, c);
			assert(need <= q.cnt);
			q.cnt -= need;
			q.cnt = min(q.cnt, getLen(q.l, l-1));
			info.erase(ptr);
			info[l-1] = q;
		}
	}
	int len = r - l + 1;
	int cnt = (len + 1)/2 - 1;
	info[r] = quanta({l, cnt, c});
	cerr << "new is " << l << " " << r << " " << pi(cnt, c) << endl;
	cerr << "{" << endl;
	for(auto p : info){
		cerr << "\t" << pi(p.second.l, p.first) << ": " << pi(p.second.cnt, p.second.val) << endl;
	}
	cerr << "}" << endl;
}

bool solve(int l, int r){
	int ctr = 0, choice = -1;
	loop(c, 2){
		if(check(l, r, c)) ctr++, choice = c;
	}
	if(ctr == 0) return false;
	if(ctr == 2) choice = 2;
	change(l, r, choice);
	return true;
}

bool solve(){
	loop(i, n) {
		if(check(i, i, patt[i] == '1')) {
			change(i, i, patt[i] == '1');
		} else {
			return false;
		}
	}
	return true; 
}

void tc(){
	scanf("%d %d", &n, &m);
	scanf("%s %s", txt, patt);
	info.clear();
	loop(i, n) {
		info[i] = quanta({i, 0, txt[i] == '1'});
	}
	bool yes = true;
	loop(q, m){
		int l, r; scanf("%d %d", &l, &r);
		l--, r--;
		if(yes) 
			yes = solve(l, r);
	}
	if(yes) yes = solve();
	puts(yes ? "YES" : "NO");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
