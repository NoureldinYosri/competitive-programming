//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vl vector<long long>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define popcnt(x) __builtin_popcountll(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//#define what_is(x) cerr << #x << " is " << x << endl
//#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
//const double PI = acos(-1);
//using namespace std;
//
//
//typedef pair<ll,ll> pl;
//ostream& operator << (ostream& st,const pl & p) {
//	st << "(" << p.xx << ", " << p.yy << ")";
//	return st;
//}
//
//int n,m;
//pl red[1 << 10],blue[1 << 10];
//
//int solve(){
//	int best = n + m;
//	vi rX,rY;
//	loop(msk1,1 << n){
//		vi X;
//		loop(i,n) if(msk1 & (1 << i)) X.pb(i);
//		loop(msk2,1 << m) {
//			FILE *C = fopen("milano.in","w");
//			fprintf(C,"1\n");
//			vi Y;
//			loop(i,m) if(msk2 & (1 << i)) Y.pb(i);
//			fprintf(C,"%d %d\n",sz(X),sz(Y));
//			loop(i,sz(X)) {
//				int j = X[i];
//				fprintf(C,"%lld %lld\n",red[j].xx,red[j].yy);
//			}
//			loop(i,sz(Y)) {
//				int j = Y[i];
//				fprintf(C,"%lld %lld\n",blue[j].xx,blue[j].yy);
//			}
//			fclose(C);
//			system("./check > res.out");
//			C = fopen("res.out","r");
//			char buffer[10];
//			fscanf(C,"%s",buffer);
//			int cost = n + m - sz(X) - sz(Y);
//			if(buffer[0] == 'Y') {
//				if(cost < best) {
//					best = cost;
//					rX = X;
//					rY = Y;
//				}
//			}
//			fclose(C);
//		}
//	}
//	return best;
//}
//
//int main(){
//	#ifdef HOME
//		freopen("in.in", "r", stdin);
//	#endif
//	int T; scanf("%d",&T);
//	range(t,1,T){
//		scanf("%d %d",&n,&m);
//		loop(i,n) scanf("%lld %lld",&red[i].xx,&red[i].yy);
//		loop(i,m) scanf("%lld %lld",&blue[i].xx,&blue[i].yy);
//		printf("%d\n",solve());
//	}
//
//	return 0;
//}
