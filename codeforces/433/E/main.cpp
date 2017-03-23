#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
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
using namespace std;

const int MAX = 300;
const int mod = 1e9 + 7;
int trie[MAX][20],fail[MAX],cnt = 1;
vector<pi > children[MAX];
vi output[MAX];
int memo[MAX][20],val[MAX],tot[MAX];
int dp[MAX][MAX][MAX][2][2];

void insert(int *P,int n,int id){
	int cur = 0;
	for(int i = 0;i < n;i++){
		int *ptr = P + i;
		if(!trie[cur][*ptr]) {
			children[cur].pb(mp(*ptr,cnt));			
			trie[cur][*ptr] = cnt++;
		}
		cur = trie[cur][*ptr];
	}
	output[cur].pb(id);
}

void BuildFailureFunction(){
	queue<int> q; 	
	fail[0] = 0;
	for(auto & e : children[0]) {
		fail[e.yy] = 0;
		q.push(e.yy);
	}
	while(!q.empty()){
		int p = q.front(); q.pop();
		for(auto & e : children[p]){
			int c = e.xx;
			int u = e.yy,v = fail[p];
			while(!trie[v][c] && v) v = fail[v];
			fail[u] = v = trie[v][c];
			for(int x : output[v])
				output[u].pb(x);
			sort(all(output[u]));
			output[u].resize(unique(all(output[u])) - output[u].begin());
			q.push(u);
		}
	}
}

int get_next(int cur,int v){
	if(memo[cur][v] != -1) return memo[cur][v];	
	int & ret = memo[cur][v];
	while(!trie[cur][v] && cur) cur = fail[cur];
	cur = trie[cur][v];
	return ret = cur;
}

vi readNumber(){
	int len; scanf("%d",&len);
	vi A(len);
	loop(i,len) scanf("%d",&A[i]);
	return A;
}

vi target;
int base;
int buffer[MAX];

int solve(int pos,int node,int k,int isEqual,int isZero){
//	cerr << pos << " " << node << " " << k << " " << isEqual << endl;
	if(pos == sz(target)) return 1;
	int & ret = dp[pos][node][k][isEqual][isZero];
	if(ret != -1) return ret;
	ret = 0;
	for(int digit = 0;digit < base;digit++){
		if(isEqual && digit > target[pos]) continue;
		int nxt = get_next(node,digit);
		int val = tot[nxt];
		if(isZero && digit == 0) {
//			assert(node == 0);		
			val = 0;
			nxt = 0;
		}
		if(val > k) continue;
		ret += solve(pos + 1,nxt,k - val,isEqual && (digit == target[pos]),isZero && digit == 0);
		if(ret >= mod) ret -= mod;	
	}
//	cerr << pos << " " << node << " " << k << " " << isEqual << " -> " << ret<< endl;
	return ret;
}

int main(){
	int n,k;
	scanf("%d %d %d",&n,&base,&k);
	
	vi L = readNumber();
	vi R = readNumber();
	
	loop(i,n){
		vi N = readNumber();
		copy(N.begin(),N.end(),buffer);
		insert(buffer,sz(N),i);
		scanf("%d",val + i);
	}
	BuildFailureFunction();
	loop(i,cnt) {
		for(int x : output[i]){
			tot[i] += val[x];
		//	assert(tot[i] >= 0);
		}
	}	
	
	memset(memo,-1,sizeof memo);
	memset(dp,-1,sizeof dp);
	
	target = R;
	int ans = solve(0,0,k,1,1);
//	cerr << ans << endl;
	memset(dp,-1,sizeof dp);
	for(int i = sz(L) - 1;i >= 0;i--){
		L[i]--;
		if(L[i] < 0) L[i] = base - 1;
		else break;
	}
	target = L;
	ans -= solve(0,0,k,1,1);
//	cerr << solve(0,0,k,1,1) << endl;
	if(ans < 0) ans += mod;
//	cerr << ans << endl;
	cout << ans << endl;

	return 0;
}
