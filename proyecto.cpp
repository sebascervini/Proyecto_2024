#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

/*Comandos git
- git init
- git add .
- git commit -m "Mensaje"
- git remote add origin
- git push -u origin master
- git pull
- git clone
- git status
- git log
- git checkout
- git branch
- git merge
- git reset
- git revert
- git rebase
- git fetch
- git stash
- git tag
- git show
- git diff
- git rm
- git mv
- git ls-files
- git log --oneline
- git log --graph
- git log --decorate
- git log --all
- git log --author="Nombre"
- git log --grep="Mensaje"
- git log --since="2020-01-01"
- git log --until="2020-01-01"
- git log --stat
- git log -p
- git log -p -2
- git log --pretty=format:"%h - %an, %ar : %s"
- git log --graph --oneline --all
- git log --graph --oneline --all --decorate
- git log --graph --oneline --all --decorate --color
- git log --graph --oneline --all --decorate --color --author="Nombre"

- git branch nombre_rama
- git checkout nombre_rama
- git checkout -b nombre_rama
- git branch -d nombre_rama
- git branch -D nombre_rama
*/

struct series_episodes{
    string chapter;
    string name;
    string duration;
    series_episodes *next;
};

struct series_seasons{
    string season;
    string number_of_chapters;
    series_seasons *next;
    series_episodes *down;
};

struct series{
    string id;
    string name;
    string genre;
    string year;
    series *next;
    series_seasons *down;
};

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

