#if defined _TDS_internal_included
    #endinput
#endif
#define _TDS_internal_included


#define INVALID_TEXTDRAW_EXTRA_ID 	(cellmin)

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
    Float:E_TD_PREVIEW_ZOOM
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
