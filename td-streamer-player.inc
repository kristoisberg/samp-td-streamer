#if defined _TDS_player_included
    #endinput
#endif
#define _TDS_player_included


#include <a_samp>
#include <PawnPlus>

#include "td-streamer-internal.inc"


static enum _:E_TD_STREAMER_PLAYER_DATA {
    String:E_TD_STRING,
    PlayerText:E_TD_INTERNAL_ID,
    bool:E_TD_VISIBLE,

    Float:E_TD_POS_X,
    Float:E_TD_POS_Y,
    
    E_TD_EXTRA_1,
    E_TD_EXTRA_2,

    E_TD_PROPERTIES[E_TD_STREAMER_PROPERTIES]
};


static Pool:TextDrawPool[MAX_PLAYERS];
static TextDrawStreamerID[MAX_PLAYERS][MAX_PLAYER_TEXT_DRAWS];


native PlayerText:_TDS_CreatePlayerTextDraw(playerid, Float:x, Float:y, AmxString:text) = CreatePlayerTextDraw;
native _TDS_PlayerTextDrawSetString(playerid, PlayerText:text, AmxString:string) = PlayerTextDrawSetString;


static stock Pool:_GetTextDrawPool(playerid) {
    if (!IsPlayerConnected(playerid)) {
        return INVALID_POOL;
    }

    if (!pool_valid(TextDrawPool[playerid])) {
        TextDrawPool[playerid] = pool_new();

        for (new PlayerText:id; id < MAX_PLAYER_TEXT_DRAWS; id++) {
            TextDrawStreamerID[playerid][id] = -1;
        }
    }

    return TextDrawPool[playerid];
}


static stock bool:_IsValidTextDraw(playerid, id, &Pool:pool = INVALID_POOL) {
    pool = _GetTextDrawPool(playerid);

    return pool_valid(pool) && pool_has(pool, id);
}


static stock bool:_GetTextDrawData(playerid, id, data[E_TD_STREAMER_PLAYER_DATA], &Pool:pool = INVALID_POOL) {
    if (!_IsValidTextDraw(playerid, id, pool)) {
        return false;
    }

    pool_get_arr(pool, id, data);
    return true;
}


static stock bool:_SetTextDrawData(playerid, id, const data[E_TD_STREAMER_PLAYER_DATA]) {
    new Pool:pool;

    if (!_IsValidTextDraw(playerid, id, pool)) {
        return false;
    }

    pool_set_arr(pool, id, data);
    return true;
}


