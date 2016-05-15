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

int n;
char words[101][100],G[10][11];
int dont[101];
pi cells[101];

int f(pi & a){
	loop(i,n + 1
}

bool cmp(const pi & a,const pi & b){
	return f(a) < f(b);
}

bool bt(int i){
	if(i == n + 1) return 1;
	if(dont[i]) return bt(i + 1);
	sort(cells + i,cells + n,&cmp);
	if(f(cells[i]) == 0) return 0;
	
}


int main(){
	for(int t = 1;scanf("%d",&n) == 1 && n;t++){
		loop(i,n) scanf("%d %d",&cells[i].xx,&cells[i].yy);
		loop(i,n + 1) scanf("%s",words[i]);
		printf("Trial %d:",t);
		loop(i,n + 1){
			dont[i] = 1;
			if(bt(0)) printf(" %s",words[i]);
			dont[i] = 0;
		}
	}	
	return 0;
}
