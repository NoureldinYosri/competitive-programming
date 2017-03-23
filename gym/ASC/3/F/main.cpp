#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 2010;
char alphabet[210],A[MAX],B[MAX];
int idx[210],d[210][210],n,m,L;
ll dp[MAX][MAX];
int choice[MAX][MAX][2];
int best[210],rbest[210],a,b;



int main(){
	freopen("dissim.in","r",stdin);
	freopen("dissim.out","w",stdout);
	scanf("%s",alphabet); 
	L = strlen(alphabet);
	memset(idx,-1,sizeof idx);
	memset(choice,-1,sizeof choice);	
	for(int i = 0;i < L;i++)
		idx[alphabet[i]] = i;
	scanf("%s %s",A,B); 
	n = strlen(A),m = strlen(B);
	loop(i,L) loop(j,L) {
		scanf("%d",&d[i][j]);
		if(d[i][best[i]] > d[i][j])
			best[i] = j;
	}
	loop(i,L){
		loop(j,L) if(d[j][i] < d[rbest[i]][i]) rbest[i] = j;
	}
	for(int i = n;i >= 0;i--)
		for(int j = m - (i == n);j >= 0;j--){
			ll & ret = dp[i][j]; ret = 1LL << 60;
			int x = idx[A[i]],y = idx[B[j]];
			ll tmp;
			if(i < n){
				tmp = dp[i+1][j] + d[x][best[x]];
				if(tmp < ret) ret = tmp,choice[i][j][0] = x,choice[i][j][1] = best[x];
			}
			if(j < m){
				tmp = dp[i][j+1] + d[rbest[y]][y];
				if(tmp < ret) ret = tmp,choice[i][j][0] = rbest[y],choice[i][j][1] = y;
			}
			if(i < n && j < m){
				tmp = dp[i+1][j+1] + d[x][y];
				if(tmp < ret) ret = tmp,choice[i][j][0] = x,choice[i][j][1] = y;			
			}
		}

	cout << dp[0][0] << endl;
	cerr << dp[0][0] << endl;
	int i = 0,j = 0;
	while(i < n || j < m){
		assert(choice[i][j][0] != -1);
		int c1 = choice[i][j][0],c2 = choice[i][j][1];
		putchar(alphabet[c1]);
		i += idx[A[i]] == c1;
		j += idx[B[j]] == c2;
	}
	puts("");
	i = j = 0;
	while(i < n || j < m){
		assert(choice[i][j][0] != -1);
		int c1 = choice[i][j][0],c2 = choice[i][j][1];
		putchar(alphabet[c2]);
		i += idx[A[i]] == c1;
		j += idx[B[j]] == c2;
	}
	puts("");

	return 0;
}
