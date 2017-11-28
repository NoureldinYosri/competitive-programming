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

const int MAX = 200*1000 + 10;
int ST[MAX*4];
int P[MAX],Q[MAX];
int rP[MAX],rQ[MAX];
int T[MAX],n;

void update(int node,int s,int e,int pos,int val) {
	ST[node] += val;
	if(s == e) return ;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) update(left,s,m,pos,val);
	else update(right,m+1,e,pos,val);
}

int getRank(int node,int s,int e,int pos) {
	if(s == e) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(pos <= m) return getRank(left,s,m,pos);
	else return ST[left] + getRank(right,m+1,e,pos);
}

int getByRank(int node,int s,int e,int r) {
	if(s == e) return s;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= ST[left]) return getByRank(left,s,m,r);
	else return getByRank(right,m+1,e,r - ST[left]);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",P + i),P[i]++;
	loop(i,n) scanf("%d",Q + i),Q[i]++;

	for(int i = n-1;i >= 0;i--){
		rP[i] = getRank(1,1,n,P[i]);
		update(1,1,n,P[i],1);
	}


	assert(ST[1] == n);
	range(i,1,n) update(1,1,n,i,-1);
	assert(ST[1] == 0);


	for(int i = n-1;i >= 0;i--){
		rQ[i] = getRank(1,1,n,Q[i]);
		update(1,1,n,Q[i],1);
	}

	assert(ST[1] == n);
	range(i,1,n) update(1,1,n,i,-1);
	assert(ST[1] == 0);


	for(int i = n-1,len = 1,r = 0;i >= 0;i--,len++) {
		r += rP[i] + rQ[i];
		T[i] = r%len;
		r /= len;
	}

//	prArr(rP,n,int);
//	prArr(rQ,n,int);
//	prArr(T,n,int);


	range(i,1,n) update(1,1,n,i,1);
	loop(i,n) {
		int x = getByRank(1,1,n,T[i] + 1);
		printf("%d%c",x-1," \n"[i==n-1]);
		update(1,1,n,x,-1);
	}
	return 0;
}