static stock _CreateTextDraw(playerid, id, data[E_TD_STREAMER_PLAYER_DATA]) {
    data[E_TD_INTERNAL_ID] = _TDS_CreatePlayerTextDraw(playerid, data[E_TD_POS_X], data[E_TD_POS_Y], data[E_TD_STRING]);

    if (data[E_TD_INTERNAL_ID] == PlayerText:INVALID_TEXT_DRAW) {
        return 1;
    }

    TextDrawStreamerID[playerid][data[E_TD_INTERNAL_ID]] = id;

    if (data[E_TD_PROPERTIES][E_TD_FONT] != TDDefaultProperties[E_TD_FONT]) {
        PlayerTextDrawFont(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_FONT]);
    }

    if (data[E_TD_PROPERTIES][E_TD_COLOUR] != TDDefaultProperties[E_TD_COLOUR]) {
        PlayerTextDrawColor(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_COLOUR]);
    }

    if (data[E_TD_PROPERTIES][E_TD_ALIGNMENT] != TDDefaultProperties[E_TD_ALIGNMENT]) {
        PlayerTextDrawAlignment(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_ALIGNMENT]);
    }

    if (data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE] != TDDefaultProperties[E_TD_SHADOW_SIZE]) {
        PlayerTextDrawSetShadow(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE]);
    }

    if (data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH] != TDDefaultProperties[E_TD_OUTLINE_WIDTH]) {
        PlayerTextDrawSetOutline(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH]);
    }

    if (data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR] != TDDefaultProperties[E_TD_BACKGROUND_COLOUR]) {
        PlayerTextDrawBackgroundColor(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR]);
    }

    if (data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL] != TDDefaultProperties[E_TD_IS_PROPORTIONAL]) {
        PlayerTextDrawSetProportional(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL]);
    }

    if (data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] != TDDefaultProperties[E_TD_IS_SELECTABLE]) {
        PlayerTextDrawSetSelectable(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X] != TDDefaultProperties[E_TD_TEXT_SIZE_X] ||
        data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y] != TDDefaultProperties[E_TD_TEXT_SIZE_Y]
    ) {
        PlayerTextDrawTextSize(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X], data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X] != TDDefaultProperties[E_TD_LETTER_SIZE_X] ||
        data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y] != TDDefaultProperties[E_TD_LETTER_SIZE_Y]
    ) {
        PlayerTextDrawLetterSize(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X], data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y]);
    }

    if (data[E_TD_PROPERTIES][E_TD_HAS_BOX] != TDDefaultProperties[E_TD_HAS_BOX]) {
        PlayerTextDrawUseBox(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_HAS_BOX]);
    }

    if (data[E_TD_PROPERTIES][E_TD_BOX_COLOUR] != TDDefaultProperties[E_TD_BOX_COLOUR]) {
        PlayerTextDrawBoxColor(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_BOX_COLOUR]);
    }

    if (data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL] != TDDefaultProperties[E_TD_PREVIEW_MODEL]) {
        PlayerTextDrawSetPreviewModel(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1] != TDDefaultProperties[E_TD_PREVIEW_VEHICLE_COLOUR_1] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2] != TDDefaultProperties[E_TD_PREVIEW_VEHICLE_COLOUR_2]
    ) {
        PlayerTextDrawSetPreviewVehCol(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1], data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2]);
    }

    if (
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X] != TDDefaultProperties[E_TD_PREVIEW_ROT_X] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y] != TDDefaultProperties[E_TD_PREVIEW_ROT_Y] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z] != TDDefaultProperties[E_TD_PREVIEW_ROT_Z] || 
        data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM] != TDDefaultProperties[E_TD_PREVIEW_ZOOM]
    ) {
        PlayerTextDrawSetPreviewRot(playerid, data[E_TD_INTERNAL_ID], data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X], data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y], data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z], data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM]);
    }

    return 1;
}


static stock _DestroyTextDraw(playerid, data[E_TD_STREAMER_PLAYER_DATA]) {
    TextDrawStreamerID[playerid][data[E_TD_INTERNAL_ID]] = -1;

    PlayerTextDrawDestroy(playerid, data[E_TD_INTERNAL_ID]);

    data[E_TD_INTERNAL_ID] = PlayerText:INVALID_TEXT_DRAW;
}


forward public _pp@on_init@0TDSP();
public _pp@on_init@0TDSP() {
    pawn_register_callback("OnPlayerDisconnect", "TDSP_OnPlayerDisconnect");
    pawn_register_callback("OnPlayerClickPlayerTextDraw", "TDSP_OnPlayerClickPlayerTD", handler_return | handler_args);
}


forward public _pp@on_exit@0TDSP();
public _pp@on_exit@0TDSP() {
    new Pool:pool, data[E_TD_STREAMER_PLAYER_DATA];

    for (new playerid, highest = GetPlayerPoolSize(); playerid <= highest; playerid++) {
        pool = _GetTextDrawPool(playerid);

        if (pool_valid(pool)) {
            for (new Iter:id = pool_iter(pool); iter_inside(id); iter_move_next(id)) {
                if (!iter_sizeof(id)) {
                    continue;
                }

                iter_get_arr(id, data);

                if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
                    PlayerTextDrawDestroy(playerid, data[E_TD_INTERNAL_ID]);
                }

                str_delete(data[E_TD_STRING]);
            }

            pool_delete(pool);
        }
    }
}


forward public TDSP_OnPlayerDisconnect(playerid, reason);
public TDSP_OnPlayerDisconnect(playerid, reason) {
    new Pool:pool = _GetTextDrawPool(playerid);

    if (pool_valid(pool)) {
        new data[E_TD_STREAMER_PLAYER_DATA];

        for (new Iter:id = pool_iter(pool); iter_inside(id); iter_move_next(id)) {
            if (!iter_sizeof(id)) {
                continue;
            }

            iter_get_arr(id, data);

            if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
                PlayerTextDrawDestroy(playerid, data[E_TD_INTERNAL_ID]);
            }

            str_delete(data[E_TD_STRING]);
        }

        pool_delete(pool);
    }

    return false;
}


