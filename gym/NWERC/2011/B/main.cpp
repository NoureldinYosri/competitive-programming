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

ll A[2][2];
int L[2][2] = {{0,1},{1,1}};
int R[2][2] = {{1,1},{1,0}};

void mul(int T[2][2]){
	ll B[2][2] = {0};
	loop(i,2) loop(j,2) loop(k,2) B[i][j] += A[i][k]*T[k][j];
	loop(i,2) loop(j,2) A[i][j] = B[i][j];
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		ll a,b; scanf("%lld/%lld",&a,&b);
		//cerr << "solving for " << a << " " << b << endl;
		ll x = 1,y = 1,d,dir = 1;
		loop(i,2) loop(j,2) A[i][j] = i == j;
		for(int i = 0;(a != x || b != y);i++){
			ll diff = a*y - b*x;
			//cerr << i + 1 << " " << x << "/" << y << " vs " << "a/b"
			if(diff < 0) {
				if(dir) putchar('L'),mul(L);
				else putchar('R'),mul(R);
			}
			else{
				if(!dir) putchar('L'),mul(L);
				else putchar('R'),mul(R);
			}
			x = A[0][0] + A[0][1];
			y = A[1][0] + A[1][1];
			//prArr(A[0],2,ll);
			//prArr(A[1],2,ll);
			d = __gcd(a,b);
			x /= d;
			x /= d;
			dir ^= 1;
			//cerr << x << " " << x << endl;
		}
		puts("");
		//break;
	}
	
	return 0;
}
