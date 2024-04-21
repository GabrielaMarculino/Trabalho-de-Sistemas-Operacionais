/*
Trabalho 1 - Sistemas Operacionais
Gabriela Marculino - RGM: 41431

linha de comando para executar o código: gcc -o main main.c

!Este código foi desenvolvido no Linux!
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/syscall.h>

#define BUFFER_SIZE 1024

int main() {
    // Nome dos arquivos de origem e destino
    char *arquivo_origem = "arquivo.txt";
    char *arquivo_destino = "arquivoCopia.txt";

    // Abrindo arquivo de origem para leitura
    int fd_origem = open(arquivo_origem, O_RDONLY);
    if(fd_origem == -1){
        perror("Erro ao abrir arquivo de origem");
        return errno;
    }

    // Criando (ou abrindo se já existir) arquivo de destino para escrita
    int fd_destino = open(arquivo_destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_destino == -1){
        perror("Erro ao criar ou abrir arquivo de destino");
        close(fd_origem);
        return errno;
    }

    // Buffer para armazenar os dados lidos do arquivo de origem
    char buffer[BUFFER_SIZE];
    ssize_t bytes_lidos, bytes_escritos;

    // Lendo dados do arquivo de origem e escrevendo no arquivo de destino
    while((bytes_lidos = read(fd_origem, buffer, BUFFER_SIZE)) > 0){
        bytes_escritos = syscall(SYS_write, fd_destino, buffer, bytes_lidos);
        if (bytes_escritos == -1) {
            perror("Erro ao escrever no arquivo de destino");
            close(fd_origem);
            close(fd_destino);
            return errno;
        }
    }

    // Verificando se houve erro na leitura do arquivo de origem
    if(bytes_lidos == -1){
        perror("Erro ao ler arquivo de origem");
        close(fd_origem);
        close(fd_destino);
        return errno;
    }

    // Fechando os arquivos
    close(fd_origem);
    close(fd_destino);

    printf("Cópia concluída com sucesso.\n");

    return 0;
}