forward public TDSP_OnPlayerClickPlayerTD(&ret, playerid, PlayerText:playertextid);
public TDSP_OnPlayerClickPlayerTD(&ret, playerid, PlayerText:playertextid) {
    new id = TextDrawStreamerID[playerid][playertextid];

    if (id == -1) { 
        ret = 0;
        return true;
    }

    new data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data) || !data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] || !data[E_TD_VISIBLE]) {
        ret = 1;
        return true;
    }

    playertextid = PlayerText:id;
    ret = 1;
    return false;
}


stock PlayerText:TDS_CreatePlayerTextDraw(playerid, Float:x, Float:y, const text[]) {
    new Pool:pool = _GetTextDrawPool(playerid);

    if (!pool_valid(pool)) {
        return PlayerText:INVALID_TEXT_DRAW;
    }

    new data[E_TD_STREAMER_PLAYER_DATA];

    data[E_TD_STRING] = str_acquire(str_new(text));
    data[E_TD_INTERNAL_ID] = PlayerText:INVALID_TEXT_DRAW;
    data[E_TD_PROPERTIES] = TDDefaultProperties;
    data[E_TD_VISIBLE] = false;

    data[E_TD_POS_X] = x;
    data[E_TD_POS_Y] = y;
    
    data[E_TD_EXTRA_1] = INVALID_TEXTDRAW_EXTRA_ID;
    data[E_TD_EXTRA_2] = INVALID_TEXTDRAW_EXTRA_ID;

    return PlayerText:pool_add_arr(pool, data);
}

#if defined _ALS_CreatePlayerTextDraw
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw TDS_CreatePlayerTextDraw


stock PlayerText:CreatePlayerTextDrawStr(playerid, Float:x, Float:y, String:text) {
    new Pool:pool = _GetTextDrawPool(playerid);

    if (!pool_valid(pool)) {
        return PlayerText:INVALID_TEXT_DRAW;
    }

    new data[E_TD_STREAMER_PLAYER_DATA];

    data[E_TD_STRING] = str_acquire(str_clone(text));
    data[E_TD_INTERNAL_ID] = PlayerText:INVALID_TEXT_DRAW;
    data[E_TD_PROPERTIES] = TDDefaultProperties;
    data[E_TD_VISIBLE] = false;

    data[E_TD_POS_X] = x;
    data[E_TD_POS_Y] = y;
    
    data[E_TD_EXTRA_1] = INVALID_TEXTDRAW_EXTRA_ID;
    data[E_TD_EXTRA_2] = INVALID_TEXTDRAW_EXTRA_ID;

    return PlayerText:pool_add_arr(pool, data);
}


stock TDS_IsValidPlayerTextDraw(playerid, PlayerText:text) {
    return _IsValidTextDraw(playerid, _:text);
}

#if defined _ALS_IsValidPlayerTextDraw
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_IsValidPlayerTextDraw
#endif
#define IsValidPlayerTextDraw TDS_IsValidPlayerTextDraw


stock TDS_PlayerTextDrawDestroy(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA], Pool:pool;

    if (!_GetTextDrawData(playerid, id, data, pool)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        _DestroyTextDraw(playerid, data);
    }

    str_delete(data[E_TD_STRING]);
    pool_remove(pool, id);
    return 1;
}

#if defined _ALS_PlayerTextDrawDestroy
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy TDS_PlayerTextDrawDestroy


stock TDS_PlayerTextDrawShow(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] == PlayerText:INVALID_TEXT_DRAW) {
        _CreateTextDraw(playerid, id, data);
    }

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        data[E_TD_VISIBLE] = true;

        PlayerTextDrawShow(playerid, data[E_TD_INTERNAL_ID]);
        _SetTextDrawData(playerid, id, data);
    }
    
    return 1;
}

#if defined _ALS_PlayerTextDrawShow
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow TDS_PlayerTextDrawShow


stock TDS_PlayerTextDrawHide(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_VISIBLE] = false;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        _DestroyTextDraw(playerid, data);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawHide
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide TDS_PlayerTextDrawHide


stock TDS_IsPlayerTextDrawVisible(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_VISIBLE];
}

#if defined _ALS_IsPlayerTextDrawVisible
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_IsPlayerTextDrawVisible
#endif
#define IsPlayerTextDrawVisible TDS_IsPlayerTextDrawVisible


stock TDS_PlayerTextDrawSetString(playerid, PlayerText:text, const string[]) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetString(playerid, data[E_TD_INTERNAL_ID], string);
    }

    str_set(data[E_TD_STRING], str_new(string));
    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawSetString
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString TDS_PlayerTextDrawSetString


