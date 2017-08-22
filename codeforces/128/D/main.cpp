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
#define popcnt(x) __builtin_popcount(x)
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
int A[MAX],freq[MAX],n;


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int N ; scanf("%d",&N);
	loop(i,N) scanf("%d",A + i);
	sort(A,A + N);
	for(int i = 0;i < N;){
		int j = i;
		while(j < N && A[i] == A[j]) j++;
		freq[n] = j - i;
		A[n] = A[i];
		n++;
		i = j;
	}
	loop(i,n - 1) if(A[i + 1] > A[i] + 1) {
		puts("NO");
		return 0;
	}
	loop(i,n) {
		freq[i]--;
		if(i!=0 && i!=n-1) freq[i]--;
		if(freq[i] < 0) {
			puts("NO");
			return 0;
		}
	}
	loop(i,n-1){
		if(freq[i + 1] < freq[i]) {
			puts("NO");
			return 0;
		}
		freq[i + 1] -= freq[i];
		freq[i] = 0;
	}

	if(freq[n-1]) {
		puts("NO");
		return 0;
	}
	puts("YES");
	return 0;
}
