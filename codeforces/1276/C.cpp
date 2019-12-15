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

int n;
int B[1 << 20];
pi A[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",B + i);
	sort(B,B + n);
	int m = 0;
	for(int i = 0;i < n;){
		int j = i;
		while(j < n && B[i] == B[j]) j++;
		A[m++] = pi(j-i,B[i]);
		i = j;
	}
	n = m;
	sort(A,A + n);
	
	pi best(0,1);
	
	int sum = 0;
	for(int h = 1,i = 0;h <= n;h++){
		while(i < n && A[i].first <= h){
			sum += A[i].first;
			i++;
		}
		int m = sum + (n - i)*h;
		int siz = m - m%h;
		int w = siz/h;
		if(w >= h)
			best = max(best,pi(siz,h));
	}
	int h = best.second;
	m = 0;
	reverse(A,A + n);
	loop(i,n) {
		A[i].first = min(A[i].first,h);
		m += A[i].first;
//		cout << A[i] << endl;
	}
	
	int w = m/h;
	m = h*w;
	vector<vi> res(h,vi(w,0));
	deque<pi> diag;
	loop(i,h) loop(j,w) if(!res[i][j]) {
		int a = i,b = j;
		while(!res[a][b]){
//			cout << pi(a,b) << " ";
			diag.emplace_back(a,b);
			res[a][b] = -1;
			a = (a + 1)%h;
			b = (b + 1)%w;
		}
//		cout << endl;
	}
	
	int Xs[h] = {0},Ys[w] = {0};
	
	loop(i,n){
		int cnt = A[i].first, x = A[i].second;
		while(cnt > 0){
			if(diag.empty()) break;
			while(1){
				pi p = diag.back();
				if(Xs[p.first] == x || Ys[p.second] == x) {
					diag.pop_back();
					diag.push_front(p);
				}
				break;
			}
			pi p = diag.back();
			diag.pop_back();
			res[p.first][p.second] = x;
		//	cout << p << ": " << x << endl;
			Xs[p.first] = x;
			Ys[p.second] = x;
			cnt--;
		}
	}
	printf("%d\n",m);
	printf("%d %d\n",h,w);
	for(auto V : res){
		for(int x : V) printf("%d ",x);
		puts("");
	}
	

	return 0;
}