stock TDS_PlayerTextDrawGetString(playerid, PlayerText:text, string[], len = sizeof(string)) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    str_get(data[E_TD_STRING], string, len);
    return 1;
}

#if defined _ALS_PlayerTextDrawGetString
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetString
#endif
#define PlayerTextDrawGetString TDS_PlayerTextDrawGetString


stock PlayerTextDrawSetStringStr(playerid, PlayerText:text, String:string) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        _TDS_PlayerTextDrawSetString(playerid, data[E_TD_INTERNAL_ID], string);
    }

    str_set(data[E_TD_STRING], string);
    _SetTextDrawData(playerid, id, data);
    return 1;
}


stock String:PlayerTextDrawGetStringStr(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return STRING_NULL;
    }

    return str_clone(data[E_TD_STRING]);
}


stock TDS_PlayerTextDrawSetPos(playerid, PlayerText:text, Float:x, Float:y) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_POS_X] = x;
    data[E_TD_POS_Y] = y;

    #if defined PlayerTextDrawSetPos
        if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawSetPos(playerid, data[E_TD_INTERNAL_ID], x, y);
        }
    #elseif defined PlayerTextDrawSetPosition
        if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawSetPosition(playerid, data[E_TD_INTERNAL_ID], x, y);
        }
    #endif

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawSetPos
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawSetPos
#endif
#define PlayerTextDrawSetPos TDS_PlayerTextDrawSetPos

#if defined PlayerTextDrawSetPosition
    #if defined _ALS_PlayerTextDrawSetPosition
        #error TextDraw streamer must be the first library to hook any textdraw functions!
    #else
        #define _ALS_PlayerTextDrawSetPosition
    #endif
    #define PlayerTextDrawSetPosition TDS_PlayerTextDrawSetPos
#endif


stock TDS_PlayerTextDrawGetPos(playerid, PlayerText:text, &Float:x, &Float:y) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    x = data[E_TD_POS_X];
    y = data[E_TD_POS_Y];

    return 1;
}

#if defined _ALS_PlayerTextDrawGetPos
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetPos
#endif
#define PlayerTextDrawGetPos TDS_PlayerTextDrawGetPos


stock TDS_PlayerTextDrawLetterSize(playerid, PlayerText:text, Float:x, Float:y) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X] = x;
    data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y] = y;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawLetterSize(playerid, data[E_TD_INTERNAL_ID], x, y);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawLetterSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize TDS_PlayerTextDrawLetterSize


stock TDS_PlayerTextDrawGetLetterSize(playerid, PlayerText:text, &Float:x, &Float:y) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    x = data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_X];
    y = data[E_TD_PROPERTIES][E_TD_LETTER_SIZE_Y];

    return 1;
}

#if defined _ALS_PlayerTDGetLetterSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDGetLetterSize
#endif
#define PlayerTextDrawGetLetterSize TDS_PlayerTextDrawGetLetterSize


stock TDS_PlayerTextDrawTextSize(playerid, PlayerText:text, Float:x, Float:y) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X] = x;
    data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y] = y;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawTextSize(playerid, data[E_TD_INTERNAL_ID], x, y);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawTextSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize TDS_PlayerTextDrawTextSize


stock TDS_PlayerTextDrawGetTextSize(playerid, PlayerText:text, &Float:x, &Float:y) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    x = data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_X];
    y = data[E_TD_PROPERTIES][E_TD_TEXT_SIZE_Y];

    return 1;
}

#if defined _ALS_PlayerTextDrawGetTextSize
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetTextSize
#endif
#define PlayerTextDrawGetTextSize TDS_PlayerTextDrawGetTextSize


stock TDS_PlayerTextDrawColor(playerid, PlayerText:text, color) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_COLOUR] = color;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawColor(playerid, data[E_TD_INTERNAL_ID], color);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawColor
#endif
#define PlayerTextDrawColor TDS_PlayerTextDrawColor


stock TDS_PlayerTextDrawGetColor(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_COLOUR];
}

#if defined _ALS_PlayerTextDrawGetColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetColor
#endif
#define PlayerTextDrawGetColor TDS_PlayerTextDrawGetColor


