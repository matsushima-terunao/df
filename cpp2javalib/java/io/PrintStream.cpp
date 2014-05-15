/**
 * @file
 *
 * $Id: PrintStream.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * PrintStream.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: PrintStream.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "PrintStream"
#include <stdio.h>
#include <windows.h>

/*------------------------------------------------------------*/

PrintStream::PrintStream()
{
    stream = OUT_STDOUT;
}

void PrintStream::print(const char* x)
{
    switch (stream)
    {
    case OUT_STDOUT:
        printf("%s", x);
        OutputDebugString(x);
        break;
    case OUT_OUTPUTDEBUGSTRING:
    case OUT_WINDOW:
        OutputDebugString(x);
        break;
    default:
        _ASSERTE(0);
        break;
    }
}

void PrintStream::println()
{
    print("\n");
}

void PrintStream::println(const char* x)
{
    print(x);
    println();
}

void PrintStream::println(long x)
{
    println(String() + x);
}

void PrintStream::print(long x)
{
    print(String() + x);
}
