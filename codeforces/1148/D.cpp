#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

int A[1 << 20],B[1 << 20],n;

vi solve1(vi I) {
	vi ret;
	sort(all(I),[](const int & a,const int & b) {
		return B[a] > B[b];
	});
	int prv = INT_MAX;
	for(int i : I) {
		if(A[i] < prv) {
			ret.push_back(i);
			prv = B[i];
		}
	}
	return ret;
}
vi solve2(vi I) {
	vi ret;
	sort(all(I),[](const int & a,const int & b) {
		return B[a] < B[b];
	});
	int prv = 0;
	for(int i : I) {
		if(A[i] > prv) {
			ret.push_back(i);
			prv = B[i];
		}
	}
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	vi t1,t2;
	loop(i,n) {
		scanf("%d %d",A + i,B + i);
		if(A[i] < B[i]) t1.push_back(i);
		else t2.push_back(i);
	}
	t1 = solve1(t1);
	t2 = solve2(t2);
	vi ans = t1;
	if(sz(t2) > sz(t1)) ans = t2;
	printf("%d\n",sz(ans));
	loop(i,sz(ans)) printf("%d%c",ans[i]+1," \n"[i==sz(ans)-1]);
	return 0;
}
#endif
