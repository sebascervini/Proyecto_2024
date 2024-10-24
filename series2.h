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
    if(id.empty()){
        return false;
    }
    else if(aux != NULL){
        while(aux != NULL){
            if(aux->id == id){
                return true;
            }
            aux = aux->next;
        }
    }
    else if(aux == NULL){
        return false;
    }
    return false;
}

//Agregar series
void add_new_serie(series *&begin, series *&end){
    series *new_serie = new series;
    cout << "Agregando serie..." << endl;
    cout << "ID: ";
    cin.ignore();
    getline(cin, new_serie->id);
    cout << "Nombre: ";
    getline(cin, new_serie->name);
    cout << "Genero: ";
    getline(cin, new_serie->genre);
    cout << "Año: ";
    getline(cin, new_serie->year);
    new_serie->next = NULL;
    new_serie->down = NULL;
    if(begin == NULL){
        begin = new_serie;
        end = new_serie;
    }else{
        end->next = new_serie;
        end = new_serie;
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
    if(aux == NULL && begin == NULL){
        cout << "No hay series registradas." << endl;
    }
}

//Eliminar series
void delete_serie(series *&begin, series *&end){
    series *aux = begin;
    series *aux2 = NULL;
    string id_serie;
    cout << "ID de la serie a eliminar: ";
    cin.ignore();
    getline(cin, id_serie);
    while(aux != NULL && aux->id != id_serie){
        aux2 = aux;
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No se encontro la serie" << endl;
    }
    else if(aux == begin){
        cout << "Eliminando serie..." << endl;
        begin = begin->next;
        delete aux;
        cout << "Serie eliminada" << endl;
    }
    else if(aux == end){
        cout << "Eliminando serie..." << endl;
        aux2->next = NULL;
        end = aux2;
        delete aux;
        cout << "Serie eliminada" << endl;
    }
    else{
        cout << "Eliminando serie..." << endl;
        aux2->next = aux->next;
        delete aux;
        cout << "Serie eliminada" << endl;
    }
}

//Guardar series
void save_series(series *begin){
    series *aux = begin;
    const char delimiter = '|';
    ofstream file("C:/Users/sebas/Documents/series.txt");
    while(aux != NULL){
        file << aux->id << delimiter;
        file << aux->name << delimiter;
        file << aux->genre << delimiter;
        file << aux->year << '\n';
        aux = aux->next;
    }
    if(aux == NULL){
        cout << "No hay series registradas." << endl;
    }
    if(!file.is_open()){
        cout << "Error al abrir el archivo de series." << endl;
        return;
    }
    else{
        cout << "Series guardadas correctamente." << endl;
    }
    file.close();
}

//Leer series
void read_file_series(series *&begin, series *&end){
    ifstream file("C:/Users/sebas/Documents/series.txt");
    string line;
    while(getline(file, line)){
        series *new_serie = new series;
        stringstream ss(line);
        getline(ss, new_serie->id, '|');
        getline(ss, new_serie->name, '|');
        getline(ss, new_serie->genre, '|');
        getline(ss, new_serie->year, '|');
        new_serie->next = NULL;
        new_serie->down = NULL;
        if(begin == NULL){
            begin = new_serie;
            end = new_serie;
        }else{
            end->next = new_serie;
            end = new_serie;
        }
    }
    if(!file.is_open()){
        cout << "Error al abrir el archivo de series." << endl;
        return;
    }
    else{
        cout << "Series cargadas correctamente." << endl;
    }
    file.close();
}

//Agregar temporadas
void add_new_season(series *begin_series){
    series_seasons *new_season = new series_seasons;
    series *aux_series = begin_series;
    string id_serie;
    if(aux_series == NULL){
        cout << "No hay series registradas." << endl;
        return;
    }
    cout << "ID de la serie: ";
    cin.ignore();
    getline(cin, id_serie);
    while(aux_series != NULL){
        if(aux_series->id == id_serie){
            cout << "Agregando temporada..." << endl;
            cout << "Numero de temporada: ";
            getline(cin, new_season->season);
            cout << "Numero de capitulos: ";
            getline(cin, new_season->number_of_chapters);
            new_season->next = NULL;
            new_season->down = NULL;
            if(aux_series->down == NULL){
                aux_series->down = new_season;
            }else{
                series_seasons *aux_seasons = aux_series->down;
                while(aux_seasons->next != NULL){
                    aux_seasons = aux_seasons->next;
                }
                aux_seasons->next = new_season;
            }
            return;
        }
        aux_series = aux_series->next;
    }
    cout << "La serie no existe." << endl;
}

//Mostrar temporadas
void show_seasons(series *begin_series){
    series *aux_series = begin_series;
    string id_serie;
    if(aux_series == NULL){
        cout << "No hay series registradas." << endl;
        return;
    }
    cout << "ID de la serie: ";
    cin.ignore();
    getline(cin, id_serie);
    while(aux_series != NULL){
        if(aux_series->id == id_serie){
            series_seasons *aux_seasons = aux_series->down;
            if(aux_seasons == NULL){
                cout << "No hay temporadas registradas para esta serie." << endl;
                return;
            }
            while(aux_seasons != NULL){
                cout << "Temporada: " << aux_seasons->season << endl;
                cout << "Numero de capitulos: " << aux_seasons->number_of_chapters << endl;
                cout << "----------------------" << endl;
                aux_seasons = aux_seasons->next;
            }
            return;
        }
        aux_series = aux_series->next;
    }
    cout << "La serie no existe." << endl;
}

//Eliminar temporadas
void delete_season(series *begin_series){
    series *aux_series = begin_series;
    string id_serie;
    if(aux_series == NULL){
        cout << "No hay series registradas." << endl;
        return;
    }
    cout << "ID de la serie: ";
    cin.ignore();
    getline(cin, id_serie);
    while(aux_series != NULL){
        if(aux_series->id == id_serie){
            series_seasons *aux_seasons = aux_series->down;
            series_seasons *aux2 = NULL;
            string season;
            cout << "Temporada a eliminar: ";
            getline(cin, season);
            while(aux_seasons != NULL){
                if(aux_seasons->season == season){
                    if(aux_seasons == aux_series->down){
                        aux_series->down = aux_series->down->next;
                        delete aux_seasons;
                        cout << "Temporada eliminada." << endl;
                        return;
                    }
                    else{
                        aux2->next = aux_seasons->next;
                        delete aux_seasons;
                        cout << "Temporada eliminada." << endl;
                        return;
                    }
                }
                aux2 = aux_seasons;
                aux_seasons = aux_seasons->next;
            }
            cout << "La temporada no existe." << endl;
            return;
        }
        aux_series = aux_series->next;
    }
    cout << "La serie no existe." << endl;
}

//Guardar temporadas
void save_seasons(series *begin_series){
    series *aux_series = begin_series;
    const char delimiter = '|';
    ofstream file("C:/Users/sebas/Documents/temporadas.txt");
    if(!file.is_open()){
        cout << "Error al abrir el archivo de temporadas." << endl;
        return;
    }
    while(aux_series != NULL){
        series_seasons *aux_seasons = aux_series->down;
        while(aux_seasons != NULL){
            file << aux_series->id << delimiter;
            file << aux_seasons->season << delimiter;
            file << aux_seasons->number_of_chapters << '\n';
            aux_seasons = aux_seasons->next;
        }
        aux_series = aux_series->next;
    }
    cout << "Temporadas guardadas correctamente." << endl;
    file.close();
}

//Leer temporadas
void read_file_seasons(series *&begin_series){
    ifstream file("C:/Users/sebas/Documents/temporadas.txt");
    string line;
    while(getline(file, line)){
        string serie_id;
        series_seasons *new_season = new series_seasons;
        stringstream ss(line);
        getline(ss, serie_id, '|');
        getline(ss, new_season->season, '|');
        getline(ss, new_season->number_of_chapters, '|');
        new_season->next = NULL;
        new_season->down = NULL;

        series *aux_series = begin_series;
        while(aux_series != NULL){
            if(aux_series->id == serie_id){
                if(aux_series->down == NULL){
                    aux_series->down = new_season;
                }else{
                    series_seasons *aux_seasons = aux_series->down;
                    while(aux_seasons->next != NULL){
                        aux_seasons = aux_seasons->next;
                    }
                    aux_seasons->next = new_season;
                }
                break;
            }
            aux_series = aux_series->next;
        }
    }
    if(!file.is_open()){
        cout << "Error al abrir el archivo de temporadas." << endl;
        return;
    }
    else{
        cout << "Temporadas cargadas correctamente." << endl;
    }
    file.close();
}
