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

ll n,m,k,x,y;
ll q;

ll F[101][101];

void build(){
	if(n == 1){
		ll k = q/m;
		q %= m;
		for(int i = 1;i <= m;i++){
			F[1][i] = k + (i <= q);
		}
		return;
	}
	ll q_r = (2*n - 2)*m;
	k = q/q_r;
	q %= q_r;
	
	vector<pi> V;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			V.emplace_back(i, j);

	for(int i = n-1;i > 1;i--)
		for(int j = 1;j <= m;j++)
			V.emplace_back(i, j);
	
	loop(i, q){
		int x = V[i%sz(V)].first;
		int y = V[i%sz(V)].second;
		F[x][y]++;
	}

	for(int i = 1; i <= n; i++)
		for(int j = 1;j <= m;j++){
			int r = 2 - (i == 1 || i == n);
			F[i][j] += r*k;
		}
	
}

int main(){
	cin >> n >> m >> q >> x >> y;
	
	build();


	ll mn = LLONG_MAX, mx = LLONG_MIN, sergi = F[x][y];
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			mn = min(mn, (ll)F[i][j]), mx = max(mx, (ll)F[i][j]);
	

	cout << mx << " " << mn << " " << sergi << endl;
		
	
	
	return 0;
}
