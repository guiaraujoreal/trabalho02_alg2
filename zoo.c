#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAM 100

typedef struct {
    char codigo[TAM];
    char nome[TAM];
    float peso;
    float altura;
    char especie[TAM];
} Info_animal;


// Funcao para cadastrar os setores
void cadSetor(char **c_Setores, int f_numero_doSetores) {
    printf("\n\n\t\t=== (+) CADASTRAR SETORES ===");

    for(int i = 0; i < f_numero_doSetores; i++) {
        setbuf(stdin, NULL);
        printf("\nNome do setor: ");
        fgets(c_Setores[i], TAM, stdin);
    }
}

//Funcao para mostrar setores
void viewSetores(char **setorView, int n_SetoresView) {
    printf("\n\t\t ==== LISTAGEM DE SETORES ====");
    printf("\n\nID \t SETORES \n");

    for(int i = 0; i < n_SetoresView; i++) {
        printf("\n%d \t %s", i + 1, setorView[i]);
    }
}

// Funcao para mostrar os animais de uma jaula
void viewAnimais(Info_animal ***m_animal, int numero_doSetor, int numero_daJaula, int qntdAnimais) {
    printf("\n\n\t\t==== (#) ANIMAIS REGISTRADOS NESSA JAULA ====\n\n#\t\tCOD.\t\tNOME\n");

    // Verificar se numero_doSetor e numero_daJaula estão dentro dos limites
    if (qntdAnimais == 0) {
        printf("\n(<->) Ainda nao ha animais cadastrados nessa jaula");
    } else {
        for (int animal = 0; animal < qntdAnimais; animal++) {
            // Remove a quebra de linha do codigo do animal
            size_t codigo_len = strlen(m_animal[numero_doSetor][numero_daJaula][animal].codigo);
            if (codigo_len > 0 && m_animal[numero_doSetor][numero_daJaula][animal].codigo[codigo_len - 1] == '\n') {
                m_animal[numero_doSetor][numero_daJaula][animal].codigo[codigo_len - 1] = '\0';
            }

            printf("\n%d\t\t%s\t\t%s", animal + 1, m_animal[numero_doSetor][numero_daJaula][animal].codigo, m_animal[numero_doSetor][numero_daJaula][animal].nome);
        }
    }
}



// Funcao para cadastrar novos animais
void cadAnimal(Info_animal ***animal, char **matrizSetores, int qntdSetores, int **m_qntdAnimal, int qntdJaulas, int qntdAnimais) {
    char set[TAM], statusDisponibilidade[TAM];
    int numero_daJaula, indiceSetor = 0, indiceAnimal = 0;
    printf("\n\t\t==== (+) CADASTRAR UM NOVO ANIMAL ====\n\n(Voce pode listar os setores digitando 'S' na opcao abaixo)");

    printf("\n\n(?) Em qual setor este animal se enquadra?\n-> ");
    fgets(set, sizeof(set), stdin);

    // Verifica se 'S' foi pressionado
    if(tolower(set[0]) == 's' && (set[1] == '\n' || set[1] == ' ')) {
        viewSetores(matrizSetores, qntdSetores);

        printf("\n\n(?) Em qual setor este animal se enquadra?\n-> ");
        fgets(set, sizeof(set), stdin);
    }
    
    // Verificar a disponibilidade das jaulas no setor correspondente
    //Recupera o indice do setor digitado
    for(int setor = 0; setor < qntdSetores; setor++) {
        if(strcmp(matrizSetores[setor], set) == 0) indiceSetor = setor;//indiceSetor = setor
    }

    // Remove a quebra de linha no final da palavra em 'set'
    for(int i = 0; set[i] != '\0'; i++) if(set[i] == '\n') set[i] = '\0';

    printf("\n\t\t-> LISTA DE JAULAS DO SETOR '%s' <-\n\nID\t\tQUANTIDADE DE ANIMAIS\t\tDISPONIBILIDADE\n", set);
    for(int jaula = 0; jaula < qntdJaulas; jaula++) {

        if(m_qntdAnimal[indiceSetor][jaula] >= qntdAnimais) strcpy(statusDisponibilidade,"Indisponivel");
        else strcpy(statusDisponibilidade, "Disponivel");

        printf("\n%d\t\t\t%d\t\t\t%s", jaula + 1, m_qntdAnimal[indiceSetor][jaula], statusDisponibilidade);
    }

    printf("\n\nEm qual jaula este animal permanecera? (Digite a ID)\n-> ");
    scanf("%d", &numero_daJaula);

    int indice_daJaula = numero_daJaula - 1;

    indiceAnimal = m_qntdAnimal[indiceSetor][(indice_daJaula)];

    printf("\n(<->) Jaula %d selecionada.", numero_daJaula);

    //Mostra os animais ja cadastrado na jaula
    viewAnimais(animal,indiceSetor,indice_daJaula,indiceAnimal);

    // Cadastro do animal no sistema
    printf("\n\n\t\t=== ADICIONAR INFORMACOES DO NOVO ANIMAL ===\n");

    setbuf(stdin, NULL);
    printf("\n(?) Qual eh o codigo deste animal?\n-> ");
    fgets(animal[indiceSetor][indice_daJaula][indiceAnimal].codigo, sizeof(animal[indiceSetor][numero_daJaula][indiceAnimal].codigo), stdin);
    
    setbuf(stdin, NULL);

    printf("\n\n(?)Qual eh o nome deste animal?\n-> ");
    fgets(animal[indiceSetor][indice_daJaula][indiceAnimal].nome, sizeof(animal[indiceSetor][numero_daJaula][indiceAnimal].nome), stdin);

    printf("\n\n(?) Qual eh o peso deste animal?\n-> ");
    scanf("%f", &animal[indiceSetor][indice_daJaula][indiceAnimal].peso);

    printf("\n\n(?) Qual eh a altura deste animal?\n-> ");
    scanf("%f", &animal[indiceSetor][indice_daJaula][indiceAnimal].altura);

    setbuf(stdin, NULL);

    printf("\n\n(?) Qual eh a especie deste animal?\n-> ");
    fgets(animal[indiceSetor][indice_daJaula][indiceAnimal].especie, sizeof(animal[indiceSetor][numero_daJaula][indiceAnimal].especie), stdin);

    m_qntdAnimal[indiceSetor][indice_daJaula] = indiceAnimal + 1;

    printf("\n\n(<->)ANIMAL CADASTRADO COM EXITO!");
}

