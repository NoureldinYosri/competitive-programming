#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 1e5 + 1e2;
int money[MAX],price[MAX],n,m,budget;
int tmp_money[MAX],needed[MAX];


int f(int num){
	int budget = ::budget;
	copy(money,money + n,tmp_money);
	reverse(tmp_money,tmp_money + num);	
	loop(i,num){
		if(budget + tmp_money[i] < price[i]) return 0;
		budget -= max(price[i] - tmp_money[i],0);
	}
	return 1;
}

int get_min(int num){
	int budget = ::budget,used = 0;
	copy(money,money + n,tmp_money);
	reverse(tmp_money,tmp_money + num);
	//prArr(tmp_money,num,int);
	//prArr(price,num,int);	
	needed[num - 1] = 0;
	for(int i = num - 2;i >= 0;i--) needed[i] = max(price[i + 1] - tmp_money[i + 1],0) + needed[i + 1];
	//prArr(needed,num,int);
	loop(i,num){
		int have = budget - needed[i];
	//	fprintf(stderr,"have = %d,price = %d,money = %d ,budget = %d,used = %d\n",have,price[i],money[i],budget,used);
		budget -= min(price[i],have);
		used += min(max(0,price[i] - have),tmp_money[i]);
	}
	return used;
}

int main(){
	scanf("%d %d %d",&n,&m,&budget);
	loop(i,n) scanf("%d",money + i);
	loop(i,m) scanf("%d",price + i);
	sort(money ,money + n);
	reverse(money ,money + n);
	sort(price ,price + m);
		
	int s = 0,e = min(n,m);
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(f(m)) s = m;
		else e = m - 1;
	}
	int ans = get_min(s);
	printf("%d %d\n",s,ans);	
	fprintf(stderr,"%d %d\n",s,ans);	
	return 0;
}
