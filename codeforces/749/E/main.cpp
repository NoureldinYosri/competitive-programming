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

const int MAX = 1e5 + 1e2;
int A[MAX],ord[MAX],n;
ll BIT[2][MAX],inv = 0;

void update(int p,ll v,ll *T){
	for(;p <= n;p += LSOne(p))
		T[p] += v;
}

ll get(int p,ll *T){
	ll ret = 0;
	for(;p;p ^= LSOne(p))
		ret += T[p];
	return ret;
}

int main(){
	double ans = 0,sum = 0;
	scanf("%d",&n);
	range(i,1,n){
		scanf("%d",A + i);
		int tmp = get(n,BIT[0]) - get(A[i],BIT[0]);
		inv += tmp;
		update(A[i],1,BIT[0]);
		ans += (n + 1 - i) * (sum - get(A[i],BIT[1]));
		update(A[i],i,BIT[1]);
		sum += i;
	}
	ll cnt = n * (n + 1LL)/2;
	range(i,1,n){
		double tmp = i*(i - 1.0)/4.0;
		ans -= tmp * (n + 1 - i);
	}
	ans /= cnt;
	ans = inv - ans;
	fprintf(stdout,"%.15f\n",ans);
	return 0;
}
