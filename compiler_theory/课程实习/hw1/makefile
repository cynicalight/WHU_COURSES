make:
	flex scanner.l
	gcc lex.yy.c
	./a.out < test.c > test.txt

clean:
	rm -f a.out lex.yy.c test.txt 