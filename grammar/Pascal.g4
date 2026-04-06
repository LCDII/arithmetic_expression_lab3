grammar Pascal;

// ---------- PARSER RULES ----------
program : statement* EOF ;

statement : assignment SEMICOLON
          | whileLoop SEMICOLON
          | expression SEMICOLON
          ;

assignment : VARIABLE '=' expression ;

whileLoop : WHILE '(' condition ')' DO statement* END ;

condition : expression ( (LESS | GREATER | EQUALS | LESS_EQ | GREATER_EQ | NOT_EQ) expression )? ;

expression : term ((PLUS | MINUS) term)* ;

term : factor ((MULTIPLY | DEVIDE) factor)* ;

factor : INTEGER
       | DOUBLE
       | VARIABLE
       | '(' expression ')'
       ;

// ---------- TOKENS ----------
PLUS       : '+' ;
MINUS      : '-' ;
MULTIPLY   : '*' ;
DEVIDE     : '/' ;
SEMICOLON  : ';' ;
EQUALS     : '=' ;
WHILE      : 'while' ;
DO         : 'do' ;
END        : 'end' ;
LESS       : '<' ;
GREATER    : '>' ;
LESS_EQ    : '<=' ;
GREATER_EQ : '>=' ;
NOT_EQ     : '!=' | '<>' ;

VARIABLE   : [a-zA-Z_][a-zA-Z0-9_]* ;
DOUBLE     : [0-9]+ '.' [0-9]+ ;
INTEGER    : [0-9]+ ;

WS         : [ \t\r\n]+ -> skip ;