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

const int MAX = 1 << 20;
int n,A[MAX],L[MAX],R[MAX],BIT[MAX];
map<int,int> freq;

void update(int p,int v){
	for(;p <= n;p += LSOne(p)) BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(;p; p -= LSOne(p)) ret += BIT[p];
	return ret;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	loop(i,n){
		if(freq.find(A[i]) == freq.end()) freq[A[i]] = 0;
		L[i] = ++freq[A[i]];
	}	
	freq.clear();
	loop(i,n){
		if(freq.find(A[n - 1 - i]) == freq.end()) freq[A[n - 1 - i]] = 0;
		R[n - 1 - i] = ++freq[A[n - 1 - i]];
	}
	ll ans = 0;
	for(int i = n - 1;i >= 0;i--){
		ans += get(L[i] - 1);
		update(R[i],1);
	}	
	cout << ans << endl;
	return 0;
}
