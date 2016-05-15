#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

int C[1 << 20][3];

int main(){
	freopen("bcount.in","r",stdin);
	freopen("bcount.out","w",stdout);
	int N,M,a,b;
	scanf("%d %d",&N,&M);  
	loop(i,N){
		scanf("%d",&a);
		--a;
		loop(j,3) C[i][j] = i ? C[i - 1][j] : 0;
		C[i][a]++;
	}
	loop(i,M){
		scanf("%d %d",&a,&b);
		--a,--b;
		loop(i,3) {
			if(i) putchar(' ');
			printf("%d",C[b][i] - (a ? C[a - 1][i] : 0));
		}
		puts("");
	}
	return 0;
}
