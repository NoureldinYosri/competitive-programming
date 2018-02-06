#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

struct DS{
	int len;
	map<int,int> S;

	DS(){
		len = 0;
		S = map<int,int>();
	}

	inline void remove(int l) {
		if(S.find(l) == S.end()) return;
		int r = S[l];
		len -= r-l+1;
		S.erase(l);
	}
	inline void add(int l,int r) {
		if(l > r) return;
		remove(l);
		len += r-l+1;
		S[l] = r;
	}
	void remove_intersecting(int s,int e) {
		while(1) {
			auto p = S.lower_bound(s);
			if(p == S.end()) break;
			if(p->xx > e) break;
			if(p->yy <= e) remove(p->xx);
			else {
				int l = p->xx,r = p->yy;
				remove(l);
				add(e+1,r);
			}
		}
		while(1) {
			auto p = S.lower_bound(s);
			if(p == S.begin()) break;
			--p;
			if(p->yy >= s) {
				int l = p->xx,r = p->yy;
				remove(l);
				add(l,s-1);
				add(e+1,r);
			}
			else break;
		}
	}
	void insert(int s,int e) {
		remove_intersecting(s,e);
		auto p = S.lower_bound(s);
		if(p != S.begin()){
			auto q = p; --q;
			if(q->yy == s-1) {
				s = q->xx;
				remove(q->xx);
			}
		}
		if(p != S.end() && p->xx == e+1) {
			e = p->yy;
			remove(p->xx);
		}
		add(s,e);
	}
	friend ostream& operator << (ostream & st,const DS & ds) {
		st << "{" << ds.len << " {";
		for(auto p : ds.S) st << "(" << p.xx << ", " << p.yy << ")";
		st << "}}";
		return st;
	}
};


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n,q; scanf("%d %d",&n,&q);
	DS working;
	working.insert(1,n);

	while(q--) {
		int l,r,k; scanf("%d %d %d",&l,&r,&k);
		if(k == 1) working.remove_intersecting(l,r);
		else  working.insert(l,r);
//		cerr << working << endl;
//		cerr << endl;
		printf("%d\n",working.len);
	}

	return 0;
}
