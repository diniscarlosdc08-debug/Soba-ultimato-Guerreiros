/*
 * Soba Ultimato Guerreiros
 * Initial PSP homebrew prototype.
 *
 * This is a technical starting point, not the finished fighting game.
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdio.h>

PSP_MODULE_INFO("Soba Ultimato", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(void)
{
    SceCtrlData pad;
    int running = 1;

    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    while (running) {
        sceCtrlReadBufferPositive(&pad, 1);

        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf("SOBA ULTIMATO GUERREIROS\n");
        pspDebugScreenPrintf("------------------------\n\n");
        pspDebugScreenPrintf("Prototipo tecnico PSP\n");
        pspDebugScreenPrintf("Compatibilidade: PPSSPP / PSP\n\n");
        pspDebugScreenPrintf("Controlos de teste:\n");
        pspDebugScreenPrintf("X      - confirmar / testar entrada\n");
        pspDebugScreenPrintf("START  - sair\n\n");
        pspDebugScreenPrintf("Estado: programa iniciado.\n");
        pspDebugScreenPrintf("Proxima etapa: menu e sistema de luta.\n");

        if (pad.Buttons & PSP_CTRL_START) {
            running = 0;
        }

        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
