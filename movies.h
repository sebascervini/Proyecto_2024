#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct movies{
    string id_movie;
    string name_movie;
    string genre_movie;
    string year_movie;
    string duration_movie;
    movies *next;
};

//Validar que la pelicula exista
bool validate_movie(string id_movie, movies *begin){
    movies *aux = begin;
    cout << "Validando pelicula..." << endl;
    while(aux != NULL){
        if(aux->id_movie == id_movie){
            return true;
        }
        aux = aux->next;
    }
    if(aux == NULL){
        return false;
    }
    return false;
}

//Validar que dos peliculas no tengan el mismo ID
bool validate_movie_id(string id_movie, movies *begin){
    movies *aux = begin;
    cout << "Validando pelicula..." << endl;
    if(id_movie.empty()){
        cout << "El ID no puede estar vacio." << endl;
        return false;
    }
    else if(aux != NULL){
        while(aux != NULL){
            if(aux->id_movie == id_movie){
                cout << "El ID ya existe." << endl;
                return false;
            }
            aux = aux->next;
        }
    }
    else if(aux == NULL){
        cout << "El ID no existe." << endl;
        return true;
    }
    return false;
}

//Validar que no haya peliculas repetidas
bool validate_movie_name(string name_movie, movies *begin){
    movies *aux = begin;
    cout << "Validando pelicula..." << endl;
    if(name_movie.empty()){
        cout << "El nombre no puede estar vacio." << endl;
        return false;
    }
    else if(aux != NULL){
        while(aux != NULL){
            if(aux->name_movie == name_movie){
                cout << "La pelicula ya existe." << endl;
                return false;
            }
            aux = aux->next;
        }
    }
    else if(aux == NULL){
        cout << "La pelicula no existe." << endl;
        return true;
    }
    return false;
}

//Agregar pelicula
void add_new_movie(movies *&begin, movies *&end){
    movies *new_movie = new movies;
    cout << "Agregando pelicula..." << endl;
    cout << "ID: ";
    cin.ignore();
    getline(cin, new_movie->id_movie);
    cout << "Nombre: ";
    getline(cin, new_movie->name_movie);
    cout << "Genero: ";
    getline(cin, new_movie->genre_movie);
    cout << "Año: ";
    getline(cin, new_movie->year_movie);
    cout << "Duracion: ";
    getline(cin, new_movie->duration_movie);
    new_movie->next = NULL;
    if(begin == NULL){
        begin = new_movie;
        end = new_movie;
    }else{
        end->next = new_movie;
        end = new_movie;
    }
}

//Mostrar peliculas
void show_movies(movies *begin){
    movies *aux = begin;
    while(aux != NULL){
        cout << "ID: " << aux->id_movie << endl;
        cout << "Nombre: " << aux->name_movie << endl;
        cout << "Genero: " << aux->genre_movie << endl;
        cout << "Año: " << aux->year_movie << endl;
        cout << "Duracion: " << aux->duration_movie << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
}

//Eliminar pelicula
void delete_movie(movies *&begin, movies *&end){
    movies *aux = begin;
    movies *aux2 = NULL;
    movies *aux3 = NULL;
    string id_movie;
    cout << "ID de la pelicula a eliminar: ";
    getline(cin, id_movie);
    while(!validate_movie(id_movie, begin)){
        cout << "El ID ingresado no existe." << endl;
        cout << "ID de la pelicula a eliminar: ";
        getline(cin, id_movie);
    }
    while(aux != NULL && aux->id_movie != id_movie){
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No se encontro la pelicula" << endl;
    }
    else if(aux == begin){
        cout << "Eliminando pelicula..." << endl;
        begin = begin->next;
        delete aux;
        cout << "Pelicula eliminada" << endl;
    }
    else if(aux == end){
        cout << "Eliminando pelicula..." << endl;
        aux2->next = NULL;
        end = aux2;
        delete aux;
        cout << "Pelicula eliminada" << endl;
    }
    else{
        cout << "Eliminando pelicula..." << endl;
        aux2->next = aux->next;
        delete aux;
        cout << "Pelicula eliminada" << endl;
    }
}

//Guardar peliculas
void save_movies(movies *begin){
    movies *aux = begin;
    const char delimiter = '|';
    ofstream file("C:/Users/sebas/Documents/peliculas.txt");
    while(aux != NULL){
        file << aux->id_movie << delimiter;
        file << aux->name_movie << delimiter;
        file << aux->genre_movie << delimiter;
        file << aux->year_movie << delimiter;
        file << aux->duration_movie << '\n';
        aux = aux->next;
    }
    file.close();
}

//Leer peliculas
void read_file_movies(movies *&begin, movies *&end){
    movies *new_movie = new movies;
    const char delimiter = '|';
    ifstream file("C:/Users/sebas/Documents/peliculas.txt");
    string line, id_movie, name_movie, genre_movie, year_movie, duration_movie;
    while(getline(file, line)){
        stringstream stream(line);
        getline(stream, id_movie, delimiter);
        if(id_movie.empty()){
            cout << "La pelicula con el ID " << id_movie << " no tiene ID." << endl;
            continue;
        }
        else if(!id_movie.empty() && !validate_movie_id(id_movie, begin)){
            cout << "La pelicula con el ID " << id_movie << " ya existe." << endl;
            continue;
        }
        else if(validate_movie(id_movie, begin)){
            cout << "La pelicula con el ID " << id_movie << " ya existe." << endl;
            continue;
        }
        getline(stream, name_movie, delimiter);
        if(name_movie.empty()){
            cout << "La pelicula con el nombre " << name_movie << " no tiene un nombre valido." << endl;
            continue;
        }
        else if(!validate_movie_name(name_movie, begin)){
            cout << "La pelicula con el nombre " << name_movie << " ya existe." << endl;
            continue;
        }
        getline(stream, genre_movie, delimiter);
        getline(stream, year_movie, delimiter);
        getline(stream, duration_movie, delimiter);
        new_movie->id_movie = id_movie;
        new_movie->name_movie = name_movie;
        new_movie->genre_movie = genre_movie;
        new_movie->year_movie = year_movie;
        new_movie->duration_movie = duration_movie;
        new_movie->next = NULL;
        if(begin == NULL){
            begin = new_movie;
            end = new_movie;
        }else{
            end->next = new_movie;
            end = new_movie;
        }
    }
    file.close();
}