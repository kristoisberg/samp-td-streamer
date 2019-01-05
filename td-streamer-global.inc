#if defined _TDS_global_included
    #endinput
#endif
#define _TDS_global_included


#include <a_samp>
#include <PawnPlus>
#include <YSI_Data\y_playerarray>
#include <YSI_Data\y_iterate>
#include <YSI_Server\y_scriptinit>

#include "td-streamer-internal.inc"


PRE_HOOK(TDSG)
#undef CHAIN_ORDER
#define CHAIN_ORDER @CO_TDSG


static enum _:E_TD_STREAMER_GLOBAL_DATA {
    String:E_TD_STRING,
    Text:E_TD_INTERNAL_ID,
    PlayerArray:E_TD_VISIBLE<MAX_PLAYERS>,

    Float:E_TD_POS_X,
    Float:E_TD_POS_Y,

    E_TD_PROPERTIES[E_TD_STREAMER_PROPERTIES]
}


static List:TDData;
static TDStreamerID[MAX_TEXT_DRAWS] = {-1, ...};


native Text:_TDS_TextDrawCreate(Float:x, Float:y, AmxString:text) = TextDrawCreate;
native _TDS_TextDrawSetString(Text:text, AmxString:string) = TextDrawSetString;


static stock bool:_IsValidTextDraw(id) {
    return list_size(TDData) > id && list_sizeof(TDData, id) != 0;
}


static stock bool:_GetTextDrawData(id, data[E_TD_STREAMER_GLOBAL_DATA]) {
    if (!_IsValidTextDraw(id)) {
        return false;
    }

    list_get_arr(TDData, id, data, sizeof(data));
    return true;
}


static stock bool:_SetTextDrawData(id, const data[E_TD_STREAMER_GLOBAL_DATA]) {
    if (!_IsValidTextDraw(id)) {
        return false;
    }

    list_set_arr(TDData, id, data);
    return true;
}


static stock _CreateTextDraw(id, data[E_TD_STREAMER_GLOBAL_DATA]) {
    data[E_TD_INTERNAL_ID] = _TDS_TextDrawCreate(data[E_TD_POS_X], data[E_TD_POS_Y], data[E_TD_STRING]);

    if (data[E_TD_INTERNAL_ID] == Text:INVALID_TEXT_DRAW) {
        return 1;
    }

    TDStreamerID[_:data[E_TD_INTERNAL_ID]] = id;

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
    TDStreamerID[_:data[E_TD_INTERNAL_ID]] = -1;

    TextDrawDestroy(data[E_TD_INTERNAL_ID]);

    data[E_TD_INTERNAL_ID] = Text:INVALID_TEXT_DRAW;
}


public OnScriptInit() {
    state _ALS : _ALS_go;

    TDData = list_new();

    return TDSG_OnScriptInit();
}

#if defined _ALS_OnScriptInit
    #undef OnScriptInit
#else
	#define _ALS_OnScriptInit
#endif
#define OnScriptInit() TDSG_OnScriptInit() <_ALS : _ALS_go>

_TDS_FORWARD TDSG_OnScriptInit();


public OnScriptExit() {
    state _ALS : _ALS_go;

    new data[E_TD_STREAMER_GLOBAL_DATA];

    for (new Iter:id = list_iter(TDData); iter_inside(id); iter_move_next(id)) {
        if (!iter_sizeof(id)) {
            continue;
        }

        iter_get_arr(id, data);

        if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
            TextDrawDestroy(data[E_TD_INTERNAL_ID]);
        }

        str_delete(data[E_TD_STRING]);
    }

    list_delete(TDData);

    return TDSG_OnScriptExit();
}

#if defined _ALS_OnScriptExit
    #undef OnScriptExit
#else
	#define _ALS_OnScriptExit
#endif
#define OnScriptExit() TDSG_OnScriptExit() <_ALS : _ALS_go>

_TDS_FORWARD TDSG_OnScriptExit();


