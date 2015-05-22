//Alex Fernandes Mansano
//Lucas C. Ferreira 
#include"stdio.h"
#include"conio.h"
#include "iostream"
#include"malloc.h"

using namespace std;
#define MAX 4 //suponha que seja sempre par



template <typename T> //lista para dados e ponteiros
struct no_lista
{
	T dado;
	no_lista *prox;
};


template <typename T>
class lista //classe com métodos para dados e ponteiros
{
	private:
		no_lista<T> *inicio;
	public:
		lista()
		{
			inicio = NULL;
		}

		void setInicio(no_lista<T> *no)
		{
			inicio = no;
		}

		int insereNo(no_lista<T> *no)
		{
			int pos = 0;

			no_lista<T> *p = inicio;
			no_lista<T> *ant;

			while(p!= NULL && p->dado < no->dado)
			{
				ant = p;
				p=p->prox;
				pos++;
			}
			if(p == inicio)
			{
				no->prox = inicio;
				inicio = no;
			}
			else
			{
				ant->prox = no;
				no->prox = p;
			}
			return pos;
		}

		int insereOrdenado(T dado)
		{
			int pos = 0;
			no_lista<T> *novo = new no_lista<T>;//cria novo nó
			novo->dado = dado;
			novo->prox = NULL;

			no_lista<T> *p = inicio;
			no_lista<T> *ant;

			while(p!= NULL && p->dado < dado)
			{
				ant = p;
				p=p->prox;
				pos++;
			}
			if(p == inicio)
			{
				novo->prox = inicio;
				inicio = novo;
			}
			else
			{
				ant->prox = novo;
				novo->prox = p;
			}
			return pos;
		}

		void insereFim(T dado)
		{
			no_lista<T> *novo = new no_lista<T>;//cria novo nó
			novo->dado = dado;
			novo->prox = NULL;

			no_lista<T> *p = inicio;

			if(inicio == NULL)
				inicio = novo;
			else
			{
				while(p->prox != NULL)
					p = p->prox;
				p->prox = novo;
			}

		}

		void inserePosicao(T dado, int pos, bool substitui)
		{
			no_lista<T> *novo = new no_lista<T>;//cria novo nó
			novo->dado = dado;
			novo->prox = NULL;

			no_lista<T> *p = inicio;
			no_lista<T> *ant;

			for(int i=0; p!=NULL && i < pos; i++)
			{
				ant = p;
				p=p->prox;
			}

			if(p == inicio)
			{
				if(substitui)	
				{
					if(inicio != NULL)
						novo->prox = inicio->prox;
					delete(inicio);
				}
				else				
					novo->prox = inicio;
				inicio = novo;				
			}
			else
			{
				ant->prox = novo;
				if(substitui)
				{
					novo->prox = p->prox;
					delete(p);
				}
				else
					novo->prox = p;
			}
		}

		no_lista<T> *getInicio()
		{
			return inicio;
		}

		void imprime()//imprime a partir dele
		{
			no_lista<T> *p = inicio;
			while(p!=NULL)
			{
				cout<<p->dado << " ";
				p=p->prox;
			}
		}
};

class Arvore
{
	private:
		int cont;
		lista<int> chaves;
		lista<Arvore*> ptr; //lista de ponteiros para os nos 

		Arvore* divide() //divide a arvore em duas partes e gera um novo nó com o elemento medio
		{
			Arvore *dir = new Arvore;
			Arvore *esq = new Arvore;
			no_lista<int> *p = chaves.getInicio();
			no_lista<int> *ant;

			no_lista<Arvore*> *pArv = NULL;
			no_lista<Arvore*> *antArv =  ptr.getInicio();
			if(antArv != NULL) //não é folha
				pArv = antArv->prox;//começa no segundo			
			
			//supondo que pos sera sempre menor que o tamanho, ja que é a metade
			int pos = MAX/2; //Não adiciono 1 pois estou começando do 0
			for(int i=0;  i< pos; i++)//anda ate a posição setada
			{
				ant = p;
				p=p->prox;

				if(pArv!=NULL)//Os ponteiros sempre andam uma posição na frente das chaves, pois há um a mais
				{
					antArv = pArv;
					pArv = pArv->prox;
				}
			}


			//poderia verificar se é o início, mas assumindo que será o tamanho médio do nó não farei essa verificação
			

			ant->prox = NULL; //finliza a metade da lista das chaves
			esq->chaves.setInicio(chaves.getInicio());

			if(antArv != NULL)//não é folha
				antArv->prox = NULL; //finliza a metade da lista dos ponteiros
			esq->ptr.setInicio(ptr.getInicio());
			esq->cont = pos;	

			dir->chaves.setInicio(p->prox); //Seta novo inicio da lista
			dir->ptr.setInicio(pArv);//seta inicio da lista dos ponteiros
			dir->cont = MAX - pos; //sempre será a metade, mas mantive o cálculo
			

			cont = 1; //resta o nó que subiu
			p->prox = NULL; //será um novo nó
			chaves.setInicio(p);

			//setar o inicio
			ptr.setInicio(NULL);
			ptr.insereFim(esq);
			ptr.insereFim(dir); //pode ser otimizado para inserir os dois.

			return this;
		}

