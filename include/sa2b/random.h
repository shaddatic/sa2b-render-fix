/*
*   Sonic Adventure Mod Tools (SA2B) - '/random.h'
*
*   Contains functions for chance and random calculations using 
*   the mersenne twister (mt) algorithm.
* 
*   Useful when game 'rand()' isn't enough, or is unreliable.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SAMT_RANDOM_H_
#define _SAMT_RANDOM_H_

/************************/
/*  Definitions         */
/************************/
#define RAND64_MAX         (18'446'744'073'709'551'615)
#define RAND32_MAX         ( 4'294'967'295)
#define RAND16_MAX         (65'535)
#define RAND15_MAX         (32'767)

#define RAND16_INVMAX      (1.0/(double)(RAND16_MAX+1))

#define RANDINT_SHIFT       0.0000000000000001

#define RANDINT_INVMAX     (RAND16_INVMAX-RANDINT_SHIFT)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set random seeds **/
void    mtRandAutoSeeds();            /* Automatically set seeds to CPU tick */
void    mtRandSetSeeds(uint64_t seed);

/** Get random integer **/
uint64_t mtRand64();     /* 0 - 18,446,744,073,709,551,615 */
uint32_t mtRand32();     /* 0 -  4,294,967,295 */
uint16_t mtRand16();     /* 0 - 65,535 */
int32_t  mtRand15();     /* 0 - 32,767           (Mimicks standard 'rand()' function) */

EXTERN_END

/************************/
/*  Rand Definitions    */
/************************/
/** Basic Rand Calculation 
    Returns a value from 0 to 1 **/
#define mtRandom()              ((double)mtRand16()*RAND16_INVMAX)

/** Random Real Value Calculation 
    Returns a value between 0 and 'max_val' **/
#define mtRandomReal(max_val)   (((double)mtRand16()*RAND16_INVMAX)*(double)(max_val))

/** Random Integer Value Calculation 
    Returns a value between 0 and 'max_val' (inclusive) **/
#define mtRandomInt(max_val)    ((int)(((double)mtRand16()*RANDINT_INVMAX)*(double)(max_val + 1)))

/** Random Boolean Calculation 
    Returns a random boolean value **/
#define mtRandomBool()          (((double)mtRand16()*RAND16_INVMAX)<0.5)

/** Array Chance Calculation 
    Returns a random element of given array **/
#define mtRandomArray(ary)      (ary[mtRandomInt(arylen(ary)-1)])

#endif /* _SAMT_RANDOM_H_ */
