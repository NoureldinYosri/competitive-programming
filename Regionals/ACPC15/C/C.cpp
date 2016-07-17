#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cout << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

pl inp [1 << 20];
ll ans [1 << 20];
pl line[1 << 20];
int ord[1 << 20];

bool cmp(const int & a,const int & b){
	if(inp[a].yy == 0 && inp[b].yy == 0) return a < b;
	else if(inp[a].yy == 0) return 1;
	else if(inp[b].yy == 0) return 0;
	
	if(inp[a].yy < 0 && inp[b].yy < 0) return inp[a].xx*inp[b].yy < inp[a].yy*inp[b].xx;
	if(inp[a].yy > 0 && inp[b].yy > 0) return inp[a].xx*inp[b].yy < inp[a].yy*inp[b].xx;
	return inp[a].xx*inp[b].yy > inp[a].yy*inp[b].xx;
}

double g(pl A,pl B){
	return (B.yy - A.yy + 0.0)/(A.xx - B.xx);
}

#define f(p) (x * p.xx + y * p.yy)

ostream& operator << (ostream & stream,const pl & p){
	stream << "(" << p.xx << " ," << p.yy << ")";
	return stream;
}

int main(){
	int T,n,m;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		ll mx_a = INT_MIN,mx_b = mx_a,mn_a = INT_MAX,mn_b = mn_a;		
		loop(i,n) {
			scanf("%lld %lld",&line[i].xx,&line[i].yy);
			mx_a = max(mx_a,line[i].xx);
			mn_a = min(mn_a,line[i].xx);
			mx_b = max(mx_b,line[i].yy);
			mn_b = min(mn_b,line[i].yy);
		}
		sort(line,line + n);
		deque<pl> p1,p2;
		loop(i,n){
			int j = i;
			while(j < n && line[i].xx == line[j].xx) j++;
			i = j - 1;
			while(sz(p1) > 1 && g(p1[sz(p1)-2],line[i]) <= g(p1[sz(p1)-2],p1[sz(p1)-1])) p1.pop_back();
			p1.pb(line[i]);
		}
		reverse(line,line + n);
		loop(i,n){
			int j = i;
			while(j < n && line[i].xx == line[j].xx) j++;
			i = j - 1;			
			while(sz(p2) > 1 && g(line[i],p2[sz(p2)-2]) <= g(p2[sz(p2)-1],p2[sz(p2)-2])) p2.pop_back();
			p2.pb(line[i]);
		}
		loop(i,m) {
			scanf("%lld %lld",&inp[i].xx,&inp[i].yy);
			ord[i] = i;
		}
		sort(ord,ord + m,&cmp);
		loop(i,m){
			int idx = ord[i];
			ll x = inp[idx].xx,y = inp[idx].yy;
			if(x == 0 && y == 0) ans[idx] = 0;
			else if(x == 0) {
				if(y > 0) ans[idx] = y * mx_b;
				else ans[idx] = y * mn_b;
			}
			else if(y == 0){
				if(x > 0) ans[idx] = x * mx_a;
				else ans[idx] = x * mn_a;
			}
			else{
				if(y > 0){
			//		cerr << "max " << x << " " << y << " " ;
					while(sz(p1) > 1 && f(p1[0]) <= f(p1[1])) p1.pop_front();
					ans[idx] = f(p1[0]);
			//		cerr << p1[0] << endl;				
				}
				else{
			//		cerr << "min " << x << " " << y << " " ;
					while(sz(p2) > 1 && f(p2[0]) <= f(p2[1])) p2.pop_front();
					ans[idx] = f(p2.front());
			//		cerr << p2.front() << endl;
				}
			}
			//cerr << x << " " << y << " " << ans[idx] << endl;
		}
		loop(i,m) printf("%lld\n",ans[i]);
	}
	return 0;
}