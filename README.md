- This is C student management project, create by Dinh Viet Hoang, student id: 23010051.
- To compile, first download libmariadbclient/ libmysqlclient 
    + if you use mingw w64 download from msys2 ucrt, you can download libmariadbclient via https://packages.msys2.org/package/mingw-w64-ucrt-x86_64-libmariadbclient?repo=ucrt64
    + if not, you can download via https://dev.mysql.com/downloads/connector/cpp/, then change #include<mysql/mysql.h> in function.h to #include"path to mysql.h"
- Then link to mysqlclient when compile. If you use gcc, the command will look like this: gcc main.c -o main -lmysqlclient
- if you are unable to compile main.c, you can run main.exe instead.
- Thank for reading.
