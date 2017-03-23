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

const int DIM = 3;
int mod;
void mul(int A[DIM][DIM],int B[DIM][DIM]){
	int C[DIM][DIM] = {0};
	loop(i,DIM) loop(j,DIM) loop(k,DIM){
		C[i][j] += (A[i][k]*1LL*B[k][j])%mod;
		if(C[i][j] >= mod) C[i][j] -= mod;
	}
	loop(i,DIM) loop(j,DIM) A[i][j] = C[i][j];
}

void make_eye(int A[DIM][DIM]) {
	loop(i,DIM) loop(j,DIM) A[i][j] = i == j;
}

void EXP(int A[DIM][DIM],int n){
	if(!n) return make_eye(A);
	int B[DIM][DIM]; make_eye(B);
	for(;n > 1; n >>= 1){
		if(n & 1) mul(B,A);
		mul(A,A);
	}
	mul(A,B);
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		int a,b,c,m,n; scanf("%d %d %d %d %d",&a,&b,&c,&n,&m);
		a %= m; b %= m; c %= m;
		if(n <= 2) printf("%d\n",1%m);
		else{
			int A[DIM][DIM]; make_eye(A); mod = m;
			A[0][0] = a; A[0][1] = b; A[0][2] = c;
			EXP(A,n - 2);
			int ans = 0;
			loop(i,3) {
				ans += A[0][i];
				if(ans >= mod) ans -= mod;
			}
			printf("%d\n",ans);
		}
	}
	
	
	return 0;
}
