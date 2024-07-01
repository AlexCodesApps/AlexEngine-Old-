# EXECUTIVE DECISION - TILES WILL BE 'Solid' BY DEFAULT
# DEFINE_FLAG Solid
# ANOTHER EXECUTIVE DECISION - 0 IS RESERVED FOR AIR
# DEFINE_FLAG Ghost
DEFINE_FLAG Dangerous

[TEX testspritesheet 16 0 "testspritesheet"]
[
# [0 = 0, 2] # AIR
[1 = 1, 0] # GRASS
[2 = 0, 0] # LEFT_GRASS
[3 = 2, 0] # RIGHT_GRASS
[4 = 1, 1] # DIRT
[5 = 0, 1] # LEFT_BOTTOM_DIRT
[6 = 2, 1] # RIGHT_BOTTOM_DIRT
]

# FLAG testspritesheet 0 Ghost

[world1 testspritesheet 4 5]
0 0 0 0 0
0 0 0 0 1
0 1 1 1 4
1 4 4 4 4
