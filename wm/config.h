/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "wezterm"
#define TERMCLASS "Wezterm"
#define BROWSER "brave"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh      = 9;        /* 2 is the default spacing around the bar's font */
static const int vertpad      = 5;       /* vertical padding of bar */
static const int sidepad      = 10;       /* horizontal padding of bar */
static char *fonts[]          = { "monospace:size=15" };


static char normbgcolor[]           = "#23282b";
static char normbordercolor[]       = "#000000";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#cee2cd";
static char selbordercolor[]        = "#5c6d7a";
static char selbgcolor[]            = "#5e8a83";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "start", "--class", "spterm", "--position", "120,34", NULL };
const char *spcmd2[] = {TERMINAL, "start", "--class", "spcalc", "--position", "50,20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { " 1  ", " 2  ", " 3  ", " 4  ", " 5  ", " 6  ", " 7  ", " 8  ", " 9  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ NULL,     NULL,         "Emulator",       	   0,       1,           0,         0,        -1 },
	{ "Mendeley Desktop",NULL,NULL,       	    1 << 3,       0,           0,         0,        1 },
	{ "music",  "music",      NULL,       	    1 << 4,       0,           0,         0,        1 },
	{ NULL,     NULL,         "newsboat",      	1 << 5,       0,           0,         0,        -1 },
	{ "Brave-browser", NULL,  NULL,             1 << 6,       0,           0,         0,        1 },
	{ NULL,     NULL,         "neomutt",        1 << 7,       0,           0,         0,        -1 },
	{ "tabbed", "neomutt",    NULL,             1 << 7,       0,           0,         0,        -1 },
	{ "Microsoft Teams - Preview",NULL,NULL,    1 << 7,       0,           0,         0,        -1 },
	{ "Caprine",NULL,         NULL,             1 << 8,       0,           0,         0,        -1 },
	{ "TelegramDesktop",NULL, NULL,             1 << 8,       0,           0,         0,        -1 },
	{ "Slack",  NULL,         NULL,             1 << 8,       0,           0,         0,        1 },
	{ TERMCLASS,NULL,         NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",    NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
	{ TERMCLASS,  NULL,       NULL,       	 0,           0,           1,          0,         -1 },
	{ NULL,       NULL,       "Event Tester", 0,          0,           0,          1,         -1 },
	{ TERMCLASS,  "floatterm", NULL,       	 0,           1,           1,          0,         -1 },
	{ TERMCLASS,  "bg",        NULL,       	 1 << 7,      0,           1,          0,         -1 },
	{ TERMCLASS,  "spterm",    NULL,       	 SPTAG(0),    1,           1,          0,         -1 },
	{ TERMCLASS,  "spcalc",    NULL,       	 SPTAG(1),    1,           1,          0,         -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.h"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },	                /* Default: Master on left, slaves on right */
	{ "TTT",	bstack },               /* Master on top, slaves on bottom */

	{ "[@]",	spiral },               /* Fibonacci spiral */
	{ "[\\]",	dwindle },              /* Decreasing in size right and leftward */

	{ "[D]",	deck },	                /* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },              /* All windows on top of eachother */

	{ "|M|",	centeredmaster },               /* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },       /* Same but master floats */

	{ "><>",	NULL },	                /* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	// { MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.h"

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },

	{ MODKEY,			XK_Tab,		view,		{0} },
	{ Mod1Mask,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ Mod1Mask|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_backslash,		view,		{0} },

	{ MODKEY,			XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,			XK_s,		togglesticky,	{0} },
	{ MODKEY,		        XK_d, spawn,    SHCMD("dwm-displays") },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.05} },
	{ MODKEY,			XK_q,		killclient,      	{.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_q, spawn,    SHCMD("dwm-power") },
	{ MODKEY,			XK_w, spawn,    SHCMD("brave")  },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,	shifttag,	{ .i = 1 } },
	{ MODKEY,			XK_apostrophe,	togglescratch,	{.ui = 1} },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 0} },
	{ MODKEY,			XK_Return,      spawn, SHCMD(TERMINAL)  },

	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY|ShiftMask,		XK_z,	zoom,	{0} },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },
	{ MODKEY,			XK_b,		togglebar,	{0} },

	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,			XK_space,       spawn, SHCMD("dmenu_run -l 15 -p 'Run: '")  },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
	{ 0, XF86XK_AudioMute,                          spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,                   spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,                   spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,                    spawn,          SHCMD("brightnessctl set +10%") },
	{ 0, XF86XK_MonBrightnessDown,                  spawn,          SHCMD("brightnessctl set 10%-") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	// { ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};
