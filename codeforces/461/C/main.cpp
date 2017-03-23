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
int n,m;
int BIT[MAX];
int s,e;
void update(int u,int v){
	for(;u <= n;u += LSOne(u)) BIT[u] += v;
}

int get(int u){
	int ret = 0;
	for(;u;u ^= LSOne(u)) ret += BIT[u];
	return ret;
}


void normal(int p){
	for(int i = 1;i <= p;i++){
		int v = get(s + i - 1) - get(s + i - 2);
		update(s + 2*p - i, v);
		update(s + i - 1, -v);
	}
	s += p;
}

void rev_normal(int p){
	for(int i = 1;i <= p;i++){
		int v = get(e - i + 1) - get(e - i);
		update(e - 2*p + i, v);
		update(e - i + 1, -v);
	}
	e -= p;
}

int main(){
	scanf("%d %d",&n,&m);
	range(i,1,n) update(i,1);

	int dir = 1;
	s = 1,e = n;	
	while(m--){
		int type; scanf("%d",&type);
		if(type == 1){
			int p; scanf("%d",&p);
			if(2*p <= e - s + 1){
				if(dir) normal(p);
				else rev_normal(p);
			}
			else{
				p = e - s + 1 - p;
				if(dir) rev_normal(p);
				else normal(p);
				dir ^= 1;
			}
		}
		else{
			int l,r; scanf("%d %d",&l,&r);
			// get sum 
			int ans = 0;
			if(dir) ans = get(s + r - 1) - get(s + l - 1);
			else ans = get(e - l) - get(e - r);
			printf("%d\n",ans);
		}
	}	
	
	
	return 0;
}
