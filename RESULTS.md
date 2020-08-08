## Runtimes 

On a single 2015 Macbook, using Catalina, Ubuntu 20.04, and Docker-based Linuxes inside those hosts, 
the differences are striking.

|Environment                   |Compiler (-O3)         | Switch  |Goto  | reduction |
|------------------------------|-----------------------|---------|------|-----------|
|Ubuntu 20.04 5.4.0-42-generic | clang 10.0.0-4ubuntu1 |5.46     |4.76  | 13%       |
|Ubuntu 20.04 5.4.0-42-generic | g++ 9.3.0-10ubuntu2   |7.80     |4.73  | 39%       |
|Docker-based Ubuntu 20.04.1   | g++ 9.3.0-10ubuntu2   |22.46    |8.91  | 60%       |
|Docker-based Ubuntu 20.04.1   | clang 10.0.0-4ubuntu1 |21.00    |9.62  | 54%       |
|Docker-based Amazon Linux 2   | g++ 7.3.1             |21.64    |9.08  | 58%       |
|Docker-based Amazon Linux 2   | clang 7.0.1           |20.67    |9.61  | 54%       |
