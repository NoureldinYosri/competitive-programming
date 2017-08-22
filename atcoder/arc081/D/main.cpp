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

const int MAX = 2010;
int H,W;
char grid[MAX][MAX];
int f[MAX][MAX];


void work(int r1,int r2,int iv1,int iv2){
	int cnt = 0;
	for(int i = 0;i < W;i++){
		int b1 = (grid[r1][i] == '#') ? 1 : 0;
		int b2 = (grid[r2][i] == '#') ? 1 : 0;
		b1 ^= iv1;
		b2 ^= iv2;
		if(b1 == b2) cnt++;
		else cnt = 0;
		f[r2][i] = max(f[r2][i],cnt);
	}
}


int aux[MAX],n;

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&H,&W);
	loop(i,H) scanf("%s",grid[i]);
	for(int i = 1;i < H;i++){
		loop(iv1,2) loop(iv2,2) work(i-1,i,iv1,iv2);
//		loop(j,W) cout << f[i][j] << " ";
//		cout << endl;
	}
	int ans = 0;
	loop(i,H) {
		int cnt = 0,lst = 0;
		for(int j = 0;j < W;j++) {
			int b = (grid[i][j] == '#') ? 1 : 0;
			if(b == lst) cnt++;
			else {
				lst = b;
				ans = max(ans,cnt);
				cnt = 1;
			}
		}
		ans = max(ans,cnt);
	}
	loop(j,W) {
		int cnt = 0,lst = 0;
		loop(i,H) {
			int b = (grid[i][j] == '#') ? 1 : 0;
			if(b == lst) cnt++;
			else {
				ans = max(ans,cnt);
				cnt = 1;
			}
			lst = b;
		}
		ans = max(ans,cnt);
	}
	for(int col = 0;col < W;col++){
		n = 0;
		for(int i = 1;i < H;i++)
			aux[n++] = f[i][col];
		for(int s = 0;s < n;s++){
			int mn = INT_MAX;
			for(int e = s;e < n;e++){
				mn = min(mn,aux[e]);
				int tmp = mn*(e - s + 2);
				ans = max(ans,tmp);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
