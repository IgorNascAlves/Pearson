#include<string>
#include<cstring>
#include<vector>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<math.h>
using namespace std;
void criaHTML(char* str){

    FILE * Stream;
    FILE * Stream2;
    char buffer [1000];

    Stream = fopen ("inicio","r");
    Stream2 = fopen ("index.html","w+");
    while ( ! feof (Stream) )
    {
        if ( fgets (buffer , 100 , Stream) == NULL ) break;{
            fputs(buffer , Stream2);
        }
    }
    fclose (Stream);

    fputs (str,Stream2);

    Stream = fopen ("fim","r");
    while ( fgets (buffer , 100 , Stream) != NULL ){
        fputs(buffer , Stream2);
    }
    fclose (Stream);
    fclose (Stream2);
}
void entradaHTML(vector<double> vetorx,vector<double> vetory, double a, char b[]){
    int tamanho = 1000* vetorx.size();
    char str[tamanho];
    char temp[tamanho];
    int i;
    for(i=0;i<tamanho;i++){
        str[i] = '\0';
        temp[i] = '\0';
    }

    sprintf(temp,"var a = %f; var b =\"%s\";var vetor = [",a,b);
    strcat(str,temp);
    for(unsigned int i=0;i<vetorx.size();i++){
        sprintf(temp, "             [%f , %f ], \n", vetorx[i],vetory[i]);
        strcat(str,temp);
    }
    sprintf(temp,"];");
    strcat(str,temp);
    criaHTML(str);
}
void lerArquivo(vector<double> &vx,vector<double> &vy,int x,int y){
    ifstream f;
    f.open("PRODUCAO_LEITE(editado).csv", fstream::in);
    double s;
    vector<double> v;
    string teste;
    int i=0;
    for(int i=0;i<5;i++){
        f>>teste;
        //cout<<teste<<endl;
    }
    while(f>>s){
        i++;
        v.push_back(s);
    }
    //cout<<i/5<<endl;
    int cont = 4;
    for(unsigned int i=0;i<v.size();i++){
        //cout<<v[i]<<" ";
        if(cont == 0){
            cont = 5;
            //cout<<endl;
        }
        cont--;
    }
    //cout<<endl;
    f.close();

    for(unsigned i=x;i<v.size();i=i+5){
        vx.push_back(v[i]);
        //cout<<v[i]<<endl;
    }
    for(unsigned i=y;i<v.size();i=i+5){
        vy.push_back(v[i]);
    }
}
class Arquivo{
public:
    vector <double> x;
    vector <double> y;

    Arquivo(vector<double> a, vector <double> b){
        x = a;
        y = b;
    };
    double mediaY(){
        double a = 0.0;
        for(vector<double>::iterator it = y.begin(); it != y.end(); ++it)
            a = a + *it;
        double mY = a / (y.size() * 1.0);
        return mY;
    }
    double mediaX(){
        double a = 0.0;
        for(vector<double>::iterator it = x.begin() ; it != x.end(); ++it)
            a = a + *it;
        double mX = a / (x.size() * 1.0);
        return mX;
    }
    double cima(){
        double mX = mediaX();
        double mY = mediaY();
        double a = 0.0;
        vector<double>::iterator itX = x.begin();
        vector<double>::iterator itY = y.begin();
        while(itX != x.end()){
            a = a + ((*itX - mX)*(*itY - mY));
            itX++;
            itY++;
        }
        return a;
    }
    double varX(){
        double mX = mediaX();
        double a = 0.0;
        for(vector<double>::iterator it = x.begin(); it != x.end(); ++it)
            a = a + pow(*it - mX,2);
        return sqrt(a);
    }
    double varY(){
        double mY = mediaY();
        double a = 0.0;
        for(vector<double>::iterator it = y.begin(); it != y.end(); ++it)
            a = a + pow(*it - mY,2);
        return sqrt(a);
    }
    double correl(){
        double r;
        r = cima() / (varX() * varY());
        return r;
    }
    char* salvaString(double x){
        if( x < 0)
            x = x * (-1);
        if( x < .3)
            return "correlação desprezível";
        else if(x < .5)
            return "correlação fraca";
        else if(x < .7)
            return "correlação moderada";
        else if(x < .9)
            return "correlação forte";
        else
            return "correlação muito forte";
    }
};
int main(){       
    int x,y;
    int opc=1;
    //system("firefox \"index.html\"");
    while(opc){
        cout<<"coluna x: ";
        cin>>x;
        cout<<"coluna y: ";
        cin>>y;
        system("clear");

        vector<double> vetorx/* = {17,18,452,20,21,22,23,24}*/;
        vector<double> vetory/* = {1,2,3,4,5,6,7,8}*/;

        lerArquivo(vetorx,vetory,x,y);
        Arquivo teste(vetorx,vetory);
        entradaHTML(vetorx,vetory,teste.correl(),teste.salvaString(teste.correl()));

//        cout<<"quer continuar ? (0/1)"<<endl;
//        cin>>opc;
    }
    //system("start index.html"); //forWindows
    return 0;
}