public OnPlayerDisconnect(playerid, reason) {
    state _ALS : _ALS_go;

    new data[E_TD_STREAMER_GLOBAL_DATA];

    for (new id; id < MAX_TEXT_DRAWS; id++) {
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

    return TDSG_OnPlayerDisconnect(playerid, reason);
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect(%0) TDSG_OnPlayerDisconnect(%0) <_ALS : _ALS_go>

_TDS_FORWARD TDSG_OnPlayerDisconnect(playerid, reason);


public OnPlayerClickTextDraw(playerid, Text:clickedid) {
    state _ALS : _ALS_go;

    if (clickedid == Text:INVALID_TEXT_DRAW) {
        return TDSG_OnPlayerClickTextDraw(playerid, clickedid);
    }

    new id = TDStreamerID[_:clickedid];

    if (id == -1) {
        return 0;
    }

    new data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data) || !data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] || !PA_Get(data[E_TD_VISIBLE], playerid)) {
        return 1;
    }

    return TDSG_OnPlayerClickTextDraw(playerid, Text:id);
}

#if defined _ALS_OnPlayerClickTextDraw
    #undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw(%0) TDSG_OnPlayerClickTextDraw(%0) <_ALS : _ALS_go>

_TDS_FORWARD TDSG_OnPlayerClickTextDraw(playerid, Text:clickedid);


stock Text:TDS_TextDrawCreate(Float:x, Float:y, const text[]) {
    new data[E_TD_STREAMER_GLOBAL_DATA];

    data[E_TD_STRING] = str_acquire(str_new(text));
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


stock Text:TextDrawCreate_s(Float:x, Float:y, String:text) {
    new data[E_TD_STREAMER_GLOBAL_DATA];

    data[E_TD_STRING] = str_acquire(str_clone(text));
    data[E_TD_INTERNAL_ID] = Text:INVALID_TEXT_DRAW;
    data[E_TD_PROPERTIES] = TDDefaultProperties;

    data[E_TD_POS_X] = x;
    data[E_TD_POS_Y] = y;

    PA_Init(data[E_TD_VISIBLE]);
    return Text:list_add_arr(TDData, data);
}


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

    str_delete(data[E_TD_STRING]);

    list_set_var(TDData, id, VAR_NULL);
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

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        PA_Set(data[E_TD_VISIBLE], playerid, true);
        TextDrawShowForPlayer(playerid, data[E_TD_INTERNAL_ID]);

        _SetTextDrawData(id, data);
    }

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

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawHideForPlayer(playerid, data[E_TD_INTERNAL_ID]);

        if (!Bit_Count(data[E_TD_VISIBLE])) {
            _DestroyTextDraw(data);
        }
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

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        foreach (new playerid : Player) {
            PA_Set(data[E_TD_VISIBLE], playerid, true);
        }
        
        TextDrawShowForAll(data[E_TD_INTERNAL_ID]);

        _SetTextDrawData(id, data);
    }

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

    Bit_SetAll(data[E_TD_VISIBLE], false);

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawHideForAll(data[E_TD_INTERNAL_ID]);

        _DestroyTextDraw(data);
    }

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


stock TDS_TextDrawSetString(Text:text, const string[]) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetString(data[E_TD_INTERNAL_ID], string);
    }

    str_set(data[E_TD_STRING], str_new(string));
    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetString
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetString
#endif
#define TextDrawSetString TDS_TextDrawSetString


stock TDS_TextDrawGetString(Text:text, string[], len = sizeof(string)) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    str_get(data[E_TD_STRING], string, len);
    return 1;
}

#if defined _ALS_TextDrawGetString
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetString
#endif
#define TextDrawGetString TDS_TextDrawGetString


stock TextDrawSetString_s(Text:text, String:string) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        _TDS_TextDrawSetString(data[E_TD_INTERNAL_ID], string);
    }

    str_set(data[E_TD_STRING], string);
    _SetTextDrawData(id, data);
    return 1;
}


stock String:TextDrawGetString_s(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return STRING_NULL;
    }

    return str_clone(data[E_TD_STRING]);
}


stock TDS_TextDrawSetPos(Text:text, Float:x, Float:y) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_POS_X] = x;
    data[E_TD_POS_Y] = y;

    #if defined TextDrawSetPos
        if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
            TextDrawSetPos(data[E_TD_INTERNAL_ID], x, y);
        }
    #elseif defined TextDrawSetPosition
        if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
            TextDrawSetPosition(data[E_TD_INTERNAL_ID], x, y);
        }
    #endif

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetPos
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetPos
#endif
#define TextDrawSetPos TDS_TextDrawSetPos

#if defined TextDrawSetPosition
    #if defined _ALS_TextDrawSetPosition
        #error TextDraw streamer must be the first library to hook any textdraw functions!
    #else
        #define _ALS_TextDrawSetPosition
    #endif
    #define TextDrawSetPosition TDS_TextDrawSetPos
