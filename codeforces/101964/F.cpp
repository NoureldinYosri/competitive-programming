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

const int MAX = 100*1000 + 10;
int A[MAX],B[MAX],n,m;
int C[MAX];

vi getSub(){
	vi subseq;
	int i = 0;
	loop(j,m) {
		int x = C[j];
		while(i < n && x != A[i]) i++;
		if(i == n) {
			puts("-1");
			exit(0);
		}
		subseq.push_back(i);
		i++;
	}
	return subseq;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) scanf("%d",B + i);
	copy(B,B + n,C);
	m = unique(C,C + n) - C;
	vi subseq = getSub();
	vector<pair<char,pi>> op;
	vector<pi> I;
	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && B[i] == B[j]) j++;
		I.emplace_back(i,j-1);
		i = j;
	}

	assert(sz(I) == sz(subseq));


	for(int q = 0;q < sz(I);q++) {
		int i = subseq[q];
		int f = I[q].first;
		int k = i,x = A[i];
		while(k > f) {
			k--;
			if(A[k] == x) continue;
			if(A[k] < x) op.emplace_back('M',pi(k+1,i+1));
			else op.emplace_back('m',pi(k+1,i+1));
			A[k] = x;
		}
	}
//	prArr(A,n,int);
	for(int q = sz(I)-1;q >= 0;q--){
		int i = subseq[q];
		int e = I[q].second;
		int k = i,x = A[i];
		while(k < e) {
			++k;
			if(A[k] == x) continue;
			if(A[k] < x) op.emplace_back('M',pi(i+1,k+1));
			else op.emplace_back('m',pi(i+1,k+1));
			A[k] = x;
		}
	}

	assert(equal(A,A + n,B));

	vector<pair<char,pi>> aux;

	for(auto p : op) {
		if(aux.empty()) {
			aux.push_back(p);
			continue;
		}
		if(p.first != aux.back().first) {
			aux.push_back(p);
			continue;
		}
		if(p.second.first == aux.back().second.first){
			aux.back().second.second = max(aux.back().second.second,p.second.second);
			continue;
		}
		if(p.second.second == aux.back().second.second){
			aux.back().second.first = min(aux.back().second.first,p.second.first);
			continue;
		}
		aux.push_back(p);
	}

//	cout << op.size() << " " << aux.size() << endl;
	op.swap(aux);
	printf("%d\n",sz(op));
	for(auto p : op) printf("%c %d %d\n",p.first,p.second.first,p.second.second);
	return 0;
}
#endif
