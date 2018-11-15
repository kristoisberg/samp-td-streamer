#include "td-streamer.inc"

#define RUN_TESTS
#include <YSI-Core/y_testing>


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
}