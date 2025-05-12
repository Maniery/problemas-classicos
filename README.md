Tarefa 1.1 – DCT2101: Sistemas Operacionais

📌 Objetivo
Esta atividade implementa soluções com semáforos POSIX para três problemas clássicos de sincronização de processos:

Problema do Buffer Limitado (Produtor-Consumidor)

Problema dos Leitores e Escritores

Problema do Jantar dos Filósofos

📁 Estrutura dos Arquivos

buffer_posix.c – Implementação do buffer limitado com semáforos POSIX

leitores_escritores.c – Solução com múltiplos leitores e escritores

filosofos.c – Solução para o jantar dos filósofos evitando deadlock

🔧 Semáforos POSIX
Utilizamos os semáforos POSIX com as seguintes funções da biblioteca <semaphore.h>:

sem_t → Tipo do semáforo

sem_init() → Inicialização

sem_wait() → Espera (bloqueia se necessário)

sem_post() → Libera (incrementa)

sem_destroy() → Libera os recursos

📦 Descrição das implementações
1. Buffer Limitado – buffer.c
Semáforos usados:
mutex – Exclusão mútua no acesso ao buffer
cheio – Conta quantos itens há no buffer (para consumidores)
vazio – Conta quantos espaços livres há no buffer (para produtores)

Funcionamento:
Produtores aguardam vazio, entram na seção crítica com mutex, produzem, e sinalizam cheio.
Consumidor aguarda cheio, entra na seção crítica com mutex, consome, e sinaliza vazio.

2. Leitores-Escritores – leitores_escritores.c
Semáforos usados:
mutex – Protege o contador de leitores readcount
wrt – Exclusão mútua entre escritores e leitores

Funcionamento:
Leitores: se o primeiro leitor entra, bloqueia escritores. O último a sair libera.
Escritores: aguardam wrt para acesso exclusivo ao dado compartilhado.

3. Jantar dos Filósofos – filosofos.c

Semáforos usados:

Vetor sem_t garfos[N] – Um semáforo para cada garfo

Funcionamento:
Filósofos pares pegam primeiro o garfo à esquerda, depois o da direita.
Filósofos ímpares pegam primeiro o da direita, depois o da esquerda.
Isso evita deadlock, pois quebra a ordem uniforme de aquisição de recursos.

⚙️ Compilação e Execução
Certifique-se de ter o compilador gcc com suporte a POSIX threads (-pthread).


-Buffer Limitado


gcc -pthread buffer_posix.c -o buffer


./buffer 5 3 (tamanho do buffer/numero de produtores)

-Leitores e Escritores


gcc -pthread leitores_escritores.c -o leitores


./leitores 3 2 (numero de leitores/numero de escritores)


-Jantar dos Filósofos


gcc -pthread filosofos.c -o filosofos


./filosofos 5 (numero de filósofos)


⚠️ Impacto da Sincronização com Semáforos POSIX
Antes da implementação com semáforos POSIX, os três códigos apresentavam problemas sérios de concorrência devido à ausência de mecanismos de controle de acesso a dados compartilhados. A seguir, descreve-se a situação anterior e os efeitos da sincronização aplicada.

1. Buffer Limitado (buffer.c)
Antes: Produtores e consumidor acessavam o buffer simultaneamente, causando condições de corrida, como sobrescrita de posições já preenchidas ou consumo de posições vazias.

Depois: Com semáforos mutex, cheio e vazio, foi possível garantir:

Exclusão mútua no acesso ao buffer;

Espera adequada por espaço ou itens disponíveis;

Eliminação completa de conflitos entre produtores e consumidor.

2. Leitores e Escritores (leitores_escritores.c)
Antes: Escritores podiam modificar o dado compartilhado enquanto leitores estavam lendo, o que resultava em leitura de dados inconsistentes. Além disso, a variável readcount era manipulada sem proteção, levando a resultados indeterminados.

Depois: Com os semáforos mutex e wrt:

Leitores podem acessar simultaneamente com segurança;

Escritores obtêm exclusividade total de acesso;

O acesso a readcount é protegido, evitando corrupção de estado interno;

As condições de sincronização estão plenamente atendidas.

3. Jantar dos Filósofos (filosofos.c)
Antes: Não havia nenhum mecanismo real de exclusão mútua para os garfos. Filósofos podiam pegar o mesmo garfo simultaneamente, causando inconsistência, deadlock e inanição.

Depois: Com o uso de semáforos individuais por garfo e a estratégia de alternância (pares pegam um garfo antes dos ímpares e vice-versa):

Garante-se que apenas um filósofo por vez segure cada garfo;

Deadlocks são evitados de forma efetiva;

A solução respeita os princípios da exclusão mútua e progresso.

