#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int n,a;
set<int> S;
vector<pi> out;

int main(){
	scanf("%d",&n);	
	int j = 0;
	loop(i,n){
		scanf("%d",&a);
		if(S.find(a) != S.end()){
			out.pb(mp(j + 1,i + 1));
			S.clear();
			j = i + 1;
		}
		else S.insert(a);
	}	
	if(out.empty()){
		puts("-1");
		return 0;
	}
	if(!S.empty()) out.back().yy = n;
	printf("%lu\n",sz(out));
	for(auto p : out) printf("%d %d\n",p.xx,p.yy);
	return 0;
}
