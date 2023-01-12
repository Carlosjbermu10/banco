#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>

using namespace std;

struct cliente{
	char nombre[50], apellido[50],ci[8];
};

struct fecha{
	int dia,mes,ano;
};

struct cuenta{
	int random;
	cliente dat_c;
	float mont;
	fecha fech;
	cuenta *der;
	cuenta *izq;
};

struct banco{
	char nombre[50];
	int id;
	cuenta *cuentas;
	banco *sig;
};

void menu(int &o);
bool existe_banco(banco *l,int c);
void ingresar_banco(banco *a,banco *&l);
void crear_banco(banco *&l);
banco *obtener_banco(char x[],banco *p);
bool num_cuenta(cuenta *a,int x);
void crear_cuentas(banco *l);
void guardar_cuentas(cuenta *&a,cuenta *n);
void cuentas(cuenta *a,banco *b);
void cuentas_banco(banco *l);
cuenta *mayor(cuenta *l,cuenta *a);
void pedir_banco(banco *l);
void cuenta_mayor(banco *l);
bool verif(cuenta *c, char cod[]);
bool enc(banco *l,char cod[]);
void mostrar(cuenta *a,banco *b,char cod[]);
void pedir_ci(banco *l);
void cuenta_cliente(banco *l,char cod[]);
void mostrar_montos(banco *b,cuenta *c,float cod);
void recorrer_banco(banco *l,float cod);
void mayor_que(banco *l);
void mostrar_montos2(banco *b,cuenta *c,float cod);
void recorrer_banco2(banco *l,float cod);
void menor_que(banco *l);
int cant(cuenta *c);
void cant_cuentas(banco *l);
void mostrar(banco *l);


int main(){
	banco *l = NULL;
	int opc = 0;
	do{
		menu(opc);
		if((opc<1)||(opc>9)){
			cout<<"Opcion invalida, escoja otra opcion"<<endl;
		}else{
			switch (opc){
				case 1: system ("cls"); crear_banco(l);
				break;
				
				case 2: system ("cls"); crear_cuentas(l);
				break;
				
				case 3: system ("cls"); cuentas_banco(l);
				break;
				
				case 4: system ("cls"); pedir_banco(l);
				break;
				
				case 5: system ("cls"); pedir_ci(l);
				break;
				
				case 6: system("cls"); mayor_que(l);
				break;
				
				case 7: system("cls"); menor_que(l); 
				break;
				
				case 8: system("cls"); cant_cuentas(l);
				system("pause");
				system("cls");
				break;
			}
		}
	}while(opc!=9);

}

void menu(int &o){
	cout<<"=============================================================================="<<endl;
	cout<<"1) Registrar un banco"<<endl;
	cout<<"2) Registrar cuenta en un banco"<<endl;
	cout<<"3) Visualizar cuentas de un banco dado"<<endl;
	cout<<"4) Visualizar cuenta con mayor monto en un banco dado"<<endl;
	cout<<"5) Visualizar cuentas de un propietario dado"<<endl;
	cout<<"6) Visualizar cuentas con un monto mayor a uno dado"<<endl;
	cout<<"7) Visualizar cuentas con un monto menor a uno dado"<<endl;
	cout<<"8) Cantidad de cuentas registrada en cada banco"<<endl;
	cout<<"9) Salir"<<endl;
	cout<<"Opcion: "; cin>>o;
	fflush(stdin);
}

bool existe_banco(banco *l,int c){
	if(l!=NULL){
		if(l->id==c){
			return true;
		}else{
			return existe_banco(l->sig,c);
		}
	}else{
		return false;
	}
}

void ingresar_banco(banco *a,banco *&l){
	if(l == NULL){
		l = a;
	}else{
		if(l->id<a->id){
			ingresar_banco(a,l->sig);
		}else{
			a->sig = l;
			l = a;
		}
	}
}

