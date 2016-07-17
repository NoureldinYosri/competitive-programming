#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 2e5 + 1e3;

int cap[MAX],n,m,type,a,b;
int cont[MAX],nxt[MAX];

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",cap + i + 1),nxt[i + 1] = i + 2;
	scanf("%d",&m);
	while(m--){
		scanf("%d %d",&type,&a);
		if(type == 1){
			scanf("%d",&b);
			vi ST; bool first = 1;			
			while(a <= n && b){
				if(!first) a = nxt[a];
				ST.pb(a);			
				first = 0;
				int d = min(cap[a] - cont[a],b);
				cont[a] += d;
				b -= d;			
			}
			for(ST.pop_back();!ST.empty();ST.pop_back()) nxt[ST.back()] = (ST.back() != a) ? a : nxt[ST.back()];
		}
		else printf("%d\n",cont[a]);
	//	prArr(cont + 1,n,int);
	//	prArr(nxt + 1,n,int);
	//	cerr << endl;
	}

	return 0;
}
