#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
using namespace std;

class jugador//CLASE JUGADOR
{
public:

char str1[21];
//char str2[60];//Nombres de los jugadores

int juegosganados;
int juegosperdidos;
int juegosempatados;
void preguntarnombrej1()
{
     system("cls");
     cout << "Como te llamas jugador/a ?"<<endl;
     cin>>str1;
     system("cls");
     cout<<"Bienvenido  "<<str1<<endl;

}
//void preguntanombrej2()
//{
//    cout << "Como te llamas jugador/a?" << endl;
//    cin >> str2;
//}
void mostrarnombre()
{
     cout<<"jugador 1: "<<str1<<endl;
     cout<<" Partidas Ganadas: "<<juegosganados<<" Partidas Perdidas: "<<juegosperdidos<<endl;
//     cout<<"jugador 2: "<<endl;
//     cout<<str2<<" Partidas Ganadas: "<<juegosperdidos<<" Partidas Perdidas: "<<juegosganados<<endl;
}
};
class oponente// CLASE OPONENTE

{
public:
};

class tablero//: public jugador// CLASE TABLERO hereda de la clase jugador
{
public:
short cuadros[3][3];//Posiciones de la cuartilla
bool winner1,winner2;//Quien gano?
bool turno;
int contador;//Para verificar que sean nueve casillas
int randomnum;
int posx,posy;//Posiciones que seran preguntadas


bool checarvertical(int jugador)
{

    bool gano = 0;
    for(int x = 0;x < 3;x++)
    {
        for(int y = 0;y < 3;y++)
        {
            if(cuadros[y][x] == jugador)
             gano = true;
            else
            {

             gano = false;
             break;
            }
        }
        if(gano == true)
            break;
    }

    return gano;
}
bool checardiagonal(int jugador)
{
    bool gano = 0;
    for(int x = 0;x < 3;x++)
    {

            if(cuadros[x][x] == jugador)
             gano = true;
            else
            {
             gano = false;
             break;
            }
    }
    return gano;
}
bool checardiagincompleto(int jugador)//Analiza si hay un hueco diagonal
{
    int posx[2];
    int posy[2];
    bool diag;
    diag = false;
    for(int x = 0;x < 2;x++)//Se llenan los valores vacios
    {
            posx[x] = -1;
            posy[x] = -1;
    }
    for(int x = 0;x < 3;x++)
    {
        for(int y = 0;y < 3;y++)
        {
            if(!diag)
            {
                if(cuadros[x][y] == jugador)
                {
                    if((posx[0] == -1))
                    {
                        posx[0] = x;
                        posy[0] = y;
                    }
                    else
                    {
                        if(posx[1] != -1)
                        {
                            posx[0] = posx[1];
                            posy[0] = posy[1];
                        }
                        posx[1] = x;
                        posy[1] = y;
                    }
                }
                if(((cuadros[1][1]==0)&&((((posx[0]==0)&&(posy[0]==0))&&(((posx[1]==2)&&(posy[1]==2))))||((posx[0]==0)&&(posy[0]==2)&&((posx[1]==2)&&(posy[1]==0))))))
                {
                    diag = true;

                }
            }

        }

    }
    return diag;
}

void inicializar()//Inicializa los valores de las variables
{
    srand ( time(NULL) );
    randomnum = 0;
    for(int x = 0;x < 3;x++)
    {
                for(int y = 0;y < 3;y++)
                {
                    cuadros[x][y] = 0;
                }
        }
        winner1 = 0;
        winner2 = 0;

        contador = 0;
        posx = 0;
        posy = 0;
        turno = false;
}



int checarincompleto(int jugador)//Analiza si hay un hueco horizontalcontr
{
    int acumvacio = 0;
    int acumjug = 0;
    int pos[2];
    pos[0] = 0;
    pos[1] = 0;
    for(int vh = 0;vh < 2;vh++)
    {
        for(int x = 0;x < 3;x++)
        {
            if(!(((acumjug == 2) && (acumvacio == 1))))
            {
            acumjug = 0;
            acumvacio = 0;

            for(int y = 0;y < 3;y++)
            {
                if(vh == 0)
                {
                    if((cuadros[x][y] == 0))
                    {
                        acumvacio++;
                        pos[0] = x;
                        pos[1] = y;
                    }
                    else if((cuadros[x][y] == jugador))
                    {
                        acumjug++;
                    }
                }
                else
                {
                    if((cuadros[y][x] == 0))
                    {
                        acumvacio++;
                        pos[0] = x;
                        pos[1] = y;
                    }
                    else if((cuadros[x][y] == jugador))
                    {
                        acumjug++;
                    }
                }

            }
            }
            if(!(((acumjug == 2) && (acumvacio == 1))))
            {
                pos[0] = 0;
                pos[1] = 0;
            }
        }
    }
    return (pos[0]*3+pos[1]);
}


bool checarhorizontal(int jugador)
{
    bool gano = 0;
    for(int x = 0;x < 3;x++)
    {
        if(gano == 0)
        {
            for(int y = 0;y < 3;y++)
            {
                if(cuadros[x][y] == jugador)
                gano = true;
                else
                {
                gano = false;
                break;
                }
            }
        }
    }
    return gano;
}
bool checarvictoria(int jugador)
{
    if(checarhorizontal(jugador) || checarvertical(jugador) || checardiagonal(jugador))
        return true;
    else
        return false;
}
void dibujarcuadricula()
{
      //  const char cuadros[] = {' ','x','o','e'};
                cout << "   1   2   3    " << endl;

        for(int x = 0;x < 3;x++)
        {
                cout << x + 1 << " ";
                for(int y = 0;y < 3;y++)
                {
                    cout << " | ";
                    if(cuadros[x][y]==0)
                     {cout <<" ";}
                    else{
                            if(cuadros[x][y]==1)
                                cout <<"X";
                            else
                                cout <<"O";
                    }
                }
                cout << " | ";
                cout << endl;
                cout << "  -+---+---+---+--" << endl;
        }
        cout << "   |   |   |   | " << endl;
}
void jugadorelige(int valor)
{

        do
        {
            do
            {
                cout << "Introduce tu posicion horizontal" << endl;
                cin >>posx;
                posx--;
                if(!((posx >= 0) && (posx < 3)))
                    cout << "No te salgas de ahi solo numeros del 1--3!" << endl;
            }while(!((posx >= 0) && (posx < 3)));
            do
            {
                cout << "Introduce tu posicion vertical" << endl;
                cin >> posy;
                posy--;
                if(!((posy >= 0) && (posy < 3)))
                    cout << "No te salgas de ahi!" << endl;
            }while(!((posy >= 0) && (posy < 3)));
            if((cuadros[posx][posy]) != 0)
                    cout << "Ya esta usado ese espacio >_>, no seas tramposo elige otro" << endl;
        }while(cuadros[posx][posy] != 0);

        cuadros[posx][posy] = valor;
}
void computadorajuega()
{
    if((checardiagincompleto(1))||(checardiagincompleto(2)))
    {
       randomnum = 4;

    }
    else if((checarincompleto(1)>0)||(checarincompleto(2)>0))
    {
       randomnum = checarincompleto(1);
    }

    else{

      do
        {
                randomnum = rand()%9;

            randomnum++;
            randomnum%=9;
        }
        while(cuadros[randomnum/3][randomnum%3] != 0);
    }
    cuadros[randomnum/3][randomnum%3] = 2;
}
};





