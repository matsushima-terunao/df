;/**
; * SIMD
; * 
; * @since   1.0 2007/04/23 matsushima
; * @author  1.0 2007/04/23 matsushima
; * @version $Id: JavaRenderMemorySSE2asm.asm,v 1.22 2008/03/06 16:42:46 matsushima Exp $
; * 
; * $Log: JavaRenderMemorySSE2asm.asm,v $
; * Revision 1.22  2008/03/06 16:42:46  matsushima
; * JavaDoc/Doxygen 対応
; *
; * Revision 1.21  2008/03/03 02:10:50  matsushima
; * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
; * テクスチャを int[] -> JavaRenderTexture
; *
; * Revision 1.20  2008/02/26 07:59:07  matsushima
; * JavaRenderMemory_drawLine のバグ修正、高速化
; *
; * Revision 1.19  2008/02/24 19:06:02  matsushima
; * 高速化
; *
; * Revision 1.10  2007/05/22 13:50:19  matsushima
; * テクスチャマッピング
; *
; * Revision 1.1  2007/05/09 04:18:38  matsushima
; * JavaRenderMemory から SSE2 を分離
; *
; * Revision 1.3  2007/05/07 18:53:16  matsushima
; * gouraud_alpha アセンブラ
; *
; * Revision 1.1  2007/05/06 18:20:40  matsushima
; * リネーム
; *
; * Revision 1.28  2007/05/06 18:00:09  matsushima
; * render_mode
; *
; * Revision 1.26  2007/05/05 18:06:03  matsushima
; * clear アセンブラ
; *
; * Revision 1.24  2007/05/04 08:08:55  matsushima
; * drawLine アセンブラ
; *
; * Revision 1.21  2007/05/02 02:51:12  matsushima
; * gouraud, solid アセンブラ
; *
; * Revision 1.1  2007/04/23 17:05:48  matsushima
; * リプレース
; *
; */

.686
.MMX
.XMM

use_sse     textequ     <>
;use_rdtsc   textequ     <>

;                           Pentium M                   Core 2 Duo
;   C++     SSE old new     mmx         sse
;s  12558    3144    2714    2312/ 2950  2312/ 2950
;sa 25327    8272    6609    5560/ 7250  5550/ 7100
;g  35581    6088    5200    4219/4790   4586/ 5420     3226/4300   2510/3360
;ga 52755   13439   10886    8100/9706   9151/10820     5530/7340   4630/6150
;t  17325   14190   10045
;ta 30083
;tg 31405
;tga 49321

assume  ds:_DATA

_DATA   segment USE32 page public

; 頂点バッファ
VERT        struct
            _x      dword   ?
            _y      dword   ?
            _c      dword   ?
            _tx     dword   ?
            _ty     dword   ?
VERT        ends

align       16
            _width          dword   640
public      _width
            _height         dword   480
public      _height
            _width_4        dword   ? ; _width * 4
public      _width_4
            _height_width   dword   ? ; _height * _width
public      _height_width
            _pixOff         dword   ?
public      _pixOff
            _pixOffBottom   dword   ? ; pixOff + width * (height - 1)
public      _pixOffBottom
            _b_tbl          dword   ?
public      _b_tbl
            _verts          dword   ?
public      _verts
align       16
            _dtx            dword   4 dup (?)                   ; _dtx|    dty2|    dtx2|    dty1|    dtx1|
            _dtc            dword   4 dup (?)                   ; _dtc|dbn2 db2|dan2 da2|dbn1 db1|dan1 da1|
align       16
            sxmm0   dword   4 dup (?)
            sxmm1   dword   4 dup (?)
            sxmm2   dword   4 dup (?)
            sxmm3   dword   4 dup (?)
            sxmm4   dword   4 dup (?)
            sxmm5   dword   4 dup (?)
            sxmm6   dword   4 dup (?)
            sxmm7   dword   4 dup (?)
            smm0   qword   ?
            smm1   qword   ?
            smm2   qword   ?
            smm3   qword   ?
            smm4   qword   ?
            smm5   qword   ?
            smm6   qword   ?
            smm7   qword   ?
            seax    dword   ?
            sebx    dword   ?
            secx    dword   ?
            sedx    dword   ?
            sesi    dword   ?
            sedi    dword   ?
            sebp    dword   ?
align       16
            _ttt1          dword   ?
public      _ttt1
            _ttt2          dword   ?
public      _ttt2
            _ttt3          dword   ?
public      _ttt3
            _ttt4          dword   ?
public      _ttt4
            _ttt5          dword   ?
public      _ttt5
            _ttt6          dword   ?
public      _ttt6
            _ttt7          dword   ?
public      _ttt7
            _ttt8          dword   ?
public      _ttt8

ifdef use_rdtsc
rdtsc1 macro
            rdtsc
            sub _ttt1, eax
            sbb _ttt2, edx
endm
rdtsc2 macro
            rdtsc
            add _ttt1, eax
            adc _ttt2, edx
endm
else
rdtsc1 macro
endm
rdtsc2 macro
endm
endif

; render_mode
render_alpha    textequ     <1>
render_gouraud  textequ     <2>
render_texture  textequ     <4>

_DATA   ends

_TEXT   segment USE32 page public

extern _logout:proc

mmx_bench proc c
pusha
    mov     _ttt1, 0
    mov     _ttt2, 0
    rdtsc1
    mov     esi, 1000 * 100
loopall:
        cnt = 0
        repeat 1000
;pshufd xmm0, xmm0, 11101110b
;pshufd xmm0, xmm0, 11101110b
movdqa xmm0, xmm1
movdqa xmm1, xmm0
        cnt = cnt + 1
        endm
    dec     esi
    jnz     loopall
    rdtsc2
    emms
    popa
    ret
mmx_bench endp

;/**
; * JavaRenderMemory_clear
; * 
; * @author  1.0 2007/05/06 matsushima
; * @since   1.0 2007/05/06 matsushima
; */
JavaRenderMemory_clear proc c \
        uses        ebx ecx edi es
if 0
;clear      :     280,   305,   918,   845 c loop
;clear      :     120,   309,   388,   394 c memset
;clear      :     110,   305,   360,   388
        pushf
        mov         eax, ds
        mov         es, eax
        mov         edi, _pixOff
        mov         ecx, _width
        imul        ecx, _height
        xor         eax, eax
        cld
        rep         stosd
        popf
else
        mov         ebx, _pixOff
        mov         ecx, _width
        imul        ecx, _height
        shl         ecx, 2
        add         ebx, ecx
        neg         ecx
    if 0
;clear      :     261,   310,   841,   868
        xor         eax, eax
        align       16
@@:
            mov         [ebx + ecx], eax
            mov         [ebx + ecx + 4], eax
            mov         [ebx + ecx + 8], eax
            mov         [ebx + ecx + 12], eax
            add         ecx, 16
            jnz         @b
    elseif 0
;clear      :     350,   307,  1140,   845
        pxor        mm0, mm0
        align       16
@@:
            movq        [ebx + ecx], mm0
            movq        [ebx + ecx + 8], mm0
            add         ecx, 16
            jnz         @b
    elseif 0
;clear      :     240,   307,   781,   846
        pxor        xmm0, xmm0
        align       16
@@:
            movdqa      [ebx + ecx], xmm0
            movdqa      [ebx + ecx + 16], xmm0
            add         ecx, 32
            jnz         @b
    else
mov eax, -1
    endif
endif
        inc         eax
        ret
JavaRenderMemory_clear endp

;/**
; * draw_line
; * 
; * @param   p_sx        sx/sy
; * @param   p_sy        sy/sx
; * @param   p_dx_2      dx * 2/dy * 2
; * @param   p_dy_2      dy * 2/dx * 2
; * @param   eax         color
; * @param   ebx         s
; * @param   edx         p
; * 
; * @author  1.0 2007/05/04 matsushima
; * @since   1.0 2007/05/04 matsushima
; */
draw_line macro p_sx, p_sy, p_dx_2, p_dy_2
        local       for_x_begin
        local       for_x_end
        local       skip0
        local       skip1
        local       skip2
        local       skip3
        mov         esi, p_sx                                   ; esi: sx
        mov         edi, p_dy_2                                 ; edi: dy * 2

        ; int s = -dx;
        sar         ebx, 1
        neg         ebx                                         ; ebx: s
        ; for (int x = 0; x <= dx; ++ x)
        mov         ecx, ebx
        imul        ecx, esi                                    ; ecx: -count * sx
        jz          proc_end
        sub         edx, ecx ; pixOff[p + dx]
        ; s & 3 -> jmp skip0..3
        push        ebx
        and         ebx, 3
        cmp         ebx, 2
        pop         ebx
        jg          skip3
        je          skip2
        test        ebx, 3
        jnz         skip1
            align       16
for_x_begin:
            for skip_label, <skip0, skip1, skip2, skip3>
skip_label:
                ; s += 2 * dy;
                add         ebx, edi
                ; pixOff[p] = color;
                mov         [edx + ecx], eax
                ; if (s >= 0)
                jnc         @f
                    ; s -= 2 * dx;
                    sub         ebx, p_dx_2
                    ; y1 += sy;
                    add         edx, p_sy
@@:
                ; x1 += sx;
                add         ecx, esi
            endm
        jnz         for_x_begin
endm

;/**
; * JavaRenderMemory_drawLine
; * 
; * @param   color
; * @param   x1
; * @param   y1
; * @param   x2
; * @param   y2
; * 
; * @author  1.0 2007/ matsushima
; * @since   1.0 2007/ matsushima
; */
JavaRenderMemory_drawLine proc c \
        uses    ebp ebx ecx esi edi,
        _color  : dword,
        _x1     : dword,
        _y1     : dword,
        _x2     : dword,
        _y2     : dword
        local   _sx: dword
        local   _sy: dword
        local   _dx_2: dword
        local   _dy_2: dword
rdtsc1

        mov         eax, _x1                                    ; eax: x1
        mov         ebx, _x2                                    ; ebx: x2
        mov         ecx, _y1                                    ; ecx: y1
        mov         edx, _y2                                    ; edx: y2
        mov         esi, _width                                 ; esi: _width
        mov         edi, _height                                ; edi: _height
        ; // 垂直
        ; if (x1 == x2)
        cmp         eax, ebx
        jne         vertical_end
            ; // スクリーンの外なら終了
            ; if ((x1 >= width) || (x1 < 0)) return;
            cmp         eax, esi
            jae         proc_end ; if ((unsigned int)x1 >= (unsigned int)width)
            ; // 点なら終了
            ; if (y1 == y2)
            cmp         ecx, edx
            je          proc_end
            ; // 上 -> 下
            ; if (y1 > y2) y1 <-> y2;
            mov         ebx, ecx
            cmovg       ecx, edx
            cmovg       edx, ebx
            ; // クリップ 上
            ; if (y1 < 0) y1 = 0;
            xor         ebx, ebx
            cmp         ecx, ebx
            cmovl       ecx, ebx
            ; // クリップ 下
            ; if (y2 > height) y2 = height;
            cmp         edx, edi
            cmovg       edx, edi
            ; // 描画
            ; for (int p = x1 + y * width; y < y2; ++ y, p += width)
            ; {
            ;     pixOff[p] = color;
            ; }
            sub         edx, ecx                ; count = y2 - y1
            jle         proc_end                ; if (y1 >= y2) return;
            dec         ecx                     ; p =                    (y1 - 1)
            mov         ebx, _pixOffBottom      ;     &pixOffBottom[
            imul        ecx, esi                ;                                 * width]
            sub         eax, ecx                ;                   x1 -
            lea         ebx, [ebx + eax * 4]    ;
            mov         edi, edx
            neg         edx                     ; count = -(y2 - y1)
            imul        edx, esi                ;                    * width
            mov         ecx, _color
            ; 2 ドット単位の端数
            test        edi, 1
            jz          @f
                mov         [ebx + edx * 4], ecx
                add         edx, esi
                jz          proc_end
@@:
            ; 2 ドット単位
            lea         edi, [ebx + esi * 4]
            shl         esi, 1
                align   16
@@:
                mov         [ebx + edx * 4], ecx
                mov         [edi + edx * 4], ecx
                add         edx, esi
                jnz         @b
            jmp         proc_end
vertical_end:
        ; // 水平
        ; else if (y1 == y2)
        cmp         ecx, edx
        jne         horizontal_end
            ; // スクリーンの外なら終了
            ; if ((y1 >= height) || (y1 < 0)) return;
            cmp         ecx, edi
            jae         proc_end
            ; // 左 -> 右
            ; if (x1 > x2) x1 <-> x2;
            cmp         eax, ebx
            mov         edx, eax
            cmovg       eax, ebx
            cmovg       ebx, edx
            ; // クリップ 左
            ; if (x1 < 0) x1 = 0;
            xor         edx, edx
            cmp         eax, edx
            cmovl       eax, edx
            ; // クリップ 右
            ; if (x2 > width) x2 = width;
            cmp         ebx, esi
            cmovg       ebx, esi
            ; // 描画
            ; for (int p = x + y1 * width; x < x2; ++ x, ++ p)
            ; {
            ;     pixOff[p] = color;
            ; }
            sub         eax, ebx                ; count = -(x2 - x1)
            jge         proc_end                ; if (x1 >= x2) return;
            mov         edx, _pixOffBottom      ; p = &pixOffBottom[
            imul        ecx, esi                ;                        y1 * width]
            sub         ebx, ecx                ;                   x2 -
            lea         edx, [edx + ebx * 4]    ;
            mov         ebx, _color
            ; 2 ドット単位の端数
            test        al, 1
            jz          @f
                mov         [edx + eax * 4], ebx
                inc         eax
                jz          proc_end
            ; 2 ドット単位
                align       16
@@:
                mov         [edx + eax * 4], ebx
                mov         [edx + eax * 4 + 4], ebx
                add         eax, 2
                jnc         @b
            jmp         proc_end
horizontal_end:
        ; // 垂直・水平以外
        ; else
            ; // 範囲チェック x
            ; // x1 > x2 なら入れ替え
            ; if (x1 > x2)
            cmp         eax, ebx
            jle         @f
                ; x1 <-> x2
                ; y1 <-> y2
                xchg        eax, ebx
                xchg        ecx, edx
                mov         _x1, eax
                mov         _x2, ebx
                mov         _y1, ecx
                mov         _y2, edx
@@:
            ; // スクリーンの外なら終了
            ; if (x2 < 0) return;
            test        ebx, ebx ; cmp ebx, 0
            jl          proc_end
            ; if (x1 > width - 1) return;
            cmp         eax, esi
            jge         proc_end
            ; // クリップ 左
            ; if (x1 < 0)
            test        eax, eax ; cmp eax, 0
            jge         @f
                ; y1 -= x1 * (y2 - y1) / (x2 - x1);
                sub         edx, ecx    ;            (y2 - y1)
                sub         ebx, eax    ;                        (x2 - x1)
                imul        edx         ;       x1 *
                idiv        ebx         ;                      /
                sub         ecx, eax    ; y1 -=
                ; x1 = 0;
                xor         eax, eax    ; x1 = 0
                mov         _x1, eax
                mov         _y1, ecx
                mov         ebx, _x2
                mov         edx, _y2
@@:
            ; // クリップ 右
            ; if (x2 > width - 1)
            cmp         ebx, esi
            jl          @f
                ; y2 -= (x2 - (width - 1)) * (y2 - y1) / (x2 - x1);
                sub         edx, ecx    ;                            (y2 - y1)
                sub         ebx, eax    ;                                        (x2 - x1)
                mov         eax, _x2    ;       (x2
                sub         eax, esi    ;           - (width
                inc         eax         ;                    - 1))
                imul        edx         ;                          *
                idiv        ebx         ;                                      /
                mov         edx, _y2    ; y2
                sub         edx, eax    ;    -=
                ; x2 = width - 1;
                mov         ebx, esi    ; x2 = width
                dec         ebx         ;            - 1
                mov         eax, _x1
                mov         _x2, ebx
                mov         _y2, edx
@@:
            ; // 範囲チェック y
            ; // y1 > y2 なら入れ替え
            ; if (y1 > y2)
            cmp         ecx, edx
            jle         @f
                ; x1 <-> x2
                ; y1 <-> y2
                xchg        eax, ebx
                xchg        ecx, edx
                mov         _x1, eax
                mov         _x2, ebx
                mov         _y1, ecx
                mov         _y2, edx
