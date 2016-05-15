#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 2200;

int dp1[MAX][MAX],dp2[MAX][MAX];
char s[MAX],t[MAX];
int m,n;
vector<pi> V;

void solve(int st,int en){
	if(st > en) return;
	bool c = 0; int x = 0;
	loop(i,m + 1) if(dp1[i][en] > dp1[x][en]) x = i;
	loop(i,m + 1) {
		if(c){
			if(dp2[i][en] > dp2[x][en]) x = i,c = 1;
		}
		else if(dp2[i][en] > dp1[x][en]) x = i,c = 1;
	}
	int l = c ? dp2[x][en] : dp1[x][en];
	l = min(l,en - st + 1);
	if(l == 0){
		V.clear();
		return;
	}
	if(c) {
		int y = x - l + 1;
		x = m - x + 1;
		y = m - y + 1;
		V.pb(mp(y,x));
	}
	else V.pb(mp(x - l + 1,x));
	solve(st,en - l);
}

int main(){
	scanf("%s %s",s,t);
	m = strlen(s),n = strlen(t);
	range(i,1,m) range(j,1,n) if(s[i - 1] == t[j - 1]) dp1[i][j] = 1 + dp1[i - 1][j - 1];
	reverse(s,s + m);	
	range(i,1,m) range(j,1,n) if(s[i - 1] == t[j - 1]) dp2[i][j] = 1 + dp2[i - 1][j - 1];
	solve(1,n);
	if(V.empty()) puts("-1");
	else {
		printf("%lu\n",sz(V));
		reverse(all(V));		
		for(auto p : V) printf("%d %d\n",p.xx,p.yy);
	}
	return 0;
}

