from Tkinter import *

master = e1 = e2 = e3 = e4 = e5 = None;

def f(event):
	print e1.get();
	master.quit();
	print "here";

def main():
	global master,e1,e2,e3,e4,e5;
	master = Tk()
	master.bind("<Return>",f);	
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

main();
