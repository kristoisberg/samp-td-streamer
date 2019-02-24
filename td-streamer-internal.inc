#if defined _TDS_internal_included
    #endinput
#endif
#define _TDS_internal_included


#if !defined CHAIN_ORDER
    #define CHAIN_ORDER() 0
#endif

#define PRE_HOOK(%0) forward @CO_%0();public @CO_%0(){return CHAIN_ORDER()+1;}

static stock _TDS_IncludeStates() <_ALS : _ALS_x0, _ALS : _ALS_x1, _ALS : _ALS_x2, _ALS : _ALS_x3> {}
static stock _TDS_IncludeStates() <_ALS : _ALS_go> {}

#define _TDS_FORWARD%0(%1); \
	forward%0(%1); \
	public%0(%1) <_ALS : _ALS_x0, _ALS : _ALS_x1> { return 1; } \
	public%0(%1) <> { return 1; }


enum _:E_TD_STREAMER_PROPERTIES {
    E_TD_FONT,
    E_TD_COLOUR,
    E_TD_ALIGNMENT,
    E_TD_SHADOW_SIZE,
    E_TD_OUTLINE_WIDTH,
    E_TD_BACKGROUND_COLOUR,

    bool:E_TD_IS_PROPORTIONAL,
    bool:E_TD_IS_SELECTABLE,

    Float:E_TD_TEXT_SIZE_X,
    Float:E_TD_TEXT_SIZE_Y,

    Float:E_TD_LETTER_SIZE_X,
    Float:E_TD_LETTER_SIZE_Y,

    bool:E_TD_HAS_BOX,
    E_TD_BOX_COLOUR,

    E_TD_PREVIEW_MODEL,
    E_TD_PREVIEW_VEHICLE_COLOUR_1,
    E_TD_PREVIEW_VEHICLE_COLOUR_2,
    Float:E_TD_PREVIEW_ROT_X,
    Float:E_TD_PREVIEW_ROT_Y,
    Float:E_TD_PREVIEW_ROT_Z,
    Float:E_TD_PREVIEW_ZOOM,
    
    E_TD_EXTRA1,
    E_TD_EXTRA2
}

new TDDefaultProperties[E_TD_STREAMER_PROPERTIES] = {
    1,
    0xE1E1E1FF,
    0,
    2,
    0,
    0x000000FF,
    true,
    false,
    1280.0,
    1280.0,
    0.48,
    1.12,
    false,
    0x80808080,
    0,
    0xFFFF,
    0xFFFF,
    0.0,
    0.0,
    0.0,
    1.0
};
