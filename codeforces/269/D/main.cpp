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

const int MAX = 4e5 + 1e2;

int A[MAX],B[MAX],n,m;
int Z[MAX];

void buildZ(int *P,int L,int *Z){
	int l = 0,r = 0;
	Z[0] = L;	
	range(i,1,L - 1){
		if(i > r){
			l = r = i;
			while(r < L && P[r - l] == P[r]) r++;
			Z[i] = r - l; 
			r--;
		}
		else{
			int k = i - l;
			if(Z[k] < r - i + 1) Z[i] = Z[k];
			else{
				l = i;
				while(r < L && P[r - l] == P[r]) r++;
				Z[i] = r - l;
				r--;
			}
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	loop(i,m) scanf("%d",B + i);
	if(m == 1) {
		printf("%d\n",n);
		return 0;
	}
	if(n == 1){
		puts("0");
		return 0;
	}
	loop(i,n - 1) A[i] = A[i + 1] - A[i];
	loop(i,m - 1) B[i] = B[i + 1] - B[i];
	--n,--m;
	B[m] = INT_MAX;
	loop(i,n) B[i + m + 1] = A[i];
	buildZ(B,n + m + 1,Z);
	int ans = 0;
	loop(i,n) ans += Z[i + m + 1] == m;
	printf("%d\n",ans);
	cerr << ans << endl;
	return 0;
}
