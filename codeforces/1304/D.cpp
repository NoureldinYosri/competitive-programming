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

char S[1 << 20];
int n;



vi aux;
void build_small(){
	set<int> M;
	for(int i = 1;i <= n;i++) M.insert(i);
	for(int i = 0;i < n-1;){
		if(S[i] == '>'){
			printf("%d ", *M.rbegin());
			M.erase(*M.rbegin());
			i++;
			continue;
		}
		int j = i;
		auto ptr = M.rbegin();
		while(j+1 < n && S[j] == '<') {
			ptr++;
			j++;
		}
		aux.clear();
		for(;i < j; i++){
			printf("%d ", *ptr);
			aux.pb(*ptr);
			ptr--;
		}
		for(int x : aux) M.erase(x);
	}
	printf("%d\n", *M.begin());	
}
void build_big(){
	set<int> M;
	for(int i = 1;i <= n;i++) M.insert(i);
	for(int i = 0;i < n-1;){
		if(S[i] == '<'){
			printf("%d ", *M.begin());
			M.erase(M.begin());
			i++;
			continue;
		}
		int j = i;
		auto ptr = M.begin();
		while(j+1 < n && S[j] == '>') {
			ptr++;
			j++;
		}
		aux.clear();
		for(;i < j; i++){
			printf("%d ", *ptr);
			aux.pb(*ptr);
			ptr--;
		}
		for(int x : aux) M.erase(x);
	}
	printf("%d\n", *M.begin());
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %s", &n, S);
		build_small();
		build_big();
	}
	return 0;
}
