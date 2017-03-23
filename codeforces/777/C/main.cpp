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

vector<vi> G,S,mx;
int n,m;

int main(){
	scanf("%d %d",&n,&m);
	G = vector<vi>(n,vi(m,0));
	S = vector<vi>(n,vi(m,0));
	mx = vector<vi>(n,vi(m,0));
	loop(i,n) loop(j,m) scanf("%d",&G[i][j]);
	for(int i = 1;i < n;i++){
		loop(j,m) {
			if(G[i - 1][j] <= G[i][j]) S[i][j] = S[i - 1][j] + 1;
			else S[i][j] = 0;
			mx[i][j] = max(S[i][j],j ? mx[i][j - 1] : 0);
		}
	//	print(S[i],int);
	}
	int k; scanf("%d",&k);
	while(k--){
		int l,r; scanf("%d %d",&l,&r);
		l--,r--;
		puts((mx[r][m-1] >= (r - l)) ? "Yes" : "No"); 
	}
	
	
	return 0;
}
