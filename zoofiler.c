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
    printf("\n\t\t ==== (#) LISTAGEM DE SETORES ====");
    printf("\n\nID \t SETORES \n");

    for(int i = 0; i < n_SetoresView; i++) {
        printf("\n%d \t %s", i + 1, setorView[i]);
    }
}

// Funcao para mostrar os animais de uma jaula
void viewAnimais(Info_animal ***m_animal, int numero_doSetor, int numero_daJaula, int qntdAnimais, int qntd_MAX_Animais) {
    printf("\n\n\t\t==== (#) ANIMAIS REGISTRADOS NESSA JAULA ====\n\n#\t\tCOD.\t\tNOME\t\tALTURA(cm)\t\tPESO(Kg)\t\tESPECIE\n");

    // Verificar se numero_doSetor e numero_daJaula estão dentro dos limites
    if (qntdAnimais == 0) {
        printf("\n(!) Ainda nao ha animais cadastrados nessa jaula");
    } else {
        for (int animal = 0; animal < qntdAnimais; animal++) {
            // Variáveis para melhor organização
            char codigo[TAM];
            char nome[TAM];
            float altura;
            float peso;
            char especie[TAM];

            // Copiar os dados das strings
            strncpy(codigo, m_animal[numero_doSetor][numero_daJaula][animal].codigo, TAM - 1);
            codigo[TAM - 1] = '\0'; // Garantir que a string termina com '\0'

            strncpy(nome, m_animal[numero_doSetor][numero_daJaula][animal].nome, TAM - 1);
            nome[TAM - 1] = '\0';

            altura = m_animal[numero_doSetor][numero_daJaula][animal].altura;
            peso = m_animal[numero_doSetor][numero_daJaula][animal].peso;

            strncpy(especie, m_animal[numero_doSetor][numero_daJaula][animal].especie, TAM - 1);
            especie[TAM - 1] = '\0';

            // Remover a quebra de linha das strings
            size_t codigo_len = strlen(codigo);
            size_t nome_len = strlen(nome);
            size_t especie_len = strlen(especie);

            if (codigo_len > 0 && codigo[codigo_len - 1] == '\n') {
                codigo[codigo_len - 1] = '\0';
            }
            if (nome_len > 0 && nome[nome_len - 1] == '\n') {
                nome[nome_len - 1] = '\0';
            }
            if (especie_len > 0 && especie[especie_len - 1] == '\n') {
                especie[especie_len - 1] = '\0';
            }

            printf("\n%d\t\t%s\t\t%s\t\t%.2f\t\t\t\t%.2f\t\t%s", animal + 1, codigo, nome, altura, peso, especie);
        }


        if(qntdAnimais < qntd_MAX_Animais) {
            int restanteAnimais = qntd_MAX_Animais - qntdAnimais;
            printf("\n\n(%d %s)",restanteAnimais, (restanteAnimais == 1) ? "vaga disponivel" : "vagas disponiveis");
        } 
    }
}



