
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
using namespace std;
// codigo ASCII
#define IZQUIERDA 75
#define DERECHA 77
void aniadir();
void gotoxy(int x, int y);
void vidas(int vi);
void barra_salud(int n);
void avion_explota();
void jugar();

char avion_l1[]= {' ',' ',' ', '*',' ',' ',' ',0};
char avion_l2[]= {' ',' ','*', '*','*',' ',' ',0};
char avion_l3[]= {' ','*',' ', '*',' ','*',' ',0};

char explocion_l1[]= {' ',' ','*','*',' ',' ',' ',0};
char explocion_l2[]= {' ','*','*','*','*',' ',' ',0};
char explocion_l3[]= {' ',' ','*','*',' ',' ',' ',0};

char explocion_r1[]= {'*',' ','*','*',' ','*',' ',0};
char explocion_r2[]= {' ','*','*','*','*',' ',' ',0};
char explocion_r3[]= {'*',' ','*','*',' ','*',' ',0};

// esta linea sirve para borrar el avion, primero se borra y luego se imprime el avion en la posicion deseada
char borrar_avion[]= {' ',' ',' ',' ',' ',' ',' ',0};

int num_vidas = 3;
int corazones = 3;
int ix = 40; //coordenada X del avion
int iy = 19; // coordenada Y del avion

// coordenada primer asteroide
int y = 8, x = 12;

// asteroide 2
int yy = 12, xx = 17;

// asteroide 3
int x1 = 58, y1 = 6;

// asteroide 4
int x2 = 70, y2 = 9;

// para los bucles
int i, v;

// variables para determinar el nivel
int repeticion = 0;
int nivel = 1;
bool condicion = false;



// libreria windows.h
void gotoxy(int x, int y)
{
    HANDLE hcon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hcon, dwPos);
}

void vidas(int vi)
{
    gotoxy(2, 1);
    printf("VIDAS: ");
}

// imrpime la cantidad de corazones que le diga
void barra_salud(int n)
{
    gotoxy(72,1);
    printf(" ");
    gotoxy(73,1);
    printf(" ");
    gotoxy(74,1);
    printf(" ");

    for(int v = 0; v < n; v++)
    {
        gotoxy(72+v,1);
        printf("%c", 3); // en el codigo ASCII es un corazon
    }

}

void avion_explota()
{
    gotoxy(ix,iy);
    puts(explocion_l1);
    gotoxy(ix,iy+1);
    puts(explocion_l2); // + 1 en eje Y para que se imprima en la linea de abajo
    gotoxy(ix,iy+2);
    puts(explocion_l3); // + 1 en eje Y para que se imprima en la linea de abajo

    Sleep(380); // el tiempo para que se vea la explosion, sino el programa va muy rapido y no se ve

    gotoxy(ix,iy);
    puts(explocion_r1);
    gotoxy(ix,iy+1);
    puts(explocion_r2);
    gotoxy(ix,iy+2);
    puts(explocion_r3);

    Sleep(380);

    gotoxy(ix,iy);
    puts(avion_l1);
    gotoxy(ix,iy+1);
    puts(avion_l2);
    gotoxy(ix,iy+2);
    puts(avion_l3);

}