// Funcao para adicionar setores
void addSetor(char ***a_Setores, int *a_numero_doSetores) {
    int qntdSetor = 0;
    printf("\n>> ADICIONAR SETOR: \n\nDeseja adicionar quantos setores? ");
    scanf("%d", &qntdSetor);

    *a_Setores = (char **)realloc(*a_Setores, ((*a_numero_doSetores) + qntdSetor) * sizeof(char *));
    if (*a_Setores == NULL) {
        exit(1);
    }

    // Nome dos novos setores
    for (int i = (*a_numero_doSetores); i < (*a_numero_doSetores) + qntdSetor; i++) {
        printf("\nQual o nome do %do setor?\n->", i + 1);
        setbuf(stdin, NULL);

        // Aloca memória para o nome do setor
        (*a_Setores)[i] = (char *)malloc(TAM * sizeof(char));
        if ((*a_Setores)[i] == NULL) {
            exit(1);
        }

        fgets((*a_Setores)[i], TAM, stdin);
    }

    *a_numero_doSetores += qntdSetor;
}

//Funcao para remover setores
// void removeSetor(char ***r_Setores, int *r_numero_doSetores) {
    
// }

int main() {
    Info_animal ***zoologico;
    char **setores;
    int numero_doSetores, numero_daJaulas, nAnimais, *p_numero_doSetores;
    int **qntdAnimais;
    p_numero_doSetores = &numero_doSetores;

    printf("\nDigite o numero de setores: ");
    scanf("%d",&numero_doSetores);

    printf("\nAgora, digite o numero de jaulas por setor: ");
    scanf("%d", &numero_daJaulas);

    printf("\nAgora, digite o numero de animais por jaula: ");
    scanf("%d", &nAnimais);

    zoologico = (Info_animal ***)malloc(numero_doSetores * sizeof(Info_animal **));
    setores = (char **)malloc(numero_doSetores * sizeof(char *));
    qntdAnimais = (int **)malloc(numero_doSetores * sizeof(int *));

    if(zoologico == NULL || setores == NULL || qntdAnimais == NULL){
        exit(1);
    }

    for(int setor = 0; setor < numero_doSetores; setor++) {
        zoologico[setor] = (Info_animal **)malloc(numero_daJaulas * sizeof(Info_animal *));
        setores[setor] = (char *)malloc(numero_daJaulas * sizeof(char));
        qntdAnimais[setor] = (int *)malloc(numero_daJaulas * sizeof(int));

        if(zoologico[setor] == NULL || setores[setor] == NULL || qntdAnimais[setor] == NULL){
            exit(1);
        }

        for(int jaula = 0; jaula < numero_daJaulas; jaula++) {
            zoologico[setor][jaula] = (Info_animal *)malloc(nAnimais * sizeof(Info_animal));

            if(zoologico[setor][jaula] == NULL){
                exit(1);
            }

            ///Zerar todas as posicoes
            for(int animal = 0; animal < nAnimais; animal++) qntdAnimais[setor][jaula] = 0;
        }
    }

    // // Preenchendo todas as posicoes com 0
    // for(int  i = 0; i < numero_doSetores; i++) {
    //     for(int j = 0; j < numero_daJaulas; j++) {
    //         zoologico[i][j] = 0;
    //     }
    // }

    cadSetor(setores, numero_doSetores);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);

    printf("\nChegou aqui");

    return 0;
}