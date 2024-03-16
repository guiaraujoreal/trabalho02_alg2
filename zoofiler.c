#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#define TAM 100
#define TAM_MIN 20

typedef struct {
    char codigo[TAM];
    char nome[TAM];
    float peso;
    float altura;
    char especie[TAM];
} Info_animal;

// *FUNCOES PARA EXIBIR CORES DE ACORDO COM O TIPO DA MENSAGEM

void alerta(char *msg) {
    printf("\n\n\033[1;33m%s\033[0m", msg);
}

void erro(char *msg) {
    printf("\n\n\033[1;31m%s\033[0m", msg);
}

void sucesso(char *msg) {
    printf("\n\n\033[1;32m%s\033[0m", msg);
}

void confirmacao(char *msg) {
    printf("\n\n\033[1;34m%s\033[0m", msg);
}

void destaque(char *msg) {
    printf("\n\n\033[1;36m%s\033[0m", msg);
}


// *FUNCOES DO PROGRAMA

// Funcao que verifica o maior peso por setor
void animal_maisPesado(char **matrizSetores, Info_animal ***matrizZoo, int qntdSetores, int qntdJaulas, int qntdAnimais) {
    printf("\n\n\t\t===== (#) ANIMAIS MAIS PESADOS POR SETOR =====");
    printf("\n\n#\t\tSETOR\t\tANIMAL\t\tPESO(Kg)");

    for(int setor = 0; setor < qntdSetores; setor++) {
        float maiorPeso = __FLT_MIN__;
        char nomeAnimal[TAM], nomeSetor[TAM];
        int nenhumAnimalEncontrado = 1; // Variável para indicar se nenhum animal foi encontrado no setor

        for(int jaula = 0; jaula < qntdJaulas; jaula++) {
            for(int animais = 0; animais < qntdAnimais; animais++) {
                if(matrizZoo[setor][jaula][animais].peso > maiorPeso) {
                    maiorPeso = matrizZoo[setor][jaula][animais].peso;

                    for(int i = 0; matrizZoo[setor][jaula][animais].nome[i] != '\0'; i++) {
                        if(matrizZoo[setor][jaula][animais].nome[i] == '\n') {
                            matrizZoo[setor][jaula][animais].nome[i] = '\0';
                        }
                    }
                    strcpy(nomeAnimal, matrizZoo[setor][jaula][animais].nome);
                    nenhumAnimalEncontrado = 0; // Se entramos neste bloco, significa que encontramos pelo menos um animal
                }
            }
        }

            // Verificar se nenhum animal foi encontrado no setor
            if(nenhumAnimalEncontrado) {
                strcpy(nomeAnimal, "Nenhum animal");
            }

            strcpy(nomeSetor, matrizSetores[setor]);

            for(int i = 0; nomeSetor[i] != '\0'; i++) {
                if(nomeSetor[i] == '\n') {
                    nomeSetor[i] = '\0';
                }
            }

        printf("\n\n%d\t\t%s\t\t%s\t\t%.2f", setor + 1, nomeSetor, nomeAnimal, maiorPeso);
    }

}


