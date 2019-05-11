yacc -d modified_grammar.y
lex scanner.l
g++ lex.yy.c y.tab.c -ll -ly
./a.out < input.txt