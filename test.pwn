#include "td-streamer.inc"

#define FIX_const 1
#define MSELECT_MAX_ITEMS 400
#include <mselect>

#define RUN_TESTS
#include <YSI_Core/y_testing>


Test:Global() {
    ASSERT(IsValidTextDraw(Text:0) == 0);

    new Text:id = TextDrawCreate(10.0, 10.0, "test");
    ASSERT(id == Text:0);
    ASSERT(IsValidTextDraw(id) == 1);

    ASSERT(TextDrawShowForAll(id) == 1);
    ASSERT(TextDrawHideForAll(id) == 1);

    ASSERT(TextDrawShowForPlayer(INVALID_PLAYER_ID, id) == 0);
    ASSERT(IsTextDrawVisibleForPlayer(INVALID_PLAYER_ID, id) == 0);
    ASSERT(TextDrawHideForPlayer(INVALID_PLAYER_ID, id) == 0);

    new string[16];
    TextDrawGetString(id, string);
    ASSERT(!strcmp(string, "test"));
    TextDrawSetString(id, "asd");
    TextDrawGetString(id, string);
    ASSERT(!strcmp(string, "asd"));

    new Float:x, Float:y, Float:z, Float:zoom;

    TextDrawGetPos(id, x, y);
    ASSERT(x == 10.0);
    ASSERT(y == 10.0);

    TextDrawSetPos(id, 100.0, 100.0);
    TextDrawGetPos(id, x, y);
    ASSERT(x == 100.0);
    ASSERT(y == 100.0);

    TextDrawLetterSize(id, 1.0, 4.0);
    TextDrawGetLetterSize(id, x, y);
    ASSERT(x == 1.0);
    ASSERT(y == 4.0);

    TextDrawTextSize(id, 100.0, 100.0);
    TextDrawGetTextSize(id, x, y);
    ASSERT(x == 100.0);
    ASSERT(y == 100.0);

    TextDrawColor(id, 0x00FF00FF);
    ASSERT(TextDrawGetColor(id) == 0x00FF00FF);

    TextDrawBoxColor(id, 0x00FF00FF);
    ASSERT(TextDrawGetBoxColor(id) == 0x00FF00FF);

    TextDrawBackgroundColor(id, 0x00FF00FF);
    ASSERT(TextDrawGetBackgroundColor(id) == 0x00FF00FF);

    TextDrawSetShadow(id, 3);
    ASSERT(TextDrawGetShadow(id) == 3);

    TextDrawSetOutline(id, 3);
    ASSERT(TextDrawGetOutline(id) == 3);

    TextDrawFont(id, 3);
    ASSERT(TextDrawGetFont(id) == 3);

    TextDrawAlignment(id, 3);
    ASSERT(TextDrawGetAlignment(id) == 3);

    TextDrawUseBox(id, 1);
    ASSERT(TextDrawIsBox(id) == 1);

    TextDrawSetProportional(id, 0);
    ASSERT(TextDrawIsProportional(id) == 0);

    TextDrawSetSelectable(id, 1);
    ASSERT(TextDrawIsSelectable(id) == 1);

    TextDrawSetPreviewModel(id, 12345);
    ASSERT(TextDrawGetPreviewModel(id) == 12345);

    TextDrawSetPreviewRot(id, 10.0, 20.0, 30.0, 0.5);
    TextDrawGetPreviewRot(id, x, y, z, zoom);
    ASSERT(x == 10.0);
    ASSERT(y == 20.0);
    ASSERT(z == 30.0);
    ASSERT(zoom == 0.5);

    new color1, color2;
    TextDrawSetPreviewVehCol(id, 15, 45);
    TextDrawGetPreviewVehCol(id, color1, color2);
    ASSERT(color1 == 15);
    ASSERT(color2 == 45);

    ASSERT(TextDrawDestroy(id) == 1);
    ASSERT(IsValidTextDraw(id) == 0);

    id = TextDrawCreate_s(10.0, 10.0, str_new("test"));
    ASSERT(_:id == 1);
    ASSERT(IsValidTextDraw(id) == 1);

    ASSERT(str_eq(TextDrawGetString_s(id), str_new("test")));
    TextDrawSetString_s(id, str_new("asd"));
    ASSERT(str_eq(TextDrawGetString_s(id), str_new("asd")));
    
    TextDrawSetExtraID(id, 23, 67);
    new extra1, extra2;
    TextDrawGetExtraID(id, extra1, extra2);
    ASSERT((extra1 == 23 && extra2 == 67));
}


