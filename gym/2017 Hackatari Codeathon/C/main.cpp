#pragma GCC optimize("O3")
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

#define mymax(a,b) ((a > b) ? a : b)

const int MAX = 101;
char G[MAX][MAX];
int m,n;
short dp[2][MAX][67][67][3];
int T[MAX][MAX];

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	loop(i,m) loop(j,n) T[i][j] = (G[i][j] == '-') + 2*(G[i][j] == '|');
	int one = 0,other = 1;
	for(int i = m-1;i >= 0;i--){
		for(int j = n-1;j >= 0;j--)
			for(int cnt1 = 0;cnt1 < 67;cnt1++)
				for(int cnt2 = 0;cnt2 < 67;cnt2++){
					int A[] = {0,cnt1,cnt2};
					for(int q = 0;q < 3;q++){
						if(q == 1) A[0] = cnt1,A[1] = 0,A[2] = cnt2;
						if(q == 2) A[0] = cnt1,A[1] = cnt2,A[2] = 0;
						A[T[i][j]]++;
						int t = 0;
						if(T[i][j] == q && cnt1 && cnt2) t = 1,A[0]--,A[1]--,A[2]--;
						int a ,b,nq;
						if(!A[0]) a = A[1],b = A[2],nq = 0;
						else if(!A[1]) a = A[0],b = A[2],nq = 1;
						else a = A[0],b = A[1],nq = 2,assert(A[2] == 0);
						a = (a < 66) ? a : 66,b = (b < 66) ? b : 66;
						dp[one][j][cnt1][cnt2][q] = t + mymax(dp[one][j + 1][a][b][nq],
															dp[other][j][a][b][nq]);
						//if(dp[one][j][cnt1][cnt2][q]) cerr << one << " " << j << " " << cnt1 << " " << cnt2 << " " << q << endl;
					}
		}
		one ^= 1;
		other ^= 1;
	}
	cerr << dp[other][0][0][0][0] << endl;
	cout << dp[other][0][0][0][0] << endl;

	
	
	return 0;
}

