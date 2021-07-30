#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>
#include<unistd.h>
typedef struct{
    char nome[51];
    float preco;
    int codigo;
    int estoque;
    int quantidade;
}produto;


typedef struct{
    int data;
    int quantidadeProdutoVendido;
    int precoProduto;
    int codigoProduto;
    int codigoDaVenda;
    char nomeDoProduto[51];
    float vendidoPor;
    int totalVendidoPorProduto;
}venda;

/**produto*/
void limparListaProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int encontrarLugarProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int cadastrarProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int validarCodigo(produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int excluirProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int editarProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
/**venda*/
void limparListaVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda);
int realizarVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int excluirVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int verAsVendasDeUmMes(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int verAsVendasDeUmProduto(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto);
int verOsProdutosMaisVendidos(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto, int quantidadeMaximaDeVendasPorProduto);

int listarProdutos(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){
        printf("\n =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Lista de Produtos =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
        printf("=-= |     PRODUTO     | =-=-=-=-=-=-= | CODIGO | =-=-=-=- | ESTOQUE | =-=-= |   PREÇO    | =-=-=-\n");
        int contador = 0;
        for(int i = 0; i < quantidadeDeElementosListaProduto; i++){
            if(listaDeProdutos[i].codigo != -1){
                printf("=-= | ");
                for(int a = 0; a < 15; a++){
                    if(listaDeProdutos[i].nome[contador] != '\0'){
                        printf("%c", listaDeProdutos[i].nome[contador]);
                        contador++;
                    }
                    else{
                        printf(" ");
                    }
                }
                contador = 0;
                printf(" | =-=-=-=-=-=-= | ");
                printf("%d", listaDeProdutos[i].codigo);
                if(listaDeProdutos[i].codigo < 10)
                    printf("     ");
                else if(listaDeProdutos[i].codigo < 100)
                    printf("    ");
                else if(listaDeProdutos[i].codigo < 1000)
                    printf("   ");
                else if(listaDeProdutos[i].codigo < 10000)
                    printf("  ");
                else if(listaDeProdutos[i].codigo < 100000)
                    printf(" ");
                printf(" | =-=-=-=-");

                printf(" | ");
                printf("%d", listaDeProdutos[i].quantidade);
                if(listaDeProdutos[i].quantidade < 10)
                    printf("      ");
                else if(listaDeProdutos[i].quantidade < 100)
                    printf("     ");
                else if(listaDeProdutos[i].quantidade < 1000)
                    printf("    ");
                else if(listaDeProdutos[i].quantidade < 10000)
                    printf("   ");
                else if(listaDeProdutos[i].quantidade < 100000)
                    printf("  ");
                else if(listaDeProdutos[i].quantidade < 1000000)
                    printf(" ");
                printf(" | =-=-= | ");
                printf("%.2f", listaDeProdutos[i].preco);
                if(listaDeProdutos[i].preco < 10)
                    printf("      ");
                else if(listaDeProdutos[i].preco < 100)
                    printf("     ");
                else if(listaDeProdutos[i].preco < 1000)
                    printf("    ");
                else if(listaDeProdutos[i].preco < 10000)
                    printf("   ");
                else if(listaDeProdutos[i].preco < 100000)
                    printf("  ");
                else if(listaDeProdutos[i].preco < 1000000)
                    printf(" ");
                printf(" | =-=-=-\n");
            }
        }
    sleep(1);
    return 1;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    FILE *arquivoDeTextoProdutos;
    FILE *arquivoDeTextoVendas;
    int quantidadeMaximaDeVendasPorProduto = 1200, quantidadeDeElementosListaProduto = 100, quantidadeDeElementosListaVenda = 1000;
    int menuProdutos = 0, menuVendas = 0, menuRelatorios = 0, condicaoDeParada = 1;
    char menu1[50];
    produto listaDeProdutos[quantidadeDeElementosListaProduto];
    venda listaDeVendas[quantidadeDeElementosListaVenda];

    arquivoDeTextoProdutos = fopen("arquivoDeProdutos.txt", "rb+");
    if(arquivoDeTextoProdutos == NULL){
        arquivoDeTextoProdutos = fopen("arquivoDeProdutos.txt", "wb+");
        if(arquivoDeTextoProdutos == NULL){
            printf("Erro ao abrir o arquivo de produtos =(");
            return 0;
        }
        limparListaProduto(listaDeProdutos, quantidadeDeElementosListaProduto);
        fseek(arquivoDeTextoProdutos,0,SEEK_SET);
        fwrite(listaDeProdutos,sizeof(produto), quantidadeDeElementosListaProduto, arquivoDeTextoProdutos);
        fclose(arquivoDeTextoProdutos);
    }
    else{
        fseek(arquivoDeTextoProdutos,0,SEEK_SET);
        fread(listaDeProdutos,sizeof(produto), quantidadeDeElementosListaProduto, arquivoDeTextoProdutos);
        fclose(arquivoDeTextoProdutos);
    }
    arquivoDeTextoVendas = fopen("arquivoDeVendas.txt", "rb+");
    if(arquivoDeTextoVendas == NULL){
        arquivoDeTextoVendas = fopen("arquivoDeVendas.txt", "wb+");
        if(arquivoDeTextoVendas == NULL){
            printf("Erro ao abrir o arquivo de vendas =(");
            return 0;
        }
        limparListaVenda(listaDeVendas, quantidadeDeElementosListaVenda);
        fseek(arquivoDeTextoProdutos,0,SEEK_SET);
        fwrite(listaDeVendas,sizeof(venda), quantidadeDeElementosListaVenda, arquivoDeTextoVendas);
        fclose(arquivoDeTextoVendas);
    }
    else{
        fseek(arquivoDeTextoVendas,0,SEEK_SET);
        fread(listaDeVendas,sizeof(venda), quantidadeDeElementosListaVenda, arquivoDeTextoVendas);
        fclose(arquivoDeTextoVendas);
    }

    printf("=-=-=-=-=-=-=-=-=-=-| Ola! |=-=-=-=-=-=-=-=-=-=-\n | Bem vindo ao sistema de produtos e vendas |\n\n");
    while (condicaoDeParada == 1)
    {
        printf("\n \t       | MENU PRINCIPAL | \n");
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n");
        printf("Insira o que deseja fazer!\n");
        printf("Digite: \n| 1 | Caso deseja tratar de produtos\n| 2 | Para operar vendas\n| 3 | Para relatorios\nPara sair, pressione enter!\n");

        arquivoDeTextoProdutos = fopen("arquivoDeProdutos.txt", "wb+");
        if(arquivoDeTextoProdutos == NULL)
            return 0;
        arquivoDeTextoVendas = fopen("arquivoDeVendas.txt", "wb+");
        if(arquivoDeTextoVendas == NULL)
            return 0;
        fwrite(listaDeProdutos, sizeof(produto), quantidadeDeElementosListaProduto, arquivoDeTextoProdutos);
        fwrite(listaDeVendas, sizeof(venda), quantidadeDeElementosListaVenda, arquivoDeTextoVendas);
        fclose(arquivoDeTextoProdutos);
        fclose(arquivoDeTextoVendas);

        setbuf(stdin, 0);
        fgets(menu1,2,stdin);
        int validacao = 0;
        if(strcmp(menu1, "\n") == 0){
            return 0;
        }
        if(strcmp(menu1, "1")==0){
            validacao = 1;
        }
        else if(strcmp(menu1, "2")==0){
            validacao = 2;
        }
        else if(strcmp(menu1, "3")==0){
            validacao = 3;
        }
        else{
            printf("Insira um valor valido entre | 1 |, | 2 | ou | 3 |! \n");
            continue;
        }

        if(validacao == 1)
        {
            printf("\n\n=-=-=-=- |BEM VINDO AO MENU DE PRODUTOS |=-=-=-=-\n");
            printf("Digite 1 para cadastrar novos produtos!\n");
            printf("Digite 2 para excluir um produto!\n");
            printf("Digite 3 para editar um produto!\n");
            printf("Insira outro valor para sair\n");

            scanf("%d", &menuProdutos);
                if(menuProdutos == 1)
                    condicaoDeParada = cadastrarProduto(listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuProdutos == 2)
                    condicaoDeParada = excluirProduto(listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuProdutos == 3)
                    condicaoDeParada = editarProduto(listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuProdutos > 3 || menuProdutos < 1)
                    continue;
        }


        else if(validacao == 2){
            printf("\n\n=-=-=-=- | BEM VINDO AO MENU DE VENDAS |=-=-=-=-\n");
            printf("Digite 1 para realizar uma venda!\n");
            printf("Digite 2 para excluir uma venda!\n");
            printf("Insira outro valor para sair\n");


            scanf("%d", &menuVendas);
                if(menuVendas == 1)
                    condicaoDeParada = realizarVenda(listaDeVendas, quantidadeDeElementosListaVenda, listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuVendas == 2)
                    condicaoDeParada = excluirVenda(listaDeVendas, quantidadeDeElementosListaVenda, listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuProdutos > 3 || menuProdutos < 1)
                    continue;

        }
        else if(validacao == 3){
            printf("=-=-=-=-RELATÓRIOS=-=-=-=\n");
            printf("Insira | 1 | para ver as vendas realizadas em determinado mês.\n");
            printf("Insira | 2 | para checar vendas de um determinado produto.\n");
            printf("Insira | 3 | para um ranking de produtos mais vendidos.\n");
            printf("Insira outro valor para sair\n");

            scanf("%d", &menuRelatorios);
                if(menuRelatorios == 1)
                    condicaoDeParada = verAsVendasDeUmMes(listaDeVendas, quantidadeDeElementosListaVenda, listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuRelatorios == 2)
                    condicaoDeParada = verAsVendasDeUmProduto(listaDeVendas, quantidadeDeElementosListaVenda, listaDeProdutos, quantidadeDeElementosListaProduto);
                if(menuRelatorios == 3)
                    condicaoDeParada = verOsProdutosMaisVendidos(listaDeVendas, quantidadeDeElementosListaVenda, listaDeProdutos, quantidadeDeElementosListaProduto, quantidadeMaximaDeVendasPorProduto);
                if(menuRelatorios == 4)
                    condicaoDeParada = listarProdutos(listaDeProdutos, quantidadeDeElementosListaProduto);
                else{
                    continue;
                }
        }
    }

    printf("Fim do programa!");
    fclose(arquivoDeTextoProdutos);
    fclose(arquivoDeTextoVendas);

    if(fopen("arquivoDeProdutos.txt", "wb+") == 0){
        printf("Erro ao abrir o arquivo!");
    }
    if(fopen("arquivoDeVendas.txt", "wb+") == 0){
        printf("Erro ao abrir o arquivo!");
    }
}
/**produtos */
void limparListaProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){
    for(int i = 0; i < quantidadeDeElementosListaProduto; i++)
        listaDeProdutos[i].codigo = -1;
}
int encontrarLugarProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){
int lugarComEspaco = 0;
    for(int i = 0; i < quantidadeDeElementosListaProduto; i++)
        if (listaDeProdutos[i].codigo == -1){
            lugarComEspaco = i;
            printf("Lugar no estoque = | %d | \n", lugarComEspaco);
            return lugarComEspaco;
        }
    return -1;
}
int cadastrarProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){

    int condicao = 0;
    printf("=-=-=| Cadastro |=-=-=-=\n");

    int lugarvazio = encontrarLugarProduto(listaDeProdutos, quantidadeDeElementosListaProduto);
    if(lugarvazio == -1){
        printf("Nao ha mais espaco, exclua algum produto para poder inserir um novo");
        exit(1);
    }
    else{
        /** nome do produto*/
        printf("Nome:\t");
        setbuf(stdin, 0);
        fgets(listaDeProdutos[lugarvazio].nome,50,stdin);
        listaDeProdutos[lugarvazio].nome[strcspn(listaDeProdutos[lugarvazio].nome, "\n")] = 0;
        /** código do produto*/
        printf("Codigo:\t");
        int codigoValido = 0;
        do {
            codigoValido = validarCodigo(listaDeProdutos, quantidadeDeElementosListaProduto);
            if(codigoValido == 0){
                printf("Ja existe um produto com este código, insira outro!: ");
            }
        }
        while(codigoValido == 0);
        listaDeProdutos[lugarvazio].codigo = codigoValido;
        /** preco do produto*/
        printf("Insira o preco:\t");
        scanf("%f", &listaDeProdutos[lugarvazio].preco);
        printf("Insira a quantidade:\t");
        /**quantidade do produto */
        scanf("%d", &listaDeProdutos[lugarvazio].quantidade);
        printf("\n=-=-= | Cadastro Efetuado | =-=-=-=\n");

        //printf(" lugar vazio = %d", lugarvazio);
        printf("\nSe deseja continuar operando, digite 1.\nPara sair do programa, digite 0\n");
        scanf("%d", &condicao);
        while(condicao < 0 || condicao > 1)
            scanf("%d", &condicao);
        if(condicao == 1){
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 1;
        }
        else{
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 0;
        }
    }

}
int excluirProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){
    int opcaoExclusao;
    printf("\n =-=-=| Exclusao |=-=-=-=\n");
    printf("Digite 2 se ja sabe o codigo do produto que deseja excluir!\n");
    printf("Para uma lista de nomes e codigos digite 3\n");
    scanf("%d", &opcaoExclusao);

        if(opcaoExclusao == 3){
        listarProdutos(listaDeProdutos, quantidadeDeElementosListaProduto);
        printf("Digite 2 para inserir o codigo!\n");
        scanf("%d", &opcaoExclusao);
    }

    if(opcaoExclusao == 2){
        int codigoASerExcluido = 0;
        printf("| Insira o codigo do produto que deseja excluir! | \n");
        scanf("%d", &codigoASerExcluido);
        for( int k = 0; k < quantidadeDeElementosListaProduto; k++){
            if(codigoASerExcluido == listaDeProdutos[k].codigo){
                printf("Produto | %s | de codigo | %d | excluido com sucesso.\n\n", listaDeProdutos[k].nome, listaDeProdutos[k].codigo);
                listaDeProdutos[k].codigo = -1;
            }
        }
    }

//}

    int condicao = 0;
    printf("\nSe deseja continuar operando, digite 1.\nPara fechar o programa, digite 0\n");
    scanf("%d", &condicao);
        while(condicao < 0 || condicao > 1){
            printf("Insira um valor válido entre 0 ou 1!\n\nSe deseja continuar operando, digite 1.\nPara fechar o programa, digite 0\n ");
            scanf("%d", &condicao);
        if(condicao == 1){
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 1;
        }
        else{
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 0;
        }

        }
return 1;
}
int editarProduto(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){

    int codigoValido = 0;
    printf("Insira o codigo do protudo que deseja editar!\n");
    printf("Para uma lista de produtos e codigos digite -1!\n");
    scanf("%d", &codigoValido);
    if(codigoValido == -1){
        listarProdutos(listaDeProdutos, quantidadeDeElementosListaProduto);
    }
    printf("\nDigite 2 para inserir o codigo!\n");
    scanf("%d", &codigoValido);

    if(codigoValido == 2){
        printf("Insira o codigo: \t");
        scanf("%d", &codigoValido);
        for(int k = 0; k < quantidadeDeElementosListaProduto; k++){
            if(listaDeProdutos[k].codigo == codigoValido){
                printf("Produto encontrado, vamos as alteracoes!\n");
                printf("Insira o novo nome:\t");
                setbuf(stdin, 0);
                fgets(listaDeProdutos[k].nome,50,stdin);
                listaDeProdutos[k].nome[strcspn(listaDeProdutos[k].nome, "\n")] = 0;
                printf("Insira o novo codigo:\t");
                scanf("%d", &listaDeProdutos[k].codigo);
                printf("Insira o novo preco:\t");
                scanf("%f", &listaDeProdutos[k].preco);
                printf("Insira a nova quantidade em estoque:\t");
                scanf("%d", &listaDeProdutos[k].quantidade);
                printf("Produto alterado com sucesso!\n");
                return 1;
            }
        }
    }
    printf("Produto nao encontrado =(\n");

    int condicao = 0;
    printf("\nSe deseja continuar operando, digite 1.\nPara fechar o programa, digite 0\n");
    scanf("%d", &condicao);
        while(condicao < 0 || condicao > 1){
            printf("Insira um valor válido entre 0 ou 1!\n\nSe deseja continuar operando, digite 1.\nPara voltar ao menu principal, digite 0\n ");
            scanf("%d", &condicao);
        if(condicao == 1){
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 1;
        }
        else{
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 0;
        }
        }
    return 1;
}
int validarCodigo(produto listaDeProdutos[], int quantidadeDeElementosListaProduto){

    int pegarCodigo = 0;
    scanf("%d", &pegarCodigo);
    for(int i = 0; i < quantidadeDeElementosListaProduto; i++){
        if(listaDeProdutos[i].codigo == pegarCodigo){
            return 0;
        }
    }
    return pegarCodigo;
}
/**vendas */
void limparListaVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda){
    for(int i = 0; i < quantidadeDeElementosListaVenda; i++)
        listaDeVendas[i].codigoDaVenda = -1;
}
int encontrarLugarVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda){
int lugarComEspaco = 0;
    for(int i = 0; i < quantidadeDeElementosListaVenda; i++)
        if (listaDeVendas[i].codigoDaVenda == -1){
            lugarComEspaco = i;
            printf("\n\nLugar na prateleira = | %d | \n", lugarComEspaco);
            return lugarComEspaco;
        }
    return -1;
}
int realizarVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto){
    int quantidadeDesejaseVender;
    float custoDeVenda;
    int descontoMenu, calculoDesconto;
    int dataDaVenda;
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Insira o produto que deseja vender!\n");
    printf("Ou entao, para uma lista com produtos e codigos, digite -1\n");
    printf("\nPara sair, digite 0\n\n");
    int menuVenda1 = 0;
    scanf("%d", &menuVenda1);
    if(menuVenda1 == 0)
        return 1;
    else if(menuVenda1 == -1){
        listarProdutos(listaDeProdutos, quantidadeDeElementosListaProduto);
        printf("Insira o produto que deseja vender!\n");
        scanf("%d", &menuVenda1);
    }

    if(menuVenda1 != -1 && menuVenda1 != 0){
    int lugarVazio = encontrarLugarVenda(listaDeVendas, quantidadeDeElementosListaVenda);
        for(int i = 0; i < quantidadeDeElementosListaVenda; i++){
            if(listaDeProdutos[i].codigo == menuVenda1){
                if(listaDeProdutos[i].quantidade != 0){
                    printf("Insira a quantidade de | %s | que deseja vender:\t\n", listaDeProdutos[i].nome);
                    scanf("%d", &quantidadeDesejaseVender);
                    if(listaDeProdutos[i].quantidade-quantidadeDesejaseVender >= 0){
                        listaDeProdutos[i].quantidade = listaDeProdutos[i].quantidade-quantidadeDesejaseVender;
                        strcpy(listaDeVendas[i].nomeDoProduto, listaDeProdutos[lugarVazio].nome);
                        printf("Insira a data da venda: | Ex:. 20 de julho de 2021 -> 20072021 |\t\n");
                        setbuf(stdin, 0);
                        scanf("%d", &listaDeVendas[lugarVazio].data);
                        dataDaVenda = listaDeVendas[lugarVazio].data;
                        listaDeVendas[lugarVazio].quantidadeProdutoVendido = quantidadeDesejaseVender;
                        custoDeVenda = listaDeProdutos[i].preco*quantidadeDesejaseVender;
                        listaDeVendas[lugarVazio].totalVendidoPorProduto = listaDeVendas[lugarVazio].totalVendidoPorProduto + listaDeVendas[lugarVazio].quantidadeProdutoVendido;
                        printf("Insira o codigo da venda:\n");
                        scanf("%d", &listaDeVendas[lugarVazio].codigoDaVenda);
                        listaDeVendas[lugarVazio].codigoProduto = listaDeProdutos[i].codigo;
                        printf("Deseja oferecer desconto ao cliente?\n| 1 | Sim\n| 2 | Nao\n");
                        scanf("%d", &descontoMenu);
                        if(descontoMenu == 1){
                            printf("Insira o desconto em %% ");
                            scanf("%d", &calculoDesconto);
                            custoDeVenda = ((100-calculoDesconto)*(quantidadeDesejaseVender*listaDeProdutos[i].preco))/100;
                            listaDeVendas[lugarVazio].vendidoPor = custoDeVenda;
                            printf("=-=-=-=-=-= Venda Realizada =-=-=-=-=-=");
                            printf("\nCodigo     | %d |\n", listaDeVendas[lugarVazio].codigoDaVenda);
                            printf("Produto    | %s |\n", listaDeProdutos[i].nome);
                            printf("Quantidade | %d |\n", quantidadeDesejaseVender);
                            printf("Custo      | %.2f |\n", custoDeVenda);
                            printf("Data       | %d/%d/%d |\n", dataDaVenda/1000000, (dataDaVenda/10000)%100, (dataDaVenda)%10000);
                            sleep(2);
                            system("cls || clear");
                            return 1;

                        }
                        else{
                            custoDeVenda = (quantidadeDesejaseVender*listaDeProdutos[i].preco);
                            listaDeVendas[lugarVazio].vendidoPor = custoDeVenda;
                            printf("=-=-=-=-=-= Venda Realizada =-=-=-=-=-=");
                            printf("\nCodigo     | %d |\n", listaDeVendas[lugarVazio].codigoDaVenda);
                            printf("Produto    | %s |\n", listaDeProdutos[i].nome);
                            printf("Quantidade | %d |\n", quantidadeDesejaseVender);
                            printf("Custo      | %.2f |\n", custoDeVenda);
                            printf("Data       | %d/%d/%d |\n", dataDaVenda/1000000, (dataDaVenda/10000)%100, (dataDaVenda)%10000);
                            sleep(2);
                            system("cls || clear");
                            return 1;
                        }
                    }
                    else{
                        printf("| ERRO | = Nao ha produtos suficientes no estoque para realizacao desta venda!\n\n\n");
                    }
                }
            }
        }
    return 1;
    }

return 1;

}


