#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ordem_crescente();
void ordem_decrescente();
int le_valida_idade(int i);

int main() {
	int i=0,j=0,c=0;
	
	struct Professor{
		char nome[20];
		int funcional;
		char titulacao[20];
	}professores[3];
	
	struct Disciplina{
		char nome[20];
		int codigo;
		int carga_horaria;
		int professor[2];
		int alunos[10][2];
		int dacc;
	}disciplinas[2];
	
	struct Aluno{
		char nome[20];
		int matricula;
		int idade;
		int disciplina;
	}alunos[15];
	
	for(i=0;i<3;i++) {
		printf("Professor %d\n",i+1);
		printf("\n");
		printf("insira o nome do professor: ");
		fflush(stdin);
		scanf("%[^\n]s",professores[i].nome);
		system("cls");
		/*
		printf("Professor %d\n",i+1);
		printf("\n");
		printf("insira a funcional(numero inteiro) do professor: ");
		fflush(stdin);
		scanf("%d",&professores[i].funcional);
		system("cls");
		*/
		professores[i].funcional = i+1;
		
		printf("Professor %d\n",i+1);
		printf("\n");
		printf("insira a titulacao do professor(especialista, mestre ou doutor): ");
		fflush(stdin);
		scanf("%[^\n]s",professores[i].titulacao);
		system("cls");
	}
	
	for(i=0;i<2;i++) {
		printf("Disciplina %d\n",i+1);
		printf("\n");
		printf("insira o nome da disciplina: ");
		fflush(stdin);
		scanf("%[^\n]s",disciplinas[i].nome);
		system("cls");
		/*
		printf("Disciplina %d\n",i+1);
		printf("\n");
		printf("insira o codigo da disciplina(numero inteiro): ");
		scanf("%d",&disciplinas[i].codigo);
		system("cls");
		*/
		disciplinas[i].codigo = i+1;
		
		printf("Disciplina %d\n",i+1);
		printf("\n");
		printf("insira a carga horaria da disciplina: ");
		scanf("%d",&disciplinas[i].carga_horaria);
		system("cls");
		
		int a = 0;
		do{
			printf("Disciplina %d\n",i+1);
			printf("\n");
			for(j=0;j<3;j++){
				printf(" %d-%s[%d]",j+1,professores[j].nome,professores[j].funcional);
				if(professores[j].funcional == disciplinas[0].professor[1]){
					printf(" - %s",disciplinas[0].nome);
				}
				printf("\n");
			}
			printf("insira o indice do professor: ");
			scanf("%d",&a);
			system("cls");
		}while(a<1 || a>3);
		
		disciplinas[i].professor[0] = a-1;
		disciplinas[i].professor[1] = professores[a-1].funcional;
		disciplinas[i].dacc = 0;
	}
	
	for(i=0;i<15;i++) {
		printf("Aluno %d\n",i+1);
		printf("\n");
		printf("insira o nome do aluno: ");
		fflush(stdin);
		scanf("%[^\n]s",alunos[i].nome);
		system("cls");
		/*
		printf("Aluno %d\n",i+1);
		printf("\n");
		printf("insira a matricula(numero inteiro) do aluno: ");
		scanf("%d",&alunos[i].matricula);
		alunos[i].matricula = i+1;
		system("cls");
		*/
		alunos[i].matricula = i+1;
		
		alunos[i].idade = le_valida_idade(i);
		
		int a = 0;
		do{
			printf("Alunos %d\n",i+1);
			printf("\n");
			for(j=0;j<2;j++){
				printf(" %d-%s[%d](%d)",j+1,disciplinas[j].nome,disciplinas[j].codigo,disciplinas[j].dacc);
				if(disciplinas[j].dacc >= 10) {
					printf("{ !!!LOTADO!!! }");
				}
				printf("\n");
			}
			printf("insira o indice da disciplina: ");
			scanf("%d",&a);
			if(disciplinas[a-1].dacc>=10) {
				a = 0;
			}
			system("cls");
		}while(a<1 || a>2);;
		alunos[i].disciplina = disciplinas[a-1].codigo;
		
		disciplinas[a-1].alunos[disciplinas[a-1].dacc][0] = alunos[i].matricula;
		disciplinas[a-1].alunos[disciplinas[a-1].dacc][1] = alunos[i].idade;
		disciplinas[a-1].dacc += 1;
	}
	
	
	// bubble sort
	ordem_crescente(disciplinas[0].alunos,disciplinas[0].dacc);
	
	ordem_decrescente(disciplinas[1].alunos,disciplinas[1].dacc);
	// imprimir o vetor de alunos da primeira disciplina
	
	
	printf("\tcodigo_disciplina\tnome_professor\tnome_estudante\tidade_estudante\n");
	for(i=0;i<disciplinas[0].dacc;i++) {
		for(j=0;j<15;j++) {
			if (alunos[j].matricula == disciplinas[0].alunos[i][0]) {
				printf("%d\t%d\t\t\t%s\t\t%s\t\t%d\n",i+1,alunos[j].disciplina,professores[disciplinas[0].professor[0]].nome,alunos[j].nome,alunos[j].idade);
				break;
			}
		}
	}
	printf("\n");
	// imprimir o vetor de alunos da segunda disciplina
	printf("\tcodigo_disciplina\tnome_professor\tnome_estudante\tidade_estudante\n");
	for(i=0;i<disciplinas[1].dacc;i++) {
		for(j=0;j<15;j++) {
			if (alunos[j].matricula == disciplinas[1].alunos[i][0]) {
				printf("%d\t%d\t\t\t%s\t\t%s\t\t%d\n",i+1,alunos[j].disciplina,professores[disciplinas[1].professor[0]].nome,alunos[j].nome,alunos[j].idade);
				break;
			}
		}
	}
	
	return 0;
}

int le_valida_idade(int i) {
	int idade=0;
	do{
		printf("Aluno %d\n",i+1);
		
		printf("insira uma idade entre 16 a 26: ");
		scanf("%d",&idade);
		system("cls");
	}while(idade<16 || idade>26);
	return idade;
}

void ordem_crescente(int alunos[][2], int dacc) {
	int i=0,j=0;
	for(i=dacc-1;i>=0;i--) {
		for(j=0;j<i;j++) {
			if (alunos[j][1] > alunos[j+1][1]) {
				alunos[j][1] += alunos[j+1][1];
				alunos[j][0] += alunos[j+1][0];
				
				alunos[j+1][1] = alunos[j][1] - alunos[j+1][1];
				alunos[j+1][0] = alunos[j][0] - alunos[j+1][0];
				
				alunos[j][1] -= alunos[j+1][1];
				alunos[j][0] -= alunos[j+1][0];
			}
		}
	}
}

void ordem_decrescente(int alunos[][2], int dacc) {
	int i=0,j=0;
	for(i=dacc-1;i>=0;i--) {
		for(j=0;j<i;j++) {
			if (alunos[j][1] < alunos[j+1][1]) {
				alunos[j][1] += alunos[j+1][1];
				alunos[j][0] += alunos[j+1][0];
				
				alunos[j+1][1] = alunos[j][1] - alunos[j+1][1];
				alunos[j+1][0] = alunos[j][0] - alunos[j+1][0];
				
				alunos[j][1] -= alunos[j+1][1];
				alunos[j][0] -= alunos[j+1][0];
			}
		}
	}
}

