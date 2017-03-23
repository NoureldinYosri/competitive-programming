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

#define rep(i,a,b) for(int i = a;i < b;i++)

const int maxn = 200010, maxlg = 18; // maxlg = ceil(log_2(maxn))
pair<pair<int,int>, int> L[maxn]; // O(n * log n) space
int P[maxlg+1][maxn], stp, cnt, sa[maxn];
struct suffix_array {
	int n;
	suffix_array(){}
	suffix_array(const string& s) : n(s.size()) { // O(n * log n)
    rep(i,0,n) P[0][i] = s[i];
    sa[0] = 0; // in case n == 1
    for (stp = 1, cnt = 1; cnt < n; stp++, cnt <<= 1) {
      rep(i,0,n) L[i] = {{P[stp-1][i], i + cnt < n ? P[stp-1][i+cnt] : -1}, i};
      std::sort(L, L + n);
      rep(i,0,n)
        P[stp][L[i].second] = i>0 && L[i].first == L[i-1].first ?  P[stp][L[i-1].second] : i;
    }
    rep(i,0,n) sa[i] = L[i].second;
  }
  int lcp(int x, int y) { // time log(n); x, y = indices into string, not SA
    int k, ret = 0;
    if (x == y) return n - x;
    for (k = stp - 1; k >= 0 && x < n && y < n; k --)
      if (P[k][x] == P[k][y])
        x += 1<<k, y += 1<<k, ret += 1<<k;
    return ret;
  }

};

const int MAX = 1e5 + 1e2,MAXLG = 20;
string line;
int LCP[MAX],k,n;
ll g[MAX],sum[MAX];
int sparse_table[MAX][20],lg[MAX];
deque<int> ST;	

void preprocess(){
	suffix_array SA = suffix_array(line);
	n = sz(line);
	loop(i,n - 1) LCP[i] = SA.lcp(sa[i],sa[i + 1]);
	loop(i,n) sum[i + 1] = sum[i] + n - sa[i];
	lg[0] = -1;
	loop(i,MAX - 1) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	loop(i,n) sparse_table[i][0] = LCP[i];
	loop(k,19){
		loop(i,n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			sparse_table[i][k + 1] = min(sparse_table[i][k],sparse_table[j][k]);
		}
	}
}

int get_min(int a,int b){
	int l = lg[b - a + 1];
	return min(sparse_table[a][l],sparse_table[b - (1 << l) + 1][l]);	
}

ll get_left(int i,int len){
	if(!i) return 0;
	int s = 0,e = i - 1;
	while(s < e){
		int m = (s + e) >> 1;
		if(get_min(m,i - 1) >= len) e = m;
		else s = m + 1;
	}
	if(get_min(s,i-1) < len) s++;
	return sum[s] + (i - s + 0LL)*len;
}

ll get_right(int i,int len){
	int s = 0,e = sz(ST) - 1;
	while(s < e){
		int m = (s + e) >> 1;
		if(LCP[ST[m]] <= min(LCP[i],len)) e = m;
		else s = m + 1;
	}
	//cerr << i << " -> "  << ST[s] << endl;
	return (ST[s] - i - 1LL) * min(len,LCP[i]) + g[ST[s]] + min(len,get_min(i,ST[s] - 1)); 
}

ll f(int i,int len){
	return len + get_left(i,len) + get_right(i,len);
}

int main(){
	cin >> line >> k;
	preprocess();	
	//loop(i,n) cerr << (line.c_str() + sa[i]) << endl;
	ST.pb(n);
	int c = -1,len = -1;
	for(int i = n - 1;i >= 0;i--){
		/*prArr(g,n,ll);
		for(int x : ST) prp(mp(x,LCP[x]));
		cerr << endl;
		if(!i) {
			cerr << "get_right " << get_right(i,1) << endl;
		}*/
		if(f(i,n - sa[i]) >= k){
			int s = 1,e = n - sa[i];
			while(s < e){
				int m = (s + e) >> 1;
				if(f(i,m) >= k) e = m;
				else s = m + 1;
			}
			c = i; len = s;
		//	cerr << "choose this " << i << " " << s << endl;
		}
		g[i] = get_right(i,n - sa[i]);
		while(!ST.empty() && LCP[ST.front()] > LCP[i]) ST.pop_front();
		ST.push_front(i); 
	}
	string ans = "";
	if(len == -1) ans = "No such line.";
	else{
		loop(i,len) ans.pb(line[sa[c] + i]); 
	}
	//cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
