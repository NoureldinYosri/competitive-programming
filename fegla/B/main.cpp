#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

const int MAX = 1e5 + 1e3;

char name[MAX][50];
pair<pi,int> A[MAX];

int n,T,m,a;

bool cmp(const pair<pi,int> & a,const pair<pi,int> & b){
	if(abs(a.xx.yy - a.xx.xx) == abs(b.xx.yy - b.xx.xx)) {
		if(a.xx.yy == b.xx.yy) return a.yy < b.yy;
		else return a.xx.yy > b.xx.yy;
	}
	else return abs(a.xx.yy - a.xx.xx) > abs(b.xx.yy - b.xx.xx);
}

int main(){
	freopen("crazy.in","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		loop(i,n){
			scanf("%s",name[i]);
			A[i] = mp(mp(INT_MAX,INT_MIN),i);
			loop(j,m){
				scanf("%d",&a);
				A[i].xx.yy = max(A[i].xx.yy,a);
			}
			loop(j,m){
				scanf("%d",&a);
				A[i].xx.xx = min(A[i].xx.xx,a);
			}
		}
		sort(A,A + n,&cmp);
		printf("%s\n",name[A[0].yy]);
	}
	return 0;
}
