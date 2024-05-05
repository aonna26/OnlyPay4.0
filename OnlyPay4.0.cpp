// Adriana Onna
// Amisadai Morales

// Administrative Code: 654321

#include <iostream>
#include <cctype>
#include <string>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <iomanip>

#define Green   "\033[32m";
#define Red     "\033[31m";
#define Yellow  "\033[33m"
#define Default  "\033[0m";

using namespace std;


//// tiempo

void blip(int x = 5) {
	Sleep(x * 100);
}

void ms() {
	Sleep(500);
	system("cls");
}

void secs(int x) {
	Sleep(x * 1000);
	system("cls");
}

//ui
void arrow() {
	cout << " -> ";
}

void line() {
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------\n";
}

void dots() {
	cout << ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .\n";
}

void invalido() {
	blip();
	cout << Red; cout << " * Ingreso NO valido * \n" << Default;
}

//// animated screen
void loading(int x = 3, string verify = "el balance disponible") {
	ms();
	for (int j = 0; j <= x; j++) { //numero de veces que se repite la animacion del mensaje 

		cout << Yellow; cout << "Este proceso tardara unos segundos en verificar que tenga " << verify;

		for (int i = 0; i <= 10; i++) { // numero de puntos animados en el mensaje
			cout << ".";
			Sleep(200);
		}
		system("cls");
	}
	cout << Default;
	secs(1);
	system("cls");
}

//se crea una estructura llamada Usuario, almacena los diferentes datos
//organizar para no tener que escribir las variables muchas veces
//bluePrint
struct Usuario
{
	int userID;
	string name;
	string lastName;
	string username;
	string password;
	int creditCardNumber;
	int securityNumber;
	int balance;
};
struct transaccion
{
	string destinario;
	float dineroEnviado;
	string fecha;
	string hora;
};

struct usuarioActivo
{
	int ID = 0;
};


//variables constantes
//0-9
const int numUsuarios = 10;
Usuario usuarios[numUsuarios]; //crear usuarios basados en el bluePrint(estructura) llamada Usuario que ya contiene las variables
const int maxTrans = 10;
transaccion Historial[maxTrans];


//// Checks
bool sNCheck(int sN) {
	string x = to_string(sN);
	cout << Red;

	//Si el password no es mayor que 8 
	//devuelve falso (Weak Password)
	if (x.length() > 3)
	{
		cout << "\n- Numero de seguridad demasiado largo! -";
		blip(10);
	}
	else if (x.length() < 3)
	{
		cout << "\n- Numero de seguridad demasiado corto! -";
		blip(10);
	}

	cout << Default;

	return x.length() == 3;
}

bool ccNCheck(int ccN)
{
	string x = to_string(ccN);
	cout << Red;

	//Si el password no es mayor que 8 
	//devuelve falso (Weak Password)
	if (x.length() <= 8)
	{
		cout << "\n- Numero de tarjeta de credito demasiado corto! -";
		blip(10);
	}

	cout << Default;

	return x.length() > 8;
}

bool UsernameCheck(string username) {
	cout << Red;

	//Si el password no es mayor que 8 
	//devuelve falso (Weak Password)
	if (username.length() <= 5)
	{
		cout << "\n\n- Nombre de usuario muy corto! -";
		blip(10);
	}
	else {
		cout << Green; cout << "\n * Nombre de Usuario fuerte! *" << Default;
		blip();
	}

	cout << Default;

	return username.length() > 5;
}

bool PasswordCheck(string password, bool pass)
{
	bool lowChar = false;
	bool SpecialChar = false;
	bool UpperChar = false;
	bool numChar = false;

	cout << Red;

	//Si el password no es mayor que 8 
	//devuelve falso (Weak Password)
	if (password.length() < 8)
	{
		cout << "\n- Password demasiado corto! -";
		blip();
	}
	//loop para verificar desde la
	// primera letra de la palabra hasta la ultima
	for (int i = 0; i < password.length(); i++)
	{
		char character = password[i];
		//Si alguna letra no es alfanumerico
		//entonces regresa true
		if (!isalnum(character))
		{
			SpecialChar = true;
		}
		//Si alguna letra tiene una mayuscula
		//regresa true
		if (isupper(character))
		{
			UpperChar = true;
		}
		//debe tener al menos una letra
		//minuscula

		if (islower(character))
		{
			lowChar = true;
		}
		//debe tener al menos un numero
		if (isdigit(character))
		{
			numChar = true;
		}
	}
	if (SpecialChar != true) {
		cout << "\n- El password debe tener un CARACTER ESPECIAL! -";
		blip();
	}
	if (UpperChar != true) {
		cout << "\n- El password debe tener una LETRA MAYUSCULA! -";
		blip();
	}
	if (lowChar != true) {
		cout << "\n- El password debe tener una LETRA MINUSCULA! -";
		blip();
	}
	//debe tener al menos un numero
	if (numChar != true) {
		cout << "\n- El password debe tener un NUMERO! -";
		blip();
	}
	cout << Default;

	if (SpecialChar && UpperChar && lowChar && numChar && password.length() > 8) {
		cout << Green; cout << "\n * Password seguro! *" << Default;
		pass = true;
		secs(2);
	}
	else {
		secs(4);
	}

	return pass;
}