// Funcao para cadastrar novos animais
void cadAnimal(Info_animal ***animal, char **matrizSetores, int qntdSetores, int **m_qntdAnimal, int qntdJaulas, int qntdAnimais) {
    char set[TAM], statusDisponibilidade[TAM];
    int numero_daJaula, indiceSetor = 0, indiceAnimal = 0;
    printf("\n\t\t==== (+) CADASTRAR UM NOVO ANIMAL ====\n\n");

    // Visualiza os setores ja cadastrados
    viewSetores(matrizSetores, qntdSetores);

    printf("\n\n(?) Em qual setor este animal se enquadra? (Digite exatamente o nome do setor correspondente)\n-> ");
    fgets(set, sizeof(set), stdin);

    
    // Verificar a disponibilidade das jaulas no setor correspondente
    //Recupera o indice do setor digitado
    for(int setor = 0; setor < qntdSetores; setor++) {
        if(strcmp(matrizSetores[setor], set) == 0) indiceSetor = setor;//indiceSetor = setor
    }

    // Remove a quebra de linha no final da palavra em 'set'
    for(int i = 0; set[i] != '\0'; i++) if(set[i] == '\n') set[i] = '\0';

    printf("\n\t\t=== (#) LISTA DE JAULAS DO SETOR '%s' ===\n\nID\t\tQUANTIDADE DE ANIMAIS\t\tDISPONIBILIDADE\n", set);
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
    viewAnimais(animal,indiceSetor,indice_daJaula,indiceAnimal, qntdAnimais);

    // Cadastro do animal no sistema
    printf("\n\n\t\t=== ADICIONAR INFORMACOES DO NOVO ANIMAL ===\n");

    setbuf(stdin, NULL);
    printf("\n(?) Qual eh o codigo deste animal?\n-> ");
    fgets(animal[indiceSetor][indice_daJaula][indiceAnimal].codigo, sizeof(animal[indiceSetor][numero_daJaula][indiceAnimal].codigo), stdin);
    
    setbuf(stdin, NULL);

    printf("\n\n(?) Qual eh o nome deste animal?\n-> ");
    fgets(animal[indiceSetor][indice_daJaula][indiceAnimal].nome, sizeof(animal[indiceSetor][numero_daJaula][indiceAnimal].nome), stdin);

    printf("\n\n(?) Qual eh o peso deste animal? (Em Kg)\n-> ");
    scanf("%f", &animal[indiceSetor][indice_daJaula][indiceAnimal].peso);

    printf("\n\n(?) Qual eh a altura deste animal? (Em cm)\n-> ");
    scanf("%f", &animal[indiceSetor][indice_daJaula][indiceAnimal].altura);

    setbuf(stdin, NULL);

    printf("\n\n(?) Qual eh a especie deste animal?\n-> ");
    fgets(animal[indiceSetor][indice_daJaula][indiceAnimal].especie, sizeof(animal[indiceSetor][numero_daJaula][indiceAnimal].especie), stdin);

    m_qntdAnimal[indiceSetor][indice_daJaula] = indiceAnimal + 1;

    printf("\n\n(<->)ANIMAL CADASTRADO COM EXITO!");
}

// Funcao para adicionar setores
void addSetor(char ***m_Setores, int *a_numero_doSetores, Info_animal ****m_Zoo, int nJaulas, int nAnimais, int ***qntdAnimais) {
    int qntdSetor = 0;
    printf("\n>> ADICIONAR SETOR: \n\nDeseja adicionar quantos setores? ");
    scanf("%d", &qntdSetor);

    // Realoca memória para os nomes dos setores
    *m_Setores = (char **)realloc(*m_Setores, ((*a_numero_doSetores) + qntdSetor) * sizeof(char *));
    if (*m_Setores == NULL) {
        exit(1);
    }

    // Realoca memória para as informações dos animais no zoo
    *m_Zoo = (Info_animal ***)realloc(*m_Zoo, ((*a_numero_doSetores) + qntdSetor) * sizeof(Info_animal **));
    if (*m_Zoo == NULL) {
        exit(1);
    }

    // Realoca memória para as informações da quantia de animais
    *qntdAnimais = (int **)realloc(*qntdAnimais, ((*a_numero_doSetores) + qntdSetor) * sizeof(int *));
    if (*qntdAnimais == NULL) {
        exit(1);
    }


    // Nome dos novos setores
    for (int i = (*a_numero_doSetores); i < (*a_numero_doSetores) + qntdSetor; i++) {
        printf("\nQual o nome do %do setor?\n-> ", i + 1);
        setbuf(stdin, NULL);

        // Aloca memória para o nome do setor
        (*m_Setores)[i] = (char *)malloc(TAM * sizeof(char));
        if ((*m_Setores)[i] == NULL) {
            exit(1);
        }

        fgets((*m_Setores)[i], TAM, stdin);

        // Aloca memória para as informações dos animais no setor
        (*m_Zoo)[i] = (Info_animal **)malloc(nJaulas * sizeof(Info_animal *));
        if ((*m_Zoo)[i] == NULL) {
            exit(1);
        }

        (*qntdAnimais)[i] = (int *)malloc(nJaulas * sizeof(int));
        if ((*qntdAnimais)[i] == NULL) {
            exit(1);
        }

        for (int j = 0; j < nJaulas; j++) {
            (*m_Zoo)[i][j] = (Info_animal *)malloc(nAnimais * sizeof(Info_animal));
            if ((*m_Zoo)[i][j] == NULL) {
                exit(1);
            }
        }
    }

    //Zerar as novas posicoes da matriz de quantidade "m_qntdAnimais"
    for(int setor = (*a_numero_doSetores); setor < ((*a_numero_doSetores) + qntdSetor); setor++) {
        for(int jaula = 0; jaula < nJaulas; jaula++) {
            (*qntdAnimais)[setor][jaula] = 0;
        }
    }

    *a_numero_doSetores += qntdSetor;
}


