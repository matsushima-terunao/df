/*
 * $Id: JavaApplet.cpp,v 1.17 2008/03/12 16:30:47 matsushima Exp $
 */

/*J*
package commons;

import java/applet.Applet;
import java/awt.Graphics;
import java/awt.Image;
import java/awt.event.KeyEvent;
import java/awt.event.KeyListener;
import java/awt.event.MouseEvent;
import java/awt.event.MouseListener;
import java/awt.event.MouseMotionListener;
import java/util.Random;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/applet/Applet"
#include "../cpp2javalib/java/awt/Graphics"
#include "../cpp2javalib/java/awt/Rectangle"
#include "../cpp2javalib/java/awt/Image"
#include "../cpp2javalib/java/awt/event/KeyEvent"
#include "../cpp2javalib/java/awt/event/KeyListener"
#include "../cpp2javalib/java/awt/event/MouseEvent"
#include "../cpp2javalib/java/awt/event/MouseListener"
#include "../cpp2javalib/java/awt/event/MouseMotionListener"
#include "../cpp2javalib/java/util/Random"
#include "Perf.cpp"

#else // cpp

#define _IS_H_
#include "JavaApplet.cpp"
#include "Log.cpp"
#undef _IS_H_

#endif
/**/

/**
 * �A�v���b�g�̊�{�N���X�B
 * 
 * @since   1.0 2000 matsushima
 * @author  1.0 2000 matsushima
 * @version $Id: JavaApplet.cpp,v 1.17 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: JavaApplet.cpp,v $
 * Revision 1.17  2008/03/12 16:30:47  matsushima
 * Doxygen �Ή�
 *
 * Revision 1.16  2008/03/11 16:24:01  matsushima
 * RenderBuffer �}���`�X���b�h��
 *
 * Revision 1.13  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen �Ή�
 *
 * Revision 1.14  2008/03/06 15:39:49  matsushima
 * h/cpp ���ʉ�
 *
 * Revision 1.13  2008/03/04 17:21:01  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.12  2008/02/23 23:45:19  matsushima
 * ������
 *
 * Revision 1.11  2007/12/01 22:14:14  matsushima
 * �ēo�^
 *
 * Revision 1.10  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.9  2007/05/14 13:38:19  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.6  2007/05/10 22:29:39  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * ���v���[�X
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*
public class JavaApplet extends Applet
    implements Runnable, KeyListener, MouseListener, MouseMotionListener
{
    public static <T> void jdelete(T p) { }
    public static <T> T _R(T p) { return p; }
    public static String String() { return ""; }
    public static String String(String s) { return s; }
    public static String String(Object o) { return o.toString(); }
    public static double fmod(double d, double s) { return d % s; }
/*C*/
#ifdef _IS_H_
class JavaApplet : public Applet,
    Runnable, KeyListener, MouseListener, MouseMotionListener
{
/**/

    /**
     * 
     */
/*J*
    private static final long serialVersionUID = -25015330400013577L;

    protected Thread thread;
    protected Image imageOff;
    protected Graphics graphOff;
    protected int mouseX, mouseY;
    protected boolean mouseButton1, mouseButton2, mouseButton3;
    protected Random random;
    public Perf run_time;
    public Perf run_each_time;
    public long frame_cnt, rest_time, skip_cnt, wait_cnt;
/*C*/
protected:
    Thread* thread;
    Image* imageOff;
    Graphics* graphOff;
    int mouseX, mouseY;
    boolean mouseButton1, mouseButton2, mouseButton3;
    Random* random;
public:
    Perf* run_time;
    Perf* run_each_time;
    long frame_cnt, rest_time, skip_cnt, wait_cnt;
#endif
/**/

    /**
     * JavaApplet �I�u�W�F�N�g���\�z����B
     */
/*J*
    protected JavaApplet() {
/*C*/
#ifdef _IS_H_
public:
    JavaApplet();
#else
    JavaApplet::JavaApplet() {
/**/
        thread = null;
        imageOff = null;
        graphOff = null;
        mouseX = mouseY = 0;
        mouseButton1 = mouseButton2 = mouseButton3 = false;
        random = null;
        run_time = null;
        run_each_time = null;
        frame_cnt = rest_time = skip_cnt = wait_cnt = 0;
    }
/*C*/
#endif
/**/

    /**
     * JavaApplet �I�u�W�F�N�g��j������B
     */
/*C*/
#ifdef _IS_H_
public:
    virtual ~JavaApplet();
#else
    JavaApplet::~JavaApplet() {
        if (null != imageOff)
        {
            delete imageOff;
        }
        if (null != random)
        {
            delete random;
        }
        delete run_time;
        delete run_each_time;
    }
#endif
/**/

    /**
     * �A�b�v���b�g������������B
     */
/*J*
    @Override // Applet
    public void init() {
/*C*/
#ifdef _IS_H_
public:
    virtual void init();
#else
    void JavaApplet::init() {
/**/
        init(true);
    }
/*C*/
#endif
/**/

    /**
     * �A�v���b�g������������B
     * 
     * @param   useImageOff �I�t�X�N���[���C���[�W���쐬����ꍇ true�B
     */
/*J*
    protected void init(boolean useImageOff) {
/*C*/
#ifdef _IS_H_
protected:
    virtual void init(boolean useImageOff);
#else
    void JavaApplet::init(boolean useImageOff) {
/**/
Log::out("-> JavaApplet.init()");
Log::out(String("> freeMemory/totalMemory : ") + Runtime::getRuntime().freeMemory() + "/" + Runtime::getRuntime().totalMemory());
System::runFinalization();
Log::out("> System::runFinalization()");
Log::out(String("> freeMemory/totalMemory : ") + Runtime::getRuntime().freeMemory() + "/" + Runtime::getRuntime().totalMemory());
System::gc();
Log::out("> System::gc()");
Log::out(String("> freeMemory/totalMemory : ") + Runtime::getRuntime().freeMemory() + "/" + Runtime::getRuntime().totalMemory());
        // �I�t�X�N���[���C���[�W���쐬
        if (false != useImageOff)
        {
            imageOff = createImage(1000, 1000);
            graphOff = imageOff->getGraphics();
        }
        // �L�[��}�E�X
        addKeyListener(this);
        addMouseListener(this);
        addMouseMotionListener(this);
        requestFocus();
        mouseX = getBounds().width / 2;
        mouseY = getBounds().height / 2;
        // �c�[��
        random = new Random();
        // �p�t�H�[�}���X����
        run_time = new Perf();
        run_each_time = new Perf();
Log::out("<- JavaApplet.init()");
    }
/*C*/
#endif
/**/

    /**
     * �A�v���b�g��j������B
     */
/*J*
    @Override // Applet
    public void destroy() {
/*C*/
#ifdef _IS_H_
public:
    virtual void destroy();
#else
    void JavaApplet::destroy() {
/**/
Log::out("-> JavaApplet.destroy()");
        removeKeyListener(this);
        removeMouseListener(this);
        removeMouseMotionListener(this);
        Log::out("title     :" + Perf::getTitle());
		Log::out("run       :" + run_time->toString());
        Log::out("run_each  :" + run_each_time->toString());
Log::out("<- JavaApplet.destroy()");
    }
/*C*/
#endif
/**/

    /**
     * �A�v���b�g���J�n����B
     */
/*J*
    @Override // Applet
    public void start() {
/*C*/
#ifdef _IS_H_
public:
    virtual void start();
#else
    void JavaApplet::start() {
/**/
Log::out("-> JavaApplet.start()");
        if (null == thread)
        {
            thread = new Thread(this);
            thread->start();
            requestFocus();
Log::out("> Thread start");
        }
Log::out("<- JavaApplet.start()");
    }
/*C*/
#endif
/**/

    /**
     * �A�v���b�g���~����B
     */
/*J*
    @Override // Applet
    public void stop() {
/*C*/
#ifdef _IS_H_
public:
    virtual void stop();
#else
    void JavaApplet::stop() {
/**/
Log::out("-> JavaApplet.stop()");
        if (null != thread)
        {
            jdelete(thread);
            thread = null;
Log::out("> Thread stop");
        }
Log::out("<- JavaApplet.stop()");
    }
/*C*/
#endif
/**/

    /**
     * �Ɨ����Ď��s�����X���b�h�B
     */
/*J*
    //@Override // Runnable
    public void run() {
/*C*/
#ifdef _IS_H_
public:
    virtual void run();
#else
    void JavaApplet::run() {
/**/
Log::out("-> JavaApplet.run()");
run_time->start();
        try
        {
            while (null != thread)
            {
run_each_time->start();
                long res_span = run_each();
run_each_time->end();
run_time->end();
                long span = (res_span < 0) ? -res_span : res_span;
                long wait = 0;
                rest_time += run_time->span - span;
                if (rest_time < 0)
                {
                    // �E�F�C�g
                    ++ wait_cnt;
                    wait = - rest_time;
                }
                else if (rest_time >= span)
                {
                    if (res_span > 0) // �t���[���X�L�b�v���s��
                    {
                        // �t���[���X�L�b�v
                        skip_cnt += rest_time / span;
                        rest_time %= span;
                    }
                }
                if (wait > 0)
                {
                    Thread::sleep(wait);
                }
                else
                {
                    Thread::sleep(5);
                }
                ++ frame_cnt;
            }
        }
        catch (InterruptedException e)
        {
Log::out("JavaApplet.run() : > InterruptedException");
Log::out(e.getMessage());
        }
Log::out("<- JavaApplet.run()");
    }
/*C*/
#endif
/**/

    /**
     * {@link #run()} ����Ăяo�����X�̃A�N�V�����B
     * 
     * @return  ��Βl: �X�̃A�N�V�����ɗv���鎞��(ms)�B
     *          ����: �t���[���X�L�b�v�������I�ɍs���ꍇ +�B
     */
/*J*
    protected long run_each() {
/*C*/
#ifdef _IS_H_
protected:
    virtual long run_each();
#else
    long JavaApplet::run_each() {
/**/
        return 30;
    }
/*C*/
#endif
/**/

    /**
     * �A�v���b�g���ĕ`�悷��B
     * 
     * @param   g   �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     */
/*J*
    @Override // Applet
    public void update(Graphics g) {
/*C*/
#ifdef _IS_H_
public:
    virtual void update(Graphics* g);
#else
    void JavaApplet::update(Graphics* g) {
/**/
        paint(g);
    }
/*C*/
#endif
/**/

    /**
     * �A�v���b�g��`�悷��B
     * {@link #imageOff} �� null �łȂ��ꍇ�A{@link #imageOff} �̓��e���`�悳���B
     * 
     * @param   g   �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     */
/*J*
    @Override // Applet
    public void paint(Graphics g) {
/*C*/
#ifdef _IS_H_
public:
    virtual void paint(Graphics* _g);
#else
    void JavaApplet::paint(Graphics* _g) {
        JPARAM(Graphics, g);
/**/
        if (null != imageOff)
        {
            g.drawImage(imageOff, 0, 0, this);
        }
    }
/*C*/
#endif
/**/

    /**
     * �L�[�������ƌĂяo�����B
     * 
     * @param   e   �L�[�C�x���g�B
     */
/*J*
    //@Override // KeyListener
    public void keyPressed(KeyEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void keyPressed(KeyEvent* e);
#else
    void JavaApplet::keyPressed(KeyEvent* e) {
/**/
    }
