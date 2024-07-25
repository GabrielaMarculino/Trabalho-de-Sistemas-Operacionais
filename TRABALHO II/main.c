/*Gabriela Marculino - RGM: 41431
Sistemas Operacionais - Prof. Dr. Osvaldo Jacques
Páginação invertida - uma forma alternativa de implementação*/

/*Explicação: 
Objetivo
O objetivo deste algoritmo é implementar um método que, dado um endereço virtual, encontre o endereço físico correspondente, se existir, utilizando uma tabela de páginas invertida.

Estrutura da Tabela de Página Invertida
A tabela de página invertida normalmente contém:

O número da página virtual.
O número do processo (PID).
O endereço da moldura de página (frame address).

Estrutura da Tabela de Página Invertida: Definimos uma estrutura IPTEntry para armazenar as entradas da tabela de página invertida. Cada entrada contém o ID do processo (PID), o número da página virtual e a moldura de página (endereço físico).

Função access_inverted_page_table: Esta função recebe o PID e o endereço virtual e retorna o endereço físico correspondente, se encontrado. Caso contrário, retorna -1 para indicar que a página não foi encontrada.

Função add_iptable_entry: Esta função adiciona uma nova entrada na tabela de página invertida. Se a tabela estiver cheia, ela imprime uma mensagem de erro.

Inicialização: No main, inicializamos a tabela de página invertida com entradas vazias (-1) e demonstramos como adicionar uma entrada e acessá-la.*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 1024 // Número de molduras de página
#define PAGE_SIZE 4096 // Tamanho da página em bytes

// Estrutura para armazenar as entradas da tabela de página invertida
typedef struct {
    int pid; // ID do processo
    int virtual_page; // Número da página virtual
    int frame; // Moldura de página (endereço físico)
} IPTEntry;

// Tabela de página invertida
IPTEntry ipt[NUM_FRAMES];

// Função para buscar na tabela de página invertida
int access_inverted_page_table(int pid, int virtual_address) {
    int virtual_page = virtual_address / PAGE_SIZE;
    int offset = virtual_address % PAGE_SIZE;

    for (int i = 0; i < NUM_FRAMES; i++) {
        if (ipt[i].pid == pid && ipt[i].virtual_page == virtual_page) {
            return (ipt[i].frame * PAGE_SIZE) + offset;
        }
    }

    // Página não encontrada
    return -1;
}

// Função para adicionar uma entrada na tabela de página invertida
void add_iptable_entry(int pid, int virtual_page, int frame) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (ipt[i].pid == -1) { // Entrada vazia
            ipt[i].pid = pid;
            ipt[i].virtual_page = virtual_page;
            ipt[i].frame = frame;
            return;
        }
    }

    printf("Erro: Tabela de página invertida cheia\n");
}

int main() {
    // Inicializar a tabela de página invertida com entradas vazias
    for (int i = 0; i < NUM_FRAMES; i++) {
        ipt[i].pid = -1;
        ipt[i].virtual_page = -1;
        ipt[i].frame = -1;
    }

    // Exemplo de uso
    int pid = 1;
    int virtual_address = 8192; // Exemplo de endereço virtual
    int frame = 2; // Exemplo de moldura de página

    // Adicionar uma entrada na tabela de página invertida
    add_iptable_entry(pid, virtual_address / PAGE_SIZE, frame);

    // Acessar a tabela de página invertida
    int physical_address = access_inverted_page_table(pid, virtual_address);
    if (physical_address != -1) {
        printf("Endereço físico: %d\n", physical_address);
    } else {
        printf("Erro: Página não encontrada\n");
    }

    return 0;
}
