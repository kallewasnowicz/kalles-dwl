/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const float rootcolor[]             = COLOR(0x222222ff);
static const float bordercolor[]           = COLOR(0x444444ff);
static const float focuscolor[]            = COLOR(0x005577ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1, 0.1, 0.1, 1.0}; /* You can also use glsl colors */
static const int center_relative_to_monitor = 0;  /* 0 means center floating relative to the window area  */
static const char cursortheme[]            = "Catppuccin-Macchiato-Dark-Cursors"; /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursorsize       = 24;

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           -1 },
	*/
	{ "blababl",  NULL,       1 << 8,       0,           -1 },
	{ "^kitty$",  NULL,       0,            0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=", tile },
    { "|M|", centeredmaster },
    { "><>", NULL },    /* no layout function means floating behavior */
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
    /* name       mfact nmaster scale layout       rotate/reflect              x  y  resx resy rate mode adaptive*/
    /* example of a HiDPI laptop monitor at 120Hz:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 0, 0, 120.000f, 1, 1},
    * mode let's the user decide on how dwl should implement the modes:
    * -1 Sets a custom mode following the users choice
    * All other number's set the mode at the index n, 0 is the standard mode; see wlr-randr
    */
    /* Macbook */
    { "eDP-1",    0.5f,    1,      1,      &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 1920, 1200, 60.000f, -1 ,0},
    /* defaults */
    { NULL,       0.5f,    1,      1,      &layouts[2], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 0, 0, 0.0f, 0 ,0},

};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.layout = "de",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

static const int cursor_timeout = 5;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_ALT

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]            = { "foot", NULL };
static const char *menucmd[]            = { "bemenu_run", NULL };
/* static const char *webbrowser[]          = { "firefox", NULL }; */
static const char *webbrowser[]         = { "brave-bin", "--password-store=basic", NULL };
static const char *screenshotScreen[]   = { "captureScreen", NULL };
static const char *screenshotArea[]     = { "captureArea", NULL };
static const char *files[]              = { "pcmanfm", NULL };
static const char *monBrightnessUp[]    = { "brightnessctl", "set", "+10%", NULL };
static const char *monBrightnessDown[]  = { "brightnessctl", "set", "10%-", NULL };
static const char *keyBrightnessUp[]    = { "brightnessctl", "-d", "smc::kbd_backlight", "set", "+10%", NULL };
static const char *keyBrightnessDown[]  = { "brightnessctl", "-d", "smc::kbd_backlight", "set", "10%-", NULL };
static const char *defVolumeUp[]        = { "pactl_default_increase", NULL };
static const char *defVolumeDown[]      = { "pactl_default_decrease", NULL };
static const char *defVolumeMute[]      = { "pactl_default_mute", NULL };
static const char *toggleBar[]          = { "waybar-toggle", NULL };

static const Key keys[] = {
    /* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
    /* modifier                     key                     function            argument */
    { MODKEY,                       XKB_KEY_space,          spawn,              {.v = menucmd} },
    { MODKEY,                       XKB_KEY_t,              spawn,              {.v = termcmd} },
    { MODKEY,                       XKB_KEY_f,              spawn,              {.v = webbrowser} },
    { MODKEY,                       XKB_KEY_Sys_Req,        spawn,              {.v = screenshotScreen} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_Sys_Req,        spawn,              {.v = screenshotArea} },
    { MODKEY,                       XKB_KEY_e,              spawn,              {.v = files} },
    { MODKEY,                       XKB_KEY_b,              spawn,              {.v = toggleBar} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_semicolon,      focusstack,         {.i = +1} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_colon,          focusstack,         {.i = -1} },
    { MODKEY,                       XKB_KEY_m,              incnmaster,         {.i = +1} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_M,              incnmaster,         {.i = -1} },
    { MODKEY,                       XKB_KEY_comma,          setmfact,           {.f = -0.05f} },
    { MODKEY,                       XKB_KEY_period,         setmfact,           {.f = +0.05f} },
    { MODKEY,                       XKB_KEY_s,              zoom,               {0} },
    { MODKEY,                       XKB_KEY_Tab,            view,               {0} },
    { MODKEY,                       XKB_KEY_c,              killclient,         {0} },
    { MODKEY|WLR_MODIFIER_CTRL,     XKB_KEY_1,              setlayout,          {.v = &layouts[0]} },
    { MODKEY|WLR_MODIFIER_CTRL,     XKB_KEY_2,              setlayout,          {.v = &layouts[1]} },
    { MODKEY|WLR_MODIFIER_CTRL,     XKB_KEY_3,              setlayout,          {.v = &layouts[2]} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_space,          togglefloating,     {0} },
    { MODKEY,                       XKB_KEY_F11,            togglefullscreen,   {0} },
    /*{ MODKEY,                       XKB_KEY_x,              movecenter,         {0} },*/
    { MODKEY,                       XKB_KEY_0,              view,               {.ui = ~0} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_parenright,     tag,                {.ui = ~0} },
    /* Multi-Monitor
    { MODKEY,                       XKB_KEY_comma,          focusmon,           {.i = WLR_DIRECTION_LEFT} },
    { MODKEY,                       XKB_KEY_period,         focusmon,           {.i = WLR_DIRECTION_RIGHT} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_less,           tagmon,             {.i = WLR_DIRECTION_LEFT} },
    { MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_greater,        tagmon,             {.i = WLR_DIRECTION_RIGHT} },*/
    /* macbook */
    { MODKEY,                       XKB_KEY_XF86MonBrightnessUp,    spawn,      {.v = monBrightnessUp} },
    { MODKEY,                       XKB_KEY_XF86MonBrightnessDown,  spawn,      {.v = monBrightnessDown} },
    { MODKEY,                       XKB_KEY_XF86KbdBrightnessUp,    spawn,      {.v = keyBrightnessUp} },
    { MODKEY,                       XKB_KEY_XF86KbdBrightnessDown,  spawn,      {.v = keyBrightnessDown} },
    { MODKEY,                       XKB_KEY_XF86AudioLowerVolume,   spawn,      {.v = defVolumeDown} },
    { MODKEY,                       XKB_KEY_XF86AudioRaiseVolume,   spawn,      {.v = defVolumeUp} },
    { MODKEY,                       XKB_KEY_XF86AudioMute,          spawn,      {.v = defVolumeMute} },

    TAGKEYS(                        XKB_KEY_1, XKB_KEY_exclam,                  0),
    TAGKEYS(                        XKB_KEY_2, XKB_KEY_quotedbl,                1),
    TAGKEYS(                        XKB_KEY_3, XKB_KEY_section,                 2),
    TAGKEYS(                        XKB_KEY_4, XKB_KEY_dollar,                  3),
    TAGKEYS(                        XKB_KEY_5, XKB_KEY_percent,                 4),
    TAGKEYS(                        XKB_KEY_6, XKB_KEY_ampersand,               5),
    TAGKEYS(                        XKB_KEY_7, XKB_KEY_slash,                   6),
    TAGKEYS(                        XKB_KEY_8, XKB_KEY_parenleft,               7),
    TAGKEYS(                        XKB_KEY_9, XKB_KEY_parenright,              8),

    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,              {0} },

    /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
    { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit,{0} },
    /* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
     * do not remove them.
     */

#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
