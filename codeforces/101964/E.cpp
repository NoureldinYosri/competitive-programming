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

const int MAX = 200*1000 + 10;
int n,m,L;
pi fish[MAX],men[MAX];
int ans[MAX];

int BIT[MAX];

void update(int p){
	for(++p;p < MAX;p += LSOne(p))
		BIT[p]++;
}
int get(int p) {
	int res = 0;
	for(++p;p;p ^= LSOne(p)) res += BIT[p];
	return res;
}

void solveLeq(){
	sort(fish,fish + n);
	sort(men,men + m);
	vi aux;
	loop(i,n) aux.push_back(fish[i].second - fish[i].first);
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());

	int j = 0;
	loop(i,m){
		while(j < n && fish[j].first <= men[i].first) {
			int v = fish[j].second-fish[j].first;
			v = lower_bound(all(aux),v) - aux.begin();
			update(v);
			j++;
		}
		int v = L - men[i].first;
		v = upper_bound(all(aux),v) - aux.begin();
		if(v)
			ans[men[i].second] += get(v-1);
	}
}
void solveMore(){
	reverse(fish,fish + n);
	reverse(men,men + m);
	vi aux;
	loop(i,n) aux.push_back(fish[i].second + fish[i].first);
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	memset(BIT,0,sizeof BIT);

	int j = 0;
	loop(i,m){
		while(j < n && fish[j].first > men[i].first) {
			int v = fish[j].second+fish[j].first;
			v = lower_bound(all(aux),v) - aux.begin();
			update(v);
			j++;
		}
		int v = L + men[i].first;
		v = upper_bound(all(aux),v) - aux.begin();
		if(v)
			ans[men[i].second] += get(v-1);
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d",&n,&m,&L);
	loop(i,n) scanf("%d %d",&fish[i].first,&fish[i].second);
	loop(i,m) {
		scanf("%d",&men[i].first);
		men[i].second = i;
	}
	solveLeq();
	solveMore();
	loop(i,m) printf("%d\n",ans[i]);
	return 0;
}
#endif
