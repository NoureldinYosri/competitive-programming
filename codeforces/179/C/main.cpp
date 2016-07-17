#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,L = (n);i < L;i++)
#define range(i,a,b) for(int i = (a),L = (b);i <= L;i++)
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

const int MAX = 2e5;

int A[MAX],n,m,k,x,y;
pair<pi,int> op[MAX];
ll times[MAX],offset[MAX];

int main(){
	scanf("%d %d %d",&n,&m,&k);
	loop(i,n) scanf("%d",A + i + 1);
	range(i,1,m) scanf("%d %d %d",&op[i].xx.xx,&op[i].xx.yy,&op[i].yy);
	loop(i,k){
		scanf("%d %d",&x,&y);
		times[x]++;
		times[y + 1]--;
	}
	ll tmp = 0;	
	range(i,1,m){
		int l = op[i].xx.xx,r = op[i].xx.yy,d = op[i].yy;
		tmp += times[i];
		offset[l] += tmp*d;
		offset[r + 1] -= tmp*d;
	}
	tmp = 0;
	range(i,1,n){
		tmp += offset[i];
		printf("%lld%c",A[i] + tmp," \n"[i == n]);
	}
	return 0;
}
