#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int mod = 1e9 + 7;

int O [] [4] = {{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}};

void multiply(int A[4][4],int B[4][4],int C[4][4]){
	int D[4][4];
	loop(i,4) loop(j,4){
		D[i][j] = 0;
		loop(k,4){
			int tmp = (A[i][k] * 1LL * B[k][j])%mod;
			D[i][j] += tmp;
			if(D[i][j] >= mod) D[i][j] -= mod;
		}
	}
	copy(D[0],D[4],C[0]);
}

void POW(int A [4][4],int p){
	int B[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};	
	for(;p > 1;p >>= 1){
		if(p & 1) multiply(A,B,B);
		multiply(A,A,A);
	}
	multiply(A,B,A);
}



int main(){
	int n;
	cin >> n;
	POW(O,n);
	printf("%d\n",O[0][0]);
	return 0;
}
