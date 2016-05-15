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

int P[1 << 20],n;
ll prefA[1 << 20],suffA[1 << 20];
ll prefB[1 << 20],suffB[1 << 20];
char line[1 << 20];

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",P + i);		
	scanf("%s",line);
	loop(i,n){
		if(line[i] == 'A') prefA[i] = P[i];
		if(line[i] == 'B') prefB[i] = P[i];
		if(i) {
			prefA[i] += prefA[i - 1];
			prefB[i] += prefB[i - 1];
		}
	}
	for(int i = n - 1;i >= 0;i--){
		if(line[i] == 'A') suffA[i] = P[i];
		else suffB[i] = P[i];
		if(i < n - 1) {
			suffA[i] += suffA[i + 1];
			suffB[i] += suffB[i + 1];
		}
	}
	ll ans = suffA[0];
	loop(i,n) ans = max(ans,max(prefA[i] + suffB[i + 1],prefB[i] + suffA[i + 1]));
	cout << ans << endl;
	return 0;
}
