#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int calcular_cr(char* nome);

void bin2txt(char* nome,char* saida){
    FILE* arq = fopen(nome, "rb");
    if(!arq)exit(1);
    int tam;
    fread(&tam,sizeof(int),1,arq);
    int *notas = malloc((sizeof(int)*tam)+1);
    notas[0] = tam;
    for(int i = 0; i < tam; i++){
        fread(&notas[i+1],sizeof(int),1,arq);
    }
    fclose(arq);
    arq = fopen(saida, "wb");
    for(int i = 0; i < tam; i+=2){
        fprintf(arq,"%d.  NOTA: %d   CARGA HORARIA: %d\n",i/2,notas[i+1],notas[i+2]);
    }
    fprintf(arq,"CR : %d\n",calcular_cr(nome));
    fclose(arq);
    free(notas);
}



int* ler_arquivo(char* nome){
    FILE* arq = fopen(nome, "rb");
    if(!arq)exit(1);
    int tam;
    fread(&tam,sizeof(int),1,arq);
    int *notas = malloc((sizeof(int)*tam)+1);
    notas[0] = tam;
    for(int i = 0; i < tam; i++){
        fread(&notas[i+1],sizeof(int),1,arq);
    }
    fclose(arq);
    return notas;
}
void print_arquivo(char* nome){
    int* notas = ler_arquivo(nome);
    int tam = notas[0];
    for(int i = 0; i < tam; i+=2){
        printf("%d.  NOTA: %d   CARGA HORARIA: %d\n",i/2,notas[i+1],notas[i+2]);
    }
    puts("");
    free(notas);
}

void escreve_arquivo(char *nome){
    FILE* arq = fopen(nome, "wb");
    int nota,ch,size;
    fseek(arq, 0,SEEK_END);
    puts("N DE MATERIAS");
    scanf("%d",&size);
    int t = size*2;
    fwrite(&t,sizeof(int),1,arq);
    for (int i = 0; i < size ; i++){
        puts("NOTA E CARGA HORARIA");
        scanf("%d %d", &nota,&ch);
        fwrite(&nota, sizeof(int),1,arq);
        fwrite(&ch, sizeof(int),1,arq);
    }
    fclose(arq);
}

void add_nota(char* nome){
    puts("N DE MATERIAS NOVAS");
    int size;
    scanf("%d",&size);
    if (size<=0){
        return;
    }
    int t;
    FILE* arq = fopen(nome,"rb+");
    if(!arq)exit(1);
    fread(&t, sizeof(int),1,arq);
    t+= size*2;
    fseek(arq, 0,SEEK_SET);
    fwrite(&t, sizeof(int),1,arq);
    fseek(arq,0,SEEK_END);
    int nota,ch;
    for(int i = 0;i<size;i++){
        puts("NOTA E CARGA HORARIA");
        scanf("%d %d",&nota, &ch);
        fwrite(&nota, sizeof(int),1,arq);
        fwrite(&ch,sizeof(int),1,arq);
    }
    fclose(arq);
}

void inicializa_arq(char* nome){
    puts("Arquivo novo ou deseja zerar um arquivo existente?");
    char c;
    scanf("%c",&c);
    if(c == 's' || c == 'S'){
        FILE* arq = fopen(nome, "wb");
        fclose(arq);
        escreve_arquivo(nome);
    }
}

int calcular_cr(char* nome){
    int* notas = ler_arquivo(nome);
    int size = notas[0];
    print_arquivo(nome);
    int cr = 0;
    int t;
    int ch = 0;
    for (int i = 0; i < size; i+=2){
        t = notas[i+1] * notas[i+2];
        ch += notas[i+2];
        cr += t;
    }
    free(notas);
    return cr/ch;
}

void remove_nota(char* nome){
    while(1){
        print_arquivo(nome);
        int indice;
        puts("QUAL INDICE???");
        scanf("%d", &indice);
        FILE* arq = fopen(nome, "rb+");
        if(!arq)exit(1);
        int size;
        fread(&size,sizeof(int),1,arq);
        if (size/2 <= indice || indice < 0){
            fclose(arq);
            return;
        }
        int nota,ch;
        FILE* temp  = fopen("temp.bin","wb");
        int t = size-2;
        fwrite(&t,sizeof(int),1,temp);
        for(int i = 0;i<size/2;i++){
            fread(&nota,sizeof(int),1,arq);
            fread(&ch,sizeof(int),1,arq);
            if(i!= indice){
                fwrite(&nota, sizeof(int),1,temp);
                fwrite(&ch, sizeof(int),1,temp);
            }
        }
        fclose(arq);
        fclose(temp);
        remove(nome);
        rename("temp.bin",nome);
    }
}
int main(void) {
    char buff[20];
    char buff2[20];
    printf("Digite o nome do arquivo binario a ser criado, ou lido\n");
    scanf("%16[^\n]%*c",buff);
    strcpy(buff2,buff);
    strcat(buff2,".txt");
    strcat(buff, ".bin");
    inicializa_arq(buff);
    while(1){
        int opcao;
        printf("[1] - Adicionar notas\n[2] - Remover notas\n[3] - Listar notas\n[4] - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                add_nota(buff);
                break;
            case 2:
                remove_nota(buff);
                break;
            case 3:
                print_arquivo(buff);
                break;
            default:
                break;
        }
        if(opcao == 4)break;
    }
    bin2txt(buff,buff2);
    printf("CR: %d", calcular_cr(buff));
    return 0;
}
