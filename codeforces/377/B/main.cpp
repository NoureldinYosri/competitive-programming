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

const int MAX = 100*1000 + 10;
int n,m,S;
pi A[MAX];
pair<pi,int> student[MAX];
int who[MAX];

bool can(int T) {
	int i = n-1,j = m-1,r = S;
	multiset<pair<pi,int> > MS;
	for(;i >= 0;) {
		while(j >= 0 && A[i].xx <= student[j].xx.xx) {
			pi tmp = student[j].xx;
			swap(tmp.xx,tmp.yy);
			MS.insert(mp(tmp,student[j].yy));
			j--;
		}
		if(MS.empty() || MS.begin()->xx.xx > r) return 0;
		auto st = *MS.begin();
		MS.erase(MS.begin());

		r -= st.xx.xx;
		for(int k = 0;k < T && i >= 0;k++,i--)
			who[A[i].yy] = st.yy;
	}
	return 1;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&m,&n,&S);
	loop(i,n) scanf("%d",&A[i].xx),A[i].yy = i;
	loop(i,m) scanf("%d",&student[i].xx.xx);
	loop(i,m) scanf("%d",&student[i].xx.yy),student[i].yy = i;

	sort(A,A + n);
	sort(student,student + m);

	if(!can(n)) puts("NO");
	else {
		puts("YES");
		int s = 1,e = n;
		while(s < e) {
			int mid = (s + e) >> 1;
			if(can(mid)) e = mid;
			else s = mid + 1;
		}
		can(s);
		loop(i,n) printf("%d%c",who[i] + 1," \n"[i==n-1]);
	}
	return 0;
}