/*C*/
#endif
/**/

    /**
     * �L�[�𗣂��ƌĂяo�����B
     * 
     * @param   e   �L�[�C�x���g�B
     */
/*J*
    //@Override // KeyListener
    public void keyReleased(KeyEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void keyReleased(KeyEvent* e);
#else
    void JavaApplet::keyReleased(KeyEvent* e) {
/**/
    }
/*C*/
#endif
/**/

    /**
     * �L�[���^�C�v����ƌĂяo�����B
     * 
     * @param   e   �L�[�C�x���g�B
     */
/*J*
    //@Override // KeyListener
    public void keyTyped(KeyEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void keyTyped(KeyEvent* e);
#else
    void JavaApplet::keyTyped(KeyEvent* e) {
/**/
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X�{�^�����N���b�N����ƌĂяo�����B
     * 
     * @param   e   �L�[�C�x���g�B
     */
/*J*
    //@Override // MouseListener
    public void mouseClicked(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouseClicked(MouseEvent* e);
#else
    void JavaApplet::mouseClicked(MouseEvent* e) {
/**/
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X������ƌĂяo�����B
     * 
     * @param   e   �}�E�X�C�x���g�B
     */
/*J*
    //@Override // MouseListener
    public void mouseEntered(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouseEntered(MouseEvent* e);
#else
    void JavaApplet::mouseEntered(MouseEvent* e) {
/**/
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X���o��ƌĂяo�����B
     * 
     * @param   e   �}�E�X�C�x���g�B
     */
