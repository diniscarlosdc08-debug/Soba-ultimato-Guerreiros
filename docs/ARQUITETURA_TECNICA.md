# Arquitetura técnica — SOBA ULTIMATO GUERREIROS EVOLUTION

## Alvo e direção

- **Plataforma:** PSP / emulador PPSSPP.
- **Tipo:** jogo homebrew compilado com PSPSDK.
- **Linguagem atual:** C.
- **Direção visual definida:** 3D cel-shading.
- **Câmara definida:** dinâmica cinematográfica, dirigida por estados de combate e eventos.
- **Prioridade:** personagens originais SOBA; crossover anime numa fase posterior.
- **Primeiro artefacto de teste:** `EBOOT.PBP`.

## Estrutura atual do repositório

- `src/main.c`: ponto de entrada e protótipo de combate.
- `Makefile`: instruções de compilação com PSPSDK.
- `assets/`: futuro conteúdo de arte, modelos, texturas, animações, som e arenas.
- `docs/PLANO_DO_PROJETO.md`: fases e critérios de conclusão.
- `docs/ARQUITETURA_TECNICA.md`: decisões técnicas.
- `.github/workflows/build-psp.yml`: compilação automática e artefacto, a validar por execução.

## Arquitetura lógica pretendida

Separar progressivamente o código por responsabilidade, evitando manter toda a lógica dentro de `main.c`:

1. **App/Game loop:** inicialização, atualização, desenho e encerramento.
2. **Input:** leitura do comando PSP e mapeamento dos controlos.
3. **Game state:** menu, seleção, combate, pausa e resultado.
4. **Fighter:** estado, posição, vida, energia, movimento, ataques e recuperação.
5. **Combat:** alcance, colisões, dano, invulnerabilidade temporária e efeitos de impacto.
6. **Camera:** enquadramento de ambos os lutadores e eventos cinematográficos limitados.
7. **Renderer:** desenho da arena, personagens, interface e efeitos.
8. **Assets:** carregamento, libertação e reutilização de modelos, texturas, animações e áudio.

Esta divisão é o destino arquitetural; nem todos estes módulos estão implementados no protótipo atual.

## Pipeline visual para PSP

### Modelos e cel-shading

- Preparar modelos low-poly com silhuetas reconhecíveis e proporções consistentes.
- Criar texturas pequenas e paletas controladas por personagem.
- Simular o cel-shading com cores por vértice, texturas pintadas e iluminação quantizada em poucos níveis, conforme o que for viável no renderer.
- Evitar depender de shaders programáveis modernos ou de efeitos de pós-processamento não adequados à PSP.
- Testar contornos por geometria duplicada ou soluções baseadas em textura apenas se o custo de desenho for aceitável.
- Manter cada personagem com materiais e partes de malha limitados; reduzir detalhes invisíveis à distância normal de combate.

### Animação e combate

- Começar com um rig simples e um conjunto mínimo de animações: idle, andar, guarda, ataque leve, ataque forte, dano, salto e especial.
- Usar máquinas de estado para evitar que ataques e animações incompatíveis sejam executados ao mesmo tempo.
- Reutilizar animações e efeitos sempre que possível.
- Fazer os efeitos de energia com sprites, billboards, texturas animadas e geometrias simples.

### Câmara dinâmica cinematográfica

- Manter como padrão uma câmara de combate que mostre os dois lutadores e a distância entre eles.
- Ajustar suavemente posição e zoom conforme a separação dos lutadores, dentro de limites definidos.
- Usar breves aproximações, deslocamentos ou enquadramentos especiais durante golpes decisivos, sem perder a leitura do combate.
- Retomar automaticamente a câmara normal no fim do evento.
- Evitar clipping na arena, movimentos bruscos e enquadramentos que escondam o jogador ou o adversário.
- Na primeira versão, privilegiar regras de câmara determinísticas em vez de um sistema cinematográfico complexo.

## Gestão de recursos e desempenho

- Controlar o orçamento de memória para código, modelos, texturas, áudio e buffers.
- Usar texturas com dimensões modestas e formatos suportados pelo pipeline PSPSDK; converter os recursos antes da integração.
- Carregar apenas os recursos da arena/personagens necessários e libertá-los quando deixam de ser usados.
- Limitar transparências sobrepostas, partículas, luzes e chamadas de desenho.
- Medir a taxa de fotogramas e o consumo de memória no PPSSPP e, quando possível, em hardware real.
- Definir limites numéricos de polígonos, ossos, materiais e tamanho das texturas depois de o primeiro personagem e a primeira arena serem medidos.

## Ordem de implementação

1. Validar o build atual e o arranque do `EBOOT.PBP`.
2. Confirmar o menu e o combate básico no PPSSPP.
3. Criar um teste de renderização 3D simples e confirmar a viabilidade do pipeline na PSP.
4. Modelar e integrar um primeiro personagem original SOBA.
5. Implementar animações e câmara de combate básica.
6. Completar Kapanji, Baraka, Makena e Jabari, depois a primeira arena.
7. Integrar efeitos, áudio, interface e câmara cinematográfica por eventos.
8. Otimizar, testar e só então iniciar a fase de crossover.

## Personagens e referências

A primeira etapa artística deve concentrar-se em Kapanji, Baraka, Makena e Jabari, mantendo as suas identidades, vestuário e poderes próprios. Personagens de outros animes serão considerados depois da base original. Para personagens reconhecíveis, as referências devem orientar a fidelidade visual; os recursos usados na distribuição devem ser próprios, autorizados ou licenciados para esse uso.

## Build e distribuição

O objetivo inicial é `EBOOT.PBP`, formato comum para homebrew PSP. Uma ISO não é necessária para testar o protótipo. O estado de sucesso da compilação deve ser confirmado no GitHub Actions e o ficheiro gerado deve ser testado no PPSSPP antes de se afirmar que uma versão está pronta.

## Estado atual e limitações

O protótipo atual em `src/main.c` é uma prova de lógica de combate apresentada em texto. Ainda não representa a direção visual 3D cel-shading, não contém modelos 3D finais nem implementa a câmara cinematográfica pretendida. Estes itens são objetivos de desenvolvimento e precisam de ser construídos e medidos na PSP.