//Recibe el blueprint Usuario que tiene un array llamado usuarios, tambien recibe el numero de usuarios y el username
//La funcion UserExists es para verificar si el usuario ya existe
bool UserExists(Usuario usuarios[], int numUsuarios, string username)
{

	//va por cada usuario en el array
	//siempre y cuando no pase la cantidad de usuarios que pueda guardar
	for (int i = 0; i < numUsuarios; i++)
	{
		string usuarioActual = usuarios[i].username;

		if (usuarioActual == username)
		{

			//si el usuario Actual es igual al username que se ha ingresado devuelve true
			return true;
		}
	}
	return false;//si son diferentes los usernames devuelve false
}

int idNum(Usuario usuarios[], string username) {

	////Recorre buscando cual es el usuario

	bool salir = false;
	int x;

	for (int i = 0; i < numUsuarios && salir == false; i++)
	{
		//si el usuario[0] esta empty en blueprint (Usuario) 0 guarda la informacion
		if (usuarios[i].username == username) //Al encontrar un elemento vacio guarda la informacion del usuario en ese elemento
		{
			salir = true;
		}
		x = i;
	}
	return x;
}

int Fondos(Usuario usuarios[], int i)
{
	int fondos;
	//// añadir fondos al balance
	ms();
	do {
		cout << "Cuanto dinero desea agregar a sus fondos?\n\n$";
		cin >> fondos;
		if (fondos > 1000) {
			invalido();
			blip();
			cout << Red; cout << "\n * Limite de $1000 *" << Default;
			blip();
			cout << "\n * Vuelva a Intentar *";
			secs(3);
		}
	} while (fondos > 1000);
	usuarios[i].balance = usuarios[i].balance + fondos;
	loading(2, "los fondos disponibles");

	//// Si el banco lo permite (se obvia que s  al momento):
	cout << Green; cout << " * Aprobado *" << Default;
	secs(2);
	return usuarios[i].balance;
}

void RegistrarCuenta(Usuario usuarios[], int numUsuarios, string name, string lastName, string username, string password, int ccN, int sN)
{
	bool salir = false;
	string opc;
	usuarioActivo usuario;

	//le envia a la funcion userExists las siguientes variables
	if (UserExists(usuarios, numUsuarios, username))
	{
		ms();
		cout << Red; cout << " * El usuario '" << username << "' ya existe. Por favor, eliga otro nombre de usuario. *\n" << Default;
		Sleep(2000);

	}
	else
	{
		//Recorrer cada elemento del array verificando si esta vacio

		for (int i = 0; i < numUsuarios && salir == false; i++)
		{
			//si el usuario[0] esta empty en blueprint (Usuario) 0 guarda la informacion
			if (usuarios[i].username.empty()) //Al encontrar un elemento vacio guarda la informacion del usuario en ese elemento
			{

				usuarios[i].userID = i + 1;
				usuarios[i].name = name;
				usuarios[i].lastName = lastName;
				usuarios[i].username = username;
				usuarios[i].password = password;
				usuarios[i].creditCardNumber = ccN;
				usuarios[i].securityNumber = sN;
				usuarios[i].balance = 0;

				ms();
				cout << Green; cout << " * Usuario '" << username << "' creado correctamente! *" << Default;
				secs(2);

				salir = true;
			}
		}
		if (salir == false) {
			ms();
			cout << Red; cout << " * No hay espacio para guardar mas usuarios. *\n" << Default;
			secs(2);
		}
	}
}

int UserMenu(string username)
{
	int opc;
	usuarioActivo usuario;

		cout << " Hola '" << username << "' Bienvenido a OnlyPay! \n\n";
		cout << "   -- " << "MENU" << " --      \n" << endl;
		cout << "1. Enviar dinero" << endl;
		cout << "2. Historial de Pagos" << endl;
		cout << "3. Recargar Fondos" << endl;
		cout << "4. Estado de cuenta" << endl;
		cout << "0. Salir\n\n";
		cout << "Seleccione una opcion: " << endl;
		cin >> opc;
		return opc;
}


