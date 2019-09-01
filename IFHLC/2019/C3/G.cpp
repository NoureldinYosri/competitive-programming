#ifdef ACTIVE
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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

char S[1 << 20];
int n,m;
string target = "desmond";
char A[50] = "I love you, Desmond!";
char B[50]= "Goodbye, my love!";

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%s %d",S,&m);
	n = strlen(S);
	map<char,vi> c2i;
	loop(i,sz(target)) c2i[target[i]].push_back(i);
	loop(i,n-sz(target)+1) {
		bool f = 1;
		loop(j,sz(target)) {
			f &= target[j] == S[i + j];
		}
		if(f) {
			puts(A);
			puts("0");
			return 0;
		}
	}
	loop(t,m){
		int p; char c;
		scanf("%d %c",&p,&c);
		p--;
		S[p] = c;
		for(int k : c2i[c]) {
			int s = p - k;
			if(s < 0 || s + sz(target) > n) continue;
			bool f = 1;
			loop(j,sz(target))
				f &= target[j] == S[s + j];
			if(f) {
				puts(A);
				printf("%d\n",t+1);
				return 0;
			}
		}
	}
	puts(B);
	return 0;
}
#endif
