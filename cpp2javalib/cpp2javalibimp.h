/**
 * @file
 *
 * $Id: cpp2javalibimp.h,v 1.4 2007/11/30 22:42:27 matsushima Exp $
 *
 * cpp2javalibimp.h : 
 *
 * @author  0.0 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.4 $
 * @since   0.0 2005/07/20 matsushima cpp2javalib
 *
 * $Log: cpp2javalibimp.h,v $
 * Revision 1.4  2007/11/30 22:42:27  matsushima
 * �ēo�^
 *
 * Revision 1.3  2007/05/07 21:39:52  matsushima
 * static�����o�A�N�Z�X :: -> .
 *
 * Revision 1.2  2007/04/24 09:35:40  matsushima
 * no message
 *
 * Revision 1.1.1.1  2006/08/17 20:26:00  matsushima
 * new
 *
 */

/*
�\���v���p�e�B -> C/C++ -> �ǉ��̃C���N���[�h�f�B���N�g��: .;..;../..;../../..
*/

#ifndef _CPP2JAVALIBIMP_H_
#define _CPP2JAVALIBIMP_H_

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1 // CRT �̃Z�L�����e�B�@�\

#define _IMPLEMENT_CPP2JAVALIB_
#include "cpp2javalibdef.h"

#include <list>

#ifdef __cplusplus
    extern "C" {
#endif

/*------------------------------------------------------------*/

#define C2J_THROWMSG(msg) String(msg) + "(" + __FILE__ + ":" + __LINE__ + ")"

// CRT �̃Z�L�����e�B�@�\
#define fopen my_fopen
#define _makepath(path, drive, dir, fname, ext) _makepath_s(path, drive, dir, fname, ext)
#define _splitpath my_splitpath

static FILE* my_fopen(const char* path, const char* mode)
{
	FILE* fp;
	fopen_s(&fp, path, mode);
	return fp;
}

static errno_t my_splitpath(const char* path, char* drive, char* dir, char* fname, char* ext)
{
	return _splitpath_s(
		path,
		drive,
		(NULL == drive) ? 0 : _MAX_DRIVE,
		dir,
		(NULL == dir) ? 0 : _MAX_DIR,
		fname,
		(NULL == fname) ? 0 : _MAX_FNAME,
		ext,
		(NULL == ext) ? 0 : _MAX_EXT);
}

// warning C4996: 'strlwr': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strlwr. See online help for details.
#define strlwr _strlwr

typedef struct _OBJSTACK
{
    typedef std::list<void*> STACK;
    STACK stack;
} OBJSTACK;

/*------------------------------------------------------------*/

#ifdef __cplusplus
    }
#endif

#endif /* #ifndef _CPP2JAVALIBIMP_H_ */