/*J*
    //@Override // MouseListener
    public void mouseExited(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouseExited(MouseEvent* e);
#else
    void JavaApplet::mouseExited(MouseEvent* e) {
/**/
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X�{�^���������ƌĂяo�����B
     * 
     * @param   e   �}�E�X�C�x���g�B
     */
/*J*
    //@Override // MouseListener
    public void mousePressed(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mousePressed(MouseEvent* e);
#else
    void JavaApplet::mousePressed(MouseEvent* e) {
/**/
        mouse_common(e, true);
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X�{�^���𗣂��ƌĂяo�����B
     * 
     * @param   e   �}�E�X�C�x���g�B
     */
/*J*
    //@Override // MouseListener
    public void mouseReleased(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouseReleased(MouseEvent* e);
#else
    void JavaApplet::mouseReleased(MouseEvent* e) {
/**/
        mouse_common(e, false);
    }
/*C*/
#endif
/**/

    /**
     * {@link #mousePressed(MouseEvent)}, {@link #mouseReleased(MouseEvent)} �̋��ʏ����B
     * 
     * @param   e       �}�E�X�C�x���g�B
     * @param   value   �������Ƃ� true�B�������Ƃ� false�B
     */
/*J*
    private void mouse_common(MouseEvent e, boolean value) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouse_common(MouseEvent* e, boolean value);
#else
    void JavaApplet::mouse_common(MouseEvent* e, boolean value) {
/**/
        //�L�[�{�[�h�t�H�[�J�Xe.consume();
        int m = e->getModifiers();
        if (MouseEvent::BUTTON1_MASK == (MouseEvent::BUTTON1_MASK & m))
        {
            mouseButton1 = value;
        }
        if (MouseEvent::BUTTON2_MASK == (MouseEvent::BUTTON3_MASK & m))
        {
            mouseButton2 = value;
        }
        if (MouseEvent::BUTTON3_MASK == (MouseEvent::BUTTON3_MASK & m))
        {
            mouseButton3 = value;
        }
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X���h���b�O����ƌĂяo�����B
     * 
     * @param   e   �}�E�X�C�x���g�B
     */