int main()
{

    tablero t;
     jugador j;
        j.juegosempatados=0;
        j.juegosganados=0;
        j.juegosperdidos=0;


        int ctrl1,ctrl2;   /*nombre del juego*/


    char  Instruct;


             cout<<"\n\n\n\n\n";

         cout<<"\n**     **  ********  *******";
         cout<<"\n**     **  ********  ********";
         cout<<"\n**     **  **    **  **    **";
         cout<<"\n**  *  **  ********  *******";
         cout<<"\n** *** **  ********  *******";
         cout<<"\n***   ***  **    **  **    **";
         cout<<"\n**     **  **    **  **    **";
         cout<<"\n\n\n";
         for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 20000; ctrl2++)
           {
           }
           }

         cout<<"\n\t\t********  ********";
         cout<<"\n\t\t********  ********";
         cout<<"\n\t\t**    **  **";
         cout<<"\n\t\t**    **  *****";
         cout<<"\n\t\t**    **  *****";
         cout<<"\n\t\t********  **";
         cout<<"\n\t\t********  **";
         cout<<"\n\n\n";
for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 20000; ctrl2++)
           {
           }
           }
         cout<<"\n\t\t\t********  **    **  ********";
         cout<<"\n\t\t\t********  **    **  ********";
         cout<<"\n\t\t\t   **     ********  **";
         cout<<"\n\t\t\t   **     ********  *****";
         cout<<"\n\t\t\t   **     **    **  **";
         cout<<"\n\t\t\t   **     **    **  ********";
         cout<<"\n\t\t\t   **     **    **  ********";
         cout<<"\n\n\n";
