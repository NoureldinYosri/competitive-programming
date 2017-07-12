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
#define pl pair<ll,ll>
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

const int MAX = 1000*1000 + 10;
int n;
ll A[MAX],B[MAX];
bool vis[MAX];



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld",B + i);
	vis[0] = 1;
	loop(i,n){
		int x = i - 1,y = (i + 2)%n;
		if(x == -1) x += n;
		ll diff = B[(i + 1)%n] - B[i];
		if(vis[x] && vis[y] ){
			if(A[y] - A[x] != diff){
				puts("-1");
				return 0;
			}
			else continue;
		}
		if(vis[x]){
			vis[y] = 1;
			A[y] = diff + A[x];
		}
		if(vis[y]){
			vis[x] = 1;
			A[x] = A[y] - diff;
		}
	}
	ll sum = 0,r = 0;
	loop(i,n){
		r += B[i];
		sum += r / 3;
		r %= 3;
	}
	if(r){
		puts("-1");
		return 0;
	}
	loop(i,n) sum -= A[i];
	if(sum%n){
		puts("-1");
		return 0;
	}
	sum /= n;
	loop(i,n) A[i] += sum;
	loop(i,n) if((A[i] + A[(i + 1)%n] + A[(i + 2)%n]) != B[(i + 1)%n]){
		puts("-1");
		return 0;
	}
	loop(i,n) printf("%lld%c",A[i]," \n"[i==n-1]);
//	prArr(A,n,ll);
	return 0;
}
