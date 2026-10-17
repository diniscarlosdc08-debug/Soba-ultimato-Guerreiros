# Plano de desenvolvimento — SOBA ULTIMATO GUERREIROS EVOLUTION

## Visão do projeto

Criar um jogo de luta para PSP, testável também no PPSSPP, com identidade visual anime em **3D cel-shading** e **câmara dinâmica cinematográfica**. A primeira prioridade é apresentar e validar os personagens originais do universo SOBA antes de iniciar o crossover com personagens de outros animes.

## Decisões confirmadas

- **Plataforma-alvo:** PSP / PPSSPP.
- **Direção visual:** 3D cel-shading — silhuetas claras, cores planas e sombras em poucos níveis para criar aparência de anime.
- **Câmara:** dinâmica cinematográfica, com enquadramentos de combate, aproximações moderadas e movimentos controlados durante golpes especiais.
- **Prioridade de produção:** personagens originais SOBA primeiro.
- **Ferramentas atuais:** C e PSPSDK para o protótipo homebrew; os recursos finais devem ser preparados em formatos e dimensões adequados à PSP.
- **Primeiro formato de teste:** `EBOOT.PBP`; não é necessário criar uma ISO para validar o protótipo.

## Ordem de produção

### Fase 1 — base técnica e protótipo
- [ ] Manter o protótipo atual funcional e validar a compilação no GitHub Actions.
- [ ] Confirmar os controlos, estados de menu, combate e resultado no PPSSPP.
- [ ] Definir resolução, escala de interface e orçamento de memória para os recursos.

### Fase 2 — direção artística e personagens originais
- [ ] Criar fichas visuais consistentes para **Kapanji, Baraka, Makena e Jabari**: silhueta, paleta, roupa, rosto, arma e poderes.
- [ ] Construir primeiro um modelo 3D simplificado de um personagem e validar a leitura visual na PSP.
- [ ] Aplicar cel-shading económico, preferindo cores por vértice/texturas e poucos níveis de luz em vez de shaders modernos dispendiosos.
- [ ] Preparar rig e animações essenciais: posição neutra, andar, guarda, ataque, dano, salto e especial.
- [ ] Criar uma arena de teste pequena com fundo simples e colisões previsíveis.

### Fase 3 — combate e câmara
- [ ] Implementar movimento, distância entre lutadores, colisões, vida, energia e recuperação após ataques.
- [ ] Criar uma câmara de combate que acompanhe os dois lutadores sem perder a ação de vista.
- [ ] Usar mudanças cinematográficas controladas em golpes especiais; regressar rapidamente ao enquadramento normal.
- [ ] Garantir que os efeitos visuais não ocultam os personagens nem prejudicam a taxa de fotogramas.

### Fase 4 — conteúdo SOBA
- [ ] Integrar personagens, armas, poderes, animações, efeitos sonoros e arenas originais.
- [ ] Criar um menu visual com retratos e seleção de personagens.
- [ ] Testar cada personagem e cada especial em hardware/emulador.

### Fase 5 — crossover e expansão
- [ ] Só depois de validar a base SOBA, planear personagens convidados de universos anime.
- [ ] Quando forem usados personagens conhecidos, procurar referências visuais fiáveis e preservar os seus traços reconhecíveis — cabelo, roupa, silhueta, cores e poderes — dentro das limitações técnicas.
- [ ] Usar apenas recursos próprios, autorizados ou com licença adequada. Personagens protegidos por direitos de autor podem exigir autorização para distribuição pública.

### Fase 6 — testes e entrega
- [ ] Compilar e inspecionar os registos do GitHub Actions.
- [ ] Testar o `EBOOT.PBP` no PPSSPP e, se possível, numa PSP real.
- [ ] Verificar estabilidade, memória, tempos de carregamento, legibilidade e desempenho.
- [ ] Publicar uma versão apenas depois de confirmar o artefacto e documentar os controlos.

## Restrições técnicas da PSP

- Manter modelos de baixa/média contagem de polígonos, malhas simples e poucos materiais por personagem.
- Preferir texturas pequenas e comprimidas/convertidas para formatos suportados pelo pipeline PSP; controlar o uso de memória de texturas.
- Limitar luzes dinâmicas, transparências, partículas e pós-processamento. Simular contornos e sombras com técnicas económicas, em vez de depender de shaders modernos.
- Usar efeitos de poderes sobretudo com sprites, billboards, texturas animadas e geometrias simples.
- Limitar ossos e influências do rig, reutilizar animações e carregar apenas os recursos necessários à arena atual.
- A câmara cinematográfica deve ser dirigida por regras e eventos simples, evitando movimentos bruscos, clipping e enquadramentos que tirem os lutadores do ecrã.
- Medir o desempenho no dispositivo/emulador; os limites exatos devem ser ajustados após o primeiro modelo e cenário de teste.

## Estado atual

O repositório contém um protótipo de combate em C, ainda baseado em apresentação textual. A direção 3D cel-shading e a câmara cinematográfica são decisões de produção, não funcionalidades já implementadas. O próximo marco é validar o protótipo e produzir um primeiro personagem SOBA de teste, sem afirmar que os modelos 3D ou a câmara final já existem.
