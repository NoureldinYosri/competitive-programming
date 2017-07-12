#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 101;
int vis[MAX][MAX];
int n,k;
int grid[MAX][MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&k);
	if(k > n*n) puts("-1");
	else{
		int i = 0,j = 0;
		for(;k > 1;j++,i += j/n,j %= n){
			if(vis[i][j]) continue;
			grid[i][j] = vis[i][j] = 1;
			k--;
			if(i != j){
				k--;
				grid[j][i] = vis[j][i] = 1;
			}
		}
		if(j > i) i++;
		if(k) grid[i][i] = 1;
		loop(i,n) loop(j,n) printf("%d%c",grid[i][j]," \n"[j ==n-1]);
	}
	return 0;
}
