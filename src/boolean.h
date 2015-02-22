#pragma once

#define false   0
#define true    1

#define bool int

/* Visual Studio 2010 will NOT allow you to use stdbool.h
which defines boolean types and values.  This is because
the C compiler doesn't support C99, a past version of the
C programming language standard.  Actually, it only supports
C89 (ANSI C) from the 1980's.  I could compile the game in
C++ and that would get rid of the problem.  However, I have
been advised against it too many times for me to count.

I could also just use 0's and 1's, but since I'm used to
writing true and false and it would make the code easier
to read, why not just define it myself? */