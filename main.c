#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mesinkata1.h"

typedef char * string;

typedef struct {
    string lhs;
    string rhs[2];
} production;


    production prod;

int findChar(Kata a, char charToFind, int start)
{
    int i=start;
    boolean found = false;
    while (!found && i<=a.Length)
    {
        if (a.TabKata[i]==charToFind)
            found = true;
        else
            i++;
    }
    if (found)
        return i;
    else
        return -1;
}
/*
void break_grammar(string a)
{
    int i;
}

string pick_lhs(string a)
{
    string retStr;
    int i;
    int iSep = findChar(a,'-');
    for (i=0;i<iSep;i++)
        retStr[i]=a[i];
    return retStr;
}

string pick_rhs1(string a)
{
    string retStr;
    int i;
    int iSep = findChar(a,'-');
    int iSlash = findChar(a,'|');
    for (i=iSep+1;i<iSlash;i++)
        retStr[i]=a[i];
    return retStr;
}

string pick_rhs2(string a)
{
    string retStr;
    int i;
    int iSlash = findChar(a,'|');
    if (iSlash == -1)
    {
        printf("ERROR: Can't pick rhs2\n");
        return "";
    }
    else
    {
        for (i=iSlash+1;i<=strlen(a);i++)
            retStr[i]=a[i];
        return retStr;
    }
}


void ReadGrammar(char *filename)
{
    FILE *f;
    char ss[256];
    char sc;
    int i;

    int totGrammar = 0;

    f = fopen(filename,"r");
    //cek EOF
    while (fscanf(f,"%c",&sc)!=EOF)
    {
        if (sc=='\n')
            totGrammar++;
    }
    fclose(f);
    printf("Total Grammar = %d\n",totGrammar);

    //membaca grammar
    f = fopen(filename,"r");
    for (i=0;i<totGrammar;i++)
    {
        fscanf(f,"%s",ss);
        prod.lhs = pick_lhs(ss);
        prod.rhs[0] = pick_rhs1(ss);
        printf("%s",prod.rhs[0]);
        int iSlash = findChar(ss,'|');
        if (iSlash == -1)
        {
            //is a terminal
        }
        else
        {
            prod.rhs[1] = pick_rhs2(ss);
        }
    }
    fclose(f);
}*/
int N;
typedef struct {
    Kata kata[5000];
    int neff;
} ARRAYKATA;

void SplitKata(Kata K, ARRAYKATA *arr)
{
    int i;
    arr->neff = 0;
    Kata Kcp;
    Kcp.Length = 0;

    for (i=1;i<=K.Length;i++)
    {
        if (K.TabKata[i] == '(' || K.TabKata[i] == ')' ||
            K.TabKata[i] == '>' || K.TabKata[i] == '<' ||
            K.TabKata[i] == '=' || K.TabKata[i] == '+' ||
            K.TabKata[i] == '-' || K.TabKata[i] == '*' ||
            K.TabKata[i] == '{' || K.TabKata[i] == '}')
        {
            if (Kcp.Length>0)
            {
                CopyKata(Kcp, &arr->kata[arr->neff++]);
                //printKata(arr->kata[arr->neff - 1]);
            }

            Kcp.TabKata[1] = K.TabKata[i];
            Kcp.Length = 1;
            if (i+1 <= K.Length)
            {
                if (K.TabKata[i] == '>')
                {
                    if (K.TabKata[i+1] == '=')
                    {
                        i++;
                        Kcp.TabKata[2] = K.TabKata[i];
                        Kcp.Length++;
                    }
                }
                else if (K.TabKata[i] == '<')
                {
                    if (K.TabKata[i+1] == '=' || K.TabKata[i+1] == '>')
                    {
                        i++;
                        Kcp.TabKata[2] = K.TabKata[i];
                        Kcp.Length++;
                    }
                }
            }
            CopyKata(Kcp, &arr->kata[arr->neff++]);
            //printKata(arr->kata[arr->neff - 1]);

            Kcp.Length = 0;
        }
        else if (K.TabKata[i] != '\t')
        {
            Kcp.Length++;
            Kcp.TabKata[Kcp.Length] = K.TabKata[i];
        }
    }
    if (Kcp.Length > 0)
    {
        CopyKata(Kcp, &arr->kata[arr->neff++]);
        //printKata(arr->kata[arr->neff - 1]);
    }
}

void ReadPascal(char *filename, ARRAYKATA *arrayKata)
{
    arrayKata->neff=0;

    ARRAYKATA tempArr;
    int i;
    boolean bisaCopy = true;

    // f = fopen(filename, "r");
    STARTKATA(filename);
    while (!EndKata)
    {
        SplitKata(CKata,&tempArr);
        for (i=0;i<tempArr.neff;i++)
        {
            if (tempArr.kata[i].TabKata[1] == '{')
                bisaCopy = false;
            else if (tempArr.kata[i].TabKata[1] == '}' && !bisaCopy)
            {
                bisaCopy = true;
                i++;
            }

            if (bisaCopy && i<tempArr.neff)
            {
                arrayKata->neff++;
                CopyKata(tempArr.kata[i],&arrayKata->kata[arrayKata->neff]);
            }
        }
        ADVKATA();
    }

    for (i=1;i<=arrayKata->neff;i++)
    {
        printKata(arrayKata->kata[i]);
    }
}

int main()
{
    printf("WELCOME to nacoPascal Syntax Checker!\n");
    ARRAYKATA arrayKata;
    ReadPascal("teks1.txt",&arrayKata);
    return 0;
}
