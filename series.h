#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

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

//Validar que la serie exista
bool validate_serie(string id, series *begin){
    series *aux = begin;
    cout << "Validando serie..." << endl;
    if(id.empty()){
        cout << "El ID no puede estar vacio." << endl;
        return false;
    }
    else if(aux != NULL){
        while(aux != NULL){
            if(aux->id == id){
                cout << "La serie existe." << endl;
                return true;
            }
            aux = aux->next;
        }
    }
    else if(aux == NULL){
        cout << "La serie no existe." << endl;
        return false;
    }
    return false;
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
    while(aux_series != NULL && !validate_serie(id_serie, aux_series)){
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
void add_new_episodes(series_episodes *&begin, series_episodes *&end, series *series_begin, series_seasons *seasons_begin){
    series_episodes *newE = new series_episodes;
    series *aux_series = series_begin;
    series_seasons *aux_season = seasons_begin;
    string id_serie, season;
    cout << "Agregando episodio..." << endl;
    cout << "ID de la serie: ";
    cin.ignore();
    getline(cin, id_serie);
    while(aux_series != NULL && !validate_serie(id_serie, series_begin)){
        aux_series = aux_series->next;
    }
    if (aux_series == NULL){
        cout << "No se encontro la serie" << endl;
        return;
    }
    aux_season = aux_series->down;
    cout << "Temporada: ";
    cin.ignore();
    getline(cin, season);
    while(aux_season != NULL && aux_season->season != season){
        aux_season = aux_season->next;
    }
    if(aux_season == NULL){
        cout << "No se encontro la temporada" << endl;
        return;
    }
    cout << "Capitulo: ";
    cin.ignore();
    getline(cin, newE->chapter);
    cout << "Nombre: ";
    getline(cin, newE->name);
    cout << "Duracion: ";
    getline(cin, newE->duration);
    newE->next = NULL;
    if(!aux_season->down){
        aux_season->down = newE;
    }else{
        series_episodes *aux_episode = aux_season->down;
        while(aux_episode->next != NULL){
            aux_episode = aux_episode->next;
        }
        aux_episode->next = newE;
    }
}

//Mostar episodios
void show_episodes(series_episodes *begin, series *begin_series, series_seasons *begin_seasons){
    series_episodes *aux = begin;
    series *aux_series = begin_series;
    series_seasons *aux_seasons = begin_seasons;
    while(aux_series != NULL && !validate_serie(aux_series->id, begin_series)){
        aux_series = aux_series->next;
    }
    if(aux_series == NULL){
        cout << "No se encontro la serie" << endl;
        return;
    }
    while(aux != NULL){
        cout << "Capitulo: " << aux->chapter << endl;
        cout << "Nombre: " << aux->name << endl;
        cout << "Duracion: " << aux->duration << endl;
        cout << "----------------------" << endl;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No hay episodios registrados en esta temporada." << endl;
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
