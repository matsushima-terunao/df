/*
 * $Id: JavaDF2Models.java,v 1.12 2008/03/06 16:43:59 matsushima Exp $
 */

/*J*/
package javadf2;

import java.util.ArrayList;
import java.util.Random;
import java3d.Java3D;
import java3d.Java3DModel;
import java3d.Java3DModelGround;
import java3d.Java3DModelSphere;
import java3d.Java3DWorld;

import javarender.JavaRender;
import javarender.JavaRenderTexture;

import commons.JavaObject;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
//#include "../cpp2javalib/java.util.ArrayList"
#include "../cpp2javalib/java.util.Random"
#include "Java3D.cpp"
#include "Java3DModel.cpp"
#include "Java3DModelGround.cpp"
#include "Java3DModelSphere.cpp"
#include "Java3DWorld.cpp"
#include <list>

class JavaDF2ModelsStatic;
extern JavaDF2ModelsStatic _JavaDF2ModelsStatic;

#else // cpp

#define _IS_H_
#include "JavaDF2Models.cpp"
#include "JavaDF2Fractal.cpp"
#undef _IS_H_

JavaDF2ModelsStatic _JavaDF2ModelsStatic;

#endif
/**/

/**
 * JavaDF2Models
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: JavaDF2Models.java,v 1.12 2008/03/06 16:43:59 matsushima Exp $
 * 
 * $Log: JavaDF2Models.java,v $
 * Revision 1.12  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.26  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.25  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.24  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.23  2008/02/24 05:52:06  matsushima
 * JavaRenderInterface -> JavaRender
 * JavaRender -> JavaRenderBuffer
 *
 * Revision 1.22  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.21  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.20  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRender を Java3D から分離
 *
 * Revision 1.14  2007/05/16 20:57:58  matsushima
 * テクスチャマッピング
 *
 * Revision 1.13  2007/05/16 18:14:02  matsushima
 * JavaDF2ModelSphere, JavaDF2ModelGround -> JavaDF2Models に統合
 *
 * Revision 1.9  2007/05/14 13:38:20  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.7  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.5  2007/05/08 22:13:37  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.4  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*/
public class JavaDF2Models extends JavaObject
{
/*C*
#ifdef _IS_H_
class JavaDF2ModelsStatic
{
/**/
/*J*/
    public static final int
/*C*
public:
    enum {
/**/
        RENDER_DEFAULT  = Java3DModel.RENDER_DEFAULT,
        EOD             = Java3DModel.EOD,

        ENEMY_CNT       = 1000,
        FRAGMENT_CNT    = 1000,

        KIND_BG_TEST    = 100,
        KIND_BG_GROUND  = 101,
        KIND_BG_EARTH   = 102,

        KIND_ENEMY1     = 10,
        KIND_ROCK1      = 11,