bool loginVerificar(Usuario usuarios[], int numUsuarios, string username, string password, int intentos)
{
	bool salir = false;
	usuarioActivo usuario;

	for (int i = 0; i < numUsuarios && salir == false; i++)
	{
		string usuarioActual = usuarios[i].username;
		string passwordActual = usuarios[i].password;
		if (usuarioActual == username && passwordActual == password)
		{
			usuario.ID = i;

			return true;


		}
	} // loop
	if (intentos < 3) {
		blip();
		cout << Red; cout << "\nNOMBRE DE USUARIO o PASSWORD * INCORRECTO *\n\n" << Yellow;
		blip();
		cout << " - Favor intentar de nuevo -\n" << Default;
		secs(3);
		salir = true;
		return false;
	}
	else {
		blip();
		cout << Red; cout << "\nNOMBRE DE USUARIO o PASSWORD * INCORRECTO *\n\n";
		blip();
		cout << " * Ingreso fallido *\n" << Default;
		secs(3);
		salir = true;
		return false;
	}
}
//se le pasa los bluePrints que tiene el array usuarios
void dbUsuarios(Usuario usuarios[], int numUsuarios)
{
	//se crea simulacion de bases de datos
	cout << "                                               " "Bases de datos Usuarios""                                                                      " << endl;
	line();
	cout << " " << "ID" << " " << "\t  Name" << " " << "\t\tLast Name" << " " << "\tUsername" << " " << "\tPassword" << "  " << "\tBalance" << " " << "\tTarjeta de Credito" << "  " << "\tNumero de Seguridad" << endl;
	line();
	//Recorre todos los bluePrints del array
	for (int i = 0; i < numUsuarios; i++)
	{
		if (usuarios[i].username.empty())
		{

		}
		else
		{
			cout << " " << usuarios[i].userID << "\t  " << usuarios[i].name << "\t\t" << usuarios[i].lastName << "\t\t" << usuarios[i].username << "\t\t" << usuarios[i].password << "\t$" << usuarios[i].balance << "\t\t" << usuarios[i].creditCardNumber << "\t\t" << usuarios[i].securityNumber << endl;
		}
		dots();
	}

}
void userSearch(Usuario usuarios[], int x)
{
	x = x - 1;
	secs(2);
	//// simulacion de query
	cout << "                                         " "Bases de datos de: " << usuarios[x].userID << "                                                                      " << endl;
	line();
	cout << " " << "ID" << " " << "\t  Name" << " " << "\t\tLast Name" << " " << "\tUsername" << " " << "\tPassword" << "  " << "\tBalance" << " " << "\tTarjeta de Credito" << "  " << "\tNumero de Seguridad" << endl;
	line();
	//Recorre todos los bluePrints del array
	cout << " " << usuarios[x].userID << "\t  " << usuarios[x].name << "\t\t" << usuarios[x].lastName << "\t\t" << usuarios[x].username << "\t\t" << usuarios[x].password << "\t$" << usuarios[x].balance << "\t\t" << usuarios[x].creditCardNumber << "\t\t" << usuarios[x].securityNumber << endl;
	dots();
}


