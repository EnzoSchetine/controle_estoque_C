#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int system();
struct produtos
{
    char nome[20];
    int quant_atual;
    int min_estoque;
    char validade[6];
};
typedef struct produtos produtos;
void menu();
void limpar();
int tamanho_arquivo();
void entra_produto(produtos *produto);
void lista_produto(produtos *produto);
void pesquisa_produto(produtos *produto);
void pesquisa_letra(produtos *produto);
void pesquisa_data(produtos *produto);
void lista_abaixo_min(produtos *produto);
void altera_estoque(produtos *produto);
void altera_produto(produtos *produto);
void exclui_produto(produtos *produto);
main()
{
    setlocale(LC_ALL, "Portuguese");
    produtos produto;
    char escolha;
    int i;
    for(;;)
    {
        system("cls");
        menu();
        escolha = getchar();
        setbuf(stdin,NULL);
        switch(escolha)
        {
            case '1':
            {
                entra_produto(&produto);
                break;
            }
            case '2':
            {
                lista_produto(&produto);
                break;
            }
            case '3':
            {
                pesquisa_produto(&produto);
                break;
            }
            case '4':
            {
                pesquisa_letra(&produto);
                break;
            }
            case '5':
            {
                pesquisa_data(&produto);
                break;
            }
            case '6':
            {
                lista_abaixo_min(&produto);
                break;
            }
            case '7':
            {
                altera_estoque(&produto);
                break;
            }
            case '8':
            {
                altera_produto(&produto);
                break;
            }
            case '9':
            {
                exclui_produto(&produto);
                break;
            }
            case '0':
            {
                exit(0);
            }
            default:
            {
                printf("Opção inválida\n");
                limpar();
                break;
            }
        }
    }
}
void menu()
{
    printf("\tDesafío 2\n");
    printf("1. Entrada de produto\n");
    printf("2. Lista todos os produtos\n");
    printf("3. Pesquisa produto por nome\n");
    printf("4. Pesquisa produto por letra\n");
    printf("5. Lista produtos vencidos por data de validade\n");
    printf("6. Lista produtos abaixo do estoque mínimo\n");
    printf("7. Movimenta quantidade em estoque\n");
    printf("8. Altera produto pesquisado por nome\n");
    printf("9. Exclui produto pesquisado por nome\n");
    printf("0. Sair\n");
}
void limpar()
{
    system("pause");
    system("cls");
}
int tamanho_arquivo()
{
    FILE *p;
    int tamanho_struct = sizeof(produtos);
    long int posicao;
    p = fopen("C11.txt", "rb");
    fseek(p, 0, 2);
    posicao = ftell(p);
    fclose(p);
    return (posicao/tamanho_struct);
}
void entra_produto(produtos *produto)
{
    FILE *p;
    p = fopen("C11.txt","ab");
    printf("Insira o nome do produto: ");
    gets(produto->nome);
    setbuf(stdin,NULL);
    printf("Insira a quantidade atual do produto: ");
    scanf("%d", &produto->quant_atual);
    setbuf(stdin,NULL);
    printf("Insira a quantidade mínima do produto: ");
    scanf("%d", &produto->min_estoque);
    setbuf(stdin,NULL);
    printf("Insira a data de validade(mm/aa): ");
    gets(produto->validade);
    setbuf(stdin,NULL);
    fwrite(produto,sizeof(*produto),1,p);
    fclose(p);
    limpar();
}
void lista_produto(produtos *produto)
{
    FILE *p;
    int i;
    p = fopen("C11.txt","rb");
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto,sizeof(*produto),1,p);
        if (produto->nome[0] != '*')
            printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
    }
    if (tamanho_arquivo() == 0)
        printf("Nenhum registro encontrado\n");
    fclose(p);
    limpar();
}
void pesquisa_produto(produtos *produto)
{
    FILE *p;
    char nome[20];
    int i, q, n, x = 0;
    p = fopen("C11.txt", "rb");
    printf("Insira o nome a ser pesquisado: ");
    gets(nome);
    setbuf(stdin,NULL);
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        q = 0;
        for (n = 0; n < 20; n++)
        {
            if (nome[n] == '\0' && produto->nome[n] == '\0' && q == n)
            {
                printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
                x++;
                break;
            }
            if (nome[n] == produto->nome[n])
                q++;
        }
    }
    if (tamanho_arquivo() == 0 || x == 0)
        printf("Nenhum registro encontrado\n");
    fclose(p);
    limpar();
}
void pesquisa_letra(produtos *produto)
{
    FILE *p;
    char c;
    int i, x = 0;
    p = fopen("C11.txt", "rb");
    printf("Insira a letra a ser pesquisada: ");
    c = getchar();
    setbuf(stdin,NULL);
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        if (c == produto->nome[0])
        {
            printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
            x++;
        }
    }
    if (tamanho_arquivo() == 0 || x == 0)
    printf("Nenhum registro encontrado\n");
    fclose(p);
    limpar();
}
void pesquisa_data(produtos *produto)
{
    FILE *p;
    char data[6];
    int i, n, x = 0, Idata, Iproduto;
    p = fopen("C11.txt", "rb");
    printf("Insira a data atual(mm/aa): ");
    gets(data);
    Idata = data[3]*1000 + data[4]*100 + data[0]*10 + data[1];
    setbuf(stdin,NULL);
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        Iproduto = produto->validade[3]*1000 + produto->validade[4]*100 + produto->validade[0]*10 + produto->validade[1];
        if (Iproduto <= Idata && produto->nome[0] != '*')
        {
            printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
            x++;
        }
    }
    if (tamanho_arquivo() == 0 || x == 0)
        printf("Nenhum registro encontrado\n");
    fclose(p);
    limpar();
}
void lista_abaixo_min(produtos *produto)
{
    FILE *p;
    int i, x = 0;
    p = fopen("C11.txt", "rb");
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        if (produto->min_estoque > produto->quant_atual && produto->nome[0] != '*')
        {
            printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
            x++;
        }
    }
    if (tamanho_arquivo() == 0 || x == 0)
        printf("Nenhum registro encontrado\n");
    fclose(p);
    limpar();
}
void altera_estoque(produtos *produto)
{
    FILE *p;
    char nome[20];
    int i, q, n, x = 0;
    p = fopen("C11.txt", "rb+");
    printf("Insira o nome a ser pesquisado: ");
    gets(nome);
    setbuf(stdin,NULL);
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        q = 0;
        for (n = 0; n < 20; n++)
        {
            if (nome[n] == '\0' && produto->nome[n] == '\0' && q == n)
            {
                printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
                x++;
                break;
            }
            if (nome[n] == produto->nome[n])
                q++;
        }
        if (x != 0)
            break;
    }
    if (tamanho_arquivo() == 0 || x == 0)
    {
        printf("Nenhum registro encontrado\n");
        fclose(p);
        limpar();
        return;
    }
    printf("Insira a quantidade a ser adicionada(use número negativo para remover): ");
    scanf("%d", &x);
    produto->quant_atual += x;
    printf("Nova quantidade atual: %d\n", produto->quant_atual);
    fseek(p,sizeof(*produto)*i,0);
    fwrite(produto,sizeof(*produto),1,p);
    limpar();
    fclose(p);
}
void altera_produto(produtos *produto)
{
    FILE *p;
    char nome[20];
    int i, q, n, x = 0;
    p = fopen("C11.txt", "rb+");
    printf("Insira o nome a ser pesquisado: ");
    gets(nome);
    setbuf(stdin,NULL);
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        q = 0;
        for (n = 0; n < 20; n++)
        {
            if (nome[n] == '\0' && produto->nome[n] == '\0' && q == n)
            {
                printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
                x++;
                break;
            }
            if (nome[n] == produto->nome[n])
                q++;
        }
        if (x != 0)
            break;
    }
    if (tamanho_arquivo() == 0 || x == 0)
    {
        printf("Nenhum registro encontrado\n");
        fclose(p);
        limpar();
        return;
    }
    printf("Insira o nome do produto: ");
    gets(produto->nome);
    setbuf(stdin,NULL);
    printf("Insira a quantidade atual do produto: ");
    scanf("%d", &produto->quant_atual);
    setbuf(stdin,NULL);
    printf("Insira a quantidade mínima do produto: ");
    scanf("%d", &produto->min_estoque);
    setbuf(stdin,NULL);
    printf("Insira a data de validade(mm/aa): ");
    gets(produto->validade);
    setbuf(stdin,NULL);
    fseek(p,sizeof(*produto)*i,0);
    fwrite(produto,sizeof(*produto),1,p);
    fclose(p);
    limpar();
}
void exclui_produto(produtos *produto)
{
    FILE *p;
    char nome[20];
    char c;
    int i, q, n, x = 0;
    p = fopen("C11.txt", "rb+");
    printf("Insira o nome a ser pesquisado: ");
    gets(nome);
    setbuf(stdin,NULL);
    for (i = 0; i < tamanho_arquivo(); i++)
    {
        fread(produto, sizeof(*produto), 1, p);
        q = 0;
        for (n = 0; n < 20; n++)
        {
            if (nome[n] == '\0' && produto->nome[n] == '\0' && q == n)
            {
                printf("Produto: %-19s Quantidade atual: %-6d Quantidade mínima: %-6d Validade: %-6s\n",produto->nome,produto->quant_atual,produto->min_estoque,produto->validade);
                x++;
                break;
            }
            if (nome[n] == produto->nome[n])
                q++;
        }
        if (x != 0)
            break;
    }
    if (tamanho_arquivo() == 0 || x == 0)
    {
        printf("Nenhum registro encontrado\n");
        fclose(p);
        limpar();
        return;
    }
    printf("Deseja mesmo deletar esse produto(s/n)? ");
    c = getchar();
    setbuf(stdin,NULL);
    if (c == 's' || c == 'S')
    {
        fseek(p,sizeof(*produto)*i,0);
        produto->nome[0] = '*';
        fwrite(produto,sizeof(*produto),1,p);
        fclose(p);
    }
    limpar();
}
