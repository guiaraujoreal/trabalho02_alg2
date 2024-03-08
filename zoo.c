#include <stdio.h>
#include <stdlib.h>

#define TAM 1000

typedef struct {
    char codigo[TAM];
    char nome[TAM];
    float peso;
    float altura;
    char especie[TAM];
} Info_animal;

//funcao para cadastrar os setores
void cadSetor(char **c_Setores, int f_nSetores) {
    for(int i = 0; i < f_nSetores; i++) {
        setbuf(stdin, NULL);
        printf("\nNome do setor: ");
        fgets(c_Setores[i], TAM, stdin);
    }
}

//funcao para adicionar setores
void addSetor(char ***a_Setores, int *a_nSetores) {
    int qntdSetor = 0;
    printf("\n>> ADICIONAR SETOR: \n\nDeseja adicionar quantos setores? ");
    scanf("%d", &qntdSetor);

    *a_Setores = (char **)realloc(*a_Setores, ((*a_nSetores) + qntdSetor) * sizeof(char *));
    if (*a_Setores == NULL) {
        exit(1);
    }

    // Nome dos novos setores
    for (int i = (*a_nSetores); i < (*a_nSetores) + qntdSetor; i++) {
        printf("\nQual o nome do %do setor?\n->", i + 1);
        setbuf(stdin, NULL);

        // Aloca memória para o nome do setor
        (*a_Setores)[i] = (char *)malloc(TAM * sizeof(char));
        if ((*a_Setores)[i] == NULL) {
            exit(1);
        }

        fgets((*a_Setores)[i], TAM, stdin);
    }

    *a_nSetores += qntdSetor;
}


int main() {
    Info_animal ***zoologico;
    char **setores;
    int nSetores, nJaulas, nAnimais, idSetor, *p_nSetores;
    p_nSetores = &nSetores;

    printf("\nDigite o numero de setores: ");
    scanf("%d",&nSetores);

    printf("\nAgora, digite o numero de jaulas por setor: ");
    scanf("%d", &nJaulas);

    printf("\nAgora, digite o numero de animais por jaula: ");
    scanf("%d", &nAnimais);

    zoologico = (Info_animal ***)malloc(nSetores * sizeof(Info_animal **));
    setores = (char **)malloc(nSetores * sizeof(char *));

    if(zoologico == NULL){
        exit(1);
    }
    for(int setor = 0; setor < nSetores; setor++) {
        zoologico[setor] = (Info_animal **)malloc(nJaulas * sizeof(Info_animal *));
        setores[setor] = (char *)malloc(nJaulas * sizeof(char));

        if(zoologico[setor] == NULL || setores[setor] == NULL){
            exit(1);
        }

        for(int jaula = 0; jaula < nJaulas; jaula++) {
            zoologico[setor][jaula] = (Info_animal *)malloc(nAnimais * sizeof(Info_animal));

            if(zoologico[setor][jaula] == NULL){
                exit(1);
            }
        }
    }

    cadSetor(setores, nSetores);
    addSetor(&setores, p_nSetores);
    printf("%d - %d",*p_nSetores, nSetores);

    //for(int i = 0; i < nSetores; i++) printf("%s", setores[i]);

    return 0;
    

}