void menuPrincipal()
{
	//La capacidad maxima de usuarios sera 10
	const int numUsuarios = 10;
	//este array tiene para crear 10 elementos
	//0-9
	Usuario usuarios[numUsuarios]; //crear usuarios basados en el bluePrint(estructura) llamada Usuario que ya contiene las variables
	bool masterkey = false, salir = false, pass = false; //Mantiene loop corriendo
	string name, lastName, username, password, admin, adminPassword;
	//se  crea menu principal
	int opc, menuOpc, input, ccN, sN, userNumberID;
	do
	{
		string adminAccess = (masterkey) ? "3. Bases de Datos\n" : "";
		cout << "   -- " << "MENU" << " --      \n" << endl;
		cout << "1. Registrar Cuenta" << endl;
		cout << "2. Iniciar Cuenta" << endl;
		cout << adminAccess;
		cout << "0. Salir\n\n";
		cin >> opc;
		if (opc == 654321) { //// CODIGO SECRETO
			opc = 3;
		}
		ms();
		//switch cases	
		switch (opc)
		{

		case 1:
			//se pide informacion del usuario
			cout << "   - Registre su Cuenta -\n\n";
			cout << "Nombre: " << endl;
			cin >> name;
			cout << "\nApellido: " << endl;
			cin >> lastName;
			do {
				do {
					ms();
					cout << "   - Registre su Cuenta -\n\n";
					cout << "Crea un nombre de usuario: " << endl;
					cout << Yellow; cout << "(El NOMBRE DE USUARIO debe tener 6 o mas CARACTERES!) \n" << Default;
					cin >> username;
				} while (UsernameCheck(username) != true);
				cout << "\n\nCrea un password: \n";
				cout << Yellow; cout << "(El PASSWORD debe tener 9 o mas CARACTERES!, Debe contener un CARACTER ESPECIAL, una letra MAYUSCULA y una letra MINUSCULA!.)\n" << Default;
				cin >> password;
			} while (PasswordCheck(password, pass) != true);
			//se pasan las variables a la funcion RegistrarCuenta
			//pasa el array de usuarios,cantidad y las demas variables
			do {
				do {
					ms();
					cout << "   - Registre su Cuenta -\n\n";
					cout << "Ingrese el numero de su Tarjeta de Credito: \n";
					cout << Yellow; cout << "(Debe ingresar los 9 DIGITOS de su tarjeta) \n" << Default;
					cin >> ccN;
				} while (ccNCheck(ccN) != true);
				cout << "\nIngrese el Numero Secreto de su tarjeta de credito: \n";
				cout << Yellow; cout << "(Debe ingresar los 3 DIGITOS detras de su tarjeta) \n" << Default;
				cin >> sN;
			} while (sNCheck(sN) != true);
			RegistrarCuenta(usuarios, numUsuarios, name, lastName, username, password, ccN, sN);
			break;

		case 2:
			for (int x = 1; x <= 3; x++) {
				cout << "   - Inicie su Cuenta -\n\n";
				cout << "Usuario: " << endl;
				cin >> username;
				cout << "Password: " << endl;
				cin >> password;
				if (loginVerificar(usuarios, numUsuarios, username, password, x))
				{
					do{
						ms();
						menuOpc = UserMenu(username);
						switch (menuOpc)
						{
						case 1:
							//sendMoney();
							break;
						case 2:
							//HistorialTransaccion();
							break;
						case 3:
							Fondos(usuarios, idNum(usuarios, username));
							break;
						default:
							if (menuOpc != 0) {
								invalido();
								secs(2);
							}
							else {
								ms();
							}
							break;
						}

					} while (menuOpc != 0);

					x = 3;
				}
			}
			break;

		case 3:
			if (masterkey == true) {
				//Para ver la base de datos de los usuarios que tienen
				//cuenta con OnlyPay
				input = -1;
				do {
					if (input == -1 || input == 3) {
						dbUsuarios(usuarios, numUsuarios);
					}
					cout << "\n\n [Presione \"1\" para regresar al menu principal]";
					if (usuarios[0].userID > 0) {
						cout << "\n [Presione \"2\" para ingresar un numero de ID]";
					}
					if (input == 2) {
						cout << "\n [Presione \"3\" para regresar a la database completa]";
					}
					cout << "\n [Presione \"0\" para salir]\n\n ";
					do {
						arrow();
						cin >> input;
						switch (input) {
						case 0:
							salir = true;
							break;

						case 2:
							cout << "\n\n- Ingrese el numero de ID del usuario que desea buscar: -\n\n ";
							arrow();
							cin >> userNumberID;
							userSearch(usuarios, userNumberID);
							break;

						case 3:
							ms();
							break;

						default:
							if (input != 3 && input != 2 && input != 1 && input != 0) {
								invalido();
							}
							break;
						}
					} while (input != 3 && input != 2 && input != 1 && input != 0);
				} while (salir == false && input != 1 && input != 0);
			}
			else {
				cout << "   - Acceda a su Cuenta Administrativa -\n\n";
				cout << "Administrador: \n";
				cin >> admin;
				cout << "\nPassword: \n";
				cin >> adminPassword;
				ms();
			}
			if (admin == "Administrador" && adminPassword == "Password") { //// AQUI USERNAME Y PASSWORD ADMINISTRATIVO
				masterkey = true;
			}
			else {
				invalido();
				secs(2);
			}
			break;

		case 0:
			salir = true;
			string goodbye = (username != "") ? "'", username, "' " : ""; //// si user login dice el username, sino no.
			cout << Green; cout << "\n\n  Gracias " << goodbye << "por utilizar OnlyPay!\n\n" << Default;
			Sleep(1000);
			break;

		}
		if (opc != 0) {
			ms();
			if (opc == 3 && salir == true) {
				cout << Green; cout << "\n\n  Gracias por utilizar OnlyPay (Nivel Administrativo)!\n\n" << Default;
				Sleep(1000);
			}
		}
	} while (salir == false);//Se repite todo hasta que salir sea cierto
}
//esta funcion recibe del bluePrint Usuario  que utiliza el array de usuarios con las demas variables

int main()
{
	menuPrincipal();
	return 0;
}