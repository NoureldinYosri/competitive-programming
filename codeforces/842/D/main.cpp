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

const int MAXN = 300*1000 + 10,MAX = MAXN * 21;

int trie[MAX][2],siz = 0;
int cnt[MAX],LA[MAX];

void insert(int x){
	static set<int> S;
	if(S.find(x) != S.end()) return;
	S.insert(x);
	int cur = 0;
	//cerr << "for " << x << " : ";
	for(int i = 19;i >= 0;i--){
	//	cerr << cur << " ";
		int b = 0;
		if(x & (1 << i)) b = 1;
		cnt[cur]++;
		if(trie[cur][b] == -1) trie[cur][b] = ++siz;
		cur = trie[cur][b];
	}
	cnt[cur]++;
	//cerr << cur << endl;
}

int solve(int root,int x,int bit = 19){
	if(bit==-1 || root == -1) return 0;
	x ^= LA[root];
	LA[root] = 0;
	if(x & (1 << bit)) {
	//	cerr << "swap" << endl;
		swap(trie[root][0],trie[root][1]);
	}
	x &= ((1 << bit)) - 1;
	int cnt0 = 0;
	if(trie[root][0] != -1) cnt0 = cnt[trie[root][0]];
	else if(root == 0) cnt0 = INT_MAX;
	int desired = (1 << bit) ;
	//cerr << "root " << root << " bit " << bit << " cnt0 " << cnt0 << " desired " << desired << " ,x = " << x << " left " << trie[root][0] << endl;
	if(cnt0 < desired) {
	//	cerr << "go left" << endl;
		if(trie[root][1] != -1) LA[trie[root][1]] ^= x;
		return solve(trie[root][0],x,bit - 1);
	}
	else {
	//	cerr << "go right" << endl;
		if(trie[root][0] != -1) LA[trie[root][0]] ^= x;
		return solve(trie[root][1],x,bit - 1) | (1 << bit);
	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	memset(trie,-1,sizeof trie);
	int n,m; scanf("%d %d",&n,&m);
	loop(i,n){
		int x; scanf("%d",&x);
		insert(x);
	}
	while(m--){
		int x; scanf("%d",&x);
		printf("%d\n",solve(0,x));
		//break;
	}
	return 0;
}
