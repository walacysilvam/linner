/* ==========================================
* >     L!NNER
* >     small code controller like GIT
* >     vs(0.1)
* >                 by @walacysilva
* >                 github.com/walacysilvam
* ===========================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* criacao da funcao shadow:: branch
int shadow(char *name) {
    int neopath = mkdir(nome, 0777);

}                                      
*/
int add(char *arq) {
    FILE *arc = NULL;
    FILE *dst = NULL;
    size_t n = 0;
    size_t m = 0;
    unsigned char buf[1024 * 8];

    arc = fopen(arq, "rb");
    if (!arc) {
        printf("Linner error:: read error: failed to read archive: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    dst = fopen("./lnn/main/arc_teste.txt", "wb");
    if (!dst) {
        fclose(arc);
        printf("Linner error: read error: failed to open destiny archive: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    do {
        m = 0;
        n = fread( buf, 1, sizeof(buf), arc);

        if(n > 0)
            m = fwrite( buf, 1, n, dst);

    } while ((n > 0) && (n == m));

    if (m) {
        printf("Linner error:: copy error: failed to copy archive: %s\n", strerror(errno));
        fclose(dst);
        fclose(arc);

        //remove(&dst);
        return EXIT_FAILURE;
    }

    fclose(dst);
    fclose(arc);

    return EXIT_SUCCESS;
}

int init() {
    // 'starta' a estrutura inicial necessaria para o linner
    int check = mkdir("lnn", 0777);
    FILE *arq;
    time_t startTime;
    startTime = time(NULL);
    struct tm tm = *localtime(&startTime);

    if(!check) {
        int main = mkdir("lnn/main", 0777);
        arq = fopen("./lnn/lnn_p.txt", "w+");
        fprintf(arq, "start_point: [init]%d%d%d%d%d", tm.tm_mday, tm.tm_mon, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
        printf("Linner started:: add archive for begin.\n");

        fclose(arq);
    } else {
        printf("Erro ao criar diretorio.");
    }
}


void main(int argc, char *argv[ ]) {
    char *s = "start";

    // Tratamento dos argumentos e chamada de funcoes.
    if (argv > 0) {
        if (!strcmp(argv[1], "start")) {
            printf("O argumento passado foi: %s \n", argv[1]);
            init();
        }
        if ((!strcmp(argv[1], "add")) && (argv[2] > 0)) {
            /* conta os argumento passados
            if( argc != 3) {
                printf("Linner error:: sintaxe error: %s \n", arc);
                return EXIT_FAILURE;
            }
            */
            add(argv[2]);
        }
        
    }
}
