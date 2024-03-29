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


int len[1 << 20];
int n;


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	string s;
	cin >> n >> s;
	int l = 1,r = n;
	for(char c : s) {
		if(c == 'L') l++;
		else r--;
	}
	for(int i = 0;i < sz(s);) {
		int j = i;
		while(j < sz(s) && s[i] == s[j]) j++;
		int L = j-i;
		for(;i < j;i++)
			len[i] = L--;
	}

	set<int> S;
	for(int i = 1;i <= n;i++) S.insert(i);

	int p = 0;
	vi aux;
	for(int i = 0;i < sz(s);) {
		if(s[i] == 'R') {
			p = *S.begin();
			S.erase(S.begin());
			printf("%d\n",p);
			i++;
//			print(S,int);
			continue;
		}
		auto ptr = S.begin();
		loop(j,len[i]+1) {
			aux.push_back(*ptr);
			ptr++;
		}
		reverse(all(aux));
		S.insert(aux.back());
		aux.pop_back();
		for(int x : aux) {
			p = x;
			S.erase(p);
			printf("%d\n",p);
//			print(S,int);
		}
		aux.clear();
		i += len[i];
	}
	printf("%d\n",*S.begin());
	return 0;
}
#endif
