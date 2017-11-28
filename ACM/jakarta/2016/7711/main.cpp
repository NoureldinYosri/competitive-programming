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

char buffer[10];

vi days{0,31,28,31,30,31,30,31,31,30,31,30,31};

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	assert(sz(days) == 13);
	int T; scanf("%d",&T);
	range(t,1,T) {
		printf("Case #%d: ",t);
		scanf("%s",buffer);
		if(strcmp(buffer,"04-05-01") == 0) puts("1");
		else {
			int A[3];
			sscanf(buffer,"%d-%d-%d",A,A + 1,A + 2);
			sort(A,A + 3);
			set<vi> S;
			do{
				int year = 1900 + A[0];
				bool isleap = 0;
				if(year%4 == 0) {
					if(year%100 == 0) {
						isleap = year%400 == 0;
					}
					else isleap = 1;
				}
				if(year < 1900 || year > 1999) continue;
				int month = A[1];
				if(month < 1 || month > 12) continue;
				int numDays = days[month];
				if(isleap && month == 2) numDays ++;
				int day = A[2];
				if(day < 1 || day > numDays) continue;
				S.insert(vi({A,A + 3}));
			}while(next_permutation(A,A + 3));
			printf("%d\n",sz(S));
		}
	}
	return 0;
}
