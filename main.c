#include <stdio.h>
#include <stdlib.h>

void bin2txt(char* nome,char* saida){
    FILE* arq = fopen(nome, "rb");
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
    fclose(arq);
    free(notas);
}



int* ler_arquivo(char* nome){
    FILE* arq = fopen(nome, "rb");
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
    free(notas);
}

void escreve_arquivo(char *nome){
    puts("ESCREVENDO???");
    char c;
    scanf(" %c",&c);
    if(c != 's' && c!= 'S'){
        return;
    }
    FILE* arq = fopen(nome, "rb+");
    if(!arq){
        arq = fopen(nome, "wb");
    }
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
    puts("ZERAR ARQUIVO???");
    char c;
    scanf("%c",&c);
    if(c == 's' || c == 'S'){
        FILE* arq = fopen(nome, "wb");
        fclose(arq);
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
    puts("remover nota???");
    char c;
    scanf(" %c",&c);
    if (c != 's' && c != 'S')return;
    while(1){
        print_arquivo(nome);
        int indice;
        puts("QUAL INDICE???");
        scanf("%d", &indice);
        FILE* arq = fopen(nome, "rb+");
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
    char baeta[10] = "testelemos";
    inicializa_arq(baeta);
    escreve_arquivo(baeta);
    add_nota(baeta);
    remove_nota(baeta);
    bin2txt(baeta,"lemos.txt");
    printf("CR: %d", calcular_cr(baeta));
    return 0;
}
