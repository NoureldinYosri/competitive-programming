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

int n,n1,n2;
int A[1 << 20];
ll S[1 << 20];

ll f(int m){
	ll x = S[m-1],y = S[n - 1] - x;
	x *= (n - m + 0LL);
	y *= m + 0LL;
	x += y;
	return x;
}

int main(){
	scanf("%d %d %d",&n,&n1,&n2);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);
	reverse(A,A + n);
	n = n1 + n2;
	reverse(A,A + n);
	//prArr(A,n,int);
	loop(i,n){
		S[i] = A[i] + (i ? S[i - 1] : 0);
	}	
	ll x = max(f(n1),f(n2));
	ll y = n1 * 1LL * n2;	
	printf("%.15f",x*1.0/y);
	return 0;
}
