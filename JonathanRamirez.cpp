#include<iostream>
using namespace std;


//COMENZADO PRUEBA 
//CREAMOS LA ESTRUCTURA QUE ALMACENARA LOS DATOS DEL PAQUETE DE SOFWARE

struct paquete{
	int codigo;
	string nombre;
	string version;
	bool instalado;
};

//ENUMERACION DE PRIORIDAD, FATIMA
enum Prioridad {Baja = 1, Media = 2, Alta = 3};

//ESTRUCTURA QUE ALMACENA LOS DATOS DE LA SOLICITUD
struct solicitud{
	int codigo;
	int tipo; //1 INSTALACION, 2 ELIMINACION.
	Prioridad prioridad; //FATIMA
};


//CREAMOS EL NODO A LA LISTA ENLAZADA
struct nodoPaquete{
	paquete dato;
	nodoPaquete* siguiente;
};

//CREAMOS EL NODO PARA LA COLA DE SOLICITUDES
struct nodoSolicitud{
	solicitud dato;
	nodoSolicitud*siguiente;
};

//ACA CREE EL PUNTERO DE INICIO
//nodoPaquete *inicio = nullptr;

//METODOS CREADOS
void registrarPaquete(nodoPaquete*& inicio);
void mostrarPaquete(nodoPaquete* inicio);
nodoPaquete* buscarPaquete(nodoPaquete* inicio,int codigo);
bool existeSolicitud(nodoSolicitud* frente, int codigo); //FATIMA
void registrarSolicitud(nodoPaquete*inicio, nodoSolicitud*& frente, nodoSolicitud*&fin);
void mostrarSolicitudes(nodoSolicitud*frente, nodoPaquete*inicio);
void procesarSolicitud(nodoPaquete* inicio, nodoSolicitud*& frente, nodoSolicitud*& fin); //FATIMA
void liberarMemoria(nodoPaquete*& inicio, nodoSolicitud*& frente, nodoSolicitud*& fin); //FATIMA

int main(){
  nodoPaquete* inicio = nullptr;
  nodoSolicitud* frente = nullptr;
  nodoSolicitud* fin = nullptr;
  int opcion = 0;
  
  do{
  
   //MOSTRAMOS EL MENU DE OPCIONES
   cout << "\n===== GESTOR DE PAQUETES =====\n";
        cout << "1. Registrar paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout <<  "3. Buscar paquete (codigo)\n";
        cout <<  "4. Registrar solicitud\n";
        cout <<  "5. Mostrar solicitudes pendientes\n";
        cout << "6. Procesar siguiente solicitud\n"; //FATIMA
        cout <<  "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
    if(opcion == 1){
    	registrarPaquete(inicio);
	}
	if(opcion == 2){
		mostrarPaquete(inicio);
	}
	if(opcion == 3){
		int codigo;
		cout << "Ingrese el codigo del paquete: "<<endl;
		cin >> codigo;
	
		
		
		//CREAMOS UN PUNTERO QUE GUARDARA EL RETORNOO DE LA FUNCION
		nodoPaquete* encontrado = buscarPaquete(inicio,codigo);
		if(encontrado != nullptr){
			cout<<"\n==PAQUETE ECONTRADO=="<<endl;
			cout<<"\nNombre: "<<encontrado->dato.nombre<<endl;
			cout<<"\nVersion: "<<encontrado->dato.version<<endl;
		}else{
			cout<<"\nEl paquete no existe"<<endl;
		}
	}
		
	if(opcion == 4){
	   registrarSolicitud(inicio,frente,fin);	
	}
	
	if(opcion == 5){
	   mostrarSolicitudes(frente,inicio);	
	}
	
	if(opcion == 6){
		procesarSolicitud(inicio, frente, fin);
	}
	}while(opcion!= 7);
	
	//LIBERAR SOLICITUDES PENDIENTES, FATIMA
	while(frente != nullptr) {
    nodoSolicitud* auxiliar = frente;
    frente = frente->siguiente;
    delete auxiliar;
	}fin = nullptr;

	// LIBERAR PAQUETES REGISTRADOS
	while(inicio != nullptr) {
    nodoPaquete* auxiliar = inicio;
    inicio = inicio->siguiente;
    delete auxiliar;
	}
	
	
return 0;	
}

//========
//VANESSA
//========

