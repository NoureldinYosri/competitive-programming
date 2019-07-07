//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define PI acos(-1)
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
//#define vl vector<long long>
//#define vd vector<double>
//#define vp vector<pair<int,int> >
//#define ll long long
//#define pi pair<int,int>
//#define point pair<double,double>
//#define pl pair<ll,ll>
//#define popcnt(x) __builtin_popcount(x)
//#define LSOne(x) ((x) & (-(x)))
//#define xx first
//#define yy second
//#define PQ priority_queue
//#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
//#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
//#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
//#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
//using namespace std;
//
//const int MAX = 1e5 + 1e2;
//int n,A[MAX],blkSize;
//deque<int> blk[500];
//deque<int> aux;
//int cnt[500][MAX];
//
//int erase(int r){
//	int u = r/blkSize;
//	r -= u*blkSize;
//	cnt[u][blk[u][r]]--;
//	for(;r;r--){
//		aux.pb(blk[u].front());
//		blk[u].pop_front();
//	}
//	int v = blk[u].front();
//	blk[u].pop_front();
//	while(!blk[u].empty()){
//		aux.pb(blk[u].front());
//		blk[u].pop_front();
//	}
//	blk[u] = aux;
//	aux.clear();
//	return v;
//}
//
//void insert(int l,int v){
//	int u = l/blkSize;
//	cnt[u][v]++;
//	l -= u*blkSize;
//	for(;l;l--){
//		aux.pb(blk[u].front());
//		blk[u].pop_front();
//	}
//	aux.pb(v);
//	while(!blk[u].empty()){
//		aux.pb(blk[u].front());
//		blk[u].pop_front();
//	}
//	blk[u] = aux;
//	aux.clear();
//}
//
//void rotate(int l,int r){
//	int v = erase(r);
//	insert(l,v);
//	int u = l/blkSize;
//	while(sz(blk[u]) > blkSize){
//		v = blk[u].back(); blk[u].pop_back();
//		cnt[u][v]--;
//		blk[u + 1].push_front(v);
//		cnt[u + 1][v]++;
//		u++;
//	}
///*	cerr << "after " << l << " " << r << endl;
//	loop(i,(n-1)/blkSize + 1){
//		print(blk[i],int);
//		prArr(cnt[i]+1,n,int);
//	}
//	cerr << "============" << endl;
//	*/
//}
//
//
//int main(){
//	scanf("%d",&n); blkSize = sqrt(n);
//	loop(i,n) {
//		scanf("%d",A + i);
//		int u = i/blkSize;
//		cnt[u][A[i]]++;
//		blk[u].pb(A[i]);
//	}/*
//	loop(i,(n-1)/blkSize + 1){
//		print(blk[i],int);
//	}
//	cerr << "============" << endl;
//	*/
//	int m,ans = 0; scanf("%d",&m);
//	while(m--){
//		int t,l,r; scanf("%d %d %d",&t,&l,&r);
//		l = (l + ans - 1)%n;
//		r = (r + ans - 1)%n;
//		if(l > r) swap(l,r);
//
//		if(t == 1) rotate(l,r);
//		else{
//			int k ; scanf("%d",&k);
//			k = (k + ans - 1)%n + 1;
//			ans = 0;
//			int u = l/blkSize,v = r/blkSize;
//			l -= u*blkSize;
//			r -= v*blkSize;
//			if(u == v){
//				for(int i = l;i <= r;i++)
//					ans += blk[u][i] == k;
//			}
//			else{
//				for(int i = l,L = blk[u].size();i < L;i++)
//					ans += blk[u][i] == k;
//				for(int i = 0;i <= r;i++)
//					ans += blk[v][i] == k;
//				for(++u;u < v;u++)
//					ans += cnt[u][k] ;
//			}
//			printf("%d\n",ans);
//	//		cerr << ans << endl;
//	//		return 0;
//		}
//	}
//	return 0;
//}
