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

const int MAX = 70*1000 + 10;
char nums[MAX][10];
int n,m;
int it[MAX*45];
ll val[MAX][9][10];
int cnt[MAX*45];

int get_val(int a){
	return val[a/100][a%10][(a%100)/10];
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);

	loop(i,n) {
		scanf("%s",nums[i]);
		for(int s = 0;s < 9;s++){
			ll x = 0;
			for(int e = s;e < 9;e++){
				x = x*10 + nums[i][e] - '0' + 1;
				val[i][s][e - s + 1] = x;
				int l = e - s + 1;
				it[m++] = i*100 + l*10 + s;
				assert(val[i][s][l] == get_val(it[m-1]));
			}
		}
	}
	auto cmp = [](const int & a,const int & b){
		return get_val(a) < get_val(b);
	};
	sort(it,it + m,cmp);
	set<int> S;
	loop(i,m){
		int j = i;
		while(j < m && get_val(it[i]) == get_val(it[j])) S.insert(it[j++]/100);
		cnt[i] = sz(S) ;
	/*	cerr << get_val(it[i]) << " - > " << i << " with " <<  endl;
		prArr(it+i,j-i,int);
		print(S,int);
	*/	S.clear();
		i = j - 1;
	}
	loop(i,n) {
		int s ,l,found = 0;
		for(l = 1;l <= 9 && !found;l++)
			for(s = 0;s < 9 && s + l <= 9 && !found;s++) {
		//		cerr << "searching for " << val[i][s][l] << " aka " << s << " " << l << endl;
				int x = lower_bound(it,it + m,val[i][s][l],[](const int & a,const int & target){
					return get_val(a) < target;
				}) - it;
		//		cerr << "gives " << x << " and " << cnt[x] << endl;
				if(cnt[x] == 1){
					found = 1;
					goto done;
				}
			}
		done:
		assert(found);
//		cerr << s << " " << l << endl;
		loop(j,l) putchar(nums[i][s + j]);
		puts("");
	}
	return 0;
}
