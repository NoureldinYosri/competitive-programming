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

deque<int> L,R;
deque<int> sL,sR;
void update(int x){
	L = sL,R = sR; int ctr = 0;
	while(!R.empty() && R.front() <= x) R.pop_front(),ctr++;
	if(ctr) R.push_front(x);
	ctr = 0;
	while(!L.empty() && L.back() >= x) L.pop_back(),ctr++;
	if(ctr) L.push_back(x);
}

void merge(deque<int> & A,deque<int> & B,deque<int> & C){
	C.clear();
	while(!A.empty() && !B.empty()){
		if(A.front() == B.front()) A.pop_front();
		else if(A.front() < B.front()) C.pb(A.front()),A.pop_front();
		else C.pb(B.front()),B.pop_front();
	}
	while(!A.empty()) C.pb(A.front()),A.pop_front();
	while(!B.empty()) C.pb(B.front()),B.pop_front();
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		int n,m; scanf("%d %d",&n,&m);
		int l,r; sL.clear(),sR.clear();
		loop(i,n){
			int a,b; scanf("%d %d",&a,&b);
			if(a > b) swap(a,b);
			if(!i){
				sL.pb(a); sR.pb(a);
				sL.pb(b); sR.pb(b);
			}
			else{			
				deque<int> tmpL,tmpR;
				update(a);
				tmpL = L,tmpR = R;
				update(b);
				merge(tmpL,L,sL);
				merge(tmpR,R,sR);
			}
		//	print(sL,int);
		//	print(sR,int);
		}
		l = sL.back(); r = sR.front();
		//cerr << l << " " << r << endl;
		while(m--){
			int a; scanf("%d",&a);
			puts((l <= a && a <= r) ? "YES" : "NOT SURE");
		}
	//	cout << l << " " << r << endl;
	}	
	
	return 0;
}
