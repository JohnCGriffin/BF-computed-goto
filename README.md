# BF Demo of Computed GOTO 

This is a reasonably fast BF interpreter to demonstrate the utility of using computed goto in C++.
The premise is that a computed *goto can be more efficient and nearly as legible as a switch statement*
in an appropriate context.

(If you just want the result: **make demo**)

## Background

Taking the summer to do some practical programming instruction with my C.S. undergraduate son, I had
him create a BF interpreter in Java.  After he succeeded and had gone on to another project,
 I remained curious about other implementations.  I found
several at [EsoLang](https://esolangs.org/wiki/Brainfuck), noting a few labeled "very fast" and one as _the fastest_.  Feeling a challenge,
I whittled away hotspots on a new C++17 program to create an interpreter faster than all on the list.

A day later, I discovered the stunning performance of [sbfi.c by Maxine
Renaldo](https://github.com/rinoldm/sbfi), more than twice the speed of others found on EsoLang.
Reviewing his code, I found it lucid, well commented, and normal. Suddenly, my eyes stopped at:

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

When the decreasing returns finally showed an asymptote, I revisited the non-standard computed goto.

## Giving goto a try

After realizing that both clang++ and g++ both supported the computed goto on both my OSes - MacOS Catalina and Amazon Linux, 
I justified to myself that computed label address support was realistically standard enough.  The existing code path was 
previously a standard for-loop indexing into 
```std::vector<Instruction>``` with a switch statement using an ```Action``` enum to direct traffic in a switch statement.
I copied that procedure into another, converting that ```case``` entries into named labels for use with goto.  The main function
was redirected to call the goto-based procedure, with the runtime dropping 20%.

## In this case, the computed goto is more maintainable

Despite a goal of performance, a primary driver for selecting C++, the need for maintainability and
legibility remains paramount.  I see two facets that lean in favor of the computed goto.  First, the individual goto labels are 
just about as clear as their ```switch``` counterparts:

### Standard C/C++
```
   case MOVE:
       ptr += instr.val;
       break;
       
   case INCR:
       ptr[0] += instr.val;
       break;
```

### Using computed goto address
```
   MOVE:
      ptr += IP->val;
      LOOP();
      
   INCR:
      ptr[0] += IP->val;
      LOOP();
```
Second, the increase in performance resulting from the computed goto permitted removal of
redundant performance tweaks that intended to compact multiple BF statements into a single instruction.  The
net effect is that the overall program is easier to comprehend.  For instance, in the standard switch version, 
INCR followed by a MOVE had been optimized into
a new INCRMOVE instruction to reduce the extra switching operation.  In the goto version, considerable amounts
of previous optimization code handled automatically because it naturally bypassed the switch path.  The code
reduction for equivalent performance is the reason the computed goto is a maintenance win in this 
particular situation.

## Usage Hints

Should you find the need for the performance of the computed goto in your application, I suggest three deviations
from the array based jump table that C++ makes easy.  One increases performance and two increase correctness
and maintainability.

#### Avoid using an array of addresses

While an array of addresses is about as fast as a data structure can be, a better choice is doing no lookup at all.  
Instead, use a data structure in one pass to assign addresses as a member of the instruction.  Note the ```jump``` member:
```
struct Instruction {
    Action action;
    short val;
    void* jump;
};
```
Now, an ```Instruction*``` can jump immediately with ```goto (*instr->jump);```.  At the beginning of ```execute```,
all instructions are iterated and their jump pointers assigned.  That change yielded a further 10% performance boost.

#### Store addresses in std::map for correctness

A std::map not susceptible to having a mismatch between values and indices. Where 
a C program is likely to require careful coordination between an enum and 
a disconnected array using enum values as indices, a C++ program can 
guarantee coordination using a ```std::map<TheEnum,void*>```.

#### Enumerate the enum

Placing TERMINATE as the last enum member, the enums can be iterated in a for-loop, querying the std::map<TheEnum,void*>.  
This is done once at the beginning of the loop to bomb with ```std::logic_error``` on an unhandled enum member.  This is 
the runtime equivalent of compiler warning that ```switch``` is not handling an enum case.  Further, labels created but
unreferenced in the std::map<TheEnum,void*> are flagged at compile-time.

## Demo

Two demonstration programs are
generated by running ```make```: ```bf-jump``` and ```bf-switch```.  Running ```make comparison```
will run the included mandelbrot BF file with ```bf-switch``` and then ```bf-jump```.  The entire
compilation with its two comparative runs should be about 15 seconds.



   
   
   




















## 
