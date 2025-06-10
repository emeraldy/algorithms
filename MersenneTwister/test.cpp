#include <iostream>
#include "MTRandom.h"

using namespace std;

void main()
{
	MTRandom randGen;
	//randGen.Randomise();
	randGen.setRandomSeed(100);
	unsigned int roll=randGen.RandomInt(100);
	cout<<roll<<endl;
	roll=randGen.RandomInt(100);
	cout<<roll<<endl;
}
