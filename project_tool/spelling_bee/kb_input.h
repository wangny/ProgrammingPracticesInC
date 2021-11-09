#include <windows.h>
#ifndef KB_INPUT_
#define KB_INPUT_
extern void	initializeKeyInput(void);
extern int waitForKeyDown(float sec);
extern int getKeyEventASCII(void);
#endif