#endif


stock TDS_TextDrawGetPos(Text:text, &Float:x, &Float:y) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    x = data[E_TD_POS_X];
    y = data[E_TD_POS_Y];

    return 1;
}

#if defined _ALS_TextDrawGetPos
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetPos
#endif
#define TextDrawGetPos TDS_TextDrawGetPos


stock TDS_TextDrawLetterSize(Text:text, Float:x, Float:y) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X] = x;
    data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y] = y;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawLetterSize(data[E_TD_INTERNAL_ID], x, y);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawLetterSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawLetterSize
#endif
#define TextDrawLetterSize TDS_TextDrawLetterSize


stock TDS_TextDrawGetLetterSize(Text:text, &Float:x, &Float:y) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    x = data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X];
    y = data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y];

    return 1;
}

#if defined _ALS_TextDrawGetLetterSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetLetterSize
#endif
#define TextDrawGetLetterSize TDS_TextDrawGetLetterSize


stock TDS_TextDrawTextSize(Text:text, Float:x, Float:y) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X] = x;
    data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y] = y;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawTextSize(data[E_TD_INTERNAL_ID], x, y);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawTextSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawTextSize
#endif
#define TextDrawTextSize TDS_TextDrawTextSize


stock TDS_TextDrawGetTextSize(Text:text, &Float:x, &Float:y) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    x = data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X];
    y = data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y];

    return 1;
}

#if defined _ALS_TextDrawGetTextSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetTextSize
#endif
#define TextDrawGetTextSize TDS_TextDrawGetTextSize


stock TDS_TextDrawColor(Text:text, color) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_COLOUR] = color;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawColor(data[E_TD_INTERNAL_ID], color);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawColor
#endif
#define TextDrawColor TDS_TextDrawColor


stock TDS_TextDrawGetColor(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_COLOUR];
}

#if defined _ALS_TextDrawGetColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetColor
#endif
#define TextDrawGetColor TDS_TextDrawGetColor


stock TDS_TextDrawBoxColor(Text:text, color) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_BOX_COLOUR] = color;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawBoxColor(data[E_TD_INTERNAL_ID], color);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawBoxColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawBoxColor
#endif
#define TextDrawBoxColor TDS_TextDrawBoxColor


stock TDS_TextDrawGetBoxColor(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_BOX_COLOUR];
}

#if defined _ALS_TextDrawGetBoxColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetBoxColor
#endif
#define TextDrawGetBoxColor TDS_TextDrawGetBoxColor


stock TDS_TextDrawBackgroundColor(Text:text, color) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR] = color;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawBackgroundColor(data[E_TD_INTERNAL_ID], color);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawBackgroundColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawBackgroundColor
#endif
#define TextDrawBackgroundColor TDS_TextDrawBackgroundColor


stock TDS_TextDrawGetBackgroundColor(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR];
}

#if defined _ALS_TextDrawGetBackgroundColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetBackgroundColor
#endif
#define TextDrawGetBackgroundColor TDS_TextDrawGetBackgroundColor


stock TDS_TextDrawSetShadow(Text:text, size) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE] = size;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetShadow(data[E_TD_INTERNAL_ID], size);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetShadow
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetShadow
#endif
#define TextDrawSetShadow TDS_TextDrawSetShadow


stock TDS_TextDrawGetShadow(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE];
}

#if defined _ALS_TextDrawGetShadow
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetShadow
#endif
#define TextDrawGetShadow TDS_TextDrawGetShadow


stock TDS_TextDrawSetOutline(Text:text, size) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH] = size;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetOutline(data[E_TD_INTERNAL_ID], size);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetOutline
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetOutline
#endif
#define TextDrawSetOutline TDS_TextDrawSetOutline


stock TDS_TextDrawGetOutline(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH];
}

#if defined _ALS_TextDrawGetOutline
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetOutline
#endif
#define TextDrawGetOutline TDS_TextDrawGetOutline


stock TDS_TextDrawFont(Text:text, font) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_FONT] = font;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawFont(data[E_TD_INTERNAL_ID], font);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawFont
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawFont
#endif
#define TextDrawFont TDS_TextDrawFont


stock TDS_TextDrawGetFont(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_FONT];
}

#if defined _ALS_TextDrawGetFont
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetFont
#endif
#define TextDrawGetFont TDS_TextDrawGetFont


