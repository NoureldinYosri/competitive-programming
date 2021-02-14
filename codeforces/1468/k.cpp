#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;

char buffer[1 << 20];
string A, B;



bool check(int bx, int by){
	int n = strlen(buffer);
	int x = 0, y = 0;
	loop(i, n){
		char c = buffer[i];
		int nx = x, ny = y;
		if(c == 'L') nx--;
		else if(c == 'R') nx++;
		else if(c == 'U') ny++;
		else ny--;
		if(mp(nx, ny) != mp(bx, by)) tie(x, y) = pi(nx, ny); 
	}
	return x == 0 && y == 0;
}

void tc(){
	scanf("%s", buffer);
	int n = strlen(buffer);
	static vp path;
	path.clear();
	int x = 0, y = 0;
	loop(i, n){
		char c = buffer[i];
		if(c == 'L') x--;
		else if(c == 'R') x++;
		else if(c == 'U') y++;
		else y--;
		path.emplace_back(x, y);		
	}
	for(auto [bx, by] : path)
		if(check(bx, by)){
			printf("%d %d\n", bx, by);
			return;
		}
	puts("0 0");
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