@@:
            ; // スクリーンの外なら終了
            ; if (y2 < 0) return;
            test        edx, edx ; cmp edx, 0
            jl          proc_end
            ; if (y1 > height - 1) return;
            cmp         ecx, edi
            jge         proc_end
            ; // クリップ 上
            ; if (y1 < 0)
            test        ecx, ecx ; cmp ecx, 0
            jge         @f
                ; x1 -= y1 * (x2 - x1) / (y2 - y1);
                xchg        eax, ecx    ; x1 <-> y1
                xchg        ebx, edx    ; x2 <-> y2
                sub         edx, ecx    ;            (x2 - x1)
                sub         ebx, eax    ;                        (y2 - y1)
                imul        edx         ;       y1 *
                idiv        ebx         ;                      /
                sub         ecx, eax    ; x1 -=
                mov         eax, ecx    ; x1
                ; y1 = 0;
                xor         ecx, ecx    ; y1 = 0
                mov         ebx, _x2
                mov         edx, _y2
                mov         _x1, eax
                mov         _y1, ecx
@@:
            ; // クリップ 下
            ; if (y2 > height - 1)
            cmp         edx, edi
            jl          @f
                ; x2 -= (y2 - (height - 1)) * (x2 - x1) / (y2 - y1);
                xchg        eax, ecx    ; x1 <-> y1
                xchg        ebx, edx    ; x2 <-> y2
                sub         edx, ecx    ;                            (x2 - x1)
                sub         ebx, eax    ;                                        (y2 - y1)
                mov         eax, _y2    ;       (y2
                sub         eax, edi    ;           - (height
                inc         eax         ;                    - 1))
                imul        edx         ;                          *
                idiv        ebx         ;                                      /
                mov         edx, _x2    ; x2
                sub         edx, eax    ;    -=
                mov         ebx, edx    ; x2
                ; y2 = height - 1;
                mov         edx, edi    ; y2 = height
                dec         edx         ;             - 1
                mov         eax, _x1
                mov         ecx, _y1
                mov         _x2, ebx
                mov         _y2, edx
@@:
            ; // 描画
            ; int sx = (x1 < x2 ? 1 : -1);
            ; int dx = (x2 - x1) * sx;
            ; sx *= 4;
            sub         ebx, eax        ; dx
            mov         edi, 4          ; sx
            jg          @f
                neg         ebx
                neg         edi
@@:
            sal         ebx, 1          ; 2 * dx                ; ebx: 2 * dx
            mov         _sx, edi
            mov         _dx_2, ebx
            ; int sy = (y1 < y2 ? 1 : -1);
            ; int dy = (y2 - y1) * sy;
            ; sy *= -width * 4;
            neg         esi
            sal         esi, 2          ; sy                    ; esi: -width * 4
            sub         edx, ecx        ; dy
            jg          @f
                neg         edx
                neg         esi
@@:
            sal         edx, 1          ; 2 * dy
            mov         _sy, esi
            mov         _dy_2, edx
            ; int p = x1 + y1 * width;
            imul        ecx, esi                ;                        y1 * (-width * 4)
            add         ecx, _pixOffBottom      ; &pixOffBottom[
            lea         edx, [eax * 4 + ecx]    ;               x1 * 4 +                  ]
            mov         eax, _color                             ; eax: color
            ; if (dx >= dy)
            cmp         ebx, _dy_2
            jl          dy_dx
                ; // 45 度以下
                draw_line   _sx, _sy, _dx_2, _dy_2
                jmp         proc_end
            ; else
dy_dx:
                ; // 45 度以上
                mov         ebx, _dy_2          ; 2 * dy        ; ebx: 2 * dy
                draw_line   _sy, _sx, _dy_2, _dx_2
                jmp         proc_end
rdtsc2
        xor     eax, eax
        ret
proc_end:
rdtsc2
        mov     eax, 1
        ret
JavaRenderMemory_drawLine endp

;/**
; * draw_scan_line_template
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm6    color|-1  r| g  b|-1  r| g  b|
; * 
; * @author  1.0 2008/01/25 matsushima
; * @since   1.0 2008/01/25 matsushima
; */
draw_scan_line_all macro code_left, cnt0 := <>
        unit        = 8                 ; ループ単位バイト数 = 8 ピクセル
        mov         eax, ecx
        and         eax, unit - 1
        sub         ecx, eax
        jmp         cs:@catstr(right_labels, cnt0)[eax * 4]
@@:
            for         cnt, <0, 1, 2, 3, 4, 5, 6, 7> ; 0, ..., unit - 1
@catstr(right_label, cnt0, cnt):
                code_left   ebx + ecx * 4 + cnt * 4
            endm
            add         ecx, unit
            jnc         @b
        ; dummy label
        for         cnt, <0, 1, 2>
@catstr(left_label, cnt0, cnt):
        endm
        for         cnt, <8, 9, 10, 11>
@catstr(right_label, cnt0, cnt):
        endm
endm

draw_scan_line_left macro code_left, unit0 := <(unit * 2)>, cnt0 := <>
        unit        = 4 * 4             ; アラインバイト数 = 16 バイト = 4 ピクセル
        sal         ecx, 2              ; -dp * 4
        cmp         ecx, -unit * 3      ; if (-dp * 4 > -unit * 3)  ; unit * 3 未満なら right
        jg          @catstr(right_loop, cnt0)   ; (center_loop が unit * 2 単位なので unit * 3 以上必要)
        ; unit バイト単位に到達するまで
@catstr(left_loop, cnt0):
        lea         edx, [ebx + ecx]    ; p1 = p2 + -dp
        and         edx, unit - 1       ; p1 &= unit - 1                        ; unit 端数
        jz          @catstr(center_loop, cnt0)
        sub         ecx, edx            ; -dp = -dp - (p1 & (unit - 1))
        add         ecx, unit           ;                               + unit  ; 次の unit 単位
        jmp         cs:@catstr(left_labels, cnt0)[edx]
        for         cnt, <0, 1, 2>
@catstr(left_label, cnt0, cnt):
            code_left   ebx + ecx - (3 - cnt) * 4                               ; -12, -8, -4
        endm
@catstr(center_loop, cnt0):
endm

draw_scan_line_center macro code_center, unit0 := <(unit * 2)>, cnt0 := <>
        ; unit * 2 バイト単位
        add         ecx, unit * 2 - 4
        align       16
@@:
            off = 0
            repeat      unit * 2 / unit0
                code_center ebx + ecx - (unit * 2 - 4) + off, \                 ; -(32 - 4)
                            ebx + ecx - (unit * 2 - 4) + off + unit0 / 2        ; -(32 - 4) + 16
                off = off + unit0
            endm
            add         ecx, unit * 2
            jnc         @b
        sub         ecx, unit * 2 - 4
endm

draw_scan_line_right macro code_right, unit0 := <(unit * 2)>, cnt0 := <>
        ; 残り
@catstr(right_loop, cnt0):
        jmp         cs:@catstr(right_labels, cnt0)[11 * 4 + ecx]
        for         cnt, <0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>
            code_right  ebx - (12 - cnt) * 4                                    ; -12 * 4 = 48, 44, 40, ..., 4
@catstr(right_label, cnt0, cnt):
        endm
endm

;/**
; * FillPolygonSolid_draw_scan_line
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm6    color|-1 r g b|-1 r g b|-1 r g b|-1 r g b|
; * 
; * @author  1.0 2007/04 matsushima
; * @since   1.0 2007/04 matsushima
; */
FillPolygonSolid_draw_scan_line macro render_mode
        movd        eax, xmm6
ifdef use_sse
else
        movdq2q     mm0, xmm6
endif
        ; // ループ
        draw_scan_line_left     FillPolygonSolid_draw_scan_line_left
        draw_scan_line_center   FillPolygonSolid_draw_scan_line_center
        draw_scan_line_right    FillPolygonSolid_draw_scan_line_left
endm

FillPolygonSolid_draw_scan_line_left macro off
        ; pixOff[p] = color; // S
        mov         [off], eax
endm

FillPolygonSolid_draw_scan_line_center macro off1, off2
        ; pixOff[p] = color; // S
ifdef use_sse
        movdqa      [off1], xmm6
        movdqa      [off2], xmm6
else
        movq        [off1], mm0
        movq        [off1 + 8], mm0
        movq        [off1 + 16], mm0
        movq        [off1 + 24], mm0
endif
endm

;/**
; * FillPolygonAlpha_draw_scan_line
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm5    0    | 0  0| 0  0| 0  0| 0  0|
; * @param  xmm6    a*c  |-1 ar|ag ab|-1 ar|ag ab|
; * @param  xmm7    an<<8| 0 an|an an| 0 an|an an|
; * 
; * @author  1.0 2007/05/24 matsushima
; * @since   1.0 2007/05/24 matsushima
; */
FillPolygonAlpha_draw_scan_line macro render_mode
        movdq2q     mm3, xmm5                                   ; mm3| 0  0| 0  0|
        movdq2q     mm4, xmm6                                   ; mm4|-1 ar|ag ab|
        movdq2q     mm5, xmm7                                   ; mm5| 0 an|an an|
        ; // ループ
        draw_scan_line_left     FillPolygonAlpha_draw_scan_line_left
ifdef use_sse
        draw_scan_line_center   FillPolygonAlpha_draw_scan_line_center
else
        movq2dq     xmm0, mm6
        movq2dq     xmm1, mm7
        movdq2q     mm5, xmm5                                   ; mm3| 0  0| 0  0|
        movdq2q     mm6, xmm6                                   ; mm4|-1 ar|ag ab|
        movdq2q     mm7, xmm7                                   ; mm5| 0 an|an an|
        draw_scan_line_center   FillPolygonAlpha_draw_scan_line_center
        movdq2q     mm6, xmm0
        movdq2q     mm7, xmm1
        movdq2q     mm3, xmm5                                   ; mm3| 0  0| 0  0|
        movdq2q     mm4, xmm6                                   ; mm4|-1 ar|ag ab|
        movdq2q     mm5, xmm7                                   ; mm5| 0 an|an an|
endif
        draw_scan_line_right    FillPolygonAlpha_draw_scan_line_left
endm

FillPolygonAlpha_draw_scan_line_left macro off
        ; int r = ((pixOff[p] & 0x00ff0000) * an1) & 0xff000000; // A
        ; int g = ((pixOff[p] & 0x0000ff00) * an1) & 0x00ff0000; // A
        ; int b = ((pixOff[p] & 0x000000ff) * an1) & 0x0000ff00; // A
        movd        mm0, [off]                                  ; mm0|    |    |             |  a  r   g  b|
        punpcklbw   mm0, mm3                                    ; mm0|    |    |     a      r|     g      b|
        pmulhuw     mm0, mm5 ; 00ff <- 00ff * ffff              ; mm0|    |    |     0    ran|   gan    ban|
        ; pixOff[p] = a1 | ((r | g | b) >> 8); // A
        paddw       mm0, mm4                                    ; mm0|    |    |     0 ran+ra|gan+rg ban+ba|
        packuswb    mm0, mm0 ; 0000ffff <- 00ff00ff             ; mm0|    |    |  0  r   g  b|  0  r   g  b|
        movd        [off], mm0
endm

FillPolygonAlpha_draw_scan_line_center macro off1, off2
ifdef use_sse
        ; int r = ((pixOff[p] & 0x00ff0000) * an1) & 0xff000000; // A
        ; int g = ((pixOff[p] & 0x0000ff00) * an1) & 0x00ff0000; // A
        ; int b = ((pixOff[p] & 0x000000ff) * an1) & 0x0000ff00; // A
        movdqa      xmm0, [off1]                                ; xmm0|    |    |             |  a  r   g  b|
        movdqa      xmm2, [off2]                                ; xmm2|    |    |             |  a  r   g  b|
        movdqa      xmm1, xmm0                                  ; xmm1|    |    |             |  a  r   g  b|
        movdqa      xmm3, xmm2                                  ; xmm3|    |    |             |  a  r   g  b|
        punpcklbw   xmm0, xmm5                                  ; xmm0|    |    |     a      r|     g      b|
        punpckhbw   xmm1, xmm5                                  ; xmm1|    |    |     a      r|     g      b|
        punpcklbw   xmm2, xmm5                                  ; xmm2|    |    |     a      r|     g      b|
        punpckhbw   xmm3, xmm5                                  ; xmm3|    |    |     a      r|     g      b|
        pmulhuw     xmm0, xmm7 ; 00ff <- 00ff * ffff            ; xmm0|    |    |     0    ran|   gan    ban|
        pmulhuw     xmm1, xmm7 ; 00ff <- 00ff * ffff            ; xmm1|    |    |     0    ran|   gan    ban|
        pmulhuw     xmm2, xmm7 ; 00ff <- 00ff * ffff            ; xmm2|    |    |     0    ran|   gan    ban|
        pmulhuw     xmm3, xmm7 ; 00ff <- 00ff * ffff            ; xmm3|    |    |     0    ran|   gan    ban|
        ; pixOff[p] = a1 | ((r | g | b) >> 8); // A
        paddw       xmm0, xmm6                                  ; xmm0|    |    |     0 ran+ra|gan+rg ban+ba|
        paddw       xmm1, xmm6                                  ; xmm1|    |    |     0 ran+ra|gan+rg ban+ba|
        paddw       xmm2, xmm6                                  ; xmm2|    |    |     0 ran+ra|gan+rg ban+ba|
        paddw       xmm3, xmm6                                  ; xmm3|    |    |     0 ran+ra|gan+rg ban+ba|
        packuswb    xmm0, xmm1 ; 0000ffff <- 00ff00ff           ; xmm0| 0 r g b| 0 r g b| 0 r g b| 0 r g b|
        packuswb    xmm2, xmm3 ; 0000ffff <- 00ff00ff           ; xmm2| 0 r g b| 0 r g b| 0 r g b| 0 r g b|
        movdqa      [off1], xmm0
        movdqa      [off2], xmm2
else
    for off, <off1, off2>
        ; int r = ((pixOff[p] & 0x00ff0000) * an1) & 0xff000000; // A
        ; int g = ((pixOff[p] & 0x0000ff00) * an1) & 0x00ff0000; // A
        ; int b = ((pixOff[p] & 0x000000ff) * an1) & 0x0000ff00; // A
        movq        mm0, [off]                                  ; mm0|             |  a  r   g  b|
        movq        mm2, [off + 8]                              ; mm2|             |  a  r   g  b|
        movq        mm1, mm0                                    ; mm1|             |  a  r   g  b|
        movq        mm3, mm2                                    ; mm3|             |  a  r   g  b|
        punpcklbw   mm0, mm5                                    ; mm0|     a      r|     g      b|
        punpckhbw   mm1, mm5                                    ; mm1|     a      r|     g      b|
        punpcklbw   mm2, mm5                                    ; mm2|     a      r|     g      b|
        punpckhbw   mm3, mm5                                    ; mm3|     a      r|     g      b|
        pmulhuw     mm0, mm7 ; 00ff <- 00ff * ffff              ; mm0|     0    ran|   gan    ban|
        pmulhuw     mm1, mm7 ; 00ff <- 00ff * ffff              ; mm1|     0    ran|   gan    ban|
        pmulhuw     mm2, mm7 ; 00ff <- 00ff * ffff              ; mm2|     0    ran|   gan    ban|
        pmulhuw     mm3, mm7 ; 00ff <- 00ff * ffff              ; mm3|     0    ran|   gan    ban|
        ; pixOff[p] = a1 | ((r | g | b) >> 8); // A
        paddw       mm0, mm6                                    ; mm0|     0 ran+ra|gan+rg ban+ba|
        paddw       mm1, mm6                                    ; mm1|     0 ran+ra|gan+rg ban+ba|
        paddw       mm2, mm6                                    ; mm2|     0 ran+ra|gan+rg ban+ba|
        paddw       mm3, mm6                                    ; mm3|     0 ran+ra|gan+rg ban+ba|
        packuswb    mm0, mm1 ; 0000ffff <- 00ff00ff             ; mm0| 0 r g b| 0 r g b|
        packuswb    mm2, mm3 ; 0000ffff <- 00ff00ff             ; mm2| 0 r g b| 0 r g b|
        movq        [off], mm0
        movq        [off + 8], mm2
    endm
endif
endm

