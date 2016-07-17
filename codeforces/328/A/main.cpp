#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

char G[8][10];
int A = INT_MAX,B = INT_MAX;

int main(){
	loop(i,8) scanf("%s",G[i]);
	loop(i,8) loop(j,8){
		if(G[i][j] != '.'){
			int d =  (G[i][j] == 'B') - (G[i][j] == 'W') ,k = i + d;
			while(k < 8 && k >= 0 && G[k][j] == '.') k += d;
			if(k == -1 || k == 8){
				if(G[i][j] == 'W') A = min(A,i);
				else B = min(B,7 - i);
			}
		}
	}
	puts((A > B) ? "B" : "A");
	return 0;
}
