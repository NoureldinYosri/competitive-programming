#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAX = 10368;
int F[MAX];
ll S[4] = {10368,10368 + 10368,10368 + 10368 + 20736,10368 + 10368 + 20736 + 41472};

void init(){
	int A[5],l;
	range(i,1,MAX - 1){
		loop(j,5) A[j] = F[i/(j + 2)];
		sort(A,A + 5);
		l = unique(A,A + 5) - A;
		loop(j,l){
			if(A[j] == F[i]) F[i]++;
			else break;
		}
	}
}

int get_grundy(ll n){
	if(n < MAX) return F[n];
	ll p = 1;
	while((p*12*S[0]) <= n) p *= 12;
	if(n < S[1] * p) return 0;
	else if(n < S[2]*p) return 1;
	else if(n < S[3]*p) return 2;
	else return 3;
}


int main(){
	init();	
	int T,n; ll a;
	scanf("%d",&T);
	while(T--){
		int ans = 0;
		scanf("%d",&n);
		loop(i,n){
			scanf("%lld",&a);
			ans ^= get_grundy(a);
		}
		puts(ans ? "Henry" : "Derek");
	}
	return 0;
}
