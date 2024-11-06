%{
#define YYSTYPE char *
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
#define _DUPTEXT {yytext = strdup(yytext);}
/* Tokens.  */
#define T_Int 1
#define T_Print 2
#define T_IntConstant 3
#define T_StringConstant 4
#define T_Identifier 5

%}

/* note \042 is '"' */

OPERATOR        ([-/+*()=,;])
INTEGER         ([0-9]+)
STRING          (\042[^\042\n]*\042)
IDENTIFIER      ([_a-zA-Z][_a-zA-Z0-9]*)
WHITESPACE      ([ \t]*)

%%
{OPERATOR}      { return yytext[0]; }
"int"           { return T_Int; }
"print"         { return T_Print; }

{INTEGER}       { return T_IntConstant; }
{STRING}        { return T_StringConstant; }
{IDENTIFIER}    { return T_Identifier; }

{WHITESPACE}    { /* ignore every whitespace */ }
\n              { cur_line++; }
.               { unrecognized_char(yytext[0]); }
%%

int yywrap(void) { 
    return 1;
}

void unrecognized_char(char c) {
    char buf[32] = "Unrecognized character: ?";
    buf[24] = c;
    yyerror(buf);
}

void yyerror(const char *msg) {
    printf("Error at line %d:\n\t%s\n", cur_line, msg);
    exit(-1);
}

// int main() {
// 	int token_type;
// 	while (token_type = yylex()) {
// 		printf("WORD:\t%s\n", yytext);
// 	}
// 	return 0;
// }

int main() {
    int token_type;
    while ((token_type = yylex()) != 0) { // 返回0表示识别结束
        switch (token_type) {
            case T_Int:
                printf("Token type: T_Int, Value: %s\n", yytext);
                break;
            case T_Print:
                printf("Token type: T_Print, Value: %s\n", yytext);
                break;
            case T_IntConstant:
                printf("Token type: T_IntConstant, Value: %s\n", yytext);
                break;
            case T_StringConstant:
                printf("Token type: T_StringConstant, Value: %s\n", yytext);
                break;
            case T_Identifier:
                printf("Token type: T_Identifier, Value: %s\n", yytext);
                break;
            default:
                printf("Token type: OPERATOR, Value: %c\n", token_type);
                break;
        }
    }
    return 0;
}