#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 5010;
int good[MAX],bad[MAX],gcd[MAX],A[MAX],P[MAX],n,m;
int good_gcd[MAX],bad_gcd[MAX];
int dp[MAX][MAX];
map<int,pi> dp2;

void f(int N,int & good,int & bad){
	if(dp2.find(N) != dp2.end()){
		good = dp2[N].xx;
		bad = dp2[N].yy;
		return;
	}
	int n = N;	
	good = bad = 0;
	for(ll j = 2;j*j <= N;j++)
		if(N%j == 0){
			bool c = binary_search(P,P + m,j);
			while(N%j == 0){
				good += !c;
				bad += c;
				N /= j;				
			}
		}
	if(N != 1){
		bool c = binary_search(P,P + m,N);
		good += !c;
		bad += c;
	}
	dp2[n] = mp(good,bad);
}


int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,m) scanf("%d",P + i);
 	sort(P,P + m);
	int g = 0;	
	loop(i,n){
		gcd[i] = g = __gcd(g,A[i]);
		f(A[i],good[i],bad[i]);
		f(g,good_gcd[i],bad_gcd[i]);
	}
	
	gcd[n] = 1;
	loop(p,n)
		for(int r = p;r <= n;r++){
			dp[p][r] = good[p] - good_gcd[r] - bad[p] + bad_gcd[r] + (p ? dp[p-1][r] : 0);
			dp[p][r] = max(dp[p][r],good[p] - good_gcd[p] - bad[p] + bad_gcd[p] + (p ? dp[p-1][p] : 0));
		}
	cout << dp[n-1][n] << endl;
	return 0;
}
