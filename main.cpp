#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class NFA
{
    int q;
    int f;
    int *F;
    int v;
    char *V;
    int g;
    struct tranz
    {
        int a,b;
        char c;
    } *G;
    int sc;
    int exista;
public:
    NFA(char *fisier)
    {
        int i;
        ifstream in(fisier);
        in>>q>>f;
        F=new int[f];
        for (i=0;i<f;i++)
            in>>F[i];
        in>>v;
        V=new char[v];
        for (i=0;i<v;i++)
            in>>V[i];
        in>>g;
        G=new tranz[g];
        for (i=0;i<g;i++)
        {
            in>>G[i].a>>G[i].c>>G[i].b;
        }
        sc=0;
        exista=0;
    }
    void show();
    bool verificare(char *cuvant, int sc, int pozitia_in_cuvant);
};

void NFA::show()
{
    int i;
    for (i=0;i<g;i++)
        cout<<G[i].a<<" "<<G[i].c<<" "<<G[i].b<<"\n";
}
bool NFA::verificare(char *cuvant, int sc, int pozitia_in_cuvant)
{
    int i;
    if ((pozitia_in_cuvant==strlen(cuvant))&&(sc<=q))
    {
        for (i=0;i<f;i++)
            if (sc==F[i])
            {
                exista=1;
                return true;
            }
    }
    else
    {
        for (i=0;i<g;i++)
        {
            if (exista==1)
                return true;
            if ((G[i].a==sc)&&(G[i].c==cuvant[pozitia_in_cuvant]))
            {
                verificare(cuvant,G[i].b,pozitia_in_cuvant+1);
            }else if(G[i].a==sc && G[i].c=='^')
                    verificare(cuvant, G[i].b, pozitia_in_cuvant);
        }
        return false;
    }
}

int main()
{
    NFA automat1("afn.in");
    if (automat1.verificare("aabb",0,0)==true)
        cout<<"Da"<<endl;
    else
        cout<<"Nu"<<endl;
        automat1.show();
    return 0;
}