/*J*
    //@Override // MouseMotionListener
    public void mouseDragged(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouseDragged(MouseEvent* e);
#else
    void JavaApplet::mouseDragged(MouseEvent* e) {
/**/
        e->consume();
        mouseX = e->getX();
        mouseY = e->getY();
    }
/*C*/
#endif
/**/

    /**
     * �}�E�X���ړ�����ƌĂяo�����B
     * 
     * @param   e   �}�E�X�C�x���g�B
     */
/*J*
    //@Override // MouseMotionListener
    public void mouseMoved(MouseEvent e) {
/*C*/
#ifdef _IS_H_
public:
    virtual void mouseMoved(MouseEvent* e);
#else
    void JavaApplet::mouseMoved(MouseEvent* e) {
/**/
        e->consume();
        mouseX = e->getX();
        mouseY = e->getY();
    }
/*C*/
#endif
/**/

    /**
     * �C���[�W���X�V���ꂽ�Ƃ��ɍĕ`�悷��B
     * 
     * @param   image       �\�������C���[�W�B
     * @param   infoflags   �t���O�B
     * @param   x           x ���W�B
     * @param   y           y ���W�B
     * @param   w           ���B
     * @param   h           �����B
     * @param   update_rate �ĕ`�悷��Ԋu�B
     */
