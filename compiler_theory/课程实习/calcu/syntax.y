%token   HEXADECIMAL INTEGER VARIABLE SIN COS TAN
%left    '+' '-'
%left    '*' '/'
%left    '&'
%left    '|'
%left    '^'
%right   '@''~'
%left    '!'

%{

/*for Xcode */
/*  #define  __STDC__   0   */   

    #include <stdio.h>   
    #include <math.h>
    #define YYSTYPE double
    #define pi 3.1415926 
    void yyerror(char*);
    int yylex(void);

    double sym[26];
%}

%%
program:
    program statement '\n'
    |
    ;
statement:
     expr    {printf("=%lf\n[calculation]:$ ", $1);}
     |VARIABLE '=' expr    {sym[(int)$1] = $3;}
     ;
expr:
    INTEGER
    |HEXADECIMAL
    |VARIABLE{$$ = sym[(int)$1];}
    |expr '+' expr    {$$ = $1 + $3;}
    |expr '-' expr    {$$ = $1 - $3;}
    |expr '*' expr    {$$ = $1 * $3;}
    |expr '/' expr    {$$ = $1 / $3;}
    |expr '&' expr    {$$ = (int)$1 & (int)$3;}
    |expr '|' expr    {$$ = (int)$1 | (int)$3;}
    |'~' expr         {$$ = ~(int)$2;}
    |'@' expr         {$$ = sqrt($2);}
    |expr '@' expr    {$$ = $1*sqrt($3);}
    |expr '!'         {int i=1,s=1;for(;i<=$2;i++)s*=i;$$=s;}
    |expr '^' expr    {$$=pow($1,$3);}
    |'('expr')'       {$$ = $2;}
    |SIN'('expr')'       {$$ = sin($3*pi/180.0);}
    |COS'('expr')'       {$$ = cos($3*pi/180.0);}
    |TAN'('expr')'       {$$ = tan($3*pi/180.0);}
    ;

%%

void yyerror(char* s)
{
    fprintf(stderr, "---%s\n", s);
}

int main(void)
{
    printf("计算器\n支持的运算符：+-*/&|~!^@ \n");
    printf("+: 加法 2+3 \n");
    printf("-: 减法 2-3 \n");
    printf("*: 乘法 2*3 \n");
    printf("/: 除法 2/3 \n");
    printf("！: 阶乘 2！\n");
    printf("^: 乘方  2^3 \n");
    printf("^: 开方  2@3 \n");
    printf("&: 与 2&3 结果为二进制转化的十进制数\n");
    printf("|: 或 2|3 结果为二进制转化的十进制数\n");
    printf("~: 非 2|3 结果为二进制转化的十进制数\n");
    printf("sin: 正弦值  sin(30) 单位为rad \n");
    printf("sin: 余弦值  cos(30) 单位为rad \n");
    printf("tan: 正切值  tan(30) 单位为rad \n");
    yyparse();
    return 0;
}
