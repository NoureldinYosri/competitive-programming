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

const int MAX = 200'010;
int X[MAX],n;
pi aux[MAX];
int name[MAX],pos[MAX];

int main(){
	int m; scanf("%d %d",&n,&m);
	range(i,1,n){
		scanf("%d",X + i);
		//if(i != 1) assert(X[i - 1] < X[i]);
		aux[i] = mp(X[i],i);
	}
	sort(aux + 1,aux + n + 1);
	range(i,1,n){
		X[i] = aux[i].xx;
		name[i] = aux[i].yy;
		pos[aux[i].yy] = i;
	}
	while(m--){
		int u ,l,dir = 1,lst = 0,ctr = 0; scanf("%d %d",&u,&l); u = pos[u];
		while(1){
			int p ;
			if(dir == 1) p = upper_bound(X + 1,X + 1 + n,X[u] + l) - X - 1;
			else p = lower_bound(X + 1,X + n + n,X[u] - l) - X ;
			//cerr << "f(" << u << "," << l << " ," << dir << ")" << " -> " << p << endl;
			if(p == u) {
				ctr++;
				if(ctr == 2) break;
				dir = (dir == 1) ? -1 : 1;
				continue;
			}
			ctr = 0;
			if(p == lst) {
				int num = l / abs(X[u] - X[p]);
				l %= abs(X[u] - X[p]);
				if(num & 1) {
					lst = u;
					u = p;
					dir = (dir == 1) ? -1 : 1;
				}
			}
			else{
				l -= abs(X[u] - X[p]);
				lst = u;
				u = p;
				dir = (dir == 1) ? -1 : 1;
			}
		}
		u = name[u];
		printf("%d\n",u);
//		cerr << u << endl;
	}
	
	return 0;
}