;/**
; * FillPolygonGouraudCommon_draw_scan_line
; * 
; * FillPolygonGouraud_draw_scan_line
; * FillPolygonGouraudAlpha_draw_scan_line
; * の共通部分。
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm6     c|( an2) r2| g2 b2|( an1) r1| g1 b1| (GA)
; * @param  xmm7    dc|(dan2)dr2|dg2db2|(dan1)dr1|dg1db1| (GA)
; * 
; * @author  1.0 2007/04/23 matsushima
; * @since   1.0 2007/04/23 matsushima
; */
FillPolygonGouraudCommon_draw_scan_line macro draw_scan_line
        ; int r = r1; // G
        ; int g = g1; // G
        ; int b = b1; // G
        movdqa      xmm0, xmm6          ; c = c1                ; xmm0|a2r2|g2b2|a1r1|g1b1|
        ; int dr = (r2 - r1) / pdx; // G
        ; int dg = (g2 - g1) / pdx; // G
        ; int db = (b2 - b1) / pdx; // G
        pshufd      xmm1, xmm6, 1110b ; ??32                    ; xmm1|    |    |a2r2|g2b2|
        psubw       xmm1, xmm0          ; dc = (c2 - c1)
        ;
        punpcklwd   xmm1, xmm1                                  ; xmm1|a2a2|r2r2|g2g2|b2b2|
        psrad       xmm1, 16      ; 符号拡張 +-                 ; xmm1|  a2|  r2|  g2|  b2|
        cvtdq2ps    xmm1, xmm1    ; ps <- dw
        cvtsi2ss    xmm2, eax     ; ss <- dw                    ; xmm2|    |    |    | pdx|
        pshufd      xmm2, xmm2, 0 ; ps <- ss                    ; xmm2| pdx| pdx| pdx| pdx|
        rcpps       xmm2, xmm2
        mulps       xmm1, xmm2          ;                / pdx
        ; if (px1 < 0)
        test        edx, edx ; cmp edx, 0
        jge         @f
            ; // 左にはみ出した分をスキップ
            ; r -= dr * px1; // G
            ; g -= dg * px1; // G
            ; b -= db * px1; // G
            cvtsi2ss    xmm2, edx     ; ss <- dw                ; xmm2|    |    |    | px1|
            pshufd      xmm2, xmm2, 0 ; ps <- ss                ; xmm2| px1| px1| px1| px1|
            mulps       xmm2, xmm1          ;      dc * px1
            cvtps2dq    xmm2, xmm2    ; dw <- ps
            packssdw    xmm2, xmm2
            psubw       xmm0, xmm2          ; c -=
@@:
        cvtps2dq    xmm1, xmm1  ; dw <- ps
        packssdw    xmm1, xmm1  ; ffff <- ffffffff              ; xmm1|    |    |dadr|dgdb|
        movdq2q     mm0, xmm0                                   ; mm0| a r| g b|
        movdq2q     mm1, xmm1                                   ; mm1|dadr|dgdb|
        ; 桁あふれ防止切り上げ(xmm1 < 0 のときのみ)
        pxor        mm2, mm2
        pcmpgtw     mm2, mm1    ; r = (0 > xmm1) ? -1 : 0       ; mm2| r r| r r|
        psubsw      mm1, mm2 
        ; // ループ
        draw_scan_line_left     @catstr(draw_scan_line, _left), 16
ifdef use_sse
        movq2dq     xmm0, mm0                                   ; xmm0|             |             |     a      r|     g      b|
        movq2dq     xmm1, mm1                                   ; xmm1|             |             |    da     dr|    dg     gb|
        movdqa      xmm2, xmm0                                  ; xmm2|             |             |     a      r|     g      b|
        paddw       xmm2, xmm1                                  ; xmm2|             |             |a+  da r+  dr|g+  dg b+  db|
        punpcklqdq  xmm0, xmm2          ; c + dc * 0, 1         ; xmm0|a+  da r+  dr|g+  dg b+  db|     a      r|     g      b|
        punpcklqdq  xmm1, xmm1                                  ; xmm1|    da     dr|    dg     gb|    da     dr|    dg     gb|
        psllw       xmm1, 1                                     ; xmm1|  2*da   2*dr|  2*dg   2*gb|  2*da   2*dr|  2*dg   2*gb|
        movdqa      xmm2, xmm0                                  ; xmm2|a+  da r+  dr|g+  dg b+  db|     a      r|     g      b|
        paddw       xmm2, xmm1          ; c + dc * 3, 2         ; xmm2|a+3*da r+3*dr|g+3*dg b+3*db|a+2*da r+2*dr|g+2*dg b+2*db|
        psllw       xmm1, 1             ; dc * 4                ; xmm1|  4*da   4*dr|  4*dg   4*gb|  4*da   4*dr|  4*dg   4*gb|
        draw_scan_line_center   @catstr(draw_scan_line, _center), 16
        movdq2q     mm0, xmm0
        draw_scan_line_right    @catstr(draw_scan_line, _left), 16
else
        movq        mm2, mm0
        paddw       mm2, mm1                                    ; mm2|a+da r+dr|g+dg b+db|
        psllw       mm1, 1              ; dc * 2                ; mm1|2*da 2*dr|2*dg 2*db|
        draw_scan_line_center   @catstr(draw_scan_line, _center), 16
        psraw       mm1, 1              ; dc * 1                ; mm1|  da   dr|  dg   db|
        draw_scan_line_right    @catstr(draw_scan_line, _left), 16
endif
endm

;/**
; * FillPolygonGouraud_draw_scan_line
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm6     c|( an2) r2| g2 b2|( an1) r1| g1 b1| (GA)
; * @param  xmm7    dc|(dan2)dr2|dg2db2|(dan1)dr1|dg1db1| (GA)
; * 
; * @author  1.0 2007/04/23 matsushima
; * @since   1.0 2007/04/23 matsushima
; */
FillPolygonGouraud_draw_scan_line macro render_mode
        ; // * FillPolygonGouraud_draw_scan_line
        ; // * FillPolygonGouraudAlpha_draw_scan_line
        ; // * の共通部分。
        FillPolygonGouraudCommon_draw_scan_line FillPolygonGouraud_draw_scan_line
endm

FillPolygonGouraud_draw_scan_line_left macro off
        ; r += dr; // G
        ; g += dg; // G
        ; b += db; // G
        movq        mm4, mm0
        paddw       mm0, mm1
        ; pixOff[p] // G
        ;     = 0xff000000 // G
        ;     | ( r        & 0x00ff0000) // G
        ;     | ((g >>  8) & 0x0000ff00) // G
        ;     | ((b >> 16) & 0x000000ff); // G
        psrlw       mm4, 7
        packuswb    mm4, mm4
        movd        [off], mm4
endm

FillPolygonGouraud_draw_scan_line_center macro off1, off2
ifdef use_sse
        ; pixOff[p] // G
        ;     = 0xff000000 // G
        ;     | ( r        & 0x00ff0000) // G
        ;     | ((g >>  8) & 0x0000ff00) // G
        ;     | ((b >> 16) & 0x000000ff); // G
            ; r += dr; // G
            ; g += dg; // G
            ; b += db; // G
        movdqa      xmm4, xmm0
        movdqa      xmm5, xmm2
        psrlw       xmm4, 7
        psrlw       xmm5, 7
            paddw       xmm0, xmm1
        packuswb    xmm4, xmm5
            paddw       xmm2, xmm1
        movdqa      [off1], xmm4
else
        ; pixOff[p] // G
        ;     = 0xff000000 // G
        ;     | ( r        & 0x00ff0000) // G
        ;     | ((g >>  8) & 0x0000ff00) // G
        ;     | ((b >> 16) & 0x000000ff); // G
            ; r += dr; // G
            ; g += dg; // G
            ; b += db; // G
        ; off1
        movq        mm4, mm0
        movq        mm3, mm2
        psrlw       mm4, 7
        psrlw       mm3, 7
            paddw       mm0, mm1
            paddw       mm2, mm1
        packuswb    mm4, mm3
        ; off2
        movq        mm5, mm0
        movq        mm3, mm2
        psrlw       mm5, 7
        psrlw       mm3, 7
            paddw       mm0, mm1
            paddw       mm2, mm1
        packuswb    mm5, mm3
        movq        [off1], mm4
        movq        [off2], mm5
endif
endm

;/**
; * FillPolygonGouraudAlpha_draw_scan_line
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm6     c|( an2) r2| g2 b2|( an1) r1| g1 b1| (GA)
; * @param  xmm7    dc|(dan2)dr2|dg2db2|(dan1)dr1|dg1db1| (GA)
; * 
; * @author  1.0 2007/04/23 matsushima
; * @since   1.0 2007/04/23 matsushima
; */
FillPolygonGouraudAlpha_draw_scan_line macro render_mode
        ; // * FillPolygonGouraud_draw_scan_line
        ; // * FillPolygonGouraudAlpha_draw_scan_line
        ; // * の共通部分。
        FillPolygonGouraudCommon_draw_scan_line FillPolygonGouraudAlpha_draw_scan_line
endm

FillPolygonGouraudAlpha_draw_scan_line_left macro off
        ; int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // GA
        ; int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // GA
        ; int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // GA
        movd        mm4, [off]                                  ; mm4|             | a1 r1  g1 b1| d1
        punpcklbw   mm4, mm4 ; ffff <- ff                       ; mm4| a1 a1  r1 r1| g1 g1  b1 b1| d1
            ; int _an = an >> 8; // 0000ffff <- 00ffffff // A
            pshufw      mm3, mm0, 11111111b                     ; mm3|   an1    an1|   an1    an1| an1
        pmulhuw     mm4, mm3 ; 7fff <- ffff * 7fff ; d * an     ; mm4|a1*an1 r1*an1|g1*an1 b1*an1| d1
        paddw       mm4, mm0                       ;        + s ; mm4|a1     r1    |g1     b1    | d1
        ; r += dr; // G
        ; g += dg; // G
        ; b += db; // G
        ; an += dan; // A
        paddw       mm0, mm1
        ; pixOff[p] // GA
        ;     = 0xff000000 // GA
        ;     | ((_r      ) & 0x00ff0000) // GA
        ;     | ((_g >>  8) & 0x0000ff00) // GA
        ;     | ((_b >> 16) & 0x000000ff); // GA
        psrlw       mm4, 7   ; 00ff <- 7f00                     ; mm4|    a1     r1|    g1     b1| d1
        packuswb    mm4, mm4                                    ; mm4|             | a1 r1  g1 b1| d1
        movd        [off], mm4
endm

FillPolygonGouraudAlpha_draw_scan_line_center macro off1, off2
ifdef use_sse
        ; int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // GA
        ; int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // GA
        ; int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // GA
        movdqa      xmm4, [off1]                                ; xmm4| a4 r4  g4 b4| a3 r3  g3 b3| a2 r2  g2 b2| a1 r1  g1 b1| d1234
            ; int _an = an >> 8; // 0000ffff <- 00ffffff // A
            pshuflw     xmm3, xmm0, 11111111b                   ; xmm3|   an2     r2|    g2     b2|   an1    an1|   an1    an1| an12
        movdqa      xmm5, xmm4                                  ; xmm5| a4 r4  g4 b4| a3 r3  g3 b3| a2 r2  g2 b2| a1 r1  g1 b1| d1234
            pshufhw     xmm3, xmm3, 11111111b                   ; xmm3|   an2    an2|   an2    an2|   an1    an1|   an1    an1| an12
        punpcklbw   xmm4, xmm4 ; ffff <- ff                     ; xmm4| a2 a2  r2 r2| g2 g2  b2 b2| a1 a1  r1 r1| g1 g1  b1 b1| d12
        punpckhbw   xmm5, xmm5 ; ffff <- ff                     ; xmm5| a4 a4  r4 r4| g4 g4  b4 b4| a3 a3  r3 r3| g3 g3  b3 b3| d34
        pmulhuw     xmm4, xmm3 ; 7fff <- ffff * 7fff ; d * an   ; xmm4|a2*an2 r2*an2|g2*an2 b2*an2|a1*an1 r1*an1|g1*an1 b1*an1| d12
            pshuflw     xmm3, xmm2, 11111111b                   ; xmm3|   an4     r4|    g4     b4|   an3    an3|   an3    an3| an34
            pshufhw     xmm3, xmm3, 11111111b                   ; xmm3|   an4    an4|   an4    an4|   an3    an3|   an3    an3| an34
        pmulhuw     xmm5, xmm3 ; 7fff <- ffff * 7fff ; d * an   ; xmm5|a4*an4 r4*an4|g4*an4 b4*an4|a3*an3 r3*an3|g3*an3 b3*an3| d34
        paddw       xmm4, xmm0                       ;      + s ; xmm4|a2     r2    |g2     b2    |a1     r1    |g1     b1    | d12
        paddw       xmm5, xmm2                       ;      + s ; xmm5|a4     r4    |g4     b4    |a3     r3    |g3     b3    | d34
        psrlw       xmm4, 7    ; 00ff <- 7fff                   ; xmm4|    a2     r2|    g2     b2|    a1     r1|    g1     b1| d12
        psrlw       xmm5, 7    ; 00ff <- 7fff                   ; xmm5|    a4     r4|    g4     b4|    a3     r3|    g3     b3| d34
        ; pixOff[p] // GA
        ;     = 0xff000000 // GA
        ;     | ((_r      ) & 0x00ff0000) // GA
        ;     | ((_g >>  8) & 0x0000ff00) // GA
        ;     | ((_b >> 16) & 0x000000ff); // GA
            ; r += dr; // G
            ; g += dg; // G
            ; b += db; // G
            ; an += dan; // A
            paddw       xmm0, xmm1
        packuswb    xmm4, xmm5                                  ; xmm4| a4 r4  g4 b4| a3 r3  g3 b3| a2 r2  g2 b2| a1 r1  g1 b1| d1234
            paddw       xmm2, xmm1
        movdqa      [off1], xmm4
else
    for off, <off1, off2>
        ; int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // GA
        ; int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // GA
        ; int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // GA
        movq        mm4, [off]                                  ; mm4| a2 r2  g2 b2| a1 r1  g1 b1| d12
            ; int _an = an >> 8; // 0000ffff <- 00ffffff // A
            pshufw      mm3, mm0, 11111111b                     ; mm3|   an1    an1|   an1    an1| an1
        movq        mm5, mm4                                    ; mm5| a2 r2  g2 b2| a1 r1  g1 b1| d12
        punpcklbw   mm4, mm4                                    ; mm4| a1 a1  r1 r1| g1 g1  b1 b1| d1
        punpckhbw   mm5, mm5                                    ; mm5| a2 a2  r2 r2| g2 g2  b2 b2| d2
        pmulhuw     mm4, mm3 ; 7fff <- ffff * 7fff ; d * an     ; mm4|a1*an1 r1*an1|g1*an1 b1*an1| d1
            pshufw      mm3, mm2, 11111111b                     ; mm3|   an2    an2|   an2    an2| an2
        pmulhuw     mm5, mm3 ; 7fff <- ffff * 7fff ; d * an     ; mm5|a2*an2 r2*an2|g2*an2 b2*an2| d2
        paddw       mm4, mm0                       ;        + s ; mm4|a1     r1    |g1     b1    | d1
        paddw       mm5, mm2                       ;        + s ; mm5|a2     r2    |g2     b2    | d2
        psrlw       mm4, 7   ; 00ff <- 7fff                     ; mm4|    a1     r1|    g1     b1| d1
        psrlw       mm5, 7   ; 00ff <- 7fff                     ; mm5|    a2     r2|    g2     b2| d2
        ; pixOff[p] // GA
        ;     = 0xff000000 // GA
        ;     | ((_r      ) & 0x00ff0000) // GA
        ;     | ((_g >>  8) & 0x0000ff00) // GA
        ;     | ((_b >> 16) & 0x000000ff); // GA
            ; r += dr; // G
            ; g += dg; // G
            ; b += db; // G
            ; an += dan; // A
            paddw       mm0, mm1
        packuswb    mm4, mm5                                    ; mm4| a2 r2  g2 b2| a1 r1  g1 b1| d12
            paddw       mm2, mm1
        movq        [off], mm4
    endm
endif
endm

