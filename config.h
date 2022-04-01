/* See LICENSE file for copyright and license details. */
/* settings */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* fonts */
static const char *fonts[]          = { "monospace:size=16", "JoyPixels:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=14";

/* colours */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]		= "#000000";

static const char col_bg[]          = "#3e445e";
static const char col_cyan[]        = "#005577";
// static const char col_focus[]       = "#e2181c";
static const char col_focus[]       = "#ffddff";
static const char col_border[]      = "#efe00e";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] 	= { norm_fg,    norm_bg,   	norm_border }, // unfocused wins
	[SchemeSel]  	= { sel_fg,     sel_bg,    	sel_border },  // the focused win
	[SchemeStatus] 	= { norm_fg,   	norm_bg,   	norm_border }, /* Statusbar right {text,background, not used but cannot be empty} 				*/
	[SchemeTagsSel] = { sel_fg, 	sel_bg,  	sel_border }, /* Tagbar left selected {text,background, not used but cannot be empty}			*/
    [SchemeTagsNorm]  	= { col_gray3, col_gray1, col_black  }, /* Tagbar left unselected {text,background, not used but cannot be empty} 		*/
    [SchemeInfoSel]  	= { norm_fg, 	norm_bg,  	norm_border  }, /* infobar middle selected {text,background, not used but cannot be empty}		*/
    [SchemeInfoNorm]  	= { col_gray3, col_gray1, col_black  }, /* infobar middle unselected {text,background, not used but cannot be empty}	*/
};

typedef struct {
const char *name;
	const void *cmd;
} Sp;

// Hardcoded, instead of using ENV Var.
static const char cmd_home[]      = "/home/andrew/documents/university/4B/";
const char *spcmd1[] = {"st", "-n", "sppython", "-g", "120x34", "-e", "python", "-q", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "lfub", "-d", cmd_home, NULL };
const char *spcmd3[] = {"st", "-n", "spfzf", "-g", "80x36", "-e", "lfub", "--cmd=fzf_select", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"sppython",     spcmd1},
	{"spfm",         spcmd2},
	{"spfzf",	 spcmd3}
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
	{ NULL,       "sppython", NULL,       SPTAG(0),     1,           -1 },
	{ NULL,       "spfm",     NULL,       SPTAG(1),     1,           -1 },
	{ NULL,       "spfzf",    NULL,       SPTAG(2),     1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },    /* first entry is default */
	{ "|||",	col },
	{ "><>",	NULL },    /* no layout function means floating behavior */
	{ "[M]",	monocle },
	{ "[@]",	spiral },
	{ "[\\]",	dwindle },
	{ "|M|",	centeredmaster }, 
	{ ">M>",	centeredfloatingmaster },
};

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define MONITORKEYS(KEY,TAG) \
	{ ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
    { ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_m,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
/*	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "shift-tools.c"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F1,     spawn,          SHCMD("aplkeys on") },
	{ MODKEY,             			XK_F2,     spawn,          SHCMD("aplkeys off") },

	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)


	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_q,      spawn,     	   SHCMD("slock") },
	{ MODKEY,            			XK_w,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,            	XK_w,      togglegaps,     {0} },
	{ MODKEY,            	        XK_e, 	   spawn,          SHCMD("st -e neomutt") },
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY,            	        XK_r, 	   togglescratch,  {.ui = 1} },
//  	{ MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("") },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* Tile. */
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} }, /* Columns. */
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} }, /* Monocle. */
//	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[4]} }, /* Spiral. */
//	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} }, /* Dwindle. */
// 	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[6]} }, /* CentredMaster. */
//	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[7]} }, /* CentredFloatingMaster. */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },         
	{ MODKEY|ShiftMask,				XK_i,      incnmaster,     {.i = -1 } },
//  	{ MODKEY,            	        XK_o, 	   spawn,          SHCMD("") },
//  	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("") },
	{ MODKEY,            	        XK_p, 	   togglescratch,  {.ui = 0} },
	{ MODKEY|ShiftMask,    	        XK_p,	   spawn,          SHCMD("screenclip") },
	{ MODKEY,                       XK_backslash, view,        {0} },

	{ MODKEY,            	        XK_s, 	   togglescratch,  {.ui = 2} },
	{ MODKEY|ShiftMask,             XK_s, 	   spawn,          SHCMD("st -f \"monospace:size=20\" -e calcurse") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,       	    XK_d,	   spawn,          SHCMD("passmenu --type") },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} }, /* Float. */
	{ MODKEY,            			XK_g, 	   shiftview,      {.i = -1} },
	{ MODKEY|ShiftMask,    			XK_g, 	   shifttag,       {.i = -1} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
//  	{ MODKEY|ShiftMask,       	    XK_h,	   spawn,          SHCMD("") },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//  	{ MODKEY|ShiftMask,       	    XK_l,	   spawn,          SHCMD("") },
	{ MODKEY,            			XK_semicolon, 	   shiftview,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_semicolon, 	   shifttag,       {.i = +1} },
  	{ MODKEY,             			XK_Return, spawn,          SHCMD("st -f \"monospace:size=20\"") },
	{ MODKEY|ShiftMask,    	        XK_Return, spawn,          SHCMD("brave") },


	{ MODKEY,    			        XK_z, 	   incrgaps,       {.i = -3} },
//  	{ MODKEY|ShiftMask,       	    XK_z,	   spawn,          SHCMD("") },
	{ MODKEY,             			XK_x, 	   incrgaps,       {.i = +3} },
//  	{ MODKEY|ShiftMask,       	    XK_x,	   spawn,          SHCMD("") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
//  	{ MODKEY|ShiftMask,       	    XK_b,	   spawn,          SHCMD("") },
	{ MODKEY,            	        XK_n, 	   spawn,          SHCMD("st -e newsboat") },
//  	{ MODKEY|ShiftMask,       	    XK_n,	   spawn,          SHCMD("") },
	{ MODKEY,       	            XK_period, spawn,          SHCMD("st -e ncmpcpp") },
//  	{ MODKEY|Shift,       	        XK_period, spawn,      SHCMD("") },

	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

//  	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
//  	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,			            XK_Left,    focusmon,	   {.i = -1} },
	{ MODKEY|ShiftMask,		        XK_Left,	tagmon,	       {.i = -1} },
	{ MODKEY,			            XK_Right,	focusmon,	   {.i = +1} },
	{ MODKEY|ShiftMask,		        XK_Right,	tagmon,	       {.i = +1} },

	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("light -A 5") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("light -U 5") },

/* How to bind modifiers only */
//  	{ MODKEY,			            XK_Shift_L, focusmon,	{.i = +1 } },


	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

// Non-scalable; better to label monitors
	MONITORKEYS(                    XK_1,                      0)
	MONITORKEYS(                    XK_2,                      1)
	MONITORKEYS(                    XK_3,                      2)

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

