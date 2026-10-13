/* The message dialog object file (retail 0x099718 to 0x099948): opens the system message
   dialog for an error code or for one of the game's messages (in the current language),
   and steps it until it has closed. */

#include <string.h>

extern "C" {
typedef struct SceUtilityMsgDialogParams {
    unsigned int size;
    int language;
    int buttonSwap;
    int graphicsThread;
    int accessThread;
    int fontThread;
    int soundThread;
    int result;
    int reserved[4];
    int unknown;
    int mode;
    unsigned int errorValue;
    char message[512];
} SceUtilityMsgDialogParams;

int sceUtilityMsgDialogInitStart(SceUtilityMsgDialogParams *params);
int sceUtilityMsgDialogGetStatus(void);
int sceUtilityMsgDialogUpdate(int n);
int sceUtilityMsgDialogShutdownStart(void);
int f_01c260(void);
void f_021b9c(void);
}

/* The game's dialog messages, seven languages per message. */
extern const char *D_1d49f4[][7];

/* @implements 0x099718 us f_099718
   WHAT IT DOES: Opens the message dialog for a system error code. */
void f_099718(SceUtilityMsgDialogParams *p, int error)
{
    memset(p, 0, sizeof *p);
    p->size = sizeof *p;
    int lang = f_01c260();
    if (lang == 6)
        lang = 1;
    p->language = lang;
    p->buttonSwap = 1;
    p->graphicsThread = 17;
    p->accessThread = 19;
    p->fontThread = 18;
    p->soundThread = 16;
    p->mode = 0;
    p->errorValue = error;
    sceUtilityMsgDialogInitStart(p);
}

/* @implements 0x0997ac us f_0997ac
   WHAT IT DOES: Opens the message dialog with one of the game's messages in the current
   language. */
void f_0997ac(SceUtilityMsgDialogParams *p, int msg)
{
    memset(p, 0, sizeof *p);
    p->size = sizeof *p;
    int lang = f_01c260();
    if (lang == 6)
        lang = 1;
    p->language = lang;
    p->buttonSwap = 1;
    p->graphicsThread = 17;
    p->accessThread = 19;
    p->fontThread = 18;
    p->soundThread = 16;
    p->mode = 1;
    memcpy(p->message, D_1d49f4[msg][f_01c260()], sizeof p->message);
    sceUtilityMsgDialogInitStart(p);
}

/* @implements 0x0998d0 us f_0998d0
   WHAT IT DOES: Steps the open dialog: updates it while visible, starts its shutdown when
   the player has answered; returns 1 once it has closed, else the step's result. */
int f_0998d0(SceUtilityMsgDialogParams *p)
{
    int r = 0;
    f_021b9c();
    switch (sceUtilityMsgDialogGetStatus()) {
    case 2:
        r = sceUtilityMsgDialogUpdate(1);
        break;
    case 1:
    case 4:
        break;
    case 0:
        r = 1;
        break;
    case 3:
        r = sceUtilityMsgDialogShutdownStart();
        break;
    }
    return r;
}
