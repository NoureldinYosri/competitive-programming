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

const int MAX = 200000;
int trie[MAX*30][2],siz = 0;
int cnt[MAX*30];
void insert(int v){
	int cur = 0;
	for(int bit = 1 << 29;bit;bit >>= 1){
		cnt[cur]++;
		int b = (v & bit) ? 1 :0;
		if(!trie[cur][b]) trie[cur][b] = ++siz;
		cur = trie[cur][b];
	}
	cnt[cur]++;
}

void erase(int v){
	int cur = 0;
	for(int bit = 1 << 29;bit;bit >>= 1){
		cnt[cur]--;
		int b = (v & bit) ? 1 :0;
		cur = trie[cur][b];
	}
	cnt[cur]--;
}

int query(int cur,int bit,int v,int l){
	if(!bit) return cnt[cur];

}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif

	return 0;
}
