#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;


struct user{
    string id;
    string name;
    string age;
    string username;
    string mail;
    string password;
    string country;
    user *next;
};

void enter(){
    cout << "Presione enter para continuar...";
    cin.ignore();
    cin.get();
}

//Validar ID
bool validate_id_user(string id, user *inicio){
    cout << "Validando ID..." << endl;
    if(id.empty()){
        cout << "El ID no puede estar vacio." << endl;
        return false;
    }
    else{
        user *aux = inicio;
        while(aux != NULL){
            if(aux->id == id){
                cout << "El ID ya existe." << endl;
                return false;
            }
            aux = aux->next;
        }
    }
    return true;
}

//Validar formato de ID
bool validate_format_id_user(string id, user *inicio){
    if(!all_of(id.begin(), id.end(), [](char i){
        return isdigit(i);
    })){
        cout << "El ID solo debe contener numeros." << endl;
        return false;
    }
    return true;
}

//Validar correo
bool validate_format_mail_user(string mail){
    cout << "Validando correo..." << endl;
    int at_sing, doc = 0;
    if(mail.empty()){
        cout << "El correo no puede estar vacio." << endl;
        return false;
    }
    else{
    for (int i = 0; i < mail.length(); i++){
        if (mail[i] == '@'){
            at_sing++;
        }
        if (mail[i] == '.'){
            doc++;
        }
    }
    }
    if (at_sing == 1 && doc >= 1 && !mail.empty()){
        return true;
    }
    return false;
}

//Validar edad
bool validate_format_age_user(string age){
    cout << "Validando edad..." << endl;
    if(age.empty()){
        cout << "La edad no puede estar vacia." << endl;
        return false;
    }
    else if(!age.empty() && !all_of(age.begin(), age.end(), [](char i){
        return isdigit(i);
    })){
        cout << "La edad solo debe contener numeros." << endl;
        return false;
    }
    else if(stoi(age) < 13 && !age.empty()){
        cout << "El usuario debe ser mayor de 13 años." << endl;
        return false;
    }
    else if(stoi(age) > 120 && !age.empty()){
        cout << "Edad invalida." << endl;
        return false;
    }
    return true;
}

//Validar que el pais exista
bool validate_country(string country){
    cout << "Validando pais..." << endl;
    string countries[] = {"Venezuela", "Colombia", "Argentina", "Chile", "Peru", "Ecuador", "Uruguay", "Paraguay", "Bolivia", "Brasil", "Mexico", "Estados Unidos", "Canada", "España", "Portugal", "Francia", "Alemania", "Italia", "Inglaterra", "Holanda", "Belgica", "Suiza", "Suecia", "Noruega", "Finlandia", "Dinamarca", "Rusia", "China", "Japon", "Corea del Sur", "India", "Australia", "Nueva Zelanda", "Sudafrica", "Egipto", "Nigeria", "Kenia", "Ghana", "Marruecos", "Argelia", "Tunez", "Libia", "Sahara Occidental", "Mauritania", "Senegal", "Gambia", "Guinea", "Sierra Leona", "Liberia", "Costa de Marfil", "Burkina Faso", "Ghana", "Togo", "Benin", "Niger", "Chad", "Sudan", "Sudan del Sur", "Etiopia", "Eritrea", "Djibouti", "Somalia", "Uganda", "Ruanda", "Burundi", "Congo", "Congo", "Angola", "Zambia", "Zimbabwe", "Mozambique", "Namibia", "Botswana", "Sudafrica", "Madagascar", "Mauricio", "Seychelles", "Comoras", "Maldivas", "Sri Lanka", "Bangladesh", "Pakistan", "Afganistan", "Iran", "Iraq", "Siria", "Libano"};
    if(country.empty()){
        cout << "El pais no puede estar vacio." << endl;
        return false;
    }
    else if(find(begin(countries), end(countries), country) != end(countries)){
        return true;
    }
    return false;
}



//Agregar usuarios
void add_new_user(user *&inicio, user *&fin){
    user *nuevo = new user;
    cout << "Agregando usuario..." << endl;
    cout << "ID: ";
    cin.ignore();
    getline(cin, nuevo->id);
    if(nuevo->id == "Cancelar"){
        cout << "Cancelando. Saliendo al menu principal." << endl;
        return;
    }
    while(!validate_id_user(nuevo->id, inicio) || !validate_format_id_user(nuevo->id, inicio)){
        cout << "ID: ";
        getline(cin, nuevo->id);
    }
    cout << "ID valido." << endl;
    cout << "Nombre: ";
    cin >> nuevo->name;
    cout << "Edad: ";
    cin.ignore();
    getline(cin, nuevo->age);
    if(nuevo->age == "Cancelar"){
        cout << "Cancelando. Saliendo al menu principal." << endl;
        return;
    }
    while(!validate_format_age_user(nuevo->age)){
        cout << "Edad: ";
        getline(cin, nuevo->age);
    }
    cout << "Edad valida." << endl;
    cout << "Username: ";
    cin >> nuevo->username;
    cout << "Mail: ";
    cin.ignore();
    getline(cin, nuevo->mail);
    if(nuevo->mail == "Cancelar"){
        cout << "Cancelando. Saliendo al menu principal." << endl;
        return;
    }
    while(!validate_format_mail_user(nuevo->mail)){
        cout << "Mail: ";
        getline(cin, nuevo->mail);
    }
    cout << "Mail valido." << endl;
    cout << "Password: ";
    cin >> nuevo->password;
    cout << "Pais: ";
    cin.ignore();
    getline(cin, nuevo->country);
    if(nuevo->country == "Cancelar"){
        cout << "Cancelando. Saliendo al menu principal." << endl;
        return;
    }
    while(!validate_country(nuevo->country)){
        cout << "Pais: ";
        getline(cin, nuevo->country);
    }
    if(nuevo->name == "Cancelar" || nuevo->username == "Cancelar" || nuevo->password == "Cancelar"){
        cout << "Cancelando. Saliendo al menu principal." << endl;
        return;
    }
    nuevo->next = NULL;
    if(inicio == NULL){
        inicio = nuevo;
        fin = nuevo;
    }else{
        fin->next = nuevo;
        fin = nuevo;
    }
}

