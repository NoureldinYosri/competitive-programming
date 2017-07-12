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

const int MAX = 100*1000 + 10,MXLG = 20,DMAX = MAX*2;
char buffer[MAX],str[DMAX];
int len;
// buildSA O(nlogn)
int sa[DMAX];
int group[DMAX];
int tg[DMAX < 128 ? 128 : DMAX];
int newsa[DMAX];
int gstart[DMAX];
int ST[DMAX][MXLG],lg[DMAX];
int rev[DMAX];

void buildSA() {
	int n;
	memset(tg, -1, (sizeof tg[0]) * 128);
	for (n = 0; n == 0 || str[n - 1]; n++) {
		newsa[n] = tg[(int)str[n]];
		tg[(int)str[n]] = n;
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
	loop(i,len) rev[sa[i]] = i;
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

void buildALL(){
	buildSA();
	buildLCP();
	loop(i,len) sa[i] = sa[i+1];
	precompute();
}

char A[MAX],B[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int n,m,x;
	cin >> n >> A;
	cin >> m >> B;
	cin >> x;
	strcpy(str,B);
	str[m] = '$';
	strcpy(str+m+1,A);
	str[n+m+1] = '#';
	len = n+m+2;
	buildALL();

	set<int> dead;

	int cur = 0,ctr = 0,j = 0;
	while(cur != m) {
		int best = 0,which = 0;
		for(int i = j;i < n;i++)  {
			int tmp = get_lcp(cur,i + m + 1);
			if(best < tmp) {
				best = tmp;
				which = i;
			}
		}
//		cerr << cur << " " << best << " " << which << endl;
		cur += best;
		j = which + best;
		ctr++;
		if(!best || ctr > x) {
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