stock TDS_PlayerTextDrawBoxColor(playerid, PlayerText:text, color) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_BOX_COLOUR] = color;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawBoxColor(playerid, data[E_TD_INTERNAL_ID], color);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawBoxColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawBoxColor
#endif
#define PlayerTextDrawBoxColor TDS_PlayerTextDrawBoxColor


stock TDS_PlayerTextDrawGetBoxColor(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_BOX_COLOUR];
}

#if defined _ALS_PlayerTextDrawGetBoxColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetBoxColor
#endif
#define PlayerTextDrawGetBoxColor TDS_PlayerTextDrawGetBoxColor


stock TDS_PlayerTDBackgroundColor(playerid, PlayerText:text, color) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR] = color;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawBackgroundColor(playerid, data[E_TD_INTERNAL_ID], color);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTDBackgroundColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDBackgroundColor
#endif
#define PlayerTextDrawBackgroundColor TDS_PlayerTDBackgroundColor


stock TDS_PlayerTDGetBackgroundColor(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_BACKGROUND_COLOUR];
}

#if defined _ALS_PlayerTDGetBackgroundColor
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDGetBackgroundColor
#endif
#define PlayerTextDrawGetBackgroundColor TDS_PlayerTDGetBackgroundColor


stock TDS_PlayerTextDrawSetShadow(playerid, PlayerText:text, size) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE] = size;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetShadow(playerid, data[E_TD_INTERNAL_ID], size);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawSetShadow
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow TDS_PlayerTextDrawSetShadow


stock TDS_PlayerTextDrawGetShadow(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_SHADOW_SIZE];
}

#if defined _ALS_PlayerTextDrawGetShadow
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetShadow
#endif
#define PlayerTextDrawGetShadow TDS_PlayerTextDrawGetShadow


stock TDS_PlayerTextDrawSetOutline(playerid, PlayerText:text, size) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH] = size;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetOutline(playerid, data[E_TD_INTERNAL_ID], size);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawSetOutline
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline TDS_PlayerTextDrawSetOutline


stock TDS_PlayerTextDrawGetOutline(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_OUTLINE_WIDTH];
}

#if defined _ALS_PlayerTextDrawGetOutline
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetOutline
#endif
#define PlayerTextDrawGetOutline TDS_PlayerTextDrawGetOutline


stock TDS_PlayerTextDrawFont(playerid, PlayerText:text, font) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_FONT] = font;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawFont(playerid, data[E_TD_INTERNAL_ID], font);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawFont
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont TDS_PlayerTextDrawFont


stock TDS_PlayerTextDrawGetFont(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_FONT];
}

#if defined _ALS_PlayerTextDrawGetFont
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetFont
#endif
#define PlayerTextDrawGetFont TDS_PlayerTextDrawGetFont


stock TDS_PlayerTextDrawUseBox(playerid, PlayerText:text, use) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_HAS_BOX] = !!use;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawUseBox(playerid, data[E_TD_INTERNAL_ID], use);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawUseBox
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox TDS_PlayerTextDrawUseBox


stock TDS_PlayerTextDrawIsBox(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_HAS_BOX];
}

#if defined _ALS_PlayerTextDrawIsBox
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawIsBox
#endif
#define PlayerTextDrawIsBox TDS_PlayerTextDrawIsBox


stock TDS_PlayerTDSetProportional(playerid, PlayerText:text, set) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL] = !!set;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetProportional(playerid, data[E_TD_INTERNAL_ID], set);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTDSetProportional
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDSetProportional
#endif
#define PlayerTextDrawSetProportional TDS_PlayerTDSetProportional


stock TDS_PlayerTDIsProportional(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_IS_PROPORTIONAL];
}

#if defined _ALS_PlayerTDIsProportional
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDIsProportional
#endif
#define PlayerTextDrawIsProportional TDS_PlayerTDIsProportional


stock TDS_PlayerTextDrawSetSelectable(playerid, PlayerText:text, set) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE] = !!set;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetSelectable(playerid, data[E_TD_INTERNAL_ID], set);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTDSetSelectable
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDSetSelectable
#endif
#define PlayerTextDrawSetSelectable TDS_PlayerTextDrawSetSelectable


stock TDS_PlayerTextDrawIsSelectable(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_IS_SELECTABLE];
}

#if defined _ALS_PlayerTextDrawIsSelectable
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawIsSelectable
#endif
#define PlayerTextDrawIsSelectable TDS_PlayerTextDrawIsSelectable