int excluirVenda(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto){

    int vendaASerDeletada = 0;
    printf("\n\n");
        printf("=-= | PRODUTO | =-=-=-=-=-=-= | CODIGO DA VENDA | =-=-=-=-\n");
        for(int i = 0; i < quantidadeDeElementosListaVenda; i++){
            if(listaDeVendas[i].codigoDaVenda != -1){
                printf("=-= | ");
                printf("%s", listaDeVendas[i].nomeDoProduto);
                printf(" | =-=-=-=-=-=-= | %d  \n", listaDeVendas[i].codigoDaVenda);
            }
        }
        printf("\n\n");
    printf("Insira o codigo da venda que deseja excluir!");
    scanf("%d", &vendaASerDeletada);
    for(int a = 0; a < quantidadeDeElementosListaVenda; a++){
        if(listaDeVendas[a].codigoDaVenda == vendaASerDeletada){
            listaDeVendas[a].codigoDaVenda = -1;
            printf("Venda excluida com sucesso!");
        }
        else{
            printf("Venda nao encontrada =(");
            return 0;
        }
    }
    int condicao = 0;
    printf("\nSe deseja continuar operando, digite 1.\nPara fechar o programa, digite 0\n");
    scanf("%d", &condicao);
        while(condicao < 0 || condicao > 1){
            printf("Insira um valor válido entre 0 ou 1!\n\nSe deseja continuar operando, digite 1.\nPara fechar o programa, digite 0\n ");
            scanf("%d", &condicao);
        if(condicao == 1){
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 1;
        }
        else{
            printf("\nRecuperando operações. . .");
            sleep(2);
            system("cls || clear");
            return 0;
        }
        }
    return 1;
}
/** Relatórios */
int verAsVendasDeUmMes(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto){

    int mesASerAnalisado = 0, data = 0;
    printf("Insira o mês que deseja analisar as vendas: | Ex:. ""julho"" = 7 \n");
    scanf("%d", &mesASerAnalisado);
    printf("=-=-=-=-=- Vendas do mes | %d | =-=-=-=-=-\n", mesASerAnalisado);
    for (int a = 0; a < quantidadeDeElementosListaVenda; a++){
        data = listaDeVendas[a].data;
        if((data/10000)%100 == mesASerAnalisado){
            printf("| %d | unidades de | %s | ____ Vendido por = | %.2f |. Operação datada de | %d/%d/%d | __\n", listaDeVendas[a].quantidadeProdutoVendido, listaDeVendas[a].nomeDoProduto, listaDeVendas[a].vendidoPor, listaDeVendas[a].data/1000000, (listaDeVendas[a].data/10000)%100,listaDeVendas[a].data%10000);
        }
    }
    return 1;
}
int verAsVendasDeUmProduto(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto){

        listarProdutos(listaDeProdutos, quantidadeDeElementosListaProduto);

        int produtoQueDesejaseAnalisarAsVendas = 0;
        printf("Insira o codigo do produto que deseja olhar as vendas: ");
        scanf("%d", &produtoQueDesejaseAnalisarAsVendas);
        printf("=-=-=-==-=-=-==-=-=-==-=-=-==-=-=-==-=-=-=\n");
        for(int i = 0; i < quantidadeDeElementosListaVenda; i++){
            if(listaDeVendas[i].codigoProduto == produtoQueDesejaseAnalisarAsVendas){
                printf("| %d | unidades de | %s | ____ vendido por = | %.2f |. Data da operação = | %d/%d/%d | __ CODIGO DA VENDA = | %d |\n", listaDeVendas[i].quantidadeProdutoVendido, listaDeVendas[i].nomeDoProduto, listaDeVendas[i].vendidoPor, listaDeVendas[i].data/1000000, (listaDeVendas[i].data/10000)%100,listaDeVendas[i].data%10000, listaDeVendas[i].codigoDaVenda);
            }
        }
            return 1;
}
int verOsProdutosMaisVendidos(venda listaDeVendas[], int quantidadeDeElementosListaVenda, produto listaDeProdutos[], int quantidadeDeElementosListaProduto, int quantidadeMaximaDeVendasPorProduto){

    for(int a = 0; a < quantidadeDeElementosListaVenda; a++){
        for(int i = quantidadeMaximaDeVendasPorProduto; i > 0; i--){
            if(listaDeVendas[a].quantidadeProdutoVendido == i){
                if(listaDeVendas[a].codigoDaVenda!= -1){
                    printf("| %d | unidades de | %s | ____ Vendido por = | %.2f |. Operação datada de | %d/%d/%d | __ CODIGO DA VENDA = %d\n", listaDeVendas[a].quantidadeProdutoVendido, listaDeVendas[a].nomeDoProduto, listaDeVendas[a].vendidoPor, listaDeVendas[a].data/1000000, (listaDeVendas[a].data/10000)%100,listaDeVendas[a].data%10000, listaDeVendas[a].codigoDaVenda);
                    break;
                }
            }
        }
    }
    return 1;
}
