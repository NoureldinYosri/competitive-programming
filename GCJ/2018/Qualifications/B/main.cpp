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

const int MAX = 100*1000 + 10;
int A[MAX],n;
int B[MAX];
vi even,odd;

int solve() {
	copy(A,A + n,B);
	even.clear();
	odd.clear();
	for(int i = 0;i < n;i += 2) even.push_back(A[i]);
	for(int i = 1;i < n;i += 2) odd.push_back(A[i]);
	sort(all(even));
	sort(all(odd));
	for(int j = 0;j < sz(even);j++) {
		B[2*j] = even[j];
		if(j < sz(odd))
			B[2*j+1] = odd[j];
	}
	for(int i = 0;i + 1 < n;i++)
		if(B[i] > B[i+1])
			return i;
	return n;
}

int bf(){
	copy(A,A + n,B);
	bool done = 0;
	while(!done) {
		done = 1;
		for(int i = 0;i + 2 < n;i++)
			if(B[i] > B[i+2]){
				done = 0;
				swap(B[i],B[i + 2]);
			}
	}
	for(int i = 0;i + 1 < n;i++)
		if(B[i] > B[i+1])
			return i;
	return n;
}

void test(){
	int N = 100,MAXA = 3;
	for(int t = 0;t < 1000;t++) {
		n = rand()%N + 1;
		for(int i = 0;i < n;i++)
			A[i] = rand()%MAXA;
		int a = bf(),b = solve();
		if(a != b) {
			cerr << "failed on" << endl;
			cerr << "1\n" << n << endl;
			for(int i = 0;i < n;i++)
				cerr << A[i] << " ";
			cerr << endl;
			cerr << "expected " << a << " found " << b << endl;
			return;
		}
	}
	cerr << "success :)" << endl;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++) {
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		printf("Case #%d: ",t);
		int res = solve();
//		int res = bf();
		if(res == n) puts("OK");
		else printf("%d\n",res);
	}
//	test();
	return 0;
}
