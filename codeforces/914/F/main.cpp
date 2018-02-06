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


const int MAXN = 100*1000 + 10,BLKSIZ = 250,MAXB = MAXN/BLKSIZ + 10,MAXSA = 3*MAXN + 3*MAXB;
char S[MAXN],buffer[MAXN];
int n,m;
bool flag[MAXB];

//suffixAutomata
int to[MAXSA][26];
int link[MAXSA],len[MAXSA],cnt[MAXSA],isTerminal[MAXSA];

struct suffixAutomata{
	int q0,nq;
	int offset,st;

	inline int create_state(){
		int q = offset++;
		link[q] = st;
		len[q] = 0;
		fill(to[q],to[q + 1],-1);
		cnt[q] = -1;
		isTerminal[q] = 0;
		return q;
	}

	void init(int id){
		st = offset = id*BLKSIZ*2 + 10*id;
		nq = q0 = create_state();
	}


	inline void insert(int c){
		c -= 'a';
		int q = nq;
		nq = create_state();
		len[nq] = len[q] + 1;
		while(to[q][c] == -1) {
			to[q][c] = nq;
			q = link[q];
		}
		if(to[q][c] == nq) link[nq] = st;
		else{
			int t = to[q][c];
			if(len[t] == len[q] + 1) link[nq] = t;
			else {
				int clone = create_state();
//				to[clone] = to[t];
				copy(to[t],to[t] + 128,to[clone]);
				link[clone] = link[t];
				len[clone] = len[q] + 1;
				link[nq] = link[t] = clone;
				while(to[q][c] == t) {
					to[q][c] = clone;
					q = link[q];
				}
			}
		}
	}


	inline int get_count(int u){
		if(cnt[u] != -1) return cnt[u];
		int & ret = cnt[u];
		ret = isTerminal[u];
		for(int c = 0;c < 26;c++)
			ret += get_count(to[u][c]);
		return ret;
	}

	inline void setTerminal(){
		int u = nq;
		while(u != st){
			isTerminal[u] = 1;
			u = link[u];
		}
	}

	inline int get_count(char *S) {
		int cur = st;
		for(char *p = S;*p;p++) {
			if(to[cur][*p - 'a'] == -1) return 0;
			cur = to[cur][*p - 'a'];
		}
		return get_count(cur);
	}
};

suffixAutomata SA[MAXB];
int mem[MAXN][26];
int fail[MAXN];
int L;

struct KMP{
	inline int get_len(char c,int len) {
		if(mem[len][c - 'a'] != -1) return mem[len][c - 'a'];
		int & ret = mem[len][c - 'a'];
		while(len > 0 && buffer[len] != c) len = fail[len - 1];
		if(c == buffer[len]) len++;
		return ret = len;
	}
	void changeString() {
		for(int i = 0;i < L;i++)
			fill(mem[i],mem[i + 1],-1);
		for(int i = 1;i < L;i++)
			fail[i] = get_len(buffer[i],fail[i - 1]);
	}
	inline int get_count(int s,int e,char *T) {
		int l = 0, ret = 0;
		for(int i = s;i <= e;i++){
			l = get_len(T[i],l);
			if(l == L) {
				l = fail[L - 1];
				ret++;
			}
		}
		return ret;
	}
};



inline void buildDS(int u) {
	int B = u*BLKSIZ,E = min(n,B + BLKSIZ);
	SA[u].init(u);
	for(int i = B;i < E;i++)
		SA[u].insert(S[i]);
	SA[u].setTerminal();
	SA[u].get_count(SA[u].st);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif

	scanf("%s",S);
	n = strlen(S);

	for(int i = 0,j = 0;i < n;i += BLKSIZ,j++)
		buildDS(j);

	KMP kmp;
	scanf("%d",&m);
	while(m--) {
		int ct; scanf("%d",&ct);
		if(ct == 1){
			int p; char c;
			scanf("%d %c",&p,&c);
			--p;
			S[p] = c;
			flag[p/BLKSIZ] = 1;
//			buildDS(p/BLKSIZ);
		}
		else{
			int l,r; scanf("%d %d %s",&l,&r,buffer);
			--l,--r;
			L = strlen(buffer);
			int u = l/BLKSIZ,v = r/BLKSIZ,ans = 0;
			kmp.changeString();

			if(L >= BLKSIZ) {
				ans = kmp.get_count(l,r,S);
			}
			else{
				for(int t = u + 1;t < v;t++) {
					if(flag[t]) {
						buildDS(t);
						flag[t] = 0;
					}
					ans += SA[t].get_count(buffer);
//					cerr << "from " << t*BLKSIZ << " " << t*BLKSIZ + BLKSIZ - 1 << " got " << SA[t].get_count(buffer) << endl;
				}
				if(u != v){
					ans += kmp.get_count(l,u*BLKSIZ + BLKSIZ - 1,S);
					ans += kmp.get_count(v*BLKSIZ,r,S);
					for(int t = u;t < v && L > 1;t++) {
						int cl = t*BLKSIZ + BLKSIZ - L + 1,cr = t*BLKSIZ + BLKSIZ + L - 2;
						if(t == u) cl = max(cl,l);
						if(t+1 == v) cr = min(cr,r);
//						assert(cr-cl+1 <= 2*L-2);
						ans += kmp.get_count(cl,cr,S);
					}
				}
				else ans += kmp.get_count(l,r,S);
			}
			printf("%d\n",ans);
		}
	}

	return 0;
}
