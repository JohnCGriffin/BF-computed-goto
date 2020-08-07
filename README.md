# BF-computed-goto

This is a reasonably fast BF interpreter to demonstrate the utility of using computed goto in C++.
The premise is that a computed *goto can be more efficient and nearly as legible as a switch statement*
in an appropriate context.

## Background

Taking the summer to do some practical programming instruction with my C.S. undergraduate son, I had
him create a BF interpreter in Java.  After he succeeded and had gone on to another project,
 I remained curious about other implementations.  I found
several at EsoLang and when seeing some noted as high performance and one as _the fastest_.  Feeling a challenge,
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

## Goto? and worse yet, an unstandard goto?

Having never found the need to use a goto, and seeing that the computed address was a compiler-specific feature, I set aside
the idea of using it.  I suspected that a switch statement in C++ had to be just as fast, and certainly more standard.  Thus,
I whittled away some more with decreasing returns.

## Let's try it

After realizing that both clang++ and g++ both supported the computed goto on both my OSes - MacOS Catalina and Amazon Linux, 
I concluded it was realistically standard enough.  My execution path was previously a standard for-loop indexing into 
```std::vector<Instruction>``` with a switch statement using an ```Action``` enum to direct traffic in a switch statement.
I copied that procedure into another, converting that ```case``` entries into named labels for use with goto.  Redirecting
the main function to call the new procedure, it worked, and my code ran in 20% less time.

## In this case, a goto is overall more legible and maintainable than the equivalent switch

Given that there is a goal of performance, one of the reasons to use C++ anyway, the question of maintainability and
legibility is paramount.  I see two facets that lean in favor of the computed goto.  First, the goto targets are 
just about as clear as their ```switch``` counterparts:
























## 
