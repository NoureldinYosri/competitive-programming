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

int A[65537],B[65537],n,m;
int BIT[65537 + 1];

void update(int p){
	for(;p <= m;p += LSOne(p)) BIT[p]++;
}

int get(int p){
	int ret = 0;
	for(;p;p -= LSOne(p)) ret += BIT[p];
	return ret;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),B[i] = A[i];
	sort(B,B + n);
	m = unique(B,B + n) - B;
	ll ans = 0;
	loop(i,n){
		A[i] = lower_bound(B,B + m,A[i]) - B + 1;
		ans += i - get(A[i]);
		update(A[i]);
	}		
	cout << ans << endl;
	return 0;
}
