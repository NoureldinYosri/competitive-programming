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

int A[3001],vis[3001],n,m,t;
vi cycle[3001];
int mn[3001];

void increase(){
	vp ans;	
	while(m < t){
		int x = INT_MAX,y = INT_MAX,j = 0;
		loop(i,m){
			if(sz(cycle[i]) == 1) continue;
			int mn = INT_MAX,mn2 = INT_MAX;
			for(int x : cycle[i]){
				mn2 = min(mn2,x);
				if(mn2 < mn) swap(mn,mn2);
			}
			if(mn < x) x = mn,y = mn2,j = i;
		}
		swap(A[x],A[y]);
		ans.pb(mp(x,y));
		for(int v : cycle[j]) vis[v] = 0;
		cycle[j].clear();
		for(;!vis[x];x = A[x]) cycle[j].pb(x),vis[x] = 1;
		for(;!vis[y];y = A[y]) cycle[m].pb(y),vis[y] = 1;
		//print(cycle[j],int);
		//print(cycle[m],int);
		m++;
	}
	printf("%d\n",sz(ans));
	for(auto p : ans) printf("%d %d ",p.xx,p.yy);
}

void decrease(){
	vp ans;	
	loop(i,m){
		mn[i] = INT_MAX;
		for(int x : cycle[i]) mn[i] = min(mn[i],x);
	}
	sort(mn,mn + m);
	reverse(mn,mn + m);
	while(m > t){
		ans.pb(mp(mn[m-1],mn[m-2]));
		swap(A[mn[m-1]],A[mn[m-2]]);
		swap(mn[m-1],mn[m-2]);		
		m--;
	}
//	prArr(A+1,n,int);
	printf("%d\n",sz(ans));
	for(auto p : ans) printf("%d %d ",p.xx,p.yy);
}



int main(){
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i);
	scanf("%d",&t);
	range(i,1,n){
		if(vis[i]) continue;
		int j = i;
		while(!vis[j]){
			cycle[m].pb(j);
			vis[j] = 1;
			j = A[j];
		}
		m++;
	}
	t = n - t;
	sort(cycle,cycle + m,[](vi & a,vi & b){
		return sz(a) > sz(b);
	});
	cerr << t << " " << m << endl;
	if(t == m) puts("0");
	else if(t < m) decrease();
	else increase();	
	return 0;
}