Test:Player() {
    new playerid = 0;
    new PlayerText:id = CreatePlayerTextDraw(playerid, 10.0, 10.0, "test");

    IsValidPlayerTextDraw(playerid, id);
    PlayerTextDrawShow(playerid, id);
    IsPlayerTextDrawVisible(playerid, id);
    PlayerTextDrawHide(playerid, id);

    new string[16];
    PlayerTextDrawGetString(playerid, id, string);
    PlayerTextDrawSetString(playerid, id, "asd");

    new Float:x, Float:y, Float:z, Float:zoom;

    PlayerTextDrawGetPos(playerid, id, x, y);
    PlayerTextDrawSetPos(playerid, id, 100.0, 100.0);

    PlayerTextDrawLetterSize(playerid, id, 1.0, 4.0);
    PlayerTextDrawGetLetterSize(playerid, id, x, y);

    PlayerTextDrawTextSize(playerid, id, 100.0, 100.0);
    PlayerTextDrawGetTextSize(playerid, id, x, y);

    PlayerTextDrawColor(playerid, id, 0x00FF00FF);
    PlayerTextDrawGetColor(playerid, id);

    PlayerTextDrawBoxColor(playerid, id, 0x00FF00FF);
    PlayerTextDrawGetBoxColor(playerid, id);

    PlayerTextDrawBackgroundColor(playerid, id, 0x00FF00FF);
    PlayerTextDrawGetBackgroundColor(playerid, id);

    PlayerTextDrawSetShadow(playerid, id, 3);
    PlayerTextDrawGetShadow(playerid, id);

    PlayerTextDrawSetOutline(playerid, id, 3);
    PlayerTextDrawGetOutline(playerid, id);

    PlayerTextDrawFont(playerid, id, 3);
    PlayerTextDrawGetFont(playerid, id);

    PlayerTextDrawAlignment(playerid, id, 3);
    PlayerTextDrawGetAlignment(playerid, id);

    PlayerTextDrawUseBox(playerid, id, 1);
    PlayerTextDrawIsBox(playerid, id);

    PlayerTextDrawSetProportional(playerid, id, 0);
    PlayerTextDrawIsProportional(playerid, id);

    PlayerTextDrawSetSelectable(playerid, id, 1);
    PlayerTextDrawIsSelectable(playerid, id);

    PlayerTextDrawSetPreviewModel(playerid, id, 12345);
    PlayerTextDrawGetPreviewModel(playerid, id);

    PlayerTextDrawSetPreviewRot(playerid, id, 10.0, 20.0, 30.0, 0.5);
    PlayerTextDrawGetPreviewRot(playerid, id, x, y, z, zoom);

    new color1, color2;
    PlayerTextDrawSetPreviewVehCol(playerid, id, 15, 45);
    PlayerTextDrawGetPreviewVehCol(playerid, id, color1, color2);

    PlayerTextDrawDestroy(playerid, id);

    id = CreatePlayerTextDraw_s(playerid, 10.0, 10.0, str_new("test"));
    PlayerTextDrawGetString_s(playerid, id);
    PlayerTextDrawSetString_s(playerid, id, str_new("asd"));
    
    PlayerTextDrawSetExtraID(playerid, id, 55, 32);
    new extra1, extra2;
    PlayerTextDrawGetExtraID(playerid, id, extra1, extra2);
    ASSERT((extra1 == 55 && extra2 == 32));
}


MSelectCreate:example_ms(playerid)
{
	static
		items_array[311] = {MSELECT_INVALID_MODEL_ID, ...},
		items_count = 0;

	if (items_count == 0) {
		for (new i = 0; i <= sizeof(items_array); i++) {
			if (i == 74) {
				continue;
			}

			items_array[items_count] = i;
			items_count++;
		}
	}

	return MSelect_Open(playerid, MSelect:example_ms, items_array, items_count, .header = "Header");
}


MSelectResponse:example_ms(playerid, MSelectType:response, itemid, modelid)
{
	new string[144];
	format(string, sizeof(string), "ID: %d | Type: %d | Item: %d | Model: %d",
	       playerid, _:response, itemid, modelid);
	SendClientMessage(playerid, -1, string);
	return 1;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & KEY_SPRINT) {
        MSelect_Show(playerid, MSelect:example_ms);
    }

    return 1;
}
