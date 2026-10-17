/*
 * SOBA ULTIMATO GUERREIROS EVOLUTION
 * Playable text-mode combat prototype for PSP / PPSSPP.
 * Next milestone: replace text arena with original 2D/3D assets.
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("Soba Ultimato", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define STATE_MENU 0
#define STATE_FIGHT 1
#define STATE_RESULT 2
#define MAX_POS 18

static const char *fighters[] = { "KAPANJI", "BARAKA", "JABARI" };
static const char *powers[] = { "4 ELEMENTOS", "TROVAO", "FOGO" };

static int state = STATE_MENU;
static int selected = 0;
static int playerHp = 100;
static int enemyHp = 100;
static int playerPos = 3;
static int enemyPos = 14;
static int special = 100;
static int frame = 0;
static int messageFrames = 0;
static char message[80] = "Escolhe o teu guerreiro e prime X.";
static unsigned int previousButtons = 0;

static int pressed(unsigned int buttons, unsigned int key)
{
    return (buttons & key) && !(previousButtons & key);
}

static void setMessage(const char *text)
{
    snprintf(message, sizeof(message), "%s", text);
    messageFrames = 70;
}

static void resetFight(void)
{
    playerHp = 100;
    enemyHp = 100;
    playerPos = 3;
    enemyPos = 14;
    special = 100;
    frame = 0;
    state = STATE_FIGHT;
    setMessage("LUTA! Aproxima-te e ataca.");
}

static void drawBar(const char *label, int value)
{
    int i;
    pspDebugScreenPrintf("%s [", label);
    for (i = 0; i < 20; i++)
        pspDebugScreenPrintf("%s", i < value / 5 ? "#" : "-");
    pspDebugScreenPrintf("] %d\n", value);
}

static void drawMenu(void)
{
    int i;
    pspDebugScreenPrintf("========================================\n");
    pspDebugScreenPrintf("   SOBA ULTIMATO GUERREIROS EVOLUTION\n");
    pspDebugScreenPrintf("========================================\n\n");
    pspDebugScreenPrintf("PROTOTIPO JOGAVEL - SELECAO DE GUERREIRO\n\n");
    for (i = 0; i < 3; i++) {
        pspDebugScreenPrintf("%s %s - %s\n",
            i == selected ? ">>" : "  ", fighters[i], powers[i]);
    }
    pspDebugScreenPrintf("\nCONTROLos\n");
    pspDebugScreenPrintf("D-PAD CIMA/BAIXO : escolher guerreiro\n");
    pspDebugScreenPrintf("X                : iniciar combate\n");
    pspDebugScreenPrintf("START            : sair\n\n");
    pspDebugScreenPrintf("Conceito: guerreiros originais inspirados em fantasia africana.\n");
}

static void drawFight(void)
{
    int i;
    pspDebugScreenPrintf("SOBA ULTIMATO - ARENA DE TREINO\n");
    pspDebugScreenPrintf("--------------------------------\n");
    pspDebugScreenPrintf("JOGADOR: %s | PODER: %s\n", fighters[selected], powers[selected]);
    drawBar("TU ", playerHp);
    drawBar("CPU", enemyHp);
    pspDebugScreenPrintf("Energia especial: %d%%\n\n", special);
    pspDebugScreenPrintf("|");
    for (i = 0; i < MAX_POS; i++) {
        if (i == playerPos && i == enemyPos)
            pspDebugScreenPrintf("X");
        else if (i == playerPos)
            pspDebugScreenPrintf("P");
        else if (i == enemyPos)
            pspDebugScreenPrintf("E");
        else
            pspDebugScreenPrintf(".");
    }
    pspDebugScreenPrintf("|\nP=tu  E=adversario\n\n");
    pspDebugScreenPrintf("D-PAD ESQ/DIR: mover\n");
    pspDebugScreenPrintf("X: ataque (perto) | O: poder especial\n");
    pspDebugScreenPrintf("TRIANGULO: afastar | START: menu\n\n");
    if (messageFrames > 0)
        pspDebugScreenPrintf("%s\n", message);
}

static void drawResult(void)
{
    pspDebugScreenPrintf("\n\n===== FIM DO COMBATE =====\n\n");
    if (playerHp > 0)
        pspDebugScreenPrintf("VITORIA! %s venceu o desafio!\n", fighters[selected]);
    else
        pspDebugScreenPrintf("DERROTA! Treina e tenta novamente.\n");
    pspDebugScreenPrintf("\nX: voltar a lutar\nO: escolher guerreiro\nSTART: sair\n");
}

int main(void)
{
    SceCtrlData pad;
    int running = 1;

    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    while (running) {
        unsigned int buttons;
        sceCtrlReadBufferPositive(&pad, 1);
        buttons = pad.Buttons;

        if (pressed(buttons, PSP_CTRL_START)) {
            if (state == STATE_FIGHT || state == STATE_RESULT)
                state = STATE_MENU;
            else
                running = 0;
        }

        if (state == STATE_MENU) {
            if (pressed(buttons, PSP_CTRL_UP))
                selected = (selected + 2) % 3;
            if (pressed(buttons, PSP_CTRL_DOWN))
                selected = (selected + 1) % 3;
            if (pressed(buttons, PSP_CTRL_CROSS))
                resetFight();
        } else if (state == STATE_FIGHT) {
            frame++;
            if (pressed(buttons, PSP_CTRL_LEFT) && playerPos > 0)
                playerPos--;
            if (pressed(buttons, PSP_CTRL_RIGHT) && playerPos < MAX_POS - 1)
                playerPos++;
            if (pressed(buttons, PSP_CTRL_TRIANGLE)) {
                if (playerPos < enemyPos && playerPos > 0) playerPos--;
                else if (playerPos > enemyPos && playerPos < MAX_POS - 1) playerPos++;
                setMessage("Recuo!");
            }
            if (pressed(buttons, PSP_CTRL_CROSS)) {
                int distance = playerPos > enemyPos ? playerPos - enemyPos : enemyPos - playerPos;
                if (distance <= 2) {
                    enemyHp -= 12;
                    if (enemyHp < 0) enemyHp = 0;
                    special += 12;
                    if (special > 100) special = 100;
                    setMessage("Ataque acertou!");
                } else {
                    setMessage("Estás longe! Aproxima-te.");
                }
            }
            if (pressed(buttons, PSP_CTRL_CIRCLE)) {
                int distance = playerPos > enemyPos ? playerPos - enemyPos : enemyPos - playerPos;
                if (special >= 40 && distance <= 5) {
                    enemyHp -= 28;
                    if (enemyHp < 0) enemyHp = 0;
                    special -= 40;
                    setMessage("PODER ESPECIAL! Grande impacto!");
                } else if (special < 40) {
                    setMessage("Energia insuficiente. Ataca para carregar.");
                } else {
                    setMessage("O adversario esta demasiado longe.");
                }
            }

            if (enemyHp > 0 && frame % 18 == 0) {
                if (enemyPos > playerPos + 1) enemyPos--;
                else if (enemyPos < playerPos - 1) enemyPos++;
                else {
                    playerHp -= 7;
                    if (playerHp < 0) playerHp = 0;
                    setMessage("O adversario atacou!");
                }
            }
            if (enemyHp <= 0 || playerHp <= 0)
                state = STATE_RESULT;
            if (messageFrames > 0) messageFrames--;
        } else if (state == STATE_RESULT) {
            if (pressed(buttons, PSP_CTRL_CROSS))
                resetFight();
            if (pressed(buttons, PSP_CTRL_CIRCLE))
                state = STATE_MENU;
        }

        pspDebugScreenClear();
        if (state == STATE_MENU) drawMenu();
        else if (state == STATE_FIGHT) drawFight();
        else drawResult();

        previousButtons = buttons;
        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
