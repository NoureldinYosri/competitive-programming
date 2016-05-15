#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int doLayout(int stonePerRing, int nRings, double *pMaxRadius, double *pLen)
{
	int i;
	double si, cs, R1, r1, R2, r2;
	si = sin(M_PI/((double)stonePerRing));
	cs = cos(M_PI/((double)stonePerRing));
	r1 = si/(1.0 - si);
	R1 = 1.0 + r1;
	for(i = 1; i < nRings ; i++) {
		R2 = R1 * cs + r1 * si + sqrt(r1 * r1 + 2*r1*R1*cs*si);
		R2 = R2/(cs*cs);
		r2 = R2*si;
		R1 = R2;
		r1 = r2;
	}
	*pMaxRadius = r1;
	*pLen = 2.0* r1 * (M_PI + ((double)stonePerRing));
	return 0;
}


int main(){
	int T,K,n,m;
	pre();
	cin >> T;
	while(T--){
		cin >> K >> n >> m;
		double a,b;
		doLayout(n,m,&a,&b);
		printf("%d %.3lf %.3lf\n",K,a,b);
	}
	return 0;
}
