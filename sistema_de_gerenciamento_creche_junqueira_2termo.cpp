/*
******* Integrantes *******
Andressa de Farias - 10442313065
Andr� de Osti Garcia Badan - 10442313851
Dayane Tiziani Boa Ventura - 10442313510
Deivid Lucas Muller Maia - 10442313486
Leonardo da Silveira Domingos - 10442313074
N�taly Lara Moraes da Silva - 10442312658 
Rafael Haddad de Lima - 10442313190
*/

//inclus�o das bibliotecas necess�rias para o funcionamento do c�digo
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<locale.h>
#include<unistd.h>//para Sleep

//in�cio das structs
typedef struct{
	int dia,mes,ano;
}data;

typedef struct{
	char nome[100], email[50], genero[20], periodo[10], habilidades[200], areaInteresse[100], finalidade[200], observacaoDoacao[100], horarioDoacao[10],horario[10];
	int codigo, status,codigoProjeto, doacaoAgendada, tipoDoacao, codigoDoacao, codigoDoador;
	float valorDoacao, horasTrabalhadas;
    char telefone[15], endereco[200], descricao[200], statusDoacao[50];
	data nascimento;                                                                                                                                                                                                                                                                                                                     
	data dataRetirada;
	data dataEntrega;
	data projetoI;
	data projetoT;
}dadosNecessarios;
//fim das structs

//in�cio das fun��es
void desenhaLinha(int tam) {
    int i;
    for(i = 0; i < tam; i++) {
        printf("_");
    }
    printf("\n\n");//pular para a pr�xima linha
} 

//todas as fun��es de busca
int busca(FILE *arquivo, int codigo) {//in�cio fun��o de busca que � utilizada dentro das demais fun��es de busca
	dadosNecessarios dados;
    rewind(arquivo);
    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo) && codigo != dados.codigo) {
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(!feof(arquivo)) {
        return ftell(arquivo) - sizeof(dadosNecessarios);
    } 
	else{
        return -1;//retorna -1 para indicar que o c�digo n�o foi encontrado
    }
}//fim da fun��o busca que � utilizada dentro das demais fun��es de busca

//fun��es utilizadas para volunt�rio 
int ordenarVoluntariosMetodoBolha(const char *nomeArquivo){//in�cio da fun��o de ordena��o com m�todo bolha
	FILE *arquivo;
    dadosNecessarios dados, dados1;
    int i, quantidade=0;
	
	arquivo = fopen(nomeArquivo, "rb+");//leitura e grava��o

    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system("pause");
        return 0;
    }
    else{
    	fseek(arquivo,0,2);//posiciona no fim do arquivo
		quantidade=ftell(arquivo)/sizeof(dadosNecessarios);//qtde de registros
		while(quantidade>1)
		{
			for(i=0;i<quantidade-1;i++)
			{
				fseek(arquivo,i*sizeof(dadosNecessarios),0);
				fread(&dados,sizeof(dadosNecessarios),1,arquivo);
				fseek(arquivo,(i+1)*sizeof(dadosNecessarios),0);
				fread(&dados1,sizeof(dadosNecessarios),1,arquivo);
				if(strcmp(dados.nome,dados1.nome)>0)
				{
					fseek(arquivo,i*sizeof(dadosNecessarios),0);
					fwrite(&dados1.nome,sizeof(dadosNecessarios),1,arquivo);
					fseek(arquivo,(i+1)*sizeof(dadosNecessarios),0);
					fwrite(&dados.nome,sizeof(dadosNecessarios),1,arquivo);
				}
			}
			quantidade--;
		}
		printf("\n Ordenando arquivo de volunt�rios...\n");
		Sleep(2000);
		system("cls");
    	printf("\n Arquivo ordenado com sucesso!\n");
		system("pause");
		system("cls");
	}
	fclose(arquivo);
}//fim da fun��o de ordena��o com m�todo bolha

int buscaPorCodigoVoluntario(const char *nomeArquivo){//in�cio fun��o busca por c�digo usada no relat�rio na op��o por c�digo
 	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos=0;
	arquivo = fopen(nomeArquivo, "rb");//leitura
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system("pause");
        return -1;
    }
    system("cls");
    printf("\n\n *Consultar por cadastro*");
    printf("\n C�digo ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da fun��o de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system("pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posi��o correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" C�digo: %d\n", dados.codigo);
            printf(" *Dados pessoais:\n");
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" G�nero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endere�o completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" *Dados sobre volunt�riado:\n");
            printf(" Per�odo de trabalho: %s\n", dados.periodo);
		    printf(" Habilidades: %s\n", dados.habilidades);
		    printf(" �rea de interesse: %s\n", dados.areaInteresse);
            printf(" Horas trabalhadas: %.2f\n", dados.horasTrabalhadas);
            printf(" -----\n\n");
            system(" pause"); //da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n C�digo ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da fun��o busca por c�digo
 
int buscaTodosCodigosVoluntario(const char *nomeArquivo){//in�cio fun��o busca todos os c�digos usado no relat�rio 
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system("pause");
        system("cls");
        return -1;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
            printf("\n C�digo: %d\n", dados.codigo);
            printf(" *Dados pessoais:\n");
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" G�nero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endere�o completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" *Dados sobre volunt�riado:\n");
            printf(" Per�odo de trabalho: %s\n", dados.periodo);
		    printf(" Habilidades: %s\n", dados.habilidades);
		    printf(" �rea de interesse: %s\n", dados.areaInteresse);
            printf(" Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
            printf("-----\n\n");
        }
         if(encontrado == 0){//c�digo n�o encontrado
			desenhaLinha(32); 
			printf(" Nenhum cadastro de volunt�rio!\n");
			desenhaLinha(32);	   
		}
        fclose(arquivo);
    }
    system("pause");
    system("cls");
}//fim da fun��o busca todos os c�digos

void buscaTodosCodigosExclusaoVoluntario(const char *nomeArquivo) {//in�cio da fun��o de busca ap�s a exclus�o
    FILE *arquivo = fopen(nomeArquivo, "rb");
    dadosNecessarios dados;
	int encontrado=0;
    if(arquivo == NULL) {
        printf(" Erro ao abrir o arquivo.\n");
        return;
    }
    printf("\n\n*** CADASTRO(S) RESTANTE(S) ***\n");

    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo)) {
    	encontrado=1;
        printf(" C�digo: %d\n", dados.codigo);
        printf(" *Dados pessoais:\n");
        printf(" Nome: %s\n",dados.nome);
	    printf(" Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
	    printf(" G�nero: %s\n", dados.genero);
	    printf(" Telefone: %s\n",dados.telefone);
	    printf(" Endere�o completo: %s\n",dados.endereco);
	    printf(" E-mail: %s\n", dados.email);
	    printf(" *Dados sobre volunt�riado:\n");
	    printf(" Per�odo de trabalho: %s\n", dados.periodo);
	    printf(" Habilidades: %s\n", dados.habilidades);
	    printf(" �rea de interesse: %s\n", dados.areaInteresse);
	    printf(" Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
		printf(" -----\n\n");

        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(encontrado == 0){//c�digo n�o encontrado
		desenhaLinha(32); 
		printf(" Nenhum cadastro de volunt�rio!\n");
		desenhaLinha(32);	   
	}
    fclose(arquivo);
    system(" pause");
    system("cls");
}//fim da fun��o de busca ap�s a exclus�o

int cadastrarVoluntario(const char *nomeArquivo){//in�cio da fun��o de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizado  para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo n�o pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			printf(" C�digo: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//fun��o de busca
			
			if(pos == -1){//c�digo n�o encontrado e vai cadastrar
			  	dados.codigo = codigo;
				printf(" *Dados pessoais:\n");
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Data nascimento (xx xx xxxx): ");
				scanf("%d %d %d",&dados.nascimento.dia,&dados.nascimento.mes,&dados.nascimento.ano);
				
				printf(" Masculino/feminino/outro): "); 
				fflush(stdin);
				gets(dados.genero);
				
				printf(" Telefone(XX XXXXX-XXXX):"); 
				fflush(stdin);
				gets(dados.telefone);
				
				printf(" Endere�o completo: ");
				fflush(stdin);
				gets(dados.endereco);
				
				printf(" E-mail: ");
				fflush(stdin);
				gets(dados.email);
				
				printf(" *Dados sobre volunt�riado:\n");
			
				printf(" Periodo de trabalho (manh�/tarde/noite): ");
				fflush(stdin);
				gets(dados.periodo);
				
				printf(" Habilidades: ");
				fflush(stdin);
				gets(dados.habilidades);
				
				printf(" Area de interesse: ");
				fflush(stdin);
				gets(dados.areaInteresse);
				
				printf("\n Se j� tiver horas trabalhadas pode colocar, se n�o tiver coloca 0: "); 
				scanf("%f",&dados.horasTrabalhadas);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system("pause");
			}  
			else{//c�digo encontrado
				desenhaLinha(47); 
				printf(" Este c�digo j� est� vinculado a um cadastro!\n");
				desenhaLinha(47);
				system(" pause");	   
			}
			system("cls");
			printf("\n\n Fazer outro cadastro? (S/N): ");
			scanf(" %c", &opcao);
					
		}while(opcao == 'S' || opcao == 's');
	}
	system("cls");
  	fclose(arquivo);
	return 1;	
}//fim da fun��o de cadastro