//METODO PARA REGISTRAR UN PAQUETE
void registrarPaquete(nodoPaquete*& inicio){
	
	//CONSULTAR SI SE PUEDE HACER
	//nodoPaquete* nuevo = (nodoPaquete*) malloc(sizeof(nodoPaquete));
	nodoPaquete* nuevo = new nodoPaquete;
	
	//PEDIMOS LA INFORMACION DEL PAQUETE DE SOFWARE
	cout<<"Ingrese el codigo: "<< endl;
	cin>>nuevo->dato.codigo;
	
	//VERIFICAMOS QUE EL PAQUETE NO EXISTA YA
	nodoPaquete* encontrado = buscarPaquete(inicio,nuevo->dato.codigo);
	if(encontrado != nullptr){
		cout<<"ERROR: YA EXISTE UN PAQUETE CON ESE CODIGO.."<<endl;
		delete nuevo;
		return;
		//CONSULTAR ACA DUDA //
	}
	
	cout<<"Ingrese el nombre: "<<endl;
	cin>>nuevo->dato.nombre;
	
	cout<<"Ingrese la version del paquete: "<<endl;
	cin>> nuevo->dato.version;
	
	nuevo->dato.instalado = false;
	nuevo->siguiente = nullptr;
	
	if(inicio == nullptr){
		inicio = nuevo;
		
	}else{
		nodoPaquete* auxiliar = inicio;
		
		while(auxiliar->siguiente!= nullptr){
			auxiliar = auxiliar->siguiente;
		}
		auxiliar->siguiente = nuevo;
		
	}
	cout<<"Paquete registrado correctamente.\n"<<endl;
}

//METODO PARA MOSTRAR LOS PAQUETES REGISTRADOS
void mostrarPaquete(nodoPaquete* inicio){
	nodoPaquete* auxiliar = inicio;
	
	while(auxiliar != nullptr){
		//MOSTRAMOS LOS DATOS
		cout<<"\n====PAQUETES REGISTRADOS===="<<endl;
		cout<<"\nCodigo: "<<auxiliar->dato.codigo<<endl;
		cout<<"\nNombre: "<<auxiliar->dato.nombre<<endl;
		cout<<"\nVersion: "<<auxiliar->dato.version<<endl;
		cout<<"\nInstalado: "<<auxiliar->dato.instalado<<endl;
		
		auxiliar = auxiliar->siguiente;
		
	}
}

//METODO PARA BUSCAR UN PAQUETE POR SU CODIGO
nodoPaquete* buscarPaquete(nodoPaquete *inicio,int codigo){
	
	nodoPaquete* auxiliar = inicio;
	while(auxiliar != nullptr){
		if(auxiliar->dato.codigo == codigo){
			return auxiliar;
		}
		auxiliar = auxiliar->siguiente;
	}
	return nullptr;
}