stock TDS_PlayerTextDrawAlignment(playerid, PlayerText:text, alignment) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_ALIGNMENT] = alignment;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawAlignment(playerid, data[E_TD_INTERNAL_ID], alignment);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTextDrawAlignment
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment TDS_PlayerTextDrawAlignment


stock TDS_PlayerTextDrawGetAlignment(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_ALIGNMENT];
}

#if defined _ALS_PlayerTextDrawGetAlignment
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTextDrawGetAlignment
#endif
#define PlayerTextDrawGetAlignment TDS_PlayerTextDrawGetAlignment


stock TDS_PlayerTDSetPreviewModel(playerid, PlayerText:text, model) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL] = model;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetPreviewModel(playerid, data[E_TD_INTERNAL_ID], model);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTDSetPreviewModel
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDSetPreviewModel
#endif
#define PlayerTextDrawSetPreviewModel TDS_PlayerTDSetPreviewModel


stock TDS_PlayerTDGetPreviewModel(playerid, PlayerText:text) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    return data[E_TD_PROPERTIES][E_TD_PREVIEW_MODEL];
}

#if defined _ALS_PlayerTDGetPreviewModel
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDGetPreviewModel
#endif
#define PlayerTextDrawGetPreviewModel TDS_PlayerTDGetPreviewModel


stock TDS_PlayerTextDrawSetPreviewRot(playerid, PlayerText:text, Float:x, Float:y, Float:z, Float:zoom = 1.0) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X] = x;
    data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y] = y;
    data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z] = z;

    data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM] = zoom;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetPreviewRot(playerid, data[E_TD_INTERNAL_ID], x, y, z, zoom);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTDSetPreviewRot
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDSetPreviewRot
#endif
#define PlayerTextDrawSetPreviewRot TDS_PlayerTextDrawSetPreviewRot


stock TDS_PlayerTextDrawGetPreviewRot(playerid, PlayerText:text, &Float:x, &Float:y, &Float:z, &Float:zoom) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    x = data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_X];
    y = data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Y];
    z = data[E_TD_PROPERTIES][E_TD_PREVIEW_ROT_Z];

    zoom = data[E_TD_PROPERTIES][E_TD_PREVIEW_ZOOM];

    return 1;
}

#if defined _ALS_PlayerTDGetPreviewRot
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDGetPreviewRot
#endif
#define PlayerTextDrawGetPreviewRot TDS_PlayerTextDrawGetPreviewRot


stock TDS_PlayerTDSetPreviewVehCol(playerid, PlayerText:text, color1, color2) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1] = color1;
    data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2] = color2;

    if (data[E_TD_INTERNAL_ID] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawSetPreviewVehCol(playerid, data[E_TD_INTERNAL_ID], color1, color2);
    }

    _SetTextDrawData(playerid, id, data);
    return 1;
}

#if defined _ALS_PlayerTDSetPreviewVehCol
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDSetPreviewVehCol
#endif
#define PlayerTextDrawSetPreviewVehCol TDS_PlayerTDSetPreviewVehCol


stock TDS_PlayerTDGetPreviewVehCol(playerid, PlayerText:text, &color1, &color2) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    color1 = data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_1];
    color2 = data[E_TD_PROPERTIES][E_TD_PREVIEW_VEHICLE_COLOUR_2];

    return 1;
}

#if defined _ALS_PlayerTDGetPreviewVehCol
    #error TextDraw streamer must be the first library to hook any textdraw functions!
#else
    #define _ALS_PlayerTDGetPreviewVehCol
#endif
#define PlayerTextDrawGetPreviewVehCol TDS_PlayerTDGetPreviewVehCol


stock PlayerTextDrawSetExtraID(playerid, PlayerText:text, extra1, extra2 = INVALID_TEXTDRAW_EXTRA_ID) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    data[E_TD_EXTRA_1] = extra1;
    data[E_TD_EXTRA_2] = extra2;

    _SetTextDrawData(playerid, id, data);
    return 1;
}


stock PlayerTextDrawGetExtraID(playerid, PlayerText:text, &extra1, &extra2 = INVALID_TEXTDRAW_EXTRA_ID) {
    new id = _:text, data[E_TD_STREAMER_PLAYER_DATA];

    if (!_GetTextDrawData(playerid, id, data)) {
        return 0;
    }

    extra1 = data[E_TD_EXTRA_1];
    extra2 = data[E_TD_EXTRA_2];

    return 1;
}