        KIND_FRAGMENT1  = 201,
        KIND_FRAGMENT2  = 202
/*J*/
    ;
/*C*
    };
};

class JavaDF2Models : public JBase<JavaDF2Models>, public JavaDF2ModelsStatic
{
public:
    class Sphere;
    class Ground;
/**/

/*J*/
    private Java3DWorld world;
    private ArrayList<Java3DModel> models;
    private Java3DModel[] enemies;
    private Java3DModel[] fragments;
    private Java3DModel model_mark;
    private Java3DModel model_shot;
    private Ground model_bg_ground;
    public Sphere model_bg_earth;
    public Java3DModel model_bg_test;
    public Java3DModelSphere[] rocks;
    private Random random;
    private int mark_x, mark_y;
    public int e_cnt, f1_cnt, f2_cnt;
/*C*
public://private:
    Java3DWorld* world;
    //ArrayList<Java3DModel> models;
    std::list<Java3DModel*> models;
    Java3DModel** enemies;
    Java3DModel** fragments;
    Java3DModel* model_mark;
    Java3DModel* model_shot;
    Ground* model_bg_ground;
    Sphere* model_bg_earth;
    Java3DModel* model_bg_test;
    Java3DModelSphere** rocks;
    Random* random;
    int mark_x, mark_y;
public:
    int e_cnt, f1_cnt, f2_cnt;
/**/

/*J*/
    public JavaDF2Models(Java3DWorld world, Java3D parent) {
/*C*
#endif
#ifdef _IS_H_
public:
    JavaDF2Models(Java3DWorld* world, Java3D* parent);
#else
    JavaDF2Models::JavaDF2Models(Java3DWorld* world, Java3D* parent) {
#define this (*this)
#define final static
        JSTATIC(Java3D);
        JSTATIC(JavaDF2Fractal);
/**/
        this.world = world;
        /*J*/this.models = new ArrayList<Java3DModel>();/**/
        this.mark_x = this.mark_y = 0;
        Java3DModel/*C** /**/ model;
        int mode, mask, i;

        // Mark
        mode = Java3D.APPEND_BACK;
        mask = Java3D.APPEND_MASK;
        final int color_mark = 0xff00ff00;
        final int verts_mark[] =
        {
            color_mark,-16,-16,0, color_mark,-16,- 8,0, color_mark,- 8,-16,0,
            color_mark, 16,-16,0, color_mark,  8,-16,0, color_mark, 16,- 8,0,
            color_mark,-16, 16,0, color_mark,- 8, 16,0, color_mark,-16,  8,0,
            color_mark, 16, 16,0, color_mark, 16,  8,0, color_mark,  8, 16,0,
            EOD
        };
        final int polys_mark[] = { 0,1,2,EOD, 3,4,5,EOD, 6,7,8,EOD, 9,10,11,EOD, EOD };
        final int lines_mark[] = { 0,1,2,0,EOD, 3,4,5,3,EOD, 6,7,8,6,EOD, 9,10,11,9,EOD, EOD };
        model = new Java3DModel(world, null);
        _R(model).init(Java3DModel/*J*/./*C*::/**/KIND_USED, 0, 0, (Java3D.RENDER_DEFAULT & ~mask) | mode,
            verts_mark, polys_mark, lines_mark);
        model_mark = model;
        append(model);

        // Shot
        final int color_shot = 0xff0000ff;
        final int verts_shot[] =
        {
            color_shot,-10,0,0, color_shot,-2,1,0, color_shot,-1,1,0,
            color_shot, 10,0,0, color_shot, 1,1,0, color_shot, 2,1,0,
            EOD
        };
        final int polys_shot[] = { 0,1,2,EOD, 3,4,5,EOD, EOD };
        final int lines_shot[] = { 0,1,2,0,EOD, 3,4,5,3,EOD, EOD };
        model = new Java3DModel(world, null);
        _R(model).init(Java3DModel/*J*/./*C*::/**/KIND_USED, 0, 0, (Java3D.RENDER_DEFAULT & ~mask) | mode,
            verts_shot, polys_shot, lines_shot);
        model_shot = model;
        append(model);

        // Backgrounds
        model_bg_ground = null;
        model_bg_earth = null;
        model_bg_test = null;

        // Enemies
        enemies = new Java3DModel/*C** /**/[ENEMY_CNT];
        for (i = 0; i < ENEMY_CNT; ++ i)
        {
            enemies[i] = new Java3DModel(world, parent);
        }
        append(enemies, ENEMY_CNT);

        // KIND_ROCK1
        final int color_tbl[] =
        {
  //            0, 128, 128, 128, // s
    //        256,  64,  64,  64, // w
            0,  64,  64,  64, // w
            128,  32,  32,  32, // w
              256, 128, 128, 128, // s
        };
        int vert_colors = 256;
        int/*J*/[]/*C** /**/ vert_color_tbl = Java3DModel/*J*/./*C*::/**/create_color_table(vert_colors, color_tbl);
        rocks = new Java3DModelSphere/*C** /**/[4];
        for (i = 0; i < 4; ++ i)
        {
            rocks[i] = new Java3DModelSphere(world, parent);
            int width = 30 + i * 30, vert_height = width / 2;
            int unit = 8, frac_height = Sphere/*J*/./*C*::/**/INIT_GROUND_HEIGHT;
            int/*J*/[]/*C** /**/ frac = JavaDF2Fractal.create(unit, 1.8, frac_height - 1);
            _R(rocks[i]).init(0, 0, 0, Java3D.RENDER_DEFAULT,
                width, width * 3 / 4, unit, 2,
                frac, vert_color_tbl, frac_height, vert_colors, vert_height,
                4, 4, 2 + i+1);
            Java3DModel/*J*/./*C*::/**/index_to_color( // 色インデックスの配列を ARGB に変換する
                frac, frac, (1 << unit) * (1 << unit), vert_color_tbl, vert_colors, frac_height);
        }
        jdelete(vert_color_tbl);

        // Fragments
        fragments = new Java3DModel/*C** /**/[FRAGMENT_CNT];
        for (i = 0; i < FRAGMENT_CNT; ++ i)
        {
            fragments[i] = new Java3DModel(world, parent);
            int vert_cnt = 5;
            _R(fragments[i]).verts = new int[4 * vert_cnt + 1];
            _R(fragments[i]).polys = new int[2 * (vert_cnt + 1) + 1];
        }
        append(fragments, FRAGMENT_CNT);

        //
        random = new Random();
    }

/*C*
#endif
#ifdef _IS_H_
public:
    virtual ~JavaDF2Models();
#else
    JavaDF2Models::~JavaDF2Models() {
        int i;
        for (i = 0; i < 4; ++ i)
        {
            rocks[i]->destroy();
            delete rocks[i];
        }
        delete[] rocks;
        for (i = 0; i < FRAGMENT_CNT; ++ i)
        {
            delete[] fragments[i]->verts;
            delete[] fragments[i]->polys;
        }
        std::list<Java3DModel*>::iterator it;
        for (it = models.begin(); it != models.end(); ++ it)
        {
            //(*it)->destroy(); not delete member
            delete (*it);
        }
        delete[] enemies;
        delete[] fragments;
        delete random;
    }
/**/

/*J*/
    public void translate(int x, int y) {
/*C*
#endif
#ifdef _IS_H_
public:
    void translate(int x, int y);
#else
    void JavaDF2Models::translate(int x, int y) {
        JMEMBER(Java3DWorld, world);
        JMEMBER(Java3DModel, model_mark);
        JMEMBER(Java3DModel, model_shot);
        JSTATIC(Java3DModel);
/**/
        // Mark
        mark_x = x;
        mark_y = y;
        model_mark.setPosition2D(x - world.viewport_x, y - world.viewport_y, -20, 1.0);
        // Shot
        model_shot.setPosition2D(0, 0, -100, 1.0);
        //final int color_shot = 0xff0000ff;
        int x0 = x - world.viewport_x;
        int x1 = world.viewport_x;
        int x2 = (int)(x1 * 1.2);
        int y0 = y - world.viewport_y;
        int y1 = world.viewport_height - world.viewport_y;
        Java3DModel.set_vert_xyz(model_shot.verts, 0, x0 - 10, y0, 0);
        Java3DModel.set_vert_xyz(model_shot.verts, 1, -x2    , y1, 0);
        Java3DModel.set_vert_xyz(model_shot.verts, 2, -x1    , y1, 0);
        Java3DModel.set_vert_xyz(model_shot.verts, 3, x0 + 10, y0, 0);
        Java3DModel.set_vert_xyz(model_shot.verts, 4, x1     , y1, 0);
        Java3DModel.set_vert_xyz(model_shot.verts, 5, x2     , y1, 0);
        // Other
/*J*/
        for (Java3DModel model: models) {
/*C*
        std::list<class Java3DModel*>::iterator it;
        for (it = models.begin(); it != models.end(); ++ it) {
            class Java3DModel& model = **it;
/**/
            if (false != model.used())
            {
                model.translate();
            }
        }
    }

/*J*/
    public void transform() {
/*C*
#endif
#ifdef _IS_H_
public:
    void transform();
#else
    void JavaDF2Models::transform() {
        JMEMBER(Java3DWorld, world);
/**/
        e_cnt = f1_cnt = f2_cnt = 0;
/*J*/
        for (Java3DModel model: models) {
/*C*
        std::list<class Java3DModel*>::iterator it;
        for (it = models.begin(); it != models.end(); ++ it) {
            class Java3DModel& model = **it;
/**/
            if (false != model.used())
            {
                model.transform();
                if (model.trcount > 0)
                {
                    boolean in_clip = ((model.trmx22 >= 0) && (model.trmx21 <= world.viewport_width)
                                    && (model.trmy22 >= 0) && (model.trmy21 <= world.viewport_height));
                    switch (model.kind)
                    {
                    case KIND_ROCK1:
                        {
                            ++ e_cnt;
                            if ((mark_x >= model.trmx21) && (mark_x <= model.trmx22)
                             && (mark_y >= model.trmy21) && (mark_y <= model.trmy22))
                            {
                                ++ model.damage;
                                if (model.damage >= model.damage_max)
                                {
                                    init_fragment(model, KIND_FRAGMENT1);
                                }
                            }
                            break;
                        }
                    case KIND_FRAGMENT1:
                        {
                            ++ f1_cnt;
                            if (false == in_clip)
                            {
                                model.unuse();
                            }
                            else
                            if (model.count < 15) // count < 15: 回転しない
                            {
                                model.ma -= model.va;
                                model.mb -= model.vb;
                            }
                            else
                            if (model.count == model.count_max - 1)
                            {
                                init_fragment(model, KIND_FRAGMENT2);
                            }
                            break;
                        }
                    case KIND_FRAGMENT2:
                        {
                            ++ f2_cnt;
                            if (false == in_clip)
                            {
                                model.unuse();
                            }
                            break;
                        }
                    }
                    if (false != model.used())
                    {
                        model.append();
                    }
                }
            }
        }
    }

/*J*/
    private void append(Java3DModel model) {
        models.add(model);
/*C*
#endif
#ifdef _IS_H_
private:
    void append(Java3DModel* model);
#else
    void JavaDF2Models::append(Java3DModel* model) {
        models.push_back(model);
/**/
    }

/*J*/
    private void append(Java3DModel[] models, int model_cnt) {
/*C*
#endif
#ifdef _IS_H_
private:
    void append(Java3DModel** models, int model_cnt);
#else
    void JavaDF2Models::append(Java3DModel** models, int model_cnt) {
/**/
        int i;
        for (i = 0; i < model_cnt; ++ i)
        {
            /*J*/this.models.add(models[i]);/**/
            /*C*this.models.push_back(models[i]);/**/
        }
    }

/*J*/
    int rand(int count) {
/*C*
#endif
#ifdef _IS_H_
    int rand(int count);
#else
    int JavaDF2Models::rand(int count) {
        JMEMBER(Random, random);
/**/
        return random.nextInt() % count;
    }

/*J*/
    int rand(int first, int count) {
/*C*
#endif
#ifdef _IS_H_
    int rand(int first, int count);
#else
    int JavaDF2Models::rand(int first, int count) {
        JMEMBER(Random, random);
/**/
        int r = random.nextInt() % count;
        r = (r < 0) ? -r : r;
        return r % count + first;
    }

