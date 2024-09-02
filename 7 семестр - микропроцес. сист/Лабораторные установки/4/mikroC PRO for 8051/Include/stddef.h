#ifndef _STDDEF_H
#define _STDDEF_H

typedef int          ptrdiff_t;      /* type of the result of subtracting two pointers */
typedef unsigned int size_t;         /* type of the result of the sizeof operator */
typedef unsigned int wchar_t;        /* wide char type */

/* Offset of member MEMBER in a struct of type TYPE. */
#define offsetof(TYPE, MEMBER) ((size_t) (&(((TYPE *)(void *)0)->MEMBER)))

#ifndef  NULL
#define  NULL  ((void *)0)
#endif

#endif
