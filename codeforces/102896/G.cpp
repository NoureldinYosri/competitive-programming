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

const int mod = 1e9 + 7, MAX = 1 << 20;
int add(int a, int b){
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a, int b){
	return (a*(ll)b)%mod;
}
int invInt[MAX], invFact[MAX], fact[MAX];
int C(int n, int k){
	if(k > n) return 0;
	assert(n >= 0);
	assert(k >= 0);
	return mul(fact[n], mul(invFact[k], invFact[n - k]));
}
void init(){
	invInt[1] = 1;
	for(int i = 2; i < MAX; i++)
		invInt[i] = mod - mul(mod/i, invInt[mod%i]);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < MAX; i++){
		fact[i] = mul(fact[i - 1], i);
		invFact[i] = mul(invFact[i - 1], invInt[i]);
	}
}


pi P[3];

ll cross(pi a, pi b, pi c){
	b.first -= a.first, b.second -= a.second;
	c.first -= a.first, c.second -= a.second;
	return b.first*(ll)c.second - b.second*(ll)c.first;
}
int sgn(ll x){
	return (x > 0) - (x < 0);
}
bool inTriangle(pi p){
	int S[3] = {sgn(cross(p, P[0], P[1])), 
				sgn(cross(p, P[1], P[2])),
				sgn(cross(p, P[2], P[0]))};
	sort(S, S + 3);
	if(S[0] == S[2]) return true;
	int target = S[2];
	if(target == 0) target = S[0];
	assert(target != 0);
	loop(i, 3) if(S[i] && target != S[i]) return false;
	return true;
}

pi getRange(int y){
	static deque<int> I;
	I.clear();
	loop(i, 3){
		int j = i + 1;
		if(j == 3) j = 0;
		int s = min(P[i].second, P[j].second);
		int e = max(P[i].second, P[j].second);
		if(!(s <= y && y <= e)) continue;
		if(s == e){
			I.push_back(P[i].first);
			I.push_back(P[j].first);
		} else {
			double x1 = P[i].first, x2 = P[j].first;
			double y1 = P[i].second, y2 = P[j].second;
			double lambda = (y - y1)/(y2 - y1);
			double x = x1 + lambda*(x2 - x1);
			I.push_back(x - 1);
			I.push_back(x);
			I.push_back(x + 1);
		}
	}
	sort(all(I));
	bool left = false, right = false;
	while(!I.empty() && I.front() < -y) I.pop_front(), left = true;
	while(!I.empty() && I.back() > y) I.pop_back(), right = true;
	if(left) I.push_front(-y);
	if(right) I.push_back(y);
	while(!I.empty() && !inTriangle(pi(I.front(), y))) I.pop_front();
	while(!I.empty() && !inTriangle(pi(I.back(), y))) I.pop_back();
	if(I.empty()) return pi(0, -1);
	int s = (I.front() + y + 1) >> 1;
	int e = (I.back() + y) >> 1;
	return pi(s, e);
}

pi getRangeOld(int y){
	bool first = true;
	int s, e;
	for(int i = 0; i <= y; i++){
		int x = -y + 2*i;
		if(inTriangle(pi(x, y))){
			s = first ? i : s;
			e = i;
			first = false;
		}
	}
	
	if(first) return pi(0, -1);
	return pi(s, e);
}

void tc(){
	loop(i, 3) scanf("%d %d", &P[i].first, &P[i].second);
	int st = max(0, min({P[0].second, P[1].second, P[2].second})); 
	int en = max({P[0].second, P[1].second, P[2].second});
	int l = 0, r = -1, sum = 0, ans = 0;
	for(int n = st; n <= en; n++){
		auto [s, e] = getRange(n);
		sum = add(sum, sum);
		if(l <= r) {
			sum = add(sum, -C(n - 1, l));
			sum = add(sum, -C(n - 1, r));
			l++;
		}
		if(s <= e){
			if(l <= r){
				while(l < s) {
					sum = add(sum, -C(n, l));
					l++;
				}
				while(l > s){
					l--;
					sum = add(sum, C(n, l));
				}
				while(r < e) {
					r++;
					sum = add(sum, C(n, r));
				}
				while(r > e){
					sum = add(sum, -C(n, r));
					r--;
				}
			} else {
				sum = 0;
				for(int i = s; i <= e; i++) {
					sum = add(sum, C(n, i));
				}
			}			
		} else {
			sum = 0;
		}
//		cerr << n << ": " << s << " " << e << endl;
		ans = add(ans, sum);
		l = s;
		r = e;
	}
	printf("%d\n", ans);

}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int T; scanf("%d", &T);
	while(T--) tc();
	return 0;
}
