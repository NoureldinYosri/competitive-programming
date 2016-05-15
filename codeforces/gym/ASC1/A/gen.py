inf = file("china.in","r");
ouf = file("china.out","w");
N = [line for line in inf]; 
N = int(N[0]); 
i = N >> 1;
while i > 1:
	a,b = N,i;
	while b : a,b = b,a%b;
	if a == 1: break;
	i -= 1;

ouf.write(str(i) + "\n");