void crear_banco(banco *&l){
	banco *aux = new banco();
	int cod1 = 0; char cod2[50];
	cout<<"=============================================================================="<<endl;
	cout<<"Ingrese el ID del banco a registrar: "<<endl;
	fflush(stdin);
	do{
		cout<<"ID: ";
		cin>>cod1;
		if(existe_banco(l,cod1)){
			cout<<"Este id Ya ha sido registrado con anterioridad, ingrese algun otro id"<<endl;
		}else{
			aux->id = cod1;
			cout<<"Ingrese el Nombre del banco "<<endl;
			fflush(stdin);
			do{
				cout<<"Nombre: ";
				gets(cod2);
				if (obtener_banco(cod2,l)!=NULL){
					cout<<"Este Banco fue registrado con anterioridad, introduzca otro nombre"<<endl;
				}else{
					strcpy(aux->nombre,cod2);
					aux->cuentas = NULL;
					cout<<"=============================================================================="<<endl;
				}
			}while(obtener_banco(cod2,l)!=NULL);	
		}
	}while(existe_banco(l,cod1));
	ingresar_banco(aux,l);
	cout<<"Banco registrado exitosamente"<<endl;
	system("pause");
	system ("cls");
}

banco *obtener_banco(char x[],banco *p){
	banco *aux = p;
	if(aux!=NULL){
		if(strcmp(x,p->nombre)==0){
			return p;
		}else{
			return obtener_banco(x,aux->sig);
		}
	}else{
		return NULL;
	}
}

bool num_cuenta(cuenta *a,int x){
	if (a==NULL){
		return false; 
	}else{
		if(a->random==x){
			return true;
		}else{
			return num_cuenta(a->izq,x)||num_cuenta(a->der,x);
		}
	}
}

void crear_cuentas(banco *l){
	banco *aux = new banco();
	cuenta *nuevo = new cuenta();
	char nom[20];
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Ingrese el Nombre del banco en el que desea Crear una cuenta"<<endl;
		fflush(stdin);
		do{
			cout<<"Nombre: "; gets(nom);
			if(obtener_banco(nom,l)==NULL){
				cout<<"Este banco aún no ha sido registrado, ingrese que ya haya sido registrado"<<endl;
			}else{
				system("cls");
				aux = obtener_banco(nom,l);
				char c1[2],c2[4],c3[6];
				int x = 0;
				fflush(stdin);
				cout<<"=============================================================================="<<endl;
				cout<<"Ingrese a Nombre de quien ira registrada la cuenta: "; gets(nuevo->dat_c.nombre);
				cout<<"Ingrese el apellido: ", gets(nuevo->dat_c.apellido);
				cout<<"Ingrese Cedula de identidad: "; gets(nuevo->dat_c.ci);
				cout<<"Ingrese el monto de apertura de la cuenta: "; cin>>nuevo->mont;
				cout<<"Indique la fecha de apertura"<<endl;
				cout<<"Dia: "; cin>>nuevo->fech.dia;
				cout<<"Mes: ", cin>>nuevo->fech.mes;
				cout<<"Año: ", cin>>nuevo->fech.ano;
				cout<<"=============================================================================="<<endl;
				do{
					srand(time(NULL));
					x = 0 + rand()%(10000);
				}while(num_cuenta(aux->cuentas,x));
				nuevo->random = x;
				guardar_cuentas(aux->cuentas,nuevo);
				system("cls");
				cout<<"=============================================================================="<<endl;
				cout<<"Cuenta registrada exitosamente"<<endl;
				cout<<"=============================================================================="<<endl;
				system("pause");
				system("cls");
				
			}
		}while(obtener_banco(nom,l)==NULL);
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay bancos registrados, registre un banco primero"<<endl;
		cout<<"=============================================================================="<<endl;
		system("pause");
		system("cls");
	}
}

void guardar_cuentas(cuenta *&a,cuenta *n){
	if(a==NULL){
		a = n;
	}else{
		if(a->random>n->random){
			guardar_cuentas(a->izq,n);
		}else{
			if(a->random<n->random){
				guardar_cuentas(a->der,n);
			}
		}
	}
}

void cuentas(cuenta *a,banco *b){
	if(a != NULL){
		cuentas(a->izq,b);
		cout<<"=============================================================================="<<endl;
		cout<<"ID de Cuenta: "<<b->id<<"-"<<a->random<<endl;
		cout<<"Fecha de apertura: "<<a->fech.dia<<"/"<<a->fech.mes<<"/"<<a->fech.ano<<endl;
		cout<<"Titular: "<<a->dat_c.nombre<<" "<<a->dat_c.apellido<<endl;
		cout<<"=============================================================================="<<endl;
		cuentas(a->der,b);
	}
}

