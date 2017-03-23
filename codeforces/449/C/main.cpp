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
vi nums[MAX];
int prime[MAX],vis[MAX];
vp ans;

void sieve(){
	for(int p = 2;p < MAX;p++)
		if(!prime[p]){
			prime[p] = p;
			for(ll j = p*1LL*p;j < MAX;j += p)
				prime[j] = p;
		}
}


int main(){
	sieve();	
	int n; cin >> n;
	vector<pair<int, int> > ans;
	for (int i = n; i > 1; i--) {
		if (prime[i] == i) {
			vector<int> aux;
			for(int j = i;j <= n;j += i)
				if (!vis[j]) 
					aux.pb(j);

			if (sz(aux) == 1) continue;
			if (sz(aux) & 1) 
				swap(aux[1], aux.back());

			loop(j,sz(aux)/2){					
				vis[aux[2*j]] = vis[aux[2*j+1]] = 1;
				ans.pb(mp(aux[2*j], aux[2*j+1]));
			}
		}
	}
	printf("%d\n",sz(ans));
	for(auto p : ans)
		printf("%d %d\n",p.xx,p.yy);
	return 0;
}

