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

int C;
int A[1000];
vector<string> G;
int who[1000];
queue<int> q;

int solve(){
	if(A[0] == 0 || A[C-1] == 0) return -1;
	int s = 0;
	loop(i,C) s += A[i];
	if(s != C) return -1;
	int r = 0;
	loop(i,C) q.push(i);
	loop(i,C) {
		while(!q.empty() && A[q.front()] == 0) q.pop();
		if(q.empty()) return -1;
		who[i] = q.front();
		A[q.front()]--;
		r = max(r,abs(i - who[i]));
	}
	if(q.size() != 1 && A[q.front()] != 0) return -1;
	while(!q.empty()) q.pop();
	r++;
	G = vector<string>(r,string(C,'.'));
	loop(i,C) {
		int cur = i,row = 0;
		while(cur != who[i]) {
			if(cur < who[i])
				G[row][cur] = '\\';
			else
				G[row][cur] = '/';
			row++;
			cur += (who[i] > cur) - (who[i] < cur);
		}
	}

	return r;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif

	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d",&C);
		loop(i,C) scanf("%d",A + i);
		printf("Case #%d: ",t);
		int r = solve();
		if(r == -1) puts("IMPOSSIBLE");
		else {
			printf("%d\n",r);
			loop(i,r) puts(G[i].c_str());
		}
	}


	return 0;
}
