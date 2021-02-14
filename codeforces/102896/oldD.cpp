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


const int B = 10;
int n;
int ones[1 << 20], zeros[1 << 20];
int val[1 << 20];
int cnt[1 << 20][B];


void read(int i){
	static char buffer[10];
	scanf("%s", buffer);
	ones[i] = zeros[i] = 0;
	loop(j, 8){
		ones[i] |= (buffer[j] == 'W') << j;
		zeros[i] |= (buffer[j] == 'R') << j;
	}
}

bool result[1 << 20];
vi adj[1 << 20];

void set_val(int i, int new_val){
	assert(val[i] != new_val);
	int old_val = val[i];
	val[i] = new_val;
	for(int j : adj[i]){
		if(old_val != -1) 
			cnt[j][old_val]--;
		cnt[j][new_val]++;
		int k = find(cnt[j], cnt[j] + B, 0) - cnt[j];
		if(val[j] != k) {
			assert(cnt[j][k] == 0);
			set_val(j, k);
		}
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		read(i);
		for(int d = 1; d <= 8 && i - d >= 0; d++){
			int j = i - d;
			int common = popcnt(ones[i] & ones[j]) + popcnt(zeros[i] & zeros[j]);
			if(d <= common) adj[i].push_back(j);
		}
	}
	fill(val, val + n, -1);
	for(int m = 1; m <= n; m++){
		set_val(m - 1, 0);
		result[m - 1] = val[0];
	}
	loop(i, n) putchar(2-result[i] + '0');
	puts("");
	return 0;
}
