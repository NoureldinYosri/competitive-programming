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

const int MAX = 1000*1000 + 10;
vi M[MAX];
string I[MAX];
int n;
char buffer[50];
int E[MAX*2],ML[MAX*2];
int cnt[MAX*2];
int ctr[MAX],H[MAX],L[MAX];
bool y[MAX];

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%s",buffer);
		I[i] = string(buffer);
	}
	memset(E,-1,sizeof E);
	loop(i,2*n) {
		int id;
		char type = I[i%n][0];
		sscanf(I[i%n].c_str()+1,"%d",&id);
		if(type == 's') M[id].push_back(i);
		else {
			if(M[id].empty() || I[M[id].back()%n][0] == 'e') M[id].push_back(i);
			else {
				int s = M[id].back();
				M[id].pop_back();
				E[s] = i;
			}
		}
	}
	loop(i,2*n) {
		int id;
		sscanf(I[i%n].c_str()+1,"%d",&id);
		ctr[id]++;
		cnt[i] = ctr[id];
	}

	loop(i,n){
		int id;
		sscanf(I[i%n].c_str()+1,"%d",&id);
		H[id]++;
	}
	int ans = 0,bm = 0,m = 0;

	for(int i = 2*n-1;i >= 0;i--) {
		int id;
		sscanf(I[i%n].c_str()+1,"%d",&id);
		m -= y[id];
		y[id] = 0;

		ML[i] = L[id];
		if(E[i] != -1){
			int h = cnt[E[i]] - cnt[i] + 1;
			L[id] = h + ML[E[i]];
			m += y[id] = L[id] >= H[id];
		}
		else L[id] = 0;
		if(m >= bm && i < n) {
			bm = m;
			ans = i;
		}
//		cerr << i+1 << " " << m << endl;
//		print(y,int);
	}


	cout << ans + 1  << " " << bm << endl;
	return 0;
}