for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 20000; ctrl2++)
           {
           }
           }
         cout<<"\n\t\t\t       **        ********  **    **  *******    *******";
         cout<<"\n\t\t\t       **        ********  ***   **  ********  ********";
         cout<<"\n\t\t\t       **        **    **  ****  **  **    **   **";
         cout<<"\n\t\t\t       **        ********  ** ** **  **    **    **";
         cout<<"\n\t\t\t       **        ********  **  ****  **    **      **";
         cout<<"\n\t\t\t       ********  **    **  **   ***  ********  ********";
         cout<<"\n\t\t\t       ********  **    **  **    **  *******   *******";
for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 20000; ctrl2++)
           {
           }
           }
     cout<<"\n\n\n\n\n\t\t    Welcome to the game WAR OF THE LANDS.\n\n\t\t";
     cout<<"\nHello , I need to tell you the story of War of the Lands. ";
     cout<<"\nDo you want to read the instructions or simply proceede with the game ? \n(R)ead or (P)roceede"<<endl;
      cin>>Instruct;
     if (Instruct=='R' ||Instruct=='r')
     {




     cout<<"\n\n     A disputed area of 900 square meters lies between two neighboring villages. ";
     cout<<"\n     The dispute between the neighboring villages has been running for  ";
     cout<<"\n     generations. The government has finally taken a decision to resolve  ";
     cout<<"\n     the dispute and grant the possession of this land to one of the ";
     cout<<"\n     villages using a fair method. ";
     cout<<"\n\n\n     The government has divided the disputed land into 9 equal square plots each";
     cout<<"\n     of 300 square meters as shown in the following figure:"<<endl;
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 20000; ctrl2++)
           {
           }
           }
     t.dibujarcuadricula();
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 20000; ctrl2++)
           {
           }
           }
     cout<<"\n\n     The following method will be used to grant possession of the land to \n     one of the villages: ";
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 80000; ctrl2++)
           {
           }
           }
     cout<<"\n\n     The government has decided that the entire land will be given to the \n     village that makes three successful plantations.";
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 80000; ctrl2++)
           {
           }
           }
     cout<<"\n\n     At one point of time, only one village will plant vegetation on a \n     square plot. Each village will be given a fair chance to grow \n     vegetation in a square block, turn-by-turn.";
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 80000; ctrl2++)
           {
           }
           }
     cout<<"\n\n     The first village that will plant vegetation on three square plots\n     from one corner to the opposite corner (vertically, horizontally,\n     or diagonally) will be given possession. For example,\n     on plots (1,1), (2,2) and (3,3) or (2,1), (2,2), and (2, 3) and so on";
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 80000; ctrl2++)
           {
           }
           }
     cout<<"\n\n     Each village can plant in a way to block the other village from planting\n     vegetation in three consecutive plots of land.";
     for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 80000; ctrl2++)
           {
           }
           }
     cout<<"\n\n     In case all the plots have been planted and neither village has planted\n     threeconsecutive plots of land, the government holds\n     possession of the entire land. Both villages will be then\n     given another chance to restart the plantation all over again."<<endl;
          for(ctrl1 = 0; ctrl1 < 2000; ctrl1++)
         {
          for(ctrl2 = 0; ctrl2 < 80000; ctrl2++)
           {
           }
           }
           }


