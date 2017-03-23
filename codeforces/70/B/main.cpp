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

const int MAX = 10*1000 + 110;
int n;
char buffer[MAX];
vi words;

bool is_end(char c){
	return c == '.' || c == '?' || c == '!';
}

int main(){
	scanf("%d\n",&n);
	fgets(buffer,MAX,stdin);
	for(char *p = buffer;*p && *p != '\n';p++) if(*p != ' '){
		int ctr = 0;
		for(;*p && *p != '\n' && !is_end(*p);p++) ctr++;
		ctr += is_end(*p);		
		words.pb(ctr);
		if(ctr > n){
			puts("Impossible");
			return 0;
		}
		if(!*p) break;
	}
	//print(words,int);
	reverse(all(words));
	int ctr = 0,siz = 0;
	while(!words.empty()){
		if(words.back() + 1 <= siz) siz -= words.back() + 1;
		else siz = n - words.back(),ctr++;
		words.pop_back();
	}
	cout << ctr << endl;
	cerr << ctr << endl;
	return 0;
}
