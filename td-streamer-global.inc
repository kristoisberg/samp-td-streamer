#if defined _TDS_global_included
    #endinput
#endif
#define _TDS_global_included


#include <a_samp>
#include <PawnPlus>
#include <YSI-Data\y_playerarray>
#include <YSI-Data\y_iterate>
#include <YSI-Server\y_scriptinit>
#include <YSI-Coding\y_hooks>

#include "td-streamer-internal.inc"


enum _:E_TD_STREAMER_GLOBAL_DATA {
    GlobalString:E_TD_STRING,
    Text:E_TD_INTERNAL_ID,
    PlayerArray:E_TD_VISIBLE<MAX_PLAYERS>,

    Float:E_TD_POS_X,
    Float:E_TD_POS_Y,

    E_TD_PROPERTIES[E_TD_STREAMER_PROPERTIES]
}


static List:TDData;
static TDStreamerID[Text:MAX_TEXT_DRAWS] = {-1, ...};


forward bool:_IsValidTextDraw(id);
forward bool:_GetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]);
forward bool:_SetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]);


hook OnScriptInit() {
    TDData = list_new();

    return Y_HOOKS_CONTINUE_RETURN_1;
}


hook OnScriptExit() {
    for (new Text:id; id < Text:MAX_TEXT_DRAWS; id++) {
        if (TDStreamerID[id] != -1) {
            TextDrawDestroy(id);
        }
    }

    return Y_HOOKS_CONTINUE_RETURN_1;
}


hook OnPlayerDisconnect(playerid, reason) {
    new data[E_TD_STREAMER_GLOBAL_DATA];

    for (new Text:id; id < Text:MAX_TEXT_DRAWS; id++) {
        if (TDStreamerID[id] != -1) {
            _GetTextDrawData(TDStreamerID[id], data);

            if (PA_Get(data[E_TD_VISIBLE], playerid)) {
                PA_Set(data[E_TD_VISIBLE], playerid, false);

                if (!Bit_Count(data[E_TD_VISIBLE])) {
                    _DestroyTextDraw(data);
                }

                _SetTextDrawData(TDStreamerID[id], data);
            }
        }
    }

    return Y_HOOKS_CONTINUE_RETURN_1;
}


hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if (clickedid == Text:INVALID_TEXT_DRAW) {
        return Y_HOOKS_CONTINUE_RETURN_1;
    }

    if (TDStreamerID[clickedid] == -1) {
        return Y_HOOKS_BREAK_RETURN_0;
    }

    new data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(TDStreamerID[clickedid], data) || !data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] || !PA_Get(data[E_TD_VISIBLE], playerid)) {
        return Y_HOOKS_BREAK_RETURN_0;
    }

    clickedid = Text:TDStreamerID[clickedid];
    return Y_HOOKS_CONTINUE_RETURN_1;
}


static stock bool:_IsValidTextDraw(id) {
    return list_sizeof(TDData, id) != 0;
}


static stock bool:_GetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]) {
    if (!_IsValidTextDraw(id)) {
        return false;
    }

    list_get_arr(TDData, id, data);
    return true;
}


static stock bool:_SetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]) {
    if (!_IsValidTextDraw(id)) {
        return false;
    }

    list_set_arr(TDData, id, data);
    return true;
}


static stock _CreateTextDraw(id, data[E_TD_STREAMER_GLOBAL_DATA]) {
    new string[1024];
    str_get(data[E_TD_STRING], string);

    data[E_TD_INTERNAL_ID] = TextDrawCreate(data[E_TD_POS_X], data[E_TD_POS_Y], string);

    if (data[E_TD_INTERNAL_ID] == Text:INVALID_TEXT_DRAW) {
        return 1;
    }

    TDStreamerID[data[E_TD_INTERNAL_ID]] = id;

    if (data[E_TD_PROPERTIES][E_TD_FONT] != TDDefaultProperties[E_TD_FONT]) {
        TextDrawFont(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_FONT]);
    }

    if (data[E_TD_PROPERTIES][E_TD_COLOUR] != TDDefaultProperties[E_TD_COLOUR]) {
        TextDrawColor(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_COLOUR]);
    }

    if (data[E_TD_PROPERTIES][E_TD_ALIGNMENT] != TDDefaultProperties[E_TD_ALIGNMENT]) {
        TextDrawAlignment(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_ALIGNMENT]);
    }

    if (data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE] != TDDefaultProperties[E_TD_SHADOW_SIZE]) {
        TextDrawSetShadow(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE]);
    }

    if (data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH] != TDDefaultProperties[E_TD_OUTLINE_WIDTH]) {
        TextDrawSetOutline(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH]);
    }

    if (data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR] != TDDefaultProperties[E_TD_BACKGROUND_COLOUR]) {
        TextDrawBackgroundColor(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR]);
    }

    if (data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL] != TDDefaultProperties[E_TD_IS_PROPORTIONAL]) {
        TextDrawSetProportional(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL]);
    }

    if (data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] != TDDefaultProperties[E_TD_IS_SELECTABLE]) {
        TextDrawSetSelectable(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X] != TDDefaultProperties[E_TD_TEXT_SIZE_X] ||
        data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y] != TDDefaultProperties[E_TD_TEXT_SIZE_Y]
    ) {
        TextDrawTextSize(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X], data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X] != TDDefaultProperties[E_TD_LETTER_SIZE_X] ||
        data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y] != TDDefaultProperties[E_TD_LETTER_SIZE_Y]
    ) {
        TextDrawLetterSize(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X], data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y]);
    }

    if (data[E_TD_PROPERTIES][E_TD_HAS_BOX] != TDDefaultProperties[E_TD_HAS_BOX]) {
        TextDrawUseBox(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_HAS_BOX]);
    }

    if (data[E_TD_PROPERTIES][E_TD_BOX_COLOUR] != TDDefaultProperties[E_TD_BOX_COLOUR]) {
        TextDrawBoxColor(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_BOX_COLOUR]);
    }

    if (data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL] != TDDefaultProperties[E_TD_PREVIEW_MODEL]) {
        TextDrawSetPreviewModel(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1] != TDDefaultProperties[E_TD_PREVIEW_VEHICLE_COLOUR_1] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2] != TDDefaultProperties[E_TD_PREVIEW_VEHICLE_COLOUR_2]
    ) {
        TextDrawSetPreviewVehCol(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1], data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X] != TDDefaultProperties[E_TD_PREVIEW_ROT_X] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y] != TDDefaultProperties[E_TD_PREVIEW_ROT_Y] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z] != TDDefaultProperties[E_TD_PREVIEW_ROT_Z] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM] != TDDefaultProperties[E_TD_PREVIEW_ZOOM]
    ) {
        TextDrawSetPreviewRot(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X], data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y], data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z], data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM]);
    }

    return 1;
}


