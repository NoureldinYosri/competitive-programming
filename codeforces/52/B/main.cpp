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

ll col[1024][1024],row[1024][1024];
int m,n;
char buffer[1024];
char G[1024][1024];

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m){
		scanf("%s",buffer);
		loop(j,n) {
			row[i][j] = j ? row[i][j - 1] : 0;
			col[i][j] = i ? col[i - 1][j] : 0;
			row[i][j] += buffer[j] == '*';
			col[i][j] += buffer[j] == '*';
		}
		strcpy(G[i],buffer);
	}	
	ll ans = 0;
	loop(i,m) loop(j,n) if(G[i][j] == '*') ans += (row[i][n-1]-1)*(col[m-1][j] - 1);
	cout << ans << endl;
	
	return 0;
}
