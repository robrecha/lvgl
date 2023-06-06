#if LV_BUILD_TEST
#include "../lvgl.h"

#include "unity/unity.h"

void setUp(void)
{
    /* Function run before every test */
    lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(lv_scr_act(), LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY);

}

void tearDown(void)
{
    /* Function run after every test */
}


void canvas_blend_test(lv_obj_t  * canvas2, lv_draw_img_dsc_t * img_dsc, const char * name_main, const char * name_sub,
                       lv_color_format_t render_cf, lv_opa_t opa)
{
    lv_area_t area;
    area.x1 = 25;
    area.x2 = 699 + 25;
    area.y1 = 25;
    area.y2 = 399 + 25;

    lv_layer_t layer2;
    static uint8_t canvas2_buf[750 * 450 * 4];
    char fn_buf[64];

    img_dsc->opa = LV_OPA_COVER;
    lv_canvas_set_buffer(canvas2, canvas2_buf, 750, 450, render_cf);
    lv_canvas_fill_bg(canvas2, lv_palette_lighten(LV_PALETTE_BLUE_GREY, 2), opa);
    lv_canvas_init_layer(canvas2, &layer2);
    lv_draw_img(&layer2, img_dsc, &area);
    lv_canvas_finish_layer(canvas2, &layer2);

    lv_snprintf(fn_buf, sizeof(fn_buf), "draw_belnd_%s_%s.png", name_main, name_sub);
    TEST_ASSERT_EQUAL_SCREENSHOT(fn_buf);

    img_dsc->opa = LV_OPA_50;
    lv_canvas_set_buffer(canvas2, canvas2_buf, 750, 450, render_cf);
    lv_canvas_fill_bg(canvas2, lv_palette_lighten(LV_PALETTE_BLUE_GREY, 2), opa);
    lv_canvas_init_layer(canvas2, &layer2);
    lv_draw_img(&layer2, img_dsc, &area);
    lv_canvas_finish_layer(canvas2, &layer2);

    lv_snprintf(fn_buf, sizeof(fn_buf), "draw_belnd_%s_%s_opa.png", name_main, name_sub);
    TEST_ASSERT_EQUAL_SCREENSHOT(fn_buf);
}



static void canvas_draw(const char * name, lv_color_format_t render_cf, lv_opa_t opa)
{
    lv_obj_clean(lv_scr_act());

    static uint8_t canvas_buf[700 * 400 * 4];

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, canvas_buf, 700, 400, render_cf);

    lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_PURPLE, 4), opa);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    static lv_style_t style;
    lv_style_init(&style);

    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.radius = 20;
    rect_dsc.bg_color = lv_palette_main(LV_PALETTE_RED);
    rect_dsc.bg_opa = LV_OPA_COVER;
    rect_dsc.outline_color = lv_palette_main(LV_PALETTE_BLUE);
    rect_dsc.outline_width = 20;
    rect_dsc.outline_pad = -10;
    rect_dsc.outline_opa = LV_OPA_50;
    rect_dsc.shadow_color = lv_palette_main(LV_PALETTE_ORANGE);
    rect_dsc.shadow_width = 30;
    rect_dsc.shadow_ofs_x = 20;
    rect_dsc.shadow_ofs_y = 40;

    lv_area_t area;
    area.x1 = 50;
    area.x2 = 200;
    area.y1 = 50;
    area.y2 = 300;

    lv_draw_rect(&layer, &rect_dsc, &area);

    area.x1 = 250;
    area.x2 = 400;

    rect_dsc.bg_grad.dir = LV_GRAD_DIR_HOR;
    rect_dsc.bg_grad.stops_count = 2;
    rect_dsc.bg_grad.stops[0].color = lv_palette_main(LV_PALETTE_RED);
    rect_dsc.bg_grad.stops[0].opa = LV_OPA_COVER;
    rect_dsc.bg_grad.stops[0].frac = 0;
    rect_dsc.bg_grad.stops[1].color = lv_palette_main(LV_PALETTE_GREEN);
    rect_dsc.bg_grad.stops[1].opa = LV_OPA_COVER;
    rect_dsc.bg_grad.stops[1].frac = 255;

    lv_draw_rect(&layer, &rect_dsc, &area);

    area.x1 = 450;
    area.x2 = 600;
    rect_dsc.bg_grad.stops[0].opa = LV_OPA_60;

    lv_draw_rect(&layer, &rect_dsc, &area);

    lv_canvas_finish_layer(canvas, &layer);

    char fn_buf[64];
    lv_snprintf(fn_buf, sizeof(fn_buf), "draw_blend_%s.png", name);
    TEST_ASSERT_EQUAL_SCREENSHOT(fn_buf);

    lv_obj_add_flag(canvas, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * canvas2 = lv_canvas_create(lv_scr_act());

    lv_img_dsc_t img;
    img.header.w = 699;
    img.header.h = 399;
    img.header.always_zero = 0;
    img.header.cf = render_cf;
    img.data = canvas_buf;

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    img_dsc.src = &img;

    canvas_blend_test(canvas2, &img_dsc, name, "to_rgb565", LV_COLOR_FORMAT_RGB565, LV_OPA_COVER);
    canvas_blend_test(canvas2, &img_dsc, name, "to_rgb888", LV_COLOR_FORMAT_RGB888, LV_OPA_COVER);
    canvas_blend_test(canvas2, &img_dsc, name, "to_xrgb8888", LV_COLOR_FORMAT_XRGB8888, LV_OPA_COVER);
    canvas_blend_test(canvas2, &img_dsc, name, "to_argb8888", LV_COLOR_FORMAT_ARGB8888, LV_OPA_COVER);
    canvas_blend_test(canvas2, &img_dsc, name, "to_argb8888_transp", LV_COLOR_FORMAT_ARGB8888, LV_OPA_50);

}

void test_xrgb8888(void)
{
    canvas_draw("xrgb8888", LV_COLOR_FORMAT_XRGB8888, LV_OPA_COVER);
}


void test_argb8888(void)
{
    canvas_draw("argb8888", LV_COLOR_FORMAT_ARGB8888, LV_OPA_COVER);
}

void test_argb8888_transp(void)
{
    canvas_draw("argb8888_transp", LV_COLOR_FORMAT_ARGB8888, LV_OPA_20);
}


void test_rgb888(void)
{
    canvas_draw("rgb888", LV_COLOR_FORMAT_RGB888, LV_OPA_COVER);
}


void test_rgb565(void)
{
    canvas_draw("rgb565", LV_COLOR_FORMAT_RGB565, LV_OPA_COVER);
}

#endif
