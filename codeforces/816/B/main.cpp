#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 200000*4 + 10;
int n,k,m;
int iL[MAX],iR[MAX],qL[MAX],qR[MAX];
vector<pair<pi,int> > V;
int memo[MAX],r[MAX],ans[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&k,&m);
	loop(i,n) scanf("%d %d",iL + i,iR + i);
	loop(i,m) scanf("%d %d",qL + i,qR + i);
	V.reserve(2f*n + 2*m);
	loop(i,n) {
		V.pb(mp(mp(iL[i],-1),i));
		V.pb(mp(mp(iR[i],2),i));
	}
	loop(i,m) {
		V.pb(mp(mp(qL[i],0),i));
		V.pb(mp(mp(qR[i],1),i));
	}
	sort(all(V));
	loop(i,sz(V)) if(V[i].xx.yy == 0) r[V[i].yy] = i;

	int com = 0,cnt = 0;
	loop(i,sz(V)){
		memo[i] = com;
		int x = V[i].xx.xx,type = V[i].xx.yy,idx = V[i].yy;
		if(type == -1) cnt++;
		else if(type == 2){
			if(cnt == k) com++;
			cnt--;
		}
		if(type == 1){
			int inv = r[idx];
			ans[idx] = memo[i] + (cnt >= k) - memo[inv];
		}
		if(cnt >= k && i != sz(V)-1)
			com += V[i + 1].xx.xx - x;
	}
	loop(i,m) printf("%d\n",ans[i]);

	return 0;
}
