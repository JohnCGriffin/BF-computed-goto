## Runtimes 

On a single 2015 Macbook, using Catalina and Ubuntu 20.04, with both clang++ and g++:

|Environment                   |Compiler (-O3)         | Switch  |Goto  | reduction |
|------------------------------|-----------------------|---------|------|-----------|
|Ubuntu 20.04 5.4.0-42-generic | clang 10.0.0-4ubuntu1 |5.46     |4.76  | 13%       |
|Ubuntu 20.04 5.4.0-42-generic | g++ 9.3.0-10ubuntu2   |7.80     |4.73  | 39%       |
|MacOS 10.15.5                 | clang++ 11.0.3 (Apple)|6.10     |4.66  | 23%       |

