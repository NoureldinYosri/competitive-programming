#ifndef __FFT
#define __FFT
#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

struct num{
	long double real,imag;
public:
	num(){real=imag=0;}
	num(double a,double b){
		real = a;
		imag = b;
	}
	num operator /= (const double & c){
		this->real /= c;
		this->imag /= c;
		return *this;
	}
	num operator * (const double & c){
		return num(real*c,imag*c);
	}
	num operator + (const num & o){
		return num(real + o.real,imag + o.imag);
	}
	num operator - (const num & o){
		return num(real - o.real,imag - o.imag);
	}
	num operator * (const num & o){
		return num(real*o.real - imag*o.imag,real*o.imag + imag*o.real);
	}
	friend ostream& operator << (ostream & st,const num & n)  {
		st << setprecision(3) <<  "(" << n.real << " ," << n.imag << " )";
		return st;
	}

};


typedef num* poly;
const num one (1.0,0.0),zero(0.0,0.0);

int rev(int n,int l){
	char s[l + 1];
	for(int i = 0;i < l;i++) s[i] = '0';
	for(int i = 0;n;i++,n /= 2) s[i] = n%2 + '0';
	int ans = 0;
	for(int i = 0;i < l;i++) ans = (ans << 1) + (s[i] - '0');
	return ans;
}
int len(int n){
	int ans = 0;
	for(;n;n /= 2) ans++;
	return ans;
}

void bit_rev(poly IN,poly OUT,int m){
	int l = len(m)-1;
	for(int i = 0;i < m;i++){
		OUT[rev(i,l)] = IN[i];
	}
}

void fft(poly IN,poly OUT,bool inv,int n){
	bit_rev(IN,OUT,n);
	for(int s = 1,lg = len(n) - 1;s <= lg;s++){
		int m = (1 << s);
		double theta = 2*PI/m;
		if(inv) theta *= -1;
		num wm = num(cos(theta),sin(theta));
		for(int k = 0;k < n;k += m){
			num w = one;
			for(int j = 0;j < m/2;j++){
				num t = w*OUT[k + j + m/2];
				num u = OUT[k + j];
				OUT[k + j] = u + t;
				OUT[k + j + m/2] = u - t;
				w = w*wm;
			}
		}
	}
	if(inv) for(int i = 0;i < n;i++) OUT[i] /= n;
}

num* transform(vector<int> V,int n) {
	poly P = new num[n];
	for(int i = 0;i < n;i++) {
		P[i] = num();
		if(i < (int)V.size())
			P[i] = num(V[i],0);
	}
	return P;
}
#endif
