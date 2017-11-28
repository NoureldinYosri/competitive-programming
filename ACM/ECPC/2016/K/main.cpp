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

int N,M,K,Q,Z;

double P[20][20],C[20][10];
int A[15];
double eP[20][20];

double solve(){
	if(C[0][A[0]] == 0) return 0;
	memset(eP,0,sizeof eP);
	eP[0][0] = 1;
	//P(city | card) = P(card | city) * P(city) / norm
	for(int t = 1;t < K;t++) {
		loop(i,N) loop(j,N) eP[t][j] += eP[t-1][i] * P[i][j];
//		prArr(eP[t],N,double);
		double norm = 0;
		loop(i,N) norm += eP[t][i] *= C[i][A[t]];
		loop(i,N) eP[t][i] /= norm;
		prArr(eP[t],N,double);
	}
	return eP[Q][Z];
}

int main(){
	freopen("trip.in", "r", stdin);
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d %d %d %d %d",&N,&M,&K,&Q,&Z);
		loop(i,N) loop(j,N) scanf("%lf",&P[i][j]);
		loop(i,N) loop(j,M) scanf("%lf",&C[i][j]);
		loop(i,K) scanf("%d",A + i);
		printf("%.3lf",solve());
	}
	return 0;
}
