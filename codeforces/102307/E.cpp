#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


const int MAX = 300*1000 + 10;
int n,d,alpha;
pair<int,int> P[MAX];


int ST[1 << 20],LA[1 << 20];

void update(int cur,int v) {
	ST[cur] += v;
	LA[cur] += v;
}
void push_down(int cur) {
	if(LA[cur] == 0) return ;
	int left = 2*cur + 1,right = left + 1;
	update(left,LA[cur]);
	update(right,LA[cur]);
	LA[cur] = 0;
}

void update(int cur,int s,int e,int l,int r,int v) {
	r = min(r,e);
	if(l <= s && e <= r) return update(cur,v);
	push_down(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m+1,e,l,r,v);
	else {
		update(left,s,m,l,m,v);
		update(right,m+1,e,m+1,r,v);
	}
	ST[cur] = max(ST[left],ST[right]);
}

int readAngel(){
	static char buffer[10],wb[5];
	scanf("%s",buffer);
	int a,b;
	sscanf(buffer,"%d.%s",&a,wb);
	sscanf(wb,"%d",&b);
	if(strlen(wb) == 1) b *= 10;
	int w =  a*100 + b;
//	cout << buffer << " -> " << w << endl;
	return w;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&d);
	alpha = readAngel();
	loop(i,n){
		scanf("%d",&P[i].first);
		P[i].second = readAngel();
	}
	for(int i = n-1; i >= 0;i--) {
		P[n++] = mp(max(0,P[i].first - d),-1);
		P[n++] = mp(P[i].first + d,-1);
	}
	sort(P,P + n);
	int ans = 0;
	int S = 0,E = 720*100;
//	cout << "alpha = " << alpha << endl;
	for(int i = 0,j = 0;i < n;) {
		j = max(i,j);
		int l = P[i].first,r = l + d;
		while(j < n && P[j].first <= r) {
			if(P[j].second != -1) {
				int w = P[j].second;
//				cout << "insert " << P[j] << " " << l << " " << r << endl;
				update(0,S,E,w,w + alpha,1);
				w += 360*100;
				update(0,S,E,w,w + alpha,1);
			}
			j++;
		}
		// query
		ans = max(ans,ST[0]);

//		cout << "should erase " << " " << P[i] << endl;
		while(i < n && P[i].first == l) {
			if(P[i].second != -1) {
				int w = P[i].second;
//				cout << "erase " << P[i] << endl;
				update(0,S,E,w,w + alpha,-1);
				w += 360*100;
				update(0,S,E,w,w + alpha,-1);
			}
			i++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
#endif
