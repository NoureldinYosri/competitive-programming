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
	int n,k; cin >> n >> k;
	if(k == 0) cout << ((n==1) ? 1 : -1) << endl;
	else if(n<=1 || n/2 > k) cout << -1 << endl;
	else{
		// x + (n - 2) = k;
		// x = k - n + 2
		int x = k - n/2 + 1;
		// x ,x , (n-2)
		printf("%d %d",x,2*x);
		int offset = 2*x + 1;
		loop(i,n/2-1) printf(" %d %d",offset + 2*i,offset + 2*i + 1);
		if(n & 1) puts(" 1000000000");		
		puts("");
	}
	
	
	return 0;
}
