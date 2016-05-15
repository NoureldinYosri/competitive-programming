from random import randint;
f = file("in.in","w");

f.write("1\n1 ");
f.write(str(randint(1,100)) + " " + str(randint(1,100)) + " " + str(randint(1,100)) + "\n");
f.close();

