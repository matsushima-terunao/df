/**
 * @file
 *
 * $Id: Random.cpp,v 1.3 2007/11/30 22:42:28 matsushima Exp $
 *
 * Random.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.3 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Random.cpp,v $
 * Revision 1.3  2007/11/30 22:42:28  matsushima
 * çƒìoò^
 *
 * Revision 1.2  2007/04/24 02:19:22  matsushima
 * no message
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Random"
#include <stdlib.h>
#include <time.h>

/*------------------------------------------------------------*/

Random::Random()
{
    static bool init = false;
    if (! init)
    {
        //srand((unsigned int)time(NULL));
        srand(RANDOM_SEED);
        init = true;
    }
}

int Random::nextInt()
{
    return rand() - RAND_MAX / 2;
}

double Random::nextDouble()
{
    return (double)rand() / RAND_MAX;
}
