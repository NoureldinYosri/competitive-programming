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

const int MAXA = 1000*1000*1000, oo = 1 << 29;

struct quanta{
	pi fst_F, lst_F;
	pi fst_B, lst_B;	
	quanta(){
		fst_F = fst_B = pi(oo, -1);
		lst_F = lst_B = pi(-1, -1);
	}
};

struct node{
	node *l, *r;
	quanta q;
};

quanta merge(quanta L, quanta R){
	quanta ret;
	ret.fst_F = min(L.fst_F, R.fst_F);
	ret.fst_B = min(L.fst_B, R.fst_B);
	ret.lst_F = max(L.lst_F, R.lst_F);
	ret.lst_B = max(L.lst_B, R.lst_B);
	return ret;	
}

quanta merge(node *L, node *R){
	if(!L && !R) return quanta();
	if(!L) return R->q;
	if(!R) return L->q;
	return merge(L->q, R->q);
}



node* update(node *cur, int s, int e, int p, pi F, pi B){
	if(!cur) cur = new node();
	if(s == e){
		cur->q.fst_F = cur->q.lst_F = F;
		cur->q.fst_B = cur->q.lst_B = B;
		return cur;
	}
	int m = (s + e) >> 1;
	if(p <= m) cur->l = update(cur->l, s, m, p, F, B);
	else cur->r = update(cur->r, m+1, e, p, F, B);
	cur->q = merge(cur->l, cur->r);
	return cur;
}

quanta query(node *cur, int s, int e, int l, int r){
	if(!cur) return quanta();
	if(l <= s && e <= r) return cur->q;
	int m = (s + e) >> 1;
	if(r <= m) return query(cur->l, s, m, l, r);
	else if(m < l) return query(cur->r, m+1, e, l, r);
	return merge(query(cur->l, s, m, l, m), query(cur->r, m+1, e, m+1, r));
}


char buffer[50];
int v;

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int n; scanf("%d", &n);
	while(n--){
		int t; scanf("%d", &t);
		int f = 0, b = 0;
		if(t == 1){
			scanf("%s", 
		}
		else if(t == 2){
			
		}
		else {
			
		}
		printf("%d %d\n", f, b);
		fflush(stdout);
	}
	return 0;
}
