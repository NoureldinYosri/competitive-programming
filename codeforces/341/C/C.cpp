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

int n,p;
int L[1 << 20],R[1 << 20];

double f(int i){
	int a = R[i]/p - (L[i] - 1)/p;
	return (R[i] - L[i] - a + 1.0)/(R[i] - L[i] + 1.0);
}

int main(){
	scanf("%d %d",&n,&p);
	loop(i,n) scanf("%d %d",L + i,R + i);
	double ans = 0;
	int j = n - 1;
	loop(i,n){
		ans += 2000*(1 - f(i) * f(j));
		j ++;
		if(j == n) j = 0;
	}
	printf("%.6f\n",ans);
	return 0;
}
