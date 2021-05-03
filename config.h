/* See LICENSE file for copyright and license details. */

/* appearance */

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
static const char *fonts[]          = { "monospace:size=12", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=12";

/* colours */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]		= "#000000";

static const char col_cyan[]        = "#005577";
static const char col_border[]      = "#005577";

static const char *colors[][3]      = {
	/*               		   fg         bg         border   */
	[SchemeNorm] 		= { col_gray3, col_gray1, col_gray2  },
	[SchemeSel]  		= { col_gray4, col_cyan,  col_border },
	[SchemeStatus]  	= { col_gray3, col_gray1, col_black  }, /* Statusbar right {text,background, not used but cannot be empty} 				*/
	[SchemeTagsSel]  	= { col_gray4, col_cyan,  col_black  }, /* Tagbar left selected {text,background, not used but cannot be empty}			*/
    [SchemeTagsNorm]  	= { col_gray3, col_gray1, col_black  }, /* Tagbar left unselected {text,background, not used but cannot be empty} 		*/
    [SchemeInfoSel]  	= { col_gray4, col_cyan,  col_black  }, /* infobar middle selected {text,background, not used but cannot be empty}		*/
    [SchemeInfoNorm]  	= { col_gray3, col_gray1, col_black  }, /* infobar middle unselected {text,background, not used but cannot be empty}	*/
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
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *browsercmd[]  = { "brave", NULL };
static const char *muttcmd[]  = { "st", "-e", "neomutt", NULL };
static const char *newsboatcmd[]  = { "st", "-e", "newsboat", NULL };
static const char *scrotcmd[]  = { "scrot", "-e", "mv $f ~/pictures/screenshots", NULL };
static const char *termcmd[]  = { "st", "-f", "monospace:size=16", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,            	        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,            	        XK_e, 	   spawn,          {.v = muttcmd } },
	{ MODKEY,            	        XK_n, 	   spawn,          {.v = newsboatcmd } },
	{ MODKEY|ShiftMask,    	        XK_Return, spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,    	        XK_p,	   spawn,          {.v = scrotcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      focusmaster,    {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,				XK_i,      incnmaster,     {.i = -1 } },
	{ Mod1Mask|ShiftMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ Mod1Mask|ShiftMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,             			XK_z, 	   zoom,           {0} },
	{ MODKEY|ShiftMask,     		XK_h, 	   zoom,           {0} },
	{ MODKEY|ShiftMask,    			XK_l, 	   zoom,           {0} },
	{ MODKEY,             			XK_u, 	   incrgaps,       {.i = +2} },
	{ MODKEY|ShiftMask,    			XK_u, 	   incrgaps,       {.i = -2} },
	{ MODKEY,             			XK_i, 	   incrigaps,      {.i = +2} },
	{ MODKEY|ShiftMask,    			XK_i, 	   incrigaps,      {.i = -2} },
	{ MODKEY,             			XK_o, 	   incrogaps,      {.i = +2} },
	{ MODKEY|ShiftMask,    			XK_o, 	   incrogaps,      {.i = -2} },
	{ MODKEY|ShiftMask,    			XK_g, 	   togglegaps,     {0} },
	{ MODKEY|ShiftMask,    			XK_equal,  defaultgaps,    {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_m, 	   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,  	   tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
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

