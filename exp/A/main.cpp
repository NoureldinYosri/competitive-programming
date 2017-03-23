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
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

map<int,int> dp;

int solve(int x){
	if(x == 1) return dp[1] = 0;
	queue<int> q;
	q.push(x);
	set<int> vis; vis.insert(x);
	int mn = INT_MAX;
	for(int d = 0;!q.empty();d++){
		for(int i = 0,L = q.size();i < L;i++){
			int u = q.front(); q.pop();
			if(dp.find(u) != dp.end()) {
				mn = min(mn,d + dp[u]);
				continue;
			}
			if(d >= mn) continue;
			int v = u + 1;
			if(vis.find(v) == vis.end()) {
				vis.insert(v);
				q.push(v);
			}
			v = u - 1;
			if(vis.find(v) == vis.end()) {
				vis.insert(v);
				q.push(v);
			}
			if(u%2 == 0){			
				v = u >> 1;			
				if(vis.find(v) == vis.end()) {
					vis.insert(v);
					q.push(v);
				}
			}
		}
	}	
	return dp[x] = mn;
}


int mn;
void g(ll x,int d){
	if(d >= mn) return ;
	while(x%2 == 0) d++,x >>= 1;
	if(x == 1) mn = min(mn,d);
	else g(x + 1,d + 1),g(x - 1,d + 1);
}

int solve2(ll x){
	mn = INT_MAX;
	g(x,0);
	return mn;
}

int f(int x){
	int i = 0,ret = 0;
	for(;x > 1; x >>= 1){
		if(x & 1) ret += i;	
		i++;
	}
	return ret;
}

int main(){
	solve(1);
	/*int MAX = 50;
	for(int i = 1;i <= MAX;i++)
		if(i == LSOne(i)) 
			for(int j = i;j > 1;j >>= 1)
				dp[i]++;
	for(int i = 1;i <= MAX;i++){
		if(i == LSOne(i)) cerr << "power of 2 -> " << dp[i] << " " << solve2(i) << endl;
		else cerr << i << " " << solve(i) << " " << solve2(i) << endl ;
		if(i%2 == 0) assert(dp[i] == dp[i/2] + 1);	
	}
	*/
	for(int i = 3;i <= 1000;i += 2){
		int ci = solve(i);
		int a = i - 1,b = i + 1;
		int cl = solve(a),cr = solve(b);
		int x = f(a),y = f(b);
		if(x > y) swap(x,y),swap(cl,cr),swap(a,b);
		if(cl > cr) cerr << a << " " << cl << " " << b << " " << cr << endl;
		assert(cl <= cr);
	}
	return 0;
}
