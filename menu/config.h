static int topbar = 0;
static int centered = 1;
static int min_width = 1000;
static int fuzzy = 1;
static const char *fonts[]          = { "monospace:size=18" };

static const char *prompt      = NULL;
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#7c9f85", "#292f2f" },
	[SchemeSel] = { "#7c9f85", "#454e4e" },
	[SchemeSelHighlight] = { "#d7d7d7", "#282f36" },
	[SchemeNormHighlight] = { "#c5a47b", "#282f36" },
	[SchemeOut] = { "#000000", "#00ffff" },
	[SchemeMid] = { "#7c9f85", "#292d2f" },
};

static unsigned int lines      = 0;
static unsigned int lineheight = 22;
static unsigned int columns    = 0;

static const char worddelimiters[] = " ";

static unsigned int border_width = 3;
