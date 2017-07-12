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

const int LIMIT = 5000;
int T[120][5],n;
int cnt[5];
int A[5];
int L [] = {2,4,8,16,32,64};
int R [] = {1,2,4,8,16,32};

bool valid(){
	int score[2] = {0};
	loop(i,2){
		loop(j,5){
			if(T[i][j] != -1) {
				int tmp = A[j]*(250 - T[i][j])/250;
				score[i] += tmp;
			}
		}
	}
	return score[0] > score[1];
}

bool can(int score,int have,int usable,bool solved){
	score /= 500; score --;
	int l = (n + usable) / L[score],r = (n + usable) / R[score];
	if(L[score] == 64) l = -1;
	if(r <= l) return 0;
	if(l < have && have <= r) return 1;
	else if(solved){
		if(have <= l) {
			int need = l+1 - have;
			if(need > usable) return 0;
			return 1;
		}
	}
	return 0;
}


bool bt(int cur,int num){
	if(cur == 5) return valid();
	for(A[cur] = 500;A[cur] <= 3000;A[cur] += 500){
		if(can(A[cur],cnt[cur],num,T[0][cur] != -1)) {
			if(bt(cur + 1,num)) return 1;
		}
	}
	return 0;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) loop(j,5) {
		scanf("%d",&T[i][j]);
		if(T[i][j] != -1) cnt[j]++;
	}
	for(int num = 0;num <= LIMIT;num++){
		if(bt(0,num )){
			cout << num  << endl;
			return 0;
		}
	}
	puts("-1");
	return 0;
}
