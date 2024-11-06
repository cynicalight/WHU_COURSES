%{
int yylex(void);
 // forward declaration!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!zj
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char*);
#define YYSTYPE char *
%}

// Definitions
// 终结符中，单字符 token （ token type 值和字符的 ASCII 码相同）也不需要预先定义，
// 在产生式内部直接用单引号括起来就可以了（如本文件中的 ‘+’, ‘-‘ 等），
// 其他类型的 token 则需要预先在 Definitions 段中定义好
%token T_Int T_Void T_Return T_Print T_IntConstant
%token T_StringConstant T_Identifier

%left '+' '-'
%left '*' '/'
%right U_neg // 一元运算符

%%
//产生式中的非终结符不需要预先定义， bison 会自动根据所有产生式的左边来确定哪些符号是非终结符
// Grammar
Program:
    /* empty */             { /* empty */ }
|   Program FuncDecl        { /* empty */ }
;

// FuncDecl 用于解析整个函数声明
FuncDecl:
    RetType FuncName '(' Args ')' '{' VarDecls Stmts '}'
                            { printf("ENDFUNC\n\n"); }
;

// RetType 用于解析函数返回类型
RetType:
    T_Int                   { /* empty */ }
|   T_Void                  { /* empty */ }
;

// FuncName 用于解析函数名
FuncName:
    T_Identifier            { printf("FUNC @%s:\n", $1); } // $1 代表第一个终结符
;

// Args 用于解析整个参数列表
Args:
    /* empty */             { /* empty */ }
|   _Args                   { printf("\n\n"); }
;

// 辅助非终结符，用于解析具体的参数，并处理多个参数的情况
_Args:
    T_Int T_Identifier      { printf("arg %s", $2); }
|   _Args ',' T_Int T_Identifier
                            { printf(", %s", $4); }
;

// VarDecls 顶层的非终结符，用于解析整个变量声明列表
VarDecls:
    /* empty */             { /* empty */ }
|   VarDecls VarDecl ';'    { printf("\n\n"); }
;

// 辅助非终结符，用于解析具体的变量声明，并处理多个变量声明的情况
VarDecl:
    T_Int T_Identifier      { printf("var %s", $2); }
|   VarDecl ',' T_Identifier
                            { printf(", %s", $3); }
;

// Stmts 用于解析整个语句列表 stmts means statements
Stmts:
    /* empty */             { /* empty */ }
|   Stmts Stmt              { /* empty */ }
;

// Stmt 用于解析整个语句
Stmt:
    AssignStmt              { /* empty */ }
|   PrintStmt               { /* empty */ }
|   CallStmt                { /* empty */ }
|   ReturnStmt              { /* empty */ }

;

// AssignStmt 用于解析整个赋值语句
AssignStmt:
    T_Identifier '=' Expr ';'
                            { printf("pop %s\n\n", $1); }
;

// PrintStmt 用于解析整个打印语句
PrintStmt:
    T_Print '(' T_StringConstant PActuals ')' ';'
                            { printf("print %s\n\n", $3); }
;

//  PActuals 用于解析整个print实参列表
PActuals:
    /* empty */             { /* empty */ }
|   PActuals ',' Expr       { /* empty */ }
;

// CallStmt 用于解析整个函数调用语句
CallStmt:
    CallExpr ';'            { printf("pop\n\n"); }
;

//  CallExpr 用于解析整个函数调用
CallExpr:
    T_Identifier '(' Actuals ')'
                            { printf("$%s\n", $1); }
;

// Actuals 用于解析整个实参列表
Actuals:
    /* empty */             { /* empty */ }
|   Expr PActuals           { /* empty */ }
;

// ReturnStmt 用于解析整个返回语句
ReturnStmt:
    T_Return Expr ';'       { printf("ret ~\n\n"); }
|   T_Return ';'            { printf("ret\n\n"); }
;

// Expr 用于解析整个表达式
Expr:
    Expr '+' Expr           { printf("add\n"); }
|   Expr '-' Expr           { printf("sub\n"); }
|   Expr '*' Expr           { printf("mul\n"); }
|   Expr '/' Expr           { printf("div\n"); }
|   '-' Expr %prec U_neg    { printf("neg\n"); }
|   T_IntConstant           { printf("push %s\n", $1); }
|   T_Identifier            { printf("push %s\n", $1); }
|   CallExpr                { /* empty */ }
|   '(' Expr ')'            { /* empty */ }
;

%%

int main() {
    int flag = yyparse(); 
    if (flag == 0) {
        printf("Parse success!\n");
    } else {
        printf("Parse failed!\n");
    }
    return flag;
}