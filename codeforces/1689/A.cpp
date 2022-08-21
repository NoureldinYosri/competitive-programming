#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;

int who[26], cnt[26];
int n, m, k;

void read(int id) {
	static char S[1 << 20];
	scanf("%s", S);
	int len = strlen(S);
	loop(i, len) {
		who[S[i] - 'a'] = id;
		cnt[S[i] - 'a']++;
	}
}
void tc() {
	fill(who, who + 26, -1);
	fill(cnt, cnt + 26, 0);
	scanf("%d %d %d", &n, &m, &k);
	read(0);
	read(1);

	int ctr[2] = {k, k};
	int rem[2] = {n, m};
	bool done;
	do {
		done = true;
		loop(i, 26) if(cnt[i] && ctr[who[i]]) {
			putchar('a' + i);
			cnt[i]--;
			ctr[who[i]]--;
			ctr[1 - who[i]] = k;
			rem[who[i]]--;
			done = false;
			break;
		}
		done |= min(rem[0], rem[1]) == 0;
	} while(!done);
	puts("");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
