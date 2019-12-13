#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


int n;
int A[1 << 20];

vi bad[1 << 20];
bool good[1 << 20];
int ans[1 << 20];
queue<int> q;

void bfs(){
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : bad[u]){
			if(ans[v] != -1) continue;
			ans[v] = ans[u] + 1;
			q.push(v);
		}
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	loop(i,n){
		for(int s = -1;s <= 1;s += 2){
			int j = i + s*A[i];
			if(j < 0 || j >= n) continue;
			if(A[i]%2 != A[j]%2)
				good[i] = 1;
			else
				bad[j].push_back(i);
		}
	}
	memset(ans,-1,sizeof ans);
	loop(p,2) {
		loop(i,n) if(good[i] && A[i]%2 == p) q.push(i),ans[i] = 1;
		bfs();
	}
	loop(i,n) printf("%d%c",ans[i]," \n"[i==n-1]);
	return 0;
}
