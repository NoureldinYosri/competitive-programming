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
vi part[MAX];
vi odd,even;

int main(){
	int n,k,p;
	scanf("%d %d %d",&n,&k,&p);
	loop(i,n){
		int a; scanf("%d",&a);
		if(a & 1) odd.pb(a);
		else even.pb(a);	
	}
	if(p){
		loop(i,sz(even)) part[i%p].pb(even[i]);
		if(sz(even) < p){
			for(int i = sz(even);i < p;i++){
				if(sz(odd) < 2){
					puts("NO");
					return 0;
				}
				part[i].pb(odd.back());
				odd.pop_back();
				part[i].pb(odd.back());
				odd.pop_back();
			}
		}
	}
	else {
		for(int x : even) part[0].pb(x);
	}
	for(int i = p;i < k;i++){
		if(odd.empty()){
			puts("NO");
			return 0;
		}
		part[i].pb(odd.back());
		odd.pop_back();
	}
	while(!odd.empty()){
		if(sz(odd) == 1){
			puts("NO");
			return 0;
		}
		part[0].pb(odd.back());
		odd.pop_back();
		part[0].pb(odd.back());
		odd.pop_back();
	}
	puts("YES");
	loop(i,k){
		printf("%d",sz(part[i]));
		for(int x : part[i]) printf(" %d",x);
		puts("");
	}
	return 0;
}
