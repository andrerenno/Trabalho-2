**Trabalho 2** 

ICC1 Eng. Comp. 2018 Prof. Adenilso

Esse projeto consiste de um programa desenvolvido em C para armazenar informações sobre alunos e suas notas na disciplina SSC-0600.
O programa pode também armazenar as informações em arquivos, os quais pode ler quando for executado novamente.

**Instalação - Linux** 

Para instalar no sistema operacional Linux, basta verificar que o ncurses está instalado e compilar o programa com o gcc. Essa biblioteca já vem instalada em vários sistemas, porém se não estiver, basta instalar o pacote que a contém (por exemplo, para arch, o pacote ncurses). para compilar, use o comando: 
gcc -o trab2 main.c groups.c file.c -lncurses -lm
execute o programa com .\trab2 

**Instalação - Windows**

Para instalar no Windows, baixe e instale o MinGW (www.mingw.org). O mingw não vem com a livraria necessária instalada por padrão, portanto, após instala-lo, abra o programa MinGW Installation Manager, clique em MinGW Libraries, do lado esquerdo da janela,  marque para instalação os pacotes que contêm pdcurses no nome, e instale-os clicando em Intallation e Apply Changes no canto superior esquerdo.
Talvez seja ainda necessário alterar as variáveis de ambiente para permitir executar o gcc pelo powershell, se esse for o caso, adicione C:\MinGW\bin à variavel Path, (pesquise Environment (ou Ambiente) para chegar à tela onde se pode alterar as variáveis  de ambiente).
Depois disso, é possível compilar pelo powershell usando o comando:
gcc -o trab2.exe main.c groups.c file.c -lpdcurses
E é possivel executá-lo clicando duas vezes em trab2.exe

