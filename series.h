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
    getline(cin, newE->duration);
    newE->next = NULL;
    if(!begin){
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
