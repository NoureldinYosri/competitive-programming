#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
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

int T,k,n;
char line[1 << 20];
int CTR[26];

int solve(){
	scanf("%s %d",line,&k);
	n = strlen(line);
	fill(CTR,CTR + 26,0);
	loop(i,n) CTR[line[i] - 'a']++;
	vi V;
	loop(i,26) if(CTR[i]) V.pb(CTR[i]);
	sort(all(V));
	int ans = INT_MAX,tmpA = 0,tmpB;
	loop(i,sz(V)){
		tmpB = tmpA;
		range(j,i + 1,sz(V) - 1) tmpB += max(V[j] - V[i] - k,0);
		ans = min(ans,tmpB);
		tmpA += V[i];
	}	
	return ans;
}

int main(){
	scanf("%d",&T);
	while(T--) printf("%d\n",solve());
	return 0;
}