static stock _DestroyTextDraw(data[E_TD_STREAMER_GLOBAL_DATA]) {
    TDStreamerID[data[E_TD_INTERNAL_ID]] = -1;

    TextDrawDestroy(data[E_TD_INTERNAL_ID]);

    data[E_TD_INTERNAL_ID] = Text:INVALID_TEXT_DRAW;
    return 1;
}


stock Text:TDS_TextDrawCreate(Float:x, Float:y, const text[]) {
    new data[E_TD_STREAMER_GLOBAL_DATA];

    data[E_TD_STRING] = str_to_global(str_new(text));
    data[E_TD_INTERNAL_ID] = Text:INVALID_TEXT_DRAW;
    data[E_TD_PROPERTIES] = TDDefaultProperties;

    data[E_TD_POS_X] = x;
    data[E_TD_POS_Y] = y;

    PA_Init(data[E_TD_VISIBLE]);
    return Text:list_add_arr(TDData, data);
}

#if defined _ALS_TextDrawCreate
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawCreate
#endif
#define TextDrawCreate TDS_TextDrawCreate


stock TDS_IsValidTextDraw(Text:text) {
    return _IsValidTextDraw(_:text);
}

#if defined _ALS_IsValidTextDraw
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_IsValidTextDraw
#endif
#define IsValidTextDraw TDS_IsValidTextDraw


stock TDS_TextDrawDestroy(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        _DestroyTextDraw(data);
    }

    list_set(TDData, id, VAR_NULL);
    return 1;
}

#if defined _ALS_TextDrawDestroy
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawDestroy
#endif
#define TextDrawDestroy TDS_TextDrawDestroy


stock TDS_TextDrawShowForPlayer(playerid, Text:text) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] == Text:INVALID_TEXT_DRAW) {
        _CreateTextDraw(id, data);
    }

    PA_Set(data[E_TD_VISIBLE], playerid, true);
    TextDrawShowForPlayer(playerid, data[E_TD_INTERNAL_ID]);

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawShowForPlayer
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawShowForPlayer
#endif
#define TextDrawShowForPlayer TDS_TextDrawShowForPlayer


stock TDS_TextDrawHideForPlayer(playerid, Text:text) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    PA_Set(data[E_TD_VISIBLE], playerid, false);
    TextDrawHideForPlayer(playerid, data[E_TD_INTERNAL_ID]);

    if (!Bit_Count(data[E_TD_VISIBLE])) {
        _DestroyTextDraw(data);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawHideForPlayer
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawHideForPlayer
#endif
#define TextDrawHideForPlayer TDS_TextDrawHideForPlayer


stock TDS_TextDrawShowForAll(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] == Text:INVALID_TEXT_DRAW) {
        _CreateTextDraw(id, data);
    }

    foreach (new playerid : Player) {
        PA_Set(data[E_TD_VISIBLE], playerid, true);
    }
    
    TextDrawShowForAll(data[E_TD_INTERNAL_ID]);

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawShowForAll
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawShowForAll
#endif
#define TextDrawShowForAll TDS_TextDrawShowForAll


stock TDS_TextDrawHideForAll(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    PA_SetAll(data[E_TD_VISIBLE], false);
    TextDrawHideForAll(data[E_TD_INTERNAL_ID]);

    _DestroyTextDraw(data);
    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawHideForAll
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawHideForAll
#endif
#define TextDrawHideForAll TDS_TextDrawHideForAll


stock TDS_IsTextDrawVisibleForPlayer(playerid, Text:text) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return PA_Get(data[E_TD_VISIBLE], playerid);
}

#if defined _ALS_IsTextDrawVisibleForPlayer
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_IsTextDrawVisibleForPlayer
#endif
#define IsTextDrawVisibleForPlayer TDS_IsTextDrawVisibleForPlayer