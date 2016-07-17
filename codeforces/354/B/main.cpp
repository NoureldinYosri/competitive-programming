#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAX = 1 << 10;

vi R[11];

int n,t;

void fill(int p,int r = 1,int v = MAX){
	if(r == n + 1 || v == 0) return;
	R[r][p] += v;
	if(R[r][p] >= MAX) {
		int q = R[r][p] - MAX;
		R[r][p] = MAX;	
		fill(p,r + 1,q >> 1);
		fill(p + 1,r + 1,q >> 1);
	}
}

int main(){
	loop(i,11) R[i] = vi(i,0);
	cin >> n >> t;	
	while(t--) fill(0);
	int ans = 0;
	loop(i,11) loop(j,i) if(R[i][j] == MAX) ans++;
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
