%{
#define YYSTYPE char * //语法分析树节点的类型
#include "y.tab.h"
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
void unterminate_string();
#define _DUPTEXT {yylval = strdup(yytext);} //duplicate text
//这个宏的目的是将 yytext 的内容复制到 yylval 中。在词法分析器中，yytext 是当前识别到的文本的字符串。strdup() 函数用于创建一个新的字符串，并将 yytext 的内容复制到新的字符串中。然后，将新的字符串赋值给 yylval，以便在语法分析器中使用。
%}

/* note \042 is '"' */
WHITESPACE          ([ \t\r\a]+)
SINGLE_COMMENT1     ("//"[^\n]*)
SINGLE_COMMENT2     ("#"[^\n]*)
OPERATOR            ([+*-/%=,;!<>(){}])
INTEGER             ([0-9]+)

IDENTIFIER          ([_a-zA-Z][_a-zA-Z0-9]*)
/* unterminated string for error handling */
UNTERM_STRING       (\042[^\042\n]*) 
STRING              (\042[^\042\n]*\042)

%%

\n                  { cur_line++; }
{WHITESPACE}        { /* ignore every whitespace */ }
{SINGLE_COMMENT1}   { /* skip for single line comment */    }
{SINGLE_COMMENT2}   { /* skip for single line comment */    }

{OPERATOR}          { return yytext[0]; } // yylex()的返回值是一个整数，它代表了识别到的词法单元的类型。在这里，我们直接返回了识别到的操作符。这样，语法分析器就可以根据返回值来判断识别到的词法单元是什么。
"int"               { return T_Int; }
"void"              { return T_Void; }
"return"            { return T_Return; }
"print"             { return T_Print; }

{INTEGER}           { _DUPTEXT return T_IntConstant; }
{STRING}            { _DUPTEXT return T_StringConstant; }
{IDENTIFIER}        { _DUPTEXT return T_Identifier; }

{UNTERM_STRING}     { unterminate_string(); }
.                   { unrecognized_char(yytext[0]); }

%%

// yywrap is called when the end of the input is reached
int yywrap(void) { 
    return 1;
}

//unrecognized character
void unrecognized_char(char c) {
    char buf[32] = "Unrecognized character: ?";
    buf[24] = c;
    yyerror(buf);
}

//unterminated string
void unterminate_string() {
    yyerror("Unterminate string constant");
}

//yyerror is called when an error occurs
void yyerror(const char *msg) {
    fprintf(stderr, "Error at line %d:\n\t%s\n", cur_line, msg);
    exit(-1);
}