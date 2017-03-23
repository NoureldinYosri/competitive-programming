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

int main(){
	int n,R,r;
	cin >> n >> R >> r;
	int a = 2*(R - r)*(R - r) - 4*r*r;
	int b = 2*(R - r)*(R - r);
	if(n == 1) puts((r <= R) ? "YES" : "NO" );
	else if(r >= R || (abs(a) > abs(b))) puts("NO");
	else{
		double t = acos(a*1.0/b)*n;
		double T = 2*acos(-1);
		if(T > t || abs(T - t) < 1e-15) puts("YES");
		else puts("NO");
	}
	
	
	return 0;
}
