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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 1 << 20;
int n,m;
int dont[1 << 20];

int dp[MAX],nxt[MAX];
vi who[MAX];



void gcd(int a,int b,int & x,int & y){
	if(b == 0){
		a = 1;
		x = 1;
		y = 0;
		return;
	}
	gcd(b,a%b,x,y);
	int x_new = y;
	int y_new = (x - (a/b) * 1LL * y)%m;
	x = x_new;
	y = y_new;
	if(y < 0) y += m;
}

int get_inverse(int a){
	int x,y;
	gcd(a,m,x,y);
	return x;
}
int solve(int A,int B){
	int x = get_inverse(A);
	int g = __gcd(A,m);
	return (x*1LL*(B/g))%m;
}



int main(){

	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) {
		int x;
		scanf("%d",&x);
		dont[x] = 1;
	}

	for(int i = 1;i < m;i++) {
		if(!dont[i])
			who[__gcd(i,m)].pb(i);
	}
	for(int i = 1;i < m;i++){
		dp[i] += sz(who[i]);
		for(int j = i+i;j < m;j += i){
			if(dp[i] > dp[j]){
				dp[j] = dp[i];
				nxt[j] = i;
			}
		}
	}

	int mx = 0,g = 0,p = 1;
	for(int i = 1;i < m;i++)
		if(dp[i] > mx){
			mx = dp[i];
			g = i;
		}

	vi P;
	vi ans;
	while(g){
		print(who[g],int);
		for(int v : who[g])
			P.pb(v);
		g = nxt[g];
	}
	reverse(all(P));
	print(P,int);
	for(int v : P){
		int x = solve(p,v);
		ans.pb(x);
		p = v;
	}
	if(!dont[0]) ans.pb(0);
	printf("%d\n",sz(ans));
	for(int x : ans) printf("%d ",x);
	return 0;
}
