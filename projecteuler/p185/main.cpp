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

vector<string> S;
vi C;
string res;
vi score;
vi ord;

bool done(){
	int n = sz(S);
	for(int i = 0;i < n;i++)
		if(score[i] != C[i])
			return 0;
	return 1;
}

bool update_belief(){
	int n = sz(S),m = sz(res);
	for(int i = 0;i < n;i++) {
		score[i] = 0;
		for(int j = 0;j < m;j++)
			score[i] += res[j] == S[i][j];
		if(score[i] > C[i]) return 0;
	}
	return 1;
}

vi getCand(){
	int mn = 3,n = sz(S);
	for(int i = 0;i < n;i++) {
		if(C[i] != score[i])
			mn = min(mn,C[i] - score[i]);
	}
	vi ret;
	loop(i,sz(score)) if((C[i] - score[i]) == mn) ret.pb(i);
	return ret;
}

vi getRem(){
	int n = sz(res);
	vi ret;
	loop(i,n) if(res[i] == '#') ret.pb(i);
	return ret;
}

vector<vi> getToMatch(vi & idx,int sc){
	assert(sc > 0);
	assert(sc <= 3);
	vector<vi> ret;
	if(sc == 1) {
		for(int x : idx)
			ret.pb(vi{x});
	}
	else if(sc == 2) {
		int n = sz(idx);
		for(int i = 0;i < n;i++)
			for(int j = i+1;j < n;j++)
				ret.pb(vi({idx[i],idx[j]}));
	}
	else {
		int n = sz(idx);
		for(int i = 0;i < n;i++)
			for(int j = i+1;j < n;j++)
				for(int k = j+1;k < n;k++)
					ret.pb(vi({idx[i],idx[j],idx[k]}));
	}
	return ret;
}

vi getOrd(){
	static int cnt [10] = {0};
	vi posScore(sz(res));
	for(int i = 0;i < sz(res);i++) if(res[i] == '#'){
		loop(j,10) cnt[j] = 0;
		for(int j = 0;j < sz(S);j++)
			cnt[(int)(S[j][i] - '0')]++;
		int ctr = 0;
		loop(j,10) ctr = max(ctr,cnt[j]);
		posScore[i] = ctr;
	}
	vi ord;
	loop(i,sz(res)) ord.pb(i);
	sort(all(ord),[posScore](const int & a,const int & b){
		return posScore[a] < posScore[b];
	});
	return ord;
}

bool bt(int d){
	cerr << res << endl;
	if(!update_belief()) return 0;
	if(d == sz(res)) return done();
	int idx = ord[d];
	vector<pair<int,char> > V(10);
	for(char c = '0';c <= '9';c++) {
		int w = 0;
		for(int i = 0,n = sz(S);i < n;i++) {
			int ns = score[i];
			if(S[i][idx] == c)
				ns++,w++;
			if(ns > C[i]) w = INT_MIN;
		}
		V[(int)(c - '0')] = mp(w,c);
	}
	sort(all(V));
	reverse(all(V));
	for(auto p : V) {
		res[idx] = p.yy;
		if(bt(d + 1)) return 1;
	}
	res[idx] = '#';
	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	string guess,correct;
	char c;
	int cnt;
	while(cin >> guess >> c >> cnt >> correct){
		S.pb(guess);
		C.pb(cnt);
		score.pb(0);
	}
//	print(S,string);
//	print(C,int);
	res = string(sz(S[0]),'#');
	ord = getOrd();

	if(bt(0)) cerr << res << endl;
	else cerr << "failed" << endl;
	return 0;
}
