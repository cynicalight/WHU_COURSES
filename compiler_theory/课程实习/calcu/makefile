run: a.out 
	./a.out

a.out: syntax.tab.c lex.yy.c
	cc lex.yy.c syntax.tab.c

syntax.tab.c: syntax.y lex.yy.c
	bison -d syntax.y

lex.yy.c: lex.l
	flex $<


