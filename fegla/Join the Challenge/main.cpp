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

int T;
char G[10][11];
char U[10][11],V[10][11];
int m,n;
int cnt[10][10];

void LEFT(){
	loop(i,m) {
		int ctr = 0;
		loop(j,n) ctr += U[i][j] == 'O';
		loop(j,n) V[i][j] = (j < ctr) ? 'O' : '.';
	}
	loop(i,m) loop(j,n) U[i][j] = V[i][j];
}

void RIGHT(){
	loop(i,m) {
		int ctr = 0;
		loop(j,n) ctr += U[i][j] == 'O';
		for(int j = n-1;j >= 0;j--) {
			if(ctr) V[i][j] = 'O',ctr--;
			else V[i][j] = '.';
		}
	}
	loop(i,m) loop(j,n) U[i][j] = V[i][j];
}

void UP(){
	loop(j,n) {
		int ctr = 0;
		loop(i,m) ctr += U[i][j] == 'O';
		for(int i = 0;i < m;i++) {
			if(ctr) V[i][j] = 'O',ctr--;
			else V[i][j] = '.';
		}
	}
	loop(i,m) loop(j,n) U[i][j] = V[i][j];
}
void DOWN(){
	loop(j,n) {
		int ctr = 0;
		loop(i,m) ctr += U[i][j] == 'O';
		for(int i = m-1;i >= 0;i--) {
			if(ctr) V[i][j] = 'O',ctr--;
			else V[i][j] = '.';
		}
	}
	loop(i,m) loop(j,n) U[i][j] = V[i][j];
}

void (*f[4])() = {UP,DOWN,LEFT,RIGHT};

int get(bool ready = 1){
	if(!ready) {
		loop(i,m) strcpy(U[i],G[i]);
	}
	loop(j,n) {
		loop(i,m) {
			cnt[i][j] = U[i][j] == 'O';
			cnt[i][j] += i ? cnt[i-1][j] : 0;
		}
	}
	int mx = 0;
	for(int x1 = 0;x1 < m;x1++)
		for(int x2 = x1;x2 < m;x2++){
			int sum = 0;
			for(int c = 0;c < n;c++){
				int tmp = cnt[x2][c] - (x1 ? cnt[x1 - 1][c] : 0);
				if(tmp == x2 - x1 + 1) {
					sum += tmp;
					mx = max(mx,sum);
				}
				else sum = 0;
			}
		}
	return mx;
}

int main(){
	freopen("game.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&m,&n);
		loop(i,m) scanf("%s",G[i]);
		vi steps;
		loop(i,4) loop(j,2) steps.pb(i);
		int best = get(0),ans = 0;
		do{
			loop(i,m) strcpy(U[i],G[i]);
			for(int i = 0;i < sz(steps);i++) {
				(*f[steps[i]])();
				int tmp = get();
				if(tmp > best) {
					best = tmp;
					ans = i +1;
				}
				else if(tmp == best) {
					ans = min(ans,i + 1);
				}
			}
		}while(next_permutation(all(steps)));
		printf("%d\n",ans);
	}
	return 0;
}