// Funcao para cadastrar os setores
void cadSetor(char **c_Setores, int f_numero_doSetores) {
    confirmacao("\n\n\t\t=== (+) CADASTRAR SETORES PELA PRIMEIRA VEZ ===\n");
    alerta("(!) NAO EH PERMITIDO NUMEROS, CARACTERES ESPECIAIS OU NOMES DE SETORES JA CADASTRADOS");
    alerta("(!) CUIDADO PARA NAO ADICIONAR ESPACOS EXTRAS AO FIM DA LINHA. ISSO PODE INTERFERIR NA BUSCA DOS SETORES\n");
    
    for(int i = 0; i < f_numero_doSetores; i++) {
        printf("\n(#) Nome do %do setor: ", i + 1);
        // scanf(" %[^\n]", c_Setores[i]); // Usamos %[^\n] para capturar toda a linha até a quebra de linha
        
        // // Verificar se o nome do setor contém apenas letras e não está vazio
        // int j = 0;
        // while (c_Setores[i][j] != '\0') {
        //     if (!isalpha(c_Setores[i][j])) {
        //         alerta("(!) NOME INVALIDO. NAO EH PERMITIDO ESPACOS EM BRANCO, NUMEROS OU SIMBOLOS\n");
        //         printf("\n(#) Nome do %do setor: ", i + 1);
        //         scanf(" %[^\n]", c_Setores[i]);
        //         j = -1; // Reiniciamos a verificação
        //     }
        //     j++;
        // }

        do {
            int condicaoOk = 1; // Flag da condicao se der tudo certo

            setbuf(stdin, NULL);
            fgets(c_Setores[i], TAM, stdin);

            // Remove o caractere de nova linha, se houver
            if(c_Setores[i][strlen(c_Setores[i]) - 1] == '\n') {
                c_Setores[i][strlen(c_Setores[i]) - 1] = '\0';
            }

            if(c_Setores[i][0] == ' ' || c_Setores[i][0] == '\0') {
                erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO NOME DO SETOR. DIGITE UM NOME VALIDO!");
                printf("\n\n-> ");
                continue;
            }

            // Verifica se tem um numero no nome
            for(int k = 0; c_Setores[i][k] != '\0'; k++) {
                if(isdigit(c_Setores[i][k])) {
                    erro("(x) NAO EH PERMITIDO NUMEROS NO NOME. ESCREVA UM NOME VALIDO!");
                    printf("\n\n-> ");
                    condicaoOk = 0;
                    break;
                }
            }

            if(condicaoOk) break;

        } while(1);

        //Verificar se esse nome ja foi cadastrado
        for(int p = 0; p < i; p++) {
            if(strcmp(c_Setores[i], c_Setores[p]) == 0) {
                alerta("(!) VOCE JA INSERIU ESTE NOME. TENTE OUTRO.\n");
                i--;
                break;
            }
        }
    }

    sucesso("\n(<->) SETORES CADASTRADOS COM SUCESSO!");
}


//Funcao para mostrar setores
void viewSetores(char **setorView, int n_SetoresView) {
    confirmacao("\t\t ==== (#) LISTAGEM DE SETORES ====");
    printf("\n\n# \t SETORES \n");

    for(int i = 0; i < n_SetoresView; i++) {
        printf("\n%d \t %s", i + 1, setorView[i]);
    }
}

// Visualiza as jaulas daquele setor
void viewJaulas(int **m_qntdAnimal,int qntdJaulas, int indiceSetor, int qntdAnimais) {
    confirmacao("\n\t\t=== (#) LISTA DE JAULAS DESTE SETOR ===");
    printf("\n\t\t\n\nID\t\tQUANTIDADE DE ANIMAIS\t\tDISPONIBILIDADE\n");
    char statusDisponibilidade[TAM];

    for(int jaula = 0; jaula < qntdJaulas; jaula++) {

        if(m_qntdAnimal[indiceSetor][jaula] >= qntdAnimais) strcpy(statusDisponibilidade,"Indisponivel");
        else strcpy(statusDisponibilidade, "Disponivel");

        printf("\n%d\t\t\t%d\t\t\t%s", jaula + 1, m_qntdAnimal[indiceSetor][jaula], statusDisponibilidade);
    }
}

// Funcao para mostrar os animais de uma jaula
void viewAnimais(Info_animal ***m_animal, int numero_doSetor, int numero_daJaula, int qntdAnimais, int qntd_MAX_Animais) {
    confirmacao("\t\t==== (#) ANIMAIS REGISTRADOS NESSA JAULA ====");
    printf("\n\n\n\n#\t\tCOD.\t\tNOME\t\tALTURA(cm)\tPESO(Kg)\t\t\tESPECIE\n");

    // Verificar se numero_doSetor e numero_daJaula estão dentro dos limites
    if (qntdAnimais == 0) {
        alerta("(!) Ainda nao ha animais cadastrados nessa jaula");
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
            printf("\n\n(\033[1;33m%d %s\033[0m)",restanteAnimais, (restanteAnimais == 1) ? "vaga disponivel" : "vagas disponiveis"); // 033 coloca a cor amarela na saida
        } 
    }
}



