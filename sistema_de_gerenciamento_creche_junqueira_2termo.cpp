/*
******* Integrantes *******
Andressa de Farias - 10442313065
André de Osti Garcia Badan - 10442313851
Dayane Tiziani Boa Ventura - 10442313510
Deivid Lucas Muller Maia - 10442313486
Leonardo da Silveira Domingos - 10442313074
Nátaly Lara Moraes da Silva - 10442312658 
Rafael Haddad de Lima - 10442313190
*/

//inclusão das bibliotecas necessárias para o funcionamento do código
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<locale.h>
#include<unistd.h>//para Sleep

//início das structs
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

//início das funções
void desenhaLinha(int tam) {
    int i;
    for(i = 0; i < tam; i++) {
        printf("_");
    }
    printf("\n\n");//pular para a próxima linha
} 

//todas as funções de busca
int busca(FILE *arquivo, int codigo) {//início função de busca que é utilizada dentro das demais funções de busca
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
        return -1;//retorna -1 para indicar que o código não foi encontrado
    }
}//fim da função busca que é utilizada dentro das demais funções de busca

//funções utilizadas para voluntário 
int ordenarVoluntariosMetodoBolha(const char *nomeArquivo){//início da função de ordenação com método bolha
	FILE *arquivo;
    dadosNecessarios dados, dados1;
    int i, quantidade=0;
	
	arquivo = fopen(nomeArquivo, "rb+");//leitura e gravação

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
		printf("\n Ordenando arquivo de voluntários...\n");
		Sleep(2000);
		system("cls");
    	printf("\n Arquivo ordenado com sucesso!\n");
		system("pause");
		system("cls");
	}
	fclose(arquivo);
}//fim da função de ordenação com método bolha

int buscaPorCodigoVoluntario(const char *nomeArquivo){//início função busca por código usada no relatório na opção por código
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
    printf("\n Código ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da função de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system("pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posição correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" Código: %d\n", dados.codigo);
            printf(" *Dados pessoais:\n");
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" Gênero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endereço completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" *Dados sobre voluntáriado:\n");
            printf(" Período de trabalho: %s\n", dados.periodo);
		    printf(" Habilidades: %s\n", dados.habilidades);
		    printf(" Área de interesse: %s\n", dados.areaInteresse);
            printf(" Horas trabalhadas: %.2f\n", dados.horasTrabalhadas);
            printf(" -----\n\n");
            system(" pause"); //da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n Código ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da função busca por código
 
int buscaTodosCodigosVoluntario(const char *nomeArquivo){//início função busca todos os códigos usado no relatório 
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
            printf("\n Código: %d\n", dados.codigo);
            printf(" *Dados pessoais:\n");
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" Gênero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endereço completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" *Dados sobre voluntáriado:\n");
            printf(" Período de trabalho: %s\n", dados.periodo);
		    printf(" Habilidades: %s\n", dados.habilidades);
		    printf(" Área de interesse: %s\n", dados.areaInteresse);
            printf(" Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
            printf("-----\n\n");
        }
         if(encontrado == 0){//código não encontrado
			desenhaLinha(32); 
			printf(" Nenhum cadastro de voluntário!\n");
			desenhaLinha(32);	   
		}
        fclose(arquivo);
    }
    system("pause");
    system("cls");
}//fim da função busca todos os códigos

