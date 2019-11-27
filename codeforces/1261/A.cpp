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

int n,K;
char S[2 << 10];
vector<pi> ans;
vi ST;


void make_correct(){
	int s = 0;
	loop(i,n){
		if(S[i] == '('){
			s += 1;
			continue;
		}
		if(s){
			s--;
			continue;
		}
		int j = i;
		while(j < n && S[j] == ')') j++;
		assert(j < n);
		ans.emplace_back(i,j);
		reverse(S + i,S + j + 1);
		i--;
	}
}

int count_prefix(){
	static vi aux;
	aux.clear();
	ST.clear();
	k = 0;
	loop(i,n){
		if(S[i] == '('){
			aux.push_back(i);
			continue;
		}
		assert(!aux.empty());
		int l = aux.back(); aux.pop_back();
		if(aux.empty()){
			ST.emplace_back(l,i);
			k++;
		}
	}
	assert(aux.empty() == 0);
	return k;
}

void increase_prefix(int k){
	int i = 0;
	while(k){
		if(S[i] == ')') {
			i++;
			continue;
		}
		int s = 1;
		int j = i;
		while(j+1 < n && s){
			j++;
			s += (S[j] == '(') - (S[j] == ')');
		}
		assert(j < n);
		if(j == i+1) {
			i += 2;
			continue;
		}
		k--;
		reverse(S + i,S + j + 1);
		
		
	}
}

void reduce_prefix(int k){
	assert(k < sz(ST));
	int l = ST[0].second;
	int r = ST[k].first;
	ans.emplace_back(l,r);
	reverse(S + l,S + r + 1);
}

void solve(){
	ans.clear();
	make_correct();
	int k = count_prefix();
	if(k > K) reduce_prefix(k - K);
	else if(k < K) increase_prefix(K - k);
	assert(count_prefix() == K);
	printf("%d\n",sz(ans));
	for(auto p : ans) printf("%d %d\n",p.first+1,p.second+1);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&K);
		scanf("%s",S);
		solve();
	}
	return 0;
}
