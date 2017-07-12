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
#define popcnt(x) __builtin_popcount(x)
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


const int MAX = 5*100*1000 + 10;
const int MAXST = MAX*20;
pi P[MAX];
int n;
int X,Y,Q;
int siz[MAXST],L[MAXST],R[MAXST],N;
int T[MAX];

void build(int node,int s,int e){
	siz[node] = L[node] = R[node] = 0;
	N = node;
	if(s == e) return;
	int m = (s + e) >> 1,left = 2*node + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
}


int update(int node,int s,int e,int p){
	int cur = ++N;
	siz[cur] = siz[node];
	L[cur] = L[node];
	R[cur] = R[node];
	siz[cur]++;
	if(s == e) return cur;
	int m = s + (e - s)/2;
	if(p <= m) L[cur] = update(L[cur],s,m,p);
	else R[cur] = update(R[cur],m+1,e,p);
	return cur;
}

int query(int u,int v,int s,int e,int target){
	if(e <= target) return siz[v] - siz[u];
	int m = s + (e - s)/2;
	if(target <= m) return query(L[u],L[v],s,m,target);
	return siz[L[v]] - siz[L[u]] + query(R[u],R[v],m + 1,e,target);
}


int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	//	freopen("output.out", "w", stdout);
	#endif
	for(int t = 1;scanf("%d %d %d %d",&X,&Y,&n,&Q) == 4 && !(X == 0 && Y == 0 && n == 0 && Q == 0);t++){
		loop(i,n){
			int x,y; scanf("%d %d",&x,&y);
			x--,y--;
			P[i] = mp(x + y,x - y);
		}
		sort(P,P + n);
		if(n) {
			build(0,-X-Y,X+Y);
			loop(i,n) T[i + 1] = update(T[i],-X-Y,X+Y,P[i].yy);
		//	loop(i,n) {prp(P[i]);}
		//	cerr << endl;
		}
		printf("Case %d:\n",t);
		loop(q,Q){
			int k; scanf("%d",&k);
			int ans = 0;
			pi best = mp(0,0);
			loop(i,X) loop(j,Y) {
				int l = i + j - k,r = i + j + k;
				int lf = i - j - k,rf = i - j + k;
				l = lower_bound(P,P + n,mp(l,INT_MIN)) - P;
				r = lower_bound(P,P + n,mp(r,INT_MAX)) - P;
				if(r <= l) continue;
				l = T[l];
				r = T[r];
				int tmp = query(l,r,-X-Y,X+Y,rf) - query(l,r,-X-Y,X+Y,lf - 1);
				tmp *= -1;
				if(tie(tmp,j,i) < tie(ans,best.yy,best.xx)){
					ans = tmp;
					best = mp(i,j);
				}
			}
			ans = -ans;
			best.xx++;
			best.yy++;
			printf("%d (%d,%d)\n",ans,best.xx,best.yy);
		}
	}
	return 0;
}

