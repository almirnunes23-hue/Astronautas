# Diário da Atividade

Este diário serve para registrar o meu progresso passo a passo na atividade 'ASTRONAUTAS' 

## Ambiente

- Versão do OpenCode (`opencode --version`): V2
- Modelo usado: LongCat 2.5

## antes de programar

- O que cada classe guarda: As classes 'Voo' e 'Astronautas' guardam as ações que efetivamente serão tomadas e o registro relacionado
aos voos e aos astronautas. Já a classe 'Agencia', manipula os métodos e objetos das duas classes anteriores.

- O que acontece em `LANCAR_VOO`, em palavras: Esse método altera o estado de um voo registrado.

- Uma dúvida que eu tinha antes de começar: A funcionalidade da Classe 'Agencia'.

## uso de IA para entender algo

- O que perguntei (ou "não usei"): Coisas relacionadas ao léxico da língua e ao funcionamento do Vector.
- O que aprendi: Comandos específicos de C++.

## Primeiro contato: revisão sem editar

- As três melhorias que a IA sugeriu, em uma linha cada:
      1. Criar a função 'ImprimirVoo' para auxiliar a função 'listarvoo'.
      2. Adicionar const aos métodos que não modificam o objeto como 'getCpf()', 'getNome()', 'estaVivo()'.
      3. Usar const string& nos parâmetros.

- A que escolhi e por quê: Escolhi a primeira sugestão como forma de harmonizar e deixar mais entendível o código.

- O que mudou no código, e se os seis testes continuaram passando: A função auxiliar ajuda a diminuir o tamanho da função 'listarvoo'.

- O que entendi que não sabia antes: A aplicação de contantes.

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

- Primeira mensagem (o pedido do plano): Primeira mensagem: Pedi o que foi informado no enunciado da questão, ressaltei que não se pode alterar nenhuma saída e o pedi para ele explicar o seu plano antes de executar as edições.

- O plano que a IA apresentou, resumido: 'void listarAstronautas()', percorre os astronautas na ordem de cadastro e os separa em três grupos: disponíveis, mortos e em voo. 'void historico(string cpf)', verifica se o astronauta existe. Se não, imprime a mensagem de erro, se sim, percorre os voos na ordem de cadastro e mostra apenas os voos lançados em que ele estava a bordo.

- Mudei algo no plano antes de liberar? Não
- Resultado de `testar.sh missao1` e de `testar.sh parte1`:
- Precisei refazer? O que mudou no pedido:

## Missão 2: SALVAR e CARREGAR

- Primeira mensagem: Pedi o que foi informado no enunciado da questão, ressaltei que não se pode alterar nenhuma saída e o pedi para ele explicar o seu plano antes de executar as edições.

- O plano, resumido: Método salvar - Abrir o arquivo com ofstream. Se não abrir retorna erro, se abrir, percorrer os astronautas e os voos gravando um por linha. Método carregar - Abrir o arquivo com ifstream. Se não abrir retorna erro, Se abrir, limpar os vetores e ler linha por linha.

- O formato do arquivo (cole cinco linhas do `dados_teste.txt`): 
      ASTRONAUTA|111|30|1|1|Ana Maria
      ASTRONAUTA|222|35|0|0|Bruno Costa
      ASTRONAUTA|333|28|1|1|Carla Souza
      VOO|10|finalizado com sucesso|111
      VOO|20|finalizado com explosao|222

- Resultado de `testar.sh missao2` e de `testar.sh parte1`:
- Precisei refazer? O que mudou no pedido: Não

## Missão 3: RELATORIO

- Primeira mensagem: Pedi o que foi informado no enunciado da questão, ressaltei que não se pode alterar nenhuma saída e o pedi para ele explicar o seu plano antes de executar as edições.

- O plano, resumido: 
      Adicionar contador voosLancados na classe Astronauta para saber quantos voos cada astronauta já voou.
      Incrementar o contador no lancarVoo, para que, quando um voo for lançado, todos os astronautas a bordo recebem +1 no contador.
      Criar método relatorio() na classe Agencia que imprime as 9 linhas pedidas
      Atualizar salvar e carregar para gravar e restaurar o contador voosLancados no arquivo.

- Resultado de `testar.sh missao3` e de `testar.sh parte1`:
- Precisei refazer? O que mudou no pedido: Não.

## Missão 4: livre

- O que escolhi e por quê: Dois novos métodos 'MostrarAstronauta(cpf)' e 'Estatistica_Voo codigo(codigo)', para conseguir dados individuais de astronautas e voos.

- Primeira mensagem: Pedi a implementação dos dois métodos, explicando o que eu gostaria que retornasse, e ressaltei que não se pode alterar nenhuma saída e o pedi para ele explicar o seu plano antes de executar as edições.

- O que veio, comparado com o que eu esperava: Veio o que eu esperava.

- `testar.sh parte1` continuou passando? Sim.

- Aceitei, ajustei ou descartei? Por quê: Aceitei, a saída me bastou.

## Fechamento

- O que a IA fez que eu não conseguiria fazer sozinho nesse prazo: apesar do prazo alongado, eu enfrentaria dificuldades em implementar as missões e de formatar a saída tal qual era o esperado pelo teste.

- Onde ela errou ou fez algo que eu não pedi: No geral, a IA seguiu uma linha muito correta em relação aos comandos por mim enviados.

- O que eu faria diferente da próxima vez: Preciso de mais experiência para ter uma ideia.
