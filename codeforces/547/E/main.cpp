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

const int MAX = 200*1000 + 10,MXLG = 20,DMAX = MAX*2,MEM = 20;
char buffer[MAX],str[DMAX];
int m,len;
int IDX[DMAX],L[MAX],R[MAX];
#define rep range

// buildSA O(nlogn)
int sa[DMAX];
int group[DMAX];
int tg[DMAX < 128 ? 128 : DMAX];
int newsa[DMAX];
int gstart[DMAX];
void buildSA() {
	int n;
	memset(tg, -1, (sizeof tg[0]) * 128);
	for (n = 0; n == 0 || str[n - 1]; n++) {
		newsa[n] = tg[str[n]];
		tg[str[n]] = n;
	}
	int ng = -1, j = 0;
	for (int i = 0; i < 128; ++i) {
	if (tg[i] != -1) {
	gstart[++ng] = j;
	int cur = tg[i];
	while (cur != -1) {
	sa[j++] = cur;
	group[cur] = ng;
	cur = newsa[cur];
	}
	}
	}
	tg[0] = tg[n - 1] = 0;
	newsa[0] = sa[0];
	for (int h = 1; tg[n - 1] != n - 1; h <<= 1) {
	for (int i = 0; i < n; ++i) {
	j = sa[i] - h;
	if (j < 0)
	continue;
	newsa[gstart[group[j]]++] = j;
	}
	for (int i = 1; i < n; ++i) {
	bool newgroup = group[newsa[i - 1]] <
	group[newsa[i]]
	|| group[newsa[i - 1]] ==
	group[newsa[i]]
	&& group[newsa[i - 1] +
	h] < group[newsa[i]
	+ h];
	tg[i] = tg[i - 1] + newgroup;
	if (newgroup)
	gstart[tg[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
	sa[i] = newsa[i];
	group[sa[i]] = tg[i];
	}
	}
}

int RANK[DMAX];
int LCP[DMAX];
void buildLCP() {
	int n;
	for (n = 0; n == 0 || str[n - 1]; n++)
		RANK[sa[n]] = n;
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (RANK[i]) {
			int j = sa[RANK[i] - 1];
			while (str[i + c] == str[j + c])
				c++;
		}
		if(RANK[i] > 1) LCP[RANK[i]-2] = c;
		if (c) c--;
	}
}

struct node{
	int siz;
	node *l,*r;
};
node *T[DMAX];
int start[MAX],rev[DMAX],LEN[MAX];
int ST[DMAX][MXLG],lg[DMAX];
node mem[MEM*DMAX];
int siz = 0;

node *build(int s,int e){
	node *root = &mem[siz++];
	if(s == e) return root;
	int m = (s + e) >> 1;
	root->l = build(s,m);
	root->r = build(m+1,e);
	return root;
}

node *update(node *root,int s,int e,int p){
	node *ret = &mem[siz++];
	node *cur = ret;
	while(1) {
		*cur = *root;
		cur->siz++;
		if(s == e) break;
		int m = (s + e) >> 1;
		if(p <= m) {
			e = m;
			cur->l = &mem[siz++];
			cur = cur->l;
			root = root->l;
		}
		else{
			s = m + 1;
			cur->r = &mem[siz++];
			cur = cur->r;
			root = root->r;
		}
		assert(siz < MEM*DMAX);
	}
	return ret;
}

int query(node *u,node *v,int s,int e,int p){
	int ret = 0;
	while(s < e){
		int m = (s + e) >> 1;
		if(p <= m) {
			u = u->l;
			v = v->l;
			e = m;
		}
		else{
			ret += v->l->siz - u->l->siz;
			u = u->r;
			v = v->r;
			s = m+1;
		}
	}
	ret += v->siz - u->siz;
	return ret;
}

inline int get_lcp(int a,int b){
	if(a == b) return len - a;
	a = rev[a],b = rev[b];
	if(a > b) swap(a,b);
	b--;
//	cerr << a << " " << b << endl;
	int l = lg[b - a + 1];
	return min(ST[a][l],ST[b - (1 << l) + 1][l]);
}

inline int getLeft(int k){
	int idx = rev[start[k]];
	int s = 0,e = idx;
	while(s < e){
		int m = (s + e) >> 1;
		if(get_lcp(sa[m],start[k]) >= LEN[k]) e = m;
		else s = m + 1;
	}
	return s;
}
inline int getRight(int k){
	int idx = rev[start[k]];
	if(idx == len-1) return idx;
	int s = idx,e = len-1;
	while(s < e){
		int m = (s + e) >> 1;
		if(get_lcp(sa[m],start[k]) < LEN[k]) e = m;
		else s = m + 1;
	}
	if(get_lcp(sa[s],start[k]) < LEN[k]) return s - 1;
	return s;
}

void precompute(){
	lg[0] = -1;
	loop(i,len) lg[i + 1] = lg[i] + ((i+1)==LSOne(i+1));
	loop(i,len) ST[i][0] = LCP[i];
	for(int k = 0;k + 1 < MXLG;k++)
		loop(i,len){
		int j = i + (1 << k);
		if(j >= len) j = i;
		ST[i][k + 1] = min(ST[i][k],ST[j][k]);
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int Q,n; scanf("%d %d",&n,&Q);
	loop(i,n){
		scanf("%s",buffer);
		LEN[i + 1] = m = strlen(buffer);
		start[i+1] = len;
		loop(j,m) {
			str[len] = buffer[j];
			IDX[len] = i+1;
			len++;
		}
		str[len] = '#';
		IDX[len] = 0;
		len++;
	}
	str[len] = 0;
	buildSA();
	buildLCP();
	loop(i,len) sa[i] = sa[i+1];

	T[0] = build(0,n);
	precompute();
	//	cerr << str << endl;
	loop(i,len){
		T[i + 1] = update(T[i],0,n,IDX[sa[i]]);
		rev[sa[i]] = i;
	}
//	loop(i,len){
//		cerr << i << " " << IDX[sa[i]] << " " << LCP[i] << " " << sa[i] + str << endl;
//	}
	range(i,1,n) L[i] = getLeft(i),R[i] = getRight(i);
	while(Q--){
		int l,r,k;
		scanf("%d %d %d",&l,&r,&k);
		int ans = query(T[L[k]],T[R[k] + 1],0,n,r);
		ans -= query(T[L[k]],T[R[k] + 1],0,n,l-1);
		printf("%d\n",ans);
	}
	return 0;
}
