"""
L-Bracket for Potentiometer Mounting
=====================================
Long wall  (horizontal top plate): 105mm long x 30mm wide x 3mm thick
Short wall (vertical end plate):    25mm tall x 30mm wide x 3mm thick
  - Short wall is at the LEFT (X=0) end of the long wall
  - Short wall hangs DOWN from the long wall

Coordinate system:
  X = along the 105mm length (left to right)
  Y = bracket width (30mm, front to back)
  Z = vertical (up)

Long  wall: X=0..105, Y=0..30, Z=0..3      (horizontal, Z=0 is bottom face)
Short wall: X=0..3,   Y=0..30, Z=-25..0    (vertical, hangs down from left end)

Holes on long wall top face (drilled through Z):
  - 9mm pot hole:  X=90, Y=15 (centered in width)
  - 3mm guide pin: X=90, Y=5  (10mm from pot center, toward front edge Y=0)
    Note: guide pin is between the pot hole and the short wall end,
    so it's toward lower X... but spec says 10mm above pot on the short wall.
    Since pot is now on long wall TOP face, "toward top" = toward lower Y (front).
    Placing guide pin at Y=15-10=5.

Holes on short wall face (drilled through X):
  - 2x 4mm mounting holes, centers 5mm from corners:
      Hole 1: Y=5,  Z=-5   (5mm from front edge, 5mm from top)
      Hole 2: Y=5,  Z=-20  (5mm from front edge, 5mm from bottom)
"""

import FreeCAD as App
import Part

doc = App.newDocument("LBracket")

# ── Dimensions ────────────────────────────────────────────────────────────────
THICKNESS           = 3.0
BRACKET_WIDTH       = 30.0   # Y axis

LONG_WALL_LENGTH    = 105.0  # X axis
SHORT_WALL_HEIGHT   = 25.0   # Z axis (hangs downward)

POT_HOLE_DIAMETER   = 9.0
POT_X               = 90.0
POT_Y               = BRACKET_WIDTH / 2.0   # 15.0 — centered in width

GUIDE_HOLE_DIAMETER = 3.0
GUIDE_Y             = POT_Y - 10.0          # 5.0 — 10mm toward front from pot center
GUIDE_MY = POT_Y+10
MOUNT_HOLE_DIAMETER = 4.0

# ── Long wall (horizontal top plate) ─────────────────────────────────────────
# X=0..105, Y=0..30, Z=0..3
long_wall = Part.makeBox(LONG_WALL_LENGTH, BRACKET_WIDTH, THICKNESS,
                         App.Vector(0, 0, 0))

# ── Short wall (vertical end plate, hangs down from left end) ─────────────────
# X=0..3, Y=0..30, Z=-25..0
short_wall = Part.makeBox(THICKNESS, BRACKET_WIDTH, SHORT_WALL_HEIGHT,
                          App.Vector(0, 0, -SHORT_WALL_HEIGHT))

bracket = long_wall.fuse(short_wall)

# ── Pot hole through long wall (Z direction) ──────────────────────────────────
hole_pot = Part.makeCylinder(POT_HOLE_DIAMETER / 2.0, THICKNESS + 2.0,
                              App.Vector(POT_X, POT_Y, -1.0),
                              App.Vector(0, 0, 1))

bracket = bracket.cut(hole_pot)

# ── Guide pin hole through long wall (Z direction, 10mm from pot toward front) ─
hole_guide = Part.makeCylinder(GUIDE_HOLE_DIAMETER / 2.0, THICKNESS + 2.0,
                                App.Vector(POT_X, GUIDE_Y, -1.0),
                                App.Vector(0, 0, 1))

bracket = bracket.cut(hole_guide)
hole_guide2 = Part.makeCylinder(GUIDE_HOLE_DIAMETER / 2.0, THICKNESS + 2.0,
                                App.Vector(POT_X, GUIDE_MY, -1.0),
                                App.Vector(0, 0, 1))

bracket = bracket.cut(hole_guide2)

# ── Mounting holes through short wall (X direction) ───────────────────────────
# Short wall face at X=0, spans Y=0..30, Z=-25..0
# Centers 5mm from corners:
#   Hole 1: Y=5, Z=-5   (5mm from front, 5mm from top)
#   Hole 2: Y=5, Z=-20  (5mm from front, 5mm from bottom)
hole_mount_1 = Part.makeCylinder(MOUNT_HOLE_DIAMETER / 2.0, THICKNESS + 2.0,
                                  App.Vector(-1.0, 5.0, -20.0),
                                  App.Vector(1, 0, 0))

hole_mount_2 = Part.makeCylinder(MOUNT_HOLE_DIAMETER / 2.0, THICKNESS + 2.0,
                                  App.Vector(-1.0, 25.0, -20.0),
                                  App.Vector(1, 0, 0))

bracket = bracket.cut(hole_mount_1)
bracket = bracket.cut(hole_mount_2)

# ── Add to document and save ──────────────────────────────────────────────────
bracket_feature = doc.addObject("Part::Feature", "LBracket")
bracket_feature.Shape = bracket

doc.recompute()

save_path = "/mnt/user-data/outputs/l_bracket.FCStd"
doc.saveAs(save_path)
print(f"Saved to {save_path}")