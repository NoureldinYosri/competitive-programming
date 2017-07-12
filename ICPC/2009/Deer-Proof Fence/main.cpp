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

int X[9],Y[9],n,M;
double dp[1 << 9];

int cross(pi o,pi u,pi v){
	u.xx -= o.xx; u.yy -= o.yy;
	v.xx -= o.xx; v.yy -= o.yy;
	return u.xx*v.yy - u.yy*v.xx;
}
vector<pi> convex_hull(vector<pi> P)
{
	int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<pi> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}
double combine(int msk){
	if(!msk) return 0;
	vp P;
	loop(i,n) if(msk & (1 << i)) P.pb(mp(X[i],Y[i]));
	//for(auto p : P) prp(p);
	//cerr << endl;

	vector<pi> CH = convex_hull(P);
	double ret = 2*PI*M;
	for(int i = 0;i + 1 < sz(CH);i++)
		ret += hypot(CH[i].xx - CH[i + 1].xx,CH[i].yy - CH[i + 1].yy);
	//for(auto p : CH) prp(p);
	//cerr << endl;
	//cerr << "=========================" << endl;
	return ret;
}

double solve(int msk){
	if(!msk) return 0;
	double & ret = dp[msk];
	if(ret == ret) return ret;
	ret = 1LL << 60;
	vi have;
	loop(i,n) if(msk & (1 << i)) have.pb(i);
	loop(nmsk,1 << sz(have)) if(nmsk) {
		int aux_msk = 0;
		loop(i,sz(have)) if(nmsk & (1 << i)) aux_msk |= 1 << have[i];
		ret = min(ret,solve(msk ^ aux_msk) + combine(aux_msk));
	}
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	for(int t = 1;scanf("%d %d",&n,&M) == 2 && !(n == 0 && M == 0);t++){
		loop(i,n) scanf("%d %d",X + i,Y + i);
		memset(dp,-1,sizeof dp);
		printf("Case %d: length = %.2f\n",t,solve((1 << n) - 1));
	}
	return 0;
}
