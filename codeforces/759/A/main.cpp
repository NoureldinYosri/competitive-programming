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

int A[1 << 20],n;
int vis[1 << 20];

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),A[i] --;
	int ans = 0;
	loop(i,n) if(!vis[i]){
		int u = i;
		ans++;
		while(!vis[u]){
			vis[u] = 1;
			u = A[u];		
		}
	}
	ans = (ans != 1) * ans;
	int x = 1;
	loop(i,n){
		int y ; scanf("%d",&y);
		x ^= y;
	}
	ans += x;
	cout << ans << endl;
	return 0;
}
