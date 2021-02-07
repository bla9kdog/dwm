/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char* fonts[] = { "JetBrainsMono Nerd Font Mono:size=9" };
static const char dmenufont[] = "JetBrainsmono Nerd Font Mono:size=9";
static const char col_gray1[] = "#1f1f24";
static const char col_gray2[] = "#43454b";
static const char col_gray3[] = "#aeb7c0";
static const char col_gray4[] = "#ffffff";
static const char col_gray5[] = "#838991";
static const char col_gray6[] = "#28282d";
static const char col_gray7[] = "#232328";
static const char col_gray8[] = "#34353b";
static const char* colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray5, col_gray1, col_gray7 },
    [SchemeSel] = { col_gray4, col_gray7, col_gray8 },
};

/* tagging */
static const char* tags[] = { "1", "10", "11", "100", "101", "110", "111", "1000" };

/* grid of tags */
#define DRAWCLASSICTAGS 1 << 0
#define DRAWTAGGRID 1 << 1

#define SWITCHTAG_UP 1 << 0
#define SWITCHTAG_DOWN 1 << 1
#define SWITCHTAG_LEFT 1 << 2
#define SWITCHTAG_RIGHT 1 << 3
#define SWITCHTAG_TOGGLETAG 1 << 4
#define SWITCHTAG_TAG 1 << 5
#define SWITCHTAG_VIEW 1 << 6
#define SWITCHTAG_TOGGLEVIEW 1 << 7

static const unsigned int drawtagmask = DRAWCLASSICTAGS; /* | DRAWCLASSICTAGS to show classic row of tags */
static const int tagrows = 2;

static const Rule rules[] = {
    /* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class      instance    title       tags mask     iscentered   isfloating   monitor */
    { "Gimp", NULL, NULL, 0, 0, 1, -1 },
    { "Firefox", NULL, NULL, 1 << 8, 0, 0, -1 },
};

