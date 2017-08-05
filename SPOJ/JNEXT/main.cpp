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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 1000000 + 10;
int nxt[MAX],A[MAX],n;
stack<int> ST;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		memset(nxt,-1,sizeof nxt);
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		loop(i,n) {
			while(!ST.empty() && A[ST.top()] >= A[i]) ST.pop();
			if(!ST.empty()) {
				int u = ST.top();
				if(nxt[u] == -1 || A[nxt[u]] > A[i])
					nxt[u] = i;
			}
			ST.push(i);
		}
		int lst = -1;
		loop(i,n) if(nxt[i] != -1) lst = i;
		if(lst == -1) puts("-1");
		else {
			swap(A[lst],A[nxt[lst]]);
			sort(A + lst + 1,A + n);
			loop(i,n) putchar(A[i] + '0');
			puts("");
		}
		while(!ST.empty()) ST.pop();
	}
	return 0;
}
