/*
 TASK: latin
 LANG: C++
*/
#include <stdio.h>
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

int n;
int m;

ll bt(int i,int j,ll & row,ll & col,int x,int y){
	if(i==n-1)return 1;
	if(j==n)return bt(i+1,1,row,col,x + n,n);
	ll res=0,mask = (m << x) & row,k1,k2;
	for(;mask;mask -= LSOne(mask)){
		k1 = LSOne(mask);
		k2 = (k1 >> x) << y;
		if(col & k2){
			row ^= k1;
			col ^= k2;
			res += bt(i,j + 1,row,col,x,y + n);
			row |= k1;
			col |= k2;
		}
	}
	return res;
}

int main(){
	freopen("latin.in", "r", stdin);
	freopen("latin.out", "w", stdout);	
	scanf("%d",&n); ll f = 1; m = (1 << n) - 1;	
	loop(i,n - 1) f *= (i + 1);
	ll row,col;
	row = col = (1LL << (n*n)) - 1;
		
	loop(i,n){
		row ^= 1LL << i;
		col ^= (1LL << i) << (n*i);
		row ^= (1LL << i) << (n*i);
		col ^= 1LL << i;
	}	
	row ^= (1LL << 2) << n;
	col ^= (1LL << 2) << n;
	ll ans = 0;
	ans += bt(1,2,row,col,n,2*n);
	ans *= n - 2;
	row |= (1LL << 2) << n;
	col |= (1LL << 2) << n;
	
	row ^= 1LL << n;
	col ^= 1LL << n;
 
	ans += bt(1,2,row,col,n,2*n);
	printf("%lld\n",ans * f);
	return 0;
}
