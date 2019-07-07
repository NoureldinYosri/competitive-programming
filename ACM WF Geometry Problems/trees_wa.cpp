//#pragma GCC optimize ("O3")
//#include <bits/stdc++.h>
//#define loop(i,n) for(int i = 0;i < (n);i++)
//#define range(i,a,b) for(int i = (a);i <= (b);i++)
//#define all(A) A.begin(),A.end()
//#define pb push_back
//#define mp make_pair
//#define sz(A) ((int)A.size())
//#define vi vector<int>
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
//using namespace std;
//
//const double PI = acos(-1),EPS = 1e-8;
//struct Tree{
//	int x,y,d,h;
//	friend ostream& operator << (ostream & st,const Tree & t) {
//		st << "{(" << t.x << ", " << t.y << "), " << t.d << ", "
//				<< t.h << "}";
//		return st;
//	}
//};
//
//int xmin,xmax,ymin,ymax,n;
//Tree T[100];
//
//bool read(){
//	scanf("%d %d %d %d %d",&xmin,&ymin,&xmax,&ymax,&n);
//	if(xmin==0 && ymin==0 && xmax==0 && ymax==0 && n==0) return 0;
//	loop(i,n) scanf("%d %d %d %d",&T[i].x,&T[i].y,&T[i].d,&T[i].h);
//	return 1;
//}
//
//void translate(){
//	ymax -= ymin;
//	xmax -= xmin;
//	loop(i,n){
//		T[i].x -= xmin;
//		T[i].y -= ymin;
//	}
//	ymax *= 2;
//	xmax *= 2;
//	loop(i,n){
//		T[i].x <<= 1;
//		T[i].y <<= 1;
//		T[i].d <<= 1;
//		T[i].h <<= 1;
//	}
//}
//
//typedef pair<double,double> pd;
//deque<Tree> forest;
//vector<pd> forbidden;
//
//inline double make_2pi(double x){
//	if(abs(x) < EPS) x = 0;
//	if(x >= 0) return x;
//	return x + 2*PI;
//}
//
//bool cos_law(double a,double b,double c,double & theta) {
//	double ct = (a*a+b*b-c*c)/(2*a*b);
//	if(abs(-1 - ct) < EPS) ct = -1;
//	if(abs(1 - ct) < EPS) ct = 1;
//	if(ct < -1 || ct > 1) return 0;
//	theta = acos(ct);
//	return 1;
//}
//
//void get_forbidden(Tree a,Tree b) {
//	ll dx = b.x - a.x,dy = b.y - a.y;
//	assert(dx != 0 || dy != 0);
//	ll d2 = dx*dx + dy*dy;
//	double ar = a.d/2,br = b.d/2;
//	double h = a.h,d = sqrt(d2);
//	double theta1,theta2;
//	double h_bar = sqrt(ar*ar + h*h);
//	if(!cos_law(h,h_bar,ar,theta1) ||
//			!cos_law(d,h_bar,br,theta2))
//				return ;
//
//	double theta = theta1 + theta2;
//	assert(theta >= 0 && theta < PI);
//
//	double phi = atan2(dy,dx);
//	phi = make_2pi(phi);
//	if(abs(phi - theta) < EPS) forbidden.pb(mp(0,2*theta));
//	else {
//		if(phi < theta) {
//			forbidden.pb(mp(0,phi + theta));
//			forbidden.pb(mp(make_2pi(phi-theta),2*PI));
//		}
//		else forbidden.pb(mp(phi-theta,phi + theta));
//	}
//
//}
//
//double get_inter(){
//	sort(all(forbidden));
//	double s = -1,e = -1,ret = 0;
//	for(auto p : forbidden) {
//		if(p.first > e && abs(e - p.first) > EPS) {
//			ret += e - s;
//			s = p.first;
//			e = p.second;
//		}
//		else e = max(e,p.second);
//	}
//	ret += e - s;
//	return ret;
//}
//
//void get_forbidden_vbound(Tree t,int x) {
//	int h = abs(x - t.x);
//	double tr = t.d/2,th = t.h;
//	double h_bar = sqrt(tr*tr + th*th);
//	double theta = acos(th/h_bar) + acos(h/h_bar);
//
//	if(theta != theta) return;
//	double phi = 0;
//	if(t.x > x) {
//		phi = 0;
//		forbidden.pb(mp(2*PI-theta,2*PI));
//		forbidden.pb(mp(0,theta));
//	}
//	else {
//		phi = PI;
//		forbidden.pb(mp(phi - theta,phi + theta));
//	}
//}
//void get_forbidden_hbound(Tree t,int y) {
//	int h = abs(y - t.y);
//	double tr = t.d/2,th = t.h;
//	double h_bar = sqrt(tr*tr + th*th);
//	double theta = acos(th/h_bar) + acos(h/h_bar);
//	if(theta != theta) return;
//	double phi = PI/2;
//	if(t.y < y) phi += PI;
//	forbidden.pb(mp(phi - theta,phi + theta));
//}
//
//int solve(){
//	translate();
//	forest.clear();
//	loop(i,n) forest.push_back(T[i]);
//	int ret = 0,done = 0;
//	do{
//		done = 1;
//		int L = sz(forest);
//		for(int i = 0;i < L;i++) {
//			Tree ct = forest[i];
//			forbidden.clear();
//			for(int j = 0;j < L;j++) {
//				if(i != j) {
//					get_forbidden(ct,forest[j]);
//				}
//			}
//			get_forbidden_vbound(ct,0);
//			get_forbidden_vbound(ct,xmax);
//			get_forbidden_hbound(ct,0);
//			get_forbidden_hbound(ct,ymax);
////			for(auto p : forbidden){
////				prp(p);
////			}
////			cerr << endl;
//			double tot = get_inter();
//			bool can_be_cut = 1;
//			if(tot >= 2*PI || abs(tot-2*PI) < EPS)
//				can_be_cut = 0;
//			if(!can_be_cut)
//				forest.push_back(ct);
//			else
//				ret++,done = 0;
//		}
//		loop(i,L) forest.pop_front();
////		print(forest,Tree);
//	}while(!done);
//	return ret;
//}
//
//int main(int argc,char **argv){
//#ifdef HOME
//	freopen("in.in","r",stdin);
//#endif
//	for(int t = 1;read();t++) {
//		int ans = solve();
//		printf("Forest %d\n",t);
//		printf("%d tree(s) can be cut\n",ans);
//		puts("");
//	}
//	return 0;
//}
