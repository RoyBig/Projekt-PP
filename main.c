#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dane
{
    char nazwa[50],mail[30],telefon[15];
    struct dane *next;
};
struct zlecenia
{
    char firma[50],produkt[50],opis[100],data[15],czas[20],cena[20],status[20];
    struct zlecenia *nast;
};
struct dane *wypelnij_z_pliku(char *sth,int n)
{
    struct dane *first=NULL;
    FILE *plik=fopen(sth,"r");
    for(int i=0;i<n;i++)
    //while(!feof(plik))
    {
        struct dane *nowy=malloc(sizeof(struct dane));
        fgets(nowy->nazwa,50,plik);
        fgets(nowy->mail,30,plik);
        fgets(nowy->telefon,15,plik);
        //fscanf(plik,"%s %s %s",nowy->nazwa,nowy->mail,nowy->telefon);
        nowy->next=first;
        first=nowy;
    }
    fclose(plik);
    return first;
}
struct zlecenia *from_file(char *sth, int n)
{
    struct zlecenia *pierwszy=NULL;
    FILE *plik=fopen(sth,"r");
    for(int i=0;i<n;i++)
    {
        struct zlecenia *news=malloc(sizeof(struct zlecenia));
        fgets(news->firma,50,plik);
        fgets(news->produkt,50,plik);
        fgets(news->opis,50,plik);
        fgets(news->data,50,plik);
        fgets(news->czas,50,plik);
        fgets(news->cena,15,plik);
        fgets(news->status,20,plik);
        news->nast=pierwszy;
        pierwszy=news;

    }
    fclose(plik);
    return pierwszy;
}
void printlist(struct dane *first)
{
    int i=1;
    while(first!=NULL)
    {
        printf("Nazwa firmy %d: %sMail: %sTelefon: %s\n",i,first->nazwa,first->mail,first->telefon);
        i++;
        first=first->next;
    }
    //printf("\n");
}
void printzlecenia(struct zlecenia *pierwszy)
{
    while(pierwszy!=NULL)
    {
        printf("\nFirma %sProdukt: %sOpis: %sData: %sCzas: %sCena: %sStatus: %s\n",pierwszy->firma,pierwszy->produkt,pierwszy->opis,pierwszy->data,pierwszy->czas,pierwszy->cena,pierwszy->status);
        pierwszy=pierwszy->nast;
    }
    printf("\n");
}
struct dane *addCompany(struct dane *first, char *smw, char *nazwa1, char *mail1, char *telefon1)
{
    FILE *plik=fopen(smw,"a");
    struct dane *nowy = malloc(sizeof(struct dane));
    strcpy(nowy->nazwa,nazwa1);
    strcpy(nowy->mail,mail1);
    strcpy(nowy->telefon,telefon1);
    nowy->next=NULL;
    struct dane *p=first;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    fputs(nowy->nazwa,plik);
    fputc('\n',plik);
    fputs(nowy->mail,plik);
    fputc('\n',plik);
    fputs(nowy->telefon,plik);
    fputc('\n',plik);
    fclose(plik);
    p->next=nowy;
    return first;
}
struct zlecenia *addmission(struct zlecenia *pierwszy,char *wh,char *firma2,char *produkt2,char *opis2,char *data2,char *czas2,char *cena2,char *status2)
{
    FILE *plik=fopen(wh,"a");
    struct zlecenia *news = malloc(sizeof(struct zlecenia));
    strcpy(news->firma,firma2);
    strcpy(news->produkt,produkt2);
    strcpy(news->opis,opis2);
    strcpy(news->data,data2);
    strcpy(news->czas,czas2);
    strcpy(news->cena,cena2);
    strcpy(news->status,status2);
    news->nast=NULL;
    struct zlecenia *p=pierwszy;
    while(p->nast!=NULL)
    {
        p=p->nast;
    }
    fputs(news->firma,plik);
    fputc('\n',plik);
    fputs(news->produkt,plik);
    fputc('\n',plik);
    fputs(news->opis,plik);
    fputc('\n',plik);
    fputs(news->data,plik);
    fputc('\n',plik);
    fputs(news->czas,plik);
    fputc('\n',plik);
    fputs(news->cena,plik);
    fputc('\n',plik);
    fputs(news->status,plik);
    fputc('\n',plik);
    fclose(plik);
    p->nast=news;
    return pierwszy;
}
void print_company(struct zlecenia *pierwszy,char *klucz)
{
    while(pierwszy!=NULL)
    {
        if(strcmp(pierwszy->firma,klucz)==0)
        {
            printf("Firma %sProdukt: %sOpis: %sData: %sCzas: %sCena: %sStatus: %s\n",pierwszy->firma,pierwszy->produkt,pierwszy->opis,pierwszy->data,pierwszy->czas,pierwszy->cena,pierwszy->status);
            pierwszy=pierwszy->nast;
        }
        else pierwszy=pierwszy->nast;
    }
}
void przerob(char *slowo)
{
    for(int i=0;i<100;i++)
    {
        if(slowo[i]=='\0')
        {
            slowo[i]='\n';
            slowo[i+1]='\0';
            break;
        }
    }
}
struct zlecenia *delete_zlecenia(struct zlecenia *pierwszy,char *firma4)
{
    if(strcmp(pierwszy->firma,firma4)==0)
    {
    struct zlecenia *tmp=pierwszy;
    pierwszy=pierwszy->nast;
    free(tmp);
    return pierwszy;
    }
    struct zlecenia *p=pierwszy;
    struct zlecenia *poprzedni;
    while(pierwszy->nast!=NULL)
    {
        if(strcmp(p->firma,firma4)==0)
        {
            poprzedni->nast=p->nast;
            free(p);
            //break;
        }
        poprzedni=p;
        p=p->nast;
    }
    return pierwszy;
}