    /*------------------------------------------------------------*/
    /*
     * Enemies
     */

/*J*/
    public void init_enemy(int kind) {
/*C*
#endif
#ifdef _IS_H_
public:
    void init_enemy(int kind);
#else
    void JavaDF2Models::init_enemy(int kind) {
        JMEMBER(Java3DWorld, world);
        JTYPEDEF_P(Java3DModel);
        JSTATIC(Java3D);
/**/
        Java3DModel model = null;
        int i;
        for (i = 0; i < ENEMY_CNT; ++ i)
        {
            if (false == _R(enemies[i]).used())
            {
                model = enemies[i];
                break;
            }
        }
        if (null == model)
        {
            return;
        }
        switch (kind)
        {
        case KIND_ENEMY1:
            {
                final int test_verts[] = { 0xff00ff00,0,-40,-40, 0xff00ff00,-40,40,-40, 0xff00ff00,40,40,-40, EOD };
                final int test_polys[] = { 0,1,2,EOD, EOD };
                final int test_lines[] = { 0,1,2,0,EOD, EOD };
                int r = world.clip_z;
                int a = rand(Java3D.ANGLE_MAX / 16) - world.ma;
                int b = rand(Java3D.ANGLE_MAX / 64);
                int r_sin_a = r * Java3D.sin(a) / Java3D.TRIFUNC_MAX;
                int r_sin_b = r * Java3D.sin(b) / Java3D.TRIFUNC_MAX;
                int r_cos_ab = r * Java3D.cos(a) / Java3D.TRIFUNC_MAX * Java3D.cos(b) / Java3D.TRIFUNC_MAX;
                int count = r / 16;
                _R(model).init(kind, count, 30, RENDER_DEFAULT, test_verts, test_polys, test_lines);
                _R(model).setPosition(
                    world.ma, 0, world.mx + r_sin_a, world.my + r_sin_b, world.mz + r_cos_ab,
                    0, 0, -r_sin_a / Java3D.TRIFUNC_MAX, -r_sin_b / Java3D.TRIFUNC_MAX, -r_cos_ab / Java3D.TRIFUNC_MAX);
                break;
            }
        case KIND_ROCK1:
            {
                int r = world.clip_z;
                int a = rand(Java3D.ANGLE_MAX / 16) - world.ma;
                int b = rand(Java3D.ANGLE_MAX / 64);
                int r_sin_a = r * Java3D.sin(a) / Java3D.TRIFUNC_MAX;
                int r_sin_b = r * Java3D.sin(b) / Java3D.TRIFUNC_MAX;
                int r_cos_ab = r * Java3D.cos(a) / Java3D.TRIFUNC_MAX * Java3D.cos(b) / Java3D.TRIFUNC_MAX;
                int count = r / (16-4);
                i = rand(0, 4);
                _R(model).init(kind, count, 30, RENDER_DEFAULT, _R(rocks[i]).verts, _R(rocks[i]).polys, null);
                _R(model).init_texture(_R(rocks[i]).texture);
                _R(model).setPosition(
                    rand(Java3D.ANGLE_MAX), rand(Java3D.ANGLE_MAX) / 8+ Java3D.ANGLE_MAX / 4, world.mx + r_sin_a, world.my + r_sin_b, world.mz + r_cos_ab,
                    rand(Java3D.ANGLE_MAX / 256), rand(Java3D.ANGLE_MAX / 1024), 0, 0, 0);
                _R(model).mc = 0;
                break;
            }
        }
    }