void buscaTodosCodigosExclusaoVoluntario(const char *nomeArquivo) {//início da função de busca após a exclusão
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
        printf(" Código: %d\n", dados.codigo);
        printf(" *Dados pessoais:\n");
        printf(" Nome: %s\n",dados.nome);
	    printf(" Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
	    printf(" Gênero: %s\n", dados.genero);
	    printf(" Telefone: %s\n",dados.telefone);
	    printf(" Endereço completo: %s\n",dados.endereco);
	    printf(" E-mail: %s\n", dados.email);
	    printf(" *Dados sobre voluntáriado:\n");
	    printf(" Período de trabalho: %s\n", dados.periodo);
	    printf(" Habilidades: %s\n", dados.habilidades);
	    printf(" Área de interesse: %s\n", dados.areaInteresse);
	    printf(" Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
		printf(" -----\n\n");

        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(encontrado == 0){//código não encontrado
		desenhaLinha(32); 
		printf(" Nenhum cadastro de voluntário!\n");
		desenhaLinha(32);	   
	}
    fclose(arquivo);
    system(" pause");
    system("cls");
}//fim da função de busca após a exclusão

int cadastrarVoluntario(const char *nomeArquivo){//início da função de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizado  para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo não pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			printf(" Código: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//função de busca
			
			if(pos == -1){//código não encontrado e vai cadastrar
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
				
				printf(" Endereço completo: ");
				fflush(stdin);
				gets(dados.endereco);
				
				printf(" E-mail: ");
				fflush(stdin);
				gets(dados.email);
				
				printf(" *Dados sobre voluntáriado:\n");
			
				printf(" Periodo de trabalho (manhã/tarde/noite): ");
				fflush(stdin);
				gets(dados.periodo);
				
				printf(" Habilidades: ");
				fflush(stdin);
				gets(dados.habilidades);
				
				printf(" Area de interesse: ");
				fflush(stdin);
				gets(dados.areaInteresse);
				
				printf("\n Se já tiver horas trabalhadas pode colocar, se não tiver coloca 0: "); 
				scanf("%f",&dados.horasTrabalhadas);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system("pause");
			}  
			else{//código encontrado
				desenhaLinha(47); 
				printf(" Este código já está vinculado a um cadastro!\n");
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
}//fim da função de cadastro

int relatorioVoluntario(const char *nomeArquivo) {//início da função de relatório
    int op;
    system("cls");
    printf("\n *Relatório*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Opção: ");
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
            printf("     Opção inválida! Escolha outra opção.\n");
            desenhaLinha(50);
        }
        printf("\n *Relatório*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Opção: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relatório foi gerado com sucesso
} //fim da função de relatório

int editarVoluntario(const char *nomeArquivo){//início da função editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
		printf("\n Código do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if (codigo == 0) {
            break;//sai do loop se o código for zero
        }
	
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				//fseek(arquivo,pos,0);//para posicionar o novo arquivo e escrever o novo dado/preço, isso usa para editar ver se precisa deixar pra relatório e verificaçãos e já existe
				//fread(&dados,sizeof(dadosNecessarios),1,arquivo);
				printf("\n\n *** EDIÇÃO DE DADOS ***\n");
				printf(" Código: %d\n",dados.codigo);
				printf(" *Dados pessoais:\n");
			    printf(" A- Nome: %s\n",dados.nome);
			    printf(" B- Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
			    printf(" C- Gênero: %s\n", dados.genero);
			    printf(" D- Telefone: %s\n",dados.telefone);
			    printf(" E- Endereço completo: %s\n",dados.endereco);
			    printf(" F- E-mail: %s\n", dados.email);
			    printf(" *Dados sobre voluntáriado\n");
			    printf(" G- Período de trabalho: %s\n", dados.periodo);
			    printf(" H- Habilidades: %s\n", dados.habilidades);
			    printf(" I- Área de interesse: %s\n", dados.areaInteresse);
			    printf(" Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
				printf(" -----\n\n");
			
			    printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
					
					do{
						printf("\n Qual a opção que deseja editar?: ");
						scanf(" %c",&opAlterar);
						opAlterar = toupper(opAlterar);
						
						switch (opAlterar) {
					        case 'A':
					            printf("\n *Alterar nome*\n");
					            printf(" Informe o novo nome: ");
					            fflush(stdin);
					            gets(dados.nome);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'B':
					            printf("\n *Alterar Data Nascimento*\n");
					            printf(" Nova Data Nascimento(xx xx xxxx): ");
					            scanf("%d %d %d", &dados.nascimento.dia, &dados.nascimento.mes, &dados.nascimento.ano);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'C':
					            printf("\n *Alterar Gênero*\n");
					            printf(" Novo Gênero: ");
					            fflush(stdin);
					            gets(dados.genero);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'D':
					            printf("\n *Alterar Telefone*\n");
					            printf(" Novo Telefone: ");
					            fflush(stdin);
					            gets(dados.telefone);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'E':
					            printf("\n *Alterar Endereço*\n");
					            printf(" Novo Endereço: ");
					            fflush(stdin);
					            gets(dados.endereco);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'F':
					            printf("\n *Alterar E-mail*\n");
					            printf(" Novo E-mail: ");
					            fflush(stdin);
					            gets(dados.email);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'G':
					            printf("\n *Alterar Período de trabalho*\n");
					            printf(" Novo Período de trabalho(manhã/tarde/noite): ");
					            fflush(stdin);
					            gets(dados.periodo);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'H':
					            printf("\n *Alterar Habilidades*\n");
					            printf(" Novo Habilidades: ");
					            fflush(stdin);
					            gets(dados.habilidades);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'I':
					            printf("\n *Alterar Área de interesse*\n");
					            printf(" Novo Área de interesse: ");
					            fflush(stdin);
					            gets(dados.areaInteresse);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        default:
					        	desenhaLinha(34);
					            printf(" Opção inválida. Tente novamente.\n");
					            desenhaLinha(34);
					    }
					    
					} while (opAlterar < 'A' || opAlterar > 'I');
					
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
					
					printf("\n Deseja editar outra opção neste cadastro? (S/N): ");
					scanf(" %c", &continuarEdicao);			
				}
				 
            }while(continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}	
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da função editar

int excluirVoluntario(const char *nomeArquivo) {//início da função excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura binária
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
	    printf("\n Código do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama função de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro não encontrado!\n");
	            desenhaLinha(28);
	            system("pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo após a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita binária
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
	                    printf(" *Dados pessoais:\n");
						printf(" Código: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
					    printf(" Gênero: %s\n", dados.genero);
					    printf(" Telefone: %s\n",dados.telefone);
					    printf(" Endereço completo: %s\n",dados.endereco);
					    printf(" E-mail: %s\n", dados.email);
					    printf(" *Dados sobre voluntáriado:\n");
					    printf(" Período de trabalho: %s\n", dados.periodo);
					    printf(" Habilidades: %s\n", dados.habilidades);
					    printf(" Área de interesse: %s\n", dados.areaInteresse);
						printf("\n Horas trabalhadas: %.2f hora(s)\n", dados.horasTrabalhadas);
						printf(" -----\n\n");
						
						if(dados.horasTrabalhadas > 0.001){
							desenhaLinha(70);
				            printf(" Este cadastro não pode ser excluído. Ele possui horas trabalhadas!\n");
				            desenhaLinha(70);
				            system(" pause");
				            system("cls");
				            marcador =0;
						}
	                    else{//confirmação para excluir
		                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");
		                    confirmacao = toupper(getch());
						    if(confirmacao == 'S') {
								marcador=1;
		                        printf("\n\n Excluindo cadastro...\n");
		                        Sleep(2000);
		                        system("cls");
		                    }
							else {
		                        printf("\n\n Operação cancelada. Cadastro não será excluído\n");
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
					printf("\n Exclusão realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoVoluntario(nomeArquivo);//mostra os cadastros restantes após a exclusão
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a opção não for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da função excluir

int lancarHoras(const char *nomeArquivo) {//início da função lançar horas para voluntarios
    FILE *arquivo;
    dadosNecessarios dados;
    int codigo, pos;
    float horasLancadas;

    system("cls");
    printf("\n *Lançar Horas*\n");
    printf(" Informe o código do voluntário: ");
    scanf("%d", &codigo);

    arquivo = fopen(nomeArquivo, "rb+");//leitura e gravação

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
        printf("  Voluntário não encontrado!\n");
        desenhaLinha(28);
        system("pause");
        fclose(arquivo);
        return 0;
    }
    fseek(arquivo, pos, SEEK_SET);
    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);

    printf("\n Horas trabalhadas atualmente: %.2f hora(s)\n", dados.horasTrabalhadas);
    printf(" Informe as horas a serem lançadas: ");
    scanf("%f", &horasLancadas);

    //adiciona as novas horas às horas já existentes
    dados.horasTrabalhadas += horasLancadas;

    fseek(arquivo, pos, SEEK_SET);
    fwrite(&dados, sizeof(dadosNecessarios), 1, arquivo);

    printf("\n Horas lançadas com sucesso!\n");
    system(" pause");
    system("cls");
	fclose(arquivo);
	
	return 1;	
}//fim da função lançar horas para voluntarios
//fim das funções utilizadas para voluntário

void executandoOpcao1(){//início da funçao executandoOpcao1, usado apenas para gerenciar voluntários pq tem a função lançar horas
	int opcao1, op;
	do{	
		
		printf("\n *Gerenciar Voluntários*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Lançar horas\n");
		printf(" 3-Editar\n");
		printf(" 4-Excluir\n");
		printf(" 5-Ordenar\n");
		printf(" 6-Relatório\n");
		printf(" 0-Retornar\n");
		printf(" Opção: ");
		scanf("%d",&opcao1);

		if(opcao1 == 1){
			printf("\n *Cadastrar Voluntário*\n");
			cadastrarVoluntario("arquivoVoluntario.bin");				
		}
		if(opcao1 == 2){
			printf("\n *Lançar horas*\n");
			lancarHoras("arquivoVoluntario.bin");		
		}
		if(opcao1 == 3){
			printf("\n *Editar Voluntário*\n");
			editarVoluntario("arquivoVoluntario.bin");
		}
		if(opcao1 == 4){
			printf("\n *Excluir Voluntário*\n");
			excluirVoluntario("arquivoVoluntario.bin");
		}
		if(opcao1 == 5){
			printf("\n *Ordenar Voluntários*\n");
			system("cls");
			ordenarVoluntariosMetodoBolha("arquivoVoluntario.bin");
		}
		if(opcao1 == 6){
			printf("\n *Relatório*\n");
			relatorioVoluntario("arquivoVoluntario.bin");
		}
		if(opcao1 < 0 || opcao1 > 6){
			system("cls");
			desenhaLinha(50);
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
	}while(opcao1 != 0);
	system("cls");
}//fim da funçao executandoOpcao1 gerenciar voluntários                           

//funções utilizadas para doador
int buscaPorCodigoDoador(const char *nomeArquivo){//início função busca por código usada no relatório na opção por código
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
    printf("\n Código ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da função de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posição correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" Gênero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endereço completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" -----\n");
            getch();//da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por Doador*");
        printf("\n Código ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da função busca por código
 
int buscaTodosCodigosDoador(const char *nomeArquivo){//início função busca todos os códigos usado no relatório após excluir
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
            printf("\n Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Data de nascimento: %02d/%02d/%04d\n", dados.nascimento.dia, dados.nascimento.mes, dados.nascimento.ano);
            printf(" Gênero: %s\n", dados.genero);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endereço completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf("-----\n");
        }
        if(encontrado == 0){//código não encontrado
			desenhaLinha(28); 
			printf(" Nenhum cadastro de doador!\n");
			desenhaLinha(28);	   
		}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da função busca todos os códigos

void buscaTodosCodigosExclusaoDoador(const char *nomeArquivo) {//início da função de busca após a exclusão
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
		printf("\n Código: %d\n", dados.codigo);
        printf(" A- Nome: %s\n",dados.nome);
	    printf(" B- Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
	    printf(" C- Gênero: %s\n", dados.genero);
	    printf(" D- Telefone: %s\n",dados.telefone);
	    printf(" E- Endereço completo: %s\n",dados.endereco);
	    printf(" F- E-mail: %s\n", dados.email);
		printf(" -----\n");

        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(encontrado == 0){//código não encontrado
		desenhaLinha(28); 
		printf(" Nenhum cadastro de doador!\n");
		desenhaLinha(28);	   
	}
    
    fclose(arquivo);
    system(" pause");
    system("cls");
}//fim da função de busca após a exclusão

int cadastrarDoador(const char *nomeArquivo){//início da função de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando  para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo não pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" Código: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//função de busca
			
			if(pos == -1){//código não encontrado e vai cadastrar
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
				
				printf(" Endereço completo: ");
				fflush(stdin);
				gets(dados.endereco);
				
				printf(" E-mail: ");
				fflush(stdin);
				gets(dados.email);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system(" pause");
				
			}  
			else{//código encontrado
				desenhaLinha(46); 
				printf(" Este código já está vinculado a um cadastro!\n");
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
}//fim da função de cadastro

int relatorioDoador(const char *nomeArquivo) {//início da função de relatório
    int op;
    system("cls");
    printf("\n *Relatório*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Opção: ");
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
            printf("     Opção inválida! Escolha outra opção.\n");
            desenhaLinha(50);
        }
        printf("\n *Relatório*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Opção: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relatório foi gerado com sucesso
}//fim da função de relatório

int editarDoador(const char *nomeArquivo){//início da função editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
		printf("\n Código do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if(codigo == 0) {
            break;//sai do loop se o código for zero
        }
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDIÇÃO DE DADOS ***\n");
				printf(" Código: %d\n",dados.codigo);
			    printf(" A- Nome: %s\n",dados.nome);
			    printf(" B- Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
			    printf(" C- Gênero: %s\n", dados.genero);
			    printf(" D- Telefone: %s\n",dados.telefone);
			    printf(" E- Endereço completo: %s\n",dados.endereco);
			    printf(" F- E-mail: %s\n", dados.email);
				printf(" -----\n");
				
				printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
				
					do{
						printf("\n Qual a opção que deseja editar?: ");
					    scanf(" %c", &opAlterar);
					    opAlterar = toupper(opAlterar);
					
						switch (opAlterar) {
					        case 'A':
					            printf("\n *Alterar nome*\n");
					            printf(" Informe o novo nome: ");
					            fflush(stdin);
					            gets(dados.nome);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'B':
					            printf("\n *Alterar Data Nascimento*\n");
					            printf(" Nova Data Nascimento(xx xx xxxx): ");
					            scanf("%d %d %d", &dados.nascimento.dia, &dados.nascimento.mes, &dados.nascimento.ano);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'C':
					            printf("\n *Alterar Gênero*\n");
					            printf(" Novo Gênero: ");
					            fflush(stdin);
					            gets(dados.genero);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'D':
					            printf("\n *Alterar Telefone*\n");
					            printf(" Novo Telefone: ");
					            fflush(stdin);
					            gets(dados.telefone);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'E':
					            printf("\n *Alterar Endereço*\n");
					            printf(" Novo Endereço: ");
					            fflush(stdin);
					            gets(dados.endereco);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        case 'F':
					            printf("\n *Alterar E-mail*\n");
					            printf(" Novo E-mail: ");
					            fflush(stdin);
					            gets(dados.email);
					            printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
					            break;
					
					        default:
					        	desenhaLinha(34);
					            printf(" Opção inválida. Tente novamente.\n");
					            desenhaLinha(34);
					    }
					    
					}while (opAlterar < 'A' || opAlterar > 'F');	
				 	
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
					
					printf("\n Deseja editar outra opção neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				}
            }while (continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}	
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da função editar

int excluirDoador(const char *nomeArquivo) {//início da função excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura binária
    	 if (arquivo == NULL) {//verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
		printf("\n\n *Excluir*");
	    printf("\n Código do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama função de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro não encontrado!\n");
	            desenhaLinha(28);
	            system(" pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo após a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita binária
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" Código: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Data de nascimento: %02d/%02d/%04d\n",dados.nascimento.dia,dados.nascimento.mes,dados.nascimento.ano);
					    printf(" Gênero: %s\n", dados.genero);
					    printf(" Telefone: %s\n",dados.telefone);
					    printf(" Endereço completo: %s\n",dados.endereco);
					    printf(" E-mail: %s\n", dados.email);
						printf(" -----\n");
						
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");//confirmação para excluir
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Operação cancelada. Cadastro não será excluído\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);//se não confirmado, escreva de volta no arquivo
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
					printf("\n Exclusão realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoDoador(nomeArquivo);//mostra os cadastros restantes após a exclusão
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a opção não for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da função excluir
//fim das funções utilizadas para doador 

void executandoOpcao2(){//início da funçao executandoOpcao2, usado apenas para gerenciar Doadores
	int opcao, op;
	do{		
		printf("\n *Gerenciar Doadores*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Relatório\n");
		printf(" 0-Retornar\n");
		printf(" Opção: ");
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
			printf("\n *Relatório*\n");
			relatorioDoador("arquivoDoador.bin");
		}
		if(opcao < 0 || opcao > 4){
			system("cls");
			desenhaLinha(50);
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da funçao executandoOpcao2, usado apenas para gerenciar Doadores

//início das funções utilizadas para Empresa
int buscaPorCodigoEmpresa(const char *nomeArquivo){//início função busca por código usada no relatório na opção por código
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
    printf("\n Código ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da função de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posição correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endereço completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf(" -----\n");
            getch();//da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n Código ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da função busca por código
 
int buscaTodosCodigosEmpresa(const char *nomeArquivo){//início função busca todos os códigos usado no relatório após excluir
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Todos os cadastros*\n");

    arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Esse arquivo ainda não existe\n");
        desenhaLinha(30);
        system(" pause");
        system("cls");
        return -1;
    } 
	else {
        while (fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
            printf("\n Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Telefone: %s\n", dados.telefone);
            printf(" Endereço completo: %s\n", dados.endereco);
            printf(" E-mail: %s\n", dados.email);
            printf("-----\n");
            
        }
        if(encontrado == 0){//código não encontrado
			desenhaLinha(32); 
			printf(" Nenhum cadastro de empresa!\n");
			desenhaLinha(32);	   
		}
        fclose(arquivo);
    }
	system(" pause");
    system("cls");
}//fim da função busca todos os códigos

void buscaTodosCodigosExclusaoEmpresa(const char *nomeArquivo) {//início da função de busca após a exclusão
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
        printf(" Código: %d\n", dados.codigo);
        printf(" Nome: %s\n",dados.nome);
	    printf(" Telefone: %s\n",dados.telefone);
	    printf(" Endereço completo: %s\n",dados.endereco);
	    printf(" E-mail: %s\n", dados.email);
		printf(" -----\n");
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
        
    }
    if(encontrado == 0){//código não encontrado
		desenhaLinha(32); 
		printf(" Nenhum cadastro de empresa!\n");
		desenhaLinha(32);	   
	}
    fclose(arquivo);
	system(" pause");
    system("cls");
}//fim da função de busca após a exclusão

int cadastrarEmpresa(const char *nomeArquivo){//início da função de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo não pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" Código: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//função de busca
			
			if(pos == -1){//código não encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Telefone(XX XXXXX-XXXX):"); 
				fflush(stdin);
				gets(dados.telefone);
				
				printf(" Endereço completo: ");
				fflush(stdin);
				gets(dados.endereco);
				
				printf(" E-mail: ");
				fflush(stdin);
				gets(dados.email);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system("pause");
			}  
			else{//código encontrado
				desenhaLinha(40); 
				printf(" Este código já está vinculado a um cadastro!\n");
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
}//fim da função de cadastro

int relatorioEmpresa(const char *nomeArquivo) {//início da função de relatório
    int op;
    system("cls");
    printf("\n *Relatório*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Opção: ");
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
            printf("     Opção inválida! Escolha outra opção.\n");
            desenhaLinha(50);
        }
        printf("\n *Relatório*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Opção: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relatório foi gerado com sucesso
}//fim da função de relatório

int editarEmpresa(const char *nomeArquivo){//início da função editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
		printf("\n Código do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if(codigo == 0) {
            break;//sai do loop se o código for zero
        }
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDIÇÃO DE DADOS ***\n");
				printf(" Código: %d\n",dados.codigo);
			    printf(" A- Nome: %s\n",dados.nome);
			    printf(" B- Telefone: %s\n",dados.telefone);
			    printf(" C- Endereço completo: %s\n",dados.endereco);
			    printf(" D- E-mail: %s\n", dados.email);
				printf(" -----\n");
			
				printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
					do {
				        printf("\n Qual a opção que deseja editar?: ");
				        scanf(" %c", &opAlterar);
				        opAlterar = toupper(opAlterar);
				
				        switch (opAlterar) {
				            case 'A':
				                printf("\n *Alterar nome*\n");
				                printf(" Informe o novo nome: ");
				                fflush(stdin);
				                gets(dados.nome);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'B':
				                printf("\n *Alterar Telefone*\n");
				                printf(" Novo Telefone: "); 
				                fflush(stdin);
				                gets(dados.telefone);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system("pause");
				                break;
				
				            case 'C':
				                printf("\n *Alterar Endereço*\n");
				                printf(" Novo Endereço: "); 
				                fflush(stdin);
				                gets(dados.endereco);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'D':
				                printf("\n *Alterar E-mail*\n");
				                printf(" Novo E-mail: "); 
				                fflush(stdin);
				                gets(dados.email);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            default:
				            	desenhaLinha(34);
				                printf(" Opção inválida. Tente novamente.\n");
				                desenhaLinha(34);
				        }
				    } while (opAlterar < 'A' || opAlterar > 'D');
					
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
					
					printf("\n Deseja editar outra opção neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				}
            }while(continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}		
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da função editar

int excluirEmpresa(const char *nomeArquivo) {//início da função excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura binária
    	 if (arquivo == NULL) {// Verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n Código do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama função de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro não encontrado!\n");
	            desenhaLinha(28);
	            system("pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            system("cls");
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo após a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita binária
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" Código: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Telefone: %s\n",dados.telefone);
					    printf(" Endereço completo: %s\n",dados.endereco);
					    printf(" E-mail: %s\n", dados.email);
						printf(" -----\n");
						
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");//confirmação para excluir
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Operação cancelada. Cadastro não será excluído\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);//se não confirmado, escreva de volta no arquivo
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
					printf("\n Exclusão realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoEmpresa(nomeArquivo);//mostra os cadastros restantes após a exclusão
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a opção não for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da função excluir

//fim das funções utilizadas para empresas

void executandoOpcao3(){//início da funçao executandoOpcao3, usado apenas para gerenciar Empresas
	int opcao, op;
	do{		
		printf("\n *Gerenciar Empresas*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Relatório\n");
		printf(" 0-Retornar\n");
		printf(" Opção: ");
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
			printf("\n *Relatório*\n");
			relatorioEmpresa("arquivoEmpresa.bin");
		}
		if(opcao < 0 || opcao > 4){
			system("cls");
			desenhaLinha(50);
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da funçao executandoOpcao3, usado apenas para gerenciar Empresas

//início das funções utilizadas para Projeto
int buscaPorCodigoProjeto(const char *nomeArquivo){//início função busca por código usada no relatório na opção por código
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
    printf("\n Código ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da função de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posição correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Finalidade: %s\n", dados.finalidade);
            printf(" Data Início: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
            printf(" Data Término prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
            printf(" -----\n");
            getch();//da uma pausa na tela
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n Código ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da função busca por código
 
int buscaTodosCodigosProjeto(const char *nomeArquivo){//início função busca todos os códigos usado no relatório após excluir
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
            printf("\n Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Finalidade: %s\n", dados.finalidade);
            printf(" Data Início: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
            printf(" Data Término prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
            printf("-----\n");
        }
         if(encontrado == 0){//código não encontrado
			desenhaLinha(32); 
			printf(" Nenhum cadastro de empresa!\n");
			desenhaLinha(32);	   
		}
        fclose(arquivo);
	}
	system(" pause");
    system("cls");
}//fim da função busca todos os códigos

void buscaTodosCodigosExclusaoProjeto(const char *nomeArquivo) {//início da função de busca após a exclusão
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
        printf(" Código: %d\n", dados.codigo);
        printf(" Nome: %s\n", dados.nome);
        printf(" Finalidade: %s\n", dados.finalidade);
        printf(" Data Início: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
        printf(" Data Término prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
		printf(" -----\n");
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
     if(encontrado == 0){//código não encontrado
		desenhaLinha(32); 
		printf(" Nenhum cadastro de empresa!\n");
		desenhaLinha(32);	   
	}
    fclose(arquivo);
	system(" pause");
    system("cls");
}//fim da função de busca após a exclusão

int cadastrarProjeto(const char *nomeArquivo){//início da função de cadastro 
    int opcao, codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando  para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo não pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" Código: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//função de busca
			
			if(pos == -1){//código não encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Finalidade: "); 
				fflush(stdin); 
				gets(dados.finalidade);
				
				printf(" Data Início(xx xx xxxx): "); 
				scanf("%d %d %d",&dados.projetoI.dia,&dados.projetoI.mes,&dados.projetoI.ano);
				
				printf(" Data Término prevista(xx xx xxxx): "); 
				scanf("%d %d %d",&dados.projetoT.dia,&dados.projetoT.mes,&dados.projetoT.ano);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system("pause");
			}  
			else{//código encontrado
				desenhaLinha(40); 
				printf(" Este código já está vinculado a um cadastro!\n");
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
}//fim da função de cadastro

int relatorioProjeto(const char *nomeArquivo){//início da função de relatório
    int op;
    system("cls");
    printf("\n *Relatório*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Opção: ");
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
            printf("     Opção inválida! Escolha outra opção.\n");
            desenhaLinha(50);
        }
        printf("\n *Relatório*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Todos os cadastros\n");
        printf(" 0- Retornar\n");
        printf(" Opção: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relatório foi gerado com sucesso
}//fim da função de relatório

int editarProjeto(const char *nomeArquivo){//início da função editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
		printf("\n Código do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if (codigo == 0) {
            break; //sai do loop se o código for zero
        }
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDIÇÃO DE DADOS ***\n");
				printf(" Código: %d\n", dados.codigo);
		        printf(" A- Nome: %s\n", dados.nome);
		        printf(" B- Finalidade: %s\n", dados.finalidade);
		        printf(" C- Data Início: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
		        printf(" D- Data Término prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
				printf(" -----\n");
			    
			    printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
				
					do {
				        printf("\n Qual a opção que deseja editar?: ");
				        scanf(" %c", &opAlterar);
				        opAlterar = toupper(opAlterar);
				
				        switch (opAlterar) {
				            case 'A':
				                printf("\n *Alterar Nome*\n");
				                printf(" Informe o novo nome: ");
				                fflush(stdin);
				                gets(dados.nome);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'B':
				                printf("\n *Alterar Finalidade*\n");
				                printf(" Informe a nova finalidade: ");
				                fflush(stdin);
				                gets(dados.finalidade);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'C':
				                printf("\n *Alterar Data Início*\n");
				                printf(" Nova Data Início(xx xx xxxx): ");
				                scanf("%d %d %d", &dados.projetoI.dia, &dados.projetoI.mes, &dados.projetoI.ano);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'D':
				                printf("\n *Alterar Data Término prevista*\n");
				                printf(" Nova Data Término prevista(xx xx xxxx): ");
				                scanf("%d %d %d", &dados.projetoT.dia, &dados.projetoT.mes, &dados.projetoT.ano);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            default:
				                desenhaLinha(34);
					            printf(" Opção inválida. Tente novamente.\n");
					            desenhaLinha(34);
				        }
				    } while (opAlterar < 'A' || opAlterar > 'D');
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
					
					printf("\n Deseja editar outra opção neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				 }	
            }while (continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}
			
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da função editar

int excluirProjeto(const char *nomeArquivo) {//início da função excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura binária
    	 if (arquivo == NULL) {//verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n Código do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama função de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro não encontrado!\n");
	            desenhaLinha(28);
	            system(" pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo após a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita binária
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" Código: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Finalidade: %s\n", dados.finalidade);
				        printf(" Data Início: %02d/%02d/%04d\n", dados.projetoI.dia, dados.projetoI.mes, dados.projetoI.ano);
				        printf(" Data Término prevista: %02d/%02d/%04d\n", dados.projetoT.dia, dados.projetoT.mes, dados.projetoT.ano);
						printf(" -----\n");
						
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");//confirmação para excluir
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Operação cancelada. Cadastro não será excluído\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);  // Se não confirmado, escreva de volta no arquivo
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
					printf("\n Exclusão realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoProjeto(nomeArquivo);//mostra os cadastros restantes após a exclusão
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a opção não for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da função excluir
//fim das funções utilizadas para projetos

void executandoOpcao4(){//início da funçao executandoOpcao4, usado apenas para gerenciar Projetos
	int opcao, op;
	do{		
		printf("\n *Gerenciar Projetos*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Relatório\n");
		printf(" 0-Retornar\n");
		printf(" Opção: ");
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
			printf("\n *Relatório*\n");
			relatorioProjeto("arquivoProjeto.bin");
		}
		if(opcao < 0 || opcao > 4){
			system("cls");
			desenhaLinha(50);
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da funçao executandoOpcao4, usado apenas para gerenciar Projetos

//início das funções utilizadas para doação
 int buscaDoador(const char *nomeArquivo, int codigo) {//início função de busca utilizado dentro da função cadastra doação
    //essa função busca dentro do arquivo doador e verifica se ele existe
	dadosNecessarios dados;
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "rb");

    if (arquivo == NULL) {
        desenhaLinha(38);
        printf("  Arquivo doador não existe!\n");
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
	printf(" Este código não está vinculado a um cadastro de doador!\n");
	desenhaLinha(57);
	system(" pause");	   
		
    fclose(arquivo);
    return 0;//não encontrado
}//fim da função busca que é utilizada dentro da função cadastra doação

int buscaDoadorDentroDoacao(const char *nomeArquivo, int codigo) {//início função de busca que é utilizada dentro da função relatorio por doador
	//essa função busca o codigo do dados.codigoDoador dentro do arquivo doação
	dadosNecessarios dados;
	FILE *arquivo = fopen(nomeArquivo, "rb"); //abre o arquivo para leitura binária

    if (arquivo == NULL) {
        desenhaLinha(30);
        printf(" Erro na abertura do arquivo\n");
        desenhaLinha(30);
        system(" pause");
        return 1;
    }
    
    rewind(arquivo);
    fseek(arquivo, 0, SEEK_SET);//move o indicador de posição para o início do arquivo
    fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    while(!feof(arquivo) && codigo != dados.codigoDoador) {
        fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
    }
    if(!feof(arquivo)) {
        return ftell(arquivo) - sizeof(dadosNecessarios);//retorna a posição onde começa o arquivo
    } 
	else{
        return -1;//retorna -1 para indicar que o código não foi encontrado
    }
    
}//fim da função busca que é utilizada dentro da função relatório por código de doador

int relatorioPorCodigoDoadorDoacao(const char *nomeArquivo){//início da função relatório por código de doador, que busca todos as doações que ele fez
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
    printf("\n *Consultar por código do doador*");
    printf("\n Código ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
	while(codigo > 0) {
    	encontrado = 0;
		pos = buscaDoador("arquivoDoador.bin",codigo);
	    
		if(pos != 1){//código não encontrado e vai solicitar outro código
			desenhaLinha(34); 
			printf(" Código de doador não encontrado!\n");
			desenhaLinha(34);
			system(" pause");	   
	    }
	    else{
			fseek(arquivo, 0, SEEK_SET);//reposiciona o ponteiro para a posição correta
	        //fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1){
				if(codigo == dados.codigoDoador){
					encontrado=1;
					printf("\n *** DADOS ENCONTRADOS! ***\n");
					printf("\n Código Doador: %d\n", dados.codigoDoador);
					printf(" Código Doação: %d\n", dados.codigo);
		            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
		            if(dados.tipoDoacao == 1)
		            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
		            if(dados.tipoDoacao == 2)
		            	printf(" Observação %s\n", dados.observacaoDoacao);
		            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
		            if(dados.doacaoAgendada == 1){
		            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
						printf(" Horário: %s\n", dados.horarioDoacao);	
		            }
		             if(dados.doacaoAgendada == 3){
		            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
						printf(" Horário: %s\n", dados.horarioDoacao);	
		            }
		            printf(" Status da Doação: %s\n", dados.statusDoacao);
		            printf(" -----\n"); 
	            }
	        }
	        if(encontrado == 0){
	        	desenhaLinha(42);
		        printf(" Esse doador não realizou nenhuma doação\n");
		        desenhaLinha(42);
	        }        
			system(" pause");
		}      
		system("cls");
	    printf("\n *Consultar por cadastro*");
	    printf("\n Código ou 0 para cancelar: ");
	    scanf("%d", &codigo);
	    system("cls");	
	}	
	fclose(arquivo);   
	return 0;
}//fim da função relatório por código de doador, que busca todos as doações que ele fez

void relatorioPorTipoDinheiro(const char *nomeArquivo) {//início função busca de doações em dinheiro
    dadosNecessarios dados;
    FILE *arquivo;
    int encontrado = 0;

    printf("\n *Doações em Dinheiro*\n");

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
                printf("\n Código Doador: %d\n", dados.codigoDoador);
                printf(" Código Doação: %d\n", dados.codigo);
                printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
                if (dados.tipoDoacao == 1)
                    printf(" Valor: R$ %.2f\n", dados.valorDoacao);
                if (dados.tipoDoacao == 2)
                    printf(" Observação %s\n", dados.observacaoDoacao);
                printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
                if (dados.doacaoAgendada == 1) {
                    printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
                    printf(" Horário: %s\n", dados.horarioDoacao);
                }
                if (dados.doacaoAgendada == 3) {
                    printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
                    printf(" Horário: %s\n", dados.horarioDoacao);
                }
                printf(" Status da Doação: %s\n", dados.statusDoacao);
                printf("-----\n");
            }
        }
        if(encontrado == 0) {
            desenhaLinha(30);
            printf(" Nenhuma doação em dinheiro encontrada\n");
            desenhaLinha(30);
        }
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da função busca de doações em dinheiro

int relatorioPorOutro(const char *nomeArquivo){//início função busca de doações por outros tipos 
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Outros tipos de Doações*\n");

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
				printf("\n Código Doador: %d\n", dados.codigoDoador);
				printf(" Código Doação: %d\n", dados.codigo);
	            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observação %s\n", dados.observacaoDoacao);
	            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doação: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}
        }
        if(encontrado == 0){
    		desenhaLinha(28);
	        printf(" Nenhuma doação encontrada\n");
	        desenhaLinha(28); 
    	}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da função busca de doações por outros tipos

int relatorioPorTodasDoacoes(const char *nomeArquivo){//início função relatório por todas doações
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
		printf("\n * Todas as Doações*\n");
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	encontrado=1;
			printf("\n Código Doador: %d\n", dados.codigoDoador);
			printf(" Código Doação: %d\n", dados.codigo);
            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
            if(dados.tipoDoacao == 1)
            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
            if(dados.tipoDoacao == 2)
            	printf(" Observação %s\n", dados.observacaoDoacao);
            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
            if(dados.doacaoAgendada == 1){
            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
				printf(" Horário: %s\n", dados.horarioDoacao);	
            }
             if(dados.doacaoAgendada == 3){
            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
				printf(" Horário: %s\n", dados.horarioDoacao);	
            }
            printf(" Status da Doação: %s\n", dados.statusDoacao);
            printf("-----\n");
        	
        }
        if(encontrado == 0){//código não encontrado
			desenhaLinha(28); 
			printf(" Nenhum cadastro de doação!\n");
			desenhaLinha(28);	   
		}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
    return 0;
}//fim da função busca todas as doações 
 
int relatorioPorAgendamentos(const char *nomeArquivo){//início função busca de doações por agendamentos
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
        	if(dados.doacaoAgendada == 1 && strcmp(dados.statusDoacao, "ESPERANDO APROVAÇÃO") == 0){
        		encontrado=1;
        		printf("\n Código Doador: %d\n", dados.codigoDoador);
				printf(" Código Doação: %d\n", dados.codigo);
	            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observação %s\n", dados.observacaoDoacao);
	            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doação: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}
        }
        if(encontrado==0){
        	desenhaLinha(28);
	        printf(" Nenhuma doação agendada \n");
	        desenhaLinha(28); 
        }
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da função busca de doações agendamentos

int relatorioPorRealizados(const char *nomeArquivo){//início função busca de doações por doações realizadas 
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Doações Realizadas*\n");

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
        		printf("\n Código Doador: %d\n", dados.codigoDoador);
				printf(" Código Doação: %d\n", dados.codigo);
	            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observação %s\n", dados.observacaoDoacao);
	            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doação: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}  
        }
        if(encontrado==0){
        	desenhaLinha(30);
	        printf(" Nenhuma doação realizada \n");
	        desenhaLinha(30); 
        }	
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
}//fim da função busca de doações realizadas 

//início das funções utilizadas em aprovar agendamento
int relatorioDoacoesAprovadas(const char *nomeArquivo){//início função relatório de doações aprovadas
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
		printf("\n *Doações Aprovadas*\n");
        while(fread(&dados, sizeof(dadosNecessarios), 1, arquivo) == 1) {
        	if(strcmp(dados.statusDoacao, "APROVADO") == 0){
				encontrado=1;
				printf("\n Código Doador: %d\n", dados.codigoDoador);
				printf(" Código Doação: %d\n", dados.codigo);
	            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observação %s\n", dados.observacaoDoacao);
	            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doação: %s\n", dados.statusDoacao);
	            printf("-----\n");
        	}
        }
        if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma doação para aprovar \n");
	        desenhaLinha(30); 
    	}
        fclose(arquivo);
    }
    system(" pause");
    system("cls");
    return 0;
}//fim da função relatório de doações aprovadas

int cadastrarDoacao(const char *nomeArquivo){//início da função de cadastro doaçao
    int codigo, encontrado, pos;
	dadosNecessarios dados;
	FILE *arquivo;
	char opcao;
	
	do
	{
		system("cls");
		printf("\n *Cadastrar Doação*\n");
		
		printf(" Código do doador que deseja realizar a doação: ");
		scanf("%d", &codigo);
		
		pos=buscaDoador("arquivoDoador.bin",codigo);//função de busca que vai ver se o código do doador existe dentro do arquivo doador 
		
		if(pos ==1){//código encontrado e vai cadastrar a doação
			
			printf("\n Buscando doador...\n");
			Sleep(2000);
			printf("\n Cadastro encontrado. Vamos cadastrar a doação!\n");
			system(" pause");
			arquivo = fopen(nomeArquivo,"ab"); 
			
			if(arquivo == NULL){
				desenhaLinha(28);
				printf("  Arquivo de doação não pode ser criado\n");
				desenhaLinha(28);
		        system(" pause");
		        system("cls");
				return 0;//encerra o programa
			}
			else{
			  	dados.codigoDoador = codigo;
				system("cls");
				printf("\n *Cadastrar Doação*\n");
				printf(" Código da doação: ");
				scanf("%d", &dados.codigo);
				
				printf(" Tipo de doação: \n");
				do{
					printf(" 1-Dinheiro ou 2-Outros: ");
					scanf("%d",&dados.tipoDoacao);
					
					if(dados.tipoDoacao == 1){
						printf(" Você escolheu Dinheiro.\n");
			            printf(" Qual o valor: R$ ");
			            scanf("%f", &dados.valorDoacao);
					}
					if(dados.tipoDoacao == 2){
						printf(" Você escolheu Outros.\n");
			            printf(" Observação: ");
						fflush(stdin);
			            gets(dados.observacaoDoacao);	
					}
					if(dados.tipoDoacao < 1 || dados.tipoDoacao > 2)
						printf(" Opção inválida.\n");
				
				}while(dados.tipoDoacao < 1 || dados.tipoDoacao > 2);
				
				printf(" Forma de doação: ");
				
				do{
					if(dados.tipoDoacao ==1){
						printf(" 2-Pix\n");
						dados.doacaoAgendada = 2;
						printf(" PIX: 18 99999-9999 \n");
						Sleep(2000);
						printf("\n Processando sua doação...aguarde um instante...\n");
						Sleep(2000);						
						strcpy(dados.statusDoacao, "FINALIZADA");
						desenhaLinha(43);
						printf("    ###Status da Doação: %s\n", dados.statusDoacao);
						printf("\n     Doação realizada com sucesso!\n");
						printf("  Agradecemos imensamente por seu apoio!\n");
						desenhaLinha(43); 
					}
					else{
						printf(" 1-Agendamento ou 2-Pix ou 3-Entrega: ");
						scanf("%d",&dados.doacaoAgendada);
						
						if(dados.doacaoAgendada == 1 && dados.tipoDoacao == 2){
							printf(" Data para retirada(xx xx xxxx): ");
							scanf("%d %d %d", &dados.dataRetirada.dia, &dados.dataRetirada.mes, &dados.dataRetirada.ano);
							
							printf(" Qual o melhor horário(XXh:XXm): ");
							fflush(stdin);
							gets(dados.horarioDoacao);
							
							strcpy(dados.statusDoacao, "ESPERANDO APROVAÇÃO");
							desenhaLinha(93); 
							printf("              ###Status da Doação: %s\n", dados.statusDoacao);
							printf("\n              Cadastro de doação realizado com sucesso!\n");
							printf(" Nossos colaboradores estarão realizando a retirada conforme agendado.\n\n");
							printf("              **Agradecemos imensamente por seu apoio!**\n");
							desenhaLinha(93); 
						}
						if(dados.doacaoAgendada == 3 && dados.tipoDoacao == 2){
							printf(" Data da entrega(xx xx xxxx): ");
							scanf("%d %d %d", &dados.dataEntrega.dia, &dados.dataEntrega.mes, &dados.dataEntrega.ano);
							
							printf(" Qual o horário da entrega(XXh:XXm): ");
							fflush(stdin);
							gets(dados.horarioDoacao);
							
							strcpy(dados.statusDoacao, "AGUARDANDO ENTREGA");
							desenhaLinha(80);
							printf("           ###Status da Doação: %s\n", dados.statusDoacao); 
							printf("\n        Cadastro de doação realizado com sucesso!\n\n");
							printf("    Nosso endereço, Rua Domingos Daré, 162, Vila Alegrete, Martinópolis-SP.\n");
							printf("    Nosso horário de funcionamento é de segunda a sexta-feira, das 9h às 18h. \n");
							printf("           Estamos te esperando ansiosamente. \n\n           **Agradecemos imensamente por seu apoio!**\n");
							desenhaLinha(80); 
						}
						if(dados.doacaoAgendada < 1 || dados.doacaoAgendada > 3)
							printf(" Opção inválida.\n");
					}	
				}while(dados.doacaoAgendada < 1 || dados.doacaoAgendada > 3);	
				
				//antes de escrever, posicionar o cursor no final do arquivo
                fseek(arquivo, 0, SEEK_END);
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				system(" pause");
				fclose(arquivo); //fecha o arquivo após a escrita
			}  
		}
		system("cls");
		printf("\n Fazer outro cadastro? (S/N): ");
		scanf(" %c", &opcao);
		
	}while(opcao == 'S' || opcao == 's');
	system("cls");
  	//fclose(arquivo);
	return 1;
}//fim da função de cadastro doaçao

void relatorioDoacao(const char *nomeArquivo) {//início da função de relatório
    int op;
    system("cls");
    printf("\n *Relatório*\n");
    printf(" 1- Doação em Dinheiro\n");
	printf(" 2- Doação de Outros\n");
	printf(" 3- Doações Agendadas\n");
	printf(" 4- Por Doador\n");
	printf(" 5- Doações Aprovadas\n");
	printf(" 6- Todas as Doações\n");
    printf(" 0- Retornar\n");
    printf(" Opção: ");
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
            printf("     Opção inválida! Escolha outra opção.\n");
            desenhaLinha(50);
        }
        printf("\n *Relatório*\n");
        printf(" 1- Doação em Dinheiro\n");
		printf(" 2- Doação de Outros\n");
		printf(" 3- Doações Agendadas\n");
		printf(" 4- Por Doador\n");
		printf(" 5- Doações Aprovadas\n");
		printf(" 6- Todas as Doações\n");
		printf(" 0- Retornar\n");
        printf(" Opção: ");
        scanf("%d", &op);
        system("cls");
    }
    
}//fim da função de relatório

int editarDoacao(const char *nomeArquivo){//início da função editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
		printf("\n Código da doação que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if (codigo == 0) {
            break;//sai do loop se o código for zero
        }
		pos = busca(arquivo,codigo);//chamando função  que retorna a posiçaõ do cadastro da doação
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Doação não encontrada!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n *** EDIÇÃO DE DADOS ***\n");
				printf("\n Código Doador: %d\n", dados.codigoDoador);
				printf(" Código Doação: %d\n", dados.codigo);
		        printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
		        if(dados.tipoDoacao == 1)
		        	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
		        
				if(dados.tipoDoacao == 2)
		            printf(" A- Observação: %s\n", dados.observacaoDoacao);
		        
				printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
		        if(dados.doacaoAgendada == 1){
		            printf(" B- Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" C- Horário: %s\n", dados.horarioDoacao);	
		        }
		         if(dados.doacaoAgendada == 3){
		        	printf(" B- Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" C- Horário: %s\n", dados.horarioDoacao);	
		        }
		        printf(" Status da Doação: %s\n", dados.statusDoacao);
				printf(" -----\n");
			    
			    if(dados.doacaoAgendada == 2){
			    	desenhaLinha(42);
		            printf(" Doação em dinheiro não pode ser editada.\n");
		            desenhaLinha(42);
		            system("pause"); 
			    }
			    else{
				    printf(" Deseja editar este cadastro? (S/N): ");
	                scanf(" %c", &continuarEdicao);
	                
					if(continuarEdicao == 'S' || continuarEdicao == 's'){
					
						do{
							if(dados.tipoDoacao == 2 && dados.doacaoAgendada == 1){
						    	
						        printf("\n Qual a opção que deseja editar?: ");
						        scanf(" %c", &opAlterar);
						        opAlterar = toupper(opAlterar);
						        
						        switch (opAlterar) {
						            case 'A':
						                printf("\n *Alterar Observação*\n");
						                printf(" Nova Observação: "); 
						                fflush(stdin);
						                gets(dados.observacaoDoacao);
						                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
						                system(" pause");
						                break;
						                
						            case 'B':
						                printf("\n *Alterar Data Retirada*\n");
						                printf(" Nova Data Retirada(xx xx xxxx): "); 
						                scanf("%d %d %d", &dados.dataRetirada.dia, &dados.dataRetirada.mes, &dados.dataRetirada.ano);
						                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
						                system(" pause");
						                break;
						                
						            case 'C':
						                printf("\n *Alterar Horário*\n");
						                printf(" Informe o novo Horário(XXh:XXm): ");
						                fflush(stdin);
						                gets(dados.horarioDoacao);
						                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
						                system(" pause");
						                break;
						                
						            default:
						            	desenhaLinha(34);
						                printf(" Opção inválida. Tente novamente.\n");
						                desenhaLinha(34);
						                break;
						    	}
					    	}
							if(dados.tipoDoacao == 2 && dados.doacaoAgendada == 3){
						    
						        printf("\n Qual a opção que deseja editar?: ");
						        scanf(" %c", &opAlterar);
						        opAlterar = toupper(opAlterar);
						
						        switch (opAlterar) {
						            case 'A':
						                printf("\n *Alterar Observação*\n");
						                printf(" Nova Observação: ");
						                fflush(stdin);
						                gets(dados.observacaoDoacao);
						                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
						                system(" pause");
						                break;
						
						            case 'B':
						                printf("\n *Alterar Data Entrega*\n");
						                printf(" Nova Data Entrega(xx xx xxxx): ");
						                scanf("%d %d %d", &dados.dataEntrega.dia, &dados.dataEntrega.mes, &dados.dataEntrega.ano);
						                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
						                system(" pause");
						                break;
						
						            case 'C':
						                printf("\n *Alterar Horário*\n");
						                printf(" Informe o novo Horário(XXh:XXm): ");
						                fflush(stdin);
						                gets(dados.horarioDoacao);
						                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
						                system(" pause");
						                break;
						
						            default:
						            	desenhaLinha(34);
						                printf(" Opção inválida. Tente novamente.\n");
						                desenhaLinha(34);
						                break;
						        }
						    }
						    
						}while (opAlterar < 'A' || opAlterar > 'C');
						
						fseek(arquivo,pos,SEEK_SET);//posicionando o ponteiro no exato lugar onde é para alterar
						fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
						
						printf("\n Deseja editar outra opção neste cadastro? (S/N): ");
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
}//fim da função editar

int excluirDoacao(const char *nomeArquivo) {//início da função excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char opcao, confirmacao;
	
	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura binária
    	 if (arquivo == NULL) {//verifica se houve erro na abertura do arquivo
            desenhaLinha(30);
            printf(" Erro na abertura do arquivo\n");
            desenhaLinha(30);
            system(" pause");
            return 1;
        }
		system("cls");
	
		printf("\n\n *Excluir*");
	    printf("\n Código da doação que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama função de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro não encontrado!\n");
	            desenhaLinha(28);
	            system("pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            system("cls");
				return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo após a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita binária
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** DOAÇÃO ENCONTRADA! ***\n");
						printf("\n Código Doador: %d\n", dados.codigoDoador);
						printf(" Código Doação: %d\n", dados.codigo);
				        printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
				        if(dados.tipoDoacao == 1)
				        	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
				        if(dados.tipoDoacao == 2)
				            printf(" Observação %s\n", dados.observacaoDoacao);
				        printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
				        if(dados.doacaoAgendada == 1){
				            printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
							printf(" Horário: %s\n", dados.horarioDoacao);	
				        }
				         if(dados.doacaoAgendada == 3){
				        	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
							printf(" Horário: %s\n", dados.horarioDoacao);	
				        }
				        printf(" Status da Doação: %s\n", dados.statusDoacao);
						printf(" -----\n");
						
	                    //confirmação para excluir
	                    printf("\n Deseja realmente excluir esta doação? (S/N): ");
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo doação...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n Operação cancelada. Doação não será excluída\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);  // Se não confirmado, escreva de volta no arquivo
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
					printf("\n Exclusão realizada com sucesso!\n");
					Sleep(2000);
		            system("cls");
		            //buscaTodosCodigosExclusaoDoador(nomeArquivo);//mostra os cadastros restantes após a exclusão
				}
				printf("\n Excluir outra doação? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a opção não for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
	
return 0;
}//fim da função excluir

int aprovarAgendamentoDoacao(const char *nomeArquivo){//início da função aprovar agendamento de doação
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+"); //leitura e gravação para fazer alteração usar +
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	system("cls");
	printf(" *Aprovar Doações*\n");
	relatorioPorAgendamentos(nomeArquivo);
	printf("\n Código da doação que deseja aprovar ou 0 para cancelar: ");
	scanf("%d",&codigo);
	
	while(codigo != 0)
	{
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system("pause");
            system("cls");
		}
		else{
			
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			if(strcmp(dados.statusDoacao,"APROVADO") == 1){
				system("cls");
				printf("\n\n ***DADOS DA DOAÇÃO***\n");
				printf("\n Código Doador: %d\n", dados.codigoDoador);
				printf(" Código Doação: %d\n", dados.codigo);
	            printf(" Tipo de doação(1-Dinheiro/2-Outros): %d\n", dados.tipoDoacao);
	            if(dados.tipoDoacao == 1)
	            	printf(" Valor: R$ %.2f\n", dados.valorDoacao);
	            if(dados.tipoDoacao == 2)
	            	printf(" Observação %s\n", dados.observacaoDoacao);
	            printf(" Forma de doação(1-Agendamento/2-Pix/3-Entrega): %d\n", dados.doacaoAgendada);
	            if(dados.doacaoAgendada == 1){
	            	printf(" Data de retirada: %02d/%02d/%04d\n", dados.dataRetirada.dia, dados.dataRetirada.mes, dados.dataRetirada.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	             if(dados.doacaoAgendada == 3){
	            	printf(" Data da entrega: %02d/%02d/%04d\n", dados.dataEntrega.dia, dados.dataEntrega.mes, dados.dataEntrega.ano);
					printf(" Horário: %s\n", dados.horarioDoacao);	
	            }
	            printf(" Status da Doação: %s\n", dados.statusDoacao);
	            printf("-----\n");
			      
				printf("\n *APROVAR AGENDAMENTO*\n");
				printf("\n Deseja aprovar esse agendamento (S/N): ");
				
				if(toupper(getche())=='S'){
					strcpy(dados.statusDoacao, "APROVADO");
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
					fclose(arquivo);
					printf("\n\n *** DOAÇÃO APROVADA COM SUCESSO! ***\n\n");
					system(" pause");
				}
				else{
					printf("\n Operação cancelada.\n");
	                fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);
				}
			}
			else{
				desenhaLinha(28);
				printf(" Doação já foi aprovada.\n");
				desenhaLinha(28);
		        system(" pause");
			}
		}
		system("cls");
		printf("\n\n *Doações*\n");
		relatorioPorAgendamentos(nomeArquivo);
		printf("\n Código da doação que deseja aprovar ou 0 para cancelar ou 0 para cancelar: ");
		scanf("%d",&codigo);	
		//abrindo o arquivo novamente aqui pra poder ficar no loop
		arquivo=fopen(nomeArquivo,"rb+"); //leitura e gravação para fazer alteração usar +
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
}//fim da função aprovar agendamento de doação
//fim das funções utilizadas para doação

void executandoOpcao5(){//início da funçao executandoOpcao5, usado apenas para gerenciar doações
	int opcao, op;
	do{		
		printf("\n *Gerenciar Doações*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Aprovar Agendamento\n");
		printf(" 5-Relatório\n");
		printf(" 0-Retornar\n");
		printf(" Opção: ");
		scanf("%d",&opcao);

		if(opcao == 1){
			printf("\n *Cadastrar Doação*\n");
			cadastrarDoacao("arquivoDoacao.bin");				
		}
		if(opcao == 2){
			printf("\n *Editar Doação*\n");
			editarDoacao("arquivoDoacao.bin");
		}
		if(opcao == 3){
			printf("\n *Excluir Doação*\n");
			excluirDoacao("arquivoDoacao.bin");	
		}
		if(opcao == 4){
			printf("\n *Aprovar Agendamento*\n");
			aprovarAgendamentoDoacao("arquivoDoacao.bin");	
		}
		if(opcao == 5){
			printf("\n *Relatório*\n");
			relatorioDoacao("arquivoDoacao.bin");
		}
		if(opcao < 0 || opcao > 5){
			system("cls");
			desenhaLinha(50);
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da funçao executandoOpcao5, usado apenas para gerenciar Doação

//início das funções utilizadas para atividade/tarefa
int buscaPorCodigoAtividadeTarefa(const char *nomeArquivo){//início função busca por código usada no relatório na opção por código
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
    printf("\n Código ou 0 para cancelar: ");
    scanf("%d", &codigo);
    
    while(codigo > 0) {
        pos = busca(arquivo, codigo);//pos recebe o return da função de busca
        if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
        } 
		else {
            fseek(arquivo, pos, SEEK_SET);//reposiciona o ponteiro para a posição correta
            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
            printf("\n *** DADOS ENCONTRADOS! ***\n");
            printf(" Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Descrição: %s\n", dados.descricao);
            printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
            printf(" -----\n");
            system(" pause");
        }
		system("cls");
        printf("\n\n *Consultar por cadastro*");
        printf("\n Código ou 0 para cancelar: ");
        scanf("%d", &codigo);
        system("cls");
    }
    fclose(arquivo);
}//fim da função busca por código
 
int buscaTodosCodigosAtividadeTarefa(const char *nomeArquivo){//início função busca todos os códigos usado no relatório após excluir
	dadosNecessarios dados;
	FILE *arquivo;
	int encontrado=0;
    printf("\n *Atividade/Tarefa Disponíveis*\n");

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
            printf("\n Código: %d\n", dados.codigo);
            printf(" Nome: %s\n", dados.nome);
            printf(" Descrição: %s\n", dados.descricao);
            printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
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
    
}//fim da função busca todos os códigos

void buscaTodosCodigosExclusaoAtividadeTarefa(const char *nomeArquivo) {//início da função de busca após a exclusão
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
        printf(" Código: %d\n", dados.codigo);
        printf(" Nome: %s\n", dados.nome);
        printf(" Descrição: %s\n", dados.descricao);
        printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
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
}//fim da função de busca após a exclusão

int buscaAtividadeTarefaNaoIniciada(const char *nomeArquivo){//início função busca atividades não iniciadas
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
           if(dados.status == 0){//apenas mostrar as atividades/tarefas não iniciadas 
				
				encontrado=1;
				printf("\n Código: %d\n", dados.codigo);
	            printf(" Nome: %s\n", dados.nome);
	            printf(" Descrição: %s\n", dados.descricao);
	            printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
	            printf(" -----\n");
	       }
    	}
    	if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma atividade não iniciada \n");
	        desenhaLinha(30); 
    	}	
    	fclose(arquivo);	
    }
    system(" pause");
    system("cls");
}//fim da função busca atividades não iniciadas

int buscaAtividadeTarefaEmAndamento(const char *nomeArquivo){//início função busca atividades em andamento
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
				printf("\n Código: %d\n", dados.codigo);
	            printf(" Nome: %s\n", dados.nome);
	            printf(" Descrição: %s\n", dados.descricao);
	            printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
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
}//fim da função busca atividades em andamento
 
int buscaAtividadeTarefaConcluida(const char *nomeArquivo){//início função busca atividade concluída
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
           if(dados.status == 2){//apenas mostrar as atividades/tarefas concluídas 
				
				encontrado=1;
				printf("\n Código: %d\n", dados.codigo);
	            printf(" Nome: %s\n", dados.nome);
	            printf(" Descrição: %s\n", dados.descricao);
	            printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
	            printf(" -----\n");
	       }
    	}
    	if(encontrado == 0){
    		desenhaLinha(30);
	        printf(" Nenhuma atividade concluída \n");
	        desenhaLinha(30);
    	}	
    	fclose(arquivo);	
    }
    system(" pause");
    system("cls");
}//fim da função busca atividade concluída

int cadastrarAtividadeTarefa(const char *nomeArquivo){//início da função de cadastro 
    int opcao, codigo, encontrado, pos, status;
	dadosNecessarios dados;
	FILE *arquivo;
	system("cls");
	printf("\n *Cadastrar*\n");
	arquivo = fopen(nomeArquivo,"ab+");//utilizando para abrir o arquivo tanto para leitura quanto para escrita.
		
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Arquivo não pode ser criado\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	else
	{
		do{
			system("cls");
			printf("\n *Cadastrar*\n");
			
			printf(" Código: ");
			scanf("%d", &codigo);
			
			pos=busca(arquivo,codigo);//função de busca
			
			if(pos == -1){//código não encontrado e vai cadastrar
			  	dados.codigo = codigo;
				
				printf(" Nome: "); 
				fflush(stdin); 
				gets(dados.nome);
				
				printf(" Descrição: "); 
				fflush(stdin); 
				gets(dados.descricao);
				
				printf(" Status \n");
				printf(" 0- Não iniciado\n");
				printf(" 1- Em andamento\n");
				printf(" 2- Concluído\n");
				printf(" Qual o status da atividade/tarefa: ");
				scanf("%d",&dados.status);
				
				fwrite(&dados,sizeof(dadosNecessarios), 1, arquivo);
				
				printf("\n Cadastro realizado com sucesso!\n\n");
				system(" pause");
			}  
			else{//código encontrado
				desenhaLinha(40); 
				printf(" Este código já está vinculado a um cadastro!\n");
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
}//fim da função de cadastro

int relatorioAtividadeTarefa(const char *nomeArquivo) {//início da função de relatório
    int op;
    system("cls");
    printf("\n *Relatório*\n");
    printf(" 1- Por cadastro\n");
    printf(" 2- Atividades não iniciadas\n");
    printf(" 3- Atividades em andamentos\n");
    printf(" 4- Atividades concluídas\n");
    printf(" 5- Todos os cadastros\n");
    printf(" 0- Retornar\n");
    printf(" Opção: ");
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
            printf("     Opção inválida! Escolha outra opção.\n");
            desenhaLinha(50);
            getch();//da uma pausa na tela
        }
        system("cls");
        printf("\n *Relatório*\n");
        printf(" 1- Por cadastro\n");
        printf(" 2- Atividades não iniciadas\n");
	    printf(" 3- Atividades em andamentos\n");
	    printf(" 4- Atividades concluídas\n");
	    printf(" 5- Todos os cadastros\n");
	    printf(" 0- Retornar\n");
        printf(" Opção: ");
        scanf("%d", &op);
        system("cls");
    }
    return 1;//relatório foi gerado com sucesso
}//fim da função de relatório

int editarAtividadeTarefa(const char *nomeArquivo){//início da função editar
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
		printf("\n Código do cadastro que deseja editar ou 0 para cancelar: ");
		scanf("%d",&codigo);
		
		if(codigo == 0) {
            break;//sai do loop se o código for zero
        }
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
			do{
				system("cls");
				printf("\n\n *** EDIÇÃO DE DADOS ***\n");
				printf(" Código: %d\n", dados.codigo);
		        printf(" A- Nome: %s\n", dados.nome);
		        printf(" B- Descrição: %s\n", dados.descricao);
       			printf(" C- Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
				printf(" -----\n");
			    
			    printf(" Deseja editar este cadastro? (S/N): ");
                scanf(" %c", &continuarEdicao);
                
				if (continuarEdicao == 'S' || continuarEdicao == 's'){
				
					do {
				        printf("\n Qual a opção que deseja editar?: ");
				        scanf(" %c", &opAlterar);
				        opAlterar = toupper(opAlterar);
				
				        switch (opAlterar) {
				            case 'A':
				                printf("\n *Alterar Nome*\n");
				                printf(" Informe o novo nome: ");
				                fflush(stdin);
				                gets(dados.nome);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'B':
				                printf("\n *Alterar Descrição*\n");
				                printf(" Informe a nova Descrição: ");
				                fflush(stdin);
				                gets(dados.descricao);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
				
				            case 'C':
				                printf("\n *Alterar Status*\n");
				                printf(" 0- Não iniciado\n");
				                printf(" 1- Em andamento\n");
				                printf(" 2- Concluído\n");
				                printf(" Qual o novo status da atividade/tarefa: ");
				                scanf("%d", &dados.status);
				                printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
								system(" pause");
				                break;
		
				            default:
				            	desenhaLinha(34);
				                printf(" Opção inválida. Tente novamente.\n");
				                desenhaLinha(34);
				                break;
				        }
				
				    }while(opAlterar < 'A' || opAlterar > 'D');	  
					fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
					fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
				
					printf("\n Deseja editar outra opção neste cadastro? (S/N): ");
				 	scanf(" %c", &continuarEdicao);
				}
            }while (continuarEdicao == 'S' || continuarEdicao == 's');//enquanto digitar s continua)
		}	
	}while(codigo != 0);

    fclose(arquivo);
    system("cls");
}//fim da função editar

int excluirAtividadeTarefa(const char *nomeArquivo) {//início da função excluir
    FILE *arquivo, *temp;
    dadosNecessarios dados;
    int pos,codigo, marcador=0;
    char nome[30],opcao, confirmacao;

	do{
		arquivo = fopen(nomeArquivo, "rb");//abre o arquivo no modo leitura binária
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
	    printf("\n Código do cadastro que deseja excluir ou 0 para cancelar: ");
		scanf("%d",&codigo);
	
	    if(codigo > 0)
		{
	        pos = busca(arquivo, codigo);//chama função de busca
	        if(pos == -1) {
	            desenhaLinha(28);
	            printf("  Cadastro não encontrado!\n");
	            desenhaLinha(28);
	            system(" pause");
	            fclose(arquivo);//fecha o arquivo antes de retornar
	            return 1;
	        } 
			else {
				fclose(arquivo);//fecha o arquivo após a leitura inicial
				temp = fopen("arquivoTemporario.bin", "wb");
	            
                arquivo = fopen(nomeArquivo, "rb");//abre o arquivo novamente, agora no modo escrita binária
	            
				rewind(arquivo);
	            fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
	            
				while(!feof(arquivo)) {
	                if(codigo != dados.codigo)
	                	fwrite(&dados, sizeof(dadosNecessarios), 1, temp);
	                else{   
	                    printf("\n\n *** CADASTRO ENCONTRADO! ***\n");
						printf(" Código: %d\n",dados.codigo);
					    printf(" Nome: %s\n",dados.nome);
					    printf(" Descrição: %s\n", dados.descricao);
       					printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
						printf(" -----\n");
						
	                    //confirmação para excluir
	                    printf("\n Deseja realmente excluir este cadastro? (S/N): ");
	                    confirmacao = toupper(getch());
					    if(confirmacao == 'S') {
							marcador=1;
	                        printf("\n\n Excluindo cadastro...\n");
	                        Sleep(2000);
	                        system("cls");
	                    }
						else {
	                        printf("\n\n Operação cancelada. Cadastro não será excluído\n");
	                        fwrite(&dados, sizeof(dadosNecessarios), 1, temp);  // Se não confirmado, escreva de volta no arquivo
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
					printf("\n Exclusão realizada com sucesso!\n");
					system(" pause");
		            system("cls");
		            buscaTodosCodigosExclusaoAtividadeTarefa(nomeArquivo);//mostra os cadastros restantes após a exclusão
				}
				printf("\n Excluir outro cadastro? (S/N): ");
		        opcao = toupper(getch());
		        fflush(stdin);//limpa o buffer de entrada para evitar problemas
		        system("cls");
		        
		        fclose(arquivo);//fechando o arquivo antes de retornar
		        
			    if (opcao != 'S') {
                	break;//para sair do loop externo se a opção não for 'S'
            	}
			}
	    }
	    system("cls");
	}while(codigo > 0);
return 0;
}//fim da função excluir

//início da função de registro de realização de atividades
int registrarAtividadeTarefaRealizada(const char *nomeArquivo){//início da função registrar atividade realizada
	FILE *arquivo;
	dadosNecessarios dados;
	int codigo, pos;
	char opAlterar,continuarEdicao;
	
	arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
	if(arquivo == NULL){
		desenhaLinha(28);
		printf("  Erro ao abrir o arquivo.\n");
		desenhaLinha(28);
        system(" pause");
		return 0;//encerra o programa
	}
	printf("\n Código da atividade que deseja registrar ou 0 para cancelar: ");
	scanf("%d",&codigo);
	
	while(codigo != 0)
	{
		pos = busca(arquivo,codigo);//chamando função que busca e imprime os dados que ela achou
		
		if(pos == -1) {
            desenhaLinha(28);
            printf("  Cadastro não encontrado!\n");
            desenhaLinha(28);
            system(" pause");
            system("cls");
		}
		else{
			fseek(arquivo, pos, SEEK_SET);
			fread(&dados, sizeof(dadosNecessarios), 1, arquivo);
		
			system("cls");
			printf("\n *Aprovar Doação*\n");
			printf("\n\n *** DADOS ATIVIDADE/TAREFA***\n");
			printf(" Código: %d\n", dados.codigo);
	        printf(" Nome: %s\n", dados.nome);
	        printf(" Descrição: %s\n", dados.descricao);
   			printf(" Status(0- Não iniciado/1- Em andamento/2- Concluído): %d\n", dados.status);
			printf(" -----\n");
		      
			printf("\n *Alterar Status*\n");
			printf(" 0- Não iniciada\n");
			printf(" 1- Em andamento\n");
			printf(" 2- Concluída\n");
			printf("\n Qual o novo status da atividade/tarefa: "); 
			scanf("%d",&dados.status);
	        	  
			fseek(arquivo,pos,0);//posicionando o ponteiro no exato lugar onde é para alterar
			fwrite(&dados,sizeof(dadosNecessarios),1,arquivo);//escreve, sendo assim fez a alteração
			fclose(arquivo);
			printf("\n *** ALTERAÇÃO CONCLUÍDA! ***\n\n");
			getch();//da uma pausa na tela
		}
		system("cls");
		
		printf("\n Código da atividade que deseja registrar ou 0 para cancelar: ");
		scanf("%d",&codigo);	
		//abrindo o arquivo novamente aqui pra poder ficar no loop
		arquivo=fopen(nomeArquivo,"rb+");//leitura e gravação para fazer alteração usar +
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
}//fim da função registrar atividade realizada
//fim das funções utilizadas para Atividade/Tarefa

void executandoOpcao6(){//início da funçao executandoOpcao6, usado apenas para gerenciar Atividades/Tarefas
	int opcao, op;
	do{		
		printf("\n *Gerenciar Atividades/Tarefas*\n");
		printf(" 1-Cadastrar\n");	
		printf(" 2-Editar\n");
		printf(" 3-Excluir\n");
		printf(" 4-Registrar Realização Atividade/Tarefa Realizada\n");
		printf(" 5-Relatório\n");
		printf(" 0-Retornar\n");
		printf(" Opção: ");
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
			printf("\n *Registrar Realização de Atividades/Tarefas*\n");
			registrarAtividadeTarefaRealizada("cadastroAtividadeTarefa.bin");
		}
		if(opcao == 5){
			printf("\n *Relatório*\n");
			relatorioAtividadeTarefa("cadastroAtividadeTarefa.bin");
		}
		if(opcao < 0 || opcao > 5){
			system("cls");
			desenhaLinha(50);
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
	}while(opcao != 0);
	system("cls");
}//fim da funçao executandoOpcao6, usado apenas para gerenciar Atividades/Tarefas

//fim das funções
void exibirArvoreDeNatal(int n) {
    //limpar a tela
    system("cls");
	printf("\n\n Nós, participantes do Projeto Integrador II - ONG Creche Junqueira, desejamos a todos um Natal repleto de alegria e um Ano Novo cheio de realizações e prosperidade!\n\n");
    //koop para a árvore
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

    //tronco da árvore
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
    printf("\n * Feliz natal *\n  * Até 2024 *     \n\n");
	printf(" Andressa de Farias\n");
    printf(" André de Osti Garcia Badan\n");
    printf(" Dayane Tiziani Boa Ventura\n");
    printf(" Deivid Lucas Muller Maia\n");
    printf(" Leonardo da Silveira Domingos\n");
    printf(" Nátaly Lara Moraes da Silva\n");
    printf(" Rafael Haddad de Lima\n");
}
 
void executandoMenu(){//início da função que executa o menu principal
	int opcao;
	do{
		printf("\n ======= SISTEMA DE GERENCIAMENTO CRECHE JUNQUEIRA =======\n");
		
		printf("\n    *PAINEL ADMIN*\n");	
		printf(" 1-Gerenciar Voluntários\n");
		printf(" 2-Gerenciar Doadores\n");
		printf(" 3-Gerenciar Empresas Parceiras\n");
		printf(" 4-Gerenciar Projetos\n");
		printf(" 5-Gerenciar Doações\n");
		printf(" 6-Gerenciar Atividades/Tarefas\n");
		printf(" 0-Sair\n");
		printf(" Opção: ");
		scanf("%d",&opcao);
	
		if(opcao == 1){
			system("cls");
			//printf("\n *Gerenciar Voluntários*\n");
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
			//printf("\n *Agendar Doação*\n");
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
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
			
	}while(opcao != 0);
	
}//fim da função que executa o menu principal

void menuDoador(){//início da função de login doador
	int opcao;
	do{
		
		printf("\n ======= PÁGINA DO DOADOR =======\n");
	    printf("\n *SEJA BEM VINDO A CRECHE JUNQUEIRA*\n");
	    printf(" Contribua para um futuro brilhante das crianças!\n");
	    printf(" Sua doação faz toda a diferença.\n\n");
		
		printf("\n   *MENU*\n");	
		printf(" 1-Cadastrar-se\n");
		printf(" 2-Editar Informações Pessoais\n");
		printf(" 3-Faça sua Doação\n");
		printf(" 4-Editar Informações sobre a Doação\n");
		printf(" 5-Visualizar Histórico de Doações\n");
		printf(" 0-Sair\n");
		printf(" Opção: ");
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
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
			
	}while(opcao != 0);
}//fim da função de login doador

void menuVoluntario(){//início da função de login Voluntario
	int opcao;
	do{
		
		printf("\n ======= PÁGINA DO VOLUNTÁRIO =======\n");
		printf("\n *SEJA UM VOLUNTÁRIO NA CRECHE JUNQUEIRA*\n");
		printf(" Junte-se a nós para fazer a diferença na vida das crianças!\n");
		printf(" Sua dedicação como voluntário é uma luz brilhante para o futuro delas.\n\n");
		
		printf("\n   *MENU*\n");	
		printf(" 1-Cadastrar-se\n");
		printf(" 2-Editar Informações Pessoais\n");
		printf(" 3-Visualizar Atividades/Tarefas Disponíveis\n");
		printf(" 0-Sair\n");
		printf(" Opção: ");
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
			printf("     Opção inválida! Escolha outra opção.\n");
			desenhaLinha(50);	
		}
			
	}while(opcao != 0);
}//fim da função de login Voluntario

main()
{
	setlocale(LC_ALL,"Portuguese");
	
	int n = 8;//altura da árvore (número de camadas)
	int op, opcao;

	do{
	
		system("cls");
		printf("\n\n	************************************\n");
	    printf("	*                                  *\n");
	    printf("	*             LOGIN                *\n");
	    printf("	*                                  *\n");
	    printf("	************************************\n");
    
    
    
	    printf("\n   	 1- Doador\n");
	    printf("    	 2- Voluntário\n");
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
			printf("     Usuário inválido! Por favor, se identifique.\n");
			desenhaLinha(55);
			system(" pause");
	    }
	    
	}while(op != 0);
	
	system("cls");
	printf("\n Você está saindo do sistema.....");
	system(" pause");
	
	exibirArvoreDeNatal(n);		
}
	
		


