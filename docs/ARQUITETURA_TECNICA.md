# Arquitetura técnica — Soba Ultimato Guerreiros

## Alvo

- Plataforma: PSP / emulador PPSSPP.
- Tipo de projeto inicial: homebrew, compilado com PSPSDK.
- Linguagem inicial: C.
- Arte e áudio: recursos originais otimizados para os limites da PSP.

## Estrutura

- `src/main.c`: ponto de entrada e ciclo principal inicial.
- `Makefile`: instruções de compilação PSPSDK.
- `assets/`: recursos do jogo.
- `docs/`: decisões e instruções do projeto.
- `.github/workflows/build-psp.yml`: tentativa de compilação automática e publicação do artefacto.

## Fases de desenvolvimento

1. Confirmar que o projeto compila e gera `EBOOT.PBP`.
2. Abrir o executável no PPSSPP e testar o arranque e o botão START.
3. Criar menu inicial e navegação.
4. Implementar jogador, controlos, câmara e primeiro cenário de teste.
5. Implementar combate, colisões, vida e animações.
6. Integrar personagens e cenários originais, áudio e interface.
7. Testar desempenho e empacotar a versão de distribuição.

## Formato de distribuição

O primeiro objetivo é `EBOOT.PBP`, formato comum de aplicações homebrew PSP. Uma ISO não é necessária para testar este protótipo e não deve ser criada artificialmente apenas mudando a extensão do ficheiro. A distribuição final dependerá da forma como o jogo for empacotado e testado.

## Limitações atuais

Este scaffold não inclui ainda modelos 3D, animações de luta, cenários completos, música ou sistema de combate. A compilação automática também precisa de ser executada e validada antes de se afirmar que o executável funciona.
