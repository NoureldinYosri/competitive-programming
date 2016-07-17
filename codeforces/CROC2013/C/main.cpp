#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;


unsigned int A[1 << 20];

int main() {
	int N,K;
	scanf(" %d %d",&N,&K);
	vector<unsigned int> A(N);
	loop(i,N) {
		unsigned int a[4];
		scanf(" %d.%d.%d.%d",&a[0],&a[1],&a[2],&a[3]);
		A[i] = a[3] + 256*(a[2] + 256 * (a[1] + 256 * a[0]));
	}
	
	vector<unsigned int> msk(31,1);
	loop(i,31) msk[0] *=2;
	range(i,1,30) {
		loop(j,31 - i) msk[i] *=2; 
		msk[i] += msk[i-1];
	}
	set<unsigned int> s;		
	loop(i,31) {
		s.clear();
		loop(j,N) s.insert(msk[i]&A[j]);
		if((int)s.size() == K) {
			unsigned int a[4];
			a[3] = msk[i];
			loop(j,3) {
				a[2-j] = a[3-j]/256;
				a[3-j] %= 256;
			}
			printf("%d.%d.%d.%d\n",a[0],a[1],a[2],a[3]);
			return 0;
		}
	}
	puts("-1");
	return 0;
}