/*J*
    public boolean imageUpdate(Image image, int infoflags, int x, int y, int w, int h, int update_rate) {
/*C*/
#ifdef _IS_H_
public:
    virtual boolean imageUpdate(Image* image, int infoflags, int x, int y, int w, int h, int update_rate);
#else
    boolean JavaApplet::imageUpdate(Image* image, int infoflags, int x, int y, int w, int h, int update_rate) {
/**/
        return imageUpdate(image, infoflags, x, y, w, h, update_rate);
    }
/*C*/
#endif
/**/

    /**
     * �C���[�W���X�V���ꂽ�Ƃ��ɍĕ`�悷��B
     * 
     * @param   image       �\�������C���[�W�B
     * @param   infoflags   �t���O�B
     * @param   x           x ���W�B
     * @param   y           y ���W�B
     * @param   w           ���B
     * @param   update_rate �ĕ`�悷��Ԋu�B
     * @param   logout1     ���O�o�� 1�B
     * @param   logout2     ���O�o�� 2�B
     */
/*J*
    public boolean imageUpdate(Image image, int infoflags, int x, int y, int w, int h, int update_rate, boolean logout1, boolean logout2) {
/*C*/
#ifdef _IS_H_
public:
    virtual boolean imageUpdate(Image* image, int infoflags, int x, int y, int w, int h, int update_rate, boolean logout1, boolean logout2);
#else
    boolean JavaApplet::imageUpdate(Image* image, int infoflags, int x, int y, int w, int h, int update_rate, boolean logout1, boolean logout2) {
/**/
    if (false != logout1)
    {
Log::out("infoflags = 0x" + Integer::toHexString(infoflags)
+ ", checkImage() = 0x" + Integer::toHexString(checkImage(image, this))
+ ", xywh = (" + x + "," + y + "," + w + "," + h + ")");
    }
    if (false != logout2)
    {
String s = "< ";
s += "WIDTH(0x01)=" + Integer::toHexString(WIDTH);
s += ",HEIGHT(0x02)=" + Integer::toHexString(HEIGHT);
s += ",PROPERTIES(0x04)=" + Integer::toHexString(PROPERTIES);
s += ",SOMEBITS(0x08)=" + Integer::toHexString(SOMEBITS);
s += ",FRAMEBITS(0x10)=" + Integer::toHexString(FRAMEBITS);
s += ",ALLBITS(0x20)=" + Integer::toHexString(ALLBITS);
s += ",ERROR(0x40)=" + Integer::toHexString(ERROR);
s += ",ABORT(0x80)=" + Integer::toHexString(ABORT);
Log::out(s);
    }
        int rate = -1;
        if (0 != (infoflags & (ALLBITS | FRAMEBITS)))
        {
            rate = 0;
        }
        else
        if (0 != (infoflags & SOMEBITS))
        {
            rate = update_rate;
        }
        if (rate >= 0)
        {
            if (false != logout1)
            {
Log::out("> repaint");
            }
            repaint(rate, x, y, w, h);
        }
        boolean result = (0 != (infoflags & (ALLBITS | ABORT))) ? false : true;
        if (false != logout1)
        {
Log::out(String("> result = ") + result + ", rate = " + rate);
        }
        return result;
    }
/*C*/
#endif
/**/

    /**
     * ���̗�����Ԃ��B
     * 
     * @param   first   �J�n�l�B
     * @param   count   �͈́B
     * @param   ���̗����B
     */
/*J*
    public int rand(int first, int count) {
/*C*/
#ifdef _IS_H_
public:
    virtual int rand(int first, int count);
#else
    int JavaApplet::rand(int first, int count) {
        JMEMBER(Random, random);
/**/
        int rand = random.nextInt();
        rand = (rand < 0) ? (- rand) : rand;
        rand = rand % count + first;
        return rand;
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/
