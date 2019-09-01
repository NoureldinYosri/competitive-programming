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

using inter = pair<ll,ll>;
bool inRange(ll s,ll e,ll l,ll r) {
	return l <= s && e <= r;
}
struct Blk{
	deque<inter> dq;
	int h;
	void update(int ch) {
		assert(ch >= h);
		if(h == ch) return;
		int d = ch - h;
		ll p2 = 1LL << d;
		for(inter & p : dq) {
			p.first *= p2;
			p.second = (p.second + 1)*p2 - 1;
		}
		h = ch;
	}
	void push_front(inter I,int ch) {
		fix(I,ch);
		update(ch);
		dq.push_front(I);
	}
	pair<inter,int> poll_back(){
		inter b = dq.back(); dq.pop_back();
		return mp(b,h);
	}
	int getSize(){
		return dq.size();
	}
	void fix(inter & I,int & ch) {
		if(ch >= h) return;
		int d = h - ch;
		ch = h;
		ll p2 = 1LL << d;
		I.first *= p2;
		I.second *= p2;
		I.second += p2 - 1;
	}
	void destroyIntersection(inter I,int ch){
		if(dq.empty()) return;
		fix(I,ch);
		assert(ch >= h);
		ll p2 = 1LL << (ch - h);
		ll l = dq.front().first*p2;
		ll r = dq.back().second*p2 + p2 - 1;
		if(inRange(l,r,I.first,I.second)) {
			dq.clear();
			return;
		}
		update(ch);
		static vector<inter> aux;
		aux.clear();
		for(auto p : dq) aux.push_back(p);
		dq.clear();
		for(auto p : aux) {
			ll s = max(p.first,I.first);
			ll e = min(p.second,I.second);
			ll x = min(s-1,p.second);
			ll y = max(e+1,p.first);
			if(p.first <= x) dq.emplace_back(p.first,x);
			if(y <= p.second && x != p.second) {
				assert(x < y);
				dq.emplace_back(y,p.second);
			}
		}
	}
	void destroyNotIntersection(inter I,int ch){
		if(dq.empty()) return;
		fix(I,ch);
		assert(ch >= h);
		ll p2 = 1LL << (ch - h);
		ll l = dq.front().first*p2;
		ll r = dq.back().second*p2 + p2 - 1;
		if(inRange(l,r,I.first,I.second)) return;
		update(ch);
		static vector<inter> aux;
		aux.clear();
		for(auto p : dq) aux.push_back(p);
		dq.clear();
		for(auto p : aux) {
			ll s = max(p.first,I.first);
			ll e = min(p.second,I.second);
			if(s <= e) dq.emplace_back(s,e);
		}
	}
};


const int B = sqrt(1e5),m = 1e6/B;
vector<inter> info[2][60];
int H,Q;
Blk DS[m];





int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&H,&Q);
	loop(q,Q) {
		int h,res;
		ll L,R;
		scanf("%d %lld %lld %d",&h,&L,&R,&res);
		info[res][h].emplace_back(L,R);
	}
	DS[0].push_front(inter(1,1),1);
	int m = 1;
	vector<inter> aux;
	for(int h = 1;h <= H;h++) {
		for(auto q : info[1][h]){
			loop(b,m) DS[b].destroyNotIntersection(q,h);
		}
		int uh = h;
		aux.clear();
		for(auto q : info[0][h]) {
			loop(b,m) {
				while(!aux.empty()) {
					DS[b].push_front(aux.back(),uh);
					aux.pop_back();
				}
				DS[b].destroyIntersection(q,h);
				uh = DS[b].h;
				while(DS[b].getSize() > B)
					aux.push_back(DS[b].poll_back().first);
				reverse(all(aux));
			}
			reverse(all(aux));
			while(!aux.empty()) {
				for(int i = 0;!aux.empty() && i < B;i++){
					DS[m].push_front(aux.back(),uh);
					aux.pop_back();
				}
				m++;
			}
		}
	}
	ll cand = 0;
	inter ans;
	loop(i,m) {
//		cerr << DS[i].h  << " " << H << endl;
		DS[i].update(H);
		for(auto p : DS[i].dq){
			cand += p.second - p.first + 1;
			ans = p;
		}
	}
	if(cand == 0) {
		puts("Game cheated!");
	}
	else if(cand != 1){
		puts("Data not sufficient!");
	}
	else {
		printf("%lld\n",ans.first);
	}
	return 0;
}
