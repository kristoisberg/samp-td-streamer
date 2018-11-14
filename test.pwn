#include "td-streamer.inc"

#define RUN_TESTS
#include <YSI-Core/y_testing>


Test:Main() {
    ASSERT(IsValidTextDraw(Text:0) == 0);

    new Text:id = TextDrawCreate(10.0, 10.0, "test");
    ASSERT(id == Text:0);
    ASSERT(IsValidTextDraw(id) == 1);
    ASSERT(TextDrawShowForPlayer(INVALID_PLAYER_ID, id) == 0);
}