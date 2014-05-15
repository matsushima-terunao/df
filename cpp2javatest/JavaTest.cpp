#include "JavaTest.h"
#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/lang/all"
#include "../cpp2javalib/java/net/all"
#include "../cpp2javalib/java/util/all"
#include "../cpp2javalib/java/awt/all"

JavaTest::JavaTest(void)
{
}

JavaTest::~JavaTest(void)
{
}

void JavaTest::init()
{
}

void JavaTest::paint(Graphics* g)
{
	g->setColor(Color::BLUE);
	g->drawLine(100, 100, 100, 100);
	g->fillRect(100, 100, 100, 100);
}

void JavaTest::Test()
{
	System::out.println("> Throwable");
	System::out.println("> Exception");
	try
	{
		throw Exception("message");
	}
	catch (Exception& e)
	{
		System::out.println("s = " + e.getMessage());
		e.printStackTrace();
	}
	System::out.println("> InterruptedException");
	try
	{
		throw InterruptedException("message");
	}
	catch (InterruptedException& e)
	{
		System::out.println("s = " + e.getMessage());
		e.printStackTrace();
	}
	Thread::sleep(100);
	System::out.println("> String");
	String s = "abc123";
	System::out.println("s = " + s);
	System::out.println(String("s.length() = ") + s.length());
	System::out.println(String("s.charAt(2) = ") + s.charAt(2));
	System::out.println("s.substring(2) = " + s.substring(2));
	System::out.println("s.substring(2, 4) = " + s.substring(2, 4));
	System::out.println("> Integer");
	Integer i = 1;
	System::out.println("i = " + i);
	System::out.println("Integer::toHexString(100) = " + Integer::toHexString(100));
	System::out.println("> Math");
	System::out.println(String("Math::PI = ") + Math::PI);
	System::out.println(String("Math::sin(Math::PI / 2) = ") + Math::sin(Math::PI / 2));
	System::out.println(String("Math::cos(Math::PI / 2) = ") + Math::cos(Math::PI / 2));
	System::out.println(String("Math::tan(Math::PI / 4) = ") + Math::tan(Math::PI / 4));
	System::out.println(String("Math::sqrt(2) = ") + Math::sqrt(2));
	System::out.println(String("Math::pow(2, 10) = ") + Math::pow(2, 10));
	System::out.println("> Runnable");
	System::out.println("> Thread");
	Thread* thread = new Thread(this);
	thread->start();
	Thread::sleep(100);
	delete thread;
	System::out.println("JavaTest::Test(): end");
	System::out.println("> System");
	System::out.print("abc");
	System::out.print(123);
	System::out.println();
	System::out.println("abc");
	System::out.println(123);
	System::out.println("> URL");
	URL url = URL("http://www.yahoo.co.jp/");
	System::out.println("url = " + url);
	System::out.println("> Random");
	Random rand = Random();
	System::out.println(String("rand.nextInt() = ") + rand.nextInt());
	System::out.println(String("rand.nextDouble() = ") + rand.nextDouble());

}

void JavaTest::run()
{
	System::out.println("JavaTest::run(): end");
}
