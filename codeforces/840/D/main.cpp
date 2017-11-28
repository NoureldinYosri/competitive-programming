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


struct holder{
	int x,cnt;
public:
	bool operator < (const holder & o){
		return tie(o.cnt,x) < tie(cnt,o.x);
	}
};
const int MAX = 300*1000 + 10,MAXS = 8;
int A[MAX],n,q,m;
int ST[MAX*4][MAXS];
int cnt[MAX*4];
vi IDX[MAX];
holder aux[MAX];
int B[MAX],len_aux;
int Q[MAXS*20],len_Q;

void finalize(int *A,int m,int node){
	len_aux = 0;
	for(int i = 0;i < m;){
		int j = i;
		while(j < m && A[i] == A[j]) j++;
		aux[len_aux++] = holder({A[i],j - i});
		i = j;
	}
	sort(aux,aux + len_aux);
	for(;cnt[node] < MAXS && cnt[node] < len_aux;cnt[node]++)
		ST[node][cnt[node]] = aux[cnt[node]].x;
}

void build(int node,int s,int e){
	if(s == e) {
		B[0] = A[s];
		return finalize(B,1,node);
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	int i = s,j = m+1,idx = 0;
	while(i <= m && j <= e) {
		if(A[i] < A[j]) B[idx++] = A[i++];
		else B[idx++] = A[j++];
	}
	while(i <= m) B[idx++] = A[i++];
	while(j <= e) B[idx++] = A[j++];
	assert(idx == e - s + 1);
	copy(B,B + idx,A + s);
	finalize(B,idx,node);
}

void query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) {
		for(int x : ST[node]) Q[len_Q++] = x;
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
		len_Q = 0;
		query(1,1,n,l,r);
		sort(Q,Q + len_Q);
		len_Q = unique(Q,Q + len_Q) - Q;
		int ans = -1;
		loop(i,len_Q){
			int x = Q[i];
			int cnt = upper_bound(all(IDX[x]),r) - lower_bound(all(IDX[x]),l);
			if(cnt > k) {
				ans = x;
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