//Mostrar usuarios
void show_users(user *begin){
    user *aux = begin;
    while(aux != NULL){
        cout << "ID: " << aux->id << endl;
        cout << "Nombre: " << aux->name << endl;
        cout << "Edad: " << aux->age << endl;
        cout << "Username: " << aux->username << endl;
        cout << "Mail: " << aux->mail << endl;
        cout << "Password: " << aux->password << endl;
        cout << "Pais: " << aux->country << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
    if(aux == NULL && begin == NULL){
        cout << "No hay usuarios registrados." << endl;
    }
}

//Eliminar usuarios
void delete_user(user *&begin, user *&end){
    string id;
    cout << "ID del usuario a eliminar: ";
    cin >> id;
    user *aux = begin;
    user *aux2 = NULL;
    while(aux != NULL && aux->id != id){
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No se encontro el usuario" << endl;
    }else if(aux == begin){
        cout << "Eliminando usuario..." << endl;
        begin = begin->next;
        delete aux;
        cout << "Usuario eliminado" << endl;
    }else{
        aux2->next = aux->next;
        cout << "Eliminando usuario..." << endl;
        delete aux;
        cout << "Usuario eliminado" << endl;
    }
}

//Guardar usuarios en un archivo
void save_users(user *begin){
    user *aux = begin;
    const char user_delimiter = '|';
    string file_path = "C:/Users/sebas/Documents/usuarios.txt";
    ofstream file_users(file_path);
    while(aux != NULL){
        file_users << aux->id << user_delimiter;
        file_users << aux->name << user_delimiter;
        file_users << aux->age << user_delimiter;
        file_users << aux->username << user_delimiter;
        file_users << aux->mail << user_delimiter;
        file_users << aux->password << user_delimiter;
        file_users << aux->country << endl;
        aux = aux->next;
    }
    if(file_users.is_open() && begin != NULL){
        cout << "Usuarios guardados correctamente." << endl;
    }
    else{
        cout << "Error al guardar los usuarios." << endl;
    }
    if(begin == NULL){
        cout << "No hay usuarios registrados. No se guardo ningun usuario." << endl;
    }
    file_users.close();
}

//Ver ruta de archivo donde se guardaron los usuarios
void show_file_path(string file_name){
    cout << "Ruta del archivo: " << file_name << endl;
}

//Leer archivo de usuarios
void read_file_users(user *&begin, user *&end){
    const char user_delimiter = '|';
    string file_path = "C:/Users/sebas/Documents/usuarios.txt";
    ifstream file_users(file_path);
    string id, name, age, username, mail, password, country;
    if(!file_users.is_open()){
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return;
    }
    string line;
    while(getline(file_users, line)){
        user *new_user = new user;
        istringstream iss(line);
        getline(iss, id, user_delimiter);
        if(!validate_format_id_user(id, begin)){
            cout << "Error archivo usuarios: El ID de usuario '" << id << "' no se ha cargado porque no tiene un formato valido.\n";
            continue;
        }
        else if(!validate_id_user(id, begin)){
            cout << "Error archivo usuarios: El ID de usuario '" << id << "' no se ha cargado porque el ID ya existe.\n";
            continue;
        }
        new_user->id = id;
        getline(iss, name, user_delimiter);
        new_user->name = name;
        getline(iss, age, user_delimiter);
        new_user->age = age;
        getline(iss, username, user_delimiter);
        new_user->username = username;
        getline(iss, mail, user_delimiter);
        if(!validate_format_mail_user(mail)){
            cout << "Error archivo usuarios: El usuario ID '" << id << "' no se ha cargado porque el correo '" << mail << "' no tiene un formato valido.\n";
            enter();
            continue;
        }
        new_user->mail = mail;
        getline(iss, password, user_delimiter);
        new_user->password = password;
        getline(iss, country, '\n');
        if(!validate_country(country)){
            cout << "Error archivo usuarios: El usuario ID '" << id << "' no se ha cargado porque el pais '" << country << "' no existe.\n";
            continue;
        }
        new_user->country = country;
        new_user->next = NULL;
        if(begin == NULL){
            begin = new_user;
            end = new_user;
        }
        else{
            end->next = new_user;
            end = new_user;
        }
    }
    file_users.close();
}
