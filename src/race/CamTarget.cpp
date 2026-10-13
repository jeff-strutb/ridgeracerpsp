/* The replay camera target (retail 0x0828e4 to 0x082970): an out of line constructor and
   the one global target's static construction. */

/* A camera target: no car (-1) and nothing pending. */
class CCamTarget {
public:
    CCamTarget();
    int m0;
    int car;
    int m8;
};

/* @implements 0x0828e4 us _ZN10CCamTargetC2Ev
   WHAT IT DOES: Base object constructor: no car, clears the other two words. */
/* @implements 0x0828f8 us _ZN10CCamTargetC1Ev
   WHAT IT DOES: Complete object constructor: the same. */
CCamTarget::CCamTarget()
{
    car = -1;
    m0 = 0;
    m8 = 0;
}

CCamTarget D_241754;

/* @implements 0x08290c us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global camera target at start up. */
/* @implements 0x082950 us _GLOBAL__I
   WHAT IT DOES: Runs the above. */