    /*------------------------------------------------------------*/
    /*
     * Fragments
     */

/*J*/
    public void init_fragment(Java3DModel model, int kind) {}
    public void init_fragment2(Java3DModel model, int kind) {
/*C*
#endif
#ifdef _IS_H_
public: void init_fragment2(Java3DModel* model, int kind);
public:
    void init_fragment(Java3DModel* model, int kind);
#else
    void JavaDF2Models::init_fragment(Java3DModel* _model, int kind) {}
    void JavaDF2Models::init_fragment2(Java3DModel* _model, int kind) {
        JMEMBER(Java3DWorld, world);
        JPARAM(Java3DModel, model);
        JSTATIC(Java3D);
        JSTATIC(Java3DModel);
/**/
        int vert_cnt=0, vert_mod=0, vert_add=0, v_ang = 64, v_crd = 4;
        if (KIND_FRAGMENT2 == kind)
        {
            vert_cnt = 2;
            vert_mod = Java3DModel.get_vert_cnt(model.polys, 0);
            vert_add = 1;
            v_ang = 16;
            v_crd = 2;
        }
        int cos_a = Java3DModel.cos(world.ma);
        int sin_a = Java3DModel.sin(world.ma);
        int cos_b = Java3DModel.cos(world.mb + world.mb0);
        int sin_b = Java3DModel.sin(world.mb + world.mb0);
        // Temporary transform vertexes
        model.render_mode = Java3D.APPEND_NONE;
        model.transform();
        int i, s, d;
        for (i = s = 0; (i < FRAGMENT_CNT) && (EOD != model.polys[s]); ++ i)
        {
            /*J*/Java3DModel frag = fragments[i];/**/
            /*C*class Java3DModel& frag = *fragments[i];/**/
            if (false == frag.used())
            {
                if (KIND_FRAGMENT1 == kind)
                {
                    vert_cnt = Java3DModel.get_vert_cnt(model.polys, s);
                    vert_mod = s + vert_cnt;
                    vert_add = vert_cnt + 1;
                }
                int count = 10;
                if (KIND_FRAGMENT1 == kind)
                {
                    count = rand(12);
                    count = (11 == count) ? 300 : count * count / 3 + 30;
                }
                frag.init(kind, count, 0, Java3D.RENDER_DEFAULT, frag.verts, frag.polys, null);
                int vx = 0, vy = 0, vz = 0;
                for (d = 0; d < vert_cnt; ++ d)
                {
                    int p = model.polys[(s + d) % vert_mod];
                    frag.verts[d * 4 + 0] = model.verts[p * 4 + 0];
                    JavaRender/*J*/./*C*::/**/Vertex trvert = world.get_trvert(p);
                    frag.verts[d * 4 + 1] = trvert.x3;
                    frag.verts[d * 4 + 2] = trvert.y3;
                    frag.verts[d * 4 + 3] = trvert.z3;
                    frag.polys[d] = d;
                    frag.polys[(vert_cnt + 1) * 2 - 2 - d] = d;
                    vx += trvert.x3;
                    vy += trvert.y3;
                    vz += trvert.z3;
                }
                frag.verts[d * 4 + 0] = EOD;
                frag.polys[d] = EOD;
                if (KIND_FRAGMENT2 == kind)
                {
                    frag.polys[d + 1] = EOD;
                }
                else
                {
                    frag.polys[(d + 1) * 2 + 1 - 2] = EOD;
                    frag.polys[(d + 1) * 2 + 1 - 1] = EOD;
                }
                vx /= vert_cnt;
                vy /= vert_cnt;
                vz /= vert_cnt;
                for (d = 0; d < vert_cnt; ++ d)
                {
                    frag.verts[d * 4 + 1] = (frag.verts[d * 4 + 1] - vx) >> 16;
                    frag.verts[d * 4 + 2] = (frag.verts[d * 4 + 2] - vy) >> 16;
                    frag.verts[d * 4 + 3] = (frag.verts[d * 4 + 3] - vz) >> 16;
                }
                int z11 = ((vz >> 8) * cos_a + (vx >> 8) * sin_a) >> 8;
                int x11 = ((vx >> 8) * cos_a - (vz >> 8) * sin_a) >> 8;
                int y11 = ((vy >> 8) * 256) >> 8;
                int z12 = z11 * cos_b + y11 * sin_b;
                int y12 = y11 * cos_b - z11 * sin_b;
                int x12 = x11 * 256;
                frag.setPosition(
                    world.ma,
                    world.mb + world.mb0,
                    model.mx + (x12 >> 16),
                    model.my + (y12 >> 16),
                    model.mz + (z12 >> 16),
                    rand(Java3D.ANGLE_MAX / v_ang),
                    rand(Java3D.ANGLE_MAX / 128),
                    model.vx + (x12 >> (v_crd + 16)) + rand(2),
                    model.vy + (y12 >> (v_crd + 16)) + rand(2),
                    model.vz + (z12 >> (v_crd + 16)) + rand(2));
                frag.ma -= frag.va; // count < 15: 回転しない
                frag.mb -= frag.vb;
                frag.lx = vx >> 16;
                frag.ly = vy >> 16;
                frag.lz = vz >> 16;
                s += vert_add;
            }
        }
        model.unuse();
    }

