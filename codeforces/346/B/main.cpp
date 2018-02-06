#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
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

const int maxn = 4e5 + 42; // Maximum amount of states
map<char, int> to[maxn]; // Transitions
int link[maxn]; // Suffix links
int len[maxn]; // Lengthes of largest strings in states
int last = 0; // State corresponding to the whole string
int sz = 1; // Current amount of states

void clean(){
	loop(i,sz) len[i] = 0,link[i] = 0,to[i].clear();
	last = 0;
	sz = 1;
}

inline void add_letter(char c) // Adding character to the end
{
	int p = last; // State of string s
	last = sz++; // Create state for string sc
	len[last] = len[p] + 1;
	for (; to[p][c] == 0; p = link[p]) // (1)
		to[p][c] = last; // Jumps which add new suffixes
	if (to[p][c] == last) { // This is the first occurrence of c if we are here
		link[last] = 0;
		return;
	}
	int q = to[p][c];
	if (len[q] == len[p] + 1) {
		link[last] = q;
		return;
	}
// We split off cl from q here
	int cl = sz++;
	to[cl] = to[q]; // (2)
	link[cl] = link[q];
	len[cl] = len[p] + 1;
	link[last] = link[q] = cl;
	for (; to[p][c] == q; p = link[p]) // (3)
		to[p][c] = cl; // Redirect transitions where needed
}



void explore(int u) {
	for(auto p : to[u])
		cerr << u << " " << p.yy << " " << p.xx << endl;
	for(auto p : to[u])
		explore(p.yy);
}

char S[90000 + 10];
ll cnt[90000*2 + 10];

char out[maxn];
int m;

int main() {
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%s",S);
		int n = strlen(S),N = 2*n;
		strncpy(S+n,S,n);
		S[N] = 0;
		for(char *p = S;*p;p++) add_letter(*p);
		m = 0;
		int u = 0;
		while(!to[u].empty()) {
			out[m++] = to[u].begin()->xx;
			u = to[u].begin()->yy;
		}
		int s = N-m,e = (s + m)%N;
		assert(s < n);
//		while(m < N) {
//			out[m++] = S[e];
//			e = (e+1)%n;
//		}
//		puts(out);

		printf("%d\n",s+1);
		clean();
	}
	return 0;

}