//==========================
//Isamara *-*
//==========================
//SE MODIFICO EL METODO ORIGINAL AGREGANDO LA PRIORIDAD, FATIMA
// REGISTRAR SOLICITUDES SEGUN SU PRIORIDAD 
void registrarSolicitud(nodoPaquete* inicio,
                        nodoSolicitud*& frente,
                        nodoSolicitud*& fin) {

    int codigo, tipo, prioridad;

    cout << "\nIngrese el codigo del paquete: ";
    cin >> codigo;

    nodoPaquete* encontrado = buscarPaquete(inicio, codigo);

    if(encontrado == nullptr) {
        cout << "El paquete no existe.\n";
        return;
    }

    // VERIFICAR SI YA EXISTE UNA SOLICITUD PENDIENTE
    nodoSolicitud* aux = frente;

    while(aux != nullptr) {
        if(aux->dato.codigo == codigo) {
            cout << "Ya existe una solicitud pendiente.\n";
            return;
        }
        aux = aux->siguiente;
    }

    cout << "\n1. Instalacion\n";
    cout << "2. Eliminacion\n";
    cout << "Seleccione el tipo: ";
    cin >> tipo;

    if(tipo != 1 && tipo != 2) {
        cout << "Tipo incorrecto.\n";
        return;
    }

    // COMPROBAR EL ESTADO ACTUAL
    if(tipo == 1 && encontrado->dato.instalado) {
        cout << "El paquete ya esta instalado.\n";
        return;
    }

    if(tipo == 2 && !encontrado->dato.instalado) {
        cout << "El paquete no esta instalado.\n";
        return;
    }

    cout << "\n=== NIVEL DE PRIORIDAD ===\n";
    cout << "1. Baja\n";
    cout << "2. Media\n";
    cout << "3. Alta\n";
    cout << "Seleccione la prioridad: ";
    cin >> prioridad;

    if(prioridad < 1 || prioridad > 3) {
        cout << "Prioridad incorrecta.\n";
        return;
    }

    // CREAR NODO EN MEMORIA DINAMICA
    nodoSolicitud* nuevo = new nodoSolicitud;

    nuevo->dato.codigo = codigo;
    nuevo->dato.tipo = tipo;
    nuevo->dato.prioridad = (Prioridad) prioridad;
    nuevo->siguiente = nullptr;

    // CASO 1: COLA VACIA
    if(frente == nullptr) {
        frente = nuevo;
        fin = nuevo;
    }

    // CASO 2: MAYOR PRIORIDAD QUE EL FRENTE
    else if(nuevo->dato.prioridad > frente->dato.prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
    }

    // CASO 3: INSERTAR EN SU POSICION
    else {
        nodoSolicitud* auxiliar = frente;

        while(auxiliar->siguiente != nullptr &&
              auxiliar->siguiente->dato.prioridad >=
              nuevo->dato.prioridad) {
            auxiliar = auxiliar->siguiente;
        }
        nuevo->siguiente = auxiliar->siguiente;
        auxiliar->siguiente = nuevo;
        if(nuevo->siguiente == nullptr) {
            fin = nuevo;
        }
    }
    cout << "\nSOLICITUD REGISTRADA CORRECTAMENTE.\n";
}
//METODO MOSTRAR SOLICITUDES REGISTRADAS
void mostrarSolicitudes(nodoSolicitud*frente, nodoPaquete*inicio){
	
	nodoSolicitud* auxiliar = frente;
	
	if(auxiliar==nullptr){
		cout<<"\nNO HAY SOLICITUDES REGISTRADAS"<<endl;
		return;
	}
	
	while(auxiliar!=nullptr){
		
		//MOSTRAMOS LOS DATOS
		cout<<"\n====SOLICITUDES REGISTRADAS===="<<endl;
		cout<<"Codigo: "<<auxiliar->dato.codigo<<endl;
		
		if(auxiliar->dato.tipo==1){
			cout<<"Tipo: INSTALACION "<<endl;
		}
		else{
		    cout<<"Tipo: ELIMINACION "<<endl;	
		}
		
		//MOSTRAR PRIORIDAD, FATIMA
		if(auxiliar->dato.prioridad == Alta){
		cout << "Prioridad: ALTA" << endl;
		}
		else if(auxiliar->dato.prioridad == Media){
		cout << "Prioridad: MEDIA" << endl;
		}
		else{
		cout << "Prioridad: BAJA" << endl;
		} 
		
		//BUSCAMOS EL PAQUETE PARA MOSTRAR SU ESTADO
		nodoPaquete*encontrado = buscarPaquete(inicio,auxiliar->dato.codigo);
		
		if(encontrado!= nullptr){
			cout<<"Nombre: "<<encontrado->dato.nombre<<endl;
			
			if(encontrado->dato.instalado== true) {
				cout<<"Estado: INSTALADO"<<endl;
			}
			else{
				cout<<"Estado: NO INSTALADO"<<endl;
			}
		}
		else{
			cout<<"PAQUETE NO ENCONTRADO"<<endl;
		}
		auxiliar = auxiliar->siguiente;
	}
}

// PROCESAR LA SOLICITUD DE MAYOR PRIORIDAD, FATIMA
void procesarSolicitud(nodoPaquete* inicio,
                       nodoSolicitud*& frente,
                       nodoSolicitud*& fin) {

    if(frente == nullptr) {
        cout << "\nNO HAY SOLICITUDES PENDIENTES.\n";
        return;
    }

    // TOMAR LA PRIMERA SOLICITUD
    nodoSolicitud* auxiliar = frente;

    // BUSCAR EL PAQUETE
    nodoPaquete* encontrado =
        buscarPaquete(inicio, auxiliar->dato.codigo);

    if(encontrado == nullptr) {
        cout << "ERROR: El paquete no existe.\n";
    }
    else {

        // PROCESAR INSTALACION
        if(auxiliar->dato.tipo == 1) {

            if(!encontrado->dato.instalado) {
                encontrado->dato.instalado = true;
                cout << "\nPaquete instalado correctamente.\n";
            }
            else {
                cout << "ERROR: Ya esta instalado.\n";
            }
        }

        // PROCESAR ELIMINACION
        if(auxiliar->dato.tipo == 2) {

            if(encontrado->dato.instalado) {
                encontrado->dato.instalado = false;
                cout << "\nPaquete eliminado correctamente.\n";
            }
            else {
                cout << "ERROR: No esta instalado.\n";
            }
        }
    }

    // ELIMINAR LA SOLICITUD DEL FRENTE
    frente = frente->siguiente;

    if(frente == nullptr) {
        fin = nullptr;
    }

    // LIBERAR MEMORIA
    delete auxiliar;
}
