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
#define pl pair<ll,ll>
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

const int mod = 1e9+ 7 ,MAX = 20000 + 10;
char buffer[1 << 20];


bool present[MAX];
int change[MAX],N,start[MAX];
int dp[MAX][1001];

int get_start(string s1,string s2){
	if(s1 == "Candidate") return 400;
	if(s1 == "International") return (s2 == "Master") ? 600 : 800;
	char ord [] = "NPSECMIGIL";
	//assert(s2 == "#");
	loop(i,10)
		if(ord[i] == s1[0])
			return i*100;
	assert(0);
}

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

void get_bounds(int rating,int st,int & l,int & r){
	if(rating + 100 < st) {
		l = r = -1;
		return;
	}
	else if(st + 100 <= rating - 100) {
		l = r = -1;
		return;
	}
	else if(rating < st) {
		l = st;
		r = rating + 100;
	}
	else if(st + 100 <= rating) {
		l = rating - 100;
		r = st + 99;
	}
	else {
		l = st;
		r = st + 99;
	}
	l = max(l,0);
	r = min(r,1000);
	assert(l <= r);
}

void solve(){
	range(i,0,1000) dp[N][i] = i+1;
	for(int i = N-1;i >= 0;i--)
		for(int rating = 0;rating <= 1000;rating++) {
			dp[i][rating] = 0;
			int l,r;
			if(present[i]) {
				int tr = rating + change[i];
				if(start[i] <= rating + change[i] && rating + change[i] < start[i] + 100)
					dp[i][rating] = add(dp[i + 1][tr],tr ? -dp[i + 1][tr - 1] : 0);
			}
			else{
				get_bounds(rating,start[i],l,r);
				if(l != -1) dp[i][rating] = add(dp[i + 1][r],l ? -dp[i + 1][l - 1] : 0);
			}
			dp[i][rating] = add(dp[i][rating],rating ? dp[i][rating - 1] : 0);
		}
	printf("%d\n",dp[0][0]);
}

int solve(int i,int rating) {
	if(i == N) return 1;
	if(dp[i][rating] != -1) return dp[i][rating];
	int & ret = dp[i][rating]; ret = 0;
	int l = -100,r = 100;
	if(present[i]) l = r = change[i];
	for(;l <= r;l++) {
		int trc = rating + l;
		if(trc < start[i]) continue;
		if(start[i] + 100 <= trc) continue;
		ret = add(ret,solve(i + 1,rating + l));
	}
	return ret;
}

int main(){
	freopen("joyfull.in", "r", stdin);
	int T;
	fgets(buffer,MAX,stdin);
	sscanf(buffer,"%d",&T);
	while(T--){
		fgets(buffer,MAX,stdin);
		sscanf(buffer,"%d",&N);
		int lst = 0;
		loop(i,N) {
			fgets(buffer,MAX,stdin);
			vector<string> V;
			char to_deli[] = "Became";
			for(int k = 0,L = strlen(buffer);k <= L-6;k++){
				bool cond = 1;
				loop(j,6) cond &= buffer[k + j] == to_deli[j];
				if(cond) {
					loop(j,6) buffer[k + j] = ' ';
				}
			}
			for(char *token = strtok(buffer," \n");token;token = strtok(0," \n"))
				V.pb(string(token));
			if(sz(V) == 2) V.pb("#");
			assert(sz(V) == 3);
			if(V[1] == "-") start[i] = lst;
			else lst = start[i] = get_start(V[1],V[2]);
			if(V[0] == "?") present[i] = 0;
			else {
				present[i] = 1;
				int sgn = 1;
				if(V[0][0] == '-') sgn = -1,V[0][0] = ' ';
				sscanf(V[0].c_str(),"%d",change + i);
				change[i] *= sgn;
			}
//			if(present[i]) cerr << change[i] << " ";
//			else cerr << "? ";
//			cerr << start[i] << endl;
		}
		solve();
//		memset(dp,-1,sizeof dp);
//		cout << solve(0,0) << endl;
	}
	return 0;
}
