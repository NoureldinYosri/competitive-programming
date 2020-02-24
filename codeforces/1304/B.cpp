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

int n, m; 
string S[100], R[100];
char buffer[1 << 20];
bool taken[100];
vector<pair<string, string>> V;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) {
		scanf("%s", buffer);
		S[i] = string(buffer);
		reverse(buffer, buffer + m);
		R[i] = string(buffer);
	}
	string center = "";
	loop(i, n) if(!taken[i]){
		bool done = 0;
		for(int j = i+1;j < n;j++)
			if(!taken[j] && S[i] == R[j]){
				taken[i] = taken[j] = 1;
				V.emplace_back(S[i], S[j]);
				done = 1;
				break;
			}
		if(!done && S[i] == R[i]) center = S[i];
	}
	int len = 2*m*sz(V) + sz(center);
	printf("%d\n", len);
	loop(i, sz(V)) printf("%s", V[i].first.c_str());
	printf("%s", center.c_str());
	reverse(all(V));
	loop(i, sz(V)) printf("%s", V[i].second.c_str());
	puts("");
	return 0;
}
