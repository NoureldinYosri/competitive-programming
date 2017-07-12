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

char buffer[30];
int P[26];
int nxt[26],vis[26];
int can[30],cant[30];
vi seq;

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%s",buffer);
		loop(i,26) P[i] = buffer[i] - 'A';
		memset(vis,0,sizeof vis);
		memset(can,0,sizeof can);
		memset(cant,0,sizeof cant);
		for(int i = 0;i < 26;i++)
			if(P[i] != i && !vis[i]){
				int u = i;
				seq.clear();
				while(!vis[u]){
					vis[u] = 1;
					seq.pb(u);
					u = P[u];
				}
				bool cond = 1;
				int n = sz(seq);
				if(n & 1){
					int step = n/2 + 1;
					for(int i = 0;i < n;i++)
						nxt[seq[i]] = seq[(i + step)%n];
					for(int i = 0;i < n && cond;i++){
						int x = seq[i];
						if (P[x] != nxt[nxt[x]])
							cond = 0;
					}
				}
				if(cond) can[n]++;
				else cant[n]++;
			}
		bool cond = 1;
		range(len,2,26){
			if(len%2 == 0){
				if(can[len] & 1)
					cond = 0;
			}
			else{
				if(cant[len]%2 == 1 && can[len] == 0)
					cond = 0;
			}
			if(!cond) break;
		}
		puts(cond ? "Yes" : "No");
	}
	return 0;
}