;/**
; * FillPolygonTextureCommon_draw_scanline
; * 
; * FillPolygonTexture_draw_scanline
; * FillPolygonTextureAlpha_draw_scanline
; * FillPolygonTextureGouraud_draw_scanline
; * FillPolygonTextureGouraudAlpha_draw_scanline
; * の共通部分。
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * @param  xmm6     tx|   ty2|   tx2|   ty1|   tx1|
; * @param  xmm7     tc|bn2 b2|an2 a2|bn1 b1|an1 a1| TA, TG, TGA
; * @return mm0      tx|    ty|    tx|
; * @return mm1     dtx|   dty|   dtx|
; * @return esi     texture
; * @return xmm6      a| an  a| an  a| an  a| an  a| TA, TGA
; * @return xmm7     da|dan da|dan da|dan da|dan da| TA, TGA
; * @return xmm0      b| bn  b| bn  b| bn  b| bn  b| TG, TGA
; * @return xmm1     db|dbn db|dbn db|dbn db|dbn db| TG, TGA
; * 
; * @author  1.0 2007/05/22 matsushima
; * @since   1.0 2007/05/22 matsushima
; */
FillPolygonTextureCommon_draw_scan_line macro render_mode
        ; int tx = tx1; // T
        ; int ty = ty1; // T
        movdqa      xmm0, xmm6          ; tx = tx1              ; xmm0| ty2| tx2| ty1| tx1|
        ; int tx2t = tx2; // T
        ; int ty2t = ty2; // T
        ; int dtx = (tx2 - tx1) / pdx; // T
        ; int dty = (ty2 - ty1) / pdx; // T
        pshufd      xmm1, xmm6, 1110b ; ??32                    ; xmm1|    |    | ty2| tx2|
        pshufd      xmm3, xmm6, 1110b ; ??32                    ; xmm3|    |    |ty2t|tx2t|
        psubd       xmm1, xmm0          ; dtx = (tx2 - tx1)
        cvtdq2ps    xmm1, xmm1    ; ps <- dw
        cvtsi2ss    xmm2, eax     ; ss <- dw
        pshufd      xmm2, xmm2, 0 ; ps <- ss
        rcpps       xmm2, xmm2
        mulps       xmm1, xmm2          ;                    / pdx
    if render_mode and (render_alpha or render_gouraud) ; A, G
        ; a = a1; // A
        ; an = an1; // A
        ; b = b1; // G
        ; bn = bn1; // G
        punpcklwd   xmm6, xmm7           ; a = a1               ; xmm6| bn1|  b1| an1|  a1|
        psrld       xmm6, 16
        ; da = (a2 - a1) / pdx; // A
        ; dan = (an2 - an1) / pdx; // A
        ; db = (b2 - b1) / pdx; // G
        ; dbn = (bn2 - bn1) / pdx; // G
        punpckhwd   xmm7, xmm7
        psrld       xmm7, 16            ; da = (a2              ; xmm7| bn2|  b2| an2|  a2|
        psubd       xmm7, xmm6          ;          - a1)
        cvtdq2ps    xmm7, xmm7    ; ps <- dw
        mulps       xmm7, xmm2          ;                / pdx  ; xmm7| dbn|  db| dan|  da|
   endif ; A, G
        ; if (px1 < 0)
        test        edx, edx ; cmp edx, 0
        jge         @f
            ; // 左にはみ出した分をスキップ
            ; tx -= dtx * px1; // T
            ; ty -= dty * px1; // T
            cvtsi2ss    xmm2, edx     ; ss <- dw
            pshufd      xmm2, xmm2, 0 ; ps <- ss
            mulps       xmm2, xmm1          ;       dtx * px1
            cvtps2dq    xmm2, xmm2    ; dw <- ps
            psubd       xmm0, xmm2          ; tx -=
    if render_mode and (render_alpha or render_gouraud) ; A, G
            ; a -= da * px1; // A
            ; an -= dan * px1; // A
            ; b -= db * px1; // G
            ; bn -= dbn * px1; // G
            cvtsi2ss    xmm2, edx     ; ss <- dw
            pshufd      xmm2, xmm2, 0 ; ps <- ss
            mulps       xmm2, xmm7          ;      da * px1
            cvtps2dq    xmm2, xmm2    ; dw <- ps
            psubd       xmm6, xmm2          ; a -=
    endif ; A, G
@@:
        cvtps2dq    xmm1, xmm1 ; dw <- ps
        movdq2q     mm0, xmm0                                   ; mm0|  ty|  tx|
        movdq2q     mm1, xmm1                                   ; mm1| dty| dtx|
        movdq2q     mm3, xmm3                                   ; mm3|ty2t|tx2t|
    if render_mode and (render_alpha or render_gouraud) ; A, G
        cvtps2dq    xmm7, xmm7 ; dw <- ps
         ; 桁あふれ防止切り上げ(dc < 0 のときのみ)
        pxor        xmm2, xmm2
        pcmpgtd     xmm2, xmm7 ; r = (0 > dc) ? -1 : 0          ; xmm7|   r|   r|   r|   r|
        psubd       xmm7, xmm2
    endif ; A, G
        cvtsi2ss    xmm2, eax     ; ss <- dw ; save pdx
        ; int tw16 = tw << 16;
        ; int th16 = th << 16;
        movd        mm4, _tw
        movd        mm5, _th
        punpckldq   mm4, mm5
        pslld       mm4, 16                                     ; mm4|th16|tw16|
        ; // tx, ty の正規化
        ; // tx = [0, tw16)
        ; // ty = [0, th16)
        ; if ((tx < -tw16) || (tx >= tw16))
        ; if ((ty < -th16) || (ty >= th16))
        movq        mm2, mm0
        movq        mm5, mm4
        paddd       mm2, mm4            ; d: if (tx + tw16 < 0) <- (tx < -tw16)
        pcmpgtd     mm5, mm0            ; !s: if (tw16 > tx) <- (tx < tw16) <- !(tx >= tw16)
        pandn       mm2, mm5            ; if (!d && s) <- !(d || !s) { ??????88h }
        pmovmskb    eax, mm2
        not         eax
        test        eax, 88h ; |????????|????????|????????|0???0???|
        jz          @f
            ; tx2t -= tx;
            ; tx %= tw16;
            ; tx2t += tx;
            psubd       mm3, mm0            ; tx2t -= t
            movd        eax, mm0 ; tx
            cdq
            movd        esi, mm4 ; tw16
            idiv        esi                 ; tx %= tw16
            movd        mm5, edx
            ; ty2t -= ty;
            ; ty %= th16;
            ; ty2t += ty;
            pshufw      mm2, mm0, 1110b ; ??32 ; ty
            movd        eax, mm2
            cdq
            pshufw      mm2, mm4, 1110b ; ??32 ; th16
            movd        esi, mm2
            idiv        esi                 ; ty %= th16
            movd        mm2, edx
            punpckldq   mm5, mm2
            movq        mm0, mm5
            paddd       mm3, mm5            ;           - tx
@@:
        ; if (tx < 0)
        pxor        mm2, mm2
        pcmpgtd     mm2, mm0            ; if (0 > tx)
        pand        mm2, mm4
            ; tx += tw16;
            ; tx2t += tw16;
            paddd       mm0, mm2            ; tx += tw16
            paddd       mm3, mm2            ; tx2t += tw16
        ; // 境界線をまたぐか
        ; boolean f = ((tx2t < 0) || (tx2t >= tw16)
        ;           || (ty2t < 0) || (ty2t >= th16));
        movq        mm5, mm4
        movq        mm2, mm3            ; d: if (tx2t < 0)
        pcmpgtd     mm5, mm3            ; !s: if (tw16 > tx2t) <- (tx2t < tw16) <- !(tx2t >= tw16)
        pandn       mm2, mm5            ; if (!d && s) <- !(d || !s) { ??????88h }
        ; if (f)
        pmovmskb    eax, mm2
        not         eax
        test        eax, 88h ; |????????|????????|????????|0???0???|
        ;jz          no_check_boundary
        jz          draw_scan_line
            ; // dtx, dty の正規化
            ; // dtx = [0, tw16)
            ; // dty = [0, th16)
            ; boolean fx = false;
            ; boolean fy = false;
            xor         esi, esi
            ; if ((dtx < -tw16) || (dtx >= tw16))
            ; if ((dty < -th16) || (dty >= th16))
            movq        mm2, mm1
            movq        mm5, mm4
            paddd       mm2, mm4            ; d: if (tx + tw16 < 0) <- (tx < -tw16)
            pcmpgtd     mm5, mm1            ; !s: if (tw16 > tx) <- (tx < tw16) <- !(tx >= tw16)
            pandn       mm2, mm5            ; if (!d && s) <- !(d || !s) { ??????88h }
            pmovmskb    eax, mm2
            not         eax
            test        eax, 88h ; |????????|????????|????????|0???0???|
            jz          @f
                ; dtx %= tw16;
                movd        eax, mm1 ; dtx
                cdq
                movd        esi, mm4 ; tw16
                idiv        esi                 ; dtx %= tw16
                movd        mm5, edx
                ; dty %= th16;
                pshufw      mm2, mm1, 1110b ; ??32 ; dty
                movd        eax, mm2
                cdq
                pshufw      mm2, mm4, 1110b ; ??32 ; th16
                movd        esi, mm2
                idiv        esi                 ; dty %= th16
                movd        mm2, edx
                punpckldq   mm5, mm2
                movq        mm1, mm5
                ; fx = true;
                not         esi
@@:
            ; if (dtx < 0)
            pxor        mm2, mm2
            pcmpgtd     mm2, mm1            ; if (0 > dtx)
                ; fx = true;
                pmovmskb    eax, mm2
                ; dtx += tw16;
                pand        mm2, mm4
                paddd       mm1, mm2            ; dtx += tw16
            ; if (fx)
            or          eax, esi
            jz          @f
                ; tx2t = tx + dtx * pdx;
                punpckldq   xmm2, xmm2 ; restore pdx
movq2dq xmm1, mm1
                cvtdq2ps    xmm3, xmm1 ; dtx
                mulps       xmm3, xmm2
                cvtps2dq    xmm3, xmm3
movdq2q mm3, xmm3
                paddd       mm3, mm0
@@:
            ; // 境界線をまたぐか
            ; f = ((tx2t < 0) || (tx2t >= tw16)
            ;   || (ty2t < 0) || (ty2t >= th16));
            movq        mm5, mm4
            movq        mm2, mm3            ; d: if (tx2t < 0)
            pcmpgtd     mm5, mm3            ; !s: if (tw16 > tx2t) <- (tx2t < tw16) <- !(tx2t >= tw16)
            pandn       mm2, mm5            ; if (!d && s) <- !(d || !s) { ??????88h }
            ; if (f)
            pmovmskb    eax, mm2
            not         eax
            test        eax, 88h ; |????????|????????|????????|0???0???|
            ;jnz         check_boundary
        ; // ループ
draw_scan_line:
        mov         esi, _texture
        mov         eax, 1
        movd        mm2, eax
        pshufw      mm3, mm4, 3 ; th
        punpcklwd   mm2, mm3                ; mm2|      | th  1|
    if render_mode and render_gouraud ; G
        packssdw    xmm0, xmm6              ; xmm0| bn  b| an  a|      |      | <- |    bn|     b|    an|     a|
        packssdw    xmm1, xmm7              ; xmm1|dbn db|dan da|      |      | <- |   dbn|    db|   dan|    da|
        pshufd      xmm0, xmm0, 11111111b   ; xmm0| bn  b| bn  b| bn  b| bn  b| <- | bn  b| an  a|      |      |
        pshufd      xmm1, xmm1, 11111111b   ; xmm1|dbn db|dbn db|dbn db|dbn db| <- |dbn db|dan da|      |      |
        mov         eax, 255
        movd        xmm3, eax
        pshuflw     xmm3, xmm3, 0           ; xmm3|      |      |255 255|255 255|
    endif ; G
    if render_mode and render_alpha ; A
        packssdw    xmm6, xmm6              ; xmm6| bn  b| an  a| bn  b| an  a| <- |    bn|     b|    an|     a|
        packssdw    xmm7, xmm7              ; xmm7|dbn db|dan da|dbn db|dan da| <- |   dbn|    db|   dan|    da|
        pshufd      xmm6, xmm6, 00000000b   ; xmm6| an  a| an  a| an  a| an  a| <- | bn  b| an  a|dbn db|dan da|
        pshufd      xmm7, xmm7, 00000000b   ; xmm7|dan da|dan da|dan da|dan da| <- |dbn db|dan da|dbn db|dan da|
    endif ; A
    if render_mode and (render_alpha or render_gouraud) ; A, G
        pxor        xmm2, xmm2              ; xmm2|      |      |  0  0|  0  0|
    endif ; A, G
        ;jnz         check_boundary
endm

;/**
; * FillPolygonTexture_draw_scanline
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * 
; * @author  1.0 2007/05/18 matsushima
; * @since   1.0 2007/05/18 matsushima
; */
FillPolygonTexture_draw_scan_line macro render_mode
        ; // * FillPolygonTexture_draw_scanline
        ; // * FillPolygonTextureAlpha_draw_scanline
        ; // * FillPolygonTextureGouraud_draw_scanline
        ; // * FillPolygonTextureGouraudAlpha_draw_scanline
        ; // * の共通部分。
        FillPolygonTextureCommon_draw_scan_line render_mode
        ; // ループ
        jnz         check_boundary
no_check_boundary:
        check_boundary_flag = 0         ; no_check_boundary
        draw_scan_line_left     FillPolygonTexture_draw_scan_line_left, 8, %check_boundary_flag
        movq        mm3, mm0
        paddd       mm3, mm1                                    ; mm3|ty+dty|tx+dtx|
        pslld       mm1, 1                                      ; mm1| 2*dty| 2*dtx|
        draw_scan_line_center   FillPolygonTexture_draw_scan_line_center, 8, %check_boundary_flag
        psrad       mm1, 1                                      ; mm1|   dty|   dtx|
        draw_scan_line_right    FillPolygonTexture_draw_scan_line_left, 8, %check_boundary_flag
        jmp         check_boundary_end
check_boundary:
        check_boundary_flag = 1         ; check_boundary
        movq        mm3, mm4                                    ; mm3|  th16|  tw16|
        draw_scan_line_left     FillPolygonTexture_draw_scan_line_left, 8, %check_boundary_flag
        draw_scan_line_center   FillPolygonTexture_draw_scan_line_center, 8, %check_boundary_flag
        draw_scan_line_right    FillPolygonTexture_draw_scan_line_left, 8, %check_boundary_flag
check_boundary_end:
endm

FillPolygonTexture_draw_scan_line_left macro off
        ; int x = tx >> 16; // T
        ; int y = ty >> 16; // T
        pshufw      mm4, mm0, 1101b ; ??32                      ; mm4|    | y x| <- | y  | x  |
        ; pixOff[p] = texture[x + y * tw]; // T
        pmaddwd     mm4, mm2                ;                    [x + y * tw]
        movd        eax, mm4
        mov         eax, [esi + eax * 4]    ;             texture
        ; tx += dtx; // T
        ; ty += dty; // T
        paddd       mm0, mm1
        mov         [off], eax              ; pixOff[p] =
    if check_boundary_flag eq 1     ; check_boundary
        ; if (tx >= tw16) // T
        ; if (ty >= th16) // T
        movq        mm4, mm3
        pcmpgtd     mm4, mm0            ; !d: if (tw16 > tx) <- (tx < tw16) <- !(tx >= tw16)
        pandn       mm4, mm3
            ; tx -= tw16; // T
            ; ty -= th16; // T
            psubd       mm0, mm4
    endif
endm

FillPolygonTexture_draw_scan_line_center macro off1, off2
    if check_boundary_flag eq 0     ; no_check_boundary
        ; int x = tx >> 16;
        ; int y = ty >> 16;
        pshufw      mm4, mm0, 1101b ; ??32                      ; mm4|    | y x| <- | y  | x  |
        pshufw      mm5, mm3, 1101b ; ??32                      ; mm5|    | y x| <- | y  | x  |
        ; pixOff[p] = texture[x + y * tw]; // T
        pmaddwd     mm4, mm2                ;                    [x + y * tw]
        pmaddwd     mm5, mm2                ;                    [x + y * tw]
        movd        eax, mm4
        movd        edx, mm5
        movd        mm4, [esi + eax * 4]    ;             texture
        ; tx += dtx; // T
        ; ty += dty; // T
        paddd       mm0, mm1
        punpckldq   mm4, [esi + edx * 4]    ;             texture
        paddd       mm3, mm1
        movq        [off1], mm4             ; pixOff[p] =
    else                            ; check_boundary
        FillPolygonTexture_draw_scan_line_left off1
        FillPolygonTexture_draw_scan_line_left off2
    endif
