#pragma once
#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/applet/Applet"

class JavaTest : public Applet, public Runnable
{
public:
	JavaTest(void);
	~JavaTest(void);
	void Test();
    virtual void run();
	virtual void init();
	virtual void paint(Graphics* g);
};
