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

const int MAX = 20000	;
int A[MAX],n;

int main(){
	cin >> n;
	loop(i,n) cin >> A[i];
	vi DIV;
	loop(i,n) if(n%(i+1)==0) DIV.pb(i+1);
	
	int	mx = INT_MIN;
	for(int d : DIV) if(n/d > 2){
		int m = n/d,sum = 0;
		loop(i,d){
			int sum = 0;	
			loop(j,m) sum += A[(j*d + i)%n];
			mx = max(mx,sum);	
		}
	}
	printf("%d\n",mx);
//	cerr << mx << endl;
	
	return 0;
}
