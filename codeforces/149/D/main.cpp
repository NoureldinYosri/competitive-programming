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

const int MAX = 705,mod = 1e9 + 7;
char S[MAX];
int pref[MAX],E[MAX],n,ac;
int dp[MAX][MAX][3][3];
vp cand;
int match[MAX];

#define add(a,b) (ac = a+b , ac - ((ac >= mod) ? mod : 0))
#define mul(a,b) ((a*1LL*b)%mod)


bool valid(int s,int e){
	if(s > e) return 1;
	if(S[s] == ')') return 0;
	return e <= E[s];
}


int solve(int s,int e,int left_color,int right_color) {
	if(s > e) return 1;
	int & ret = dp[s][e][left_color][right_color];
	if(ret != -1) return ret;
	ret = 0;
	int k = match[s];
	for(auto p : cand){
		int c1 = p.xx,c2 = p.yy;
		if(c1 && c1 == left_color) continue;
		if(k==e && c2 && c2 == right_color) continue;
		if(!valid(s+1,k-1) || !valid(k+1,e)) continue;
		int f1 = solve(s+1,k-1,c1,c2);
		int f2 = solve(k+1,e,c2,right_color);
//			cerr << s+1 << " " << k-1 << " " << c1 << " " << c2 << " -> " << f1 << endl;
//			cerr << k+1 << " " << e << " " << c2 << " " << right_color << " -> " << f2 << endl;
//			cerr << endl;
		ret = add(ret,mul(f1,f2));
	}

	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s",S);
	n = strlen(S);
	vi ST;
	loop(i,n) {
		if(S[i] == '(') ST.push_back(i);
		else {
			match[ST.back()] = i;
			ST.pop_back();
		}
	}
	for(int i = 0;i < n;i++) if(S[i] == '('){
		int j = i,s = 0;
		while(j < n && s >= 0) {
			s += (S[j] == '(') - (S[j] == '(');
			if(s < 0) break;
			if(j+1==n) break;
			j++;
		}
		E[i] = j;
	}
	loop(c1,3) loop(c2,3) if((!c1 || !c2) && (c1 != c2)) {
//		cerr << c1 << " " << c2 << endl;
		cand.pb(mp(c1,c2));
	}
	memset(dp,-1,sizeof dp);
	cout << solve(0,n-1,0,0) << endl;

	return 0;
}