endm

;/**
; * FillPolygonTextureAlpha_draw_scanline
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * 
; * @author  1.0 2008/02/17 matsushima
; * @since   1.0 2008/02/17 matsushima
; */
FillPolygonTextureAlpha_draw_scan_line macro render_mode
        movdqa      sxmm6, xmm6
        movdqa      sxmm7, xmm7
        ; // * FillPolygonTexture_draw_scanline
        ; // * FillPolygonTextureAlpha_draw_scanline
        ; // * FillPolygonTextureGouraud_draw_scanline
        ; // * FillPolygonTextureGouraudAlpha_draw_scanline
        ; // * の共通部分。
        FillPolygonTextureCommon_draw_scan_line render_mode
        ; // ループ
        jnz         check_boundary
no_check_boundary:
        check_boundary_flag = 0         ; no_check_boundary
        draw_scan_line_all      FillPolygonTextureAlpha_draw_scan_line_left, %check_boundary_flag
        jmp         check_boundary_end
check_boundary:
        check_boundary_flag = 1         ; check_boundary
        movq        mm3, mm4                                    ; mm3|  th16|  tw16|
        draw_scan_line_all      FillPolygonTextureAlpha_draw_scan_line_left, %check_boundary_flag
check_boundary_end:
        movdqa      xmm6, sxmm6
        movdqa      xmm7, sxmm7
endm

FillPolygonTextureAlpha_draw_scan_line_left macro off
        ; int x = tx >> 16; // T
        ; int y = ty >> 16; // T
        pshufw      mm4, mm0, 1101b ; ??32                      ; mm4|    | y x| <- | y  | x  |
        ; int color = texture[x + y * tw]; // A
        pmaddwd     mm4, mm2                ;                    [x + y * tw]
        movd        eax, mm4
        movd        xmm4, [esi + eax * 4]   ; color = texture
        ; int r = (color >> 16) & 0xff; // A
        ; int g = (color >> 8) & 0xff; // A
        ; int b = (color >> 0) & 0xff; // A
        punpcklbw   xmm4, xmm2                                  ; xmm4|    |    | a r| g b| <- |    |    |    |argb|
        ; // s = s * _a
        ; int _a = a >> 8; // 0000ffff <- 00ffffff // A
        ; int _an = an >> 8; // 0000ffff <- 00ffffff // A
        ; r = r * _a; // 00ffffff <- 000000ff * 0000ffff // A
        ; g = g * _a; // 00ffffff <- 000000ff * 0000ffff // A
        ; b = b * _a; // 00ffffff <- 000000ff * 0000ffff // A
        ; // d = s + (d * _an)
        ; int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // A
        ; int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // A
        ; int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // A
        movd        xmm5, [off]                                 ; xmm5|      |      |      | AR GB|
        punpcklbw   xmm5, xmm2                                  ; xmm5|      |      |  A  R|  G  B|
        punpcklwd   xmm4, xmm5                                  ; xmm4|  A  a|  R  r|  G  g|  B  b|
        pmaddwd     xmm4, xmm6                                  ; xmm4|Aan+aa|Ran+ra|Gan+ga|Ban+ba|
        psrld       xmm4, 15 ; 000000ff <- 007fffff
        ; tx += dtx; // T
        ; ty += dty; // T
        paddd       mm0, mm1
        ; pixOff[p] // A
        ;     = 0xff000000 // A
        ;     | ((_r      ) & 0x00ff0000) // A
        ;     | ((_g >>  8) & 0x0000ff00) // A
        ;     | ((_b >> 16) & 0x000000ff); // A
        packssdw    xmm4, xmm4                                  ; xmm4|    |    | a r| g b| <- |   a|   r|   g|   b|
        packuswb    xmm4, xmm4                                  ; xmm4|    |    |    |argb| <- |    |    | a r| g b|
        ; a += da; // A
        ; an += dan; // A
        paddd       xmm6, xmm7          ; a += da
        ; pixOff[p] // A
        ;     = 0xff000000 // A
        ;     | ((_r      ) & 0x00ff0000) // A
        ;     | ((_g >>  8) & 0x0000ff00) // A
        ;     | ((_b >> 16) & 0x000000ff); // A
        movd         [off], xmm4            ; pixOff[p] =
    if check_boundary_flag eq 1     ; check_boundary
        ; if (tx >= tw16) // T
        ; if (ty >= th16) // T
        movq        mm4, mm3
        pcmpgtd     mm4, mm0            ; !d: if (tw16 > tx) <- (tx < tw16) <- !(tx >= tw16)
        pandn       mm4, mm3
            ; tx -= tw16; // T
            ; ty -= th16; // T
            psubd       mm0, mm4
    endif
endm

;/**
; * FillPolygonTextureGouraud_draw_scanline
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * 
; * @author  1.0 2007/05/22 matsushima
; * @since   1.0 2007/05/22 matsushima
; */
FillPolygonTextureGouraud_draw_scan_line macro render_mode
        movdqa      sxmm6, xmm6
        movdqa      sxmm7, xmm7
        ; // * FillPolygonTexture_draw_scanline
        ; // * FillPolygonTextureAlpha_draw_scanline
        ; // * FillPolygonTextureGouraud_draw_scanline
        ; // * FillPolygonTextureGouraudAlpha_draw_scanline
        ; // * の共通部分。
        FillPolygonTextureCommon_draw_scan_line render_mode
        ; // ループ
        jnz         check_boundary
no_check_boundary:
        check_boundary_flag = 0         ; no_check_boundary
        draw_scan_line_left     FillPolygonTextureGouraud_draw_scan_line_left, 16, %check_boundary_flag
        movq        mm3, mm0
        paddd       mm3, mm1                                    ; mm3|ty+dty|tx+dtx|
        pslld       mm1, 1                                      ; mm1| 2*dty| 2*dtx|
        draw_scan_line_center   FillPolygonTextureGouraud_draw_scan_line_center, 16, %check_boundary_flag
        psrad       mm1, 1                                      ; mm1|   dty|   dtx|
        draw_scan_line_right    FillPolygonTextureGouraud_draw_scan_line_left, 16, %check_boundary_flag
        jmp         check_boundary_end
check_boundary:
        check_boundary_flag = 1         ; check_boundary
        movq        mm3, mm4                                    ; mm3|  th16|  tw16|
        draw_scan_line_all      FillPolygonTextureGouraud_draw_scan_line_left, %check_boundary_flag
check_boundary_end:
        movdqa      xmm6, sxmm6
        movdqa      xmm7, sxmm7
endm

FillPolygonTextureGouraud_draw_scan_line_left macro off
        ; int x = tx >> 16; // T
        ; int y = ty >> 16; // T
        pshufw      mm4, mm0, 1101b ; ??32                      ; mm4|    | y x| <- | y  | x  |
        ; int color = texture[x + y * tw]; // G
        pmaddwd     mm4, mm2                ;                    [x + y * tw]
        movd        eax, mm4
        movd        xmm4, [esi + eax * 4]   ; color = texture
        ; int _r = (color >> 16) & 0xff; // G
        ; int _g = (color >> 8) & 0xff; // G
        ; int _b = (color >> 0) & 0xff; // G
        punpcklbw   xmm4, xmm2                                  ; xmm4|    |    | a r| g b| <- |    |    |    |argb|
        ; // d = (s * b) + ((255 - s) * bn)
        ; _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
        ; _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
        ; _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
        movdqa      xmm5, xmm3          ; 255 -
        psubw       xmm5, xmm4          ;       c
        punpcklwd   xmm4, xmm5                                  ; xmm4|255-a        a|255-r    r|255-g    g|255-b    b|
        pmaddwd     xmm4, xmm0                                  ; xmm4|a*b+(255-a)*bn|r...      |g...      |b...      |
        psrld       xmm4, 15 ; 000000ff <- 007fffff             ; xmm4|   a|   r|   g|   b| <- | a  | r  | g  | b  |
        ; tx += dtx; // T
        ; ty += dty; // T
        paddd       mm0, mm1
        ; pixOff[p] = 0xff000000 | (_r << 16) | (_g << 8) | _b; // G
        packssdw    xmm4, xmm4                                  ; xmm4|    |    | a r| g b| <- |   a|   r|   g|   b|
        packuswb    xmm4, xmm4                                  ; xmm4|    |    |    |argb| <- |    |    | a r| g b|
        ; b += db; // G
        ; bn += dbn; // G
        paddw       xmm0, xmm1          ; b += db
        ; pixOff[p] = 0xff000000 | (_r << 16) | (_g << 8) | _b; // G
        movd         [off], xmm4             ; pixOff[p] =
    if check_boundary_flag eq 1     ; check_boundary
        ; if (tx >= tw16) // T
        ; if (ty >= th16) // T
        movq        mm4, mm3
        pcmpgtd     mm4, mm0            ; !d: if (tw16 > tx) <- (tx < tw16) <- !(tx >= tw16)
        pandn       mm4, mm3
            ; tx -= tw16; // T
            ; ty -= th16; // T
            psubd       mm0, mm4
    endif
endm

FillPolygonTextureGouraud_draw_scan_line_center macro off1, off2
    for cnt2, <0, 1>
        xm47        textequ @catstr(xmm, %cnt2 * 3 + 4)         ; xmm4, xmm7
        ; int x = tx >> 16; // T
        ; int y = ty >> 16; // T
        pshufw      mm4, mm0, 1101b ; ??32                      ; mm4|    | y x| <- | y  | x  |
        pshufw      mm5, mm3, 1101b ; ??32                      ; mm5|    | y x| <- | y  | x  |
        ; int color = texture[x + y * tw]; // G
        pmaddwd     mm4, mm2                ;                    [x + y * tw]
        pmaddwd     mm5, mm2                ;                    [x + y * tw]
        movd        eax, mm4
        movd        edx, mm5
        movd        xm47, [esi + eax * 4]   ; color = texture
        movd        xmm6, [esi + edx * 4]   ; color = texture
        ; int _r = (color >> 16) & 0xff; // G
        ; int _g = (color >> 8) & 0xff; // G
        ; int _b = (color >> 0) & 0xff; // G
        punpcklbw   xm47, xmm2                                  ; xm47|    |    | a r| g b| <- |    |    |    |argb|
        punpcklbw   xmm6, xmm2                                  ; xmm6|    |    | a r| g b| <- |    |    |    |argb|
        ; // d = (s * b) + ((255 - s) * bn)
        ; _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
        ; _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
        ; _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
        movdqa      xmm5, xmm3          ; 255 -
        psubw       xmm5, xm47          ;       c
        punpcklwd   xm47, xmm5                                  ; xm47|255-a        a|255-r    r|255-g    g|255-b    b|
        movdqa      xmm5, xmm3          ; 255 -
        psubw       xmm5, xmm6          ;       c
        punpcklwd   xmm6, xmm5                                  ; xmm6|255-a        a|255-r    r|255-g    g|255-b    b|
        pmaddwd     xm47, xmm0                                  ; xm47|a*b+(255-a)*bn|r...      |g...      |b...      |
        paddd       xmm0, xmm1          ; b += db
        pmaddwd     xmm6, xmm0                                  ; xmm6|a*b+(255-a)*bn|r...      |g...      |b...      |
        psrld       xm47, 15 ; 000000ff <- 007fffff             ; xm47|   a|   r|   g|   b| <- | a  | r  | g  | b  |
        psrld       xmm6, 15 ; 000000ff <- 007fffff             ; xmm6|   a|   r|   g|   b| <- | a  | r  | g  | b  |
        ; tx += dtx; // T
        ; ty += dty; // T
        paddd       mm0, mm1
        paddd       mm3, mm1
        ; pixOff[p] = 0xff000000 | (_r << 16) | (_g << 8) | _b; // G
        packssdw    xm47, xmm6                                  ; xm47| a r| g b| a r| g b| <- |   a|   r|   g|   b|
        ; b += db; // G
        ; bn += dbn; // G
        paddw       xmm0, xmm1          ; b += db
    if cnt2 eq 1
        ; pixOff[p] = 0xff000000 | (_r << 16) | (_g << 8) | _b; // G
        packuswb    xmm4, xmm7                                  ; xmm4|argb|argb|argb|argb| <- | a r| g b| a r| g b|
        movdqa      [off1], xmm4            ; pixOff[p] =
    endif
    endm
endm

;/**
; * FillPolygonTextureGouraudAlpha_draw_scanline
; * 
; * @param  edx     px1
; * @param  eax     pdx
; * @param  ebx     p2
; * @param  ecx     -dp
; * 
; * @author  1.0 2007/05/24 matsushima
; * @since   1.0 2007/05/24 matsushima
; */
FillPolygonTextureGouraudAlpha_draw_scan_line macro render_mode
        movdqa      sxmm6, xmm6
        movdqa      sxmm7, xmm7
        ; // * FillPolygonTexture_draw_scanline
        ; // * FillPolygonTextureAlpha_draw_scanline
        ; // * FillPolygonTextureGouraud_draw_scanline
        ; // * FillPolygonTextureGouraudAlpha_draw_scanline
        ; // * の共通部分。
        FillPolygonTextureCommon_draw_scan_line render_mode
        ; // ループ
        jnz         check_boundary
no_check_boundary:
        check_boundary_flag = 0         ; no_check_boundary
        draw_scan_line_all      FillPolygonTextureGouraudAlpha_draw_scan_line_left, %check_boundary_flag
        jmp         check_boundary_end
check_boundary:
        check_boundary_flag = 1         ; check_boundary
        movq        mm3, mm4                                    ; mm3|  th16|  tw16|
        draw_scan_line_all      FillPolygonTextureGouraudAlpha_draw_scan_line_left, %check_boundary_flag
check_boundary_end:
        movdqa      xmm6, sxmm6
        movdqa      xmm7, sxmm7
endm

FillPolygonTextureGouraudAlpha_draw_scan_line_left macro off
        ; int x = tx >> 16; // T
        ; int y = ty >> 16; // T
        pshufw      mm4, mm0, 1101b ; ??32                      ; mm4|    | y x| <- | y  | x  |
        ; int color = texture[x + y * tw]; // GA
        pmaddwd     mm4, mm2                ;                    [x + y * tw]
        movd        eax, mm4
        movd        xmm4, [esi + eax * 4]   ; color = texture
        ; int _r = (color >> 16) & 0xff; // G
        ; int _g = (color >> 8) & 0xff; // G
        ; int _b = (color >> 0) & 0xff; // G
        punpcklbw   xmm4, xmm2                                  ; xmm4|    |    | a r| g b| <- |    |    |    |argb|
        ; // s = (s * b) + ((255 - s) * bn)
        ; _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
        ; _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
        ; _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
        movdqa      xmm5, xmm3          ; 255 -
        psubw       xmm5, xmm4          ;       c
        punpcklwd   xmm4, xmm5                                  ; xmm4|255-a        a|255-r    r|255-g    g|255-b    b|
        pmaddwd     xmm4, xmm0                                  ; xmm4|a*b+(255-a)*bn|r...      |g...      |b...      |
        psrld       xmm4, 15 ; 000000ff <- 007fffff             ; xmm4|   a|   r|   g|   b| <- | a  | r  | g  | b  |
        packssdw    xmm4, xmm4                                  ; xmm4|    |    | a r| g b| <- |   a|   r|   g|   b|
        ; // s = s * _a
        ; int _a = a >> 8; // 0000ffff <- 00ffffff // A
        ; int _an = an >> 8; // 0000ffff <- 00ffffff // A
        ; _r *= _a; // 00ffffff <- 000000ff * 0000ffff // A
        ; _g *= _a; // 00ffffff <- 000000ff * 0000ffff // A
        ; _b *= _a; // 00ffffff <- 000000ff * 0000ffff // A
        ; // d = s + (d * _an)
        ; _r += ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // A
        ; _g += ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // A
        ; _b += ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // A
        movd        xmm5, [off]                                 ; xmm5|      |      |      | AR GB|
        punpcklbw   xmm5, xmm2                                  ; xmm5|      |      |  A  R|  G  B|
        punpcklwd   xmm4, xmm5                                  ; xmm4|  A  a|  R  r|  G  g|  B  b|
        pmaddwd     xmm4, xmm6                                  ; xmm4|Aan+aa|Ran+ra|Gan+ga|Ban+ba|
        psrld       xmm4, 15 ; 0000ff <- 7fffff
        ; tx += dtx; // T
        ; ty += dty; // T
        paddd       mm0, mm1
        ; pixOff[p] // GA
        ;     = 0xff000000 // GA
        ;     | ((_r      ) & 0x00ff0000) // GA
        ;     | ((_g >>  8) & 0x0000ff00) // GA
        ;     | ((_b >> 16) & 0x000000ff); // GA
        packssdw    xmm4, xmm4                                  ; xmm4|    |    | a r| g b| <- |   a|   r|   g|   b|
        packuswb    xmm4, xmm4                                  ; xmm4|    |    |    |argb| <- |    |    | a r| g b|
        ; b += db; // G
        ; bn += dbn; // G
        paddw       xmm0, xmm1          ; b += db
        ; a += da; // A
        ; an += dan; // A
        paddw       xmm6, xmm7          ; a += da
        ; pixOff[p] // GA
        ;     = 0xff000000 // GA
        ;     | ((_r      ) & 0x00ff0000) // GA
        ;     | ((_g >>  8) & 0x0000ff00) // GA
        ;     | ((_b >> 16) & 0x000000ff); // GA
       movd         [off], xmm4            ; pixOff[p] =
    if check_boundary_flag eq 1     ; check_boundary
        ; if (tx >= tw16) // T
        ; if (ty >= th16) // T
        movq        mm4, mm3
        pcmpgtd     mm4, mm0            ; !d: if (tw16 > tx) <- (tx < tw16) <- !(tx >= tw16)
        pandn       mm4, mm3
            ; tx -= tw16; // T
            ; ty -= th16; // T
            psubd       mm0, mm4
    endif
