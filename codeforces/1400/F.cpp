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

const int MAXN = 1024, MAXM = 20*MAXN;
char txt[MAXN];
int n, X;
vi divs;

int dp[MAXN][MAXM];

const vi phi;

bool isGood(const vi & S){
	if(S.empty() || S.back() != X) return true;
	int msk = 1;
	for(int s : S){
		for(int d : divs) if(d <= s && ((msk >> (s - d)) & 1)) return true;		
		msk |= 1 << s;
	}
	return false;
}
map<int, vi> i2v;
int trans[MAXM][10];

pair<int, bool> getId(const vi & S){
	static map<vi, int> mem;
	if(mem.count(S)) return mp(mem[S], false);
	int res = sz(mem);
	i2v[res] = S;
	return mp(mem[S] = res, true);
}

pair<int, bool> getNext(const vi & S, int d){
	vi tmp; tmp.pb(0);
	for(int s : S) tmp.pb(s);
	for(int & s : tmp) s += d;
	while(!tmp.empty() && tmp.back() > X) tmp.pop_back();
	if(isGood(tmp)){
		return getId(tmp);
	} else {
		return mp(-1, false);
	}
}

void bt(const vi & S){
	int cur = getId(S).first;
	for(int d = 2; d <= 9; d++){
		auto [id, isNew] = getNext(S, d);
		trans[cur][d] = id;
		if(isNew) bt(i2v[id]);
	}
}
int getNext(int seqId, int d){
	static map<int, int> mem[10];
	if(mem[d].count(seqId)) return mem[d][seqId];
	return mem[d][seqId] = getNext(i2v[seqId], d).first;
}

int solve(int i, int seqId){
	if(i == n) return 0;
	int & ret = dp[i][seqId];
	if(ret != -1) return ret;
	if(txt[i] == '1' || (txt[i] - '0') > X) return ret = solve(i + 1, 0);
	int d = txt[i] - '0';
	ret = solve(i + 1, seqId) + 1;
	if(trans[seqId][d] != -1) ret = min(ret, solve(i + 1, trans[seqId][d]));
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> txt >> X;
	n = strlen(txt);
	if(X == 1){
		cout << count(txt, txt + n, '1') << endl;
		return 0;
	}
	for(int d = 1; d < X; d++) if(X%d == 0) divs.pb(d);
	getId(phi);
	bt(phi);
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << endl;
	
	return 0;
}
