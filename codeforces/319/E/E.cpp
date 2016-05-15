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

int P[1 << 20][2],n;
vi bucket[1 << 10];
int f;

bool cmp(const int & a,const int & b){
	if(f) return P[a][1] > P[b][1];
	else return P[a][1] < P[b][1];
}

int main(){
	scanf("%d",&n);
	loop(i,n) {
		loop(j,2) scanf("%d",P[i] + j);
		bucket[P[i][0]/1000].pb(i);
	}
	loop(i,1 << 10) {	
		sort(all(bucket[i]),&cmp);
		f = 1 - f;	
	}
	bool c = 0;
	loop(i,1 << 10) for(auto p : bucket[i]) printf("%s%d",c ? " " : "",p + 1),c = 1;
	puts("");
	return 0;
}
