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

	int n; 
vector<string> ask(int l,int r){
	cout << "? " << l << " " << r << endl;
	fflush(stdout);
	vector<string> ret;
	string s;
	int m = r-l+1;
	int cnt = m*(m + 1)/2;
	while(cnt > 0){
		cin >> s;
		cnt --;
		ret.emplace_back(s);
	}
	return ret;
}

vi G[128];


vi euler(){
	int root = 0;
	for(int c = 'a';c <= 'z';c++){
		if(G[c].empty()) continue;
		if(!root) root = c;
		else if(sz(G[c])%2) root = c;
	}

	vi ST,tour;
	ST.push_back(root);
	while(!ST.empty()){
		int u = ST.back();
		if(G[u].empty()) {
			tour.push_back(u);
			ST.pop_back();
			continue;
		}
		int v = G[u].back(); G[u].pop_back();
		G[v].erase(find(all(G[v]),u));
		ST.push_back(v);
	}
	return tour;
}

vi getCnts(string s) {
	vi f(26,0);
	for(char c : s)
		f[c-'a']++;
	return f;
}

bool check(const string t, const map<vi,int> & cnt){
	map<vi,int> tmp;
	for(int i = 0;i < sz(t);i++){
		vi f(26,0);
		for(int j = i;j < sz(t);j++){
			f[t[j]-'a']++;
			tmp[f]++;
		}
	}
	for(auto p : cnt) if(p.second != tmp[p.first]) return 0;
	return 1;
}

vector<string> getCand(string t,vector<string> S){
	map<vi,int> cnt;
	for(string s : S)
		cnt[getCnts(s)]++;
	
	vector<string> ret;
	loop(k, sz(t)){
		if(check(t, cnt)) ret.push_back(t);
		rotate(t.begin(), t.begin() + 1, t.end());
	}
	reverse(all(t));
	loop(k, sz(t)){
		if(check(t, cnt)) ret.push_back(t);
		rotate(t.begin(), t.begin() + 1, t.end());
	}
	return ret;
}

vector<string> build(int s,int e){
	auto S = ask(s,e);
	if(sz(S) == 1) return S;
	for(int c = 'a';c <= 'z';c++)
		G[c].clear();
	for(string s : S){
		if(sz(s) != 2) continue;
		int c1 = s[0], c2 = s[1];
		G[c1].push_back(c2);
		G[c2].push_back(c1);
	}
	vi tour = euler();
	string t = "";
	for(int c : tour)
		t.push_back((char)c);
	cout << "tour is " << t << " " << sz(t) << " " << e-s+1 << endl;
	return getCand(t, S);
}

int main(){
	cin >> n;
	if(n == 1) {
		string s = build(1,n)[0];
		cout << "! " << s << endl;
		return 0;
	}
	auto A = build(1,n/2);
	print(A,string);
	auto B = build(n/2+1,n);
	print(B,string);
	auto C = build(1,n);
	print(C,string);
	for(string a : A)
		for(string b : B)
			for(string c : C)
				if(a+b == c){
					cout << "! " << c << endl;
					return 0;
				}
	assert(0);
	return 0;
}
