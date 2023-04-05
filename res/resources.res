# first declare a SPRITE
# then name of the sprite
# link it to the proper file
# then set the tile by tile ratio
# choose the compression speed BEST, FAST, NONE 
# Choose the animation speed, remmeber that the sprite changes every x cycles per second 

SPRITE small_guy "player-g.png" 2 2 FAST 0

TILESET level_1_tileset "indexed-Level_1-v1.bmp" BEST
MAP level_1_map "indexed-Level_1-v1.bmp" level_1_tileset BEST
PALETTE level_1_palette "indexed-Level_1-v1.bmp"