//Funcao para remover setores
void removeSetor(char ***m_Setores, int *a_numero_doSetores, Info_animal ****m_Zoo, int nJaulas, int ***qntdAnimais) {
    
    char select[TAM], nomeSetor_remove[TAM];
    int indiceSetor_remove;

    printf("\n\n\t\t===== (-) REMOVER UM SETOR =====\n\n(!) ESTEJA CIENTE DE QUE AO REMOVER UM SETOR, VOCE REMOVERA TODAS AS INFORMACOES CONTIDAS NELE.");
    printf("\n\n(?) Voce esta ciente disso?(S ou s para 'Sim' e qualquer digito para 'Nao')\n-> ");
    fgets(select, sizeof(select), stdin);

    if(tolower(select[0]) != 's') {
        printf("\nN digitado;");
        return; //Encerra a funcao
    }

    //Mostra os setores cadastrados
    viewSetores(*m_Setores, *a_numero_doSetores);

    printf("\n\n(?) Qual o nome do setor que deseja remover? (Digite o nome exato)\n-> ");
    fgets(nomeSetor_remove, sizeof(nomeSetor_remove), stdin);

    for(int setor = 0; setor < (*a_numero_doSetores); setor++) {
        if(strcmp(nomeSetor_remove, (*m_Setores)[setor]) == 0) {
            indiceSetor_remove = setor;
        }
    }

    //Remove o setor
    free((*m_Setores)[indiceSetor_remove]);
    free((*qntdAnimais)[indiceSetor_remove]);

    for (int jaula = 0; jaula < nJaulas; jaula++) {
        free((*m_Zoo)[indiceSetor_remove][jaula]);
    }
    free((*m_Zoo)[indiceSetor_remove]);

    // Realocar os arrays de setores e quantidades de animais para remover o setor
    for (int i = indiceSetor_remove; i < *a_numero_doSetores - 1; i++) {
        (*m_Setores)[i] = (*m_Setores)[i + 1];
        (*m_Zoo)[i] = (*m_Zoo)[i + 1];
        (*qntdAnimais)[i] = (*qntdAnimais)[i + 1];
    }


    (*a_numero_doSetores)--;

    printf("\n\n(<->) DEU CERTO! SETOR REMOVIDO PERMANENTEMENTE COM EXITO.");
}

int main() {
    Info_animal ***zoologico;
    char **setores;
    int numero_doSetores, numero_daJaulas, nAnimais, *p_numero_doSetores;
    int **qntdAnimais;
    p_numero_doSetores = &numero_doSetores;

    printf("\t\t\t\t===== ZOOFILER ===== \n\n\tBem vindo(a) ao ZOOFILER! Seu programa de gestao para zoologicos\n");
    printf("\n(!) Antes de tudo, precisamos cadastrar algumas informacoes a respeito do zoologico.\nPor favor, responda as isnttrucoes a seguir.");

    printf("\n\n(+) Digite o numero de setores: ");
    scanf("%d",&numero_doSetores);

    printf("\n(+) Agora, digite o numero de jaulas por setor: ");
    scanf("%d", &numero_daJaulas);

    printf("\n(+) Agora, digite o numero de animais por jaula: ");
    scanf("%d", &nAnimais);

    printf("\n\n(<->) So um instante, estamos salvando suas informacoes...");

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

            //Zerar todas as posicoes
            qntdAnimais[setor][jaula] = 0;
        }
    }

    printf("\n\n(<->) Deu certo!");

    cadSetor(setores, numero_doSetores);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    removeSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, &qntdAnimais);
    // cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    addSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, nAnimais, &qntdAnimais);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    removeSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, &qntdAnimais);
    cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);

    printf("\nChegou aqui");

    return 0;
}