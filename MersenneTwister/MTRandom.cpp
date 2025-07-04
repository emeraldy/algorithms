#include "MTRandom.h"
#define _USE_32BIT_TIME_T
#include <time.h>

MTRandom::MTRandom()
{
	rseed=1;
	mti=CMATH_N+1;
}

//Returns a number from 0 to n (excluding n)
unsigned int MTRandom::RandomInt(unsigned int n)
{
	unsigned long y;
	static unsigned long mag01[2]={0x0,CMATH_MATRIX_A};

	if(n==0)
		return n;

	//mag01[x]=x*MATRIX_A for x=0,1
	if(mti>=CMATH_N)//generate N words at one time
	{
		int kk;

		if(mti==CMATH_N+1)//if no default seed
			setRandomSeed(4357);

		for(kk=0;kk<CMATH_N-CMATH_M;kk++)
		{
			y=(mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
			mt[kk]=mt[kk+CMATH_M]^(y>>1)^mag01[y&0x1];
		}

		for(;kk<CMATH_N-1;kk++)
		{
			y=(mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
			mt[kk]=mt[kk+(CMATH_M-CMATH_N)]^(y>>1)^mag01[y&0x1];
		}

		y=(mt[CMATH_N-1]&CMATH_UPPER_MASK)|(mt[0]&CMATH_LOWER_MASK);
		mt[CMATH_N-1]=mt[CMATH_M-1]^(y>>1)^mag01[y&0x1];

		mti=0;
	}

	y=mt[mti++];
	y^=CMATH_TEMPERING_SHIFT_U(y);
	y^=CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
	y^=CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
	y^=CMATH_TEMPERING_SHIFT_L(y);

	return y%n;
}

void MTRandom::setRandomSeed(unsigned int n)
{
	mt[0]=n & 0xffffffff;
	for(mti=1;mti<CMATH_N;mti++)
		mt[mti]=(69069*mt[mti-1]) & 0xffffffff;
	rseed=n;
}

unsigned int MTRandom::getRandomeSeed()
{
	return rseed;
}

void MTRandom::Randomise()
{
	setRandomSeed(time(NULL));
}