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

const int MAX = 3e6;
int is_prime[MAX];
void sieve(){
	fill(is_prime + 2,is_prime + MAX,1);
	for(ll i = 2;i < MAX;i++){
		if(is_prime[i]){
			for(ll j = i*i; j < MAX; j += i)
				is_prime[j] = 0;
		}
	}
}

int ones;
vi odd,even;

int main(){
	sieve();
	int n,a;
	scanf("%d",&n);
	loop(i,n){
		scanf("%d",&a);
		if(a == 1) ones++;
		else if(a & 1) odd.pb(a);
		else even.pb(a);
	}
	if(ones){	
		for(int a : even){
			if(is_prime[a + 1]){
				printf("%d\n",ones + 1);
				printf("%d",a);
				loop(i,ones) printf(" 1");
				puts("");			
				return 0;
			} 
		}
		if(ones > 1){
			printf("%d\n",ones);
			loop(i,ones) printf("1%s",(i == ones - 1) ? "\n":" ");
			puts("");			
			return 0;	
		}
	}
	for(int a : odd){
		for(int b : even){
			if(is_prime[a + b]){
				printf("2\n%d %d\n",a,b);
				return 0;
			}
		}
	}
	if(ones){
		puts("1\n1");
		return 0;
	}
	for(int a : odd){
		printf("1\n%d\n",a);
		return 0;
	}
	for(int a : even){
		printf("1\n%d\n",a);
		return 0;
	}
	puts("0");
	return 0;
}
