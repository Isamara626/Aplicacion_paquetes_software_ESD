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

//ESTRUCTURA QUE ALMACENA LOS DATOS DE LA SOLICITUD
struct solicitud{
	int codigo;
	int tipo; //1 INSTALACION, 2 ELIMINACION.
	
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
void registrarSolicitud(nodoPaquete*inicio, nodoSolicitud*& frente, nodoSolicitud*&fin);


int main(){
  nodoPaquete* inicio = nullptr;
  nodoSolicitud* frente = nullptr;
  nodoSolicitud* fin = nullptr;
  int opcion;
  
  do{
  
   //MOSTRAMOS EL MENU DE OPCIONES
   cout << "\n===== GESTOR DE PAQUETES =====\n";
        cout << "1. Registrar paquete\n";
        cout << "2. Mostrar paquetes\n";
        cout<< "3. Buscar paquete (codigo)\n";
        cout<< "4.Registrar solicitud\n";
        cout << "5. Salir\n";
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
	}while(opcion!= 5);
	
	
return 0;	
}


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
//Isamara
//==========================


//METODO PARA REGISTRAR SOLICITUDES DE INSTALACION Y ELIMINACION

void registrarSolicitud(nodoPaquete*inicio, nodoSolicitud*& frente, nodoSolicitud*&fin){
	
	int codigo, tipo;
	
	//PEDIMOS EL CODIGO DEL PAQUETE
    cout<<"\nIngrese el codigo del paquete."<<endl;
    cin>>codigo;
    
    //BUSCAMOS EL PAQUETE
    nodoPaquete*encontrado = buscarPaquete(inicio,codigo);
    
    //VERIFICAMOS SI EL PAQUETE EXISTE
    
    if(encontrado == nullptr){
    	cout<<"ERROR: EL PAQUETE NO EXISTE."<<endl;
    	
    	return;
	}
	
	//MOSTRAMOS OPCIONES PARA PODER REGISTRAR UNA SOLICITUD
	
    	cout<<"\n====REGISTRAR SOLICITUD===="<<endl;
		cout<<"\n1. Solicitud de instalacion"<<endl;
		cout<<"\n2. Solicitud de eliminacion"<<endl;
		cout<<"\nSeleccione una opcion"<<endl;
		cin>>tipo;
    
    //VERIFICAMOS QUE LA OPCION SEA LA CORRECTA
    if(tipo!=1 && tipo!=2){
    	cout<<"\nOpcion correcta."<<endl;
    	return;
	}
	
	//CREAMOS UN NUEVO NODO PARA LA SOLICITUD
	nodoSolicitud*nuevo = new nodoSolicitud;
	
	//GUARDAMOS LOS DATOS DE LA SOLICITUD
	
    nuevo->dato.codigo = codigo;
	nuevo->dato.tipo = tipo;
    nuevo->siguiente = nullptr;
    
    //VERIFICAR SI LA COLA ESTA VACIA
    if(frente == nullptr){
    	
    	//EL NUEVO NODO SERA EL PRIMERO Y EL ULTIMO
    	frente = nuevo;
    	fin = nuevo;	
	}
	else{
		//AGREGAMOS LA SOLICITUD AL FINAL DE LA COLA
		fin->siguiente = nuevo;
	    fin = nuevo;
	}
	
	//MOSTRAMOS UN MENSAJE DE CONFIRMACION
	cout<<"\n SU SOLICITUD SE REGISTRO CORRECTAMENTE."<<endl;
}


