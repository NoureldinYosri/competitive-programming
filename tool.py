#! /usr/bin/env python
from random import *;
from string import *;
from Tkinter import *
import shutil
import os;


def refine(path,name,inp,out,categories):
	if inp == "": inp = "in.in";
	if out == "": out = "out.out";
	if path == "": path = "..";
	path = "/home/noureldin/Desktop/workspace/" + path + "/";
	if name == "": name = choice("rand %d"%rand(1,1000));
	categories = "_".join(categories.split());
	return path,name,inp,out,categories;

def create_main(inp,out):
	try:
		os.mknod("main.cpp");
		f = file("/home/noureldin/Desktop/workspace/template.cpp","r");
		s = "".join([l for l in f]);
		f.close();
		f = file("main.cpp","w");
		f.write(s%(inp if inp != "in.in" else "",out if out != "out.out" else ""));
		f.close();
		print "successfully created main.cpp"
	except:
		print "couldn't create main.cpp";
		pass;

def create_meta(judge,inp,out):
	try:
		os.mknod("meta.data");
		f = file("meta.data","w");
		f.write("%s %s %s"%(inp,out,judge));
		f.close();
		print "successfully created meta.data";
	except:
		print "couldn't create meta.data";
		pass;

def create_tester():
	try:
		os.mknod("tester.py");
		shutil.copy("/home/noureldin/Desktop/workspace/tester.py","tester.py");
		print "successfully created tester.py";
	except:
		print "couldn't create tester.py";
		pass;

def create_project(path,name,categories,inp,out):	
	path,name,inp,out,categories = refine(path,name,inp,out,categories);
	if not os.path.exists(path + name):
		os.makedirs(path + name);
	os.chdir(path + name);	
	files = [inp,out,"correct.out",categories];
	for f in files:
		try:
			os.mknod(f);
			print "success created",f;
		except:
			print "counldn't create '",f,"'";
	create_main(inp,out);
	create_meta(path,inp,out);
	create_tester();
	for f in files + ["main.cpp","tester.py"]:
		os.system("gedit %s"%f);
	

def read_data():
	master = e1 = e2 = e3 = e4 = e5 = None;	
	def read(event):
		create_project(e1.get(),e2.get(),e3.get(),e4.get(),e5.get());
		master.quit();

	master = Tk()
	master.bind("<Return>",read);	
	Label(master, text="judge").grid(row=0)
	Label(master, text="probID").grid(row=1)
	Label(master, text="categories").grid(row=2)
	Label(master, text="input file").grid(row=3)
	Label(master, text="output file").grid(row=4)
	e1 = Entry(master)
	e2 = Entry(master)
	e3 = Entry(master)
	e4 = Entry(master)
	e5 = Entry(master)

	e1.grid(row=0, column=1)
	e2.grid(row=1, column=1)
	e3.grid(row=2, column=1)
	e4.grid(row=3, column=1)
	e5.grid(row=4, column=1)

	master.mainloop();

if __name__ == "__main__":
	read_data();