// Funcao para cadastrar novos animais
void cadAnimal(Info_animal ***animal, char **matrizSetores, int qntdSetores, int **m_qntdAnimal, int qntdJaulas, int qntdAnimais) {
    char set[TAM];
    int numero_daJaula, indiceSetor = 0, indiceAnimal = 0, setorEncontrado = 0;
    confirmacao("\n\t\t==== (+) CADASTRAR UM NOVO ANIMAL ====\n\n");

    // Visualiza os setores ja cadastrados
    viewSetores(matrizSetores, qntdSetores);

    printf("\n\n(?) Em qual setor este animal se enquadra? (Digite exatamente o nome do setor correspondente)\n-> ");

    do {
        setbuf(stdin, NULL);
        fgets(set, sizeof(set), stdin);

        //Recupera o indice do setor digitado
        for(int setor = 0; setor < qntdSetores; setor++) {

            // // Remove a quebra de linha
            // for(int i = 0; set[i] != '\0'; i++) {
            //     if(set[i] == '\n') {
            //         set[i] = '\0';
            //     }
            // }

            if(set[strlen(set) - 1] == '\n') {
                set[strlen(set) - 1] = '\0';
            }

            if(strcmp(matrizSetores[setor], set) == 0) {
                indiceSetor = setor;
                setorEncontrado = 1;
                break;
            }
        }

        // Verifica se o setor digitado existe
        if(setorEncontrado == 0) {
            erro("(x) OOPS! SETOR NAO ENCONTRADO. TENTE NOVAMENTE.");
            printf("\n\n-> ");
        }


    } while(setorEncontrado == 0);

    printf("\n\033[1;32m(<->) Setor selecionado exito.\033[0m"); // O \033 deixa a confirmacao verde


    viewJaulas(m_qntdAnimal, qntdJaulas, indiceSetor, qntdAnimais);

    printf("\n\n(?) Em qual jaula este animal permanecera? (Digite a ID)\n-> ");

    char input[TAM];

    do {
        scanf("%s", input);

        // Verificar se a entrada contém apenas dígitos
        int i = 0;
        while (input[i] != '\0') {
            if (!isdigit(input[i])) {
                break;
            }
            i++;
        }

        // Se o loop terminou e input[i] eh '\0', então todos os caracteres são dígitos
        if (input[i] == '\0') {
            numero_daJaula = atoi(input); // Converter a string para um número inteiro
            if (numero_daJaula <= 0 || numero_daJaula > qntdJaulas) {
                erro("(x) VOCE DIGITOU UM NUMERO INVALIDO OU ACIMA DA QUANTIDADE DE JAULAS. TENTE NOVAMENTE!\n\n");
                printf("\n\n-> ");
            }
        } else {
            erro("(x) VOCE DIGITOU UM CARACTERE INVALIDO. TENTE NOVAMENTE!\n\n");
            printf("\n\n-> ");
        }
    } while (numero_daJaula <= 0 || numero_daJaula > qntdJaulas);

    int indice_daJaula = numero_daJaula - 1;

    indiceAnimal = m_qntdAnimal[indiceSetor][indice_daJaula];

    printf("\n\033[1;32m(<->) Jaula %d selecionada.\033[0m", numero_daJaula); // O \033 deixa a confirmacao verde

    //Mostra os animais ja cadastrado na jaula
    viewAnimais(animal,indiceSetor,indice_daJaula,indiceAnimal, qntdAnimais);

    // Cadastro do animal no sistema
    printf("\n\n\t\t=== ADICIONAR INFORMACOES DO NOVO ANIMAL ===\n");

    // Alem da criacao das variaveis char para a estrutura, criamos todas char para verificar os casos de erro.
    // As vezes, pode haver uma letra no lugar de um numero, entao verificamos usando o char.
    char codigo[TAM], nome[TAM], altura[TAM], peso[TAM], especie[TAM];

    setbuf(stdin, NULL);
    printf("\n(?) Qual eh o codigo deste animal?");

    alerta("(!) EH PERMITIDO LETRAS E NUMEROS NO CODIGO. O CODIGO EH UNICO E EXCLUSIVO PARA CADA ANIMAL.");
    printf("\n-> ");

    // Remove o caractere de nova linha, se houver
        if(codigo[strlen(codigo) - 1] == '\n') {
            codigo[strlen(codigo) - 1] = '\0';
        }


    // Casos de erro para codigo
    do {
        int condicaoOk = 1; // Flag da condicao se der tudo certo
        int codigoExistente = 0; // Flag que verifica se o codigo ja existe

        setbuf(stdin, NULL);
        fgets(codigo, sizeof(codigo), stdin);

        if(codigo[0] == ' ' || codigo[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO CODIGO. DIGITE UM CODIGO VALIDO!");
            printf("\n\n-> ");
            condicaoOk = 0;
        }


        if(condicaoOk) {
            // Verifica se esse codigo ja pertence a outro animal
            for(int setor = 0; setor <  qntdSetores; setor++) {
                for(int jaula = 0; jaula <  qntdJaulas; jaula++) {
                    for(int animais = 0; animais < qntdAnimais; animais++) {
                        if(strcmp(animal[setor][jaula][animais].codigo, codigo) == 0) {
                            codigoExistente = 1;
                            break;
                        }
                    }
                }
            }

            if(codigoExistente) {
                erro("(x) ESTE CODIGO JA EXISTE. DIGITE UM NOVO!");
                printf("\n\n-> ");
                continue;
            } 

            strcpy(animal[indiceSetor][indice_daJaula][indiceAnimal].codigo, codigo);
            break;
        }

    } while(1);


    setbuf(stdin, NULL);

    printf("\n\n(?) Qual eh o nome deste animal?\n-> ");

    // Casos de erro para nome
    do {
        int condicaoOk = 1; // Flag da condicao se der tudo certo

        setbuf(stdin, NULL);
        fgets(nome, sizeof(nome), stdin);

        // Remove o caractere de nova linha, se houver
        if(nome[strlen(nome) - 1] == '\n') {
            nome[strlen(nome) - 1] = '\0';
        }

        if(nome[0] == ' ' || nome[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO NOME. DIGITE UM NOME VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se tem um numero no nome
        for(int i = 0; nome[i] != '\0'; i++) {
            if(isdigit(nome[i])) {
                erro("(x) NAO EH PERMITIDO NUMEROS NO NOME. ESCREVA UM NOME VALIDO!");
                printf("\n\n-> ");
                condicaoOk = 0;
                break;
            }
        }

        if(condicaoOk) {
            strcpy(animal[indiceSetor][indice_daJaula][indiceAnimal].nome, nome);
            break;
        }

    } while(1);

    printf("\n\n(?) Qual eh o peso deste animal? (Em Kg)\n-> ");

    // Casos de erro para peso
    do {
        int condicaoOk = 1; // Flag da condicao se der tudo certo
        int pontoDecimal = 0; // A entrada pode haver o '.', em casos de valores decimais. Vamos incluir na condicao para que seja aceito

        setbuf(stdin, NULL);
        fgets(peso, sizeof(peso), stdin);

        // Remove o caractere de nova linha, se houver
        if(peso[strlen(peso) - 1] == '\n') {
            peso[strlen(peso) - 1] = '\0';
        }

        // Verifica se ha espacos ou linha vazia
        if(peso[0] == ' ' || peso[0] == '\0' || peso[0] == '.') {
            erro("(x) NAO EH PERMITIDO RESPOSTAS EM BRANCO, COM ESPACOS INICIAIS OU PONTO UNICO. DIGITE UM PESO VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se eh uma letra
        for (int i = 0; peso[i] != '\0'; i++) {
            if (!isdigit(peso[i])) {
                if (peso[i] == '.' && !pontoDecimal) {
                    // Se encontrou um ponto decimal
                    pontoDecimal = 1;
                } else {
                    // Outro caractere que nao eh digito ou mais de um ponto decimal
                    printf("(x) DIGITE UM VALOR NUMERICO VALIDO!\n\n");
                    condicaoOk = 0;
                    break;
                }
            }
        }

        if(condicaoOk) {
            animal[indiceSetor][indice_daJaula][indiceAnimal].peso = atof(peso); // Converte de string para float
            break;
        }

    } while(1);

    printf("\n\n(?) Qual eh a altura deste animal? (Em cm)\n-> ");
    
    //Casos de erro para altura
    do {
        int condicaoOk = 1; // Flag da condicao se der tudo certo
        int pontoDecimal = 0; // A entrada pode haver o '.', em casos de valores decimais. Vamos incluir na condicao para que seja aceito

        setbuf(stdin, NULL);
        fgets(altura, sizeof(altura), stdin);

        // Remove o caractere de nova linha, se houver
        if (altura[strlen(altura) - 1] == '\n') {
            altura[strlen(altura) - 1] = '\0';
        }

        // Verifica se ha espacos ou linha vazia
        if(altura[0] == ' ' || altura[0] == '\0' || altura[0] == '.') {
            erro("(x) NAO EH PERMITIDO RESPOSTAS EM BRANCO, COM ESPACOS INICIAIS OU PONTO UNICO. DIGITE UMA ALTURA VALIDA!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se ha uma letra
        for (int i = 0; altura[i] != '\0'; i++) {
            if (!isdigit(altura[i])) {
                if (altura[i] == '.' && !pontoDecimal) {
                    // Se encontrou um ponto decimal
                    pontoDecimal = 1;
                } else {
                    // Outro caractere que nao eh digito ou mais de um ponto decimal
                    erro("(x) DIGITE UM VALOR NUMERICO VALIDO!\n\n");
                    condicaoOk = 0;
                    break;
                }
            }
        }

        if(condicaoOk) {
            animal[indiceSetor][indice_daJaula][indiceAnimal].altura = atof(altura);
            break;
        }
        
    } while(1);

    setbuf(stdin, NULL);

    printf("\n\n(?) Qual eh a especie deste animal?\n-> ");

    // Casos de erro para especie
    do {
        int condicaoOk = 1; // Flag da condicao se der tudo certo

        setbuf(stdin, NULL);
        fgets(especie, sizeof(especie), stdin);

        // Remove o caractere de nova linha, se houver
        if (especie[strlen(especie) - 1] == '\n') {
            especie[strlen(especie) - 1] = '\0';
        }

        if(especie[0] == ' ' || especie[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DA ESPECIE. DIGITE UMA ESPECIE VALIDA!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se tem um numero no nome
        for(int i = 0; especie[i] != '\0'; i++) {
            if(isdigit(especie[i])) {
                erro("(x) NAO EH PERMITIDO NUMEROS NA ESPECIE. ESCREVA UMA ESPECIE VALIDA!");
                printf("\n\n-> ");
                condicaoOk = 0;
                break;
            }
        }

        if(condicaoOk) {
            strcpy(animal[indiceSetor][indice_daJaula][indiceAnimal].especie, especie);
            break;
        }

    } while(1);

    m_qntdAnimal[indiceSetor][indice_daJaula] = indiceAnimal + 1;

    sucesso("(<->)ANIMAL CADASTRADO COM EXITO!");
}

// Funcao para adicionar setores
void addSetor(char ***m_Setores, int *a_numero_doSetores, Info_animal ****m_Zoo, int nJaulas, int nAnimais, int ***qntdAnimais) {
    int qntdSetor = 0;
    printf("\n\n\t\t\t===== (+) ADICIONAR SETOR ===== \n\nDeseja adicionar quantos setores? ");
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
void removeSetor(char ***m_Setores, int *a_numero_doSetores, Info_animal ****m_Zoo, int ***qntdAnimais, int *p_setorCadastrado_Ok) {
    
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

    // Realocar memória para reduzir o tamanho dos arrays em uma unidade
    *m_Setores = realloc(*m_Setores, (*a_numero_doSetores - 1) * sizeof(char *));
    *m_Zoo = realloc(*m_Zoo, (*a_numero_doSetores - 1) * sizeof(Info_animal **));
    *qntdAnimais = realloc(*qntdAnimais, (*a_numero_doSetores - 1) * sizeof(int *));

    // Mover os elementos restantes para preencher o espaço do setor removido
    for (int i = indiceSetor_remove; i < *a_numero_doSetores - 1; i++) {
        (*m_Setores)[i] = (*m_Setores)[i + 1];
        (*m_Zoo)[i] = (*m_Zoo)[i + 1];
        (*qntdAnimais)[i] = (*qntdAnimais)[i + 1];
    }



    (*a_numero_doSetores)--;

    if(*a_numero_doSetores == 0) *p_setorCadastrado_Ok = 0;

    printf("\n\n(<->) DEU CERTO! SETOR REMOVIDO PERMANENTEMENTE COM EXITO.");
}

// *NOVA FUNCAO - Esta funcao permite editar as informacoes do animal 
int editAnimal(Info_animal ****mZoo, char **matrizSetores, int numeroSetores, int qntdAnimais, int **matriz_qntdAnimais, int numeroJaulas) {
    int numeroAnimal = -1; // O -1 eh apenas um valor diferente de zero para verificar o retorno da funcao
    char codAnimal[TAM];
    char nomeSetor[TAM];
    int indiceSetor = -1, nJaula, indiceJaula, indiceAnimal;

    printf("\n\n\t\t\t===== (@) EDITAR INFORMACOES DE UM ANIMAL =====\n");

    viewSetores(matrizSetores, numeroSetores);

    do {
        printf("\n\n(?) Em que setor esta este animal? \n-> ");
        fgets(nomeSetor, sizeof(nomeSetor), stdin);

        // Retorna o indice do setor, se achar
        for(int setor = 0; setor < numeroSetores; setor++) {
            if(strcmp(nomeSetor, matrizSetores[setor]) == 0) {
                indiceSetor = setor;
            }
        
        }

        if(indiceSetor == -1) {
            printf("\n\n(!) SETOR NAO ENCONTRADO. DIGITE NOVAMENTE OU DIGITE 'E' PARA SAIR");
        }

    } while(indiceSetor == -1);

    viewJaulas(matriz_qntdAnimais, numeroJaulas, indiceSetor, qntdAnimais);

    printf("\n\n(?) Em que jaula este animal habita?\n-> ");
    scanf("%d", &nJaula);

    indiceJaula = nJaula - 1;

    indiceAnimal = matriz_qntdAnimais[indiceSetor][indiceJaula];

    viewAnimais(*mZoo,indiceSetor,indiceJaula,indiceAnimal, qntdAnimais);

    getchar();

    printf("\n\n(?) Qual o codigo do animal que voce editar as informacoes?\n-> ");
    fgets(codAnimal, sizeof(codAnimal), stdin);

    // Confere se o codigo digitado esta registrado e dá retorno mediante a busca
    for(int n = 0; n < qntdAnimais; n++) {
        if(strcmp(codAnimal,(*mZoo)[indiceSetor][indiceJaula][n].codigo) == 0) numeroAnimal = n;
    }

    /// Se nenhum registro foi encontrado
    if(numeroAnimal == -1) return 0;

    printf("\n\n(#) ESTAS SAO AS INFORMACOES SALVAS DESTE ANIMAL: \n\nCOD.\t\tNOME\t\tPESO(Kg)\t\tALTURA(cm)\t\tESPECIE");

    // Variaveis para o printf ficar organizado
    char codigo[TAM];
    char nome[TAM];
    char especie[TAM];
    float peso = (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].peso;
    float altura = (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].altura;
    strcpy(codigo, (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].codigo);
    strcpy(nome, (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].nome);
    strcpy(especie, (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].especie);

    printf("\n\n%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s", codigo, nome, peso, altura, especie);

    char opcao[TAM_MIN];
    
    printf("\n\n(#) ESCOLHA O QUE VOCE DESEJA EDITAR. EH ACEITO APENAS UMA EDICAO POR VEZ");
    printf("\n\n(A) CODIGO\n(B) NOME\n(C) PESO\n(D) ALTURA\n(E) ESPECIE\n(F) FECHAR MENU DE EDICAO\n\n-> ");

    fgets(opcao, sizeof(opcao), stdin);

    char novoCodigo[TAM];
    char novoNome[TAM];
    float novoPeso;
    float novaAltura;
    char novaEspecie[TAM];


    switch(tolower(opcao[0])) {
        case 'a':
            printf("\n\n(?) Qual o novo codigo do animal?\n-> ");
            fgets(novoCodigo, sizeof(novoCodigo), stdin);

            strcpy((*mZoo)[indiceSetor][indiceJaula][numeroAnimal].codigo, novoCodigo);
            break;

        case 'b':
            printf("\n\n(?) Qual o novo nome do animal?\n-> ");
            fgets(novoNome, sizeof(novoNome), stdin);

            strcpy((*mZoo)[indiceSetor][indiceJaula][numeroAnimal].nome, novoNome);
            break;
        
        case 'c':
            printf("\n\n(?) Qual o novo peso do animal?\n-> ");
            scanf("%f", &novoPeso);

            (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].peso = novoPeso;
            break;
        
        case 'd':
            printf("\n\n(?) Qual a nova altura do animal?\n-> ");
            scanf("%f", &novaAltura);

            (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].altura = novaAltura;
            break;
        
        case 'e':
            printf("\n\n(?) Edite a especie?\n-> ");
            fgets(novaEspecie, sizeof(novaEspecie), stdin);

            strcpy((*mZoo)[indiceSetor][indiceJaula][numeroAnimal].especie, novaEspecie);
            break;

        default:
            printf("\n\nErro");
    }

    return 1;

}


// Mostra o menu conforme a acao executada ou aviso dado
void viewMenu(char textMenu_A[TAM]) {
    printf("\n\n\n\t\t===== MENU DE OPCOES ====");

    // A variavel textMenu_A altera o texto do menu A caso o user ja cadastrou um setor pela 1a vez ou nao
    printf("\n\n\n(A) %s\t\t(B) REMOVER UM SETOR\n\n(C) CADASTRAR UM NOVO ANIMAL\t\t(D) EDITAR INFO. DO ANIMAL", textMenu_A);
    printf("\n\n(E) ANIMAL MAIS PESADO P/ SETOR\n\n(F) LISTA DE SETORES");
}


int main() {
    Info_animal ***zoologico;
    char **setores;
    int numero_doSetores, numero_daJaulas, nAnimais, *p_numero_doSetores;
    int **qntdAnimais;
    p_numero_doSetores = &numero_doSetores;

    // Determina local para usos de acentos e simbolos
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Variaveis de mudanca de estado (global)  - (certificam que algumas mudancas so podem ser realizadas mediante outras)
    int setorCadastrado_ok = 0;
    int *p_setorCadastrado_Ok = &setorCadastrado_ok;
    int showMenu = 0;
    int animalCadastrado_Ok = 0;
    int *p_animalCadastrado_ok = &animalCadastrado_Ok;
    int primeiroCadastro_Setor_Ok = 0;

    destaque("\t\t\t\t===== ZOOFILER =====");

    printf("\n\n\tBem vindo(a) ao ZOOFILER! Seu programa de gestao para zoologicos\n");
    printf("\n(!) Antes de tudo, precisamos cadastrar algumas informacoes a respeito do zoologico.\nPor favor, responda as instrucoes a seguir.");

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

     printf("\n\n(<->) DEU CERTO! INFORMACOES INICIAIS CONSIDERADAS");

    // Loop para manter programa em funcionamento
    while(1) {
        char opcaoMenu[TAM_MIN];

        // Variaveis de mudanca de estado (interno)  - (certificam que algumas mudancas so podem ser realizadas mediante outras)
        int menuOk = 0; // Verifica no fim do loop se alguma caractere condiz com algum menu abaixo. Se n condiz, continua 0.

        // *MENU DE OPCOES

        // *Verifica se o user ja cadastrou pelo menos 1 setor pela primeira vez (altera o txt do menu A)
        //Tambem mostra o menu de acordo com a acao executada (altera o valor de 'showMenu' para 0. Se for 0, o menu aparece)
        if(showMenu == 0) {
            if(setorCadastrado_ok == 0) viewMenu("\033[1;33m[!] CADASTRE OS PRIMEIROS SETORES\033[0m");
            else viewMenu("CADASTRAR NOVO(S) SETOR(ES)");
        }

        showMenu = 0;

        printf("\n\n\n(#) Digite uma opcao somente dentre os menus acima\n-> ");
        setbuf(stdin,NULL);
        fgets(opcaoMenu, sizeof(opcaoMenu), stdin);


        // Cadastrar um novo setor
        if(tolower(opcaoMenu[0]) == 'a') {
            menuOk = 1;

            if(primeiroCadastro_Setor_Ok == 0) {
                cadSetor(setores, numero_doSetores);
                primeiroCadastro_Setor_Ok = 1;
            } else addSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, nAnimais, &qntdAnimais);

            setorCadastrado_ok = 1;
            showMenu = 0;
        }

        // Remover um setor
        if(tolower(opcaoMenu[0]) == 'b') {
            menuOk = 1;

            if(setorCadastrado_ok == 0) {
                printf("\n\n(!) ACAO NEGADA - < NAO E POSSIVEL REMOVER UM SETOR SEM ANTES CADASTRAR UM >");
                showMenu = 1;
            }
            else {
                removeSetor(&setores, p_numero_doSetores, &zoologico, &qntdAnimais, p_setorCadastrado_Ok);
                showMenu = 0;
            }
        }

        // Cadastrar um novo animal
        if(tolower(opcaoMenu[0]) == 'c') {
            menuOk = 1;

            cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
            animalCadastrado_Ok = 1;
            showMenu = 0;
        }

        // Editar informacoes do animal
        if(tolower(opcaoMenu[0]) == 'd') {
            menuOk = 1;

            if(animalCadastrado_Ok == 0) {
                printf("\n\n(!) ACAO NEGADA - < NAO E POSSIVEL REMOVER UM SETOR SEM ANTES CADASTRAR UM >");
                showMenu = 1;
            }
            else {

                editAnimal(&zoologico, setores, numero_doSetores, nAnimais, qntdAnimais, numero_daJaulas);
            }
        }

        // Animal mais pesado por setor
        if(tolower(opcaoMenu[0]) == 'e') {
            menuOk = 1;
            animal_maisPesado(setores, zoologico, numero_doSetores, numero_daJaulas, nAnimais);
        }

        if(tolower(opcaoMenu[0]) == 'f') {
            menuOk = 1;
            viewSetores(setores, numero_doSetores);
        }

        

        // Se o caractere digitado nao entrou em nenhum menu
        if(menuOk == 0) {
            printf("\n\n\n(!) VOCE DIGITOU UM CARACTERE INVALIDO OU FORA DOS PARAMETROS.");
            showMenu = 1;
        }
    }

    

    // cadSetor(setores, numero_doSetores);
    // cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    // cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    // editAnimal(&zoologico, 1, 2, "123", nAnimais);
    // removeSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, &qntdAnimais);
    // // cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    // addSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, nAnimais, &qntdAnimais);
    // cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
    // removeSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, &qntdAnimais);
    // cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);

    printf("\nChegou aqui");

    return 0;
}