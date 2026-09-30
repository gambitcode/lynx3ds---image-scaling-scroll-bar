/* Draws a horizontal scrollbar along the bottom edge of the bottom screen.
 *
 * Must be called between C2D_SceneBegin() and C3D_FrameEnd(), i.e. in the
 * same C2D frame as the background/guide images.
 *
 * Citro2d depth convention: z = 0 is closest to the camera (front), z = 1
 * is furthest away (back). The background/guide images are drawn at z = 0
 * and z = 0.5 respectively, so the scrollbar must use z values *below*
 * those to appear on top. We use -0.5 and -0.4 to sit clearly in front.
 *
 * scroll_x is the current horizontal offset.
 * max_scroll_x is the maximum possible offset before the end of the document.
 * If max_scroll_x <= 0, the scrollbar is treated as fully filled.
 */
void font_draw_scrollbar_bottom(int scroll_x, int max_scroll_x)
{
    const float screen_w = (float) FB_BOTTOM_W;
    const float screen_h = (float) FB_BOTTOM_H;
    const float bar_h = 4.0f;
    const float bar_y = screen_h - bar_h;
    const float z_track = -0.5f;
    const float z_thumb = -0.4f;

    const u32 track_color = C2D_Color32(0x42, 0x42, 0x42, 0xFF);	/* dark grey */
    const u32 thumb_color = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);	/* white */

    /* Track: always drawn full width. */
    C2D_DrawRectSolid(0.0f, bar_y, z_track, screen_w, bar_h, track_color);

    if (max_scroll_x <= 0) {
	/* Nothing to scroll -- fill the whole track with the thumb. */
	C2D_DrawRectSolid(0.0f, bar_y, z_thumb, screen_w, bar_h, thumb_color);
	return;
    }

    /* Clamp scroll offset so the thumb can never go negative or overshoot. */
    if (scroll_x < 0)
	scroll_x = 0;
    if (scroll_x > max_scroll_x)
	scroll_x = max_scroll_x;

    float fill_w = (screen_w * (float) scroll_x) / (float) max_scroll_x;

    /* Thumb, on top of the track. */
    if (fill_w > 0.0f)
	C2D_DrawRectSolid(0.0f, bar_y, z_thumb, fill_w, bar_h, thumb_color);
}
