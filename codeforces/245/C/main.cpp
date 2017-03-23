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

const int MAX = 1001;
int A[MAX],n;

int solve(int p){
	if(2*p + 1 > n) return 0;
	int ret = solve(2*p);
	ret += solve(2*p + 1);
	int k = max(A[2*p],A[2*p + 1]);
	ret += k;
	A[p] = max(0,A[p] - k);
	if(p == 1) ret += A[p];
	return ret;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i + 1);
	if(n <= 2){
		puts("-1");
		return 0;
	}
	else {
		vi vis(n+1,0);
		queue<int> q; q.push(1);
		while(!q.empty()){
			int u = q.front(); q.pop();
			vis[u] = 1;
			if(2*u + 1 <= n) q.push(2*u),q.push(2*u + 1);
		}		
		bool can = 1;
		range(i,1,n) can &= vis[i];
		if(can)	printf("%d\n",solve(1));  
		else puts("-1");
	}	
	
	return 0;
}
