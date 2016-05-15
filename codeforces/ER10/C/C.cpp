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

int n,m,a,b;
int A[1 << 20];
int id[1 << 20];
int flag[1 << 20];

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i),id[A[i]] = i + 1,flag[i + 1] = n;
	loop(i,m){
		scanf("%d %d",&a,&b);
		a = id[a],b = id[b];
		if(a > b) swap(a,b);
		flag[a] = min(flag[a],b - 1);
	}
	ll ans = 0; int e = n;
	for(int i = n;i;i--){
		e = min(e,flag[i]);
		ans += max(0,e - i + 1);
	}
	cout << ans << endl;
	return 0;
}
