# BF-computed-goto

This is a reasonably fast BF interpreter to demonstrate the utility of using computed goto in C++.
The premise is that a computed *goto can be more efficient and nearly as legible as a switch statement*
in an appropriate context.

## Background

Taking the summer to do some practical programming instruction with my C.S. undergraduate son, I had
him create a BF interpreter in Java.  After he succeeded and had gone on to another project,
 I remained curious about other implementations.  I found
several at EsoLang and when seeing some noted as high performance and one _the fastest_.  Not resisting the challenge,
I whittled away hotspots on a new  C++17 program to create an interpreter faster than all on the list.

A day later, my satifisfaction was blown out of the water with the performance of sbfi.c by Maxine
Renaldo.  I started reading his code. Everything seemed lucid and well done. My eyes stopped at:

```
static const void *instr[9] =
    {
        &&end,
        &&changevalue,
        &&leftbracket,
        &&rightbracket,
        &&zerocell,
        &&seekzerocell,
        &&movecell,
        &&output,
        &&input
    };
```
The comments below this structure explained that they were the addresses of labels.  Each label
was reached via
```
goto *(instr[(int)code[i]]);
```

## 




## 
