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

int n,L;
int A[50],B[50];
int C[50],D[50];

int main(){
	scanf("%d %d",&n,&L);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",B + i);
	
	loop(i,n-1){
		C[i] = A[i + 1] - A[i];
		D[i] = B[i + 1] - B[i];
	}
	C[n - 1] = L - A[n - 1] + A[0];
	D[n - 1] = L - B[n - 1] + B[0];
	

	loop(i,n){
		if(equal(C,C + n,D,D + n)){
			puts("YES");
			return 0;
		}
		rotate(C,C + 1,C + n);
	}	
	puts("NO");
	return 0;
}
