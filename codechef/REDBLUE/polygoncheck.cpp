//#include <iostream>
//#include <algorithm>
//#include <stdio.h>
//using namespace std;
//
//
//struct point{
//	long long x;
//	long long y;
//};
//bool operator<(point a,point b){
//	if(a.x==b.x){
//		return a.y<b.y;
//	}
//	return a.x<b.x;
//}
//int n,m;
//
//point red[100100],blue[100100];
//
//
//point upper_red[100100],lower_red[100100],upper_blue[100100],lower_blue[100100];
//
//int upr=0,lwr=0,upb=0,lwb=0;
//
//
//bool is_left(point a,point b,point c){
//	long long x1=b.x-a.x;
//	long long y1=b.y-a.y;
//	long long x2=c.x-b.x;
//	long long y2=c.y-b.y;
//
//	return x1*y2 - x2*y1 >= 0;
//}
//
//bool is_right(point a,point b,point c){
//	long long x1=b.x-a.x;
//	long long y1=b.y-a.y;
//	long long x2=c.x-b.x;
//	long long y2=c.y-b.y;
//
//	return x1*y2 - x2*y1 <= 0;
//}
//
//bool is_intersect(point a,point b,point c,point d){
//	if(is_left(a,b,c) && is_left(a,b,d) && is_right(a,b,c) && is_right(a,b,d)){
//		if(a.x > b.x){
//			swap(a.x,b.x);
//		}
//		if(a.y > b.y){
//			swap(a.y,b.y);
//		}
//		if(c.x > c.x){
//			swap(c.x,c.x);
//		}
//		if(c.y > c.y){
//			swap(c.y,c.y);
//		}
//		if(a.x==b.x){
//			return min(b.y,d.y) >= max(a.y,c.y);
//		} else {
//			return min(b.x,d.x) >= max(a.x,c.x);
//		}
//	}
//	if((is_right(a,b,c) && is_left(a,b,d)) ||  (is_left(a,b,c) && is_right(a,b,d))){
//		if((is_right(c,d,a) && is_left(c,d,b)) || (is_left(c,d,a) && is_right(c,d,b))){
//			return true;
//		}
//	}
//	return false;
//}
//int T;
//bool pointInsideSeg(point p,point q,point a){
//	if(!is_right(p,q,a) || !is_left(p,q,a)){
//		return false;
//	}
//
//	if(p.x==q.x){
//		return min(p.y,q.y)<=a.y && a.y <=max(p.y,q.y);
//	} else {
//		return min(p.x,q.x)<=a.x && a.x <=max(p.x,q.x);
//	}
//}
//int main(){
//	freopen("milano.in","r",stdin);
//	point a,b,c;
//	//cin>>T;
//	scanf("%d",&T);
//	while(T--){
//		//cin>>n>>m;
//		scanf("%d %d",&n,&m);
//		for(int i=0;i<n;i++){
//			scanf("%lld %lld",&red[i].x,&red[i].y);
//			//cin>>red[i].x>>red[i].y;
//		}
//		for(int i=0;i<m;i++){
//			//cin>>blue[i].x>>blue[i].y;
//			scanf("%lld %lld",&blue[i].x,&blue[i].y);
//		}
//		if(n==1 && m==1){
//			printf("YES\n");
//			continue;
//		}
//		sort(red,red+n);
//		sort(blue,blue+m);
//		upr=lwr=upb=lwb=0;
//		for(int i=0;i<n;i++){
//			while(upr > 1 && is_left(upper_red[upr-2],upper_red[upr-1],red[i])){
//				upr--;
//			}
//			while(lwr > 1 && is_right(lower_red[lwr-2],lower_red[lwr-1],red[i])){
//				lwr--;
//			}
//			upper_red[upr++]=red[i];
//			lower_red[lwr++]=red[i];
//		}
//		for(int i=0;i<m;i++){
//			while(upb > 1 && is_left(upper_blue[upb-2],upper_blue[upb-1],blue[i])){
//				upb--;
//			}
//			while(lwb > 1 && is_right(lower_blue[lwb-2],lower_blue[lwb-1],blue[i])){
//				lwb--;
//			}
//			upper_blue[upb++]=blue[i];
//			lower_blue[lwb++]=blue[i];
//		}
//		bool ok=false;
//
//		point B=upper_blue[0],R=upper_red[0];
//
//		if(n>1){
//			bool is_in=true;
//
//			if(upr ==2 && lwr==2){
//				if(!pointInsideSeg(upper_red[0],upper_red[1],B)){
//					is_in=false;
//				}
//			} else {
//				for(int i=1;i<upr;i++){
//					if(!is_right(upper_red[i-1],upper_red[i],B)){
//						is_in=false;
//					}
//				}
//				for(int i=1;i<lwr;i++){
//					if(!is_left(lower_red[i-1],lower_red[i],B)){
//						is_in=false;
//					}
//				}
//				if(is_in){
//					ok=true;
//				}
//			}
//
//			if(m==1){
//				if(is_in){
//					printf("NO\n");
//				} else {
//					printf("YES\n");
//				}
//				continue;
//			}
//		}
//		if(m>1){
//			bool is_in=true;
//			if(lwb==2 && upb==2){
//				if(!pointInsideSeg(upper_blue[0],upper_blue[1],R)){
//					is_in=false;
//				}
//			} else {
//				for(int i=1;i<upb;i++){
//					if(!is_right(upper_blue[i-1],upper_blue[i],R)){
//						is_in=false;
//					}
//				}
//				for(int i=1;i<lwb;i++){
//					if(!is_left(lower_blue[i-1],lower_blue[i],R)){
//						is_in=false;
//					}
//				}
//				if(is_in){
//					ok=true;
//				}
//			}
//			if(n==1){
//				if(is_in){
//					printf("NO\n");
//				} else {
//					printf("YES\n");
//				}
//				continue;
//			}
//		}
//		if(ok){
//			printf("NO\n");
//			continue;
//		}
//		int a=0,b=0,c=0,d=0;
//		bool is_inter=false;
//		while(a<upr-2 || b<lwr-2 || c<upb-2 || d<lwb - 2){
//			if(is_intersect(upper_red[a],upper_red[a+1],upper_blue[c],upper_blue[c+1])){
//				is_inter=true;
//				break;
//			}
//			if(is_intersect(upper_red[a],upper_red[a+1],lower_blue[d],lower_blue[d+1])){
//				is_inter=true;
//				break;
//			}
//
//			if(is_intersect(lower_red[b],lower_red[b+1],upper_blue[c],upper_blue[c+1])){
//				is_inter=true;
//				break;
//			}
//			if(is_intersect(lower_red[b],lower_red[b+1],lower_blue[d],lower_blue[d+1])){
//				is_inter=true;
//				break;
//			}
//
//			if(a<upr-2 && (upper_red[a+1].x <= lower_red[b+1].x || !(b<lwr-2)) && (upper_red[a+1].x <= upper_blue[c+1].x || !(c<upb-2)) && (upper_red[a+1].x <= lower_blue[d+1].x || !(d<lwb-2))){
//				a++;
//				continue;
//			}
//
//			if(b<lwr-2 && (lower_red[b+1].x <= upper_red[a+1].x || !(a<upr-2)) && (lower_red[b+1].x <= upper_blue[c+1].x || !(c<upb-2)) && (lower_red[b+1].x <= lower_blue[d+1].x || !(d<lwb-2))){
//				b++;
//				continue;
//			}
//
//			if(c<upb-2 && (upper_blue[c+1].x <= upper_red[a+1].x || !(a<upr-2)) && (upper_blue[c+1].x <= lower_red[b+1].x  || !(b<lwr-2)) && (upper_blue[c+1].x <= lower_blue[d+1].x || !(d<lwb-2))){
//				c++;
//				continue;
//			}
//
//			if(d<lwb-2 && (lower_blue[d+1].x <= upper_red[a+1].x || !(a<upr-2)) && (lower_blue[d+1].x <= lower_red[b+1].x  || !(b<lwr-2)) && (lower_blue[d+1].x <= upper_blue[c+1].x || !(c<upb-2))){
//				d++;
//				continue;
//			}
//		}
//		if(is_intersect(upper_red[a],upper_red[a+1],upper_blue[c],upper_blue[c+1])){
//			is_inter=true;
//		}
//		if(is_intersect(upper_red[a],upper_red[a+1],lower_blue[d],lower_blue[d+1])){
//			is_inter=true;
//		}
//		if(is_intersect(lower_red[b],lower_red[b+1],upper_blue[c],upper_blue[c+1])){
//			is_inter=true;
//		}
//		if(is_intersect(lower_red[b],lower_red[b+1],lower_blue[d],lower_blue[d+1])){
//			is_inter=true;
//		}
//		if(is_inter){
//			printf("NO\n");
//		} else {
//			printf("YES\n");
//		}
//	}
//}
