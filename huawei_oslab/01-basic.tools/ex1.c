myapp: main.o my.o
 gcc –o myapp main.o my.o
main.o: main.c a.h
 gcc –c main.c 
my.o : my.c b.h
 gcc –c my.c 
clean:
 rm myapp main.o my.o
