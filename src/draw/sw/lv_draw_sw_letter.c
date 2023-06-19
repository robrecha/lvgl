/**
 * @file lv_draw_sw_letter.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_draw_sw.h"
#if LV_USE_DRAW_SW

#include "../../core/lv_disp.h"
#include "../../misc/lv_math.h"
#include "../../misc/lv_assert.h"
#include "../../misc/lv_area.h"
#include "../../misc/lv_style.h"
#include "../../font/lv_font.h"
#include "../../core/lv_refr.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

LV_ATTRIBUTE_FAST_MEM static void draw_letter_cb(lv_draw_unit_t * draw_unit, lv_draw_letter_dsc_t * draw_dsc);


#if LV_DRAW_SW_FONT_SUBPX
static void draw_letter_subpx(lv_layer_t * layer, const lv_draw_label_dsc_t * dsc, const lv_point_t * pos,
                              lv_font_glyph_dsc_t * g, const uint8_t * map_p);
#endif /*LV_DRAW_SW_FONT_SUBPX*/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_sw_label(lv_draw_unit_t * draw_unit, const lv_draw_label_dsc_t * dsc, const lv_area_t * coords)
{
    if(dsc->opa <= LV_OPA_MIN) return;

    lv_draw_label_interate_letters(draw_unit, dsc, coords, draw_letter_cb);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

LV_ATTRIBUTE_FAST_MEM static void draw_letter_cb(lv_draw_unit_t * draw_unit, lv_draw_letter_dsc_t * draw_dsc)
{
    if(draw_dsc->bitmap == NULL) {
#if LV_USE_FONT_PLACEHOLDER
        /* Draw a placeholder rectangle*/
        lv_draw_border_dsc_t border_draw_dsc;
        border_draw_dsc.opa = draw_dsc->letter_opa;
        border_draw_dsc.color = draw_dsc->letter_color;
        border_draw_dsc.width = 1;
        lv_draw_sw_border(draw_unit, &border_draw_dsc, draw_dsc->bg_coords);
#endif
        return;
    }

    if(draw_dsc->format == LV_DRAW_LETTER_BITMAP_FORMAT_A8) {
        lv_draw_sw_blend_dsc_t blend_dsc;
        lv_memzero(&blend_dsc, sizeof(blend_dsc));
        blend_dsc.color = draw_dsc->letter_color;
        blend_dsc.opa = draw_dsc->letter_opa;
        blend_dsc.mask_buf = draw_dsc->bitmap;
        blend_dsc.mask_area = draw_dsc->letter_coords;
        blend_dsc.blend_area = draw_dsc->letter_coords;
        blend_dsc.mask_res = LV_DRAW_SW_MASK_RES_CHANGED;

        lv_draw_sw_blend(draw_unit, &blend_dsc);
    }
    if(draw_dsc->format == LV_DRAW_LETTER_BITMAP_FORMAT_SUBPX) {
#if LV_USE_FONT_SUBPX
        LV_LOG_WARN("Sub pixel rendering is not implemented yet.");
#endif
    }

#if LV_USE_IMGFONT
    if(draw_dsc->format == LV_DRAW_LETTER_BITMAP_FORMAT_IMAGE) {
        lv_draw_img_dsc_t img_dsc;
        lv_draw_img_dsc_init(&img_dsc);
        img_dsc.angle = 0;
        img_dsc.zoom = LV_ZOOM_NONE;
        img_dsc.opa = draw_dsc->letter_opa;
        img_dsc.src = draw_dsc->bitmap;
        lv_draw_sw_img(draw_unit, &img_dsc, draw_dsc->letter_coords);
        return;
    }
#endif
}

#endif /*LV_USE_DRAW_SW*/
