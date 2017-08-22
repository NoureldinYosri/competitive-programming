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

const int MAX = 300*1000 + 10;
int A[MAX],n,q,m;
vi ST[MAX*3];
vi IDX[MAX];
vi *Q[20];
int cur[20];
vi cand;

void build(int node,int s,int e){
	ST[node].reserve(e - s + 1);
	for(int i = s;i <= e;i++) ST[node].pb(A[i]);
	sort(all(ST[node]));
	ST[node].resize(unique(all(ST[node])) - ST[node].begin());
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}

void query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) {
		Q[m++] = &ST[node];
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	query(left,s,m,l,m);
	query(right,m+1,e,m+1,e);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&q);
	range(i,1,n) {
		scanf("%d",A + i);
		IDX[A[i]].pb(i);
	}
	build(1,1,n);
	while(q--) {
		int l,r,k; scanf("%d %d %d",&l,&r,&k);
		k = (r - l + 1)/k;
		m = 0;
		query(1,1,n,l,r);
		int ctr = m;
		loop(i,m) {
			cand[i] = Q[i]->at(0);
			cur[i] = 0;
		}
		int ans = -1;
		while(ans == -1 && ctr) {
			sort(cand,cand + ctr);
			ctr = unique(cand,cand + ctr) - cand;
			int x = cand[0],cnt = upper_bound(all(IDX[x]),r) - lower_bound(all(IDX[x]),l);
			if(cand > k) {
				ans = x;
				break;
			}
			swap(cand[0],cand[ctr-1]);
			ctr--;
			loop(i,m){
				if(cur[i] < (int)Q[i]->size() && Q[i]->at(cur[i]) == x) {
					cur[i]++;
					if(cur[i] < (int)Q[i]->size())
						cand[ctr++] =  Q[i]->at(cur[i]);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
