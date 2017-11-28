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

int n,k;

double P[20];
double dp[1 << 20];
double ans [20];


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
/*	cin >> n >> k ;
	loop(i,n) cin >> P[i];
	dp[0] = 1;
	for(int msk = 0;msk < (1 << n);msk++) {
		if(popcnt(msk) < k){
			double sum = 0;
			for(int i = 0;i < n;i++)
				if((msk >> i) & 1)
					sum += P[i];
			dp[msk] /= 1.0 - sum;
			for(int i = 0;i < n;i++)
				if(!(msk & (1 << i)))
					dp[msk | (1 << i)] += P[i] * dp[msk];
		}
	}
	for(int msk = 0;msk < (1 << 20);msk++) if(popcnt(msk) == k) {
		for(int i = 0;i < n;i++)
			if(msk & (1 << i))
				ans[i] += dp[i];
	}
	prArr(ans,n,double);
*/
	double a = 0.1 + 0.1 + 0.1;
	double b = 0.3;
	cout << (a == b) << endl;
	return 0;
}
