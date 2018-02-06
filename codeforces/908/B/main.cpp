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

const int MAX = 111;

char G[MAX][MAX];
char ord[MAX];
int dx[] = {0,-1,0,1},dy [] = {-1,0,1,0};
int m,n;
pi S,E;

bool follow(int *f){
	int x = S.xx,y = S.yy;
	for(char *p = ord;*p;p++){
		int dir = f[*p - '0'];
		x += dx[dir],y += dy[dir];
		if(x < 0 || x >= m || y < 0 || y >= n) return 0;
		if(G[x][y] == '#') return 0;
		if(G[x][y] == 'E') return 1;
	}
	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&m,&n);
	loop(i,m) {
		scanf("%s",G[i]);
		loop(j,n) {
			if(G[i][j] == 'S') S = mp(i,j);
			if(G[i][j] == 'E') E = mp(i,j);
		}

	}
	scanf("%s",ord);

	int f[4],ans = 0;
	loop(i,4) f[i] = i;
	do{
		ans += follow(f);
	}while(next_permutation(f,f + 4));
	printf("%d\n",ans);
	return 0;
}
