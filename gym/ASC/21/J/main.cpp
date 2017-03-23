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

int dp[5001],aux[2][5001];
int mod,L;
set<pi> demand;
map<pi,int> CF;

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int mul(int x,int y){
	return (x*1LL*y)%mod;
}

int C(int n,int k){
	if(k == 0 || k == n) return 1%mod;
	return CF[mp(n,k)];
}

int main(){
	freopen("twothree.in","r",stdin);
	freopen("twothree.out","w",stdout);
	scanf("%d %d",&L,&mod);
	if(L == 1){
		puts((mod == 1) ? "0" : "1");
		return 0;
	}
	dp[1] = 1;
	range(i,2,L){
		for(int three = 0;three <= i/3;three++){
			int r = i - three*3;
			if(r & 1) continue;
			demand.insert(mp(three + r/2,three));
		}
	}
	int one = 1,other = 0;
	range(i,0,5000){
		aux[one][0] = aux[one][i] = 1;
		range(j,1,i-1){
			aux[one][j] = add(aux[other][j - 1],aux[other][j]);
			if(demand.find(mp(i,j)) != demand.end()){
				CF[mp(i,j)] = aux[one][j];
			}
		}
		swap(one,other);
	}
	dp[1] = 1;
	range(i,2,L){
		for(int three = 0;three <= i/3;three++){
			int r = i - three*3;
			if(r & 1) continue;
			dp[i] = add(dp[i],mul(C(three + r/2,three),dp[r/2 + three]));
		}
	}
	cout << dp[L] << endl;
	return 0;
}
