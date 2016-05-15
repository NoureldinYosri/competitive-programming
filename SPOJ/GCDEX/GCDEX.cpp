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

const int MAX = 10001;
int SQRT[MAX];
ll G[MAX];

int main(){
	loop(i,101) SQRT[i*i] = i;
	int l = 0;	
	loop(i,MAX){
		if(SQRT[i]) l = SQRT[i];
		else SQRT[i] = l;
	}
	range(i,1,MAX - 1){
		G[i] = G[i - 1];
		ll tmp = i*i;	
		range(j,1,SQRT[i]){
			tmp -= j*(i/j - SQRT[i] + 0LL) + i/j * (i/j + 1LL)/2;
		}
		if(i <= 20) cerr << i << " " << tmp << endl;
		G[i] += tmp ;
	}
	cout << G[10] << " " << G[100] << endl;
	return 0;
}
