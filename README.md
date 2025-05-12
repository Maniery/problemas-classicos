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

gcc -pthread buffer.c -o buffer

./buffer 5 3 (tamanho do buffer/numero de produtores)

-Leitores e Escritores

gcc -pthread leitores_escritores.c -o leitores

./leitores 3 2 (numero de leitores/numero de escritores)


-Jantar dos Filósofos


gcc -pthread filosofos.c -o filosofos


./filosofos 5 (numero de filósofos)


