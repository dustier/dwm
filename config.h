/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int viewontag          = 1;     /* Switch view on tag switch */
/* static const char font[]            = "monospace 15"; */
/* static const char font[]            = "Fira Code Nerd Font 15"; */
static const char font[]            = "Sauce Code Pro Nerd Font 15";
static const char dmenufont[]       = "monospace:size=15";
static const char col_normbg[]      = "#222222";
static const char col_normborder[]  = "#444444";
static const char col_normfg[]      = "#bbbbbb";
static const char col_selfg[]       = "#eeeeee";
static const char col_selbg[]       = "#005577";
static const char col_selborder[]   = "#770000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_normfg, col_normbg, col_normborder },
	[SchemeSel]  = { col_selfg, col_selbg, col_selborder  },
};

/* tagging */
#define MAX_TAGNAME_LEN 14		/* excludes TAG_PREPEND */
#define TAG_PREPEND "%1i:"		/* formatted as 2 chars */
#define MAX_TAGLEN 16			/* altogether */
static char tags[][MAX_TAGLEN] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ NULL,      NULL,     "Alacritty",           0,         0,          1,           0,        -1 },
	{ "netease-cloud-music", NULL, NULL,   1 << 8,    0,          0,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *roficmd[] = { "rofi", "-show", "drun", NULL};
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *browserproxycmd[] = { "chromium",  "--proxy-server=127.0.0.1:8889", NULL };
static const char *browsercmd[] = { "chromium", NULL };
static const char *zealcmd[] = { "zeal", NULL };
static const char *neteasecmd[] = { "netease-cloud-music", NULL };
static const char *sysactcmd[] = { "rofi", "-show", "p", "-modi", "p:powermenu.sh", "-width", "20", "-lines", "6", NULL };
static const char *screenlockcmd[] = { "i3lock", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browserproxycmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_z,      spawn,          {.v = zealcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = neteasecmd } },
	{ MODKEY,                    XK_BackSpace, spawn,          {.v = sysactcmd } },
	{ MODKEY,                    XK_l,       spawn,          {.v = screenlockcmd } },
	{ MODKEY,                       XK_apostrophe,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ Mod1Mask,                     XK_h,      setmfact,       {.f = -0.05} },
	{ Mod1Mask,                     XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    /* tag view */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },


    /* volume control */
    { 0,             XF86XK_AudioMute,         spawn,       SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { 0,             XF86XK_AudioLowerVolume,  spawn,       SHCMD("pamixer -d 3; kill -44 $(pidof dwmblocks)") },
    { 0,             XF86XK_AudioRaiseVolume,  spawn,       SHCMD("pamixer -i 3; kill -44 $(pidof dwmblocks)") },

	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      killunsel,      {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	/* { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },

    /* gaps */
	{ MODKEY,              XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,    XK_a,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,              XK_h,      incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,              XK_l,      incrgaps,       {.i = -3 } },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      nametag,        {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

