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


static stock _CreateTextDraw(id) {
    new data[E_TD_STREAMER_GLOBAL_DATA];
    _GetTextDrawData(id, data);

    new string[1024];
    str_get(data[E_TD_STRING], string);

    data[E_TD_INTERNAL_ID] = TextDrawCreate(data[E_TD_POS_X], data[E_TD_POS_Y], string);

    if (data[E_TD_PROPERTIES][E_TD_FONT] != TDDefaultProperties[E_TD_FONT]) {
        TextDrawFont(data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_FONT]);
    }

    _SetTextDrawData(id, data);
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
        _CreateTextDraw(id);
    }

    PA_Set(data[E_TD_VISIBLE], playerid, true);
    TextDrawShowForPlayer(playerid, data[E_TD_INTERNAL_ID]);
    return 1;
}

#if defined _ALS_TextDrawShowForPlayer
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawShowForPlayer
#endif
#define TextDrawShowForPlayer TDS_TextDrawShowForPlayer