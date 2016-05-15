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

int A[1 << 20];
char line[1 << 20];

int main(){
	int x,y,s,e;
	scanf("%d %d %d %d %s",&x,&y,&s,&e,line);
	int L = strlen(line); A[0] = 1; 
	int ctr = 1;
	set<pi> S; S.insert(mp(s,e));
	loop(i,L - 1){
		printf("%d ",A[i]);
		int nx = s,ny = e;
		if(line[i] == 'U') nx--;
		else if(line[i] == 'D') nx++;
		else if(line[i] == 'L') ny--;
		else ny++;
		if(ny < 1 || ny > y || nx < 1 || nx > x) continue;
		if(S.count(mp(nx,ny))) {
			s = nx;
			e = ny;
			continue;
		}
		S.insert(mp(nx,ny));
		s = nx;
		e = ny;
		A[i + 1] = 1;
		++ctr;
	//	cerr << s << " " << e << endl;
	}
	printf("%d %d\n",A[L - 1],x*y - ctr);
	return 0;
}
