%{
#define LABEL_A 1
#define LABEL_B 2
#define TEXT 3

int num_labela = 0, num_labelb = 0, num_text = 0;

%}

LABEL_B     ("</"[^<>]+">")
LABEL_A     ("<"[^<>/]+">")
SINGLE_COMMENT1     ("//"[^\n]*)
SINGLE_COMMENT2     ("#"[^\n]*)

%%

[\n]                { /* ignore all spaces */               }
[ \t\n]+   			{ /* Ignore whitespace, tabs, and newlines */ }
[ \t\r\a]+          { /* ignore all spaces */               }
{SINGLE_COMMENT1}   { /* skip for single line comment */    }
{SINGLE_COMMENT2}   { /* skip for single line commnet */    }
{LABEL_A}    		{ num_labela++; printf("\nLABEL_A: %s\n", yytext); }
{LABEL_B}    		{ num_labelb++; printf("\nLABEL_B: %s\n", yytext); }
[^<>]+              { num_text++; printf("\nTEXT: %s\n", yytext); }
.                   { printf("\nUnrecognized character\n---------------------");      }

%%

int main() {
    yylex();
    printf("\nnum_labela\tnum_labelb\tnum_text\n");
    printf("%d\t%d\t%d\n", num_labela, num_labelb, num_text);
    return 0;
}



int yywrap() {
    return 1;
}
