include <stdio.h>
include <stdlib.h>

//struct auxiliar para filas
struct Fila
{
	//tamanho do vetor
	int tam;
	//vetor para armazenar os elementos
	int fila[tam];
	//variavel indica indice de inicio da fila
	int fi = 0;
	//variavel indica indice de final da fila
	int ff = 0;
	//função para adicionar elemento na fila
	void adicionar(int elem);
	//funcao para remover elemento na fila
	void remover();
}

//adiciona o elem no final da fila
void adicionar(int elem)
{
	if(ff <= tam)
	{
		fila[ff] = elem;
		ff++;
	}
	else
	{
		printf("Impossível adicionar elemento em fila cheia.");	
	}
	return;
}

//apenas atualiza os valores de cada indice do vetor sem retornar o valor do primeiro da fila
void remover()
{
	if(ff > fi)
	{
		for(int i = 1; i < ff; i++)
		{
			fila[i-1] = fila[i];
		}
		ff--;	
	}
	else
	{
		printf("Impossível remover elemento de fila vazia.");
	}
	
	return;
}



//struct auxiliar para semáforos
struct Semaforo
{
	//contador da fila
    int contador;
    //fila para armazenar PID de processos
    Fila fila_de_processos;
    //liberar recurso
    void up(int processo);
    //requisitar recurso
    void down(int processo);
};

//INCOMPLETO
void up(int proc)
{
	contador++;
	if(contador >= 0)
	{
		fila_de_processos.remover();
	}
	return;
}

//INCOMPLETO
void down(int proc)
{
	contador--;
	if(contador < 0)
	{
		fila_de_processos.adicionar(proc);
	}
	return;
}


//INCOMPLETO
int main()
{
	//Variáveis Compartilhadas
	Semaforo mutex=1;
	Semaforo a=2;
	Semaforo b=0;
	
	//Processo A:
	while true do 
		down(a);
		down(mutex);
		print(A);
		print(B);
		up(mutex);
		up(b);
	end while
	
	//Processo B:
	while true do
		down(b);
		down(mutex);
		print(C);
		print(D);
		up(mutex);
		up(a);
	end while
	
	return 0;
}
