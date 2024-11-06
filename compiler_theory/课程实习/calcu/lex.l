%{

    //int yywrap();
    #define YYSTYPE double
    #define HEXADECIMAL 258
    #define INTEGER 259
    #define VARIABLE 260
    #define SIN 261
    #define COS 262
    #define TAN 263
    void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    }

    //#include "syntax.tab.h"


%}

%%

     /* a-z为变量 */   
[a-z]   {
            //yylval = *yytext - 'a';
            return VARIABLE;
        }
    /*16进制数*/
0x\.?[a-f0-9]+|0x[a-f0-9]+\.[a-f0-9]* {
            //yylval=atof(yytext);
            return HEXADECIMAL;
        }

    /* 实数部分 */
\.?[0-9]+|[0-9]+\.[0-9]*    {
            //yylval = atof(yytext);
            return INTEGER;
        }

    /* 运算符 */
[-+()=/*&|~!^@\n]  {return *yytext;}

    /* 三角函数 */
sin {
    return SIN;
    }

cos {
    return COS;
    }
tan {
    return TAN;
    }

<<EOF>> { return 0; }

    /* 空白被忽略 */
[ \t]    ;

    /* 其他字符都是非法的 */
.    yyerror("警告！输入无效ERROR！");

%%


int main() {
	int token_type;
	while (token_type = yylex()) {
		printf("WORD:\t%s\n", yytext);
	}
	// printf("\nChars\tWords\tLines\n");
	// printf("%d\t%d\t%d\n", numChars, numWords, numLines);
	return 0;
}

int yywrap()
{return 1;}
