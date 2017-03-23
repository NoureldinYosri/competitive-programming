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

const int MAX = 1024;
int G[MAX][MAX],m,n,k,p;
ll sum[MAX << 1],X,Y;



ll f[1 << 20],g[1 << 20];

int main(){
	scanf("%d %d %d %d",&m,&n,&k,&p);
	loop(i,m) loop(j,n) scanf("%d",&G[i][j]);
	loop(i,m) loop(j,n) sum[i] += G[i][j],sum[j + m] += G[i][j];
	multiset<ll> row,col;
	loop(i,m) row.insert(sum[i]);
	loop(i,n) col.insert(sum[i + m]);
	loop(i,k){
		ll val = *row.rbegin();	
		f[i + 1] = val + f[i];
		row.erase(row.find(val));
		row.insert(val - n*1LL*p);
	}	
	loop(i,k){
		ll val = *col.rbegin();	
		g[i+1] = val + g[i];
		col.erase(col.find(val));
		col.insert(val - m*1LL*p);
	}	
	ll ans = LLONG_MIN;
	loop(i,k+1){
	//	cerr << i << " f = " << f[i] << " g = " <<  g[k - i] << " aux " << (k - i)*1LL*i*1LL*p << endl; 
		ans = max(ans,f[i] + g[k - i] - (k - i)*1LL*i*1LL*p);
	}
	cout << ans << endl;
	return 0;
}