    /*------------------------------------------------------------*/
    /*
     * Backgrounds
     */

/*J*/
    public void init_background(int kind) {
/*C*
#endif
#ifdef _IS_H_
public:
    void init_background(int kind);
#else
    void JavaDF2Models::init_background(int kind) {
        JMEMBER(Java3DWorld, world);
        JSTATIC(Java3D);
        JSTATIC(Java3DModel);
/**/
        switch (kind)
        {
        case KIND_BG_TEST:
            {
                int C_SHOT = 0x7f0000ff;
                int vx = 100, vz = 0;
                //final int verts[] = { C_SHOT|0xff000000,0,-vx,vz, C_SHOT|0x3f000000,-vx,vx,vz, C_SHOT|0x00000000,vx,vx,vz, EOD };
                //final int polys[] = { 0,1,2, Java3D.EOP, EOD };
                //final int lines[] = { 0,1,2,0, Java3D.EOP, EOD };
                final int verts[] = { C_SHOT,-vx,-vx,-vx+vz, C_SHOT,-vx,vx,-vx+vz, C_SHOT,vx,vx,-vx+vz, C_SHOT,vx,-vx,-vx+vz,
                                       C_SHOT,-vx,-vx, vx+vz, C_SHOT,-vx,vx, vx+vz, C_SHOT,vx,vx, vx+vz, C_SHOT,vx,-vx, vx+vz, EOD };
                final int polys[] = { 0,1,2,3,EOD, 3,2,6,7,EOD, 7,6,5,4,EOD, 4,5,1,0,EOD, 0,3,7,4,EOD, 1,5,6,2,EOD, EOD };
                final int lines[] = { 0,1,2,0, EOD, EOD };
                model_bg_test = new /*C*class /**/Java3DModel(world, world);
                //int mask = 0;//Java3D.RENDER_SHADING_MASK;
                //int mode = 0;//Java3D.RENDER_SHADING_SOLID;
                _R(model_bg_test).init(Java3DModel.KIND_USED, 0, 0,
                    Java3D.RENDER_DEFAULT,//(Java3D.RENDER_DEFAULT & ~mask) | mode,
                    verts, polys, lines);
                _R(model_bg_test).mz += 1000;
            }
        case KIND_BG_GROUND:
            {
                world.setViewport(world.viewport_width / 2, world.viewport_height * 6 / 5);
                int angle = 75;//75;//120;
                world.setPerspective(angle, world.max_z, world.clip_z, (int)(world.max_z * 1.0), - (int)(angle * Java3D.ANGLE_MAX / 360 / 2.0));
                final int color_tbl[] =
                {
                        0, 255, 255, 255, // s
                       20, 128, 128, 128, // m
                       40, 100,  30,  10, // m
                      160,  20, 150,   0, // g
                      190, 160,  80,  60, // b
                      220,   0,   0, 240, // w
                      256,   0,   0,   0, // w
                };
                int unit_max = 8;
                model_bg_ground = new Ground(world, world, unit_max, color_tbl);
                append(model_bg_ground);
                break;
            }
        case KIND_BG_EARTH:
            {
                final int color_tbl[] =
                {
                        0, 255, 255, 254, // s
                       20/2, 128, 128, 128, // m
                       40/2, 100,  30,  10, // m
                    //  160/2,  20, 150,   0, // g
                    //  190/2, 160,  80,  60, // b
                      160/2,  20, 120,   0, // g
                      190/2, 160,  100,  80, // b
                      220/2,   0,   0, 240, // w
                      256,   0,   0,   0, // w
                };
                int unit_max = 8;
                int rate2 = 2;
                int frac_unit = 9;
                int frac_unit_mul = 3;
                model_bg_earth = new Sphere(world, null, unit_max, color_tbl, rate2, frac_unit, frac_unit_mul);
int width = 3000;
_R(model_bg_earth).mz = world.clip_z/1;
_R(model_bg_earth).mb = Java3D.ANGLE_MAX / 6;
_R(model_bg_earth).lx = width;
_R(model_bg_earth).ly = width;
_R(model_bg_earth).lz = -width * 2;
                append(model_bg_earth);
                break;
            }
        }
    }

/*J*/
    public void set_background_unit(int unit) {
/*C*
#endif
#ifdef _IS_H_
public:
    void set_background_unit(int unit);
#else
    void JavaDF2Models::set_background_unit(int unit) {
        JMEMBER(Ground, model_bg_ground);
        JMEMBER(Sphere, model_bg_earth);
/**/
        if (null != model_bg_ground)
        {
            model_bg_ground.change_model(unit);
        }
        if (null != model_bg_earth)
        {
            model_bg_earth.change_model(unit);
        }
    }

/*J*/
    public int get_background_unit() {
/*C*
#endif
#ifdef _IS_H_
public:
    int get_background_unit();
#else
    int JavaDF2Models::get_background_unit() {
        JMEMBER(Ground, model_bg_ground);
        JMEMBER(Sphere, model_bg_earth);
/**/
        if (null != model_bg_ground)
        {
            return model_bg_ground.unit;
        }
        if (null != model_bg_earth)
        {
            return model_bg_earth.unit;
        }
        return 4;
    }

/*J*/
    public class Ground extends Java3DModelGround
    {
/*C*
#endif
#ifdef _IS_H_
public:
    class Ground : public Java3DModelGround
    {
/**/
/*J*/
        public static final int
/*C*
    public:
        enum {
/**/
            UNIT_MIN    = 4,
            INIT_GROUND_HEIGHT = 65536
/*J*/
        ;
/*C*
        };
/**/
/*J*/
//        public int unit;
//        private int unit_min, unit_max;
        private Java3DModelGround[] models;
/*C*
    public:
        //int unit;
    private:
        //int unit_min, unit_max;
        Java3DModelGround** models;
/**/

/*J*/
        public Ground(Java3DWorld world, Java3D parent, int unit_max, final int[] color_tbl) {
            super(world, parent);
/*C*
#endif
#ifdef _IS_H_
    public:
        Ground(Java3DWorld* world, Java3D* parent, int unit_max, const int* color_tbl);
#else
        JavaDF2Models::Ground::Ground(Java3DWorld* _world, Java3D* parent, int unit_max, const int* color_tbl)
            : Java3DModelGround(_world, parent) {
#define this (*this)
            JPARAM(Java3DWorld, world);
            JSTATIC(Java3D);
            JSTATIC(JavaDF2Fractal);
/**/
            int width = 1 << unit_max;
            int mul = 4;
            int height = 256 * 2;
            int/*J*/[]/*C** /**/ vert_colors = create_color_table(height, color_tbl);
            int/*J*/[]/*C** /**/ frac = JavaDF2Fractal.create(unit_max, 0.8, INIT_GROUND_HEIGHT - 1);
            int/*J*/[]/*C** /**/ frac2 = index_to_color(null, frac, width * width, vert_colors, height, INIT_GROUND_HEIGHT);
            int/*J*/[]/*C** /**/ frac3 = zoom_texture(frac2, width, width, mul, mul);
            jdelete(frac2);
            init(world.max_z * 2, height, INIT_GROUND_HEIGHT, -1, unit_max, Java3D.RENDER_DEFAULT & ~Java3D.SHADING_ALPHA,
                frac, vert_colors);
            models = init_models(UNIT_MIN);
            init_texture(new JavaRenderTexture(frac3, width * mul, width * mul, null, null));
            change_model(unit_max - 1);
        }

/*C*
#endif
#ifdef _IS_H_
    public:
        virtual ~Ground();
#else
        JavaDF2Models::Ground::~Ground() {
            delete[] verts;
            delete[] vert_colors;
            delete[] texture->pix;
            int i;
            for (i = UNIT_MIN; i <= unit_max; ++ i)
            {
                models[i - UNIT_MIN]->verts = null;
                models[i - UNIT_MIN]->texture->pix = null;
                models[i - UNIT_MIN]->destroy();
                delete models[i - UNIT_MIN];
            }
            delete[] models;
        }
/**/

/*J*/
        public void change_model(int unit) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual void change_model(int unit);
#else
        void JavaDF2Models::Ground::change_model(int unit) {
            JTYPEDEF_R(Java3DModelGround);
/**/
            Java3DModelGround model = _R(models[unit - UNIT_MIN]);
            verts = model.verts;
            polys = model.polys;
            lines = model.lines;
            this.unit = model.unit;
            this.unit_max = model.unit_max;
        }
/*J*/
    }

