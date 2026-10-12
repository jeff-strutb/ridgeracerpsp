# Race RAM notes (US, oracle conditions)

These are working notes for the steering driver. Every address was measured in rrbox on `race_seaside_start` (Seaside Route 765, Class 1, an empty memory stick). Each is a hypothesis with the evidence beside it. None of these is a name, and none should become one until code proves it.

| Address | What it looks like | Evidence |
|---|---|---|
| 0x08a43b84, 0x08a43b88 | The player car's x and z (floats) | They move about 835 units per two frames while racing (~25 m/s if the unit is mm, which fits the speedometer). Almost static while stuck on the tunnel wall. Copied at 0x08a43fb4. |
| 0x08a4d76c | A per-section progress counter (int) | It rises by 34 per two frames while racing, freezes when stuck, and reset to 0 at frame 6070 (a section boundary?). |
| 0x08a5165c to 0x08a51668, 0x08a51dcc to 0x08a51dd8 | Groups of four ints that rise together | These were NOT per-wheel course positions: a steering test showed no left/right split, and they look like a timing history. |
| 0x09c07734, 0x09c09ed4, 0x09fbcd70 | Moving float pairs that keep moving while the player is stuck | Possibly AI cars in another coordinate frame or record layout. Unconfirmed. |

The simulation updates every other 60 Hz frame. Compare dumps 2 frames apart, not 1.

## Driver plan (not built)

Steer from the player's own state:

1. Find the car's heading and the course direction (for example from the code that reads 0x08a4d76c).
2. Steer to hold the angle between them near zero, using rrbox's `--rr-peek` and analog input.
3. Record the inputs as an ordinary script.

Alternatively, record an AI car's path as waypoints once the AI records are identified.
