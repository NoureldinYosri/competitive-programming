#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int who[100][100],what[100][100],m,n,q,a,b,c,v;


int main(){
	scanf("%d %d %d",&m,&n,&q);
	loop(i,m) loop(j,n) who[i][j] = i*n + j;
	while(q--){
		scanf("%d %d",&a,&b); b--;
		if(a <= 2){
			if(a == 1) {
				loop(j,n - 1) swap(who[b][j],who[b][j + 1]);
			}
			else{
				loop(j,m - 1) swap(who[j][b],who[j + 1][b]);
			}
		}
		else{
			scanf("%d %d",&c,&v); c--;
			int x = who[b][c]/n;
			int y = who[b][c]%n;
			what[x][y] = v;
		}
	}
	loop(i,m) loop(j,n) printf("%d%s",what[i][j],(j == n - 1) ? "\n" : " ");
	return 0;
}
