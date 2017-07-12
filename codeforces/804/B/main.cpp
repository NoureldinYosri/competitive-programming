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

const int MAX = 1 << 20,mod = 1e9 + 7;
char buffer[MAX];
int p2[MAX];

int add(int x,int y){
	x += y;
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	p2[0] = 1;
	loop(i,MAX - 1){
		p2[i + 1] = p2[i] << 1;
		if(p2[i + 1] >= mod) p2[i + 1] -= mod;
	}
	scanf("%s",buffer + 1);
	int n = strlen(buffer + 1);
	int ans = 0;
	for(int i = 1,l = 0;i <= n;i++){
		if(buffer[i] == 'a'){
			l++;
		}
		else{
			ans = add(ans,add(p2[l],-1));
		}
	}
	cout << ans << endl;
	return 0;
}