stock TDS_TextDrawUseBox(Text:text, use) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_HAS_BOX] = !!use;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawUseBox(data[E_TD_INTERNAL_ID], use);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawUseBox
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawUseBox
#endif
#define TextDrawUseBox TDS_TextDrawUseBox


stock TDS_TextDrawIsBox(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_HAS_BOX];
}

#if defined _ALS_TextDrawIsBox
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawIsBox
#endif
#define TextDrawIsBox TDS_TextDrawIsBox


stock TDS_TextDrawSetProportional(Text:text, set) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL] = !!set;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetProportional(data[E_TD_INTERNAL_ID], set);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetProportional
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetProportional
#endif
#define TextDrawSetProportional TDS_TextDrawSetProportional


stock TDS_TextDrawIsProportional(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL];
}

#if defined _ALS_TextDrawIsProportional
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawIsProportional
#endif
#define TextDrawIsProportional TDS_TextDrawIsProportional


stock TDS_TextDrawSetSelectable(Text:text, set) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] = !!set;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetSelectable(data[E_TD_INTERNAL_ID], set);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetSelectable
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetSelectable
#endif
#define TextDrawSetSelectable TDS_TextDrawSetSelectable


stock TDS_TextDrawIsSelectable(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE];
}

#if defined _ALS_TextDrawIsSelectable
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawIsSelectable
#endif
#define TextDrawIsSelectable TDS_TextDrawIsSelectable


stock TDS_TextDrawAlignment(Text:text, alignment) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_ALIGNMENT] = alignment;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawAlignment(data[E_TD_INTERNAL_ID], alignment);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawAlignment
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawAlignment
#endif
#define TextDrawAlignment TDS_TextDrawAlignment


stock TDS_TextDrawGetAlignment(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_ALIGNMENT];
}

#if defined _ALS_TextDrawGetAlignment
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetAlignment
#endif
#define TextDrawGetAlignment TDS_TextDrawGetAlignment


stock TDS_TextDrawSetPreviewModel(Text:text, model) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL] = model;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetPreviewModel(data[E_TD_INTERNAL_ID], model);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetPreviewModel
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetPreviewModel
#endif
#define TextDrawSetPreviewModel TDS_TextDrawSetPreviewModel


stock TDS_TextDrawGetPreviewModel(Text:text) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL];
}

#if defined _ALS_TextDrawGetPreviewModel
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetPreviewModel
#endif
#define TextDrawGetPreviewModel TDS_TextDrawGetPreviewModel


stock TDS_TextDrawSetPreviewRot(Text:text, Float:x, Float:y, Float:z, Float:zoom = 1.0) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X] = x;
    data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y] = y;
    data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z] = z;

    data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM] = zoom;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetPreviewRot(data[E_TD_INTERNAL_ID], x, y, z, zoom);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetPreviewRot
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetPreviewRot
#endif
#define TextDrawSetPreviewRot TDS_TextDrawSetPreviewRot


stock TDS_TextDrawGetPreviewRot(Text:text, &Float:x, &Float:y, &Float:z, &Float:zoom) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    x = data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X];
    y = data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y];
    z = data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z];

    zoom = data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM];

    return 1;
}

#if defined _ALS_TextDrawGetPreviewRot
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetPreviewRot
#endif
#define TextDrawGetPreviewRot TDS_TextDrawGetPreviewRot


stock TDS_TextDrawSetPreviewVehCol(Text:text, color1, color2) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1] = color1;
    data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2] = color2;

    if (data[E_TD_INTERNAL_ID] != Text:INVALID_TEXT_DRAW) {
        TextDrawSetPreviewVehCol(data[E_TD_INTERNAL_ID], color1, color2);
    }

    _SetTextDrawData(id, data);
    return 1;
}

#if defined _ALS_TextDrawSetPreviewVehCol
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawSetPreviewVehCol
#endif
#define TextDrawSetPreviewVehCol TDS_TextDrawSetPreviewVehCol


stock TDS_TextDrawGetPreviewVehCol(Text:text, &color1, &color2) {
    new id = _:text, data[E_TD_STREAMER_GLOBAL_DATA];

    if (!_GetTextDrawData(id, data)) {
        return 0;
    }

    color1 = data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1];
    color2 = data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2];

    return 1;
}

#if defined _ALS_TextDrawGetPreviewVehCol
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_TextDrawGetPreviewVehCol
#endif
#define TextDrawGetPreviewVehCol TDS_TextDrawGetPreviewVehCol