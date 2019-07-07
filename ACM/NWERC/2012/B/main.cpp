#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
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
using namespace std;

const int MAX = 3478761;
double dp [MAX][5];
char vis_num[MAX];
int n,k,visID;
ll CT[1024][1024];

void init(){
	for(int n = 0;n < 1024;n++) {
		CT[n][0] = CT[n][n] = 1;
		for(int k = 1;k < n;k++)
			CT[n][k] = CT[n-1][k] + CT[n-1][k-1];
	}
}

auto get_sum = [](const vi & S) {
	int r = 0;
	for(const int & x : S)
		r += x;
	return r;
};

auto C = [](const int & n,const int & k) {
	if(n < 0 || k > n || k < 0) return 0LL;
	int rk = min(k,n - k);
	assert(n < 1024);
	return CT[n][rk];
};

auto get_idx = [](const vi & A,int s) {
	int r = 0;
//	if(s)
		r = C(n+s-1,s-1);
	for(int i = 0;i+1 < n;i++) {
		int m = A[i],k = n-1-i;
//		if(m)
			r += ((k+s)*C(k+s-1,s) - (k-m+s)*C(k-m+s-1,s-m))/k;
		s -= A[i];
	}
//	cerr << r << " ... " ; print(A,int);
	return r;
};


void solve(vi & A,int s,int pos){
	if(s == k) {
		int mx = *max_element(all(A));
		int ctr = count(all(A),mx);
		fill(dp[pos],dp[pos] + n,0.0);
		for(int i = 0;i < n;i++)
			if(A[i] == mx)
				dp[pos][i] = 1.0/ctr;
		return;
	}
	if(vis_num[pos] == visID) return;
	vis_num[pos] = visID;
	fill(dp[pos],dp[pos] + n,0.0);
	for(int i = 0;i < n;i++) {
		int c = A[i];
		double p = c*1.0/s;
		A[i]++;
		int tmp = get_idx(A,s+1);
		solve(A,s+1,tmp);

		A[i]--;

		for(int j = 0;j < n;j++)
			dp[pos][j] += p*dp[tmp][j];
	}
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	while(scanf("%d %d",&n,&k) == 2) {
		visID++;
		vi A(n);
		loop(i,n) scanf("%d",&A[i]);
		int s = get_sum(A);
		int pos = get_idx(A,s);
		solve(A,s,pos);
		loop(i,n) printf("pub %d: %.2f %%\n",i+1,dp[pos][i]*100);
	}


//	n = 3;
//	k = 7;
//	for(int a = 0;a <= k;a++)
//		for(int b = 0;a + b <= k;b++) {
//			vi A{a,b,k-a-b};
//			get_idx(A);
//		}

//	n = 3;
//	k = 1;
//	vi A{0,1,0};
//	cerr << get_idx(A) << endl;
	return 0;
}
