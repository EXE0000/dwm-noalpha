/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int tabModKey = 0x40;
static const unsigned int tabCycleKey = 0x17;
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:size=14",
										"WenQuanYi Micro Hei Mono:size:14:style=Regular:antialias:true:autohint:true",
										"JoyPixels:pixelsize:14:style=Regular:antialias:true:autohint:true",
										"Symbols Nerd Font:pixelsize=14:type=2048-em:antialias:true:autohint:true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#37374f";
#include "themes/nord.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	/*SchemeNorm      普通      */   { black, "#FFDEAD", "#444444" }, // 
	/*SchemeSel       选中      */   { red2, "#88c0d0", "#f09a7f" },      //SchemeSel,    选中的
	/*SchemeSelGlobal 全局选中  */   { "#ffffff", "#47575F", "#fcf86f" },
	/*SchemeTabSel    选中tag   */   { red2,    black,  black },
	/*SchemeTabNorm   普通tag   */   { white,   black,  black },
	/*SchemeUnderline 下划线    */   { red2, black, black }, 
	/*SchemeMode      模式      */   { green,   black,  black },
	/*SchemeHid       隐藏      */   { "#dddddd", NULL, NULL },
	/*SchemeSystray   托盘      */   { NULL, blue, NULL },
	/*SchemeNormTag   普通标签  */   { "#aaaaaa", "#333333", NULL },
	/*SchemeSelTag    选中标签  */   { "#eeeeee", "#333333", NULL },
	/*SchemeBarEmpty  空白状态栏*/   { "#1e222a", "#1e222a", NULL },
	/*SchemeOverView  overview  */   { red2, black, black },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* launcher commands (They must be NULL terminated) */
static const char* net[]      = { "microsoft-edge-stable", NULL, NULL };
static const char* obs[]      = { "obs", NULL, NULL };

static const Launcher launchers[] = {
       /* command       name to display */
	{ net,         "edge" },
	{ obs,         "obs" },
};

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

#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[G]",      gaplessgrid },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", NULL };
static const char *alacrittycmd[] = { "alacritty", NULL };
static const char *voldown[]  = { "/home/jh/dwm-noalpha/scripts/voldown.sh", NULL };
static const char *volup[]  = { "/home/jh/dwm-noalpha/scripts/volup.sh", NULL };
static const char *voltoggle[]  = { "/home/jh/dwm-noalpha/scripts/voltoggle.sh", NULL };
static const char *lightdown[]  = { "/home/jh/dwm-noalpha/scripts/lightdown.sh", NULL };
static const char *lightup[]  = { "/home/jh/dwm-noalpha/scripts/lightup.sh", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "70x24", NULL };
static const char *trayer[] = { "~/dwm-noalpha/script/trayer.sh", NULL }

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F5,      spawn,          {.v = lightdown } },
	{ MODKEY,                       XK_F6,      spawn,          {.v = lightup } },
	{ MODKEY,                       XK_F1,      spawn,          {.v = voltoggle } },
	{ MODKEY,                       XK_F2,      spawn,          {.v = voldown } },
	{ MODKEY,                       XK_F3,      spawn,          {.v = volup } },
	{ MODKEY,                       XK_z,      spawn,          {.v = trayer } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,				XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,						XK_a,		spawn,			{.v = alacrittycmd } },
	{ MODKEY,                       XK_c,		togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3] } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, 
	{ MODKEY,                       XK_o,      winview,        {0} },
	{ Mod1Mask,                     XK_Tab,    alttab,         {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

