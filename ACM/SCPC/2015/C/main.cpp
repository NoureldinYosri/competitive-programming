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

const int MAX = 500*1000 + 10;
char buffer[MAX];
int trie[MAX][26],cnt;
map<int,int> M[MAX];
string S[MAX];
int ord[MAX],n;

void clean(){
	for(int u = 0;u <= cnt;u++) {
		M[u].clear();
		fill(trie[u],trie[u + 1],0);
	}
	cnt = 0;
}


void insert(const char *ptr,int who,int idx) {
	int cur = 0;
	for(;*ptr;ptr++) {
		int siz = sz(M[cur]);
		M[cur][who] = siz;
		int c = *ptr - 'a';
		if(!trie[cur][c]) trie[cur][c] = ++cnt;
		cur = trie[cur][c];
 	}
	int siz = sz(M[cur]);
	M[cur][who] = siz;
}

int solve(const char *ptr,int who) {
	int ans = INT_MAX;
	int cur = 0;
	int t = 0;
	for(;*ptr;ptr++) {
		int a = M[cur][who],b = sz(M[cur]) - a;
		int ctr = min(a,b);
		ctr ++;
		ans = min(ans,t + ctr);

		int c = *ptr - 'a';
		cur = trie[cur][c];
		++t;
	}
	int ctr = M[cur][who];
	if(ctr == sz(M[cur]) -1) ctr = min(ctr,1);
	ctr ++;
	ans = min(ans,t + ctr);
	return ans;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d",&n);
		loop(i,n) {
			scanf("%s",buffer);
			S[i] = string(buffer);
			ord[i] = i;
		}
		sort(ord,ord + n,[](const int & a,const int & b) {
			return S[a] < S[b];
		});
//		loop(i,n){
//			cerr << S[ord[i]] << " ";
//		}
//		cerr << endl;
//		cerr << "lst word is : " << S[n-1] << endl;
		loop(i,n) insert(S[ord[i]].c_str(),ord[i],i);
		loop(i,n) printf("%d%c",solve(S[i].c_str(),i)," \n"[i==n-1]);
		clean();
	}
	return 0;
}
