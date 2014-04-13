#include "mathHelper.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

// Taken from the Nils Engine
// Credit to Nils Desle

namespace MathHelper
{
	double frac( double val )
	{
		return val - floor( val );
	}

	float frac( float val )
	{
		return val - floor( val );
	}

	float Damp( float oldValue, float newValue, float newFactor )	// a big newFactor means less damping
	{
		assert( newFactor >= 0.0f );
		assert( newFactor <= 1.0f );

		return oldValue * (1.0f - newFactor) + newValue * newFactor;
	}

	bool IsPowerOf2( unsigned int i ) 
	{ 
		return ((i & (i-1)) == 0); 
	}

	float rFloatRange( float a, float b )
	{
		return ((b-a)*((float)rand()/RAND_MAX))+a;
	}

	int rIntRange( int a, int b )
	{
		return a + (rand() % (int)(b - a + 1));
	}

}