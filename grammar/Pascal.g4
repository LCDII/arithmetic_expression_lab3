grammar Polynomial;


poly
    : term (('+'|'-') term)* EOF
    ;

term
    : coefficient? monomial?
    ;

coefficient
    : NUMBER
    | INTEGER
    ;


monomial
    : factor+
    ;


factor
    : VARIABLE (POW exponent)?
    ;

exponent
    : INTEGER
    ;


INTEGER  : [+-]? [0-9]+ ;
NUMBER   : [+-]? [0-9]+ ('.' [0-9]+)? ;
VARIABLE : [xyz] ;
POW      : '^' ;
WS       : [ \t\r\n]+ -> skip ;