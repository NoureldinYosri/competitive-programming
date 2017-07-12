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

const int MAX = 3*200000;
string name[MAX];
int cur[MAX],nxt[MAX],n,m;
char buffer[MAX];

int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	//	freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);
	range(i,1,n){
		scanf("%s",buffer);
		name[i] = string(buffer);
		cur[i] = i;
		nxt[i] = 0;
	}
	scanf("%d",&m);
	for(int k = 0,j = n + 1;k < m;k++,j++){
		int x,y; scanf("%d %d",&x,&y);
		nxt[j] = cur[y];
		cur[x] = j;
	}
	for(int e = cur[1];e;e = nxt[e]){
		if(e <= n) puts(name[e].c_str());
		else printf("I_love_");
	}
	return 0;
}