void cuentas_banco(banco *l){
	banco *aux = new banco();
	char cod[20];
	fflush(stdin);
	if(l != NULL){
		cout<<"Ingrese Nombre del banco; para visualizar las cuentas que tiene"<<endl;
		do{
			cout<<"Nombre: "; gets(cod);
			if(obtener_banco(cod,l)==NULL){
				cout<<"Este nombre no se encuentra registrado entre los bancos"<<endl;
			}else{
				aux = obtener_banco(cod,l);
				if(aux->cuentas != NULL){
					cuentas(aux->cuentas,aux);
					system("pause");
					system("cls");
				}else{
						cout<<"=============================================================================="<<endl;
						cout<<"No hay cuentas registradas, registre una cuenta primero"<<endl;
						cout<<"=============================================================================="<<endl;
						system("pause");
						system("cls");
				}
			}
		}while(obtener_banco(cod,l)==NULL);
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay bancos registrados, registre un banco primero"<<endl;
		cout<<"=============================================================================="<<endl;
		system("pause");
		system("cls");
	}
}

cuenta *mayor(cuenta *l,cuenta *a){
	if(l != NULL){
		if(l->mont>a->mont){
			a = l;
		}
		a = mayor(l->izq,a);
		a = mayor(l->der,a);
		return a;
	}else{
		return a;
	}
}

void pedir_banco(banco *l){
	char nom[20];
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Ingrese el Nombre del Banco"<<endl;
		fflush(stdin);
		do{
			cout<<"Nombre: "; gets(nom);
			if(obtener_banco(nom,l)==NULL){
				cout<<"Este banco aún no ha sido registrado, ingrese que ya haya sido registrado"<<endl;
			}else{
				cuenta_mayor(obtener_banco(nom,l));
			}
		}while(obtener_banco(nom,l)==NULL);
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay bancos registrados, registre un banco primero"<<endl;
		cout<<"=============================================================================="<<endl;
		system("pause");
		system("cls");
	}
}	

void cuenta_mayor(banco *l){
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Banco: "<<l->nombre<<endl;
		cuenta *aux = new cuenta();
		aux->mont = -100;
		aux = mayor(l->cuentas,aux);
		cout<<"Cuenta con mayor monto: "<<l->id<<"-"<<aux->random<<endl;
		cout<<"Monto: "<<aux->mont<<" Bs."<<endl;
		cout<<"CI propietario: "<<aux->dat_c.ci<<endl;
		cout<<"=============================================================================="<<endl;
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay ningun banco registrado actualmente"<<endl;
		cout<<"=============================================================================="<<endl;
	}
}

bool verif(cuenta *c, char cod[]){
	if (c==NULL){
		return false;
	}else{
		if(strcmp(c->dat_c.ci,cod)==0){
			return true;
		}else{
			return verif(c->izq,cod)||verif(c->der,cod);
		}
	}
}

bool enc(banco *l,char cod[]){
	if(l != NULL){
		if(verif(l->cuentas,cod)){
			return true;
		}else{
			return enc(l->sig,cod);
		}
	}else{
		return false;
	}
}

void mostrar(cuenta *a,banco *b,char cod[]){
	if(a != NULL){
		mostrar(a->izq,b,cod);
		if(strcmp(a->dat_c.ci,cod)==0){
			cout<<"=============================================================================="<<endl;
			cout<<"ID de Cuenta: "<<b->id<<"-"<<a->random<<endl;
			cout<<"Fecha de apertura: "<<a->fech.dia<<"/"<<a->fech.mes<<"/"<<a->fech.ano<<endl;
			cout<<"Titular: "<<a->dat_c.nombre<<" "<<a->dat_c.apellido<<endl;
			cout<<"=============================================================================="<<endl;
		}
		mostrar(a->der,b,cod);
	}
}

void pedir_ci(banco *l){
	char cod[20];
	fflush(stdin);
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Ingrese la cedula de identidad de un propietario para visualizar sus cuentas"<<endl;
		cout<<"CI: ", gets(cod);
		if(!enc(l,cod)){
			cout<<"Ninguna cuenta tiene como titular al propietario: "<<cod<<endl;
		}else{
			cuenta_cliente(l,cod);
		}
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay ningun banco registrado actualmente"<<endl;
		cout<<"=============================================================================="<<endl;
		
	}
	system("pause");
	system("cls");
}


