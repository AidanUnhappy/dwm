/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Liberation Sans:size=14" };
static const char dmenufont[]       = "Liberation Sans:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_suckless[]    = "#005577";

static const char col_base03[]      = "#002b36";
static const char col_base02[]      = "#073642";
static const char col_base01[]      = "#586e75";
static const char col_base00[]      = "#657b83";
static const char col_base0[]       = "#839496";
static const char col_base1[]       = "#93a1a1";
static const char col_base2[]       = "#eee8d5";
static const char col_base3[]       = "#fdf6e3";
static const char col_yellow[]      = "#b58900";
static const char col_orange[]      = "#cb4b16";
static const char col_red[]         = "#dc322f";
static const char col_magenta[]     = "#d33682";
static const char col_violet[]      = "#6c71c4";
static const char col_blue[]        = "#268bd2";
static const char col_cyan[]        = "#2aa198";
static const char col_green[]       = "#859900";

static const char *colors[][3]      = {
	/*               fg                    bg                    border       */
	[SchemeNorm] = { col_gray3,            col_gray1,            col_gray3     },
	[SchemeSel]  = { col_gray4,            col_suckless,         col_magenta   },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_suckless, "-sf", col_gray4, NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *browsercmd[]  = { "google-chrome-stable", NULL };

static const char *briup[]       = { "/home/aidan/Aidan/FD/script/bri-up.sh",  NULL };
static const char *bridown[]     = { "/home/aidan/Aidan/FD/script/bri-down.sh",  NULL };

static const char *volup[]       = { "/home/aidan/Aidan/FD/script/vol-up.sh",  NULL };
static const char *voldown[]     = { "/home/aidan/Aidan/FD/script/vol-down.sh",  NULL };
static const char *voltoggle[]   = { "/home/aidan/Aidan/FD/script/vol-toggle.sh",  NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier            key                      function        argument */
	{ MODKEY,              XK_slash,                spawn,          {.v = dmenucmd } },
	{ MODKEY,              XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,              XK_o,                    spawn,          {.v = browsercmd } },
	{ MODKEY,              XK_q,                    killclient,     {0} },
	{ 0,                   XF86XK_MonBrightnessUp,  spawn,          {.v = briup } },
	{ 0,                   XF86XK_MonBrightnessDown,spawn,          {.v = bridown } },
	{ 0,                   XF86XK_AudioRaiseVolume, spawn,          {.v = volup } },
	{ 0,                   XF86XK_AudioLowerVolume, spawn,          {.v = voldown } },
	{ 0,                   XF86XK_AudioMute,        spawn,          {.v = voltoggle } },

	{ MODKEY,              XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,              XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,              XK_period,               zoom,           {0} },
	{ MODKEY,              XK_n,                    inplacerotate,  {.i = +2} },
	{ MODKEY,              XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,              XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,              XK_bracketleft,          setmfact,       {.f = -0.05} },
	{ MODKEY,              XK_bracketright,         setmfact,       {.f = +0.05} },
//	{ MODKEY|ShiftMask,    XK_Return,               zoom,           {0} },
//	{ MODKEY|ShiftMask,    XK_j,                    rotatestack,    {.i = +1 } },
//	{ MODKEY|ShiftMask,    XK_k,                    rotatestack,    {.i = -1 } },
//	{ MODKEY|ShiftMask,    XK_j,                    inplacerotate,  {.i = +1} },
//	{ MODKEY|ShiftMask,    XK_k,                    inplacerotate,  {.i = -1} },
//	{ MODKEY|ShiftMask,    XK_h,                    inplacerotate,  {.i = +2} },
//	{ MODKEY|ShiftMask,    XK_l,                    inplacerotate,  {.i = -2} },

	{ MODKEY,              XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,              XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,              XK_backslash,            togglefloating, {0} },
//	{ MODKEY,              XK_f,                    setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,              XK_space,                setlayout,      {0} },
//	{ MODKEY|ShiftMask,    XK_space,                togglefloating, {0} },
//	{ MODKEY,              XK_b,                    togglebar,      {0} },

	TAGKEYS(               XK_1,                                    0)
	TAGKEYS(               XK_2,                                    1)
	TAGKEYS(               XK_3,                                    2)
	TAGKEYS(               XK_4,                                    3)
	TAGKEYS(               XK_5,                                    4)
	TAGKEYS(               XK_6,                                    5)
	TAGKEYS(               XK_7,                                    6)
	TAGKEYS(               XK_8,                                    7)
	TAGKEYS(               XK_9,                                    8)
	{ MODKEY,              XK_Tab,                  view,           {0} },
	{ MODKEY,              XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,              XK_h,                    viewtoleft,     {0} },
	{ MODKEY,              XK_l,                    viewtoright,    {0} },
	{ MODKEY|ShiftMask,    XK_h,                    tagtoleft,      {0} },
	{ MODKEY|ShiftMask,    XK_l,                    tagtoright,     {0} },

//	{ MODKEY,              XK_comma,                focusmon,       {.i = -1 } },
//	{ MODKEY,              XK_period,               focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,    XK_comma,                tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,    XK_period,               tagmon,         {.i = +1 } },

	{ MODKEY|ShiftMask,    XK_q,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

