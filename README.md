# Simulador de escalonamento de processos

## :book: Descrição

Projeto final da matéria de Sistemas Operacionais da UFRJ no período de 2021.2.

### Membros do grupo:
- Arthur Guilherme
- Gabriel Izoton
- Yago Alves

## :dart: Objetivo

Desenvolver um simulador que implementa o algoritmo de escalonamento de processos, usando
a estratégia de seleção *Round Robin (ou Circular)* com *Feedback*.


## <a name="dependencias"></a> :books: Dependências

- ### GCC:
    
    Compilador de C da GNU, versão compatível com o padrão C17. Baixe do site oficial: https://gcc.gnu.org/;


- ### make:
    
    Ferramenta para controlar a criação e limpeza dos arquivos executáveis usados neste projeto. Para Windows, o MinGW já possui o make e geralmente distribuições Linux já vem com a ferramenta instalada. Caso não possua a ferramenta, baixe do site oficial: https://www.gnu.org/software/make/;


- ### SDL2:
    O Simple DirectMedia Layer é utilizado neste projeto para gerenciar janelas e gráficos em baixo nível. As bibliotecas de desenvolvimento estão em https://www.libsdl.org/download-2.0.php.

    Também utilizamos a extensão SDL2 TTF para mostrar texto na janela. A biblioteca está disponível em https://github.com/libsdl-org/SDL_ttf.
    

## :computer: Executando o projeto:

### A partir do código fonte:

- Garanta que todas as [dependências](#dependencias) estão satisfeitas.
- Execute `make` para compilar, conectar e criar o executável.
- Execute `./scheduling_sim` para rodar o projeto.
- Execute `make clean` para remover os binários gerados caso queira realizar uma outra compilação.


## :busts_in_silhouette: Contribuindo com o projeto

### Caso não seja um colaborador do projeto:

- Crie uma nova [**issue**](https://github.com/Gaizgrol/os-process-scheduling-sim/issues) no projeto.
- Realize um *fork* do projeto no GitHub.
- Faça as alterações necessárias e envie para o seu *fork*.
- Crie uma *pull request* para a branch `contribuidores` e descreva as alterações realizadas.


## :x: Problemas

- Caso não consiga executar algum comando ou não consiga abrir a janela do projeto, verifique se as dependências foram corretamente instaladas.
- Caso tenha algum erro de execução, sinta-se à vontade para criar uma nova [**issue**](https://github.com/Gaizgrol/os-process-scheduling-sim/issues) no projeto.


## :label: Créditos:

- Fonte utilizada para visualização: https://www.fontspace.com/pixelletters-font-f22954