/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<< 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  return ~(~(x & ~y) & ~(~x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign = x >> 31;
  return sign & (~x + 1);
}

// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int srcByte = (x >> srcShift) & 0xFF;
  int clear = ~(0xFF << dstShift);
  return (x & clear) | (srcByte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int lo = 0x0F | (0x0F << 8) | (0x0F << 16) | (0x0F << 24);
  int hi = lo << 4;
  int lowNibbles = (x & lo) << 4;
  int highNibbles = (x & hi) >> 4;
  highNibbles = highNibbles & lo;   /* 清除算术右移补出的符号位 */
  return lowNibbles | highNibbles;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y = x | (x + 1);
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int y = x;
  y = y ^ (y >> 16);
  y = y ^ (y >> 8);
  y = y ^ (y >> 4);
  y = y ^ (y >> 2);
  y = y ^ (y >> 1);
  return ~y & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int s = n & 31;
  int left = (32 + (~s + 1)) & 31;
  int mask = ~(((1 << 31) >> s) << 1);
  return ((x >> s) & mask) | (x << left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int q = x >> n;
  int mask = (1 << n) + ~0;
  int r = x & mask;
  int half = 1 << (n + ~0);
  int roundUp = ((half + ~r + 1) >> 31) & 1;
  int tie = !(r ^ half);
  int odd = q & 1;
  int inc = roundUp | (tie & odd);
  return (q + inc) << n;
}
// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int avg = (x & y) + ((x ^ y) >> 1);
  int sumOdd = (x ^ y) & 1;
  int xNeg = x >> 31;
  int yNeg = y >> 31;
  int diff = x + ~y + 1;
  int diffNeg = diff >> 31;
  int xLarger = ((~xNeg & yNeg) | (~(xNeg ^ yNeg) & ~diffNeg)) & 1;
  return avg + (sumOdd & xLarger);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31, sa = a >> 31, sb = b >> 31;
  int dxa = sx ^ sa, dxb = sx ^ sb;
  int nsx = !sx, nsa = !sa, nsb = !sb;
  int ge_xa = (dxa & nsx) | (~dxa & !((x + ~a + 1) >> 31));
  int ge_xb = (dxb & nsx) | (~dxb & !((x + ~b + 1) >> 31));
  int ge_ax = (dxa & nsa) | (~dxa & !((a + ~x + 1) >> 31));
  int ge_bx = (dxb & nsb) | (~dxb & !((b + ~x + 1) >> 31));
  return (ge_xa & ge_bx) | (ge_xb & ge_ax);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int limit = 0x99 | (0x99 << 8) | (0x99 << 16) | (0x19 << 24);
  int xSign = x >> 31;

  int posOverMask = ~xSign & ((limit + ~x + 1) >> 31);
  int negOverMask = xSign & ((x + limit) >> 31);
  int overMask = posOverMask | negOverMask;

  int r = (x << 2) + x;
  int sat = (posOverMask & ~(1 << 31)) | (negOverMask & (1 << 31));

  return (r & ~overMask) | (sat & overMask);
}
// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int s2 = s1 + z;

  int c1 = ((x & y) | ((x | y) & ~s1)) >> 31 & 1;
  int c2 = ((s1 & z) | ((s1 | z) & ~s2)) >> 31 & 1;

  int neg = ((x >> 31) & 1) + ((y >> 31) & 1) + ((z >> 31) & 1);

  int m = neg + (~c1 + 1) + (~c2 + 1);

  int sign_s2 = (s2 >> 31) & 1;
  int pos_s2  = (~s2 >> 31) & 1;

  int overflow = (!m) & sign_s2;
  int underflow = ((!(m ^ 1)) & pos_s2) | (m >> 1);

  return overflow + (~underflow + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */

unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp  = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;

  if (exp == 0xFFu || !(exp | frac)) return uf;

  unsigned mant;
  int e;

  if (exp == 0) {
    mant = frac;
    e = -149;
    while ((mant & 0x800000u) == 0) {
      mant <<= 1;
      e--;
    }
  } else {
    mant = frac | 0x800000u;
    e = exp - 150;
  }

  unsigned prod = mant * 3u;
  unsigned q = prod >> 1;

  /* round-to-nearest-even：prod 奇数且 q 奇数时进位 */
  q += (prod & q & 1u);

  while (q >= 0x1000000u) {
    unsigned rb = q & 1u;
    q >>= 1;
    e++;
    if (rb && (q & 1u)) q++;
  }

  int msb = 0;
  unsigned tmp = q;
  while (tmp >>= 1) msb++;

  int exponent = msb + e;

  if (exponent < -126) {
    int shift = e + 149;

    if (shift >= 0) {
      unsigned fracOut = q << shift;
      if (fracOut & 0x800000u)
        return sign | (1u << 23) | (fracOut & 0x7FFFFFu);
      return sign | fracOut;
    } else {
      int rshift = -shift;
      if (rshift >= 32) return sign;

      unsigned fracOut = q >> rshift;
      unsigned rem = q & ((1u << rshift) - 1u);
      unsigned half = 1u << (rshift - 1);

      if (rem > half || (rem == half && (fracOut & 1u))) fracOut++;

      if (fracOut & 0x800000u)
        return sign | (1u << 23) | (fracOut & 0x7FFFFFu);
      return sign | fracOut;
    }
  } else {
    int expField = exponent + 127;
    if (expField >= 255) return sign | 0x7F800000u;

    unsigned sig = (msb == 23) ? q : (q << (23 - msb));
    return sign | (expField << 23) | (sig & 0x7FFFFFu);
  }
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  
  if (exp == 0xFF) return uf;  // NaN or Inf
  if (exp == 0) return sign;   // subnormal/zero rounds to 0
  
  int e = exp - 127;
  
  if (e < 0) {
    if (e == -1 && frac != 0)
      return sign | 0x3F800000;  // (0.5, 1) → 1.0
    return sign;                 // [0, 0.5] → 0
  }
  
  if (e >= 23) return uf;        // already integer
  
  unsigned full = frac | 0x800000;
  int shift = 23 - e;
  unsigned intpart = full >> shift;
  unsigned fracbits = full & ((1u << shift) - 1);
  
  if (fracbits == 0) return uf;
  
  unsigned half = 1u << (shift - 1);
  if (fracbits > half) {
    intpart += 1;
  } else if (fracbits == half) {
    if (intpart & 1) intpart += 1;
  }
  
  int msb = 31;
  while (!(intpart & (1u << msb))) msb--;
  
  unsigned newExp = msb + 127;
  unsigned newFrac = (msb >= 23) ? 0 : ((intpart << (23 - msb)) & 0x7FFFFF);
  
  return sign | (newExp << 23) | newFrac;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    unsigned sign, abs, exp, frac, shift;

    if (x == 0) return 0;

    /* 取符号位，注意不要用强制转换 */
    sign = x & 0x80000000;

    /* 取绝对值，注意 INT_MIN 取负仍然是 INT_MIN，但位模式正确 */
    if (sign) abs = -x;
    else abs = x;

    /* 求最高位 1 的位置 msb */
    int msb = 31;
    while (!(abs & (1u << msb))) msb--;

    /* 指数域 */
    exp = msb + 127;

    if (msb <= 23) {
        /* 尾数可以直接左移对齐 */
        frac = (abs << (23 - msb)) & 0x7FFFFF;
    } else {
        /* 需要舍入 */
        shift = msb - 23;
        frac = abs >> shift;

        unsigned rem  = abs & ((1u << shift) - 1);
        unsigned half = 1u << (shift - 1);

        /* round-to-nearest-even */
        if (rem > half || (rem == half && (frac & 1))) {
            frac++;
            if (frac == (1u << 24)) {
                frac = 0;
                exp++;
            }
        }
        frac &= 0x7FFFFF;
    }

    return sign | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);
  m1 = m1 | (m1 << 16);          // 0x55555555
  int m2 = 0x33 | (0x33 << 8);
  m2 = m2 | (m2 << 16);          // 0x33333333
  int m4 = 0x0F | (0x0F << 8);
  m4 = m4 | (m4 << 16);          // 0x0F0F0F0F
  int m8 = 0xFF | (0xFF << 16);  // 0x00FF00FF
  int m16 = 0xFF | (0xFF << 8);  // 0x0000FFFF

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x & m8) + ((x >> 8) & m8);
  x = (x & m16) + ((x >> 16) & m16);

  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
    /* 只能用 0x00~0xFF 常量，所以先拼出各个掩码 */

    int m1 = 0x55 | (0x55 << 8);
    m1 = m1 | (m1 << 16);          /* 0x55555555 */

    int m2 = 0x33 | (0x33 << 8);
    m2 = m2 | (m2 << 16);          /* 0x33333333 */

    int m4 = 0x0F | (0x0F << 8);
    m4 = m4 | (m4 << 16);          /* 0x0F0F0F0F */

    int m8 = 0xFF | (0xFF << 16);  /* 0x00FF00FF */

    int m16 = 0xFF | (0xFF << 8);  /* 0x0000FFFF */

    x = ((x >> 1) & m1) | ((x & m1) << 1);
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    x = ((x >> 4) & m4) | ((x & m4) << 4);
    x = ((x >> 8) & m8) | ((x & m8) << 8);
    x = ((x >> 16) & m16) | (x << 16);

    return x;
}