mkdir .\output
g++ -O2 .\src\main.cpp .\src\Lexer.cpp .\src\LR1Parser.cpp -o .\output\test.exe

.\output\test.exe .\test\input\input.txt test\grammer\grammer.txt