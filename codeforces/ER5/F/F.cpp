#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1 << 20;
char text[MAX];
int names[MAX],P[MAX],SA[MAX],RANK[MAX],LCP[MAX],MAP[MAX];
int n,L,h;
multiset<int> S;

bool cmp0(const int & a,const int & b){
	return RANK[a] < RANK[b];
}

bool cmp1(const int & a,const int & b){
	if(RANK[a] != RANK[b]) return RANK[a] < RANK[b];
	int _a = min(a + (1 << h),L),_b = min(b + (1 << h),L);
	return RANK[_a] < RANK[_b];
}

int main(){
	scanf("%d",&n);
	loop(i,n){
		scanf("%s",text + L);
		names[i] = L + strlen(text + L);
		L = names[i];		
		text[L++] = '$';
	}
	text[L] = '\0';
	loop(i,n) scanf("%d",P + i);
	loop(i,L + 1) SA[i] = i,RANK[i] = text[i];
	sort(SA,SA + L,&cmp0);
	for(h = 0; (1 << h) < L;h++){
		sort(SA,SA + L,&cmp1);
		loop(i,L){
			int j = i;
			while(j < L && !(cmp1(SA[i],SA[j]) || cmp1(SA[j],SA[i]))) RANK[SA[j++]] = i;
			i = j -1;
		}
	}	
	loop(i, L) MAP[SA[i]] = i;
	for(int i = 0,k = 0; i < L;i++){
		if(MAP[i] == L - 1) {
			k = 0;		
			continue;
		}
		int j = SA[MAP[i] + 1];		
		while(j + k < L && j + k < L && text[i + k] == text[j + k]) k++;
		LCP[MAP[i]] = k;
		if(k) k--;
	}
	//loop(i,L) cerr << LCP[i] << " " << (char*) (text + SA[i]) << endl; 
	ll ans = LLONG_MIN,accum = 0;
	dequeue<int> LEN; int i = 0;
	loop(j,L){
		if(text[SA[j]] == '$'){
			LEN.clear();		
			accum = 0;
			continue;
		}
		if(LEN.empty() || LCP[LEN.front()] == 0){
			int k = upper_bound(names,names + n,SA[j]) - names;
			accum = P[k];
			LEN.clear();
			LEN.pb(j);
			continue;
		}
		int k = upper_bound(names,names + n,SA[j]) - names;
		accum += P[k];
		ans = max(accum * 1LL * LCP[LEN.front()],ans);
		int i1 = upper_bound(names,names + n,SA[i]) - names;
		while(LEN.front() == i1){
			LEN.pop_front();
			k = upper_bound(names,names + n,SA[j]) - names;
			ll tmp = accum - P[k],l = LEN.empty() ? LCP[i1] : LCP[LEN.front()];
			if(tmp * l >= accum * LCP[i1]) continue;
			else 
		}
		if(accum <= 0) {
			accum = 0;
			i = j + 1;
			LEN.clear();
			continue;
		}
		while(!LEN.empty() && LCP[LEN.back()] >= LEP[j]) LEN.pop_back();
		LEN.pb(j);
	}
	//cerr << ans << endl;
	//loop(i,L) cerr << (char*)(text + SA[i]) << endl;
	loop(i,n) {
		int l = P[i] - (i ? P[i - 1] : 0);	
		ans = max(ans,P[i] * 1LL * l);
	}
	cout << ans << endl;
	return 0;
}