endm

;/**
; * new_point
; * if (y >= py[i1]) // 左: 新しい頂点に到達
; * if (y >= py[i2]) // 右: 新しい頂点に到達
; * 
; * @param  _i1         _i1/_i2
; * @param  _y1_next    _y1_next/_y2_next
; * @param  sgn         -/+
; * @param  macro_end   new_point_left_end/new_point_right_end
; * @return mm0      x1/  x2 ->  mm6:   x|       x2|     x1|
; * @return mm1     dx1/ dx2 ->  mm7:  dx|      dx2|    dx1|
; * @return xmm4     c1/  c2 -> xmm6:   c|( an2) r2|  g2 b2|( an1) r1|  g1 b1| (GA) G, GA
; * @return xmm5    dc1/ dc2 -> xmm7:  dc|(dan2)dr2| dg2db2|(dan1)dr1| dg1db1| (GA) G, GA
; * @return xmm4    tx1/ tx2 -> xmm6:  tx|      ty2|    tx2|      ty1|    tx1| T
; * @return xmm5   dtx1/dtx2 -> xmm7: dtx|     dty2|   dtx2|     dty1|   dtx1| T (TA, TG, TGA は xmm7 -> dtx)
; * @return xmm0    tc1/ tc2 -> xmm7:  tc|   bn2 b2| an2 a2|   bn1 b1| an1 a1| TA, TG, TGA
; * @return xmm1   dtc1/dtc2 ->  dtc: dtc|  dbn2db2|dan2da2|  dbn1db1|dan1da1| TA, TG, TGA
; * 
; * @author  1.0 2007/04/24 matsushima
; * @since   1.0 2007/04/24 matsushima
; */
new_point macro _i1, _y1_next, sgn, macro_end, render_mode
        ; if (y >= py[i1]) // 左: 新しい頂点に到達
        cmp         ecx, _y1_next
        jl          macro_end
            ; do { ++ i1; } while (y >= py[i1]); // y 方向に変化しないならスキップ
            mov         ebx, _i1
@@:
                add         ebx, -(sgn sizeof VERT)
                mov         eax, [ebx].VERT._y
                cmp         ecx, eax            ; y >= py[i1]
                jge         @b
            mov         _i1, ebx
            mov         _y1_next, eax
            ; int dy = py[i1] - py[i1 - 1];
            sub         eax, [ebx sgn sizeof VERT].VERT._y
            cvtsi2ss    xmm2, eax     ; ss <- dw
            pshufd      xmm2, xmm2, 0 ; ps <- ss
; mm0      x1/  x2 ->  mm6:   x|       x2|     x1|
; mm1     dx1/ dx2 ->  mm7:  dx|      dx2|    dx1|
            ; x1 = px[i1 - 1] << 16;
            mov         eax, [ebx sgn sizeof VERT].VERT._x
            sal         eax, 16
            movd        mm4, eax
            ; dx1 = ((px[i1] - px[i1 - 1]) << 16) / dy;
            mov         edx, [ebx].VERT._x
            sal         edx, 16
            sub         edx, eax
            cvtsi2ss    xmm0, edx ; ss <- dw
            rcpps       xmm2, xmm2
            mulss       xmm0, xmm2
            cvtss2si    edx, xmm0
            movd        mm5, edx
            ; new_point_left(i1, dy);
ife render_mode and render_texture ; !T
    if  (render_mode and (render_gouraud or render_alpha)) eq render_gouraud ; G
; xmm4     c1/  c2 -> xmm6:   c|( an2) r2|  g2 b2|( an1) r1|  g1 b1| (GA) G, GA
; xmm5    dc1/ dc2 -> xmm7:  dc|(dan2)dr2| dg2db2|(dan1)dr1| dg1db1| (GA) G, GA
            ; a1 = (pc[i1 - 1] >>  8) & 0x00ff0000; // A
            ; r1 = (pc[i1 - 1]      ) & 0x00ff0000; // G
            ; g1 = (pc[i1 - 1] <<  8) & 0x00ff0000; // G
            ; b1 = (pc[i1 - 1] << 16) & 0x00ff0000; // G
            movd        xmm4, [ebx sgn sizeof VERT].VERT._c ; c1 = pc[i1 - 1]
            ; dr1 = (((pc[i1]      ) & 0x00ff0000) - r1) / dy; // G
            ; dg1 = (((pc[i1] <<  8) & 0x00ff0000) - g1) / dy; // G
            ; db1 = (((pc[i1] << 16) & 0x00ff0000) - b1) / dy; // G
            movd        xmm5, [ebx].VERT._c                 ; db1 = (pc[i1]
            punpcklbw   xmm4, xmm4 ; ffff <- ff
            punpcklbw   xmm5, xmm5 ; ffff <- ff
            punpcklwd   xmm4, xmm4 ; ffffffff <- ffff
            punpcklwd   xmm5, xmm5 ; ffffffff <- ffff
            psrld       xmm4, 17   ; 00007fff <- ffffffff ; 符号ビット 0
            psrld       xmm5, 17   ; 00007fff <- ffffffff ; 符号ビット 0
            psubd       xmm5, xmm4                          ;               - b1)
            cvtdq2ps    xmm5, xmm5 ; ps <- dw
            mulps       xmm5, xmm2                          ;                     / dy
            cvtps2dq    xmm5, xmm5 ; dw <- ps
            packssdw    xmm4, xmm4 ; 7fff <- 00007fff
            packssdw    xmm5, xmm5 ; 7fff <- 00007fff
            ; 桁あふれ防止切り上げ(dc < 0 のときのみ)
            pxor        xmm2, xmm2
            pcmpgtw     xmm2, xmm5 ; r = (0 > dc) ? -1 : 0      ; xmm2|    |    | r r| r r|
            psubsw      xmm5, xmm2
    elseif (render_mode and (render_gouraud or render_alpha)) eq (render_gouraud or render_alpha) ; GA
