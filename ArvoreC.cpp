#include"stdio.h"
#include"conio.h"
#include "iostream"
#include"malloc.h"

using namespace std;
#define MAX 6 //suponha que seja sempre par



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

		int insere(T dado)
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

		void insere(T dado, int pos)
		{
			no_lista<T> novo = new no_lista<T>;//cria novo nó
			novo.dado = dado;
			novo.prox = NULL;

			no_lista<T> *p = inicio;
			no_lista<T> *ant;

			for(int i=0; p!=NULL && i <=pos; i++)
			{
				ant = p;
				p=p->prox;
			}

			if(p == inicio)
			{
				novo->prox = inicio;
				inicio = novo;
			}
			else
			{
				ant->prox = &novo;
				novo.prox = p;
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
	public:
		Arvore()
		{
			cont = 0;	
			//ptr.insere(NULL);
		}

		Arvore* divide() //divide a arvore em duas partes e gera um novo nó com o elemento medio
		{
			Arvore dir;
			no_lista<int> *p = chaves.getInicio();
			no_lista<int> *ant;

			no_lista<Arvore*> *pArv = ptr.getInicio();//começa no segundo
			no_lista<Arvore*> *antArv;
			//supondo que pos sera sempre menor que o tamanho, ja que é a metade
			int pos = MAX/2 - 1;
			for(int i=0;  i<= pos; i++)
			{
				ant = p;
				p=p->prox;

				antArv = pArv;
				pArv = pArv->prox;
			}

			int ind = MAX/2 + 1; //metade da lista

			//poderia verificar se é o início, mas assumindo que será o tamanho médio do nó não farei essa verificação
			ant->prox = NULL;
			dir.chaves.setInicio(p->prox); //Seta novo inicio da lista
			p->prox = NULL; //será um novo nó
			cont = pos; 
			dir.cont = MAX - pos - 1; //-1 pois o um nó subirá para o pai
			
			antArv->prox = NULL;
			pArv->prox = NULL;
			dir.ptr.setInicio(pArv->prox->prox); //lista com tamanho minimo maior que 4, logo nao precisa validar
			pArv->prox->prox = NULL;
	
			Arvore noArvore;
			noArvore.chaves.setInicio(p);
			noArvore.ptr.setInicio(pArv);		

			return &noArvore;
		}

		Arvore* insere(int dado)//se for inserir no pai traz as chaves junto
		{
			Arvore *no = NULL;
			cont++;
			int pos = chaves.insere(dado);
			//folha nao precisa de ponteiro para arvores

			if(cont > MAX)							
				 no = divide();

			return no;
		}

		void imprime()
		{
			chaves.imprime();
		}
};

int main()
{
	int op = 0;
	Arvore arv;	
	
	do
	{
		cout<<"Digite o valor: ";
		cin >> op;
		if(op != 0)
			arv.insere(op);
		else
			arv.imprime();
	}while(op!=0);

	getch();
}
