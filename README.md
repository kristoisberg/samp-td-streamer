# TextDraw Streamer* - No more textdraw limits!

[![sampctl](https://shields.southcla.ws/badge/sampctl-samp--td--streamer-2f2f2f.svg?style=for-the-badge)](https://github.com/kristoisberg/samp-td-streamer)

This library removes the limits on how many textdraws can be created at the same time (2048 global and 256 per-player textdraws as of 0.3.7 and 0.3.DL). The library works by only creating the textdraws when they are visible for anyone. This is a rewrite of the `PlayerTextDrawStreamer` include, originally created by theYiin and later maintained by me. Some benefits over the old include:

* Support for global textdraws.
* No limits at all - the old include used static arrays meaning that the limits were still there, they were just higher. This library uses PawnPlus for dynamic containers and dynamically allocated strings, meaning that there is no limit on how many textdraws can be created.
* Smaller footprint on the binary size - Again, static arrays are replaced with dynamic memory, the old include increased the binary size by several megabytes and also increased the compilation time drastically, compared to this the footprint of this library is almost non-existent. 

**\*** - Technically, this library does not do any streaming. However, in the SA-MP community, the name "streamer" is often associated with something that removes hardcoded limits from something, therefore this name is used to help people find the library.

## Installation

Simply install to your project:

```bash
sampctl package install kristoisberg/samp-td-streamer
```

To use the streamer for global textdraws, include the following file:

```pawn
#include <td-streamer-global>
```

To use the streamer for per-player textdraws, include the following file:

```pawn
#include <td-streamer-player>
```

If you wish to use it for both, you can either include both of the previous files or simply include:

```pawn
#include <td-streamer>
```

**Notes:** This library must be the first one to hook any textdraw-related functions, otherwise a compile time error will be thrown. Neither should any textdraw-related functions or callbacks be used before the inclusion of this library. If YSF or SKY are used, they must be included before this library.


## Usage

The include is completely plug & play, after being installed properly it should automatically do its job.


## Functions

The following functions are either modified or added by this library:

### td-streamer-global.inc

```pawn
Text:TextDrawCreate(Float:x, Float:y, const text[]);
Text:TextDrawCreate_s(Float:x, Float:y, String:text);
IsValidTextDraw(Text:text);
TextDrawDestroy(Text:text);
TextDrawShowForPlayer(playerid, Text:text);
TextDrawHideForPlayer(playerid, Text:text);
TextDrawShowForAll(Text:text);
TextDrawHideForAll(Text:text);
IsTextDrawVisibleForPlayer(playerid, Text:text);
TextDrawSetString(Text:text, const string[]);
TextDrawGetString(Text:text, string[], len = sizeof(string));
TextDrawSetString_s(Text:text, String:string);
String:TextDrawGetString_s(Text:text);
TextDrawSetPos(Text:text, Float:x, Float:y); // TextDrawSetPosition also works if SKY is included
TextDrawGetPos(Text:text, &Float:x, &Float:y);
TextDrawLetterSize(Text:text, Float:x, Float:y);
TextDrawGetLetterSize(Text:text, &Float:x, &Float:y);
TextDrawTextSize(Text:text, Float:x, Float:y);
TextDrawGetTextSize(Text:text, &Float:x, &Float:y);
TextDrawColor(Text:text, color);
TextDrawGetColor(Text:text);
TextDrawBoxColor(Text:text, color);
TextDrawGetBoxColor(Text:text);
TextDrawBackgroundColor(Text:text, color);
TextDrawGetBackgroundColor(Text:text);
TextDrawSetShadow(Text:text, size);
TextDrawGetShadow(Text:text);
TextDrawSetOutline(Text:text, size);
TextDrawGetOutline(Text:text);
TextDrawFont(Text:text, font);
TextDrawGetFont(Text:text);
TextDrawUseBox(Text:text, use);
TextDrawIsBox(Text:text);
TextDrawSetProportional(Text:text, set);
TextDrawIsProportional(Text:text);
TextDrawSetSelectable(Text:text, set);
TextDrawIsSelectable(Text:text);
TextDrawAlignment(Text:text, alignment);
TextDrawGetAlignment(Text:text);
TextDrawSetPreviewModel(Text:text, model);
TextDrawGetPreviewModel(Text:text);
TextDrawSetPreviewRot(Text:text, Float:x, Float:y, Float:z, Float:zoom = 1.0);
TextDrawGetPreviewRot(Text:text, &Float:x, &Float:y, &Float:z, &Float:zoom);
TextDrawSetPreviewVehCol(Text:text, color1, color2);
TextDrawGetPreviewVehCol(Text:text, &color1, &color2);
TextDrawSetExtraID(Text:text, extra1, extra2 = INVALID_TEXTDRAW_EXTRA_ID);
TextDrawGetExtraID(Text:text, &extra1, &extra2 = INVALID_TEXTDRAW_EXTRA_ID);
```


### td-streamer-player.inc

```pawn
PlayerText:CreatePlayerTextDraw(playerid, Float:x, Float:y, const text[]);
PlayerText:CreatePlayerTextDraw_s(playerid, Float:x, Float:y, String:text);
PlayerTextDrawDestroy(playerid, PlayerText:text);
PlayerTextDrawShow(playerid, PlayerText:text);
PlayerTextDrawHide(playerid, PlayerText:text);
IsPlayerTextDrawVisible(playerid, PlayerText:text);
PlayerTextDrawSetString(playerid, PlayerText:text, const string[]);
PlayerTextDrawGetString(playerid, PlayerText:text, string[], len = sizeof(string));
PlayerTextDrawSetString_s(playerid, PlayerText:text, String:string);
String:PlayerTextDrawGetString_s(playerid, PlayerText:text);
PlayerTextDrawSetPos(playerid, PlayerText:text, Float:x, Float:y); // PlayerTextDrawSetPosition also works if SKY is included
PlayerTextDrawGetPos(playerid, PlayerText:text, &Float:x, &Float:y);
PlayerTextDrawLetterSize(playerid, PlayerText:text, Float:x, Float:y);
PlayerTextDrawGetLetterSize(playerid, PlayerText:text, &Float:x, &Float:y);
PlayerTextDrawTextSize(playerid, PlayerText:text, Float:x, Float:y);
PlayerTextDrawGetTextSize(playerid, PlayerText:text, &Float:x, &Float:y);
PlayerTextDrawColor(playerid, PlayerText:text, color);
PlayerTextDrawGetColor(playerid, PlayerText:text);
PlayerTextDrawBoxColor(playerid, PlayerText:text, color);
PlayerTextDrawGetBoxColor(playerid, PlayerText:text);
PlayerTextDrawBackgroundColor(playerid, PlayerText:text, color);
PlayerTextDrawGetBackgroundColor(playerid, PlayerText:text);
PlayerTextDrawSetShadow(playerid, PlayerText:text, size);
PlayerTextDrawGetShadow(playerid, PlayerText:text);
PlayerTextDrawSetOutline(playerid, PlayerText:text, size);
PlayerTextDrawGetOutline(playerid, PlayerText:text);
PlayerTextDrawFont(playerid, PlayerText:text, font);
PlayerTextDrawGetFont(playerid, PlayerText:text);
PlayerTextDrawUseBox(playerid, PlayerText:text, use);
PlayerTextDrawIsBox(playerid, PlayerText:text);
PlayerTextDrawSetProportional(playerid, PlayerText:text, set);
PlayerTextDrawIsProportional(playerid, PlayerText:text);
PlayerTextDrawSetSelectable(playerid, PlayerText:text, set);
PlayerTextDrawIsSelectable(playerid, PlayerText:text);
PlayerTextDrawAlignment(playerid, PlayerText:text, alignment);
PlayerTextDrawGetAlignment(playerid, PlayerText:text);
PlayerTextDrawSetPreviewModel(playerid, PlayerText:text, model);
PlayerTextDrawGetPreviewModel(playerid, PlayerText:text);
PlayerTextDrawSetPreviewRot(playerid, PlayerText:text, Float:x, Float:y, Float:z, Float:zoom = 1.0);
PlayerTextDrawGetPreviewRot(playerid, PlayerText:text, &Float:x, &Float:y, &Float:z, &Float:zoom);
PlayerTextDrawSetPreviewVehCol(playerid, PlayerText:text, color1, color2);
PlayerTextDrawGetPreviewVehCol(playerid, PlayerText:text, &color1, &color2);
PlayerTextDrawSetExtraID(playerid, PlayerText:text, extra1, extra2 = INVALID_TEXTDRAW_EXTRA_ID);
PlayerTextDrawGetExtraID(playerid, PlayerText:text, &extra1, &extra2 = INVALID_TEXTDRAW_EXTRA_ID);
```


## Testing

The `test.pwn` file contains automated tests and a test script using MSelect by Open-GTO. To test, simply run the package:

```bash
sampctl package run
```
