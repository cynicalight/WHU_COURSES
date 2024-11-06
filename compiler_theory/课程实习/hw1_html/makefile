run: lex 
	./lex < html.txt > out.txt

lex: lex.yy.c
	gcc -o $@ $<

lex.yy.c: lex.l
	flex $<
