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

const int MAX = 1 << 20;
char A[MAX],B[MAX],C[MAX],line[MAX];
int a,b,d;
int main(){
	scanf("%d.%s",&a,B);
	char *q = B;
	while(*q != 'e') q++;
	*q = 0;
	q++;
	sscanf(q,"%d",&d);
	cerr << a << " " << B << " " << d << endl;
	b = strlen(B);	
	if(d == 0){
		printf("%d.%s\n",a,B);
	}
	else {
		char *p = B;
		sprintf(A,"%d",a);
		char *q = A + strlen(A);
		for(;*p && p - B < d;p++,q++) *q = *p;
		for(;p - B < d;d--,q++) *q = '0';
		q = A;
		for(;*q == '0';q++);
		if(!*q) putchar('0');
		else printf("%s",q);
		if(*p) printf(".%s",p);
		puts(""); 
	}	
	return 0;
}
