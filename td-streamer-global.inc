#if defined _TDS_global_included
    #endinput
#endif
#define _TDS_global_included


#include <a_samp>
#include <PawnPlus>
#include <YSI-Data\y_playerarray>
#include <YSI-Server\y_scriptinit>
#include <YSI-Coding\y_hooks>


enum _:E_TD_STREAMER_GLOBAL_DATA {
    GlobalString:E_TD_STRING,
    Text:E_TD_INTERNAL_ID,
    PlayerArray:E_TD_VISIBLE<MAX_PLAYERS>,

    E_TD_FONT,
    E_TD_COLOUR,
    E_TD_ALIGNMENT,
    E_TD_SHADOW_SIZE,
    E_TD_OUTLINE_WIDTH,
    E_TD_BACKGROUND_COLOUR,

    bool:E_TD_IS_PROPORTIONAL,
    bool:E_TD_IS_SELECTABLE,

    Float:E_TD_POS_X,
    Float:E_TD_POS_Y,

    Float:E_TD_TEXT_SIZE_X,
    Float:E_TD_TEXT_SIZE_Y,

    bool:E_TD_HAS_BOX,
    E_TD_BOX_COLOUR,
    Float:E_TD_BOX_SIZE_X,
    Float:E_TD_BOX_SIZE_Y,

    E_TD_PREVIEW_MODEL,
    E_TD_PREVIEW_VEHICLE_COLOUR_1,
    E_TD_PREVIEW_VEHICLE_COLOUR_2,
    Float:E_TD_PREVIEW_ROT_X,
    Float:E_TD_PREVIEW_ROT_Y,
    Float:E_TD_PREVIEW_ROT_Z,
    Float:E_TD_PREVIEW_ZOOM
}


static List:TDData;
static TDStreamerID[Text:MAX_TEXT_DRAWS] = {-1, ...};


forward bool:_GetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]);


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


hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if (clickedid == Text:INVALID_TEXT_DRAW) {
        return Y_HOOKS_CONTINUE_RETURN_1;
    }

    if (TDStreamerID[clickedid] == -1) {
        return Y_HOOKS_BREAK_RETURN_0;
    }

    new data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(TDStreamerID[clickedid], data) || !data[E_TD_IS_SELECTABLE] || !PA_Get(data[E_TD_VISIBLE], playerid)) {
        return Y_HOOKS_BREAK_RETURN_0;
    }

    clickedid = Text:TDStreamerID[clickedid];
    return Y_HOOKS_CONTINUE_RETURN_1;
}


static bool:_GetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]) {
    if (list_tagof(TDData, id) == tagof(Var:)) { // the slot contains VAR_NULL so the textdraw has been deleted
        return false;
    }

    if (!list_get_arr(TDData, id, data)) {
        return false;
    }

    return true;
}