; xmm4     c1/  c2 -> xmm6:   c|( an2) r2|  g2 b2|( an1) r1|  g1 b1| (GA) G, GA
; xmm5    dc1/ dc2 -> xmm7:  dc|(dan2)dr2| dg2db2|(dan1)dr1| dg1db1| (GA) G, GA
            ; int a11 = (pc[i1 - 1] >> 24) & 0x000000ff; // A
            ; int r11 = (pc[i1 - 1] >> 16) & 0x000000ff; // G
            ; int g11 = (pc[i1 - 1] >>  8) & 0x000000ff; // G
            ; int b11 = (pc[i1 - 1]      ) & 0x000000ff; // G
            movd        xmm4, [ebx sgn sizeof VERT].VERT._c ; c1 = pc[i1 - 1]
            ; int a12 = (pc[i1    ] >> 24) & 0x000000ff; // A
            ; int r12 = (pc[i1    ] >> 16) & 0x000000ff; // G
            ; int g12 = (pc[i1    ] >>  8) & 0x000000ff; // G
            ; int b12 = (pc[i1    ]      ) & 0x000000ff; // G
            movd        xmm5, [ebx].VERT._c                 ; db1 = (pc[i1]
            pxor        xmm3, xmm3
            punpcklbw   xmm4, xmm3 ; 00ff <- ff                 ; xmm4|    |    |a1r1|g1b1|
            punpcklbw   xmm5, xmm3 ; 00ff <- ff                 ; xmm5|    |    |a1r1|g1b1|
            punpcklwd   xmm4, xmm3 ; 000000ff <- 00ff           ; xmm4|  a1|  r1|  g1|  b1|
            punpcklwd   xmm5, xmm3 ; 000000ff <- 00ff           ; xmm5|  a1|  r1|  g1|  b1|
            cvtdq2ps    xmm4, xmm4 ; ps <- dw
            cvtdq2ps    xmm5, xmm5 ; ps <- dw
            ; int t11 = (a11 << 8) | a11; // A
            ; int t12 = (a12 << 8) | a12; // A
            movdqa      xmm0, xmm4                              ; xmm0|  a1|  r1|  g1|  b1|
            movdqa      xmm1, xmm5                              ; xmm1|  a1|  r1|  g1|  b1|
            mov         eax, -257
            cvtsi2ss    xmm0, eax                               ; xmm0|  a1|  r1|  g1|-257|
            cvtsi2ss    xmm1, eax                               ; xmm1|  a1|  r1|  g1|-257|
            pshufd      xmm0, xmm0, 00111111b ; ?333            ; xmm0|-257|  r1|  g1|  b1|
            pshufd      xmm1, xmm1, 00111111b ; ?333            ; xmm1|-257|  r1|  g1|  b1|
            ; r1 = r11 * t11;
            ; g1 = g11 * t11;
            ; b1 = b11 * t11;
            mulps       xmm4, xmm0                              ; xmm4|   -a1a1|   r1*a1|   g1*a1|   b1*a1|
            mulps       xmm5, xmm1                              ; xmm5|   -a1a1|   r1*a1|   g1*a1|   b1*a1|
            ; dr1 = ((r12 * t12) - r1) / dy; // ffffff
            ; dg1 = ((g12 * t12) - g1) / dy; // ffffff
            ; db1 = ((b12 * t12) - b1) / dy; // ffffff
            ; dan1 = ((-t12) - (-t11)) / dy; // (an12 - an11) / py // A
            subps       xmm5, xmm4
            mulps       xmm5, xmm2
            cvtps2dq    xmm4, xmm4 ; dw <- ps
            cvtps2dq    xmm5, xmm5 ; dw <- ps
            ; an1 = 0x00ffffff - t11; // 255 - a11 // A
            mov         eax, 65535
            movd        xmm0, eax
            pshufd      xmm0, xmm0, 00010101b ; 0111            ; xmm0|0000ffff     |       0|       0|       0|
            paddd       xmm4, xmm0                              ; xmm4|0000ffff-a1a1|   r1*a1|   g1*a1|   b1*a1|
            psrld       xmm4, 1 ; 00007fff <- 0000ffff ; 符号ビット 0
            psrad       xmm5, 1 ; 00007fff <- 0000ffff ; 符号拡張 +-
            packssdw    xmm4, xmm4
            packssdw    xmm5, xmm5
            ; 桁あふれ防止切り上げ(dc < 0 のときのみ)
            pxor        xmm2, xmm2
            pcmpgtw     xmm2, xmm5 ; r = (0 > dc) ? -1 : 0      ; xmm2|    |    | r r| r r|
            psubsw      xmm5, xmm2
    endif ; G
else ; !T -> T
; JavaRenderMemorySSE2_fillPolygonTextureCommon
; xmm4    tx1/ tx2 -> xmm6:  tx|      ty2|    tx2|      ty1|    tx1| T
; xmm5   dtx1/dtx2 -> xmm7: dtx|     dty2|   dtx2|     dty1|   dtx1| T (TA, TG, TGA は xmm7 -> dtx)
            ; tx1 = ptx[i1 - 1] << 16; // T
            ; ty1 = pty[i1 - 1] << 16; // T
            movd        xmm4, [ebx sgn sizeof VERT].VERT._tx ; tx1 = ptx[i1 - 1]
            movd        xmm0, [ebx sgn sizeof VERT].VERT._ty ; ty1 = pty[i1 - 1]
            ; dtx1 = ((ptx[i1] - ptx[i1 - 1]) << 16) / dy; // T
            ; dty1 = ((pty[i1] - pty[i1 - 1]) << 16) / dy; // T
            movd        xmm5, [ebx].VERT._tx                 ; dtx1 = ((ptx[i1]
            movd        xmm1, [ebx].VERT._ty                 ; dty1 = ((pty[i1]
            punpckldq   xmm4, xmm0                              ; xmm4|    |    | ty1| tx1|
            punpckldq   xmm5, xmm1                              ; xmm5|    |    |dty1|dtx1|
            psubd       xmm5, xmm4                           ;                  - tx1)
            pslld       xmm4, 16 ; ffff0000 <- 0000ffff      ;                   << 16
            pslld       xmm5, 16 ; ffff0000 <- 0000ffff      ;                        << 16)
            cvtdq2ps    xmm5, xmm5 ; ps <- dw
            mulps       xmm5, xmm2                           ;                               / dy
            cvtps2dq    xmm5, xmm5 ; dw <- ps
    if render_mode and render_alpha ; TA
; xmm0    tc1/ tc2 -> xmm7:  tc|   bn2 b2| an2 a2|   bn1 b1| an1 a1| TA, TG, TGA
; xmm1   dtc1/dtc2 ->  dtc: dtc|  dbn2db2|dan2da2|  dbn1db1|dan1da1| TA, TG, TGA
            ; int a11 = (pc[i1 - 1] >> 24) & 0x000000ff; // A
            ; int a12 = (pc[i1    ] >> 24) & 0x000000ff; // A
            mov         esi, [ebx sgn sizeof VERT].VERT._c  ; a11 = pc[i1 - 1]
            mov         edi, [ebx].VERT._c                  ; a12 = pc[i1]
            ; a11 = (a11 << 8) | a11; // A
            ; a12 = (a12 << 8) | a12; // A
            ; a11 = (a11 << 8) | a11; // A
            ; a12 = (a12 << 8) | a12; // A
            shr         esi, 17 + 8 ; 0000007f <- ff000000
            shr         edi, 17 + 8 ; 0000007f <- ff000000
            shl         esi, 8      ; 00007f00
            shl         edi, 8      ; 00007f00
            ; a1 = a11; // A
            ; an1 = 0x00ffffff - a11; // 255 - a11 // A
            movd        mm0, esi       ; a = a11
            mov         eax, 00007f00h
            sub         eax, esi
            movd        mm1, eax       ; an = 255 - a11
            punpckldq   mm0, mm1                                ; mm0|  an|   a|
            ; da1 = (a12 - a11) / dy; // A
            ; dan1 = ((-a12) - (-a11)) / dy; // A
            sub         edi, esi
            movd        mm1, edi       ; da = (a12 - a11)
            neg         edi
            movd        mm2, edi       ; dan = ((-a12) - (-a11))
            punpckldq   mm1, mm2                                ; mm1| dan|  da|
            movq2dq     xmm0, mm0                               ; xmm0|    |    |  an|   a|
            movq2dq     xmm1, mm1                               ; xmm1|    |    | dan|  da|
    endif ; TA
    if render_mode and render_gouraud ; TG
; xmm0    tc1/ tc2 -> xmm7:  tc|   bn2 b2| an2 a2|   bn1 b1| an1 a1| TA, TG, TGA
; xmm1   dtc1/dtc2 ->  dtc: dtc|  dbn2db2|dan2da2|  dbn1db1|dan1da1| TA, TG, TGA
            mov         esi, _b_tbl
            ; b1   =   b_tbl[pc[i1 - 1] & 0x00ffffff][255] << 8; // G
            ; bn1  =   b_tbl[pc[i1 - 1] & 0x00ffffff][  0] << 8; // G
            ; db1  = ((b_tbl[pc[i1    ] & 0x00ffffff][255] << 8) - b1 ) / dy; // G
            ; dbn1 = ((b_tbl[pc[i1    ] & 0x00ffffff][  0] << 8) - bn1) / dy; // G
            mov         edx, [ebx sgn sizeof VERT].VERT._c  ;          pc[i1 - 1] & 0x00ffffff
            shl         edx, 8
            movd        mm0, [esi + edx * 4 + 255 * 4]  ; b1   = b_tbl[  ][255]
           ;movd        mm3, [esi + edx * 4 + 1 * 4]    ; bn1  = b_tbl[  ][  0] ; オーバーフロー防止 [1] <- [0]
            movd        mm3, [esi + edx * 4 + 0 * 4]    ; bn1  = b_tbl[  ][  0]
            punpckldq   mm0, mm3                                ; mm0| bn|  b|
            mov         edx, [ebx].VERT._c              ;              pc[i1] & 0x00ffffff
            shl         edx, 8
            movd        mm1, [esi + edx * 4 + 255 * 4]  ; db2  = b_tbl[  ][255]
           ;movd        mm3, [esi + edx * 4 + 1 * 4]    ; dbn2 = b_tbl[  ][  0] ; オーバーフロー防止 [1] <- [0]
            movd        mm3, [esi + edx * 4 + 0 * 4]    ; dbn2 = b_tbl[  ][  0]
            punpckldq   mm1, mm3                                ; mm1|dbn| db|
            pslld       mm0, 8
            pslld       mm1, 8
            psubd       mm1, mm0
            psrld       mm0, 1 ; 00007fff <- 0000ffff ; 符号ビット 0
            psrad       mm1, 1 ; 00007fff <- 0000ffff ; 符号拡張 +-
            movq2dq     xmm3, mm0
            punpcklqdq  xmm0, xmm3                              ; xmm0| bn|  b|  an|   a|
            movq2dq     xmm3, mm1
            punpcklqdq  xmm1, xmm3                              ; xmm1|dbn| db| dan|  da|
    endif ; TG
    if render_mode and (render_alpha or render_gouraud) ; TA, TG
            cvtdq2ps    xmm1, xmm1 ; ps <- dw
            mulps       xmm1, xmm2      ;                         / dy
            cvtps2dq    xmm1, xmm1 ; dw <- ps
            packssdw    xmm0, xmm0                              ; xmm0| bn  b| an  a| bn  b| an  a|
            packssdw    xmm1, xmm1                              ; xmm1|dbn db|dan da|dbn db|dan da|
            ; 桁あふれ防止切り上げ(dc < 0 のときのみ)
            pxor        xmm2, xmm2
            pcmpgtw     xmm2, xmm1 ; r = (0 > dc) ? -1 : 0      ; xmm2|    |    | r r| r r|
            psubsw      xmm1, xmm2
    endif ; TA, TG
endif ; T
endm

fill_polygon macro proc_name, draw_scan_line, render_mode
align 16
proc_name proc c \
        uses    ebx ecx esi edi,
        _cnt    : dword,
        _x_min  : dword,
        _x_max  : dword,
        _y_min  : dword,
        _y_max  : dword,
        _y_min_p: ptr dword,
        _color  : dword,
        _texture: ptr dword,
        _tw     : dword,
        _th     : dword
        local   _i1: ptr dword
        local   _i2: ptr dword
        local   _y1_next: dword
        local   _y2_next: dword
        local   _y: dword
        local   _y_off: dword
rdtsc1

        ; // 位置と大きさ
        ; if ((x_max < 0) || (x_min >= width) || (y_max < 0) || (y_min >= height)) // スクリーンの外
        ;     return;
        xor         eax, eax
        cmp         _x_max, eax         ; if (x_max < 0)
        jl          proc_end
        mov         ebx, _width         ; if (x_min >= width)
        cmp         _x_min, ebx
        jge         proc_end
        cmp         _y_max, eax         ; if (y_max < 0)
        jl          proc_end
        mov         ebx, _height        ; if (y_min >= height)
        cmp         _y_min, ebx
        jge         proc_end
        ; if ((x_max == x_min) || (y_max == y_min)) // 空
        mov         eax, _x_min         ; if (x_max == x_min)
        cmp         _x_max, eax
        je          proc_end
        mov         eax, _y_min         ; if (y_max == y_min)
        cmp         _y_max, eax
        je          proc_end

        ; // スクリーンの上と下の頂点をスキップ
        ; int i1 = y_min_p;
        mov         esi, _y_min_p
        ; int i2 = y_min_p + cnt;
        mov         edi, sizeof VERT
        imul        edi, _cnt
        add         edi, esi
        ; while (py[i1 + 1] < 0)
        jmp         while_py_i1_end
while_py_i1_begin:
            ; ++ i1;
            add         esi, sizeof VERT
while_py_i1_end:
        cmp         [esi + sizeof VERT].VERT._y, word ptr 0
        jl          while_py_i1_begin
        ; while (py[i2 - 1] < 0)
        jmp         while_py_i2_end
while_py_i2_begin:
            ; -- i2;
            sub         edi, sizeof VERT
while_py_i2_end:
        cmp         [edi - sizeof VERT].VERT._y, word ptr 0
        jl          while_py_i2_begin
        ; y_min = (py[i1] < py[i2]) ? py[i1] : py[i2];
        mov         eax, [esi].VERT._y
        mov         ebx, [edi].VERT._y
        cmp         eax, ebx
        cmovge      eax, ebx
        mov         _y_min, eax
        ; y_max = (y_max < height) ? y_max : height;
        mov         eax, _height
        cmp         _y_max, eax
        jl          @f
            mov         _y_max, eax
@@:
        mov         eax, [esi].VERT._y
        mov         _i1, esi
        mov         _y1_next, eax
        mov         eax, [edi].VERT._y
        mov         _i2, edi
        mov         _y2_next, eax

        ; color
if render_mode eq 0 ; S
        movd        xmm6, _color
        pshufd      xmm6, xmm6, 00000000b ; 0000                ; xmm6|argb|argb|argb|argb| <- |    |    |    |argb|
elseif render_mode eq render_alpha ; A
        ; a1 = (color >> 24) & 0xff;
        movd        xmm6, _color
        movdqa      xmm0, xmm6      ; a1 = (color               ; xmm0|   0|   0|   0|argb|
        psrld       xmm0, 24        ;             >> 24) & 0xff ; xmm0|   0|   0|   0|   a|
        punpcklbw   xmm0, xmm0 ; ffff <- ff                     ; xmm0|   0|   0|   0|  aa|
        pshuflw     xmm0, xmm0, 00000000b ; 0,0,0,0             ; xmm0|   0|   0|aaaa|aaaa|
        ; da1 = dan1 = 0; // A
        pxor        xmm5, xmm5                                  ; xmm5|   0|   0|   0|   0| ; xmm5: da2 da2 = dan2 dan1
        ; r1 = ((color & 0x00ff0000) * a1) & 0xff000000;
        ; g1 = ((color & 0x0000ff00) * a1) & 0x00ff0000;
        ; b1 = ((color & 0x000000ff) * a1) & 0x0000ff00;
        ; a1 = 0xff000000 | ((r1 | g1 | b1) >> 8); // A
        punpcklbw   xmm6, xmm5 ; 0f0f0f0f <- ffff               ; xmm6|   0|   0| a r| g b| <- |   0|   0|   0|argb|
        pmulhuw     xmm6, xmm0 ; ff <- ff * ffff                ; xmm6|   0|   0|aaar|agab|
        mov         ebx, 0ffffh
        movd        xmm2, ebx
        pshuflw     xmm2, xmm2, 00010101b ; 0111                ; xmm2|    |    |ff 0| 0 0|
        por         xmm6, xmm2                                  ; xmm6|    |    |ffar|agab|
        ; an1 = 255 - a1; // A
        mov         eax, 0ffffh
        movd        xmm7, eax           ; an = 255
        pshuflw     xmm7, xmm7, 00000000b ; 0000                ; xmm7|    |    |ffff|ffff|
        psubw       xmm7, xmm0          ;           - a1        ; xmm7|    |    |anan|anan|
        pshuflw     xmm2, xmm2, 00111111b ; 0333                ; xmm2|    |    | 0ff|ffff|
        pand        xmm7, xmm2                                  ; xmm7|    |    | 0an|anan|
        ; right, left
        punpcklqdq  xmm6, xmm6                                  ; xmm6|ffar|agab|ffar|agab| ; xmm6:  a2*c   a1*c
        punpcklqdq  xmm7, xmm7                                  ; xmm7| 0an|anan| 0an|anan| ; xmm7: an2<<8 an1<<8
endif

        ; // スキャンラインを描画
        ; for (y = y_min; y < y_max; ++ y)
        mov         ecx, _y_min                                 ; ecx: y
        mov         ebx, _height        ; y_off = (height       ; ebx: y_off
        mov         eax, _y_max
        sub         ebx, ecx            ;                 - y_min)
        imul        ebx, _width_4       ;                          * width
        add         ebx, _pixOff        ;                                  + pixOff
        jmp         for_y_end
for_y_begin:
            ; if (y >= py[i1]) // 左: 新しい頂点に到達
            ; new_point _i1, _y1_next, sgn, macro_end, render_mode
            new_point   _i1, _y1_next, -, new_point_left_end, render_mode
            punpckhdq   mm6, mm6        ; mm6| x2| x2| <- | x2| x1|
            punpckhdq   mm7, mm7        ; mm7|dx2|dx2| <- |dx2|dx1|
            punpckldq   mm4, mm6        ; mm4| x2| x1|
            punpckldq   mm5, mm7        ; mm5|dx2|dx1|
            movq        mm6, mm4        ; mm6| x2| x1|
            movq        mm7, mm5        ; mm7|dx2|dx1|
    ife render_mode and render_texture ; !T
        if render_mode and render_gouraud ; G, GA
            punpckhqdq  xmm4, xmm6      ; xmm4|       c2|       c1| ; |2|1new| <- |1new|1new|, |2|1|
            punpckhqdq  xmm5, xmm7      ; xmm5|      dc2|      dc1| ; |2|1new| <- |1new|1new|, |2|1|
            movdqa      xmm6, xmm4      ; xmm6|       c2|       c1|
            movdqa      xmm7, xmm5      ; xmm7|      dc2|      dc1|
        endif ; G, GA
    else ; !T -> T
            punpcklqdq  xmm4, xmm4      ; xmm4| ty1| tx1| ty1| tx1| ; |1new|1new| <- |    |1new|
            punpcklqdq  xmm5, xmm5      ; xmm5|dty1|dtx1|dty1|dtx1| ; |1new|1new| <- |    |1new|
        ife render_mode and (render_alpha or render_gouraud) ; T
            punpckhqdq  xmm4, xmm6      ; xmm4| ty2| tx2| ty1| tx1| ; |2|1new| <- |1new|1new|, |2|1|
            punpckhqdq  xmm5, xmm7      ; xmm5|dty2|dtx2|dty1|dtx1| ; |2|1new| <- |1new|1new|, |2|1|
            movdqa      xmm6, xmm4      ; xmm6| ty2| tx2| ty1| tx1|
            movdqa      xmm7, xmm5      ; xmm7|dty2|dtx2|dty1|dtx1|
        else ; T -> TA, TG, TGA
            punpckhqdq  xmm4, xmm6      ; xmm4| ty2| tx2| ty1| tx1| ; |2|1new| <- |1new|1new|, |2|1|
            punpckhqdq  xmm0, xmm7      ; xmm0| tb2| ta2| tb1| ta1| ; |2|1new| <- |1new|1new|, |2|1|
            movdqa      xmm6, xmm4      ; xmm6| ty2| tx2| ty1| tx1|
            movdqa      xmm7, xmm0      ; xmm7| tb2| ta2| tb1| ta1|
            punpckhqdq  xmm5, _dtx      ; xmm5|dty2|dtx2|dty1|dtx1| ; |2|1new| <- |1new|1new|, |2|1|
            punpckhqdq  xmm1, _dtc      ; xmm1|dtb2|dta2|dtb1|dta1| ; |2|1new| <- |1new|1new|, |2|1|
            movdqa      _dtx, xmm5      ; _dtx|dty2|dtx2|dty1|dtx1|
            movdqa      _dtc, xmm1      ; _dtc|dtb2|dta2|dtb1|dta1|
        endif ; TA, TG, TGA
    endif ; T
new_point_left_end:
            ; if (y >= py[i2]) // 右: 新しい頂点に到達
            ; new_point _i1, _y1_next, sgn, macro_end, render_mode
            new_point   _i2, _y2_next, +, new_point_right_end, render_mode
            punpckldq   mm6, mm4        ; mm6| x2| x1| <- | x2(old)|dx1|, |   | x2|
            punpckldq   mm7, mm5        ; mm7|dx2|dx1| <- |dx2(old)|dx1|, |   |dx2|
    ife render_mode and render_texture ; !T
        if render_mode and render_gouraud ; G, GA
            punpcklqdq  xmm6, xmm4      ; xmm6|       c2|       c1| ; |2new|1| <- |2|1|, |2new|2new|
            punpcklqdq  xmm7, xmm5      ; xmm7|      dc2|      dc1| ; |2new|1| <- |2|1|, |2new|2new|
        endif ; G, GA
    else ; !T -> T
        ife render_mode and (render_alpha or render_gouraud) ; T
            punpcklqdq  xmm6, xmm4      ; xmm6| ty2| tx2| ty1| tx1| ; |2new|1| <- |2|1|, |    |2new|
            punpcklqdq  xmm7, xmm5      ; xmm7|dty2|dtx2|dty1|dtx1| ; |2new|1| <- |2|1|, |2new|2new|
        else ; T -> TA, TG, TGA
            punpcklqdq  xmm6, xmm4      ; xmm6| ty2| tx2| ty1| tx1| ; |2new|1| <- |2|1|, |    |2new|
            punpcklqdq  xmm7, xmm0      ; xmm7| tb2| ta2| tb1| ta1| ; |2new|1| <- |2|1|, |2new|2new|
            movdqa      xmm4, _dtx      ; xmm4|dty2|dtx2|dty1|dtx1|
            movdqa      xmm0, _dtc      ; xmm0|dtb2|dta2|dtb1|dta1|
            punpcklqdq  xmm4, xmm5      ; xmm4|dty2|dtx2|dty1|dtx1| ; |2new|1| <- |2|1|, |    |2new|
            punpcklqdq  xmm0, xmm1      ; xmm0|dtb2|dta2|dtb1|dta1| ; |2new|1| <- |2|1|, |2new|2new|
            movdqa      _dtx, xmm4      ; _dtx|dty2|dtx2|dty1|dtx1|
            movdqa      _dtc, xmm0      ; _dtc|dtb2|dta2|dtb1|dta1|
        endif ; TA, TG, TGA
    endif ; T
new_point_right_end:
            ; if (y >= 0)
            test        ecx, ecx ; cmp ecx, 0 ; y
            jl          end_draw_scan_line
                ; px1 = x1 >> 16;
                ; px2 = x2 >> 16;
                movq        mm1, mm6            ; px2 = x2
                movq        mm0, mm6            ; px1 = x1
                punpckhdq   mm1, mm1
                psrad       mm0, 16             ;          >> 16
                psrad       mm1, 16             ;          >> 16
                movd        edx, mm0                            ; edx: px1
                ; pdx = px2 - px1;
                movq        mm2, mm1            ; pdx = px2
                psubd       mm2, mm0            ;         - px1 ; mm2: pdx
                ; if (pdx > 0)
                ; 略
                    ; p1 = (px1 > 0) ? px1 : 0;
                    ; p2 = (px2 < width) ? px2 : width;
                    pxor        mm3, mm3
                    movd        mm4, _width
                    pmaxsw      mm0, mm3            ; p1
                    pminsw      mm1, mm4            ; p2
                    ; if (p1 < p2)
                    movd        ecx, mm0            ; p1
                    movd        eax, mm1            ;      p2
                    sub         ecx, eax            ;    -      ; ecx: -dp
                    jge         end_draw_scan_line
                        ; int off = _y(y) * width;
                        mov         ebx, _y_off
                        ; p1 += off;
                        ; p2 += off;
                        lea         ebx, [ebx + eax * 4]    ; p2 += off ; ebx: p2
                        ; // スキャンラインを描画
                        ; draw_scan_line();
                        movd        eax, mm2                    ; eax: pdx
                        draw_scan_line render_mode
end_draw_scan_line:
            ; x1 += dx1;
            ; x2 += dx2;
            paddd       mm6, mm7
    ife render_mode and render_texture ; !T
        if render_mode and render_gouraud ; G, GA
            ; r1 += dr1; // G
            ; r2 += dr2; // G
            ; g1 += dg1; // G
            ; g2 += dg2; // G
            ; b1 += db1; // G
            ; b2 += db2; // G
            ; a1 += da1; // A
            ; a2 += da2; // A
            ; an1 += dan1; // A
            ; an2 += dan2; // A
            paddw       xmm6, xmm7
        endif ; G, GA
    else ; !T -> T
        ife render_mode and (render_alpha or render_gouraud) ; T
            ; tx1 += dtx1; // T
            ; tx2 += dtx2; // T
            ; ty1 += dty1; // T
            ; ty2 += dty2; // T
            paddd       xmm6, xmm7
        else ; T -> TA, TG, TGA
            ; tx1 += dtx1; // T
            ; tx2 += dtx2; // T
            ; ty1 += dty1; // T
            ; ty2 += dty2; // T
            paddd       xmm6, _dtx
            ; a1 += da1; // A
            ; a2 += da2; // A
            ; an1 += dan1; // A
            ; an2 += dan2; // A
            ; b1 += db1; // G
            ; b2 += db2; // G
            ; bn1 += dbn1; // G
            ; bn2 += dbn2; // G
            paddw       xmm7, _dtc
        endif ; TA, TG, TGA
    endif ; T
        ; // スキャンラインを描画
        ; for (y = y_min; y < y_max; ++ y)
        mov         ecx, _y
        mov         ebx, _y_off
        mov         eax, _y_max
        inc         ecx
for_y_end:
        sub         ebx, _width_4
        cmp         ecx, eax            ; if (y < y_max)
        mov         _y, ecx
        mov         _y_off, ebx
        jl          for_y_begin
proc_end:
        ;emms
        mov         eax, 1
rdtsc2
        ret

        ; draw_scan_line ラベルテーブル
        align       16
ife render_mode and render_texture
    left_labels:
            dd  0, left_label0, left_label1, left_label2, left_label2
    right_labels:
            dd  right_label0, right_label1, right_label2, right_label3,
                right_label4, right_label5, right_label6, right_label7,
                right_label8, right_label9, right_label10, right_label11
else
    left_labels0:
            dd  0, left_label00, left_label01, left_label02, left_label02
    right_labels0:
            dd  right_label00, right_label01, right_label02, right_label03,
                right_label04, right_label05, right_label06, right_label07,
                right_label08, right_label09, right_label010, right_label011
    left_labels1:
            dd  0, left_label10, left_label11, left_label12, left_label12
    right_labels1:
            dd  right_label10, right_label11, right_label12, right_label13,
                right_label14, right_label15, right_label16, right_label17,
                right_label18, right_label19, right_label110, right_label111
endif
endm

fill_polygon JavaRenderMemorySSE2_fillPolygonSolid, FillPolygonSolid_draw_scan_line, 0
JavaRenderMemorySSE2_fillPolygonSolid endp

fill_polygon JavaRenderMemorySSE2_fillPolygonAlpha, FillPolygonAlpha_draw_scan_line, render_alpha
JavaRenderMemorySSE2_fillPolygonAlpha endp

fill_polygon JavaRenderMemorySSE2_fillPolygonGouraud, FillPolygonGouraud_draw_scan_line, render_gouraud
JavaRenderMemorySSE2_fillPolygonGouraud endp

fill_polygon JavaRenderMemorySSE2_fillPolygonGouraudAlpha, FillPolygonGouraudAlpha_draw_scan_line, (render_gouraud or render_alpha)
JavaRenderMemorySSE2_fillPolygonGouraudAlpha endp

fill_polygon JavaRenderMemorySSE2_fillPolygonTexture, FillPolygonTexture_draw_scan_line, render_texture
JavaRenderMemorySSE2_fillPolygonTexture endp

fill_polygon JavaRenderMemorySSE2_fillPolygonTextureAlpha, FillPolygonTextureAlpha_draw_scan_line, (render_texture or render_alpha)
JavaRenderMemorySSE2_fillPolygonTextureAlpha endp

fill_polygon JavaRenderMemorySSE2_fillPolygonTextureGouraud, FillPolygonTextureGouraud_draw_scan_line, (render_texture or render_gouraud)
JavaRenderMemorySSE2_fillPolygonTextureGouraud endp

fill_polygon JavaRenderMemorySSE2_fillPolygonTextureGouraudAlpha, FillPolygonTextureGouraudAlpha_draw_scan_line, (render_texture or render_gouraud or render_alpha)
JavaRenderMemorySSE2_fillPolygonTextureGouraudAlpha endp

; /** 描画方法のマスク。 */
RENDER_MASK             textequ <0ffh>
; /** ワイヤーフレームを描画。 */
RENDER_POLYLINE         textequ <1>
; /** ポリゴンの枠を描画。 */
RENDER_POLYFRAME        textequ <2>
; /** ポリゴンを描画。 */
RENDER_POLYGON          textequ <4>;,//3,
; /** 文字列を描画。 */
RENDER_STRING           textequ <8>;,//4,

; /** シェーディング方法のマスク。 */
SHADING_MASK            textequ <07h shl 8>
; /** テクスチャマッピング。 */
SHADING_TEXTURE         textequ <1 shl 8>
; /** 各頂点の色で変化させる。 */
SHADING_GOURAUD         textequ <1 shl 9>
; /** 透過。 */
SHADING_ALPHA           textequ <1 shl 10>

; /** 明るさのしきい値。 */
BRIGHTNESS_BORDER2      textequ <2048>
; /** 明るさのしきい値。 */
BRIGHTNESS_BORDER1      textequ <4096>
; /** 明るさの最大値。 */
BRIGHTNESS_MAX          textequ <BRIGHTNESS_BORDER1 + (BRIGHTNESS_BORDER1 / 8)>

align 16
JavaRenderMemorySSE2_render proc c \
        uses    ebx ecx esi edi,
        _render_mode : dword,
        _texture: ptr dword,
        _tw     : dword,
        _th     : dword,
        _cnt    : dword
        local   _x_min: dword
        local   _x_max: dword
        local   _y_min: dword
        local   _y_max: dword
        local   _y_min_p: dword
        local   _f_brightness: dword
        local   _f_alpha: dword
        local   _color: dword
        mov         ebx, _verts
        mov         ecx, _cnt

        ; if (2 == cnt)
        cmp     _cnt, 2
        jne     @f
            ; drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
            invoke      JavaRenderMemory_drawLine, \
                            [ebx].VERT._c, [ebx].VERT._x, [ebx].VERT._y, \
                            [ebx + sizeof VERT].VERT._x, [ebx + sizeof VERT].VERT._y
            jmp         proc_end
@@:
        ; else
            ; switch (render_mode & JavaRender::RENDER_MASK)
            mov         eax, _render_mode
            and         eax, RENDER_MASK
            ; case JavaRender::RENDER_POLYLINE:
            cmp         eax, RENDER_POLYLINE
            jne         render_polyline_end
                    ; for (i = idx; i < idx + cnt - 1; ++ i)
                    dec         ecx
@@:
                        ; drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
                        invoke      JavaRenderMemory_drawLine, \
                                        [ebx].VERT._c, [ebx].VERT._x, [ebx].VERT._y, \
                                        [ebx + sizeof VERT].VERT._x, [ebx + sizeof VERT].VERT._y
                    add         ebx, sizeof VERT
                    dec         ecx
                    jnz         @b
                    jmp         proc_end
render_polyline_end:
            ; case JavaRender::RENDER_POLYFRAME:
            cmp         eax, RENDER_POLYFRAME
            jne         render_polyframe_end
                    ; for (i = idx; i < idx + cnt - 1; ++ i)
                    dec         ecx
@@:
                        ; drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
                        invoke      JavaRenderMemory_drawLine, \
                                        [ebx].VERT._c, [ebx].VERT._x, [ebx].VERT._y, \
                                        [ebx + sizeof VERT].VERT._x, [ebx + sizeof VERT].VERT._y
                    add         ebx, sizeof VERT
                    dec         ecx
                    jnz         @b
                    ; drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[idx]).x2, _R(vert[idx]).y2);
                    mov         ecx, _verts
                    invoke      JavaRenderMemory_drawLine, \
                                    [ebx].VERT._c, [ebx].VERT._x, [ebx].VERT._y, \
                                    [ecx].VERT._x, [ecx].VERT._y
                    jmp         proc_end
render_polyframe_end:
            ; case JavaRender::RENDER_POLYGON:
            cmp         eax, RENDER_POLYGON
            jne         render_polygon_end
                    ; // 頂点を二重化、外接四角形
                    ; int x_min = _R(vert[i]).x2, x_max = x_min;
                    ; int y_min = _R(vert[i]).y2, y_max = y_min, y_min_p = 0;
                    mov         eax, [ebx].VERT._x
                    mov         _x_min, eax
                    mov         _x_max, eax
                    mov         eax, [ebx].VERT._y
                    mov         _y_min, eax
                    mov         _y_max, eax
                    mov         _y_min_p, ebx
mov         eax, [ebx].VERT._c
mov         _color, eax
                    ; // brightness, alpha
                    ; boolean f_brightness = (null != texture) ? true : false; // 明るさ [BRIGHTNESS_BORDER2, BRIGHTNESS_BORDER1]
                    ; int f_alpha = 0xff000000; // アルファ成分が全て最大
                    mov         _f_brightness, 0
                    cmp         _texture, 0
                    je          @f
                        mov         _f_brightness, -1
@@:
                    mov         _f_alpha, 0ff000000h
                    ; for (i = 0; i < cnt; ++ i)
                    mov         edx, ecx
                    imul        edx, sizeof VERT
for_i_begin:
                        ; // 頂点を二重化
                        ; // 外接四角形
                        ; verts[i].x = verts[i + cnt].x = _R(vert[idx + i]).x2;
                        ; verts[i].y = verts[i + cnt].y = _R(vert[idx + i]).y2;
                        mov         eax, [ebx].VERT._x
                        mov         [ebx + edx].VERT._x, eax
                        ; if (x_min > verts[i].x) { x_min = verts[i].x; }
                        cmp         _x_min, eax
                        jle         @f
                            mov         _x_min, eax
@@:
                        ; if (x_max < verts[i].x) { x_max = verts[i].x; }
                        cmp         _x_max, eax
                        jge         @f
                            mov         _x_max, eax
@@:
                        mov         eax, [ebx].VERT._y
                        mov         [ebx + edx].VERT._y, eax
                        ; if (y_min > verts[i].y) { y_min = verts[i].y; y_min_p = i; }
                        cmp         _y_min, eax
                        jle         @f
                            mov         _y_min, eax
                            mov         _y_min_p, ebx
@@:
                        ; if (y_max < verts[i].y) { y_max = verts[i].y; }
                        cmp         _y_max, eax
                        jge         @f
                            mov         _y_max, eax
@@:
                        ; if (null == texture)
                        ; {
                        ;     verts[i].c = verts[i + cnt].c = _R(vert[idx + i]).color;    // solid:   |  a|  r|  g|  b|
                        ; }
                        ; else
                        ; {
                        ;     verts[i].c = verts[i + cnt].c
                        ;         = (_R(vert[idx + i]).color & 0xff000000)
                        ;         | (_R(vert[idx + i]).brightness & 0x00ffffff);          // texture: |  a| brightness|
                        ;     verts[i].tx = verts[i + cnt].tx = _R(vert[idx + i]).tx;
                        ;     verts[i].ty = verts[i + cnt].ty = _R(vert[idx + i]).ty;
                        ; }
                        mov         eax, [ebx].VERT._c
                        mov         [ebx + edx].VERT._c, eax
                        ; // brightness, alpha
                        ; f_alpha &= verts[i].c;
                        and         _f_alpha, eax
                        ; f_brightness = f_brightness &&
                        ;       ((verts[i].c & 0x00ffffff <= JavaRender::BRIGHTNESS_BORDER1)
                        ;     && (verts[i].c & 0x00ffffff >= JavaRender::BRIGHTNESS_BORDER2));
                        cmp         _f_brightness, 0
                        je          @f
                        and         eax, 00ffffffh
                        cmp         eax, BRIGHTNESS_BORDER1 + 1
                        sbb         _f_brightness, -1
                        cmp         eax, BRIGHTNESS_BORDER2
                        adc         _f_brightness, 0
@@:
                        ;     verts[i].tx = verts[i + cnt].tx = _R(vert[idx + i]).tx;
                        ;     verts[i].ty = verts[i + cnt].ty = _R(vert[idx + i]).ty;
                        mov         eax, [ebx].VERT._tx
                        mov         [ebx + edx].VERT._tx, eax
                        mov         eax, [ebx].VERT._ty
                        mov         [ebx + edx].VERT._ty, eax
                    ; for (i = 0; i < cnt; ++ i)
                    add         ebx, sizeof VERT
                    dec         ecx
                    jnz         for_i_begin
                    ; int render_shading = render_mode & JavaRender::SHADING_MASK & ~JavaRender::SHADING_TEXTURE;
                    and         _render_mode, SHADING_MASK and not SHADING_TEXTURE
                    ; if (false != f_brightness) // 明るさ [BRIGHTNESS_BORDER2, BRIGHTNESS_BORDER1]
                    cmp         _f_brightness, 0
                    je          @f
                        ; render_shading &= ~JavaRender::SHADING_GOURAUD;
                        and         _render_mode, not SHADING_GOURAUD
@@:
                    ; if (0xff000000 == f_alpha) // アルファ成分が全て最大
                    cmp         _f_brightness, 0ff000000h
                    jne         @f
                        ; render_shading &= ~JavaRender::SHADING_ALPHA;
                        and         _render_mode, not SHADING_ALPHA
@@:
                    cmp         _texture, 0
                    jne         call_texture
                    ; switch (render_shading)
                    ; case 0:
                    cmp         _render_mode, 0
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonSolid, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
                        jmp         proc_end
@@:
                    ; case JavaRender::SHADING_ALPHA:
                    cmp         _render_mode, SHADING_ALPHA
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonAlpha, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
                        jmp         proc_end
@@:
                    ; case JavaRender::SHADING_GOURAUD:
                    cmp         _render_mode, SHADING_GOURAUD
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonGouraud, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
                        jmp         proc_end
@@:
                    ; case JavaRender::SHADING_GOURAUD | JavaRender::SHADING_ALPHA:
                    cmp         _render_mode, SHADING_GOURAUD or SHADING_ALPHA
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonGouraudAlpha, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
@@:
                    jmp         proc_end
call_texture:
                    ; switch (render_shading)
                    ; case 0:
                    cmp         _render_mode, 0
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonTexture, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
                        jmp         proc_end
@@:
                    ; case JavaRender::SHADING_ALPHA:
                    cmp         _render_mode, SHADING_ALPHA
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonTextureAlpha, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
                        jmp         proc_end
@@:
                    ; case JavaRender::SHADING_GOURAUD:
                    cmp         _render_mode, SHADING_GOURAUD
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonTextureGouraud, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
                        jmp         proc_end
@@:
                    ; case JavaRender::SHADING_GOURAUD | JavaRender::SHADING_ALPHA:
                    cmp         _render_mode, SHADING_GOURAUD or SHADING_ALPHA
                    jne         @f
                        invoke      JavaRenderMemorySSE2_fillPolygonTextureGouraudAlpha, \
                                        _cnt, _x_min, _x_max, _y_min, _y_max, _y_min_p, \
                                        _color, _texture, _tw, _th
@@:
                    jmp         proc_end
render_polygon_end:

proc_end:
        ret
JavaRenderMemorySSE2_render endp

_TEXT   ends

end