void jugar()
{
// rutina de los asteroides
    gotoxy(x, y);
    printf("%c", 2); // 2: codigo ASCII de asteroide
    gotoxy(xx, yy);
    printf("%c", 2);
    gotoxy(x1, y1);
    printf("%c", 2);
    gotoxy(x2, y2);
    printf("%c", 2);

    Sleep(70);

    // borra los asteroides despues de imprimirlos
    gotoxy(x, y); printf(" ");
    gotoxy(xx, yy); printf(" ");
    gotoxy(x1, y1); printf(" ");
    gotoxy(x2, y2); printf(" ");

    // cuando el asteroide llega hasta abajo del todo, vuelve para arriba
    // la posicion X siempre va a ser random !!
    if(y > 20)
    {
        y = 4;
        x = (rand()%70) + 6;
    }

    if(yy > 20)
    {
        yy = 4;
        xx = (rand()%70) + 6;
    }

    if(y1 > 20)
    {
        y1 = 4;
        x1 = (rand()%70) + 6;
    }

    if(y2 > 20)
    {
        y2 = 4;
        x2 = (rand()%70) + 6;
    }

    // rutina para mover el avion
    if(kbhit()) // si se presiona una tecla
    {
        char tecla = getch();

        switch(tecla)
        {
        case IZQUIERDA:
            // para que no se salga de la pantalla
            if(ix > 4)
            {
                // primero se borra el avion
                gotoxy(ix, iy); puts(borrar_avion);
                gotoxy(ix, iy +1); puts(borrar_avion);
                gotoxy(ix, iy +2); puts(borrar_avion);

                // le da movimiento al avion hacia la izquierda
                ix -= 2;

                // ahora dibujamos el avion en las nuevas coordenadas
                gotoxy(ix, iy); puts(avion_l1);
                gotoxy(ix, iy +1); puts(avion_l2);
                gotoxy(ix, iy +2); puts(avion_l3);
            }
            break;

        case DERECHA:
            // para que no se salga de la pantalla
            if(ix < 70)
            {
                gotoxy(ix, iy); puts(borrar_avion);
                gotoxy(ix, iy +1); puts(borrar_avion);
                gotoxy(ix, iy +2); puts(borrar_avion);

                // le da movimiento al avion hacia la izquierda
                ix += 2;

                // ahora dibujamos el avion en las nuevas coordenadas
                gotoxy(ix, iy); puts(avion_l1);
                gotoxy(ix, iy +1); puts(avion_l2);
                gotoxy(ix, iy +2); puts(avion_l3);
            }
            break;
        } // fin del SWITCH
    } // fin del IF

    // rutina para golpes de asteroides
    // coordenadas que abarca el avion en X
    if((x > ix && x < ix +6 && y == iy-1) || (xx > ix && xx < ix +6 && yy == iy-1) || (x1 > ix && x1 < ix +6 && y1 == iy-1) ||(x2 > ix && x2 < ix +6 && y2 == iy-1))
    {
    corazones --;
    barra_salud(corazones);
    printf("\a"); // hace el ruidito cuando le pega

    }
    // imprime el avion
    gotoxy(ix, iy); puts(avion_l1);
    gotoxy(ix, iy +1); puts(avion_l2);
    gotoxy(ix, iy +2); puts(avion_l3);

    if(corazones == 0)
    {
        num_vidas --;
        vidas(num_vidas);
        avion_explota();
        corazones = 3;
        barra_salud(corazones);
    }

    // incremento de los asteroides
    y++;
    yy++;
    y1++;
    y2++;

}

void aniadir(){
	
   cout<<"               _____________________________         ";       
   cout<<"\n    _______|   _    _   __  _ _ _   |_____ ";
   cout<<"\n    |       |  |_|  (_   |     |   |   |    |      | ";
   cout<<"\n    |       | |   |  _) |_  | | |   |      |  ";
   cout<<"\n    |       |_______________________________|      |  ";
   cout<<"\n    |__________)                        (__________| ";
		  
   cout<<"\n     _^_                                      __^__";
   cout<<"\n    ( _ )------------------------------------( _ )";
   cout<<"\n     | | |                                      | | |";
   cout<<"\n     | | |          |  WELCOME TO GAME  |       | | |";
   cout<<"\n     |___|                                      |___|";
   cout<<"\n    (_____)------------------------------------(_____) "; 


	
	
	ofstream archivo;
	
	archivo.open("Puntuacion.txt", ios::app);
	
	if (archivo.fail()){
		
	cout<<"no se pudo crear el archivo de texto";
		exit(1);
	}
	
	char nombre[20];
	archivo<<"\n";
	
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hConsole, 5);
	cout<<"\n\n  [I][n][g][r][e][s][e] "; 
	 
	SetConsoleTextAttribute(hConsole, 15);
	cout<<"[s][u] ";
	
	SetConsoleTextAttribute(hConsole, 5);
	cout<<" [N][o][m][b][r][e]: ";
	cin>>nombre;
	
	
	
	archivo<<nombre;
	
	
	archivo.close();
	
	
}


int main(){
	
		aniadir();
	vidas(num_vidas);
	barra_salud(corazones);
	
	
	gotoxy(ix, iy); puts(avion_l1);
    gotoxy(ix, iy +1); puts(avion_l2);
    gotoxy(ix, iy +2); puts(avion_l3);
	
	
	
	while(num_vidas>0)
	
		jugar();
	
	  HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
 SetConsoleTextAttribute(hConsole, 7);
	cout<<"\n\n[¯G¯][¯R¯][¯A¯][¯C¯][¯I¯][¯A¯][¯S¯]  ";

 SetConsoleTextAttribute(hConsole, 	13);
	cout<<"[¯P¯][¯O¯][¯R¯] ";

 SetConsoleTextAttribute(hConsole, 	11);
	cout<<" [¯J¯][¯U¯][¯G¯][¯A¯][¯R¯]\n\n\n\n\n";  
		
	
	system("pause");
	getch();
	
	
	return 0;
}

