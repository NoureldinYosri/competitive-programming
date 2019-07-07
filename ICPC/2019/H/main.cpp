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

const int MAX = 500*1000 + 10;
int nxt[MAX];
int n,K;
bool notInCycle[MAX],inCycle[MAX];
int inDeg[MAX],ans[MAX];
vi rG[MAX];
bool vis[MAX];

vp updates;
int BIT[MAX];
vi D[MAX];

void add(int p,int v,bool store = 1) {
	if(store) updates.push_back(mp(p,v));
	for(++p;p < MAX;p += LSOne(p))
		BIT[p] += v;
}
int get(int p) {
	int ret = 0;
	for(p = min(p+1,MAX-1);p;p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}
void clear(){
	for(auto pv : updates)
		add(pv.first,-pv.second,0);
	updates.clear();
}


void detectCycles(){
	static queue<int> q;
	for(int i = 1;i <= n;i++)
		inDeg[nxt[i]]++;
	for(int i = 1;i <= n;i++)
		if(!inDeg[i])
			q.push(i);
	while(!q.empty()){
		int u = q.front(); q.pop();
		notInCycle[u] = 1;
		int v = nxt[u];
		inDeg[v]--;
		if(inDeg[v] == 0) q.push(v);
	}
	for(int i = 1;i <= n;i++)
		inCycle[i] = !notInCycle[i];
}

void dfs(int u,int d) {
	ans[u] = -(get(d + K) - get(d));
	for(int v : rG[u])
		dfs(v,d + 1);
	ans[u] += get(d+K) - get(d) + 1;
	add(d,1);
}

void compress(int u){
	static vi V;
	V.clear();
	V.push_back(0);
	int prv = 0;
	for(int h = 0;h < K;h++) {
		int v = get(h);
		assert(v >= prv);
		if(prv == v) break;
		V.push_back(v);
		prv = v;
	}
//	print(D[u],int);
//	print(V,int);
	int a = 0,b = 0;
	for(int h = 0;h < sz(D[u]) || h < sz(V);h++){
		a = (h < sz(D[u])) ? D[u][h] : a;
		b = (h < sz(V)) ? V[h] : b;
		if(h == sz(D[u])) D[u].push_back(0);
		D[u][h] = a + b;
	}
//	print(D[u],int);
//	cerr << string(100,'*') << endl;
}

vector<vi> cycles,sums;
int id[MAX],pos[MAX],m;

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
	freopen("/home/noureldin/Desktop/competitive-programming/ICPC/2019/icpc2019data/H-hobsonstrains/secret-16.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	scanf("%d %d",&n,&K);
	for(int i = 1;i <= n;i++) {
		scanf("%d",nxt + i);
		rG[nxt[i]].push_back(i);
//		cerr << i << " " << nxt[i] << endl;
	}
	detectCycles();
	for(int i = 1;i <= n;i++) {
		if(!inCycle[i] && inCycle[nxt[i]]) {
			dfs(i,0);
			compress(nxt[i]);
			clear();
		}
	}
//	prArr(inCycle+1,n,bool);
//	prArr(ans+1,n,int);

	for(int i = 1;i <= n;i++){
		if(!inCycle[i] && !vis[i]) continue;
		int u = i;
		cycles.push_back(vi());
		sums.push_back(vi());
		while(!vis[u]) {
			vis[u] = 1;
			id[u] = m;
			pos[u] = cycles.back().size();
			cycles.back().push_back(u);
			sums.back().push_back(0);
			u = nxt[u];
		}
		m++;
	}
	for(int i = 1;i <= n;i++){
		if(!inCycle[i]) continue;
		vi & vals = D[i];
		if(sz(vals) <= 1) continue;
		int j = pos[i];
		vi & cycle = cycles[id[i]];
		vi & sum = sums[id[i]];
		int d = K+1-sz(vals);
//		cerr << i << " @" << j << " " << d << " " << vals.back()  << " " << sz(vals) << endl;
//		print(vals,int);
		if(d >= sz(cycle)) {
			sum[0] += vals.back();
			continue;
		}
		else {
			sum[j] += vals.back();
			if(j+d < sz(cycle)) {
				sum[j+d] -= vals.back();
				j = (j + d)%sz(cycle);
			}
			else {
				sum[0] += vals.back();
				j = (j + d)%sz(cycle);
				sum[j] -= vals.back();
			}
		}
		int u = cycle[j];
//		cerr << "lead to " << u << endl;
		while(sz(vals) > 1 && d < sz(cycle)) {
			ans[u] += vals.back();
			vals.pop_back();
			u = nxt[u];
			d++;
		}
	}
	for(int c = 0;c < m;c++) {
		vi & cycle = cycles[c];
		vi & sum = sums[c];
//		print(sum,int);
		int s = 0;
		for(int i = 0;i < sz(cycle);i++) {
			s += sum[i];
			ans[cycle[i]] += s;
		}
	}
//	prArr(ans+1,n,int);
	for(int i = 1;i <= n;i++) {
		if(!inCycle[i]) continue;
		vi & cycle = cycles[id[i]];
		int val = min(sz(cycle),K+1);
		ans[i] += val;
	}

	for(int i = 1;i <= n;i++)
		printf("%d\n",ans[i]);


	return 0;
}


/*
7 4
2
3
4
1
1
5
6


7
7
6
5
3
2
1
 */
