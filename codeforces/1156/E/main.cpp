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

const int MAX = 200*1000 + 10;
int P[MAX],pos[MAX],n;
int L[MAX],R[MAX];

void build(){
	vi ST;
	loop(i,n) {
		while(!ST.empty() && P[ST.back()] < P[i]) ST.pop_back();
		if(ST.empty()) L[i] = -1;
		else L[i] = ST.back();
		ST.push_back(i);
	}
	ST.clear();
	for(int i = n-1;i >= 0;i--) {
		while(!ST.empty() && P[ST.back()] < P[i]) ST.pop_back();
		if(ST.empty()) R[i] = n;
		else R[i] = ST.back();
		ST.push_back(i);
	}
}

int goLeft(int pivot) {
	int ret = 0;
	for(int i = L[pivot]+1;i < pivot;i++){
		int y = P[pivot] - P[i];
		if(pivot < pos[y] && pos[y] < R[pivot]) ret++;
	}
//	if(ret) cout << pivot << " left " << ret << endl;
	return ret;
}
int goRight(int pivot) {
	int ret = 0;
	for(int i = pivot+1;i < R[pivot];i++){
		int y = P[pivot] - P[i];
		if(pos[y] > L[pivot] && pos[y] < pivot) ret++;
	}
//	if(ret) cout << pivot << " right " << ret << endl;
	return ret;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",P + i);
		pos[P[i]] = i;
	}
	build();
	ll ans = 0;
	loop(i,n){
		if(i - L[i] < R[i] - i) ans += goLeft(i);
		else ans += goRight(i);
	}
	cout << ans << endl;
	return 0;
}
