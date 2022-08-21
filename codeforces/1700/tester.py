from random import *
from string import *
from os import system, walk
import sys, os
import time
import argparse

MAXN = 5
MAXM = 5
MAXA = 5
MAXT = 5

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


def create_multiple(gen):
    T = randint(1,MAXT);
    ret = [str(T)];
    for t in range(T):
        ret += gen();
    return ret;


def compile(code):
    name,ext = code.split(".");
    if "py" == ext: return "python " + code;
    if "cpp" == ext: 
        system("g++ %s -o %s -std=c++17 -D DEBUG"%(code,name));
        return "./" + name;
    if "java" == ext:
        system("javac " + code);
        return "java -Xss256m " + name;
    raise IllegalArgumentException;


def format_time(elapsed_time):
    m = elapsed_time//60
    s = elapsed_time - m*60
    return f'{m}m {s}s'

def run(command, input_file, output_file, message = 'failed to run'):
    start_time = time.time()
    c = system(command + f" < {input_file} > {output_file}" );
    if c != 0:
        print(message, command)
        exit(0)
    if args.verbose:
        print('took', format_time(time.time() - start_time), 'to run', command)

def tokenize(fname):
    ret = [];
    with open(fname, 'r') as f:
        for l in f:
            ret.extend(l.split());
    return ret;


def tokens_checker():
    return tokenize('out.out') == tokenize('correct.out')

def doubles_checker():
    A = [float(s) for s in tokenize('out.out')]
    B = [float(s) for s in tokenize('correct.out')]
    if len(A) != len(B): return False
    for a, b in zip(A, B):
        d = abs(a - b)
        if not (d < 1e-6 or d/b < 1e-6):
            return False
    return True

def get_checker(mode):
    if '.' in mode:
        command = compile(mode)
        return lambda : system(command) == 0

    if mode == 'doubles':
        return doubles_checker
    else:
        return tokens_checker
        

def test_files(dname, S, checker, ifname):
    _, _, files = next(walk(dname))
    ifiles = list(filter(lambda s: ".in" in s, files))
    ofiles = list(filter(lambda s: '.ans' in s, files))
    for fname in ifiles:
        pref = fname.replace(".in", "")
        target = pref + ".ans"
        if target not in ofiles:
            print(fname, 'has no target output')
            exit(0)
    all_correct = True
    for i, fname in enumerate(ifiles):
        pref = fname.replace(".in", "")
        target = pref + ".ans"
        fr = os.path.join(dname, fname)
        to = os.path.join(dname, target)
        system(f'cp {fr} {ifname}')
        system(f'cp {to} correct.out')
        run(S, ifname, 'out.out')
        if not checker():
            print(f'failed :( on case {i+1}/{len(ifiles)} {fname}')
            all_correct = False
        else:
            print(f'passed :D case {i+1}/{len(ifiles)} {fname}')
    print('passed :D' if all_correct else "failed :'(")

def create_case(G, ifname, multiple):
    c = system(G + f" {ifname}" + (' multiple' if multiple else '' ) )
    if c:
        print('failed to create case')
        exit(0)


def test_random(S, J, G, checker, ifname, multiple):
    t = 0
    while True:
        create_case(G, ifname, multiple)
        run(S, ifname, 'out.out')
        if J is not None: run(J, ifname, 'correct.out')
        if not checker():
            print('found')
            exit(0)
        t += 1
        print(f'passed case #{t}')


if __name__ == "__main__":
    parser = argparse.ArgumentParser('automatic testing script')
    parser.add_argument('-S', help = 'code to be tested')
    parser.add_argument('-J', help = 'judging code')
    parser.add_argument('-G', help = 'test generator')
    parser.add_argument('-mode', help = 'testing mode or checker code')
    parser.add_argument('-input_dir', help = 'input dir to read cases from', default = None)
    parser.add_argument('-input_file_name', help = 'input file name', default = 'in.in')
    parser.add_argument('-multiple', help = 'multiple cases', default = False, action='store_true')
    parser.add_argument('-verbose', help = 'verbose', default = False, action='store_true')

    args = parser.parse_args()

    if args.mode is None:
        print('no testing mode supplied')
        exit(0)

    if args.S is None:
        print('no code to test')
        exit(0)
    else:
        S = compile(args.S)


    G = None
    if args.G is not None:
        G = compile(args.G)
        
    J = None
    if args.J is not None:
        J = compile(args.J)

    checker = get_checker(args.mode)


    if args.input_dir is not None:
        test_files(args.input_dir, S, checker, args.input_file_name)
    else:
        if G is None:
            print('no generator supplied')
            exit(0)
        test_random(S, J, G, checker, args.input_file_name, args.multiple)