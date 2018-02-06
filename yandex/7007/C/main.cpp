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

int readS(){
	char s[50]; cin >> s;
	int len = strlen(s),pos = find(s,s + len,'.') - s;
	s[pos] = 0;
	int Sa,Sb;
	sscanf(s,"%d",&Sa);
	sscanf(s + pos + 1,"%d",&Sb);
	if(s[pos+1] != '0' && Sb < 10) Sb *= 10;
	int S = Sa * 100 + Sb;
//	cerr << s << " -> " << S << endl;
	return S;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int S = readS(),best = INT_MAX,found = 0;
	pi P,Q;
	for(int x1 = 0;x1 <= 100 && !found;x1++)
		for(int y1 = 0;y1 <= 100 && !found;y1++)
			for(int x2 = 0;x2 <= 100 && !found;x2++)
				for(int y2 = 0;y2 <= 100 && !found;y2++) {
					int A = abs(x1*y2 - x2*y1)*50;
//					int diff = abs(A - S);
					if(A == S) {
						found = 1;
						P = mp(x1,y1);
						Q = mp(x2,y2);
					}
				}
	if(found)
		cout << "0 0 " << P.xx << " " << P.yy << " " << Q.xx << " " << Q.yy << endl;
	else
		cout << -1 << endl;
	return 0;
}