struct dane *delete_company(struct dane *first,char *firma4)
{
    if(strcmp(first->nazwa,firma4)==0)
    {
    struct dane *tmp=first;
    first=first->next;
    free(tmp);
    return first;
    }
    struct dane *p=first;
    struct dane *poprzedni;
    while(p->next!=NULL)
    {
        if(strcmp(p->nazwa,firma4)==0)
        {
            poprzedni->next=p->next;
            free(p);
            break;
        }
        poprzedni=p;
        p=p->next;
    }
    return first;
}
void to_file_dane(struct dane *first,char *kkk)
{
    FILE *plik=fopen(kkk,"w");
    while(first!=NULL)
    {
        fputs(first->nazwa,plik);
        fputs(first->mail,plik);
        fputs(first->telefon,plik);
        first=first->next;
    }
    fclose(plik);
}
void to_file_zlecenia(struct zlecenia *pierwszy,char *xxx)
{
    FILE *plik=fopen(xxx,"w");
    while(pierwszy!=NULL)
    {
        fputs(pierwszy->firma,plik);
        fputs(pierwszy->produkt,plik);
        fputs(pierwszy->opis,plik);
        fputs(pierwszy->data,plik);
        fputs(pierwszy->czas,plik);
        fputs(pierwszy->cena,plik);
        fputs(pierwszy->status,plik);
        pierwszy=pierwszy->nast;
    }
    fclose(plik);
}
struct zlecenia *change_status(struct zlecenia *pierwszy,char *firma5,char *produkt5, char *status5)
{
    struct zlecenia *p=pierwszy;
    while(p!=NULL)
    {
        if((strcmp(p->firma,firma5)==0)&&(strcmp(p->produkt,produkt5)==0))
        {
            strcpy(p->status,status5);
            return pierwszy;
        }
        p=p->nast;
    }
    return pierwszy;
}
struct zlecenia *change_opis(struct zlecenia *pierwszy,char *firma6,char *produkt6,char *opis6)
{
    struct zlecenia *p=pierwszy;
    while(p!=NULL)
    {
        if((strcmp(p->firma,firma6)==0)&&(strcmp(p->produkt,produkt6)==0))
        {
            strcpy(p->opis,opis6);
            return pierwszy;
        }
        p=p->nast;
    }
    return pierwszy;
}
struct dane *sortowanie_alfabetyczne(struct dane *first)
{
    struct dane *nowa=NULL;
    while (first != NULL)
    {
        struct dane *p = first;
        struct dane *pop = NULL;
        struct dane *min = first;
        struct dane *popmin = NULL;
        while (p!=NULL)
        {
            if (strcmp(p->nazwa,min->nazwa)<0)
            {
                popmin = pop;
                min = p;
            }
            pop = p;
            p = p->next;
        }
        if (popmin == NULL)
        {
            first = first->next;
        }
        else
        {
            popmin->next = popmin->next->next;
        }
        min->next = nowa;
        nowa = min;
    }
    return nowa;
}
struct zlecenia *sortowanie_cenowo(struct zlecenia *pierwszy)
{
    struct zlecenia *nowa=NULL;
    while (pierwszy != NULL)
    {
        struct zlecenia *p = pierwszy;
        struct zlecenia *pop = NULL;
        struct zlecenia *min = pierwszy;
        struct zlecenia *popmin = NULL;
        while (p!=NULL)
        {
            if (strcmp(p->cena,min->cena)<0)
            {
                popmin = pop;
                min = p;
            }
            pop = p;
            p = p->nast;
        }
        if (popmin == NULL)
        {
            pierwszy = pierwszy->nast;
        }
        else
        {
            popmin->nast = popmin->nast->nast;
        }
        min->nast = nowa;
        nowa = min;
    }
    return nowa;
}
int main()
{
    int n=10,g=16;
    int v=-1;
    while(v!=0)
    {
    struct dane *first=wypelnij_z_pliku("firmy.txt",n);
    struct zlecenia *pierwszy=from_file("zlecenia.txt",g);
    printf("AGENCJA REKLAMOWA\n");
    printf("Wybierz co chcesz zrobic wybierajac odpowiednia opcje:\n");
    printf("1.Wypisywanie danych klientow\n");
    printf("2.Wypisywanie wszystkich zlecen\n");
    printf("3.Nadanie zlecenia\n");
    printf("4.Wyswietlenia zlecen danego klienta\n");
    printf("5.Usuwanie danych klienta\n");
    printf("6.Zmiana statusu zamowienia:\n");
    printf("7.Edycja opisu produktu:\n");
    printf("8.Sortowanie danych klientow alfabetycznie\n");
    printf("9.Sortowanie zlecen od najtanszych do najdrozszych\n");
    printf("0.Zakoncz dzialanie programu\n");
    printf("> ");
    scanf("%d",&v);
    if(v==1)
    {
        printlist(first);
        v=-1;
    }
    if(v==2)
    {
        printzlecenia(pierwszy);
        v=-1;
    }
    if(v==3)
    {
        int x=-1;
        printf("Czy twoja firma skladala juz wczesniej zamowienie?\nJesli tak wpisz 1, jesli nie wpisz 0\n");
        scanf("%d",&x);
        if(x==0)
        {
            char firma1[50],mail1[20],telefon1[20];
            printf("Podaj nazwe firmy: ");
            gets(firma1);
            gets(firma1);
            printf("Podaj maila: ");
            gets(mail1);
            printf("Podaj nr telefonu: ");
            gets(telefon1);
            first=addCompany(first,"firmy.txt",firma1,mail1,telefon1);
            v=-1;
            n++;
            x=1;
        }
        if(x==1)
        {
            char firma2[50],produkt2[50],opis2[100],data2[15],czas2[20],cena2[20],status2[20];
            printf("Podaj nazwe firmy: ");
            gets(firma2);
            gets(firma2);
            printf("Podaj nazwe reklamowanego produktu: ");
            gets(produkt2);
            printf("Opis filmu: ");
            gets(opis2);
            printf("Data realizacji: ");
            gets(data2);
            printf("Czas trwania nagrania: ");
            gets(czas2);
            printf("Cena (w zl): ");
            gets(cena2);
            printf("Status zamowienia:(0-zlecone 1-przyjete 2-wykonane 3-anulowane):");
            gets(status2);
            pierwszy=addmission(pierwszy,"zlecenia.txt",firma2,produkt2,opis2,data2,czas2,cena2,status2);
            g++;
            v=-1;
        }
    }
    if(v==4)
    {
        char firma3[50];
        printf("Zlecenia, ktorej firmy chcesz wyswietlic? > ");
        gets(firma3);
        gets(firma3);
        przerob(firma3);
        print_company(pierwszy,firma3);
        v=-1;
    }
    if(v==5)
    {
        char firma4[50],produkt4[50];
        printf("Dane, ktorej firmy chcesz usunac?: ");
        gets(firma4);
        gets(firma4);
        przerob(firma4);
        pierwszy=delete_zlecenia(pierwszy,firma4);
        to_file_zlecenia(pierwszy,"zlecenia.txt");
        first=delete_company(first,firma4);
        to_file_dane(first,"firmy.txt");
        n--;
        g--;
        v=-1;
    }
    if(v==6)
    {
        char firma5[50],produkt5[50],status5[2];
        printf("Status, ktorego zamowienia chcesz zmienic:\n");
        printf("Nazwa firmy: ");
        gets(firma5);
        gets(firma5);
        przerob(firma5);
        printf("Nazwa produktu: ");
        gets(produkt5);
        przerob(produkt5);
        printf("Zmiana statusu na(0-zlecone 1-przyjete 2-wykonane 3-anulowane): ");
        gets(status5);
        przerob(status5);
        pierwszy=change_status(pierwszy,firma5,produkt5,status5);
        to_file_zlecenia(pierwszy,"zlecenia.txt");
        v=-1;
    }
    if(v==7)
    {
        char firma6[50],produkt6[50],opis6[100];
        printf("Opis, ktorego zamowienia chcesz zmienic:\n");
        printf("Nazwa firmy: ");
        gets(firma6);
        gets(firma6);
        przerob(firma6);
        printf("Nazwa produktu: ");
        gets(produkt6);
        przerob(produkt6);
        printf("Nowy opis: ");
        gets(opis6);
        przerob(opis6);
        pierwszy=change_opis(pierwszy,firma6,produkt6,opis6);
        to_file_zlecenia(pierwszy,"zlecenia.txt");
        v=-1;
    }
    if(v==8)
    {
        first=sortowanie_alfabetyczne(first);
        to_file_dane(first,"firmy.txt");
        v=-1;
    }
    if(v==9)
    {
        pierwszy=sortowanie_cenowo(pierwszy);
        to_file_zlecenia(pierwszy,"zlecenia.txt");
        v=-1;
    }
    if(v==0)
    {
        printf("Dziekujemy, program zakonczyl wlasnie dzialanie!");
        return 0;
    }
    }
    return 0;
}

