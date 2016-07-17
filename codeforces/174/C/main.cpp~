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

const int MAX = 3e5;
ll BIT[MAX + 1];
ll A[MAX + 1];
int n;

void update(int p,int v){
	for(;p <= MAX;p += LSOne(p)) BIT[p] += v;
}

ll get(int p){
	ll ret = 0;
	for(;p;p -= LSOne(p)) ret += BIT[p];
	return ret;
}

int main(){
	ll sum = 0,r = 0;  int e = 2,c,a,b;
	scanf("%d",&n);
	loop(i,n){
		scanf("%d",&c);
		if(c == 1){
			scanf("%d %d",&a,&b);
			sum += a*1LL*b;
			update(1,b);
			update(a + 1,-b);
		}
		else if(c == 2){
			scanf("%d",&a);
			A[e++] = a;
			sum += a;
		}
		else{
			--e;
			sum -= get(e) + A[e];
			ll v = get(e);
			update(e,-v);
			update(e + 1,v);
		}
		printf("%.6f\n",sum*1.0/(e - 1));
	}	
	return 0;
}
