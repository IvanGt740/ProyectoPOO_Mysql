#pragma once
#include "Persona.h"
#include <mysql.h>
#include "ConexionBD.h"
#include <iostream>
#include <string>

using namespace std;

class Cliente : Persona {
	//Atributos
private: string nit;

	   //constructor
public:
	Cliente() {
	}
	Cliente(string nom, string ape, string dir, int tel,string fn, string n) : Persona(nom, ape, dir, tel,fn) {
		nit = n;
	}

	//metodos
	//set modificar
	void setNit(string n) { nit = n; }
	void setNombres(string nom) { nombres = nom; }
	void setApellidos(string ape) { apellidos = ape; }
	void setDireccion(string dir) { direccion = dir; }
	void setTelefono(int tel) { telefono = tel; }
	void setFeha_Nacimiento(int fn) { fecha_nacimiento = fn; }
	//get mostrar
	string getNit() { return nit; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getDireccion() { return direccion; }
	int getTelefono() { return telefono; }
	string getFecha_Nacimiento() { return fecha_nacimiento; }

	//metodo
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();
		string t = to_string(telefono);

		if (cn.getConectar()) {
				string insertar = "INSERT INTO clientes(nit,nombres,apellidos,direccion,telefono,fecha_nacimiento)VALUES('"+ nit +"','" + nombres + "','" + apellidos + "','" + direccion + "'," + t + ", '" + fecha_nacimiento + "'); ";
			const char* i = insertar.c_str();

			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso..." << endl;
			}
			else {
				cout << " XXXX Error al Ingresar XXXX" << endl;
			}
		}
		else {
			cout << "--- Error en la conexion ---" << endl;
		}
		cn.cerrar_conexion();
	}
	void leer() {
	
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "select * from clientes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				cout << "Ingreso Exitoso..." << endl;
				resultado = mysql_store_result(cn.getConectar());
				cout << "------------------------Clientes------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << endl;

				}
			}
			else {
				cout << " XXXX Error al Ingresar XXXX" << endl;
			}
		}
		else {
			cout << "--- Error en la conexion ---" << endl;
		}
		cn.cerrar_conexion();
	}
};

