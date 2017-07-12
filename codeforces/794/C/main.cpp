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

int cnt[2][128];
char out[1 << 20];
deque<char> I[2];
int n;



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	string A,B; cin >> A >> B;
	I[0] = deque<char>(all(A));
	I[1] = deque<char>(all(B));
	sort(all(I[0]));
	sort(all(I[1]));
	n = sz(I[0]);
	while(sz(I[0]) > (n + 1)/2) I[0].pop_back();
	while(sz(I[1]) > n/2) I[1].pop_front();

//	print(I[0],char);
//	print(I[1],char);

	deque<char> U,V;
	int i,turn;
	for(i = 0,turn = 0;i < n;i++,turn ^= 1){
		if(I[0].front() >= I[1].back()) {
			if(turn == 0) {
				V.push_front(I[0].back());
				I[0].pop_back();
			}
			else{
				V.push_front(I[1].front());
				I[1].pop_front();
			}
		}
		else{
			if(turn == 0){
				U.pb(I[0].front());
				I[0].pop_front();
			}
			else{
				U.pb(I[1].back());
				I[1].pop_back();
			}
		}
	}

	for(char c : U) putchar(c);
	for(char c : V) putchar(c);
	puts("");
	return 0;
}
