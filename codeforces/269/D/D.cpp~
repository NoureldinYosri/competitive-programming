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

int A[1 << 20],B[1 << 20],n,m;
int RANK[1 << 20],ord[1 << 20],h;

bool cmp0(const int & a,const int & b){return RANK[a] < RANK[b];}
bool cmp1(const int & a,const int & b){
	if(RANK[a] != RANK[b]) return RANK[a] < RANK[b];
	int a_ = min(n,a + (1 << h) - 1),b_ = min(n,b + (1 << h) - 1);
	return RANK[a_] < RANK[b_];	
}

bool greater(int a,int b,int c){
	loop(i,m - 1){
		if(A[a + i] < A[b + i]) a++,b++;
		else if(c && A[a + i] == A[b + i]) a++,b++;
	} 
	return 
}

int f(){
	int u = 0,v = n - 1,ans;
	while(u < v){
		int m = (u + v) >> 1;
		if(cmp
	}
}

int main(){
	scanf("%d %d",&n,&m);
	if(m > n) puts("0");
	else if(m == 1) printf("%d\n",n);
	else{
		loop(i,n) scanf("%d",A + i);
		loop(i,n - 1) A[i] = A[i + 1] - A[i];
		loop(i,m) scanf("%d",B + i);
		loop(i,m - 1) B[i] = B[i + 1] - B[i];
		A[n] = B[m] = INT_MIN;
		loop(i,n) RANK[i] = A[i],ord[i] = i;
		sort(ord,ord + n,&cmp0);
		for(h = 0;(1 << h) < n;h++) sort(ord,ord + n,&cmp1);
		printf("%d\n",f());
	}
	return 0;
}
