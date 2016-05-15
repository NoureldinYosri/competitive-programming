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

char line[1 << 20],tmp[1 << 20];
int n,m,l,r,k;

int main(){
	scanf("%s %d",line,&m); n = strlen(line);
	while(m--){
		scanf("%d %d %d",&l,&r,&k);
		--l,--r; 
		if(r < l) swap(l,r);
		if(r == l) continue;
		k %= r - l + 1;
		loop(i,r - l + 1) tmp[(i + k)%(r - l + 1)] = line[i + l];
		range(i,l,r) line[i] = tmp[i - l];
	}
	printf("%s\n",line);
	return 0;
}