int relatorioVoluntario(const char *nomeArquivo) {//in�cio da fun��o de relat�rio
    int op;
    system("cls");
    printf("\n *Relat�rio*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Op��o: ");
    scanf("%d", &op);
    system("cls");

    while(op != 0) {
        if(op == 1) {
            buscaPorCodigoVoluntario(nomeArquivo);
        } 
		 if(op == 2) {
            buscaTodosCodigosVoluntario(nomeArquivo);
        } 
		if(op < 0 || op > 2) {
            system("cls");
            desenhaLinha(50);
            printf("     Op��o inv�lida! Escolha outra op��o.\n");
            desenhaLinha(50);
        }
        printf("\n *Relat�rio*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Op��o: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relat�rio foi gerado com sucesso
} //fim da fun��o de relat�rio

int editarVoluntario(const char *nomeArquivo){//in�cio da fun��o editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	system("cls");
	
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	do{
		system("cls");
		printf("\n\n *Editar*");
		printf("\n C�digo do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if (codigo == 0) {
            break;//sai do loop se o c�digo for zero
        }
	
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				//fseek(arquivo,pos,0);//para posicionar o novo arquivo e escrever o novo dado/pre�o, isso usa para editar ver se precisa deixar pra relat�rio e verifica��os e j� existe
				//fread(&dados,sizeof(dadosNecessarios),1,arquivo);
				printf("\n\n *** EDI��O DE DADOS ***\n");
				printf(" C�digo: %d\n",dados.codigo);
				printf(" *Dados pessoais:\n");
			    printf(" A- Nome: %s\n",dados.nome);
			    printf(" B- Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
			    printf(" C- G�nero: %s\n", dados.genero);
			    printf(" D- Telefone: %s\n",dados.telefone);
			    printf(" E- Endere�o completo: %s\n",dados.endereco);
			    printf(" F- E-mail: %s\n", dados.email);
			    printf(" *Dados sobre volunt�riado\n");
			    printf(" G- Per�odo de trabalho: %s\n", dados.periodo);
			    printf(" H- Habilidades: %s\n", dados.habilidades);
			    printf(" I- �rea de interesse: %s\n", dados.areaInteresse);
			    printf(" Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
				printf(" -----\n\n");
			
			    printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
					
					do{
						printf("\n Qual a op��o que deseja editar?: ");
						scanf(" %c",&opAlterar);
						opAlterar = toupper(opAlterar);
						
						switch (opAlterar) {
					        case 'A':
					            printf("\n *Alterar nome*\n");
					            printf(" Informe o novo nome: ");
					            fflush(stdin);
					            gets(dados.nome);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'B':
					            printf("\n *Alterar Data Nascimento*\n");
					            printf(" Nova Data Nascimento(xx xx xxxx): ");
					            scanf("%d %d %d", &dados.nascimento.dia, &dados.nascimento.mes, &dados.nascimento.ano);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'C':
					            printf("\n *Alterar G�nero*\n");
					            printf(" Novo G�nero: ");
					            fflush(stdin);
					            gets(dados.genero);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'D':
					            printf("\n *Alterar Telefone*\n");
					            printf(" Novo Telefone: ");
					            fflush(stdin);
					            gets(dados.telefone);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'E':
					            printf("\n *Alterar Endere�o*\n");
					            printf(" Novo Endere�o: ");
					            fflush(stdin);
					            gets(dados.endereco);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'F':
					            printf("\n *Alterar E-mail*\n");
					            printf(" Novo E-mail: ");
					            fflush(stdin);
					            gets(dados.email);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'G':
					            printf("\n *Alterar Per�odo de trabalho*\n");
					            printf(" Novo Per�odo de trabalho(manh�/tarde/noite): ");
					            fflush(stdin);
					            gets(dados.periodo);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'H':
					            printf("\n *Alterar Habilidades*\n");
					            printf(" Novo Habilidades: ");
					            fflush(stdin);
					            gets(dados.habilidades);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'I':
					            printf("\n *Alterar �rea de interesse*\n");
					            printf(" Novo �rea de interesse: ");
					            fflush(stdin);
					            gets(dados.areaInteresse);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        default:
					        	desenhaLinha(34);
					            printf(" Op��o inv�lida. Tente novamente.\n");
					            desenhaLinha(34);
					    }
					    
					} while (opAlterar < 'A' || opAlterar > 'I');
					
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
					
					printf("\n Deseja editar outra op��o neste cadastro? (S/N): ");
					scanf(" %c", &continuarEdicao);			
				}
				 
            }while(continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}	
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da fun��o editar

int excluirVoluntario(const char *nomeArquivo) {//in�cio da fun��o excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura bin�ria
    	 if(arquivo == NULL) {
            //verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n C�digo do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama fun��o de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro n�o encontrado!\n");
	            desenhaLinha(28);
	            system("pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo ap�s a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita bin�ria
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
	                    printf(" *Dados pessoais:\n");
						printf(" C�digo: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
					    printf(" G�nero: %s\n", dados.genero);
					    printf(" Telefone: %s\n",dados.telefone);
					    printf(" Endere�o completo: %s\n",dados.endereco);
					    printf(" E-mail: %s\n", dados.email);
					    printf(" *Dados sobre volunt�riado:\n");
					    printf(" Per�odo de trabalho: %s\n", dados.periodo);
					    printf(" Habilidades: %s\n", dados.habilidades);
					    printf(" �rea de interesse: %s\n", dados.areaInteresse);
						printf("\n Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
						printf(" -----\n\n");
						
						if(dados.horasTrabalhadas > 0.001){
							desenhaLinha(70);
				            printf(" Este cadastro n�o pode ser exclu�do. Ele possui horas trabalhadas!\n");
				            desenhaLinha(70);
				            system(" pause");
				            system("cls");
				            marcador =0;
						}
	                    else{//confirma��o para excluir
		                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");
		                    confirmacao = toupper(getch());
						    if(confirmacao == 'S') {
								marcador=1;
		                        printf("\n\n Excluindo cadastro...\n");
		                        Sleep(2000);
		                        system("cls");
		                    }
							else {
		                        printf("\n\n Opera��o cancelada. Cadastro n�o ser� exclu�do\n");
		                        system(" pause");
		                        system("cls");
		                	}
		            	}
	            	}
					fread(&dados, sizeof(dadosNecessarios), 1, arquivo);	
	        	}
	        	fclose(arquivo);
	            fclose(temp);
	            
				if(marcador == 1){
					remove(nomeArquivo);
	            	rename("arquivoTemporario.bin", nomeArquivo);
					printf("\n Exclus�o realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoVoluntario(nomeArquivo);//mostra os cadastros restantes ap�s a exclus�o
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a op��o n�o for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da fun��o excluir

int lancarHoras(const char *nomeArquivo) {//in�cio da fun��o lan�ar horas para voluntarios
    FILE *arquivo;
    dadosNecessarios dados;
    int codigo, pos;
    float horasLancadas;

    system("cls");
    printf("\n *Lan�ar Horas*\n");
    printf(" Informe o c�digo do volunt�rio: ");
    scanf("%d", &codigo);

    arquivo = fopen(nomeArquivo, "rb+");//leitura e grava��o

    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return 0;
    }
    pos = busca(arquivo, codigo);

    if(pos == -1) {
        desenhaLinha(28);
        printf("  Volunt�rio n�o encontrado!\n");
        desenhaLinha(28);
        system("pause");
        fclose(arquivo);
        return 0;
    }
    fseek(arquivo, pos, SEEK_SET);
    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);

    printf("\n Horas trabalhadas atualmente: %.2f hora(s)\n", dados.horasTrabalhadas);
    printf(" Informe as horas a serem lan�adas: ");
    scanf("%f", &horasLancadas);

    //adiciona as novas horas �s horas j� existentes
    dados.horasTrabalhadas += horasLancadas;

    fseek(arquivo, pos, SEEK_SET);
    fwrite(&dados, sizeof(dadosNecessarios), 1, arquivo);

    printf("\n Horas lan�adas com sucesso!\n");
    system(" pause");
    system("cls");
	fclose(arquivo);
	
	return 1;	
}//fim da fun��o lan�ar horas para voluntarios
//fim das fun��es utilizadas para volunt�rio

void executandoOpcao1(){//in�cio da fun�ao executandoOpcao1, usado apenas para gerenciar volunt�rios pq tem a fun��o lan�ar horas
	int opcao1, op;
	do{	
		
		printf("\n *Gerenciar Volunt�rios*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Lan�ar horas\n");
		printf(" 3-Editar\n");
		printf(" 4-Excluir\n");
		printf(" 5-Ordenar\n");
		printf(" 6-Relat�rio\n");
		printf(" 0-Retornar\n");
		printf(" Op��o: ");
		scanf("%d",&opcao1);

		if(opcao1 == 1){
			printf("\n *Cadastrar Volunt�rio*\n");
			cadastrarVoluntario("arquivoVoluntario.bin");				
		}
		if(opcao1 == 2){
			printf("\n *Lan�ar horas*\n");
			lancarHoras("arquivoVoluntario.bin");		
		}
		if(opcao1 == 3){
			printf("\n *Editar Volunt�rio*\n");
			editarVoluntario("arquivoVoluntario.bin");
		}
		if(opcao1 == 4){
			printf("\n *Excluir Volunt�rio*\n");
			excluirVoluntario("arquivoVoluntario.bin");
		}
		if(opcao1 == 5){
			printf("\n *Ordenar Volunt�rios*\n");
			system("cls");
			ordenarVoluntariosMetodoBolha("arquivoVoluntario.bin");
		}
		if(opcao1 == 6){
			printf("\n *Relat�rio*\n");
			relatorioVoluntario("arquivoVoluntario.bin");
		}
		if(opcao1 < 0 || opcao1 > 6){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
	}while(opcao1 != 0);
	system("cls");
}//fim da fun�ao executandoOpcao1 gerenciar volunt�rios                           

//fun��es utilizadas para doador
int buscaPorCodigoDoador(const char *nomeArquivo){//in�cio fun��o busca por c�digo usada no relat�rio na op��o por c�digo
 	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos=0;
	arquivo = fopen(nomeArquivo, "rb");//leitura
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    }
    system("cls");
    printf("\n\n *Consultar por Doador*");
    printf("\n C�digo ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da fun��o de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posi��o correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" G�nero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endere�o completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" -----\n");
            getch();//da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por Doador*");
        printf("\n C�digo ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da fun��o busca por c�digo
 
int buscaTodosCodigosDoador(const char *nomeArquivo){//in�cio fun��o busca todos os c�digos usado no relat�rio ap�s excluir
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
            printf("\n C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" G�nero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endere�o completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf("-----\n");
        }
        if(encontrado == 0){//c�digo n�o encontrado
			desenhaLinha(28); 
			printf(" Nenhum cadastro de doador!\n");
			desenhaLinha(28);	   
		}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca todos os c�digos

void buscaTodosCodigosExclusaoDoador(const char *nomeArquivo) {//in�cio da fun��o de busca ap�s a exclus�o
    FILE *arquivo = fopen(nomeArquivo, "rb");
    dadosNecessarios dados;
    int encontrado=0;

    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    printf("\n\n*** CADASTRO(S) RESTANTE(S) ***\n");

    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo)) {
        encontrado=1;
		printf("\n C�digo: %d\n", dados.codigo);
        printf(" A- Nome: %s\n",dados.nome);
	    printf(" B- Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
	    printf(" C- G�nero: %s\n", dados.genero);
	    printf(" D- Telefone: %s\n",dados.telefone);
	    printf(" E- Endere�o completo: %s\n",dados.endereco);
	    printf(" F- E-mail: %s\n", dados.email);
		printf(" -----\n");

        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(encontrado == 0){//c�digo n�o encontrado
		desenhaLinha(28); 
		printf(" Nenhum cadastro de doador!\n");
		desenhaLinha(28);	   
	}
    
    fclose(arquivo);
    system(" pause");
    system("cls");
}//fim da fun��o de busca ap�s a exclus�o

int cadastrarDoador(const char *nomeArquivo){//in�cio da fun��o de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando  para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo n�o pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" C�digo: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//fun��o de busca
			
			if(pos == -1){//c�digo n�o encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Data nascimento (xx xx xxxx): ");
				scanf("%d %d %d",&dados.nascimento.dia,&dados.nascimento.mes,&dados.nascimento.ano);
				
				printf(" Masculino/feminino/outro): "); 
				fflush(stdin);
				gets(dados.genero);
				
				printf(" Telefone(XX XXXXX-XXXX):"); 
				fflush(stdin);
				gets(dados.telefone);
				
				printf(" Endere�o completo: ");
				fflush(stdin);
				gets(dados.endereco);
				
				printf(" E-mail: ");
				fflush(stdin);
				gets(dados.email);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system(" pause");
				
			}  
			else{//c�digo encontrado
				desenhaLinha(46); 
				printf(" Este c�digo j� est� vinculado a um cadastro!\n");
				desenhaLinha(46);
				system(" pause");	   
			}
			system("cls");
			printf("\n Fazer outro cadastro?? (S/N): ");
			scanf(" %c", &opcao);
					
		}while(opcao == 'S' || opcao == 's');
	}
	system("cls");
  	fclose(arquivo);
	return 1;	
}//fim da fun��o de cadastro

int relatorioDoador(const char *nomeArquivo) {//in�cio da fun��o de relat�rio
    int op;
    system("cls");
    printf("\n *Relat�rio*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Op��o: ");
    scanf("%d", &op);
    system("cls");

    while(op != 0) {
        if(op == 1) {
            buscaPorCodigoDoador(nomeArquivo);
        } 
		 if(op == 2) {
            buscaTodosCodigosDoador(nomeArquivo);
        } 
		if(op < 0 || op > 2) {
            system("cls");
            desenhaLinha(50);
            printf("     Op��o inv�lida! Escolha outra op��o.\n");
            desenhaLinha(50);
        }
        printf("\n *Relat�rio*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Op��o: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relat�rio foi gerado com sucesso
}//fim da fun��o de relat�rio

int editarDoador(const char *nomeArquivo){//in�cio da fun��o editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	system("cls");
	
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	do{
		system("cls");
		printf("\n\n *Editar*");
		printf("\n C�digo do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if(codigo == 0) {
            break;//sai do loop se o c�digo for zero
        }
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDI��O DE DADOS ***\n");
				printf(" C�digo: %d\n",dados.codigo);
			    printf(" A- Nome: %s\n",dados.nome);
			    printf(" B- Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
			    printf(" C- G�nero: %s\n", dados.genero);
			    printf(" D- Telefone: %s\n",dados.telefone);
			    printf(" E- Endere�o completo: %s\n",dados.endereco);
			    printf(" F- E-mail: %s\n", dados.email);
				printf(" -----\n");
				
				printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
				
					do{
						printf("\n Qual a op��o que deseja editar?: ");
					    scanf(" %c", &opAlterar);
					    opAlterar = toupper(opAlterar);
					
						switch (opAlterar) {
					        case 'A':
					            printf("\n *Alterar nome*\n");
					            printf(" Informe o novo nome: ");
					            fflush(stdin);
					            gets(dados.nome);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'B':
					            printf("\n *Alterar Data Nascimento*\n");
					            printf(" Nova Data Nascimento(xx xx xxxx): ");
					            scanf("%d %d %d", &dados.nascimento.dia, &dados.nascimento.mes, &dados.nascimento.ano);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'C':
					            printf("\n *Alterar G�nero*\n");
					            printf(" Novo G�nero: ");
					            fflush(stdin);
					            gets(dados.genero);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'D':
					            printf("\n *Alterar Telefone*\n");
					            printf(" Novo Telefone: ");
					            fflush(stdin);
					            gets(dados.telefone);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'E':
					            printf("\n *Alterar Endere�o*\n");
					            printf(" Novo Endere�o: ");
					            fflush(stdin);
					            gets(dados.endereco);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'F':
					            printf("\n *Alterar E-mail*\n");
					            printf(" Novo E-mail: ");
					            fflush(stdin);
					            gets(dados.email);
					            printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
					            break;
					
					        default:
					        	desenhaLinha(34);
					            printf(" Op��o inv�lida. Tente novamente.\n");
					            desenhaLinha(34);
					    }
					    
					}while (opAlterar < 'A' || opAlterar > 'F');	
				 	
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
					
					printf("\n Deseja editar outra op��o neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				}
            }while (continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}	
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da fun��o editar

int excluirDoador(const char *nomeArquivo) {//in�cio da fun��o excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura bin�ria
    	 if (arquivo == NULL) {//verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
		printf("\n\n *Excluir*");
	    printf("\n C�digo do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama fun��o de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro n�o encontrado!\n");
	            desenhaLinha(28);
	            system(" pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo ap�s a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita bin�ria
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" C�digo: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
					    printf(" G�nero: %s\n", dados.genero);
					    printf(" Telefone: %s\n",dados.telefone);
					    printf(" Endere�o completo: %s\n",dados.endereco);
					    printf(" E-mail: %s\n", dados.email);
						printf(" -----\n");
						
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");//confirma��o para excluir
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Opera��o cancelada. Cadastro n�o ser� exclu�do\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);//se n�o confirmado, escreva de volta no arquivo
	                        system("pause");
							system("cls");
	                	}
	            	}
					fread(&dados, sizeof(dadosNecessarios), 1, arquivo);	
	        	}
	        	fclose(arquivo);
	            fclose(temp);
	            remove(nomeArquivo);
	            rename("arquivoTemporario.bin", nomeArquivo);
				
				if(marcador == 1){
					printf("\n Exclus�o realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoDoador(nomeArquivo);//mostra os cadastros restantes ap�s a exclus�o
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a op��o n�o for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da fun��o excluir
//fim das fun��es utilizadas para doador 

void executandoOpcao2(){//in�cio da fun�ao executandoOpcao2, usado apenas para gerenciar Doadores
	int opcao, op;
	do{		
		printf("\n *Gerenciar Doadores*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Relat�rio\n");
		printf(" 0-Retornar\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);

		if(opcao == 1){
			printf("\n *Cadastrar Doador*\n");
			cadastrarDoador("arquivoDoador.bin");				
		}
		if(opcao == 2){
			printf("\n *Editar Doador*\n");
			editarDoador("arquivoDoador.bin");
		}
		if(opcao == 3){
			printf("\n *Excluir Doador*\n");
			excluirDoador("arquivoDoador.bin");
		}
		if(opcao == 4){
			printf("\n *Relat�rio*\n");
			relatorioDoador("arquivoDoador.bin");
		}
		if(opcao < 0 || opcao > 4){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da fun�ao executandoOpcao2, usado apenas para gerenciar Doadores

//in�cio das fun��es utilizadas para Empresa
int buscaPorCodigoEmpresa(const char *nomeArquivo){//in�cio fun��o busca por c�digo usada no relat�rio na op��o por c�digo
 	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos=0;
	arquivo = fopen(nomeArquivo, "rb");//leitura
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    }
    system("cls");
    printf("\n\n *Consultar por cadastro*");
    printf("\n C�digo ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da fun��o de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posi��o correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endere�o completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" -----\n");
            getch();//da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n C�digo ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da fun��o busca por c�digo
 
int buscaTodosCodigosEmpresa(const char *nomeArquivo){//in�cio fun��o busca todos os c�digos usado no relat�rio ap�s excluir
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Esse arquivo ainda n�o existe\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
        while (fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
            printf("\n C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endere�o completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf("-----\n");
            
        }
        if(encontrado == 0){//c�digo n�o encontrado
			desenhaLinha(32); 
			printf(" Nenhum cadastro de empresa!\n");
			desenhaLinha(32);	   
		}
        fclose(arquivo);
    }
	system(" pause");
    system("cls");
}//fim da fun��o busca todos os c�digos

void buscaTodosCodigosExclusaoEmpresa(const char *nomeArquivo) {//in�cio da fun��o de busca ap�s a exclus�o
    FILE *arquivo = fopen(nomeArquivo, "rb");
    dadosNecessarios dados;
	int encontrado=0;
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    printf("\n\n*** CADASTRO(S) RESTANTE(S) ***\n");

    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo)) {
    	encontrado=1;
        printf(" C�digo: %d\n", dados.codigo);
        printf(" Nome: %s\n",dados.nome);
	    printf(" Telefone: %s\n",dados.telefone);
	    printf(" Endere�o completo: %s\n",dados.endereco);
	    printf(" E-mail: %s\n", dados.email);
		printf(" -----\n");
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
        
    }
    if(encontrado == 0){//c�digo n�o encontrado
		desenhaLinha(32); 
		printf(" Nenhum cadastro de empresa!\n");
		desenhaLinha(32);	   
	}
    fclose(arquivo);
	system(" pause");
    system("cls");
}//fim da fun��o de busca ap�s a exclus�o

int cadastrarEmpresa(const char *nomeArquivo){//in�cio da fun��o de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo n�o pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" C�digo: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//fun��o de busca
			
			if(pos == -1){//c�digo n�o encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Telefone(XX XXXXX-XXXX):"); 
				fflush(stdin);
				gets(dados.telefone);
				
				printf(" Endere�o completo: ");
				fflush(stdin);
				gets(dados.endereco);
				
				printf(" E-mail: ");
				fflush(stdin);
				gets(dados.email);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system("pause");
			}  
			else{//c�digo encontrado
				desenhaLinha(40); 
				printf(" Este c�digo j� est� vinculado a um cadastro!\n");
				desenhaLinha(40);
				system(" pause");	   
			}
			system("cls");
			printf("\n\n Fazer outro cadastro? (S/N): ");
			scanf(" %c", &opcao);
					
		}while(opcao == 'S' || opcao == 's');
	}
	system("cls");
  	fclose(arquivo);
	return 1;	
}//fim da fun��o de cadastro

int relatorioEmpresa(const char *nomeArquivo) {//in�cio da fun��o de relat�rio
    int op;
    system("cls");
    printf("\n *Relat�rio*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Op��o: ");
    scanf("%d", &op);
    system("cls");

    while(op != 0) {
        if(op == 1) {
            buscaPorCodigoEmpresa(nomeArquivo);
        } 
		 if(op == 2) {
            buscaTodosCodigosEmpresa(nomeArquivo);
        } 
		if(op < 0 || op > 2) {
            system("cls");
            desenhaLinha(50);
            printf("     Op��o inv�lida! Escolha outra op��o.\n");
            desenhaLinha(50);
        }
        printf("\n *Relat�rio*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Op��o: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relat�rio foi gerado com sucesso
}//fim da fun��o de relat�rio

int editarEmpresa(const char *nomeArquivo){//in�cio da fun��o editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	system("cls");
	
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
        system("cls");
		return 0;//encerra o programa
	}
	do{
		system("cls");
		printf("\n\n *Editar*");
		printf("\n C�digo do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if(codigo == 0) {
            break;//sai do loop se o c�digo for zero
        }
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDI��O DE DADOS ***\n");
				printf(" C�digo: %d\n",dados.codigo);
			    printf(" A- Nome: %s\n",dados.nome);
			    printf(" B- Telefone: %s\n",dados.telefone);
			    printf(" C- Endere�o completo: %s\n",dados.endereco);
			    printf(" D- E-mail: %s\n", dados.email);
				printf(" -----\n");
			
				printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
					do {
				        printf("\n Qual a op��o que deseja editar?: ");
				        scanf(" %c", &opAlterar);
				        opAlterar = toupper(opAlterar);
				
				        switch (opAlterar) {
				            case 'A':
				                printf("\n *Alterar nome*\n");
				                printf(" Informe o novo nome: ");
				                fflush(stdin);
				                gets(dados.nome);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'B':
				                printf("\n *Alterar Telefone*\n");
				                printf(" Novo Telefone: "); 
				                fflush(stdin);
				                gets(dados.telefone);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system("pause");
				                break;
				
				            case 'C':
				                printf("\n *Alterar Endere�o*\n");
				                printf(" Novo Endere�o: "); 
				                fflush(stdin);
				                gets(dados.endereco);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'D':
				                printf("\n *Alterar E-mail*\n");
				                printf(" Novo E-mail: "); 
				                fflush(stdin);
				                gets(dados.email);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            default:
				            	desenhaLinha(34);
				                printf(" Op��o inv�lida. Tente novamente.\n");
				                desenhaLinha(34);
				        }
				    } while (opAlterar < 'A' || opAlterar > 'D');
					
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
					
					printf("\n Deseja editar outra op��o neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				}
            }while(continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}		
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da fun��o editar

int excluirEmpresa(const char *nomeArquivo) {//in�cio da fun��o excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura bin�ria
    	 if (arquivo == NULL) {// Verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n C�digo do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama fun��o de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro n�o encontrado!\n");
	            desenhaLinha(28);
	            system("pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            system("cls");
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo ap�s a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita bin�ria
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" C�digo: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Telefone: %s\n",dados.telefone);
					    printf(" Endere�o completo: %s\n",dados.endereco);
					    printf(" E-mail: %s\n", dados.email);
						printf(" -----\n");
						
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");//confirma��o para excluir
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Opera��o cancelada. Cadastro n�o ser� exclu�do\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);//se n�o confirmado, escreva de volta no arquivo
	                        system(" pause");
							system("cls");
	                	}
	            	}
					fread(&dados, sizeof(dadosNecessarios), 1, arquivo);	
	        	}
	        	fclose(arquivo);
	            fclose(temp);
	            remove(nomeArquivo);
	            rename("arquivoTemporario.bin", nomeArquivo);
				
				if(marcador == 1){
					printf("\n Exclus�o realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoEmpresa(nomeArquivo);//mostra os cadastros restantes ap�s a exclus�o
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a op��o n�o for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da fun��o excluir

//fim das fun��es utilizadas para empresas

void executandoOpcao3(){//in�cio da fun�ao executandoOpcao3, usado apenas para gerenciar Empresas
	int opcao, op;
	do{		
		printf("\n *Gerenciar Empresas*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Relat�rio\n");
		printf(" 0-Retornar\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);

		if(opcao == 1){
			printf("\n *Cadastrar Empresa*\n");
			cadastrarEmpresa("arquivoEmpresa.bin");				
		}
		if(opcao == 2){
			printf("\n *Editar Empresa*\n");
			editarEmpresa("arquivoEmpresa.bin");
		}
		if(opcao == 3){
			printf("\n *Excluir Empresa*\n");
			excluirEmpresa("arquivoEmpresa.bin");
		}
		if(opcao == 4){
			printf("\n *Relat�rio*\n");
			relatorioEmpresa("arquivoEmpresa.bin");
		}
		if(opcao < 0 || opcao > 4){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da fun�ao executandoOpcao3, usado apenas para gerenciar Empresas

//in�cio das fun��es utilizadas para Projeto
int buscaPorCodigoProjeto(const char *nomeArquivo){//in�cio fun��o busca por c�digo usada no relat�rio na op��o por c�digo
 	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos=0;
	arquivo = fopen(nomeArquivo, "rb"); 
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    }
    system("cls");
    printf("\n\n *Consultar por cadastro*");
    printf("\n C�digo ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da fun��o de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posi��o correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Finalidade: %s\n", dados.finalidade);
            printf(" Data In�cio: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
            printf(" Data T�rmino prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
            printf(" -----\n");
            getch();//da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n C�digo ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da fun��o busca por c�digo
 
int buscaTodosCodigosProjeto(const char *nomeArquivo){//in�cio fun��o busca todos os c�digos usado no relat�rio ap�s excluir
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
            printf("\n C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Finalidade: %s\n", dados.finalidade);
            printf(" Data In�cio: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
            printf(" Data T�rmino prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
            printf("-----\n");
        }
         if(encontrado == 0){//c�digo n�o encontrado
			desenhaLinha(32); 
			printf(" Nenhum cadastro de empresa!\n");
			desenhaLinha(32);	   
		}
        fclose(arquivo);
	}
	system(" pause");
    system("cls");
}//fim da fun��o busca todos os c�digos

void buscaTodosCodigosExclusaoProjeto(const char *nomeArquivo) {//in�cio da fun��o de busca ap�s a exclus�o
    FILE *arquivo = fopen(nomeArquivo, "rb");
    int encontrado=0;
    dadosNecessarios dados;

    if(arquivo == NULL) {
        printf(" Erro ao abrir o arquivo.\n");
        return;
    }
    printf("\n\n*** CADASTRO(S) RESTANTE(S) ***\n");

    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo)) {
    	encontrado=1;
        printf(" C�digo: %d\n", dados.codigo);
        printf(" Nome: %s\n", dados.nome);
        printf(" Finalidade: %s\n", dados.finalidade);
        printf(" Data In�cio: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
        printf(" Data T�rmino prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
		printf(" -----\n");
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
     if(encontrado == 0){//c�digo n�o encontrado
		desenhaLinha(32); 
		printf(" Nenhum cadastro de empresa!\n");
		desenhaLinha(32);	   
	}
    fclose(arquivo);
	system(" pause");
    system("cls");
}//fim da fun��o de busca ap�s a exclus�o

int cadastrarProjeto(const char *nomeArquivo){//in�cio da fun��o de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando  para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo n�o pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" C�digo: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//fun��o de busca
			
			if(pos == -1){//c�digo n�o encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Finalidade: "); 
				fflush(stdin); 
				gets(dados.finalidade);
				
				printf(" Data In�cio(xx xx xxxx): "); 
				scanf("%d %d %d",&dados.projetoI.dia,&dados.projetoI.mes,&dados.projetoI.ano);
				
				printf(" Data T�rmino prevista(xx xx xxxx): "); 
				scanf("%d %d %d",&dados.projetoT.dia,&dados.projetoT.mes,&dados.projetoT.ano);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system("pause");
			}  
			else{//c�digo encontrado
				desenhaLinha(40); 
				printf(" Este c�digo j� est� vinculado a um cadastro!\n");
				desenhaLinha(40);
				system("pause");	   
			}
			system("cls");
			printf("\n\n Fazer outro cadastro? (S/N): ");
			scanf(" %c", &opcao);
					
		}while(opcao == 'S' || opcao == 's');
	}
	system("cls");
  	fclose(arquivo);
	return 1;	
}//fim da fun��o de cadastro

int relatorioProjeto(const char *nomeArquivo){//in�cio da fun��o de relat�rio
    int op;
    system("cls");
    printf("\n *Relat�rio*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Op��o: ");
    scanf("%d", &op);
    system("cls");

    while(op != 0) {
        if(op == 1) {
            buscaPorCodigoProjeto(nomeArquivo);
        } 
		 if(op == 2) {
            buscaTodosCodigosProjeto(nomeArquivo);
        } 
		if(op < 0 || op > 2) {
            system("cls");
            desenhaLinha(50);
            printf("     Op��o inv�lida! Escolha outra op��o.\n");
            desenhaLinha(50);
        }
        printf("\n *Relat�rio*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Op��o: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relat�rio foi gerado com sucesso
}//fim da fun��o de relat�rio

int editarProjeto(const char *nomeArquivo){//in�cio da fun��o editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	system("cls");
	
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	do{
		system("cls");
		printf("\n\n *Editar*");
		printf("\n C�digo do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if (codigo == 0) {
            break; //sai do loop se o c�digo for zero
        }
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDI��O DE DADOS ***\n");
				printf(" C�digo: %d\n", dados.codigo);
		        printf(" A- Nome: %s\n", dados.nome);
		        printf(" B- Finalidade: %s\n", dados.finalidade);
		        printf(" C- Data In�cio: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
		        printf(" D- Data T�rmino prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
				printf(" -----\n");
			    
			    printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
				
					do {
				        printf("\n Qual a op��o que deseja editar?: ");
				        scanf(" %c", &opAlterar);
				        opAlterar = toupper(opAlterar);
				
				        switch (opAlterar) {
				            case 'A':
				                printf("\n *Alterar Nome*\n");
				                printf(" Informe o novo nome: ");
				                fflush(stdin);
				                gets(dados.nome);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'B':
				                printf("\n *Alterar Finalidade*\n");
				                printf(" Informe a nova finalidade: ");
				                fflush(stdin);
				                gets(dados.finalidade);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'C':
				                printf("\n *Alterar Data In�cio*\n");
				                printf(" Nova Data In�cio(xx xx xxxx): ");
				                scanf("%d %d %d", &dados.projetoI.dia, &dados.projetoI.mes, &dados.projetoI.ano);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'D':
				                printf("\n *Alterar Data T�rmino prevista*\n");
				                printf(" Nova Data T�rmino prevista(xx xx xxxx): ");
				                scanf("%d %d %d", &dados.projetoT.dia, &dados.projetoT.mes, &dados.projetoT.ano);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            default:
				                desenhaLinha(34);
					            printf(" Op��o inv�lida. Tente novamente.\n");
					            desenhaLinha(34);
				        }
				    } while (opAlterar < 'A' || opAlterar > 'D');
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
					
					printf("\n Deseja editar outra op��o neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				 }	
            }while (continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}
			
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da fun��o editar

int excluirProjeto(const char *nomeArquivo) {//in�cio da fun��o excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura bin�ria
    	 if (arquivo == NULL) {//verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n C�digo do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama fun��o de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro n�o encontrado!\n");
	            desenhaLinha(28);
	            system(" pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo ap�s a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita bin�ria
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" C�digo: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Finalidade: %s\n", dados.finalidade);
				        printf(" Data In�cio: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
				        printf(" Data T�rmino prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
						printf(" -----\n");
						
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");//confirma��o para excluir
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Opera��o cancelada. Cadastro n�o ser� exclu�do\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);  // Se n�o confirmado, escreva de volta no arquivo
	                        system(" pause");
							system("cls");
	                	}
	            	}
					fread(&dados, sizeof(dadosNecessarios), 1, arquivo);	
	        	}
	        	fclose(arquivo);
	            fclose(temp);
	            remove(nomeArquivo);
	            rename("arquivoTemporario.bin", nomeArquivo);
				
				if(marcador == 1){
					printf("\n Exclus�o realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoProjeto(nomeArquivo);//mostra os cadastros restantes ap�s a exclus�o
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a op��o n�o for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da fun��o excluir
//fim das fun��es utilizadas para projetos

void executandoOpcao4(){//in�cio da fun�ao executandoOpcao4, usado apenas para gerenciar Projetos
	int opcao, op;
	do{		
		printf("\n *Gerenciar Projetos*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Relat�rio\n");
		printf(" 0-Retornar\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);

		if(opcao == 1){
			printf("\n *Cadastrar Projeto*\n");
			cadastrarProjeto("arquivoProjeto.bin");				
		}
		if(opcao == 2){
			printf("\n *Editar Projeto*\n");
			editarProjeto("arquivoProjeto.bin");
		}
		if(opcao == 3){
			printf("\n *Excluir Projeto*\n");
			excluirProjeto("arquivoProjeto.bin");
		}
		if(opcao == 4){
			printf("\n *Relat�rio*\n");
			relatorioProjeto("arquivoProjeto.bin");
		}
		if(opcao < 0 || opcao > 4){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da fun�ao executandoOpcao4, usado apenas para gerenciar Projetos

//in�cio das fun��es utilizadas para doa��o
 int buscaDoador(const char *nomeArquivo, int codigo) {//in�cio fun��o de busca utilizado dentro da fun��o cadastra doa��o
    //essa fun��o busca dentro do arquivo doador e verifica se ele existe
	dadosNecessarios dados;
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        desenhaLinha(38);
        printf("  Arquivo doador n�o existe!\n");
        desenhaLinha(38);
        system(" pause");
        return -1;//encerra o programa
    }

    rewind(arquivo);
    while (fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        if (codigo == dados.codigo) {
            fclose(arquivo);
            return 1;//encontrado
        }
    }
	desenhaLinha(57); 
	printf(" Este c�digo n�o est� vinculado a um cadastro de doador!\n");
	desenhaLinha(57);
	system(" pause");	   
		
    fclose(arquivo);
    return 0;//n�o encontrado
}//fim da fun��o busca que � utilizada dentro da fun��o cadastra doa��o

int buscaDoadorDentroDoacao(const char *nomeArquivo, int codigo) {//in�cio fun��o de busca que � utilizada dentro da fun��o relatorio por doador
	//essa fun��o busca o codigo do dados.codigoDoador dentro do arquivo doa��o
	dadosNecessarios dados;
	FILE *arquivo = fopen(nomeArquivo, "rb"); //abre o arquivo para leitura bin�ria

    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return 1;
    }
    
    rewind(arquivo);
    fseek(arquivo, 0, SEEK_SET);//move o indicador de posi��o para o in�cio do arquivo
    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo) && codigo != dados.codigoDoador) {
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(!feof(arquivo)) {
        return ftell(arquivo) - sizeof(dadosNecessarios);//retorna a posi��o onde come�a o arquivo
    } 
	else{
        return -1;//retorna -1 para indicar que o c�digo n�o foi encontrado
    }
    
}//fim da fun��o busca que � utilizada dentro da fun��o relat�rio por c�digo de doador

int relatorioPorCodigoDoadorDoacao(const char *nomeArquivo){//in�cio da fun��o relat�rio por c�digo de doador, que busca todos as doa��es que ele fez
 	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos=0, encontrado=0;;
	
	arquivo = fopen(nomeArquivo, "rb"); 
    
	if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    }
	system("cls");
    printf("\n *Consultar por c�digo do doador*");
    printf("\n C�digo ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
	while(codigo > 0) {
    	encontrado = 0;
		pos = buscaDoador("arquivoDoador.bin",codigo);
	    
		if(pos != 1){//c�digo n�o encontrado e vai solicitar outro c�digo
			desenhaLinha(34); 
			printf(" C�digo de doador n�o encontrado!\n");
			desenhaLinha(34);
			system(" pause");	   
	    }
	    else{
			fseek(arquivo, 0, SEEK_SET);//reposiciona o ponteiro para a posi��o correta
	        //fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1){
				if(codigo == dados.codigoDoador){
					encontrado=1;
					printf("\n *** DADOS ENCONTRADOS! ***\n");
					printf("\n C�digo Doador: %d\n", dados.codigoDoador);
					printf(" C�digo Doa��o: %d\n", dados.codigo);
		            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
		            if(dados.tipoDoacao == 1)
		            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
		            if(dados.tipoDoacao == 2)
		            	printf(" Observa��o %s\n", dados.observacaoDoacao);
		            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
		            if(dados.doacaoAgendada == 1){
		            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
						printf(" Hor�rio: %s\n", dados.horarioDoacao);	
		            }
		             if(dados.doacaoAgendada == 3){
		            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
						printf(" Hor�rio: %s\n", dados.horarioDoacao);	
		            }
		            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
		            printf(" -----\n"); 
	            }
	        }
	        if(encontrado == 0){
	        	desenhaLinha(42);
		        printf(" Esse doador n�o realizou nenhuma doa��o\n");
		        desenhaLinha(42);
	        }        
			system(" pause");
		}      
		system("cls");
	    printf("\n *Consultar por cadastro*");
	    printf("\n C�digo ou 0 para cancelar: ");
	    scanf("%d", &codigo);
	    system("cls");	
	}	
	fclose(arquivo);   
	return 0;
}//fim da fun��o relat�rio por c�digo de doador, que busca todos as doa��es que ele fez

void relatorioPorTipoDinheiro(const char *nomeArquivo) {//in�cio fun��o busca de doa��es em dinheiro
    dadosNecessarios dados;
    FILE *arquivo;
    int encontrado = 0;

    printf("\n *Doa��es em Dinheiro*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
            if (dados.tipoDoacao == 1) {
                encontrado = 1;
                printf("\n C�digo Doador: %d\n", dados.codigoDoador);
                printf(" C�digo Doa��o: %d\n", dados.codigo);
                printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
                if (dados.tipoDoacao == 1)
                    printf(" Valor: R$ %.2f\n", dados.valorDoacao);
                if (dados.tipoDoacao == 2)
                    printf(" Observa��o %s\n", dados.observacaoDoacao);
                printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
                if (dados.doacaoAgendada == 1) {
                    printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
                    printf(" Hor�rio: %s\n", dados.horarioDoacao);
                }
                if (dados.doacaoAgendada == 3) {
                    printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
                    printf(" Hor�rio: %s\n", dados.horarioDoacao);
                }
                printf(" Status da Doa��o: %s\n", dados.statusDoacao);
                printf("-----\n");
            }
        }
        if(encontrado == 0) {
            desenhaLinha(30);
            printf(" Nenhuma doa��o em dinheiro encontrada\n");
            desenhaLinha(30);
        }
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca de doa��es em dinheiro

int relatorioPorOutro(const char *nomeArquivo){//in�cio fun��o busca de doa��es por outros tipos 
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Outros tipos de Doa��es*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	if(dados.tipoDoacao == 2){
        		encontrado = 1;
				printf("\n C�digo Doador: %d\n", dados.codigoDoador);
				printf(" C�digo Doa��o: %d\n", dados.codigo);
	            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observa��o %s\n", dados.observacaoDoacao);
	            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}
        }
        if(encontrado == 0){
    		desenhaLinha(28);
	        printf(" Nenhuma doa��o encontrada\n");
	        desenhaLinha(28); 
    	}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca de doa��es por outros tipos

int relatorioPorTodasDoacoes(const char *nomeArquivo){//in�cio fun��o relat�rio por todas doa��es
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system("pause");
        system("cls");
        return -1;
    } 
	else {
		printf("\n * Todas as Doa��es*\n");
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
			printf("\n C�digo Doador: %d\n", dados.codigoDoador);
			printf(" C�digo Doa��o: %d\n", dados.codigo);
            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
            if(dados.tipoDoacao == 1)
            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
            if(dados.tipoDoacao == 2)
            	printf(" Observa��o %s\n", dados.observacaoDoacao);
            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
            if(dados.doacaoAgendada == 1){
            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
				printf(" Hor�rio: %s\n", dados.horarioDoacao);	
            }
             if(dados.doacaoAgendada == 3){
            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
				printf(" Hor�rio: %s\n", dados.horarioDoacao);	
            }
            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
            printf("-----\n");
        	
        }
        if(encontrado == 0){//c�digo n�o encontrado
			desenhaLinha(28); 
			printf(" Nenhum cadastro de doa��o!\n");
			desenhaLinha(28);	   
		}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
    return 0;
}//fim da fun��o busca todas as doa��es 
 
int relatorioPorAgendamentos(const char *nomeArquivo){//in�cio fun��o busca de doa��es por agendamentos
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    
    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	if(dados.doacaoAgendada == 1 && strcmp(dados.statusDoacao, "ESPERANDO APROVA��O") == 0){
        		encontrado=1;
        		printf("\n C�digo Doador: %d\n", dados.codigoDoador);
				printf(" C�digo Doa��o: %d\n", dados.codigo);
	            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observa��o %s\n", dados.observacaoDoacao);
	            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}
        }
        if(encontrado==0){
        	desenhaLinha(28);
	        printf(" Nenhuma doa��o agendada \n");
	        desenhaLinha(28); 
        }
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca de doa��es agendamentos

int relatorioPorRealizados(const char *nomeArquivo){//in�cio fun��o busca de doa��es por doa��es realizadas 
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Doa��es Realizadas*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	if(dados.doacaoAgendada == 2 || dados.doacaoAgendada == 3){
        		encontrado=1;
        		printf("\n C�digo Doador: %d\n", dados.codigoDoador);
				printf(" C�digo Doa��o: %d\n", dados.codigo);
	            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observa��o %s\n", dados.observacaoDoacao);
	            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}  
        }
        if(encontrado==0){
        	desenhaLinha(30);
	        printf(" Nenhuma doa��o realizada \n");
	        desenhaLinha(30); 
        }	
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca de doa��es realizadas 

//in�cio das fun��es utilizadas em aprovar agendamento
int relatorioDoacoesAprovadas(const char *nomeArquivo){//in�cio fun��o relat�rio de doa��es aprovadas
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
	
    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
		printf("\n *Doa��es Aprovadas*\n");
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	if(strcmp(dados.statusDoacao, "APROVADO") == 0){
				encontrado=1;
				printf("\n C�digo Doador: %d\n", dados.codigoDoador);
				printf(" C�digo Doa��o: %d\n", dados.codigo);
	            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observa��o %s\n", dados.observacaoDoacao);
	            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}
        }
        if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma doa��o para aprovar \n");
	        desenhaLinha(30); 
    	}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
    return 0;
}//fim da fun��o relat�rio de doa��es aprovadas

int cadastrarDoacao(const char *nomeArquivo){//in�cio da fun��o de cadastro doa�ao
    int codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	char opcao;
	
	do
	{
		system("cls");
		printf("\n *Cadastrar Doa��o*\n");
		
		printf(" C�digo do doador que deseja realizar a doa��o: ");
		scanf("%d", &codigo);
		
		pos=buscaDoador("arquivoDoador.bin",codigo);//fun��o de busca que vai ver se o c�digo do doador existe dentro do arquivo doador 
		
		if(pos ==1){//c�digo encontrado e vai cadastrar a doa��o
			
			printf("\n Buscando doador...\n");
			Sleep(2000);
			printf("\n Cadastro encontrado. Vamos cadastrar a doa��o!\n");
			system(" pause");
			arquivo = fopen(nomeArquivo,"ab"); 
			
			if(arquivo == NULL){
				desenhaLinha(28);
				printf("  Arquivo de doa��o n�o pode ser criado\n");
				desenhaLinha(28);
		        system(" pause");
		        system("cls");
				return 0;//encerra o programa
			}
			else{
			  	dados.codigoDoador = codigo;
				system("cls");
				printf("\n *Cadastrar Doa��o*\n");
				printf(" C�digo da doa��o: ");
				scanf("%d", &dados.codigo);
				
				printf(" Tipo de doa��o: \n");
				do{
					printf(" 1-Dinheiro ou 2-Outros: ");
					scanf("%d",&dados.tipoDoacao);
					
					if(dados.tipoDoacao == 1){
						printf(" Voc� escolheu Dinheiro.\n");
			            printf(" Qual o valor: R$ ");
			            scanf("%f", &dados.valorDoacao);
					}
					if(dados.tipoDoacao == 2){
						printf(" Voc� escolheu Outros.\n");
			            printf(" Observa��o: ");
						fflush(stdin);
			            gets(dados.observacaoDoacao);	
					}
					if(dados.tipoDoacao < 1 || dados.tipoDoacao > 2)
						printf(" Op��o inv�lida.\n");
				
				}while(dados.tipoDoacao < 1 || dados.tipoDoacao > 2);
				
				printf(" Forma de doa��o: ");
				
				do{
					if(dados.tipoDoacao ==1){
						printf(" 2-Pix\n");
						dados.doacaoAgendada = 2;
						printf(" PIX: 18 99999-9999 \n");
						Sleep(2000);
						printf("\n Processando sua doa��o...aguarde um instante...\n");
						Sleep(2000);						
						strcpy(dados.statusDoacao, "FINALIZADA");
						desenhaLinha(43);
						printf("    ###Status da Doa��o: %s\n", dados.statusDoacao);
						printf("\n     Doa��o realizada com sucesso!\n");
						printf("  Agradecemos imensamente por seu apoio!\n");
						desenhaLinha(43); 
					}
					else{
						printf(" 1-Agendamento ou 2-Pix ou 3-Entrega: ");
						scanf("%d",&dados.doacaoAgendada);
						
						if(dados.doacaoAgendada == 1 && dados.tipoDoacao == 2){
							printf(" Data para retirada(xx xx xxxx): ");
							scanf("%d %d %d", &dados.dataRetirada.dia, &dados.dataRetirada.mes, &dados.dataRetirada.ano);
							
							printf(" Qual o melhor hor�rio(XXh:XXm): ");
							fflush(stdin);
							gets(dados.horarioDoacao);
							
							strcpy(dados.statusDoacao, "ESPERANDO APROVA��O");
							desenhaLinha(93); 
							printf("              ###Status da Doa��o: %s\n", dados.statusDoacao);
							printf("\n              Cadastro de doa��o realizado com sucesso!\n");
							printf(" Nossos colaboradores estar�o realizando a retirada conforme agendado.\n\n");
							printf("              **Agradecemos imensamente por seu apoio!**\n");
							desenhaLinha(93); 
						}
						if(dados.doacaoAgendada == 3 && dados.tipoDoacao == 2){
							printf(" Data da entrega(xx xx xxxx): ");
							scanf("%d %d %d", &dados.dataEntrega.dia, &dados.dataEntrega.mes, &dados.dataEntrega.ano);
							
							printf(" Qual o hor�rio da entrega(XXh:XXm): ");
							fflush(stdin);
							gets(dados.horarioDoacao);
							
							strcpy(dados.statusDoacao, "AGUARDANDO ENTREGA");
							desenhaLinha(80);
							printf("           ###Status da Doa��o: %s\n", dados.statusDoacao); 
							printf("\n        Cadastro de doa��o realizado com sucesso!\n\n");
							printf("    Nosso endere�o, Rua Domingos Dar�, 162, Vila Alegrete, Martin�polis-SP.\n");
							printf("    Nosso hor�rio de funcionamento � de segunda a sexta-feira, das 9h �s 18h. \n");
							printf("           Estamos te esperando ansiosamente. \n\n           **Agradecemos imensamente por seu apoio!**\n");
							desenhaLinha(80); 
						}
						if(dados.doacaoAgendada < 1 || dados.doacaoAgendada > 3)
							printf(" Op��o inv�lida.\n");
					}	
				}while(dados.doacaoAgendada < 1 || dados.doacaoAgendada > 3);	
				
				//antes de escrever, posicionar o cursor no final do arquivo
                fseek(arquivo, 0, SEEK_END);
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				system(" pause");
				fclose(arquivo); //fecha o arquivo ap�s a escrita
			}  
		}
		system("cls");
		printf("\n Fazer outro cadastro? (S/N): ");
		scanf(" %c", &opcao);
		
	}while(opcao == 'S' || opcao == 's');
	system("cls");
  	//fclose(arquivo);
	return 1;
}//fim da fun��o de cadastro doa�ao

void relatorioDoacao(const char *nomeArquivo) {//in�cio da fun��o de relat�rio
    int op;
    system("cls");
    printf("\n *Relat�rio*\n");
    printf(" 1- Doa��o em Dinheiro\n");
	printf(" 2- Doa��o de Outros\n");
	printf(" 3- Doa��es Agendadas\n");
	printf(" 4- Por Doador\n");
	printf(" 5- Doa��es Aprovadas\n");
	printf(" 6- Todas as Doa��es\n");
    printf(" 0- Retornar\n");
    printf(" Op��o: ");
    scanf("%d", &op);
    system("cls");

    while(op != 0) {
        if(op == 1) {
            relatorioPorTipoDinheiro(nomeArquivo);
        } 
		 if(op == 2) {
            relatorioPorOutro(nomeArquivo);
        } 
         if(op == 3) {
            relatorioPorAgendamentos(nomeArquivo);
        }
        if(op == 4) {
            relatorioPorCodigoDoadorDoacao(nomeArquivo);
        }
        if(op == 5) {
            relatorioDoacoesAprovadas("arquivoDoacao.bin");
        }
        if(op == 6){
        	relatorioPorTodasDoacoes(nomeArquivo);	
        }
		if(op < 0 || op > 6) {
            system("cls");
            desenhaLinha(50);
            printf("     Op��o inv�lida! Escolha outra op��o.\n");
            desenhaLinha(50);
        }
        printf("\n *Relat�rio*\n");
        printf(" 1- Doa��o em Dinheiro\n");
		printf(" 2- Doa��o de Outros\n");
		printf(" 3- Doa��es Agendadas\n");
		printf(" 4- Por Doador\n");
		printf(" 5- Doa��es Aprovadas\n");
		printf(" 6- Todas as Doa��es\n");
		printf(" 0- Retornar\n");
        printf(" Op��o: ");
        scanf("%d", &op);
        system("cls");
    }
    
}//fim da fun��o de relat�rio

int editarDoacao(const char *nomeArquivo){//in�cio da fun��o editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	system("cls");
	
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
        system("cls");
		return 0;//encerra o programa
	}
	rewind(arquivo);
	do{
		system("cls");
		printf("\n\n *Editar*");
		printf("\n C�digo da doa��o que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if (codigo == 0) {
            break;//sai do loop se o c�digo for zero
        }
		pos = busca(arquivo,codigo);//chamando fun��o  que retorna a posi�a� do cadastro da doa��o
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Doa��o n�o encontrada!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n *** EDI��O DE DADOS ***\n");
				printf("\n C�digo Doador: %d\n", dados.codigoDoador);
				printf(" C�digo Doa��o: %d\n", dados.codigo);
		        printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
		        if(dados.tipoDoacao == 1)
		        	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
		        
				if(dados.tipoDoacao == 2)
		            printf(" A- Observa��o: %s\n", dados.observacaoDoacao);
		        
				printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
		        if(dados.doacaoAgendada == 1){
		            printf(" B- Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" C- Hor�rio: %s\n", dados.horarioDoacao);	
		        }
		         if(dados.doacaoAgendada == 3){
		        	printf(" B- Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" C- Hor�rio: %s\n", dados.horarioDoacao);	
		        }
		        printf(" Status da Doa��o: %s\n", dados.statusDoacao);
				printf(" -----\n");
			    
			    if(dados.doacaoAgendada == 2){
			    	desenhaLinha(42);
		            printf(" Doa��o em dinheiro n�o pode ser editada.\n");
		            desenhaLinha(42);
		            system("pause"); 
			    }
			    else{
				    printf(" Deseja editar este cadastro? (S/N): ");
	                scanf(" %c", &continuarEdicao);
	                
					if(continuarEdicao == 'S' || continuarEdicao == 's'){
					
						do{
							if(dados.tipoDoacao == 2 && dados.doacaoAgendada == 1){
						    	
						        printf("\n Qual a op��o que deseja editar?: ");
						        scanf(" %c", &opAlterar);
						        opAlterar = toupper(opAlterar);
						        
						        switch (opAlterar) {
						            case 'A':
						                printf("\n *Alterar Observa��o*\n");
						                printf(" Nova Observa��o: "); 
						                fflush(stdin);
						                gets(dados.observacaoDoacao);
						                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
						                system(" pause");
						                break;
						                
						            case 'B':
						                printf("\n *Alterar Data Retirada*\n");
						                printf(" Nova Data Retirada(xx xx xxxx): "); 
						                scanf("%d %d %d", &dados.dataRetirada.dia, &dados.dataRetirada.mes, &dados.dataRetirada.ano);
						                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
						                system(" pause");
						                break;
						                
						            case 'C':
						                printf("\n *Alterar Hor�rio*\n");
						                printf(" Informe o novo Hor�rio(XXh:XXm): ");
						                fflush(stdin);
						                gets(dados.horarioDoacao);
						                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
						                system(" pause");
						                break;
						                
						            default:
						            	desenhaLinha(34);
						                printf(" Op��o inv�lida. Tente novamente.\n");
						                desenhaLinha(34);
						                break;
						    	}
					    	}
							if(dados.tipoDoacao == 2 && dados.doacaoAgendada == 3){
						    
						        printf("\n Qual a op��o que deseja editar?: ");
						        scanf(" %c", &opAlterar);
						        opAlterar = toupper(opAlterar);
						
						        switch (opAlterar) {
						            case 'A':
						                printf("\n *Alterar Observa��o*\n");
						                printf(" Nova Observa��o: ");
						                fflush(stdin);
						                gets(dados.observacaoDoacao);
						                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
						                system(" pause");
						                break;
						
						            case 'B':
						                printf("\n *Alterar Data Entrega*\n");
						                printf(" Nova Data Entrega(xx xx xxxx): ");
						                scanf("%d %d %d", &dados.dataEntrega.dia, &dados.dataEntrega.mes, &dados.dataEntrega.ano);
						                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
						                system(" pause");
						                break;
						
						            case 'C':
						                printf("\n *Alterar Hor�rio*\n");
						                printf(" Informe o novo Hor�rio(XXh:XXm): ");
						                fflush(stdin);
						                gets(dados.horarioDoacao);
						                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
						                system(" pause");
						                break;
						
						            default:
						            	desenhaLinha(34);
						                printf(" Op��o inv�lida. Tente novamente.\n");
						                desenhaLinha(34);
						                break;
						        }
						    }
						    
						}while (opAlterar < 'A' || opAlterar > 'C');
						
						fseek(arquivo,pos,SEEK_SET);//posicionando o ponteiro no exato lugar onde � para alterar
						fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
						
						printf("\n Deseja editar outra op��o neste cadastro? (S/N): ");
						scanf(" %c", &continuarEdicao);		
					}
					
	            }
			}while(continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}
		fclose(arquivo);
    	arquivo = fopen(nomeArquivo, "rb+");
			
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
    return 0;
}//fim da fun��o editar

int excluirDoacao(const char *nomeArquivo) {//in�cio da fun��o excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char opcao, confirmacao;
	
	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura bin�ria
    	 if (arquivo == NULL) {//verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n C�digo da doa��o que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama fun��o de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro n�o encontrado!\n");
	            desenhaLinha(28);
	            system("pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            system("cls");
				return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo ap�s a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita bin�ria
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** DOA��O ENCONTRADA! ***\n");
						printf("\n C�digo Doador: %d\n", dados.codigoDoador);
						printf(" C�digo Doa��o: %d\n", dados.codigo);
				        printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
				        if(dados.tipoDoacao == 1)
				        	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
				        if(dados.tipoDoacao == 2)
				            printf(" Observa��o %s\n", dados.observacaoDoacao);
				        printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
				        if(dados.doacaoAgendada == 1){
				            printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
							printf(" Hor�rio: %s\n", dados.horarioDoacao);	
				        }
				         if(dados.doacaoAgendada == 3){
				        	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
							printf(" Hor�rio: %s\n", dados.horarioDoacao);	
				        }
				        printf(" Status da Doa��o: %s\n", dados.statusDoacao);
						printf(" -----\n");
						
	                    //confirma��o para excluir
	                    printf("\n Deseja realmente excluir esta doa��o? (S/N): ");
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo doa��o...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n Opera��o cancelada. Doa��o n�o ser� exclu�da\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);  // Se n�o confirmado, escreva de volta no arquivo
	                        system(" pause");
							system("cls");
	                	}
	            	}
					fread(&dados, sizeof(dadosNecessarios), 1, arquivo);	
	        	}
	        	fclose(arquivo);
	            fclose(temp);
	            remove(nomeArquivo);
	            rename("arquivoTemporario.bin", nomeArquivo);
				
				if(marcador == 1){
					printf("\n Exclus�o realizada com sucesso!\n");
					Sleep(2000);
		            system("cls");
		            //buscaTodosCodigosExclusaoDoador(nomeArquivo);//mostra os cadastros restantes ap�s a exclus�o
				}
				printf("\n Excluir outra doa��o? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a op��o n�o for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
	
return 0;
}//fim da fun��o excluir

int aprovarAgendamentoDoacao(const char *nomeArquivo){//in�cio da fun��o aprovar agendamento de doa��o
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+"); //leitura e grava��o para fazer altera��o usar +
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	system("cls");
	printf(" *Aprovar Doa��es*\n");
	relatorioPorAgendamentos(nomeArquivo);
	printf("\n C�digo da doa��o que deseja aprovar ou 0 para cancelar: ");
	scanf("%d",&codigo);
	
	while(codigo != 0)
	{
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system("pause");
            system("cls");
		}
		else{
			
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			if(strcmp(dados.statusDoacao,"APROVADO") == 1){
				system("cls");
				printf("\n\n ***DADOS DA DOA��O***\n");
				printf("\n C�digo Doador: %d\n", dados.codigoDoador);
				printf(" C�digo Doa��o: %d\n", dados.codigo);
	            printf(" Tipo de doa��o(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observa��o %s\n", dados.observacaoDoacao);
	            printf(" Forma de doa��o(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Hor�rio: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doa��o: %s\n", dados.statusDoacao);
	            printf("-----\n");
			      
				printf("\n *APROVAR AGENDAMENTO*\n");
				printf("\n Deseja aprovar esse agendamento (S/N): ");
				
				if(toupper(getche())=='S'){
					strcpy(dados.statusDoacao, "APROVADO");
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
					fclose(arquivo);
					printf("\n\n *** DOA��O APROVADA COM SUCESSO! ***\n\n");
					system(" pause");
				}
				else{
					printf("\n Opera��o cancelada.\n");
	                fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);
				}
			}
			else{
				desenhaLinha(28);
				printf(" Doa��o j� foi aprovada.\n");
				desenhaLinha(28);
		        system(" pause");
			}
		}
		system("cls");
		printf("\n\n *Doa��es*\n");
		relatorioPorAgendamentos(nomeArquivo);
		printf("\n C�digo da doa��o que deseja aprovar ou 0 para cancelar ou 0 para cancelar: ");
		scanf("%d",&codigo);	
		//abrindo o arquivo novamente aqui pra poder ficar no loop
		arquivo=fopen(nomeArquivo,"rb+"); //leitura e grava��o para fazer altera��o usar +
		system("cls");
		
		if(arquivo == NULL){
			desenhaLinha(28);
			printf("  Erro ao abrir o arquivo.\n");
			desenhaLinha(28);
	        system(" pause");
			return 0;//encerra o programa
		}	
	}
	fclose(arquivo);
    system("cls");
}//fim da fun��o aprovar agendamento de doa��o
//fim das fun��es utilizadas para doa��o

void executandoOpcao5(){//in�cio da fun�ao executandoOpcao5, usado apenas para gerenciar doa��es
	int opcao, op;
	do{		
		printf("\n *Gerenciar Doa��es*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Aprovar Agendamento\n");
		printf(" 5-Relat�rio\n");
		printf(" 0-Retornar\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);

		if(opcao == 1){
			printf("\n *Cadastrar Doa��o*\n");
			cadastrarDoacao("arquivoDoacao.bin");				
		}
		if(opcao == 2){
			printf("\n *Editar Doa��o*\n");
			editarDoacao("arquivoDoacao.bin");
		}
		if(opcao == 3){
			printf("\n *Excluir Doa��o*\n");
			excluirDoacao("arquivoDoacao.bin");	
		}
		if(opcao == 4){
			printf("\n *Aprovar Agendamento*\n");
			aprovarAgendamentoDoacao("arquivoDoacao.bin");	
		}
		if(opcao == 5){
			printf("\n *Relat�rio*\n");
			relatorioDoacao("arquivoDoacao.bin");
		}
		if(opcao < 0 || opcao > 5){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da fun�ao executandoOpcao5, usado apenas para gerenciar Doa��o

//in�cio das fun��es utilizadas para atividade/tarefa
int buscaPorCodigoAtividadeTarefa(const char *nomeArquivo){//in�cio fun��o busca por c�digo usada no relat�rio na op��o por c�digo
 	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos=0;
	arquivo = fopen(nomeArquivo, "rb"); 
    if(arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    }
    system("cls");
    printf("\n\n *Consultar por cadastro*");
    printf("\n C�digo ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da fun��o de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posi��o correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Descri��o: %s\n", dados.descricao);
            printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
            printf(" -----\n");
            system(" pause");
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n C�digo ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da fun��o busca por c�digo
 
int buscaTodosCodigosAtividadeTarefa(const char *nomeArquivo){//in�cio fun��o busca todos os c�digos usado no relat�rio ap�s excluir
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Atividade/Tarefa Dispon�veis*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    } 
	else {
        while (fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
            printf("\n C�digo: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Descri��o: %s\n", dados.descricao);
            printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
            printf(" -----\n");
        }
        if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma Atividade/Tarefa encontrada\n");
	        desenhaLinha(30); 
    	}
        fclose(arquivo);
    }
    system(" pause");
    
}//fim da fun��o busca todos os c�digos

void buscaTodosCodigosExclusaoAtividadeTarefa(const char *nomeArquivo) {//in�cio da fun��o de busca ap�s a exclus�o
    FILE *arquivo = fopen(nomeArquivo, "rb");
    dadosNecessarios dados;
    int encontrado=0;
    if(arquivo == NULL) {
        printf(" Erro ao abrir o arquivo.\n");
        return;
    }
    printf("\n\n*** CADASTRO(S) RESTANTE(S) ***\n");

    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo)) {
    	encontrado=1;
        printf(" C�digo: %d\n", dados.codigo);
        printf(" Nome: %s\n", dados.nome);
        printf(" Descri��o: %s\n", dados.descricao);
        printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
		printf(" -----\n");

        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
     if(encontrado == 0){
    	desenhaLinha(30);
	    printf(" Nenhuma Atividade/Tarefa encontrada\n");
	    desenhaLinha(30); 
    }
    fclose(arquivo);
    system(" pause");
    system("cls");
}//fim da fun��o de busca ap�s a exclus�o

int buscaAtividadeTarefaNaoIniciada(const char *nomeArquivo){//in�cio fun��o busca atividades n�o iniciadas
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    } 
	else {
		while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
           if(dados.status == 0){//apenas mostrar as atividades/tarefas n�o iniciadas 
				
				encontrado=1;
				printf("\n C�digo: %d\n", dados.codigo);
	            printf(" Nome: %s\n", dados.nome);
	            printf(" Descri��o: %s\n", dados.descricao);
	            printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
	            printf(" -----\n");
	       }
    	}
    	if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma atividade n�o iniciada \n");
	        desenhaLinha(30); 
    	}	
    	fclose(arquivo);	
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca atividades n�o iniciadas

int buscaAtividadeTarefaEmAndamento(const char *nomeArquivo){//in�cio fun��o busca atividades em andamento
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    } 
	else {
		while (fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
           if(dados.status == 1){//apenas mostrar as atividades/tarefas em andamento 
				
				encontrado=1;
				printf("\n C�digo: %d\n", dados.codigo);
	            printf(" Nome: %s\n", dados.nome);
	            printf(" Descri��o: %s\n", dados.descricao);
	            printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
	            printf(" -----\n");
	       }
    	}
    	if(encontrado == 0){
    		desenhaLinha(32);
	        printf(" Nenhuma atividade em andamento \n");
	        desenhaLinha(32);
    	}	
    	fclose(arquivo);	
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca atividades em andamento
 
int buscaAtividadeTarefaConcluida(const char *nomeArquivo){//in�cio fun��o busca atividade conclu�da
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return -1;
    } 
	else {
		while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
           if(dados.status == 2){//apenas mostrar as atividades/tarefas conclu�das 
				
				encontrado=1;
				printf("\n C�digo: %d\n", dados.codigo);
	            printf(" Nome: %s\n", dados.nome);
	            printf(" Descri��o: %s\n", dados.descricao);
	            printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
	            printf(" -----\n");
	       }
    	}
    	if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma atividade conclu�da \n");
	        desenhaLinha(30);
    	}	
    	fclose(arquivo);	
    }
    system(" pause");
    system("cls");
}//fim da fun��o busca atividade conclu�da

int cadastrarAtividadeTarefa(const char *nomeArquivo){//in�cio da fun��o de cadastro 
    int opcao, codigo, encontrado, pos, status;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo n�o pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" C�digo: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//fun��o de busca
			
			if(pos == -1){//c�digo n�o encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Descri��o: "); 
				fflush(stdin); 
				gets(dados.descricao);
				
				printf(" Status \n");
				printf(" 0- N�o iniciado\n");
				printf(" 1- Em andamento\n");
				printf(" 2- Conclu�do\n");
				printf(" Qual o status da atividade/tarefa: ");
				scanf("%d",&dados.status);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system(" pause");
			}  
			else{//c�digo encontrado
				desenhaLinha(40); 
				printf(" Este c�digo j� est� vinculado a um cadastro!\n");
				desenhaLinha(40);
				system(" pause");	   
			}
			system("cls");
			printf("\n Fazer outro cadastro? (S/N): ");
			scanf(" %c", &opcao);
					
		}while(opcao == 'S' || opcao == 's');
	}
	system("cls");
  	fclose(arquivo);
	return 1;	
}//fim da fun��o de cadastro

int relatorioAtividadeTarefa(const char *nomeArquivo) {//in�cio da fun��o de relat�rio
    int op;
    system("cls");
    printf("\n *Relat�rio*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Atividades n�o iniciadas\n");
    printf(" 3- Atividades em andamentos\n");
    printf(" 4- Atividades conclu�das\n");
    printf(" 5- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Op��o: ");
    scanf("%d", &op);
    system("cls");

    while(op != 0) {
        if(op == 1) {
            buscaPorCodigoAtividadeTarefa(nomeArquivo);
        }
		 if(op == 2) {
            buscaAtividadeTarefaNaoIniciada(nomeArquivo);
        }
		 if(op == 3) {
            buscaAtividadeTarefaEmAndamento(nomeArquivo);
        }
		 if(op == 4) {
            buscaAtividadeTarefaConcluida(nomeArquivo);
        } 
		 if(op == 5) {
            buscaTodosCodigosAtividadeTarefa(nomeArquivo);
        } 
		if(op < 0 || op > 5) {
            system("cls");
            desenhaLinha(50);
            printf("     Op��o inv�lida! Escolha outra op��o.\n");
            desenhaLinha(50);
            getch();//da uma pausa na tela
        }
        system("cls");
        printf("\n *Relat�rio*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Atividades n�o iniciadas\n");
	    printf(" 3- Atividades em andamentos\n");
	    printf(" 4- Atividades conclu�das\n");
	    printf(" 5- Todos os cadastros\n");
	    printf(" 0- Retornar\n");
        printf(" Op��o: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relat�rio foi gerado com sucesso
}//fim da fun��o de relat�rio

int editarAtividadeTarefa(const char *nomeArquivo){//in�cio da fun��o editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	system("cls");
	
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	do{
		system("cls");
		printf("\n\n *Editar*");
		printf("\n C�digo do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if(codigo == 0) {
            break;//sai do loop se o c�digo for zero
        }
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDI��O DE DADOS ***\n");
				printf(" C�digo: %d\n", dados.codigo);
		        printf(" A- Nome: %s\n", dados.nome);
		        printf(" B- Descri��o: %s\n", dados.descricao);
       			printf(" C- Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
				printf(" -----\n");
			    
			    printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
				
					do {
				        printf("\n Qual a op��o que deseja editar?: ");
				        scanf(" %c", &opAlterar);
				        opAlterar = toupper(opAlterar);
				
				        switch (opAlterar) {
				            case 'A':
				                printf("\n *Alterar Nome*\n");
				                printf(" Informe o novo nome: ");
				                fflush(stdin);
				                gets(dados.nome);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'B':
				                printf("\n *Alterar Descri��o*\n");
				                printf(" Informe a nova Descri��o: ");
				                fflush(stdin);
				                gets(dados.descricao);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'C':
				                printf("\n *Alterar Status*\n");
				                printf(" 0- N�o iniciado\n");
				                printf(" 1- Em andamento\n");
				                printf(" 2- Conclu�do\n");
				                printf(" Qual o novo status da atividade/tarefa: ");
				                scanf("%d", &dados.status);
				                printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
								system(" pause");
				                break;
		
				            default:
				            	desenhaLinha(34);
				                printf(" Op��o inv�lida. Tente novamente.\n");
				                desenhaLinha(34);
				                break;
				        }
				
				    }while(opAlterar < 'A' || opAlterar > 'D');	  
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
				
					printf("\n Deseja editar outra op��o neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				}
            }while (continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}	
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da fun��o editar

int excluirAtividadeTarefa(const char *nomeArquivo) {//in�cio da fun��o excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura bin�ria
    	 if (arquivo == NULL) {
            //verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n C�digo do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama fun��o de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro n�o encontrado!\n");
	            desenhaLinha(28);
	            system(" pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo ap�s a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita bin�ria
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" C�digo: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Descri��o: %s\n", dados.descricao);
       					printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
						printf(" -----\n");
						
	                    //confirma��o para excluir
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Opera��o cancelada. Cadastro n�o ser� exclu�do\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);  // Se n�o confirmado, escreva de volta no arquivo
	                        system(" pause");
							system("cls");
	                	}
	            	}
					fread(&dados, sizeof(dadosNecessarios), 1, arquivo);	
	        	}
	        	fclose(arquivo);
	            fclose(temp);
	            remove(nomeArquivo);
	            rename("arquivoTemporario.bin", nomeArquivo);
				
				if(marcador == 1){
					printf("\n Exclus�o realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoAtividadeTarefa(nomeArquivo);//mostra os cadastros restantes ap�s a exclus�o
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a op��o n�o for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da fun��o excluir

//in�cio da fun��o de registro de realiza��o de atividades
int registrarAtividadeTarefaRealizada(const char *nomeArquivo){//in�cio da fun��o registrar atividade realizada
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	printf("\n C�digo da atividade que deseja registrar ou 0 para cancelar: ");
	scanf("%d",&codigo);
	
	while(codigo != 0)
	{
		pos = busca(arquivo,codigo);//chamando fun��o que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro n�o encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
		
			system("cls");
			printf("\n *Aprovar Doa��o*\n");
			printf("\n\n *** DADOS ATIVIDADE/TAREFA***\n");
			printf(" C�digo: %d\n", dados.codigo);
	        printf(" Nome: %s\n", dados.nome);
	        printf(" Descri��o: %s\n", dados.descricao);
   			printf(" Status(0- N�o iniciado/1- Em andamento/2- Conclu�do): %d\n", dados.status);
			printf(" -----\n");
		      
			printf("\n *Alterar Status*\n");
			printf(" 0- N�o iniciada\n");
			printf(" 1- Em andamento\n");
			printf(" 2- Conclu�da\n");
			printf("\n Qual o novo status da atividade/tarefa: "); 
			scanf("%d",&dados.status);
	        	  
			fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde � para alterar
			fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a altera��o
			fclose(arquivo);
			printf("\n *** ALTERA��O CONCLU�DA! ***\n\n");
			getch();//da uma pausa na tela
		}
		system("cls");
		
		printf("\n C�digo da atividade que deseja registrar ou 0 para cancelar: ");
		scanf("%d",&codigo);	
		//abrindo o arquivo novamente aqui pra poder ficar no loop
		arquivo=fopen(nomeArquivo,"rb+");//leitura e grava��o para fazer altera��o usar +
		system("cls");
		
		if(arquivo == NULL){
			desenhaLinha(28);
			printf("  Erro ao abrir o arquivo.\n");
			desenhaLinha(28);
	        system(" pause");
			return 0;//encerra o programa
		}	
	}
	fclose(arquivo);
    system("cls");
}//fim da fun��o registrar atividade realizada
//fim das fun��es utilizadas para Atividade/Tarefa

void executandoOpcao6(){//in�cio da fun�ao executandoOpcao6, usado apenas para gerenciar Atividades/Tarefas
	int opcao, op;
	do{		
		printf("\n *Gerenciar Atividades/Tarefas*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Registrar Realiza��o Atividade/Tarefa Realizada\n");
		printf(" 5-Relat�rio\n");
		printf(" 0-Retornar\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);

		if(opcao == 1){
			printf("\n *Cadastrar Atividades/Tarefas*\n");
			cadastrarAtividadeTarefa("cadastroAtividadeTarefa.bin");			
		}
		if(opcao == 2){
			printf("\n *Editar Atividades/Tarefas*\n");
			editarAtividadeTarefa("cadastroAtividadeTarefa.bin");
		}
		if(opcao == 3){
			printf("\n *Excluir Atividades/Tarefas*\n");
			excluirAtividadeTarefa("cadastroAtividadeTarefa.bin");
		}
		if(opcao == 4){
			system("cls");
			printf("\n *Registrar Realiza��o de Atividades/Tarefas*\n");
			registrarAtividadeTarefaRealizada("cadastroAtividadeTarefa.bin");
		}
		if(opcao == 5){
			printf("\n *Relat�rio*\n");
			relatorioAtividadeTarefa("cadastroAtividadeTarefa.bin");
		}
		if(opcao < 0 || opcao > 5){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da fun�ao executandoOpcao6, usado apenas para gerenciar Atividades/Tarefas

//fim das fun��es
void exibirArvoreDeNatal(int n) {
    //limpar a tela
    system("cls");
	printf("\n\n N�s, participantes do Projeto Integrador II - ONG Creche Junqueira, desejamos a todos um Natal repleto de alegria e um Ano Novo cheio de realiza��es e prosperidade!\n\n");
    //koop para a �rvore
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }
        for (int k = 0; k < 2 * i + 1; k++) {
            printf("*");
        }
        printf("\n");
        usleep(500000);//atraso de 500 milissegundos (0.5 segundos)
    }

    //tronco da �rvore
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf(" ");
        }
        printf("|||\n");
        usleep(500000);//atraso de 500 milissegundos (0.5 segundos)
    }

    //Papai Noel
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf(" ");
        }
        printf("H");
        for (int k = 0; k < 3; k++) {
            printf("O");
        }
        printf("\n");
        usleep(500000);//atraso de 500 milissegundos (0.5 segundos)
    }
    printf("\n * Feliz natal *\n  * At� 2024 *     \n\n");
	printf(" Andressa de Farias\n");
    printf(" Andr� de Osti Garcia Badan\n");
    printf(" Dayane Tiziani Boa Ventura\n");
    printf(" Deivid Lucas Muller Maia\n");
    printf(" Leonardo da Silveira Domingos\n");
    printf(" N�taly Lara Moraes da Silva\n");
    printf(" Rafael Haddad de Lima\n");
}
 
void executandoMenu(){//in�cio da fun��o que executa o menu principal
	int opcao;
	do{
		printf("\n ======= SISTEMA DE GERENCIAMENTO CRECHE JUNQUEIRA =======\n");
		
		printf("\n    *PAINEL ADMIN*\n");	
		printf(" 1-Gerenciar Volunt�rios\n");
		printf(" 2-Gerenciar Doadores\n");
		printf(" 3-Gerenciar Empresas Parceiras\n");
		printf(" 4-Gerenciar Projetos\n");
		printf(" 5-Gerenciar Doa��es\n");
		printf(" 6-Gerenciar Atividades/Tarefas\n");
		printf(" 0-Sair\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);
	
		if(opcao == 1){
			system("cls");
			//printf("\n *Gerenciar Volunt�rios*\n");
			executandoOpcao1();	
		}
		if(opcao == 2){
			system("cls");
			//printf("\n *Gerenciar Doadores*\n");
			executandoOpcao2();		
		}
		if(opcao == 3){
			system("cls");
			//printf("\n *Gerenciar Empresas Parceiras*\n");
			executandoOpcao3();	
		}
		if(opcao == 4){
			system("cls");
			//printf("\n *Gerenciar Projetos*\n");
			executandoOpcao4();
		}
		if(opcao == 5){
			system("cls");
			//printf("\n *Agendar Doa��o*\n");
			executandoOpcao5();
		}
		if(opcao == 6){
			system("cls");
			//printf("\n *Gerenciar Atividades/Tarefas*\n");
			executandoOpcao6();	
		}
		if(opcao < 0 || opcao > 6){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
			
	}while(opcao != 0);
	
}//fim da fun��o que executa o menu principal

void menuDoador(){//in�cio da fun��o de login doador
	int opcao;
	do{
		
		printf("\n ======= P�GINA DO DOADOR =======\n");
	    printf("\n *SEJA BEM VINDO A CRECHE JUNQUEIRA*\n");
	    printf(" Contribua para um futuro brilhante das crian�as!\n");
	    printf(" Sua doa��o faz toda a diferen�a.\n\n");
		
		printf("\n   *MENU*\n");	
		printf(" 1-Cadastrar-se\n");
		printf(" 2-Editar Informa��es Pessoais\n");
		printf(" 3-Fa�a sua Doa��o\n");
		printf(" 4-Editar Informa��es sobre a Doa��o\n");
		printf(" 5-Visualizar Hist�rico de Doa��es\n");
		printf(" 0-Sair\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);
	
		if(opcao == 1){
			cadastrarDoador("arquivoDoador.bin");	
		}
		if(opcao == 2){
			editarDoador("arquivoDoador.bin");		
		}
		if(opcao == 3){
			cadastrarDoacao("arquivoDoacao.bin");	
		}
		if(opcao == 4){
			editarDoacao("arquivoDoacao.bin");
		}
		if(opcao == 5){
			relatorioPorCodigoDoadorDoacao("arquivoDoacao.bin");
		}		
		if(opcao < 0 || opcao > 5){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
			
	}while(opcao != 0);
}//fim da fun��o de login doador

void menuVoluntario(){//in�cio da fun��o de login Voluntario
	int opcao;
	do{
		
		printf("\n ======= P�GINA DO VOLUNT�RIO =======\n");
		printf("\n *SEJA UM VOLUNT�RIO NA CRECHE JUNQUEIRA*\n");
		printf(" Junte-se a n�s para fazer a diferen�a na vida das crian�as!\n");
		printf(" Sua dedica��o como volunt�rio � uma luz brilhante para o futuro delas.\n\n");
		
		printf("\n   *MENU*\n");	
		printf(" 1-Cadastrar-se\n");
		printf(" 2-Editar Informa��es Pessoais\n");
		printf(" 3-Visualizar Atividades/Tarefas Dispon�veis\n");
		printf(" 0-Sair\n");
		printf(" Op��o: ");
		scanf("%d",&opcao);
	
		if(opcao == 1){
			cadastrarVoluntario("arquivoVoluntario.bin");	
		}
		if(opcao == 2){
			editarVoluntario("arquivoVoluntario.bin");		
		}
		if(opcao == 3){
			system("cls");
			buscaAtividadeTarefaNaoIniciada("cadastroAtividadeTarefa.bin");		
		}		
		if(opcao < 0 || opcao > 2){
			system("cls");
			desenhaLinha(50);
			printf("     Op��o inv�lida! Escolha outra op��o.\n");
			desenhaLinha(50);	
		}
			
	}while(opcao != 0);
}//fim da fun��o de login Voluntario

main()
{
	setlocale(LC_ALL,"Portuguese");
	
	int n = 8;//altura da �rvore (n�mero de camadas)
	int op, opcao;

	do{
	
		system("cls");
		printf("\n\n	************************************\n");
	    printf("	*                                  *\n");
	    printf("	*             LOGIN                *\n");
	    printf("	*                                  *\n");
	    printf("	************************************\n");
    
    
    
	    printf("\n   	 1- Doador\n");
	    printf("    	 2- Volunt�rio\n");
	    printf("    	 3- Admin\n");
	    printf("    	 0- Sair\n");
	    printf("    	 Se identifique: ");
	    scanf("%d",&op);
	    
		if(op == 1){
	    	system("cls");
	    	menuDoador();//Doador
	    }	
	    if(op ==2){
	    	system("cls");
	    	menuVoluntario();//Voluntario	
	    }
		 if(op ==3){
	    	system("cls");
	    	executandoMenu();//Admin	
	    }	
	    if(op <0 || op >3){
	    	system("cls");
			desenhaLinha(55);
			printf("     Usu�rio inv�lido! Por favor, se identifique.\n");
			desenhaLinha(55);
			system(" pause");
	    }
	    
	}while(op != 0);
	
	system("cls");
	printf("\n Voc� est� saindo do sistema.....");
	system(" pause");
	
	exibirArvoreDeNatal(n);		
}
	
		


