#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 10*1000;
int N,M,K;
int A[MAX],P[MAX];
vi B,C;
ll best;
int coef[MAX][MAX],prod[MAX];
int f[MAX];

int mul(ll a,int b,int m) {
	ll ret = (a*1LL*b)%m;
	if(ret < 0) ret += m;
	return ret;
}
int add(ll a,int b,int m){
	return (a+b)%m;
}



ll eval(bool c) {
	ll ret = 0;
	loop(j,M) {
		int tmp = prod[j];
		loop(i,N){
			int v = add(B[i],A[i],P[j]);
			tmp = add(tmp,mul(v,coef[i][j],P[j]),P[j]);
		}
		ret += tmp;
		if(c) f[j] = tmp;
	}
	return ret;
}

ll inc(int i,ll val) {
	loop(j,M) {
		int o = f[j];
		f[j] = add(f[j],coef[i][j],P[j]);
		val += f[j] - o;
	}
	B[i]++;
	return val;
}

ll dec(int i,ll val) {
	loop(j,M) {
		int o = f[j];
		f[j] = add(f[j],P[j]-coef[i][j],P[j]);
		val += f[j] - o;
	}
	B[i]--;
	return val;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	srand((unsigned ll)(new char()));
	scanf("%d %d %d",&N,&M,&K);
	loop(i,N) scanf("%d",A + i);
	loop(i,M) scanf("%d",P + i);
	vi suff(N+1,0);

	loop(j,M){
		suff[N] = 1;
		for(int i = N-1;i >= 0;i--)
			suff[i] = mul(suff[i+1],A[i],P[j]);
		int pref = 1;
		prod[j] = suff[0];
		loop(i,N){
			coef[i][j] = mul(pref,suff[i+1],P[j]);
			pref = mul(pref,A[i],P[j]);
		}
	}


	B = C = vi(N,0);
	best = eval(0);

	ll tot = 8e7;
	PQ<pair<ll,int>> pq;
	loop(i,N) pq.push(mp((rand()*1LL*rand()+rand())%best,i));

	for(;tot > 0;){
		loop(i,N) B[i] = (rand()*1LL*rand() + rand())%K;
		ll cur = eval(1);
		tot -= N*M;
		if(cur > best){
			best = cur;
			C = B;
		}
		int ctr = 0,f = 0;
		for(int itr = 0;itr < 250 && tot > 0;itr++,tot -= M){
			f = 0;
			int i = pq.top().yy; pq.pop();
			ll bi = -rand();
			int c = -1;
			if(B[i] > 0 && B[i] < K)
				c = rand()%2;
			else if(B[i] > 0)
				c = 0;
			else if(B[i] + 1 <= K)
				c = 1;
			if(c == 0) {
				ll tmp = dec(i,cur);
				if(tmp >= cur){
					f = 1;
					cur = tmp;
				}
				else{
					inc(i,tmp);
				}
				bi = max(bi,tmp);
			}
			if(c == 1) {
				ll tmp = inc(i,cur);
				if(tmp >= cur){
					f = 1;
					cur = tmp;
				}
				else{
					dec(i,tmp);
				}
				bi = max(bi,tmp);
			}
//			assert(cur == eval(0));
//			print(B,int);
//			print(C,int);
			if(cur > best){
				best = cur;
				C = B;
			}
			bi = (rand()*bi*1.0)/RAND_MAX;
			pq.push(mp(bi,i));
			if(f == 0) ctr ++;
			else ctr = 0;
			if(ctr == 70) break;
		}
	}
//	B = C;
//	cerr << eval(0) << endl;
	cerr << best << endl;
	loop(i,N)
		printf("%d%c",A[i] + C[i]," \n"[i==N-1]);
	return 0;
}