char compu;//Decide si es contra la compu o un jugador

 while(1)
    {
    int resp;
             cout<<"*****************"<<endl;
             cout<<"*MENU DEL JUEGO*"<<endl;
             cout<<"*****************"<<endl;
             cout<<"*    1 Jugar Gato!"<<endl;
             cout<<"*****************"<<endl;
             cout<<"*    2 Ver Score..."<<endl;
             cout<<"*****************"<<endl;
             cout<<"*    0 Salir "<<endl;
             cout<<"******************"<<endl;
    cin>>resp;
if(resp==1)
{
char repeticion;//Si se quiere jugar de nuevo, esta variable sera s, si no, n;
system("cls");
    repeticion = 'r';
    do
    {
        t.inicializar();
        if(repeticion == 'r'||repeticion=='R')
        {

            cout<<"MENU DE JUEGO\n"<<endl;
            cout<<"Usuario 1 es X, Usuario2 es O"<<endl;
            cout<<"LOS TURNOS SE DECIDIRAN ALEATORIAMENTE\n"<<endl;
            cout << "¿Quieres jugar contra la compu o contra alguien?" << endl;
            cout << "Cualquier tecla para jugar con un  Jugador" << endl;
            cout << "C) Compu" << endl;
            cin >>compu;
            j.preguntarnombrej1();
           ofstream ofile("player.txt",ios::app);
           ofile.write((char*)&j,sizeof(j));
            ofile.close();




            if((compu == 'c') ||(compu == 'C'))
            {

    //            j.str2 = "la computadora sin sentimientos";
            }
            else
            {
//             j.preguntanombrej2();
            }
        }
        t.turno = rand()%2;
        do
        {

            if(!t.turno)//Turno del jugador 1
            {
                t.dibujarcuadricula();
                cout << "Es el turno de "<<j.str1 <<endl;
                t.jugadorelige(1);
                t.turno =t.turno^1;
                t.contador++;

            }
            t.winner1 =t.checarvictoria(1);
            t.winner2 =t.checarvictoria(2);
            if((t.contador < 9)&&t.turno && ((t.winner1 == false)||(t.winner2 == false)))//Turno del jugador 2
            {

                    t.dibujarcuadricula();
                    cout << "Es el turno de El jugador 2"<<endl;
                    t.turno=t.turno^1;
                    if(((compu == 'c') ||(compu == 'C')))
                    {
                        t.computadorajuega();

                    }
                    else
                    t.jugadorelige(2);
                    t.contador++;
            }
            t.winner1 =t.checarvictoria(1);
            t.winner2 =t.checarvictoria(2);
        }
        while((t.winner1==false)&&(t.winner2==false)&&(t.contador<9));
        t.dibujarcuadricula();
        if(t.winner1)
        {
            cout<<"Wiii wiiwiwiwiiwiwiwi, gano "<<j.str1<<" lol"<<endl;
j.juegosganados=j.juegosganados+1;

        }
        else if(t.winner2)
        {
            cout << "Wiii wiiwiwiwiiwiwiwi, gano el jugador 2"<<endl;
j.juegosperdidos=j.juegosperdidos+1;

        }
        else
        cout << "Empataron XD";
j.juegosempatados=j.juegosempatados+1;

        cout << endl;
        cout << "Deseas volver a jugar?:"<< endl;
        cout << "Cualquier tecla Jugar otra  "<< endl;
        cout << " R ) JUGAR CON UN OPONENTE DISTINTO"<< endl;
        cout << " N ) IR AL MENU DEL JUEGO";
        cin >> repeticion;
    }
    while(repeticion != 'n');
    }
    if(resp==2)
    {
               ifstream ifile("player.txt");
               ifile.read((char*)&j,sizeof(j));
               while(ifile)
                {
                   j.mostrarnombre();
                    ifile.read((char*)&j,sizeof(j));
                }
                ifile.close();

    }
    if(resp==0)
    {
        exit(0);
    }
}
    return 0;
}