/* layout(s) */
static const float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;     /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]", tile }, /* first entry is default */
    { "[F]", NULL }, /* no layout function means floating behavior */
    { "[M]", monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                              \
    { MODKEY, KEY, view, { .ui = 1 << TAG } },                         \
        { MODKEY | ControlMask, KEY, toggleview, { .ui = 1 << TAG } }, \
        { MODKEY | ShiftMask, KEY, tag, { .ui = 1 << TAG } },          \
        { MODKEY | ControlMask | ShiftMask, KEY, toggletag, { .ui = 1 << TAG } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                          \
    {                                                       \
        .v = (const char*[]) { "/bin/sh", "-c", cmd, NULL } \
    }

#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char* dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray6, "-nf", col_gray4, "-sb", col_gray2, "-sf", col_gray4, NULL };
static const char* termcmd[] = { "st", NULL };
static const char* brupcmd[] = { "xbacklight", "-inc", "10", NULL };
static const char* brdowncmd[] = { "xbacklight", "-dec", "10", NULL };
static const char* mutecmd[] = { "pamixer", "-t", NULL };
static const char* volupcmd[] = { "pamixer", "-i", "5", NULL };
static const char* voldowncmd[] = { "pamixer", "-d", "5", NULL };
static const char* qutecmd[] = { "qutebrowser", "-r", "default", NULL };
static const char* figmacmd[] = { "figma", NULL };
static const char* calccmd[] = { "=", NULL };
static const char* zathuracmd[] = { "zathura", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { 0, XF86XK_AudioMute, spawn, { .v = mutecmd } },
    { 0, XF86XK_AudioLowerVolume, spawn, { .v = voldowncmd } },
    { 0, XF86XK_AudioRaiseVolume, spawn, { .v = volupcmd } },
    { 0, XF86XK_MonBrightnessUp, spawn, { .v = brupcmd } },
    { 0, XF86XK_MonBrightnessDown, spawn, { .v = brdowncmd } },
    { MODKEY | ShiftMask, XK_r, spawn, SHCMD("redshift -l 44:20") },
    { MODKEY | ShiftMask, XK_s, spawn, SHCMD("maim -s | xclip -selection clipboard -t image/png") },
    { MODKEY | ShiftMask, XK_w, spawn, { .v = qutecmd } },
    { MODKEY | ShiftMask, XK_f, spawn, { .v = figmacmd } },
    { MODKEY | ShiftMask, XK_space, spawn, { .v = calccmd } },
    { MODKEY | ShiftMask, XK_z, spawn, { .v = zathuracmd } },
    { MODKEY, XK_space, spawn, { .v = dmenucmd } },
    { MODKEY | ShiftMask, XK_Return, spawn, { .v = termcmd } },
    { MODKEY, XK_b, togglebar, { 0 } },
    { MODKEY, XK_j, focusstack, { .i = +1 } },
    { MODKEY, XK_k, focusstack, { .i = -1 } },
    { MODKEY, XK_i, incnmaster, { .i = +1 } },
    { MODKEY, XK_d, incnmaster, { .i = -1 } },
    { MODKEY, XK_h, setmfact, { .f = -0.05 } },
    { MODKEY, XK_l, setmfact, { .f = +0.05 } },
    { MODKEY | ShiftMask, XK_h, setcfact, { .f = +0.25 } },
    { MODKEY | ShiftMask, XK_l, setcfact, { .f = -0.25 } },
    { MODKEY | ShiftMask, XK_o, setcfact, { .f = 0.00 } },
    { MODKEY, XK_Return, zoom, { 0 } },
    { MODKEY, XK_Tab, view, { 0 } },
    { MODKEY | ShiftMask, XK_q, killclient, { 0 } },
    { MODKEY, XK_t, setlayout, { .v = &layouts[0] } },
    { MODKEY, XK_f, setlayout, { .v = &layouts[1] } },
    { MODKEY, XK_m, setlayout, { .v = &layouts[2] } },
    { MODKEY, XK_p, setlayout, { 0 } },
    { MODKEY | ShiftMask, XK_p, togglefloating, { 0 } },
    { MODKEY, XK_0, view, { .ui = ~0 } },
    { MODKEY | ShiftMask, XK_0, tag, { .ui = ~0 } },
    { MODKEY, XK_comma, focusmon, { .i = -1 } },
    { MODKEY, XK_period, focusmon, { .i = +1 } },
    { MODKEY | ShiftMask, XK_comma, tagmon, { .i = -1 } },
    { MODKEY | ShiftMask, XK_period, tagmon, { .i = +1 } },
    TAGKEYS(XK_1, 0)
        TAGKEYS(XK_2, 1)
            TAGKEYS(XK_3, 2)
                TAGKEYS(XK_4, 3)
                    TAGKEYS(XK_5, 4)
                        TAGKEYS(XK_6, 5)
                            TAGKEYS(XK_7, 6)
                                TAGKEYS(XK_8, 7)
                                    TAGKEYS(XK_9, 8) { MODKEY | ShiftMask, XK_c, quit, { 0 } },

    { MODKEY | ControlMask, XK_Up, switchtag, { .ui = SWITCHTAG_UP | SWITCHTAG_VIEW } },
    { MODKEY | ControlMask, XK_Down, switchtag, { .ui = SWITCHTAG_DOWN | SWITCHTAG_VIEW } },
    { MODKEY | ControlMask, XK_Right, switchtag, { .ui = SWITCHTAG_RIGHT | SWITCHTAG_VIEW } },
    { MODKEY | ControlMask, XK_Left, switchtag, { .ui = SWITCHTAG_LEFT | SWITCHTAG_VIEW } },

    { MODKEY | Mod4Mask, XK_Up, switchtag, { .ui = SWITCHTAG_UP | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY | Mod4Mask, XK_Down, switchtag, { .ui = SWITCHTAG_DOWN | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY | Mod4Mask, XK_Right, switchtag, { .ui = SWITCHTAG_RIGHT | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
    { MODKEY | Mod4Mask, XK_Left, switchtag, { .ui = SWITCHTAG_LEFT | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol, 0, Button1, setlayout, { 0 } },
    { ClkLtSymbol, 0, Button3, setlayout, { .v = &layouts[2] } },
    { ClkWinTitle, 0, Button2, zoom, { 0 } },
    { ClkStatusText, 0, Button2, spawn, { .v = termcmd } },
    { ClkClientWin, MODKEY, Button1, movemouse, { 0 } },
    { ClkClientWin, MODKEY, Button2, togglefloating, { 0 } },
    { ClkClientWin, MODKEY, Button3, resizemouse, { 0 } },
    { ClkTagBar, 0, Button1, view, { 0 } },
    { ClkTagBar, 0, Button3, toggleview, { 0 } },
    { ClkTagBar, MODKEY, Button1, tag, { 0 } },
    { ClkTagBar, MODKEY, Button3, toggletag, { 0 } },
};
