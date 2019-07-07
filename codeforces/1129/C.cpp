#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int mod = 1e9 + 7,mod2 = 1e9 + 9;
const int base1 = 5,base2 = 3;

int add(int a,int b,int mod) {
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b,int mod) {
	return (a*(ll)b)%mod;
}
// "0011", "0101", "1110", and "1111".
int forbidden [] = {3,5,14,15};


int dp[3000 + 1][3000 + 1];
int m;
int A[3000 + 1];
vp good;
int ans[3 << 10];

bool isForbidden(int len,int x) {
	if(len != 4) return 0;
	return x == 3 || x == 5 || x == 14 || x == 15;
}


int getKthBit(int batIdx,int bit) {
	return (good[batIdx].yy >> bit) & 1;
}


bool isInstance(int s,int e,int i) {
	int len = e-s+1;
	if(len != good[i].xx) return 0;
	for(int j = 0;j < len;j++){
		int b = (good[i].yy >> (len-j-1))&1;
		if(A[s+j] != b)
			return 0;
	}
	return 1;
}


string c2s(int len,int x) {
	string s(len,'0');
	for(int i = 0;i < len;i++)
		s[i] = ((x >> i) & 1) + '0';
	reverse(all(s));
	return s;
}
int solve(int s,int e) {
	if(s > e) return 1;
	int & ret = dp[s][e];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 0;i < 26;i++) {
		for(int j = 1;j <= 4 && s+j-1 <= e;j++)
			if(isInstance(s,s+j-1,i)){
				int tmp = solve(s+j,e);
				ret = add(ret,tmp,mod);
			}
	}
	return ret;
}

int trie[3000*3000][2];
int siz = 1;

int insert(int e) {
	int ret = 0,cur = 0;
	for(int s = e;s >= 0;s--) {
		if(!trie[cur][A[s]]) {
			trie[cur][A[s]] = siz++;
			ret = add(ret,solve(s,e),mod);
		}
		cur = trie[cur][A[s]];
	}
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("C.in","r",stdin);
#endif

	for(int len = 1;len <= 4;len++)
		for(int i = 0;i < (1 << len);i++)
			if(!isForbidden(len,i))
				good.push_back(mp(len,i));


	scanf("%d",&m);
	loop(i,m) scanf("%d",A + i);


	memset(dp,-1,sizeof dp);

	unordered_set<ll> S;
	int ans = 0;
	for(int e = 0;e < m;e++) {
		ans = add(ans,insert(e),mod);
		printf("%d\n",ans);
	}


	return 0;
}
