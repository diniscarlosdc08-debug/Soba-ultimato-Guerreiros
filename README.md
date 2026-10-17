# Soba Ultimato Guerreiros

Projeto de jogo de luta anime caseiro para **PSP / PPSSPP**.

## Estado atual

Foi criada a estrutura técnica inicial para um protótipo homebrew em C usando o **PSPSDK**. Ainda não é o jogo completo e ainda não foi confirmada uma compilação funcional.

## Estrutura

- `src/main.c` — ponto de entrada inicial; mostra um ecrã de teste e permite sair com START.
- `Makefile` — configuração para compilar com PSPSDK.
- `assets/` — local reservado para recursos originais de personagens, cenários, áudio e interface.
- `docs/ARQUITETURA_TECNICA.md` — arquitetura e etapas de desenvolvimento.
- `.github/workflows/build-psp.yml` — fluxo de trabalho que tenta compilar o projeto e guardar os ficheiros gerados como artefacto do GitHub Actions.
- `docs/PLANO_DO_PROJETO.md` — plano geral.

## Como testar

1. Abre o separador **Actions** deste repositório.
2. Seleciona o fluxo **Build PSP homebrew** e verifica o resultado da execução mais recente.
3. Se a compilação terminar com sucesso, abre a execução e descarrega o artefacto `Soba-Ultimato-PSP`.
4. Extrai o artefacto e testa o `EBOOT.PBP` no PPSSPP.

Se a compilação falhar, abre os registos da execução e usa a primeira mensagem de erro para corrigir a configuração.

## Compilação local

É necessário ter o PSPSDK instalado e configurado no ambiente de compilação. Depois, executa:

```sh
make
```

O resultado esperado é `EBOOT.PBP`. A saída só deve ser considerada funcional depois de ser testada no PPSSPP.

## Próximas etapas

1. Confirmar a compilação e o arranque do protótipo.
2. Criar o menu inicial e os controlos.
3. Implementar o primeiro personagem e um cenário de teste.
4. Desenvolver o sistema de luta, colisões, vida e animações.
5. Otimizar e integrar os recursos artísticos e sonoros.

**Nota:** neste momento ainda não existem modelos 3D, animações de combate, cenários completos nem uma ISO pronta. Não renomeies simplesmente o `EBOOT.PBP` para `.iso`; são formatos diferentes.


## Nova versão: seleção e combate inicial

O protótipo inclui agora:
- seleção entre Kapanji, Baraka e Jabari;
- arena de treino em modo texto;
- movimento horizontal;
- ataque normal e poder especial;
- energia, barras de vida e adversário com comportamento simples;
- ecrã de vitória/derrota e opção para recomeçar.

### Controlos no PPSSPP
- **Cima/Baixo:** escolher guerreiro no menu.
- **X:** iniciar combate / ataque normal.
- **Esquerda/Direita:** mover na arena.
- **O (Círculo):** poder especial (gasta 40% de energia).
- **Triângulo:** recuar.
- **START:** regressar ao menu; no menu, sair.

Esta é uma primeira mecânica de combate e ainda usa uma interface de texto. O próximo marco é validar a compilação e os controlos no PPSSPP antes de começar a integração de gráficos e animações.
