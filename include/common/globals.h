#ifndef GLOBALS_H
#define	GLOBALS_H

#define FCY 39936000UL      // Frequency in hertz [Hz]
#define TCY 25U             // Period in nanoseconds [ns]

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b)        ( (a) |=  (1 << (b)) )  // BSET
#define BIT_CLR(a,b)        ( (a) &= ~(1 << (b)) )
#define BIT_TGL(a,b)        ( (a) ^=  (1 << (b)) )  // BTG
#define BIT_CHECK(a,b)      ( (a) & (1 << (b))   )

/* x=target variable, y=mask */
#define BITMASK_SET(x,y)    ( (x) |=   (y)  )
#define BITMASK_CLR(x,y)    ( (x) &= (~(y)) )
#define BITMASK_FLIP(x,y)   ( (x) ^=   (y)  )
#define BITMASK_CHECK(x,y)  ( (x) & (y)     )

#endif	/* GLOBALS_H */

