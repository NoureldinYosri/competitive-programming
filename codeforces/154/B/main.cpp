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

const int MAX = 1e5 + 10;
int prime[MAX];

int n,m;
int on[MAX];
set<int> num[MAX];

void sieve(){
	for(int i = 2;i < MAX;i++)
		if(!prime[i]){
			prime[i] = i;
			for(ll j = i*1LL*i;j < MAX;j += i)
				prime[j] = i;
		}
}

int main(){
	sieve();
	scanf("%d %d",&n,&m);
	loop(i,m){
		char c;int x; scanf(" %c %d",&c,&x);
		if(c == '+'){
			if(on[x]) puts("Already on");
			else {
				int y = x,c = 1;
				while(x > 1){
					int p = prime[x];
					if(!num[p].empty()){
						printf("Conflict with %d\n",*num[p].begin());
						c = 0;
						break;
					}
					while(x%p == 0) x /= p;
				}
				if(c){
					x = y;
					on[x] = 1;
					while(x > 1){
						int p = prime[x];
						num[p].insert(y);						
						while(x%p == 0) x /= p;
					}
					puts("Success");
				}
			}
		}
		else{
			if(on[x]) {
				puts("Success");
				int y = x;
				while(x > 1){
					int p = prime[x];
					num[p].erase(y);
					while(x%p == 0) x /= p;
				}
				on[y] = 0;
			}
			else puts("Already off");
		}
	}	
	
	
	return 0;
}
