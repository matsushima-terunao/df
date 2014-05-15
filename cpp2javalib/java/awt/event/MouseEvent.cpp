/**
 * @file
 *
 * $Id: MouseEvent.cpp,v 1.6 2007/11/30 22:42:27 matsushima Exp $
 *
 * MouseEvent.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/08/11 matsushima cpp2javalib
 * @version $Revision: 1.6 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: MouseEvent.cpp,v $
 * Revision 1.6  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.5  2007/05/10 22:29:47  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.4  2007/05/09 12:45:23  matsushima
 * no message
 *
 * Revision 1.3  2007/05/08 15:24:46  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.2  2007/04/23 17:06:33  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "MouseEvent"
#include "../Component"

/*------------------------------------------------------------*/

MouseEvent::MouseEvent(Component* source, int id, long when, int modifiers, int x, int y, int clickCount, bool popupTrigger, int button)
{
    this->source = source;
    this->id = id;
    this->when = when;
    this->modifiers = modifiers;
    this->x = x;
    this->y = y;
    this->clickCount = clickCount;
    this->popupTrigger = popupTrigger;
    this->button = button;
}

int MouseEvent::getX()
{
    return x;
}

int MouseEvent::getY()
{
    return y;
}

int MouseEvent::getModifiers()
{
    return modifiers;
}

void MouseEvent::consume()
{
}
