# ⚔️ Batalha Pokémon

Simulador de batalhas de Pokémon em C

---

## Descrição

O programa simula uma batalha por turnos entre dois treinadores. Cada treinador possui uma equipe de Pokémons com atributos individuais (nome, ataque, defesa, vida e tipo). Os dados são lidos de um arquivo `.txt` e a batalha é processada automaticamente, levando em conta as vantagens e desvantagens de tipo entre os Pokémons.

---

## Funcionalidades

- Leitura dos dados dos Pokémons a partir de um arquivo de texto
- Cálculo de vantagem/desvantagem de tipo (bônus de +20% ou penalidade de -20% no ataque)
- Simulação de batalha por turnos entre os dois treinadores
- Exibição do vencedor, Pokémons sobreviventes e derrotados

---

## Estrutura do Projeto

```
propostatp.c          # Código-fonte principal
arquivopokemon.txt    # Arquivo de entrada com os dados dos Pokémons (criado pelo usuário)
```

---

## Formato do Arquivo de Entrada

O arquivo `arquivopokemon.txt` deve estar na mesma pasta do executável e seguir o formato abaixo:

```
<qtd_pokémons_jogador1> <qtd_pokémons_jogador2>
<nome> <ataque> <defesa> <vida> <tipo>   ← Pokémons do Jogador 1 (um por linha)
<nome> <ataque> <defesa> <vida> <tipo>   ← Pokémons do Jogador 2 (um por linha)
```

### Tipos disponíveis

| Tipo       | Vantagem contra | Desvantagem contra |
|------------|-----------------|--------------------|
| `eletrico` | `agua`          | `pedra`            |
| `agua`     | `fogo`          | `eletrico`         |
| `fogo`     | `gelo`          | `agua`             |
| `gelo`     | `pedra`         | `fogo`             |
| `pedra`    | `eletrico`      | `gelo`             |

### Exemplo de arquivo de entrada

```
3 2
Squirtle 10 15 15 agua
Vulpix 15 15 15 fogo
Onix 5 20 20 pedra
Golem 20 5 10 pedra
Charmander 20 15 12 fogo
```

---

## Exemplo de Saída

```
Pokemons do Treinador 1:
Squirtle 10 15 15 agua
Vulpix 15 15 15 fogo
Onix 5 20 20 pedra

Pokemons do Treinador 2:
Golem 20 5 10 pedra
Charmander 20 15 12 fogo

Resultados finais:
Squirtle venceu Golem
Charmander venceu Squirtle
Vulpix venceu Charmander

Treinador 1 Venceu!!

Pokemon sobreviventes:
Vulpix
Onix

Pokemon derrotados:
Golem
Charmander
```

---

## Compilação e Execução

### Pré-requisitos

- Compilador C (GCC recomendado)

### Compilar

```bash
gcc propostatp.c -o batalha_pokemon
```

### Executar

```bash
./batalha_pokemon
```

> O arquivo `arquivopokemon.txt` deve estar no mesmo diretório que o executável.

---

## Funções Principais

### `vantagens(Pokemon atacante, char *tipo_oponente)`
Calcula o ataque ajustado com base na relação de tipos entre atacante e defensor.
- Retorna `ataque * 1.2` se o tipo do atacante tem vantagem
- Retorna `ataque * 0.8` se o tipo do atacante tem desvantagem
- Retorna `ataque` em caso neutro

### `batalha_pokemon(Pokemon jogador1[], int n1, Pokemon jogador2[], int n2)`
Simula os confrontos turno a turno. Em cada turno, o Pokémon do Jogador 1 ataca o Pokémon atual do Jogador 2. Se o defensor sobreviver, ele contra-ataca. Pokémons com vida ≤ 0 são eliminados e o próximo Pokémon entra em campo.

### `carregar_dados(const char *arquivopokemon, ...)`
Abre e lê o arquivo de entrada, preenchendo os arrays de Pokémons de cada jogador com seus respectivos atributos.

### `main()`
Ponto de entrada do programa. Chama `carregar_dados`, exibe as equipes e inicia a batalha via `batalha_pokemon`.

---

## Limitações

- Máximo de 100 Pokémons por jogador (`MAX_POKEMON`)
- Nomes e tipos com até 49 caracteres (`MAX_NOME`)
- Apenas 5 tipos disponíveis: `eletrico`, `agua`, `fogo`, `gelo`, `pedra`
