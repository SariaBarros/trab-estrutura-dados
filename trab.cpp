#include <cstdio>
#include <cctype>
#include <cstring>

#define MIN 3
#define MAX 20

/* Célula de uma lista encadeada de ocorrências, armazena um inteiro */
class Ocorrencia {
  friend class ListaO;

public:
  Ocorrencia(int linha); // Construtor padrão
  ~Ocorrencia();         // Destrutor padrão

private:
  int linha;
  Ocorrencia *prox;
};


/* Lista encadeada de ocorrências, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaO {
public:
  ListaO();               // Construtor padrão
  ~ListaO();              // Destrutor padrão
  void insere(int linha); // Recebe um inteiro e insere na lista
  void escreve();         // Escreve os elementos da lista

private:
  Ocorrencia *inicio; // Início da lista
  Ocorrencia *fim;    // Fim da lista
};


/* Célula de uma lista encadeada de palavras, armazena uma cadeia de caracteres */
class Palavra {
  friend class ListaP;

public:
  Palavra(char p[]);      // Construtor padrão
  ~Palavra();             // Destrutor padrão
  void insere(int linha); // Insere uma ocorrência na lista de ocorrências
  void escreve();         // Escreve a palavra e suas ocorrências

private:
  char p[MAX];        // A palavra em si
  ListaO ocorrencias; // Lista de ocorrências
  Palavra *prox;      // Próxima Palavra na lista
};


/* Lista encadeada de palavras, inserção realizada no fim da lista.
   Tenha o cuidado de não inserir duplicatas */
class ListaP {
public:
  ListaP();                  // Construtor padrão
  ~ListaP();                 // Destrutor padrão
  Palavra *insere(char p[]); // Recebe uma palavra e insere na lista, devolvendo um ponteiro para o objeto inserido
  Palavra *busca(char p[]);  // Busca e devolve o objeto de uma palavra na lista
  void escreve();            // Escreve os elementos da lista

private:
  Palavra *inicio; // Início da lista
  Palavra *fim;    // Fim da lista
};


/* Tabela de dispersão que guarda um índice de palavras */
class TabelaDispersao {
public:
  TabelaDispersao();  // Construtor padrão
  ~TabelaDispersao(); // Destrutor padrão
  void escreve();     // Escreve a tabela (incluindo fator de carga) SAÍDA????siiiim
  void novaOcorrencia(char p[], int linha); // Registra uma nova ocorrência de uma palavra
  
private:
  static const int TAMANHO = 47; // Tamanho da tabela
  ListaP tabela[TAMANHO];        // Listas da tabela

  int valor(char p[]); // Valor da palavra p
  int h(char p[]);     // Função de hash
};

/*
*Implementação da main
*/
int main(int argc, char *argv[]){
  TabelaDispersao H;
  
  int linha = 1;
  int i = 0;
  char palavra[50];
  char c;
	FILE *arq = fopen(argv[1], "r");

	while((c = fgetc(arq)) != EOF){
		if(c >= 'A' && c <= 'Z'){
			palavra[i] = c + 32;
      i++;
		}
    else if (c >= 'a' && c <= 'z'){
      palavra[i] = c;
      i++;
    }
    else{
      palavra[i] = '\0';
      if(i >= MIN && i <= MAX)
        H.novaOcorrencia(palavra, linha);
      i = 0;
      if(c=='\n')
        linha++;        
    }
	}

  fclose(arq);  
  return 0;
}
/**************************/
/*1° criar os contrutores.*/
/**************************/
Ocorrencia::Ocorrencia(int linha): 
    linha(linha),
    prox(NULL){
}

ListaO::ListaO():
    inicio(NULL),
    fim(NULL){
}

Palavra::Palavra(char p[]): ocorrencias(){
    strcpy(this->p, p);
    prox = NULL;
}

ListaP::ListaP():
    inicio(NULL),
    fim(NULL){
}
TabelaDispersao::TabelaDispersao(){

}
/*******************************/
/*Implementação dos destrutores*/
/*******************************/
Ocorrencia::~Ocorrencia(){

}

ListaO::~ListaO(){
  Ocorrencia *ptr = inicio;
  Ocorrencia *aux = NULL; 

    while(ptr)                      
    {
      aux = ptr;
      ptr = ptr ->prox;
      delete(aux);
    }

    inicio = NULL;
    fim = NULL;
}

Palavra::~Palavra(){

}

ListaP::~ListaP(){
  Palavra *ptr = inicio;
  Palavra *aux = NULL; 

    while(ptr)                      
    {
      aux = ptr;
      ptr = ptr ->prox;
      delete(aux);
    }

    inicio = NULL;
    fim = NULL;
}
TabelaDispersao::~TabelaDispersao(){

}

/****************************/
/*Implementação dos métodos*/
/****************************/
void ListaO::insere(int linha){
  Ocorrencia *novo = new Ocorrencia(linha);
  if(inicio == NULL){
    inicio = novo;
    fim = novo;
  }
  else{
    if(fim -> linha != linha){
      fim -> prox = novo;
      fim = novo;
    }  
  }
}

void ListaO::escreve(){   //prestar atenção quando
  Ocorrencia *p = inicio; //a celula for vazia
  while(p){
    if(p->prox != NULL)
      printf("%d, ", p -> linha);
    else{
      printf("%d", p -> linha);
    }
    p = p-> prox;
  }
}

void Palavra::insere(int linha){
    ListaO *lista = new ListaO();
    lista->insere(linha);
}

void Palavra::escreve(){  //// Escreve a palavra e suas ocorrências
  printf(" %s(", p);
  ocorrencias.escreve();
  printf(")");
  
}
// Recebe uma palavra e insere na lista, devolvendo um ponteiro para o objeto inserido
Palavra* ListaP::insere(char p[]){
  Palavra *novo = new Palavra(p);
  if(inicio==NULL)
    inicio = novo;
  else{
    fim -> prox = novo;
    fim = novo;
  }

  return novo;
}
Palavra* ListaP::busca(char p[]){  // Busca e devolve o objeto de uma palavra na lista
    Palavra *ptr = inicio;
    while(ptr!=NULL && strcmp(ptr->p, p) != 0){
      ptr = ptr -> prox;
    }
    if(ptr == NULL)
      return NULL;
    else
      return ptr;
} 
// Escreve os elementos da lista
void ListaP::escreve(){
    Palavra *ptr = inicio;

    while (ptr)
    {
      ptr->escreve();
      ptr = ptr -> prox;
    }   
}
 // Escreve a tabela (incluindo fator de carga)
void TabelaDispersao::escreve(){
  for(int i = 0; i < TAMANHO; i++){
    printf("%d:", i);
    tabela[i].escreve();
    printf("\n");
  }
}

void TabelaDispersao::novaOcorrencia(char p[], int linha){
  int hash = h(p);
  Palavra *ptr = NULL; //armazena o end de um obj palavra
  ptr = tabela[hash].busca(p);
  if(ptr != NULL)
    ptr->insere(linha);
  else{
    ptr = tabela[hash].insere(p);
    ptr -> insere(linha);
  }
}

int TabelaDispersao::valor(char p[]){
  int soma = 0;
    for(int i = 0; p[i] != '\0'; i++){
        soma= soma+p[i];
    }
    return soma; 
}

int TabelaDispersao::h(char p[]){
  int v;
  v = valor(p);
  return v % 47;
}