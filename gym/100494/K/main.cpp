#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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

const int MAX = 30'010;
char S[MAX];
int R[MAX],L[MAX];
int n;
deque<int> dq;
deque<int> q;

int main(){
	scanf("%d",&n);
	loop(i,n){
		char c; scanf(" %c",&c);
		S[i] = c;
		dq.pb(i);
	}
	//cerr << S << endl;
	vi ST;
	loop(i,n){
		while(!ST.empty() && S[ST.back()] == S[i]) ST.pop_back();
		L[i] = ST.empty() ? -1 : ST.back();
		ST.pb(i);
	}
	ST.clear();
	for(int i = n-1;i >= 0;i--){
		while(!ST.empty() && S[ST.back()] == S[i]) ST.pop_back();
		R[i] = ST.empty() ? n : ST.back();
		ST.pb(i);
	}
//	print(dq,int);	
	while(dq.size() > 1){
		if(S[dq.front()] < S[dq.back()]) q.pb(dq.front()),dq.pop_front();
		else if(S[dq.back()] < S[dq.front()]) q.pb(dq.back()),dq.pop_back();
		else{
			if(L[dq.back()] < dq.front()){
				q.pb(dq.front());
				dq.pop_front();
			}
			else{
				int l = L[dq.back()],r = R[dq.front()];
				assert(r < n);
				if(S[l] < S[r])  q.pb(dq.back()),dq.pop_back();
				else if(S[r] < S[l]) q.pb(dq.front()),dq.pop_front();
				else if(r - dq.front() < dq.back() - l) q.pb(dq.front()),dq.pop_front();
				else q.pb(dq.back()),dq.pop_back();
			}
		}
	}
	while(!dq.empty()) q.pb(dq.front()),dq.pop_front();

	do{
		for(int i = 0;i < 80 && !q.empty();q.pop_front(),i++)
			putchar(S[q.front()]);
		puts("");
	}while(!q.empty());	
	return 0;
}
