from random import *;
from string import *;
from os import system;
import sys;

MAXN = 5;
MAXM = 2;
MAXA = 5;
MAXT = 5;
firstRun = True;

def create_tree(n):
    name = [i+1 for i in range(n)];
    E = [[name[i-1],name[randint(1,i-1)-1]] for i in range(2,n+1)];
    return E;

def create_str(n,alpha):
	return "".join(choice(alpha) for i in range(n));

def create_thue_morse_string(n,a,b):
    if n == 1: return a;
    ret = ['' for i in range(n)]
    ret[0] = a;
    m = 1;
    while m < n:
        for i in range(m):
            if i + m >= n: break;
            if ret[i] == a:
                ret[i + m] = b;
            else:
                ret[i + m] = a;
        m <<= 1;
    return;

def checker():
	def read(s):
		f = open(s,'r')
		F = [l for l in f]
		f.close()
		S = []
		for l in F:
			S.extend(l.split())
		return S

	return len(read('out.out')) == len(read('correct.out'))

def create_small_case():
	ret = []
	n = randint(1,MAXN)
	ret.append(str(n))
	for i in range(n):
		ret.append("{} {} {}".format(randint(-MAXA,MAXA),randint(1,MAXA),randint(1,MAXA)))	
	ret.append("0")
	return ret

def create_big_case():
    pass

def create_worst_case():
    pass;

def create_trick_case():
    pass


def create_multiple(gen):
    T = randint(1,MAXT);
    ret = [str(T)];
    for t in range(T):
        ret += gen();
    return ret;

def create_test():
    f = open("in.in","w");
    testGens = []
    testGens.append(create_small_case)

    gen = choice(testGens);
    case = gen()
    

    for l in case:
        f.write(l + "\n");

    f.close();


def read(name):
    f = open(name);
    F = [l for l in f];
    f.close();
    return F;

def tokenize(F):
    ret = [];
    for l in F:
        ret.extend(l.split());
    return ret;

def same(a,b):
    diff = abs(b - a);
    return diff <= 1e-6 or diff <= b*1e-6;
    
def is_correct(test_mode):
    global firstRun
    A = read("out.out");
    B = read("correct.out");
    modes = ["doubles","tokens","firstToken","firstDouble","speed","checker"];
    if test_mode not in modes:
        #compare lines and don't ignore white spaces
        if firstRun:
            print ("compare lines and don't ignore white spaces")
            firstRun = False;
        system("diff out.out correct.out > err.log");
        F = read("err.log");
        return len(F) == 0;        

    
    A = tokenize(A);
    B = tokenize(B);
    if len(A) != len(B):
        return False;

    n = len(A);
    if n == 0: return True;

    if test_mode == "doubles":
        for i in range(n):
            a = float(A[i]);
            b = float(B[i]);
            if not same(a,b): return False;
        return True;
    elif test_mode == "tokens":
        return A == B;
    elif test_mode == "firstToken":
        return A[0] == B[0]
    elif test_mode == "firstDouble":
        return same(float(A[0]),float(B[0]));
    elif test_mode == "speed":
        return True;
    elif test_mode == "checker":
    	return checker()
    raise Exception;


def compile(code):
    name,ext = code.split(".");
    if "py" == ext: return "python " + code;
    if "cpp" == ext: 
        system("g++ %s -o %s -std=c++11 -D DEBUG"%(code,name));
        return "./" + name;
    if "java" == ext:
        system("javac " + code);
        return "java -Xss256m " + name;
    raise IllegalArgumentException;


def run(command,output_file):
    c = system(command + " < in.in > " + output_file);
    if c != 0:
        print("failed to run",command)
        exit(0)

def main():
    main,correct,test_mode = sys.argv[1:4];
    main = compile(main);
    correct = compile(correct);

    i = 1;
    while True:
        create_test();
        run(main,"out.out");
        run(correct,"correct.out");
        if not is_correct(test_mode):
            print ("found");
            break;
        print ("done with %d"%i)
        i += 1;

if __name__ == "__main__":
    main();