void cuenta_cliente(banco *l,char cod[]){
	fflush(stdin);
	if(l != NULL){
		if(verif(l->cuentas,cod)){
			cout<<"Banco: "<<l->nombre<<endl;
		}
		mostrar(l->cuentas,l,cod);
		cuenta_cliente(l->sig,cod);
	}
}

void mostrar_montos(banco *b,cuenta *c,float cod){
	if(c != NULL){
		mostrar_montos(b,c->izq,cod);
		if(c->mont>cod){
			cout<<"=============================================================================="<<endl;
			cout<<"ID de Cuenta: "<<b->id<<"-"<<c->random<<endl;
			cout<<"Fecha de apertura: "<<c->fech.dia<<"/"<<c->fech.mes<<"/"<<c->fech.ano<<endl;
			cout<<"Titular: "<<c->dat_c.nombre<<" "<<c->dat_c.apellido<<endl;
			cout<<"Saldo en cuenta: "<<c->mont<<" Bs"<<endl;
			cout<<"=============================================================================="<<endl;
		}
		mostrar_montos(b,c->der,cod);
	}
}

void recorrer_banco(banco *l,float cod){
	if(l != NULL){
		if(l->cuentas != NULL){
			cout<<"=============================================================================="<<endl;
			cout<<"Banco: "<<l->nombre<<endl;
			mostrar_montos(l,l->cuentas,cod);
			cout<<"=============================================================================="<<endl;
		}
		recorrer_banco(l->sig,cod);
	}
}

void mayor_que(banco *l){
	float cod = 0;
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Ingrese un monto: "; cin>>cod;
		system("cls");
		fflush(stdin);
		recorrer_banco(l,cod);
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay ningun banco registrado actualmente"<<endl;
		cout<<"=============================================================================="<<endl;
	}
	system("pause");
	system("cls");
}

void mostrar_montos2(banco *b,cuenta *c,float cod){
	if(c != NULL){
		mostrar_montos(b,c->izq,cod);
		if(c->mont<cod){
			cout<<"=============================================================================="<<endl;
			cout<<"ID de Cuenta: "<<b->id<<"-"<<c->random<<endl;
			cout<<"Fecha de apertura: "<<c->fech.dia<<"/"<<c->fech.mes<<"/"<<c->fech.ano<<endl;
			cout<<"Titular: "<<c->dat_c.nombre<<" "<<c->dat_c.apellido<<endl;
			cout<<"Saldo en cuenta: "<<c->mont<<" Bs"<<endl;
			cout<<"=============================================================================="<<endl;
		}
		mostrar_montos(b,c->der,cod);
	}
}

void recorrer_banco2(banco *l,float cod){
	if(l != NULL){
		if(l->cuentas != NULL){
			cout<<"=============================================================================="<<endl;
			cout<<"Banco: "<<l->nombre<<endl;
			mostrar_montos2(l,l->cuentas,cod);
			cout<<"=============================================================================="<<endl;
		}
		recorrer_banco(l->sig,cod);
	}
}

void menor_que(banco *l){
	float cod = 0;
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Ingrese un monto: "; cin>>cod;
		system("cls");
		fflush(stdin);
		recorrer_banco2(l,cod);
	}else{
		cout<<"=============================================================================="<<endl;
		cout<<"No hay ningun banco registrado actualmente"<<endl;
		cout<<"=============================================================================="<<endl;
	}
	system("pause");
	system("cls");
}

int cant(cuenta *c){
	if(c!=NULL){
		return 1+cant(c->izq)+cant(c->der);
	}else{
		return 0;
	}
}

void cant_cuentas(banco *l){
	if(l != NULL){
		cout<<"=============================================================================="<<endl;
		cout<<"Banco: "<<l->nombre<<endl;
		cout<<"Cantidad de cuentas registradas: "<<cant(l->cuentas)<<endl;
		cant_cuentas(l->sig);
	}
}

//Metodo pajuo para ver si esta ordenando bien
void mostrar(banco *l){
	while(l != NULL){
		cout<<"Id: "<<l->id<<endl;
		l = l->sig;
	}
}