    public static class Sphere extends Java3DModelSphere
    {
/*C*
#endif
#ifdef _IS_H_
    };

public:
    class Sphere : public Java3DModelSphere
    {
/**/
/*J*/
        public static final int
/*C*
    public:
        enum {
/**/
            UNIT_MIN    = 4,
            INIT_GROUND_HEIGHT = 65536
/*J*/
        ;
/*C*
        };
/**/
/*J*/
        public int unit;
        private int unit_min, unit_max;
        private Java3DModelSphere[] models;
/*C*
    public:
        int unit;
    private:
        int unit_min, unit_max;
        Java3DModelSphere** models;
/**/

/*J*/
        public Sphere(Java3DWorld world, Java3D parent, int unit_max, final int[] color_tbl,
            int rate2, int frac_unit, int frac_unit_mul) {
            super(world, parent);
/*C*
#endif
#ifdef _IS_H_
    public:
        Sphere(Java3DWorld* world, Java3D* parent, int unit_max, const int* color_tbl,
            int rate2, int frac_unit, int frac_unit_mul);
#else
        JavaDF2Models::Sphere::Sphere(Java3DWorld* world, Java3D* parent, int unit_max, const int* color_tbl,
            int rate2, int frac_unit, int frac_unit_mul)
            : Java3DModelSphere(world, parent) {
            JSTATIC(JavaDF2Fractal);
/**/
            int surfaces = 1;
            int width = 3000;
            int height = 256;
            int/*J*/[]/*C** /**/ frac = JavaDF2Fractal.create(frac_unit, 0.8, INIT_GROUND_HEIGHT - 1);
            int/*J*/[]/*C** /**/ frac2 = JavaDF2Fractal.create(frac_unit, 0.6, INIT_GROUND_HEIGHT - 1);
            /*C*Java3DModel::/**/init(Java3DModel.KIND_USED, 0, 0, Java3D.RENDER_DEFAULT & ~Java3D.APPEND_MASK | Java3D.APPEND_FRONT,
                null, null, null);
            this.unit_min = UNIT_MIN;
            models = init_models(
                width, height, this.unit_min, unit_max, surfaces,
                frac, INIT_GROUND_HEIGHT, frac_unit, color_tbl,
                frac2, rate2, frac_unit_mul);
            this.unit_min = UNIT_MIN;
            this.unit_max = unit_max;
            this.fog_z = 0;
            change_model(this.unit_max - 1);
        }

/*C*
#endif
#ifdef _IS_H_
    public:
        virtual ~Sphere();
#else
        JavaDF2Models::Sphere::~Sphere() {
            delete[] texture->pix;
            int i;
            for (i = unit_min; i <= unit_max; ++ i)
            {
                models[i - unit_min]->texture->pix = null;
                models[i - unit_min]->destroy();
                delete models[i - unit_min];
            }
            delete[] models;
        }
/**/

/*J*/
        public boolean translate() {
/*C*
#endif
#ifdef _IS_H_
    public:
        boolean translate();
#else
        boolean JavaDF2Models::Sphere::translate() {
            JMEMBER(Java3DWorld, world);
/**/
            ma += ANGLE_MAX / 8192;
int mul = 1;
            mx = world.ma * mul / 128;
            my = world.mb * mul / 32 - world.my * mul / 2;
/*
            if (world.va / 16 < 0) mx += (world.va / 16 > -10) ? world.va / 16 : -10;
            if (world.va / 16 > 0) mx += (world.va / 16 <  10) ? world.va / 16 :  10;
            if (world.vb / 16 < 0) my += (world.vb / 16 > -10) ? world.vb / 16 : -10;
            if (world.vb / 16 > 0) my += (world.vb / 16 <  10) ? world.vb / 16 :  10;
*/
            return (count < count_max) || (0 == count_max) ? false : true;
        }

/*J*/
        public void change_model(int unit) {
/*C*
#endif
#ifdef _IS_H_
    public:
        void change_model(int unit);
#else
        void JavaDF2Models::Sphere::change_model(int unit) {
            JTYPEDEF_R(Java3DModelSphere);
/**/
            Java3DModelSphere model = _R(models[unit - UNIT_MIN]);
            verts = model.verts;
            polys = model.polys;
            lines = model.lines;
            init_texture(model.texture);
            this.unit = unit;
        }
/*J*/
    }
}
/*C*
#endif
#ifdef _IS_H_
    };
};
#endif
/**/
