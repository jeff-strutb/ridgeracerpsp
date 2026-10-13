# Race RAM notes (US, oracle conditions)

These are working notes for the steering driver. Every address was measured in rrbox on `race_seaside_start` (Seaside Route 765, Class 1, an empty memory stick). Each is a hypothesis with the evidence beside it. None of these is a name, and none should become one until code proves it.

| Address | What it looks like | Evidence |
|---|---|---|
| 0x08a4d3b0, 0x08a4d3b4, 0x08a4d3b8 | The player car's x, y and z (floats) | What the search driver scores progress with. A replay of the recorded full-race drive reproduces them exactly on every frame. |
| 0x08a43b80 to 0x08a43b88, 0x08a43b90 to 0x08a43b98 | The camera position (floats), then a unit vector on its view axis | Measured 2026-10-13 on the start straight (frames 5000 to 6400): the position is the car position x1000 (x exactly, z within 0.2%) and about 1000 higher. The unit vector reads (0, -0.02, 1.0) while the car travels toward -z, so it points back along the view axis. The earlier steering tests saw the camera swing wide on turns, which made it a poor progress measure. |
| 0x08a4d76c | A millisecond duration timer (int), condition unknown; NOT progress | It adds 17 every frame while it runs (34 per two frames). On the full Seaside race replay it counts from frame 5549 through the countdown to 20723, drops to 0 at frame 6768, and from then on counts up in short bursts (17 to 5151 ms) and drops to 0 about 70 times by frame 18600, at frames unrelated to the 20-frame input steps. It sits at 0 for long stretches of clean driving. |
| 0x08a5165c to 0x08a51668, 0x08a51dcc to 0x08a51dd8 | Groups of four ints that rise together | These were NOT per-wheel course positions: a steering test showed no left/right split, and they look like a timing history. |
| 0x09c07734, 0x09c09ed4, 0x09fbcd70 | Moving float pairs that keep moving while the player is stuck | Possibly AI cars in another coordinate frame or record layout. Unconfirmed. |

The simulation updates every other 60 Hz frame. Compare dumps 2 frames apart, not 1.

## The search driver (built)

rrbox's `--rr-drive=START:OUT` (tools/oracle/README.md) does not read the car's heading or the course. Every 20 frames it snapshots the machine, plays out five button choices for 80 frames each, and keeps the one that carries the car (0x08a4d3b0, 0x08a4d3b8) furthest along its direction of travel over the last six decisions. It writes the result as an ordinary input script.
