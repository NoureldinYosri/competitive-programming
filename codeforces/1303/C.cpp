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

set<char> adj[26];
char S[1 << 20];
string ans;
int L[26], R[26];
bool in_res[26];
int I[26];

bool solve(){
	ans.clear();
	int n = strlen(S);
	memset(L, -1, sizeof L);
	memset(R, -1, sizeof R);
	memset(in_res, 0, sizeof in_res);
	
	loop(i, n-1){
		int a = S[i] - 'a';
		int b = S[i+1] - 'a';
		if(a == b) continue;
		if(R[a] == b || L[a] == b) continue;
		if(R[a] == -1 && L[b] == -1) {
			R[a] = b;
			L[b] = a;
		}
		else if(L[a] == -1 && R[b] == -1){
			L[a] = b;
			R[b] = a;
		}
		else return 0;
	}
	
	loop(i, 26) if(!in_res[i] && L[i] == -1) {
		int j = i;
		while(j != -1 && !in_res[j]){
			ans.pb((char)(j + 'a'));
			in_res[j] = 1;
			j = R[j];
		}
	}
	if(sz(ans) != 26) return 0;
	loop(i, 26) I[ans[i] - 'a'] = i;
	
	loop(i, n-1){
		int a = S[i] - 'a';
		int b = S[i+1] - 'a';
		if(abs(I[a] - I[b]) > 1) return 0;
	}
	
		
	return 1;	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		loop(c, 26) adj[c].clear();
		scanf("%s", S);
		if(solve()) printf("YES\n%s\n", ans.c_str());
		else puts("NO");
	}
	return 0;
}
