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
int id[MAX],W[MAX],n,m;
int fr[MAX],to[MAX],C[MAX],ord[MAX];

int get(int a){
	return (id[a] == a) ? a : get(id[a]);
}

int join(int a,int b){
	a = get(a),b = get(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
	return 1;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		range(i,1,n) {
			id[i] = i;
			W[i] = 1;
		}
		ll ans = 0;
		loop(i,m) scanf("%d %d %d",fr + i,to + i,C + i),ord[i] = i,ans += C[i];
		sort(ord,ord + m,[](const int & a,const int & b){
			return C[a] < C[b];
		});
		loop(i,m) ans -= C[ord[i]] * join(fr[ord[i]],to[ord[i]]);
		printf("%lld\n",ans);
	}	
	
	
	return 0;
}
