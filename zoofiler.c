#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <limits.h>
#include <unistd.h>

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

            //printf("\n%d\t\t%s\t\t%s\t\t%.2f\t\t\t%.2f\t\t%s", animal + 1, codigo, nome, altura, peso, especie);

            printf("\n\n\033[1;34m%d\033[0m", animal + 1);
            printf("\n\t\033[1;34mCOD. ->\033[0m"); printf(" %s", codigo);
            printf("\n\t\033[1;34mNOME ->\033[0m"); printf(" %s", nome);
            printf("\n\t\033[1;34mALTURA ->\033[0m"); printf(" %.2f cm", altura);
            printf("\n\t\033[1;34mPESO ->\033[0m"); printf(" %.2f kg", peso);
            printf("\n\t\033[1;34mESPECIE ->\033[0m"); printf(" %s", especie);
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

    printf("\n\033[1;32m(<->) Setor selecionado com exito.\033[0m"); // O \033 deixa a confirmacao verde


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
                    erro("(x) DIGITE UM VALOR NUMERICO VALIDO!\n\n");
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
    char entradaSetor[TAM]; // Capturamos a entrada da quantia de setor como char para verificar se uma letra ou caractere foi digitado no lugar de um int

    confirmacao("\n\t\t\t===== (+) ADICIONAR SETOR ===== ");
    alerta("(!) LEMBRE-SE QUE O NOME DO SETOR EH UNICO E NAO PODE SER REPETIDO.\n");
    printf("\n\n(?) Deseja adicionar quantos setores? ");

    // Casos de erro para qntdSetor
    do {
        int situacaoOk = 1; // Flag q verifica a situacao dos casos de erro

        setbuf(stdin, NULL);

        fgets(entradaSetor, sizeof(entradaSetor), stdin);

        // Remove quebra de linha
        if(entradaSetor[strlen(entradaSetor) - 1] == '\n') {
            entradaSetor[strlen(entradaSetor) - 1] = '\0';
        }

        // Evita espacos vazios
        if(entradaSetor[0] == ' ' || entradaSetor[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU LINHAS VAZIAS. DIGITE UM VALOR VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se a entrada eh um numero
        for(int i = 0; entradaSetor[i] != '\0'; i++){
            if(!isdigit(entradaSetor[i])) {
                situacaoOk = 0;
                break;
            }
        }
        

        if(!situacaoOk) {
            erro("(x) VOCE DIGITOU UM VALOR INVALIDO. TENTE NOVAMENTE!");
            printf("\n\n-> ");
            continue;
        }

        qntdSetor = atoi(entradaSetor);

        if(qntdSetor <= 0) {
            alerta("(!) ADICIONE PELO MENOS 1 SETOR! (OU DIGITE 'X' PARA SAIR)");
            printf("\n\n-> ");
            continue;
        } else break;

    } while(1);


    // Realoca memória para os nomes dos setores
    *m_Setores = (char **)realloc(*m_Setores, ((*a_numero_doSetores) + qntdSetor) * sizeof(char *));
    if (*m_Setores == NULL) {
        erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
        sleep(3);
        exit(1);
    }

    // Realoca memória para as informações dos animais no zoo
    *m_Zoo = (Info_animal ***)realloc(*m_Zoo, ((*a_numero_doSetores) + qntdSetor) * sizeof(Info_animal **));
    if (*m_Zoo == NULL) {
        erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
        sleep(3);
        exit(1);
    }

    // Realoca memória para as informações da quantia de animais
    *qntdAnimais = (int **)realloc(*qntdAnimais, ((*a_numero_doSetores) + qntdSetor) * sizeof(int *));
    if (*qntdAnimais == NULL) {
        erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
        sleep(3);
        exit(1);
    }


    // Nome dos novos setores
    for (int i = (*a_numero_doSetores); i < (*a_numero_doSetores) + qntdSetor; i++) {
        printf("\n(?) Qual o nome do %do setor?\n-> ", i + 1);
        setbuf(stdin, NULL);

        // Aloca memória para o nome do setor
        (*m_Setores)[i] = (char *)malloc(TAM * sizeof(char));
        if ((*m_Setores)[i] == NULL) {
            erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
            sleep(3);
            exit(1);
        }

        // Casos de erro para o nome do setor
        do {
            int condicaoOk = 1; // Flag da condicao se der tudo certo
            int setorEncontrado = 0; // Flag que verifica se o setor digitado foi encontrado

            setbuf(stdin, NULL);
            fgets((*m_Setores)[i], TAM, stdin);

            // Remove o caractere de nova linha, se houver
            for(int z = 0;  (*m_Setores)[i][z] != '\0'; z++) {
                if((*m_Setores)[i][z] == '\n') {
                    (*m_Setores)[i][z] = '\0';
                }
            }

            if((*m_Setores)[i][0] == ' ' || (*m_Setores)[i][0] == '\0') {
                erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO NOME DO SETOR. DIGITE UM NOME VALIDO!");
                printf("\n\n-> ");
                continue;
            }



            // Verifica se tem um numero no nome
            for(int y = 0; (*m_Setores)[i][y] != '\0'; y++) {
                if(isdigit((*m_Setores)[i][y])) {
                    erro("(x) NAO EH PERMITIDO NUMEROS NO NOME. ESCREVA UM NOME VALIDO!");
                    printf("\n\n-> ");
                    condicaoOk = 0;
                    break;
                }
            }

            if(condicaoOk) {
                for(int setor = 0; setor < *(a_numero_doSetores); setor++) {
                    if(strcmp((*m_Setores)[i], *(m_Setores)[setor]) == 0) {
                        setorEncontrado = 1;
                        break;
                    }
                }

                if(setorEncontrado) {
                    erro("(x) JA EXISTE UM SETOR COM ESTE NOME. TENTE OUTRO.");
                    printf("\n\n-> ");
                    continue;
                }

                break;
            }

        } while(1);

        // Aloca memória para as informações dos animais no setor
        (*m_Zoo)[i] = (Info_animal **)malloc(nJaulas * sizeof(Info_animal *));
        if ((*m_Zoo)[i] == NULL) {
            erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
            sleep(3);
            exit(1);
        }

        (*qntdAnimais)[i] = (int *)malloc(nJaulas * sizeof(int));
        if ((*qntdAnimais)[i] == NULL) {
            erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
            sleep(3);
            exit(1);
        }

        for (int j = 0; j < nJaulas; j++) {
            (*m_Zoo)[i][j] = (Info_animal *)malloc(nAnimais * sizeof(Info_animal));
            if ((*m_Zoo)[i][j] == NULL) {
                erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
                sleep(3);
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
void removeSetor(char ***m_Setores, int *a_numero_doSetores, Info_animal ****m_Zoo, int ***qntdAnimais, int *p_setorCadastrado_Ok, int *p_animalCadastrado_ok) {
    
    char select[TAM], nomeSetor_remove[TAM];
    int indiceSetor_remove;

    erro("\n\t\t===== (-) REMOVER UM SETOR =====\n\n");
    alerta("\n(!) ESTEJA CIENTE DE QUE AO REMOVER UM SETOR, VOCE REMOVERA TODAS AS INFORMACOES CONTIDAS NELE.");
    printf("\n\n(?) Voce esta ciente disso?(S ou s para 'Sim' e qualquer digito para 'Nao')\n-> ");
    fgets(select, sizeof(select), stdin);


    if(tolower(select[0]) != 's') {
        destaque("(#) VOCE ESCOLHEU SAIR");
        return; //Encerra a funcao
    }

    //Mostra os setores cadastrados
    viewSetores(*m_Setores, *a_numero_doSetores);

    printf("\n\n(?) Qual o nome do setor que deseja remover? (Digite o nome exato)\n-> ");

    // Casos de erro para nomeSetor_remove
    do {
        int setorEncontrado = 0; // Inicializa como 0 para cada iteração do loop

        setbuf(stdin, NULL);
        fgets(nomeSetor_remove, sizeof(nomeSetor_remove), stdin);

        // Remove o caractere de nova linha, se houver
        if(nomeSetor_remove[strlen(nomeSetor_remove) - 1] == '\n') {
            nomeSetor_remove[strlen(nomeSetor_remove) - 1] = '\0';
        }

        if(nomeSetor_remove[0] == ' ' || nomeSetor_remove[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO NOME DO SETOR. DIGITE UM NOME VALIDO!");
            printf("\n->");
            continue; // Reinicia o loop, pedindo novamente o nome do setor
        }

        for(int setor = 0; setor < *a_numero_doSetores; setor++) {
            if(strcmp(nomeSetor_remove, (*m_Setores)[setor]) == 0) {
                setorEncontrado = 1;
                break;
            }
        }

        if(!setorEncontrado) {
            erro("(x) SETOR NAO ENCONTRADO. TENTE OUTRO");
            printf("\n->");
            continue; // Reinicia o loop, pedindo novamente o nome do setor
        }

        // Se chegou aqui, significa que o setor foi encontrado, então podemos sair do loop
        break;

    } while(1);


    for(int setor = 0; setor < (*a_numero_doSetores); setor++) {
        if(strcmp(nomeSetor_remove, (*m_Setores)[setor]) == 0) {
            indiceSetor_remove = setor;
        break;  // Se encontrado, não precisa continuar procurando
        }
    }

    // Liberar a memória do elemento removido
    free((*m_Setores)[indiceSetor_remove]);
    free((*m_Zoo)[indiceSetor_remove]);

    // Mover os elementos restantes para preencher o espaço do setor removido
    for (int i = indiceSetor_remove; i < *a_numero_doSetores - 1; i++) {
        (*m_Setores)[i] = (*m_Setores)[i + 1];
        (*m_Zoo)[i] = (*m_Zoo)[i + 1];
        (*qntdAnimais)[i] = (*qntdAnimais)[i + 1];
    }

    // Realocar memória para reduzir o tamanho dos arrays em uma unidade
    *m_Setores = realloc(*m_Setores, (*a_numero_doSetores - 1) * sizeof(char *));
    *m_Zoo = realloc(*m_Zoo, (*a_numero_doSetores - 1) * sizeof(Info_animal **));
    *qntdAnimais = realloc(*qntdAnimais, (*a_numero_doSetores - 1) * sizeof(int));

    (*a_numero_doSetores)--;

    if (*a_numero_doSetores == 0){ 
        *p_setorCadastrado_Ok = 0;
        *p_animalCadastrado_ok = 0;
    }

    sucesso("(<->) DEU CERTO! SETOR REMOVIDO PERMANENTEMENTE COM EXITO.");
}


// *NOVA FUNCAO - Esta funcao permite editar as informacoes do animal 
void editAnimal(Info_animal ****mZoo, char **matrizSetores, int numeroSetores, int qntdAnimais, int **matriz_qntdAnimais, int numeroJaulas) {
    int numeroAnimal = -1; // O -1 eh apenas um valor diferente de zero para verificar o retorno da funcao
    char codAnimal[TAM];
    char nomeSetor[TAM];
    int indiceSetor = -1, nJaula, indiceJaula, indiceAnimal;
    char numeroDaJaula[TAM]; // Usa-se char para verficiar os casos de erro

    confirmacao("\n\t\t\t===== (@) EDITAR INFORMACOES DE UM ANIMAL =====\n");

    viewSetores(matrizSetores, numeroSetores);

    printf("\n\n(?) Em que setor esta este animal? \n-> ");

    // Casos de erro para nomeSetor
    do {
        int condicaoOk = 1; // Flag da condicao se der tudo certo
        int setorEncontrado = 0; // Flag que verifica se o setor digitado foi encontrado

        setbuf(stdin, NULL);
        fgets(nomeSetor, sizeof(nomeSetor), stdin);

        // Remove o caractere de nova linha, se houver
        if(nomeSetor[strlen(nomeSetor) - 1] == '\n') {
            nomeSetor[strlen(nomeSetor) - 1] = '\0';
        }

        if(nomeSetor[0] == ' ' || nomeSetor[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO NOME DO SETOR. DIGITE UM NOME VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Sai da funcao se 'X' for digitado
        if(tolower(nomeSetor[0]) == 'x') {
            destaque("(#) VOCE ESCOLHEU SAIR");
            return;
        }

        // Verifica se tem um numero no nome
        for(int y = 0; nomeSetor[y] != '\0'; y++) {
            if(isdigit(nomeSetor[y])) {
                erro("(x) NAO EH PERMITIDO NUMEROS NO NOME. ESCREVA UM NOME VALIDO!");
                printf("\n\n-> ");
                condicaoOk = 0;
                break;
            }
        }

        if(condicaoOk) {

            for(int setor = 0; setor < numeroSetores; setor++) {
                if(strcmp(nomeSetor, matrizSetores[setor]) == 0) {
                    setorEncontrado = 1;
                    break;
                }
            }

            if(!setorEncontrado) {
                erro("(x) SETOR NAO ENCONTRADO. TENTE OUTRO");
                printf("\n\n-> ");
                continue;
            }
        }

        // Retorna o indice do setor, se achar
        for(int setor = 0; setor < numeroSetores; setor++) {
            if(strcmp(nomeSetor, matrizSetores[setor]) == 0) {
                indiceSetor = setor;
            }
        
        }

        if(indiceSetor == -1) {
            erro("\n\n(x) SETOR NAO ENCONTRADO. DIGITE NOVAMENTE OU DIGITE 'X' PARA SAIR");
            printf("\n\n-> ");
            continue;
        }

        break;

    } while(1);

    viewJaulas(matriz_qntdAnimais, numeroJaulas, indiceSetor, qntdAnimais);

    printf("\n\n(?) Em que jaula este animal habita?\n-> ");

    // Casos de erro para qntdSetor
    do {
        int situacaoOk = 1; // Flag q verifica a situacao dos casos de erro

        setbuf(stdin, NULL);

        fgets(numeroDaJaula, sizeof(numeroDaJaula), stdin);

        // Remove quebra de linha
        if(numeroDaJaula[strlen(numeroDaJaula) - 1] == '\n') {
            numeroDaJaula[strlen(numeroDaJaula) - 1] = '\0';
        }

        // Evita espacos vazios
        if(numeroDaJaula[0] == ' ' || numeroDaJaula[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU LINHAS VAZIAS. DIGITE UM VALOR VALIDO!");
            printf("\n\n-> ");
            continue;
        }


        // Verifica se a entrada eh um numero
        for(int i = 0; numeroDaJaula[i] != '\0'; i++){
            if(!isdigit(numeroDaJaula[i])) {
                situacaoOk = 0;
                break;
            }
        }
        

        if(!situacaoOk) {
            erro("(x) VOCE DIGITOU UM VALOR INVALIDO. TENTE NOVAMENTE!");
            printf("\n\n-> ");
            continue;
        }

        nJaula = atoi(numeroDaJaula);

        if(nJaula <= 0 || nJaula > numeroJaulas) {
            erro("(x) VALOR FORA DA QUANTIDADE PRSENTE DE JAULAS");
            printf("\n\n-> ");
            continue;
        } else break;

    } while(1);

    indiceJaula = nJaula - 1;

    indiceAnimal = matriz_qntdAnimais[indiceSetor][indiceJaula];

    viewAnimais(*mZoo,indiceSetor,indiceJaula,indiceAnimal, qntdAnimais);

    printf("\n\n(?) Qual o codigo do animal que voce editar as informacoes?\n-> ");

    // Casos de erro para codAnimal
    do {
        int codigoExistente = 0; // Flag que verifica se o codigo existe ou nao

        fgets(codAnimal, sizeof(codAnimal), stdin);

        // Remove a quebra de linha
        if(codAnimal[strlen(codAnimal) - 1] == '\n') {
            codAnimal[strlen(codAnimal) - 1] = '\0';
        }

        // Evita linha vazia
        if(codAnimal[0] == '\0') {
            erro("(x) NAO EH PERMITIDO RESPOSTA EM BRANCO. DIGITE O CODIGO!");
            printf("\n\n-> ");
            continue;
        }



        for(int animais = 0; animais < qntdAnimais; animais++) {
            // Remove a qubra de linha antes da comparacao
            for (int t = 0; (*mZoo)[indiceSetor][indiceJaula][animais].codigo[t] != '\0'; t++) {
                if ((*mZoo)[indiceSetor][indiceJaula][animais].codigo[t] == '\n') {
                    (*mZoo)[indiceSetor][indiceJaula][animais].codigo[t] = '\0';
                    break;
                }
            }


            if(strcmp((*mZoo)[indiceSetor][indiceJaula][animais].codigo, codAnimal) == 0) {
                codigoExistente = 1;
                break;
            }
        }

        if(!codigoExistente) {
            erro("(x) CODIGO NAO ENCONTRADO! TENTE NOVAMENTE.");
            printf("\n\n-> ");
            continue;
        }

        break;

    } while(1);

    // Confere se o codigo digitado esta registrado e dá retorno mediante a busca
    for(int n = 0; n < qntdAnimais; n++) {
        if(strcmp(codAnimal,(*mZoo)[indiceSetor][indiceJaula][n].codigo) == 0) numeroAnimal = n;
    }

    /// Se nenhum registro foi encontrado
    if(numeroAnimal == -1) return;

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
    printf("\n\n(A) CODIGO\n(B) NOME\n(C) PESO\n(D) ALTURA\n(E) ESPECIE\n(X) FECHAR MENU DE EDICAO\n\n-> ");


    do {
        fgets(opcao, sizeof(opcao), stdin);
        
        // Remove o caractere de nova linha, se houver
        if(opcao[strlen(opcao) - 1] == '\n') {
            opcao[strlen(opcao) - 1] = '\0';
        }

        // Volta ao menu
        if(tolower(opcao[0]) == 'x') {
            destaque("(#) VOCE ESCOLHEU SAIR");
            return;
        }

        if (!isalpha(opcao[0]) || (tolower(opcao[0]) < 'a' || tolower(opcao[0]) > 'e') || opcao[1] != '\0') {
            erro("(x) OPCAO INVALIDA OU FORA DOS PARAMETROS. DIGITE UMA DAS OPCOES ACIMA!");
            printf("\n\n-> ");
            continue;
        }

        break;

    } while(1);

    char novoCodigo[TAM];
    char novoNome[TAM];
    char novoPeso[TAM];
    char novaAltura[TAM];
    char novaEspecie[TAM];


    switch(tolower(opcao[0])) {
        case 'a':
            printf("\n\n(?) Qual o novo codigo do animal?\n-> ");

            // Casos de erro para codigo
            do {
                int condicaoOk = 1; // Flag da condicao se der tudo certo
                int codigoExistente = 0; // Flag que verifica se o codigo ja existe

                setbuf(stdin, NULL);
                fgets(novoCodigo, sizeof(novoCodigo), stdin);


                if(novoCodigo[0] == ' ' || novoCodigo[0] == '\0') {
                    erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO CODIGO. DIGITE UM CODIGO VALIDO!");
                    printf("\n\n-> ");
                    condicaoOk = 0;
                }

        
                if(condicaoOk) {
                    // Verifica se esse codigo ja pertence a outro animal
                    for(int setor = 0; setor <  numeroSetores; setor++) {
                        for(int jaula = 0; jaula <  numeroJaulas; jaula++) {
                            for(int animais = 0; animais < qntdAnimais; animais++) {
                                if(strcmp((*mZoo)[setor][jaula][animais].codigo, novoCodigo) == 0) {
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

                    strcpy((*mZoo)[indiceSetor][indiceJaula][numeroAnimal].codigo, novoCodigo);
                    break;
                }

            } while(1);
            
            break;

        case 'b':
            printf("\n\n(?) Qual o novo nome do animal?\n-> ");

            // Casos de erro para nome
            do {
                int condicaoOk = 1; // Flag da condicao se der tudo certo

                setbuf(stdin, NULL);
                fgets(novoNome, sizeof(novoNome), stdin);

                // Remove o caractere de nova linha, se houver
                if(novoNome[strlen(novoNome) - 1] == '\n') {
                    novoNome[strlen(novoNome) - 1] = '\0';
                }

                if(novoNome[0] == ' ' || novoNome[0] == '\0') {
                    erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DO NOME. DIGITE UM NOME VALIDO!");
                    printf("\n\n-> ");
                    continue;
                }

                // Verifica se tem um numero no nome
                for(int i = 0; novoNome[i] != '\0'; i++) {
                    if(isdigit(novoNome[i])) {
                        erro("(x) NAO EH PERMITIDO NUMEROS NO NOME. ESCREVA UM NOME VALIDO!");
                        printf("\n\n-> ");
                        condicaoOk = 0;
                        break;
                    }
                }

                if(!condicaoOk) {
                    continue;
                }

                strcpy((*mZoo)[indiceSetor][indiceJaula][numeroAnimal].nome, novoNome);
                break;

            } while(1);

            break;

        case 'c':
            printf("\n\n(?) Qual o novo peso do animal?\n-> ");
            
            // Casos de erro para peso
            do {
                int condicaoOk = 1; // Flag da condicao se der tudo certo
                int pontoDecimal = 0; // A entrada pode haver o '.', em casos de valores decimais. Vamos incluir na condicao para que seja aceito

                setbuf(stdin, NULL);
                fgets(novoPeso, sizeof(novoPeso), stdin);

                // Remove o caractere de nova linha, se houver
                if(novoPeso[strlen(novoPeso) - 1] == '\n') {
                    novoPeso[strlen(novoPeso) - 1] = '\0';
                }

                // Verifica se ha espacos ou linha vazia
                if(novoPeso[0] == ' ' || novoPeso[0] == '\0' || novoPeso[0] == '.') {
                    erro("(x) NAO EH PERMITIDO RESPOSTAS EM BRANCO, COM ESPACOS INICIAIS OU PONTO UNICO. DIGITE UM PESO VALIDO!");
                    printf("\n\n-> ");
                    continue;
                }



                // Verifica se eh uma letra
                for (int i = 0; novoPeso[i] != '\0'; i++) {
                    if (!isdigit(novoPeso[i])) {
                        if (novoPeso[i] == '.' && !pontoDecimal) {
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
                    (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].peso = atof(novoPeso); // Converte de string para float
                    break;
                }

            } while(1);
            
            break;
        
        case 'd':
            printf("\n\n(?) Qual a nova altura do animal?\n-> ");

            // Casos de erro para peso
            do {
                int condicaoOk = 1; // Flag da condicao se der tudo certo
                int pontoDecimal = 0; // A entrada pode haver o '.', em casos de valores decimais. Vamos incluir na condicao para que seja aceito

                setbuf(stdin, NULL);
                fgets(novaAltura, sizeof(novaAltura), stdin);

                // Remove o caractere de nova linha, se houver
                if(novaAltura[strlen(novaAltura) - 1] == '\n') {
                    novaAltura[strlen(novaAltura) - 1] = '\0';
                }

                // Verifica se ha espacos ou linha vazia
                if(novaAltura[0] == ' ' || novaAltura[0] == '\0' || novaAltura[0] == '.') {
                    erro("(x) NAO EH PERMITIDO RESPOSTAS EM BRANCO, COM ESPACOS INICIAIS OU PONTO UNICO. DIGITE UM PESO VALIDO!");
                    printf("\n\n-> ");
                    continue;
                }



                // Verifica se eh uma letra
                for (int i = 0; novaAltura[i] != '\0'; i++) {
                    if (!isdigit(novaAltura[i])) {
                        if (novaAltura[i] == '.' && !pontoDecimal) {
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
                    (*mZoo)[indiceSetor][indiceJaula][numeroAnimal].altura = atof(novaAltura); // Converte de string para float
                    break;
                }

            } while(1);
            
            break;
        
        case 'e':
            printf("\n\n(?) Edite a especie?\n-> ");

            // Casos de erro para especie
            do {
                int condicaoOk = 1; // Flag da condicao se der tudo certo

                setbuf(stdin, NULL);
                fgets(novaEspecie, sizeof(novaEspecie), stdin);

                // Remove o caractere de nova linha, se houver
                if (novaEspecie[strlen(novaEspecie) - 1] == '\n') {
                    novaEspecie[strlen(novaEspecie) - 1] = '\0';
                }

                if(novaEspecie[0] == ' ' || novaEspecie[0] == '\0') {
                    erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DA ESPECIE. DIGITE UMA ESPECIE VALIDA!");
                    printf("\n\n-> ");
                    continue;
                }

                // Verifica se tem um numero no nome
                for(int i = 0; novaEspecie[i] != '\0'; i++) {
                    if(isdigit(novaEspecie[i])) {
                        erro("(x) NAO EH PERMITIDO NUMEROS NA ESPECIE. ESCREVA UMA ESPECIE VALIDA!");
                        printf("\n\n-> ");
                        condicaoOk = 0;
                        break;
                    }
                }

                if(condicaoOk) {
                    strcpy((*mZoo)[indiceSetor][indiceJaula][numeroAnimal].especie, novaEspecie);
                    break;
                }

            } while(1);
            
            break;

        default:
            printf("\n\nErro");
    }

    sucesso("<-> INFORMACOES DO ANIMAL ATUALIZADAS COM SUCESSO!");

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
    char **setores, numero_doSetores_char[TAM], numero_daJaulas_char[TAM], nAnimais_char[TAM];
    int numero_doSetores, numero_daJaulas, nAnimais, *p_numero_doSetores;
    int **qntdAnimais;
    p_numero_doSetores = &numero_doSetores;

    // Determina local para usos de acentos e simbolos
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // FLAGS (GLOBAL) (Variaveis de mudanca de estado)  - (certificam que algumas mudancas so podem ser realizadas mediante outras)
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

    // Casos de erro para numero_doSetores
    do {
        int condicaoOk = 1;

        fgets(numero_doSetores_char, sizeof(numero_doSetores_char), stdin);

        if(numero_doSetores_char[strlen(numero_doSetores_char) - 1] == '\n') {
            numero_doSetores_char[strlen(numero_doSetores_char) - 1] = '\0';
        }

        if(numero_doSetores_char[0] == ' ' || numero_doSetores_char[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DA LINHA. DIGITE UM VALOR VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se eh uma letra
        for (int i = 0; numero_doSetores_char[i] != '\0'; i++) {
            if(!isdigit(numero_doSetores_char[i])) {
                erro("(x) NAO EH PERMITIDO LETRAS OU SIMBOLOS NESTE CAMPO. DIGITE UM VALOR VALIDO!");
                printf("\n\n-> ");
                condicaoOk = 0;
                break;
            }
        }

        if(!condicaoOk) continue;

        // Verifica se se eh maior que zero
        if(atoi(numero_doSetores_char) <= 0) {
            erro("(x) NAO EH PERMITIDO VALORES MENORES OU IGUAIS A ZERO!");
            printf("\n\n-> ");
            continue;
        }

        numero_doSetores = atoi(numero_doSetores_char);
        break;

    } while(1);

    printf("\n(+) Agora, digite o numero de jaulas por setor: ");

    // Casos de erro para numero_daJaulas
    do {
        int condicaoOk = 1;

        fgets(numero_daJaulas_char, sizeof(numero_daJaulas_char), stdin);

        if(numero_daJaulas_char[strlen(numero_daJaulas_char) - 1] == '\n') {
            numero_daJaulas_char[strlen(numero_daJaulas_char) - 1] = '\0';
        }

        if(numero_daJaulas_char[0] == ' ' || numero_daJaulas_char[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DA LINHA. DIGITE UM VALOR VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se eh uma letra
        for (int i = 0; numero_daJaulas_char[i] != '\0'; i++) {
            if(!isdigit(numero_daJaulas_char[i])) {
                erro("(x) NAO EH PERMITIDO LETRAS NESTE CAMPO. DIGITE UM VALOR VALIDO!");
                printf("\n\n-> ");
                condicaoOk = 0;
                break;
            }
        }

        if(!condicaoOk) continue;

        // Verifica se se eh maior que zero
        if(atoi(numero_daJaulas_char) <= 0) {
            erro("(x) NAO EH PERMITIDO VALORES MENORES OU IGUAIS A ZERO!");
            printf("\n\n-> ");
            continue;
        }

        numero_daJaulas = atoi(numero_daJaulas_char);
        break;

    } while(1);

    printf("\n(+) Agora, digite o numero de animais por jaula: ");

    // Casos de erro para nAnimais
    do {
        int condicaoOk = 1;

        fgets(nAnimais_char, sizeof(nAnimais_char), stdin);

        if(nAnimais_char[strlen(nAnimais_char) - 1] == '\n') {
            nAnimais_char[strlen(nAnimais_char) - 1] = '\0';
        }

        if(nAnimais_char[0] == ' ' || nAnimais_char[0] == '\0') {
            erro("(x) NAO EH PERMITIDO ESPACOS EM BRANCO OU NO INICIO DA LINHA. DIGITE UM VALOR VALIDO!");
            printf("\n\n-> ");
            continue;
        }

        // Verifica se eh uma letra
        for (int i = 0; nAnimais_char[i] != '\0'; i++) {
            if(!isdigit(nAnimais_char[i])) {
                erro("(x) NAO EH PERMITIDO LETRAS NESTE CAMPO. DIGITE UM VALOR VALIDO!");
                printf("\n\n-> ");
                condicaoOk = 0;
                break;
            }
        }

        if(!condicaoOk) continue;

        // Verifica se se eh maior que zero
        if(atoi(nAnimais_char) <= 0) {
            erro("(x) NAO EH PERMITIDO VALORES MENORES OU IGUAIS A ZERO!");
            printf("\n\n-> ");
            continue;
        }

        nAnimais = atoi(nAnimais_char);
        break;

    } while(1);

    confirmacao("(<->) So um instante, estamos salvando suas informacoes...");

    zoologico = (Info_animal ***)malloc(numero_doSetores * sizeof(Info_animal **));
    setores = (char **)malloc(numero_doSetores * sizeof(char *));
    qntdAnimais = (int **)malloc(numero_doSetores * sizeof(int *));

    if(zoologico == NULL || setores == NULL || qntdAnimais == NULL){
        erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
        sleep(3);
        exit(1);
    }

    for(int setor = 0; setor < numero_doSetores; setor++) {
        zoologico[setor] = (Info_animal **)malloc(numero_daJaulas * sizeof(Info_animal *));
        setores[setor] = (char *)malloc(numero_daJaulas * sizeof(char));
        qntdAnimais[setor] = (int *)malloc(numero_daJaulas * sizeof(int));

        if(zoologico[setor] == NULL || setores[setor] == NULL || qntdAnimais[setor] == NULL){
            erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
            sleep(3);
            exit(1);
        }

        for(int jaula = 0; jaula < numero_daJaulas; jaula++) {
            zoologico[setor][jaula] = (Info_animal *)malloc(nAnimais * sizeof(Info_animal));

            if(zoologico[setor][jaula] == NULL){
                erro("\n(x) UM ERRO CRITICO ACONTECEU. ENCERRANDO ESTE PROGRAMA");
                sleep(3);
                exit(1);
            }

            //Zerar todas as posicoes
            qntdAnimais[setor][jaula] = 0;
        }
    }

    sucesso("(<->) DEU CERTO! INFORMACOES INICIAIS CONSIDERADAS");

    // Loop para manter programa em funcionamento
    while(1) {
        char opcaoMenu[TAM_MIN];

        // FLAGS INTERNAS (Variaveis de mudanca de estado)  - (certificam que algumas mudancas so podem ser realizadas mediante outras)
        int menuOk = 0; // Verifica no fim do loop se alguma caractere condiz com algum menu abaixo. Se n condiz, continua 0.

        // *MENU DE OPCOES

        // *Verifica se o user ja cadastrou pelo menos 1 setor pela primeira vez (altera o txt do menu A)
        //Tambem mostra o menu de acordo com a acao executada (altera o valor de 'showMenu' para 0. Se for 0, o menu aparece)
        
        if(showMenu == 0) {
            if(setorCadastrado_ok == 0) viewMenu("\033[1;33m[!] CADASTRE OS PRIMEIROS SETORES\033[0m");
            else viewMenu("CADASTRAR NOVO(S) SETOR(ES)");
        }

        showMenu = 0;

        confirmacao("\n(#) Digite uma opcao somente dentre os menus acima\n-> ");
        setbuf(stdin,NULL);
        fgets(opcaoMenu, sizeof(opcaoMenu), stdin);


        // CADASTRAR SETORES
        if(tolower(opcaoMenu[0]) == 'a') {
            menuOk = 1;

            if(primeiroCadastro_Setor_Ok == 0) {
                cadSetor(setores, numero_doSetores);
                primeiroCadastro_Setor_Ok = 1;
            } else addSetor(&setores, p_numero_doSetores, &zoologico, numero_daJaulas, nAnimais, &qntdAnimais);

            setorCadastrado_ok = 1;
            showMenu = 0;
        }

        // REMOVER UM SETOR
        if(tolower(opcaoMenu[0]) == 'b') {
            menuOk = 1;

            if(!setorCadastrado_ok) {
                erro("(x) ACAO NEGADA - < NAO E POSSIVEL REMOVER UM SETOR SEM ANTES CADASTRAR UM >");
                showMenu = 1;
            }
            else {
                removeSetor(&setores, p_numero_doSetores, &zoologico, &qntdAnimais, p_setorCadastrado_Ok, p_animalCadastrado_ok);
                showMenu = 0;
            }
        }

        // CADASTRAR UM NOVO ANIMAL
        if(tolower(opcaoMenu[0]) == 'c') {
            menuOk = 1;
            
            if(!setorCadastrado_ok) {
                erro("(x) ACAO NEGADA - < NAO E POSSIVEL ADICIONAR UM ANIMAL SEM ANTES CADASTRAR UM SETOR >");
                showMenu = 1;
            } else {
                cadAnimal(zoologico, setores, numero_doSetores, qntdAnimais, numero_daJaulas, nAnimais);
                animalCadastrado_Ok = 1;
                showMenu = 0;
            }
        }

        // EDITAR INFO. DO ANIMAL
        if(tolower(opcaoMenu[0]) == 'd') {
            menuOk = 1;

            if(!animalCadastrado_Ok) {
                erro("(x) ACAO NEGADA - < NAO EH POSSIVEL EDITAR UM ANIMAL SEM ANTES CADASTRAR UM >");
                showMenu = 1;
            } else {
                editAnimal(&zoologico, setores, numero_doSetores, nAnimais, qntdAnimais, numero_daJaulas);
            }
        }

        // ANIMAL MAIS PESADO P/ SETOR
        if(tolower(opcaoMenu[0]) == 'e') {
            menuOk = 1;

            if(!animalCadastrado_Ok) {
                erro("(x) ACAO NEGADA - < NAO EH POSSIVEL FAZER UMA BUSCA DE ANIMAIS SEM ANTES CADASTRAR UM >");
                showMenu = 1;
            } else {
                animal_maisPesado(setores, zoologico, numero_doSetores, numero_daJaulas, nAnimais);
                showMenu = 0;
            }
        }

        // LISTA DE SETORES
        if(tolower(opcaoMenu[0]) == 'f') {
            menuOk = 1;
            
            if(!setorCadastrado_ok) {
                erro("(x) ACAO NEGADA - < NAO E POSSIVEL LISTAR SETORES INEXISTENTES >");
                showMenu = 1;
            }
            else {
                viewSetores(setores, numero_doSetores);
                showMenu = 0;
            }
        }

        

        // Se o caractere digitado nao entrou em nenhum menu
        if(menuOk == 0) {
            erro("\n(x) VOCE DIGITOU UM CARACTERE INVALIDO OU FORA DOS PARAMETROS.");
            showMenu = 1;
        }
    }

    return 0;
}