void show_series_episodes(series_episodes *inicio){
    series_episodes *aux = inicio;
    while(aux != NULL){
        cout << "Capitulo: " << aux->chapter << endl;
        cout << "Nombre: " << aux->name << endl;
        cout << "Duracion: " << aux->duration << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
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
    if(mail.empty()){
        cout << "El correo no puede estar vacio." << endl;
        return false;
    }
    else if(count(mail.begin(), mail.end(), '@') > 1 && !mail.empty()){
        cout << "El correo solo debe contener un '@'." << endl;
        return false;
    }
    return true;
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

//Agregar usuarios
void add_new_user(user *&inicio, user *&fin){
    user *nuevo = new user;
    cout << "Agregando usuario..." << endl;
    cout << "ID: ";
    cin.ignore();
    getline(cin, nuevo->id);
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
    while(!validate_format_mail_user(nuevo->mail)){
        cout << "Mail: ";
        getline(cin, nuevo->mail);
    }
    cout << "Mail valido." << endl;
    cout << "Password: ";
    cin >> nuevo->password;
    cout << "Pais: ";
    cin >> nuevo->country;
    nuevo->next = NULL;
    if(inicio == NULL){
        inicio = nuevo;
        fin = nuevo;
    }else{
        fin->next = nuevo;
        fin = nuevo;
    }
}

//Agregar series
void add_new_serie(series *&begin, series *&end){
    series *newS = new series;
    cout << "Agregando serie..." << endl;
    cout << "ID: ";
    cin.ignore();
    getline(cin, newS->id);
    cout << "Nombre: ";
    cin >> newS->name;
    cout << "Genero: ";
    cin >> newS->genre;
    cout << "Año: ";
    cin >> newS->year;
    newS->next = NULL;
    newS->down = NULL;
    if(begin == NULL){
        begin = newS;
        end = newS;
    }else{
        end->next = newS;
        end = newS;
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

//Mostrar series
void show_series(series *begin){
    series *aux = begin;
    while(aux != NULL){
        cout << "ID: " << aux->id << endl;
        cout << "Nombre: " << aux->name << endl;
        cout << "Genero: " << aux->genre << endl;
        cout << "Año: " << aux->year << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
}

//Eliminar series
void delete_serie(series *&begin, series *&end){
    string id;
    cout << "ID de la serie a eliminar: ";
    cin >> id;
    series *aux = begin;
    series *aux2 = NULL;
    while(aux != NULL && aux->id != id){
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No se encontro la serie" << endl;
    }else if(aux == begin){
        cout << "Eliminando serie..." << endl;
        begin = begin->next;
        delete aux;
        cout << "Serie eliminada" << endl;
    }else{
        aux2->next = aux->next;
        cout << "Eliminando serie..." << endl;
        delete aux;
        cout << "Serie eliminada" << endl;
    }
}

//Agregar temporadas
void add_new_seasons(series_seasons *&begin, series_seasons *&end, series *aux_series){
    series_seasons *new_season = new series_seasons;
    string id_serie;
    cout << "Agregando temporada..." << endl;
    cout << "ID de la serie: ";
    cin.ignore();
    getline(cin, id_serie);
    while(aux_series != NULL && aux_series->id != id_serie){
        aux_series = aux_series->next;
    }
    if(aux_series == NULL){
        cout << "No se encontro la serie" << endl;
        return;
    }
    cout << "Temporada: ";
    cin.ignore();
    getline(cin, new_season->season);
    cout << "Numero de capitulos: ";
    cin >> new_season->number_of_chapters;
    new_season->next = NULL;
    new_season->down = NULL;
    if(begin == NULL){
        begin = new_season;
        end = new_season;
    }else{
        end->next = new_season->next;
        end = new_season;
    }
}

//Mostar temporadas
void show_seasons(series_seasons *begin){
    series_seasons *aux = begin;
    while(aux != NULL){
        cout << "Temporada: " << aux->season << endl;
        cout << "Numero de capitulos: " << aux->number_of_chapters << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
}

//Eliminar temporadas
void delete_seasons(series_seasons *&begin, series_seasons *&end){
    string season;
    cout << "Temporada a eliminar: ";
    cin >> season;
    series_seasons *aux = begin;
    series_seasons *aux2 = NULL;
    while(aux != NULL && aux->season != season){
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No se encontro la temporada" << endl;
    }else if(aux == begin){
        cout << "Eliminando temporada..." << endl;
        begin = begin->next;
        delete aux;
        cout << "Temporada eliminada" << endl;
    }else{
        aux2->next = aux->next;
        cout << "Eliminando temporada..." << endl;
        delete aux;
        cout << "Temporada eliminada" << endl;
    }
}

//Agregar episodios
void add_new_episodes(series_episodes *&begin, series_episodes *&end){
    series_episodes *newE = new series_episodes;
    cout << "Agregando episodio..." << endl;
    cout << "Capitulo: ";
    cin.ignore();
    getline(cin, newE->chapter);
    cout << "Nombre: ";
    cin >> newE->name;
    cout << "Duracion: ";
    cin >> newE->duration;
    newE->next = NULL;
    if(begin == NULL){
        begin = newE;
        end = newE;
    }else{
        end->next = newE;
        end = newE;
    }
}

//Mostar episodios
void show_episodes(series_episodes *begin){
    series_episodes *aux = begin;
    while(aux != NULL){
        cout << "Capitulo: " << aux->chapter << endl;
        cout << "Nombre: " << aux->name << endl;
        cout << "Duracion: " << aux->duration << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
}

//Eliminar episodios
void delete_episodes(series_episodes *&begin, series_episodes *&end){
    string chapter;
    cout << "Capitulo a eliminar: ";
    cin >> chapter;
    series_episodes *aux = begin;
    series_episodes *aux2 = NULL;
    while(aux != NULL && aux->chapter != chapter){
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No se encontro el capitulo" << endl;
    }else if(aux == begin){
        cout << "Eliminando capitulo..." << endl;
        begin = begin->next;
        delete aux;
        cout << "Capitulo eliminado" << endl;
    }else{
        aux2->next = aux->next;
        cout << "Eliminando capitulo..." << endl;
        delete aux;
        cout << "Capitulo eliminado" << endl;
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
void read_file_users(user *&begin){
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
            enter();
            continue;
        }
        else if(!validate_id_user(id, begin)){
            cout << "Error archivo usuarios: El ID de usuario '" << id << "' no se ha cargado porque el ID ya existe.\n";
            enter();
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
        new_user->country = country;
        new_user->next = NULL;
        if(begin == NULL){
            begin = new_user;
        }
        else{
            user *aux = begin;
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux->next = new_user;
        }
    }
    file_users.close();
}


//Excepci[on caso 5 cuando estan vacias las listas y caso 6]

//Nombre año y genero
//Nombre, año, genero

int main(){
    user *begin_user = NULL;
    user *end_user = NULL;
    user *new_user = NULL;
    user *aux_user = NULL;
    user *aux2_user = NULL;
    series *new_series = NULL;
    series *begin_series = NULL;
    series *end_series = NULL;
    series *aux_series = NULL;
    series *aux2_series = NULL;
    series_seasons *new_seasons = NULL;
    series_seasons *aux_seasons = NULL;
    series_seasons *aux2_seasons = NULL;
    series_episodes *new_episodes = NULL;
    series_episodes *aux_episodes = NULL;
    series_episodes *aux2_episodes = NULL;
    string id, name, username, password, mail, age, genre, year, season, number_of_chapters, chapter, duration;
    int opcion = 0;
    read_file_users(begin_user);
    do{
        cout << "1. Agregar usuario" << endl;
        cout << "2. Mostrar usuarios" << endl;
        cout << "3. Eliminar usuario" << endl;
        cout << "4. Agregar serie" << endl;
        cout << "5. Mostrar series" << endl;
        cout << "6. Eliminar serie" << endl;
        cout << "7. Agregar temporada" << endl;
        cout << "8. Mostrar temporadas" << endl;
        cout << "9. Eliminar temporada" << endl;
        cout << "10. Agregar episodio" << endl;
        cout << "11. Mostrar episodios" << endl;
        cout << "12. Eliminar episodio" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 0:
                cout << "Saliendo..." << endl;
                save_users(begin_user);
                show_file_path("usuarios.txt");
                break;
            case 1:
                add_new_user(begin_user, end_user);
                break;
            case 2:
                show_users(begin_user);
                enter();
                break;
            case 3:
                show_users(begin_user);
                delete_user(begin_user, end_user);
                enter();
                break;
            case 4:
                add_new_serie(begin_series, end_series);
                break;
            case 5:
                show_series(begin_series);
                enter();
                break;
            case 6:
                show_series(begin_series);
                delete_serie(begin_series, end_series);
                break;
            case 7:
                new_seasons = NULL;
                add_new_seasons(begin_series->down, new_seasons, begin_series);
                break;
            case 8:
                show_seasons(aux_series->down);
                break;
            case 9:
                show_seasons(aux_series->down);
                delete_seasons(aux_series->down, aux_seasons->next);
                break;
            case 10:
                add_new_episodes(aux_seasons->down, aux_episodes->next);
                break;
            case 11:
                show_episodes(aux_seasons->down);
                break;
            case 12:
                show_episodes(aux_seasons->down);
                delete_episodes(aux_seasons->down, aux_episodes->next);
                break;
        }
    }while(opcion != 0);
    return 0;
}
