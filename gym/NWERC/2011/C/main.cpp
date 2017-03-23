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

const int MAX = 100'010;

int n,m;
int BIT[MAX << 1];
int id[MAX];
void add(int p,int v){
	for(;p <= m + n;p += LSOne(p))
		BIT[p] += v;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		memset(BIT,0,sizeof BIT);
		range(i,1,n) {
			add(i+m,1);
			id[i] = i + m;
		}
		for(int i = m;i;i--){
			int x; scanf("%d",&x);
//			cerr << x << " " << id[x] << " " << get(id[x]) << endl;
			printf("%d%c",get(id[x]) - 1," \n"[i==1]);
			add(id[x],-1);
			add(id[x] = i,1);
		}
	}		
	
	
	return 0;
}
