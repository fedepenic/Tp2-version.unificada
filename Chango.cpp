#include <iostream>
#include "Chango.h"

using namespace std;

Chango::Chango(){
	cout << "Constructor de Chango" << endl;
	tamanio_chango = TAMANIO_INICIAL_CHANGO;
	monto_a_abonar = MONTO_INICIAL_A_ABONAR;
	ahorro_total = AHORRO_INICIAL;
	productos_chango = NULL;
	chango_auxiliar = NULL;
}

void Chango::agregar_producto(Producto* producto_a_agregar){
	tamanio_chango ++;
	if(tamanio_chango == PRIMER_TAMANIO_CHANGO){
		productos_chango = new Producto[tamanio_chango];
		agregar_nuevo_producto(producto_a_agregar);
	}
	else{
		chango_auxiliar = new Producto[tamanio_chango];
		preparar_chango(producto_a_agregar);
	}	
}

void Chango::agregar_nuevo_producto(Producto* producto_a_agregar){
	productos_chango[tamanio_chango-1].asignar_nombre(producto_a_agregar->obtener_nombre());
	productos_chango[tamanio_chango-1].asignar_codigo(producto_a_agregar->obtener_codigo());
	productos_chango[tamanio_chango-1].asignar_precio(producto_a_agregar->obtener_precio());
	productos_chango[tamanio_chango-1].asignar_oferta(producto_a_agregar->obtener_oferta());
	cout<<endl<<"Su producto ha sido agregado correctamente al Chango"<<endl;
	actualizar_monto_y_ahorro(producto_a_agregar);
	informar_monto_y_ahorro();
}

void Chango::preparar_chango(Producto* producto_a_agregar){
	desplazar_chango_viejo();
	delete[] productos_chango;
	productos_chango = chango_auxiliar;
	agregar_nuevo_producto(producto_a_agregar);
	chango_auxiliar = NULL;
}

void Chango::desplazar_chango_viejo(){
	for(int i=0;i<(tamanio_chango-1);i++){
		chango_auxiliar[i].asignar_nombre(productos_chango[i].obtener_nombre());
		chango_auxiliar[i].asignar_codigo(productos_chango[i].obtener_codigo());
		chango_auxiliar[i].asignar_precio(productos_chango[i].obtener_precio());
		chango_auxiliar[i].asignar_oferta(productos_chango[i].obtener_oferta());
	}
}

void Chango::mostrar_productos_chango(){
	cout << "Mostrando productos de Chango [" << tamanio_chango << "]" << endl << endl;
    if(tamanio_chango>TAMANIO_INICIAL_CHANGO){
    	for(int i = 0; i < tamanio_chango; i++){
       	 	mostrar_producto_particular_chango(i);
    	}
    	informar_monto_y_ahorro();
    }
    else{
    	cout << endl << "Actualmente no tiene ningún producto en su Chango." << endl;
    }	
}

void Chango::mostrar_producto_particular_chango(int posicion){
    cout << "Codigo: " << productos_chango[posicion].obtener_codigo() << endl;
    cout << "Producto: " << productos_chango[posicion].obtener_nombre() << endl;
    cout << "Precio: $ " << productos_chango[posicion].obtener_precio() << endl;
    if(productos_chango[posicion].obtener_oferta()){
        cout << "Oferta: Esta en oferta! :D" << endl << endl;
    }else{
        cout << "Oferta: No esta en oferta :(" << endl << endl;
    }
}

void Chango::actualizar_monto_y_ahorro(Producto* producto_a_agregar){
	monto_a_abonar += producto_a_agregar->obtener_precio();
	if(producto_a_agregar->obtener_oferta()){
		ahorro_total += ((producto_a_agregar->obtener_precio()) * TASA_DE_DESCUENTO);
	}
}

void Chango::informar_monto_y_ahorro(){
	cout << endl << endl << "El monto sin descuento del chango es de $" << monto_a_abonar << endl;
	cout << endl << endl << "Y el ahorro total hasta ahora es de $" << ahorro_total << endl;
	cout << endl << endl << "En resumen, el monto total a abonar es de $" << monto_a_abonar - ahorro_total << endl;
}

Chango::~Chango(){
	cout << "Destructor Chango" << endl;
    if(productos_chango!=NULL){
    	delete[] productos_chango;
    }
}