	public:
		Arvore()
		{
			cont = 0;
			//ptr.insere(NULL);
		}		

		Arvore* insere(int dado)//se for inserir no pai traz as chaves junto
		{
			if(ptr.getInicio() != NULL) //não é folha
			{
				no_lista<int> *p = chaves.getInicio();
				no_lista<Arvore*> *pArv = ptr.getInicio();
			
				while(p!=NULL && dado > p->dado)
				{
					p = p->prox; 
					pArv = pArv->prox;
				}

				Arvore *novo = (pArv->dado)->insere(dado);//pAv->dado é o ponteiro para objeto Arvore
				if( novo != NULL) // Se dividiu
				{
					int pos = chaves.insereNo(novo->chaves.getInicio()); //ha apenas uma chave nesse caso
					cont++;
					no_lista<Arvore *> *aux = novo->ptr.getInicio();
					ptr.inserePosicao(aux->dado, pos, true);
					ptr.inserePosicao(aux->prox->dado, pos + 1, false);			

					if(cont > MAX)							
						return divide();
					else
						return NULL;
				}
			}
			else
			{	
				cont++;
				int pos = chaves.insereOrdenado(dado);
				//folha nao precisa de ponteiro para arvores
	
				if(cont > MAX)							
					return divide();
				else
					return NULL;
			}
		}

		void setCont(int c)
		{
			cont = c;
		}
		
		bool busca(int dado) //pode-se também retornar o endereço do elemento
		{
			no_lista<Arvore *> *pArv = ptr.getInicio();
			no_lista<int> *p = chaves.getInicio();

			while(p!=NULL && p->dado < dado)
			{
				p=p->prox;
				if(pArv != NULL)//não é folha
					pArv = pArv->prox;
			}

			if(p!= NULL) //o ideal seria pensar em uma solução com menos if's, diminuindo desvios no código, mas não houve tempo
			{
				if(p->dado == dado)
					return true;
				else //p->dado é maior
				{
					if(pArv != NULL)//não é folha
						return (pArv->dado)->busca(dado);
					else 
						return false; //é folha, procurou tudo
				}
			}
			if(pArv != NULL)//não é folha
				return (pArv->dado)->busca(dado);
			else 
				return false; //é folha, procurou tudo
		}

		void imprime(int n)
		{
			chaves.imprime();
			no_lista<Arvore*> *p = ptr.getInicio();
			cout<<"\n";
			while(p != NULL)
			{
				for(int i=0;i<n;i++)//identa, deixa a complexidade quadrática, mas nao é uma operação custosa
					cout << "   ";
				(p->dado)->imprime(n+1);
				p=p->prox;
			}
		}
};

int main()
{
	int op = 0;
	int val;
	Arvore *raiz; //raiz	
	Arvore arv;
	
		/*arv.insere(1);
		arv.insere(12);
		arv.insere(8);
		arv.insere(2);
		arv.insere(25);
		arv.insere(6);
		arv.insere(14);
		arv.insere(28);
		arv.insere(17);
		arv.insere(7);
		arv.insere(52);
		arv.insere(16);
		arv.insere(48);
		arv.insere(68);
		arv.insere(3);
		arv.insere(26);
		arv.insere(29);
		arv.insere(53);
		arv.insere(55);
		arv.insere(45);*/
	do
	{
		cout << "\n1- Inserir \n2- Imprimir \n3- Buscar \n0- Sair \n";
		cin>>op;
		switch(op)
		{
			case 1:
				cout<<"Digite o valor: ";
				cin >> val;
				arv.insere(val);
				break;
			case 2:
				cout<<"\n";
				arv.imprime(1);
				break;			
			case 3:
				cout<<"Digite o valor: ";
				cin >> val;
				if(arv.busca(val))
					cout << "Elemento encontrado!";
				else
					cout << "Elemento não encontrado";
				break;
		}
	}while(op!=0);

	getch();
}
