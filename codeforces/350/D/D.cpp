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

int n,k;
int A[1 << 20];
int B[1 << 20];

bool can(ll m){
	int tmp = k;
	loop(i,n){
		ll d = B[i] - A[i] * m;
		if(d >= 0) continue;
		d = abs(d);
		if(d > tmp) return 0;
		tmp -= d;
	}
	return 1;
}

int main(){
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",B + i);
	ll s = 0,e = 3e9;
	while(s < e){
		ll m = s + (e - s + 1)/2;
		if(can(m)) s = m;
		else e = m - 1;
	}	
	cerr << s << endl;
	cout << s << endl;
	return 0;
}

