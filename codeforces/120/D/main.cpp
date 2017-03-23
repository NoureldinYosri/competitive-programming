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

const int MAX = 55;
int G[MAX][MAX];
ll sum[MAX];
ll tot,A,B,C;
int n,m;

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	loop(i,n) loop(j,m) scanf("%d",&G[i][j]),tot += G[i][j];
	scanf("%lld %lld %lld",&A,&B,&C);
	if(A > B) swap(A,B);
	if(A > C) swap(A,C);
	if(B > C) swap(B,C);
	if(A + B + C != tot) puts("0");
	else{
		int ans = 0;
		loop(i,n) loop(j,m) sum[j] += G[i][j];
		loop(i,m) sum[i] += i ? sum[i - 1] : 0;
		for(int i = 1;i < m;i++) 
			for(int j = i+1;j < m;j++){
				ll s1 = sum[i - 1],s2 = sum[j - 1] - s1;
				if(s1 > s2) swap(s1,s2);
				if(s1 == A && s2 == B) ans++;
				else if(s1 == A && s2 == C) ans++;
				else if(s1 == B && s2 == C) ans++;
			}
		memset(sum,0,sizeof sum);
		loop(i,n) loop(j,m) sum[i] += G[i][j];
		loop(i,n) sum[i] += i ? sum[i - 1] : 0;
		for(int i = 1;i < n;i++) 
			for(int j = i+1;j < n;j++){
				ll s1 = sum[i - 1],s2 = sum[j - 1] - s1;
				if(s1 > s2) swap(s1,s2);
				if(s1 == A && s2 == B) ans++;
				else if(s1 == A && s2 == C) ans++;
				else if(s1 == B && s2 == C) ans++;
			}
		cout << ans << endl;
		cerr << ans << endl;
	}
	
	
	return 0;
}
