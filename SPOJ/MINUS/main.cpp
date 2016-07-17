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


const int MAX = 30000;
int A[100];
int dp[100][MAX];
int nxt[100][MAX];
int n,target,offset = MAX >> 1;

int solve(int e,int tot){
	if(e == -1) return tot == target;
	if(dp[e][tot + offset] != -1) return dp[e][tot + offset];
	if(e) {
		if(solve(e - 1,A[e] - tot)){
			nxt[e][tot + offset] = 1;
			return dp[e][tot + offset] = 1;
		}
		else{
			nxt[e][tot + offset] = 0;	
			return dp[e][tot + offset] = solve(e - 1,A[e] + tot);
		}
	}
	else {
		nxt[e][tot + offset] = 1;
		return  dp[e][tot + offset] = solve(e - 1,A[e] - tot);
	}
}

void recons(int p,int carry,int ones,int zeros,vi & V){
	int cur = (V[p] + carry) & 1;	
	ones -= cur;
	zeros -= cur ^ 1;
	if(zeros == 0){
		loop(i,sz(V) - p) printf("%d\n",p + 1);
		return;
	}
	int j = p + 1;
	while((V[j] + carry) & 1) j++;
	ones -= j - p - 1;
	recons(j ,1 - carry,zeros,ones,V);	
	loop(i,j - p ) printf("%d\n",p + 1);
}

void recon(){
	int p = n - 1,sum = 0,ones = 0,zeros = 0;
	vi V;
	while(p >= 0){
		V.pb(nxt[p][sum + offset]);
		sum = A[p] + sum - 2*nxt[p][sum + offset]*sum;
		p--;
	}
	reverse(all(V));
	V.pop_back();
	int carry = 0;
	for(auto & v : V){
		v = (v + carry) & 1;
		carry = v & 1;
		ones += v;
		zeros += v ^ 1;
	}	
	//print(V,int);
	recons(0,0,ones,zeros,V);
}


int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&target);
		loop(i,n) scanf("%d",A + i);
		loop(i,n) loop(j,MAX) dp[i][j] = -1;		
		solve(n - 1,0);
		recon();
		puts("");
	}	
	return 0;
}
