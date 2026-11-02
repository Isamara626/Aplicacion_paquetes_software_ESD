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
void mostrarSolicitudes(nodoSolicitud*frente, nodoPaquete*inicio);
void organizarPrioridades(nodoSolicitud*&frente,nodoSolicitud*&fin);
void procesarPendiente(nodoPaquete*inicio, nodoSolicitud*&frente, nodoSolicitud*&fin);

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
        cout <<  "3. Buscar paquete (codigo)\n";
        cout <<  "4. Registrar solicitud\n";
        cout <<  "5. Mostrar solicitudes\n";
        cout <<  "6. Organizar prioridades\n";
        cout <<  "7. Procesar solicitud pendiente\n";
        cout <<  "8. Salir\n";
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
	   organizarPrioridades(frente,fin);	
	}
	if(opcion == 7){
	   procesarPendiente(inicio,frente,fin);	
	}
	}while(opcion!= 8);
	
	
return 0;	
}

//==========================================
//JONATHAN
//==========================================

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
		
		//CONSULTAR ACA DUDA //SOBRE SI PODEMOS UTILIZAR EL DELETE
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


//METODO PARA REGISTRAR SOLICITUDES DE INSTALACION Y ELIMINACION
void registrarSolicitud(nodoPaquete*inicio, nodoSolicitud*& frente, nodoSolicitud*&fin){
	
	int codigo;
	int tipo;
	
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
    cout << "\n==== REGISTRAR SOLICITUD ====\n";
		cout<<"1. Solicitud de instalacion\n";
		cout<<"2. Solicitud de eliminacion\n";
		cout<<"Seleccione una opcion: ";
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
	cout<<"SOLICITUD REGISTRADA CORRECTAMENTE."<<endl;
	
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
//METODO PARA ORGANIZAR PRIORIDADES
void organizarPrioridades(nodoSolicitud*&frente,nodoSolicitud*&fin){
	
	//VERIFICAMOS SI LA COLA ESTA VACIA
	if(frente== nullptr){
		cout<<"\nNo hay solicitudes pendientes"<<endl;
		return;
	}
	
	//CREAMOS LOS PUNTEROS DE LAS PRIORIDADES
	nodoSolicitud*alta = nullptr;
	nodoSolicitud*finAlta=nullptr;
	nodoSolicitud*media = nullptr;
	nodoSolicitud*finMedia=nullptr;
	nodoSolicitud*baja= nullptr;
	nodoSolicitud*finBaja=nullptr;
	nodoSolicitud*auxiliar=frente;
	
	//RECORREMOS LAS SOLICITUDES
	while(auxiliar!=nullptr){
		int prioridad;
		cout<<"\nCodigo: "<<auxiliar->dato.codigo<<endl;
	
	
	  //PEDIMOS LA PRIORIDAD
	  do{
		 cout<<"1. BAJA"<<endl;
		 cout<<"2. MEDIA"<<endl;
		 cout<<"3. ALTA"<<endl;
		 cout<<"Seleccione la prioridad: ";
		 cin>>prioridad;
		 
		   if(prioridad<1 || prioridad>3){
		     cout<<"PRIORIDAD INCORRECTA"<<endl;
		   }
		   
		}while(prioridad<1 || prioridad>3);
		
		//GUARDAMOS EL SIGUIENTE NODO
		nodoSolicitud*siguiente=auxiliar->siguiente;
		auxiliar->siguiente=nullptr;
		
		//PRIORIDAD ALTA
		if(prioridad==3){
		    if(alta==nullptr){
		    	alta=auxiliar;
		    	finAlta=auxiliar;
		    	
			}else{
				finAlta->siguiente=auxiliar;
				finAlta=auxiliar;
			}
	   }
	   
	   //PRIORIDAD MEDIA
	   if(prioridad==2){
		    if(media==nullptr){
		    	media=auxiliar;
		    	finMedia=auxiliar;
		    	
			}else{
				finMedia->siguiente=auxiliar;
				finMedia=auxiliar;
			}
	   }
	   
	   //PRIORIDAD BAJA
	   if(prioridad==1){
		    if(baja==nullptr){
		    	baja=auxiliar;
		    	finBaja=auxiliar;
		    	
			}else{
				finBaja->siguiente=auxiliar;
				finBaja=auxiliar;
			}
	   }
	   auxiliar=siguiente;
	}
	//VOLVEMOS A UNIR LA COLA SEGUN PRIORIDAD
	frente=nullptr;
	fin=nullptr;
	
	//PRIMERO PRIORIDAD ALTA
	if(alta!=nullptr){
    	frente=alta;
		fin=finAlta;
	}
	
	//AHORA PRIORIDAD MEDIA
	if(media!=nullptr){
		if(frente==nullptr){
			frente=media;
			
		}else{
			fin->siguiente=media;
		}
    	fin=finMedia;
	}
	//POR ULTIMO PRIORIDAD BAJA
	if(baja!=nullptr){
		if(frente==nullptr){
			frente=baja;
		}else{
			fin->siguiente=baja;
		}
		fin=finBaja;
	}
	cout<<"\nSolicitudes organizadas por prioridad: "<<endl;
}
//METODO PARA PROCESAR UNA SOLICITUD PENDIENTE
void procesarPendiente(nodoPaquete*inicio, nodoSolicitud*&frente, nodoSolicitud*&fin){
	
	//VERIFICAMOS SI LA COLA ESTA VACIA
	if(frente==nullptr){
		cout<<" \nNo hay solicitudes pendientes"<<endl;
		return;
	}
	//TOMAMOS LA PRIMERA SOLICITUD
	nodoSolicitud*auxiliar=frente;
	
	//BUSCAMOS EL PAQUETE
	nodoPaquete*encontrado=buscarPaquete(inicio,auxiliar->dato.codigo);
	if(encontrado!=nullptr){
		cout<<"\nCodigo: "<<auxiliar->dato.codigo<<endl;
		
		//PROCESAMOS LA INSTALACION    //ACA SE HICIERON CAMBIOS POR JONATHAN..
		if(auxiliar->dato.tipo==1){
			encontrado->dato.instalado=false;
			cout<<"Solicitud: INSTALACION "<<endl;
			cout<<"Paquete instalado correctamente."<<endl;
			encontrado->dato.instalado = true;
		}
	}else  
	    if(auxiliar->dato.tipo==2){
	    	encontrado->dato.instalado = false;
	    	cout<<"Solicitud: ELIMINACION"<<endl;
		cout<<"paquete eliminado correctamente"<<endl;	//HASTA ACA
	}
	//QUITAMOS LA SOLICITUD DE ENFRENTE
	frente=frente->siguiente;
	
	//VERIFICAMOS SI LA COLA QUEDO VACIA
	if(frente==nullptr){
		fin=nullptr;
	}
	//LIBERAMOS MEMORIA
	delete auxiliar;
}




