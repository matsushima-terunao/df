/**
 * @file
 *
 * $Id: cpp2javalibdef.h,v 1.10 2007/11/30 22:42:27 matsushima Exp $
 *
 * cpp2javalibdef.h : 
 *
 * @author  0.0 2005/03/14 matsushima h2java
 * @author  0.1 2006/07/13 matsushima cpp2javalib
 * @version $Revision: 1.10 $
 * @since   0.0 2005/03/14 matsushima h2java
 *
 * $Log: cpp2javalibdef.h,v $
 * Revision 1.10  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.9  2007/05/14 13:38:09  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.8  2007/05/14 05:21:53  matsushima
 * no message
 *
 * Revision 1.7  2007/05/10 22:29:47  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.6  2007/05/10 14:31:24  matsushima
 * operator T&()
 *
 * Revision 1.5  2007/05/09 21:17:23  matsushima
 * no message
 *
 * Revision 1.4  2007/05/09 12:45:23  matsushima
 * no message
 *
 * Revision 1.3  2007/05/07 21:39:52  matsushima
 * staticメンバアクセス :: -> .
 *
 * Revision 1.2  2007/04/23 17:06:33  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:00  matsushima
 * new
 *
 */

#ifndef _CPP2JAVALIBDEF_H_
#define _CPP2JAVALIBDEF_H_

#if 0//1//def _DEBUG
#pragma warning(disable:4786)
#endif

#pragma include_alias("../cpp2javalib/java/awt/Image", "../cpp2javalib/java/awt/Image_")

#ifdef _DEBUG
#include <cstdlib>
#include <new>
#include <memory>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#undef _ASSERT
#define _ASSERT(expr) expr
#undef _ASSERTE
#define _ASSERTE(expr) expr
#endif

template<typename T> void jdelete(T& p) { delete p; }
template<typename T> T& _R(T* p) { return *p; }
//#define _R(p) (*(p))

#define JTYPEDEF_R(c)   typedef c& c
#define JTYPEDEF_P(c)   typedef c* c
#define JSTATIC(c)      c##Static& c = _##c##Static
#define JMEMBER(c, m)   c& m = *this->m
#define JPARAM(c, p)    c& p = *_##p

#ifdef __cplusplus
    extern "C" {
#endif

/*------------------------------------------------------------*/

extern void ap_split();

#define _C(expr) expr
#define _J(expr)

//
#define null    NULL

// type
typedef unsigned char   jbyte;
typedef short           jshort;
typedef int             jint;
typedef _int64          jlong;
typedef unsigned short  jchar;
//typedef bool            boolean;
typedef unsigned char   byte;
typedef unsigned char   boolean;

// class
#define jcpublic        _J(public)
#define jcprotected     _J(protected)
#define jcprivate       _J(private)
#define jcabstract      _J(abstract)
#define jinterface      _C(class)_J(interface)
#define jextends        _C(: public)_J(extends)     // class A jextends B               class A : public B              class A extends B
#define jimplements     _C(, public)_J(implements)  // class A jextends B jimplements C class A : public B, public C    class A extends B implements C
#define jimplements1    _C(: public)_J(implements)  // class A jimplements1 C           class A : public C              class A implements C

// method
#define jfpublic        public _C(: virtual)    // jfpublic f();    public: virtual f();    public f() { ... }
#define jfpritected     protected _C(: virtual) // jfprotected f(); protected: virtual f(); protected f() { ... }
#define jfprivate       private _C(:)           // jfprotected f(); private: f();           private f() { ... }
#define jfabstract(f)   _C(f = 0)_J(abstract f) // jabstract(f());  f() = 0;                abstract f() { ... }
#define jthrows(e)      _J(throws e)
#define jthrows1(e1)                _J(throws e1)
#define jthrows2(e1,e2)             _J(throws e1, e2)
#define jthrows3(e1,e2,e3)          _J(throws e1, e2, e3)
#define jthrows4(e1,e2,e3,e4)       _J(throws e1, e2, e3, e4)
#define jthrows5(e1,e2,e3,e4,e5)    _J(throws e1, e2, e3, e4, e5)

// other member
#define jmpublic        public _C(:)
#define jmprotected     protected _C(:)
#define jmprivate       private _C(:)

/*------------------------------------------------------------*/

#ifdef __cplusplus
    }
#endif

//template<typename T> class JBase
//{
//public:
//    operator T*() const { return (T*)this; }
//    operator T&() const { return (T&)this; }
//    T* operator->() const { return (T*)this; }
//};
//
////template<typename T> bool operator==(void* p, T& p2) { return p == &p2; }
//template<typename T> bool operator!=(void* p, T& p2) { return p != &p2; }

// auto pointer
template<class T> class JPtr
{
private:
    T* ptr;
    void refer(T* t)   { if (t) t->refer(); ptr = t; }
    void release(T* t) { if (t && t->release()) delete t; }
    void outref(const char* m) { if (ptr) ptr->outref(m); }
public:
    JPtr(JPtr& p)            {               refer(p.ptr); outref("JPtr(JPtr&)"); }
    JPtr(T* t = 0)           {               refer(t);     outref("JPtr(T*)"); }
    JPtr(T& t)               {               refer(&t);    outref("JPtr(T&)"); }
    JPtr& operator=(JPtr& p) { release(ptr); refer(p.ptr); outref("=JPtr&"); return *this; }
    JPtr& operator=(T* t)    { release(ptr); refer(t);     outref("=T*");    return *this; }
    ~JPtr()                  { outref("~"); release(ptr); }
    T* operator->() const { return ptr; }
    T* operator&()  const { return ptr; }
    operator T&() const { return *ptr; }
};

/*------------------------------------------------------------*/

#include "java/lang/all"
///#include "java.util.h"

#endif /* #ifndef _CPP2JAVALIBDEF_H_ */
