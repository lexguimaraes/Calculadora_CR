#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int calcular_cr(char* nome);

int pai(int ind){
    if(ind>0)return ind-1/2;
    return -1;
}

int esq(int ind){
    return ind*2+1;
}

int dir(int ind){
    return esq(ind)+1;
}

void max_heapify(int* v, int n, int ind){
    int e = esq(ind);
    int d = dir(ind);
    int maior = ind;
    if(e < n && v[e]>v[ind])maior = e;
    if(d < n && v[d]>v[maior])maior = d;
    if(maior != ind){
        int temp = v[maior];
        v[maior] = v[ind];
        v[ind] = temp;
        max_heapify(v, n, maior);
    }
}

void build_maxheap(int*v, int n){
    int ult_pai = pai(n-1);
    for(int i = ult_pai;i>=0;i--){
        max_heapify(v,n,i);
    }
}

void heap_sort(int *v, int n){
    build_maxheap(v, n);
    for(int i = n-1;i>0;i--){
        int temp = v[i];
        v[i] = v[0];
        v[0] = temp;
        max_heapify(v, i, 0);
    }
}

int in_vet(const int* vet,int n,int k,int o){
    for(int i = 0;i<n;i+=2){
        if(vet[i] == k && vet[i+1] == o)return 1;
    }
    return 0;
}




void bin2txt(char* nome,char* saida){
    FILE* arq = fopen(nome, "rb");
    if(!arq)exit(1);
    int tam;
    fread(&tam,sizeof(int),1,arq);
    int *notas = malloc((sizeof(int)*tam));
    for(int i = 0; i < tam; i++){
        fread(&notas[i],sizeof(int),1,arq);
    }
    fclose(arq);
    int notas_ord[tam];
    int ind = 0;
    for(int i = 0; i < tam; i++){
        notas_ord[i] = notas[ind];
        ind+=2;
    }
    heap_sort(notas_ord,tam/2);
    arq = fopen(saida, "wb");
    int ch_rep[tam];
    int ch_ind=0;
    for(int j = 0;j<tam/2;j++){
            for(int i = 0; i < tam; i+=2){
                if(notas_ord[j] == notas[i]) {
                    if(!in_vet(ch_rep,ch_ind,notas[i],notas[i+1])){
                        fprintf(arq, "%d.  NOTA: %d   CARGA HORARIA: %d\n", ch_ind/2, notas[i], notas[i + 1]);
                        ch_rep[ch_ind] = notas[i];
                        ch_ind++;
                        ch_rep[ch_ind] = notas[i+1];
                        ch_ind++;
                    }
                }
            }
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
    puts("N DE MATERIAS NOVAS, NO MÁXIMO 20 DE UMA VEZ");
    int size;
    scanf("%d",&size);
    if (size<=0 || size > 20){
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
    scanf(" %c",&c);
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
                printf("CR: %d\n\n", calcular_cr(buff));
                //print_arquivo(buff);
                break;
            default:
                break;
        }
        if(opcao == 4)break;
    }
    bin2txt(buff,buff2);
    printf("CR: %d\n", calcular_cr(buff));
    return 0;
}
