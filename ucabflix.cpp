#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "users.h"
#include "series2.h"
#include "movies.h"
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


//Excepci[on caso 5 cuando estan vacias las listas y caso 6]

//Nombre año y genero
//Nombre, año, genero

int main(){
    user *begin_user = NULL;
    user *end_user = NULL;
    movies *begin_movie = NULL;
    movies *end_movie = NULL;
    series *begin_series = NULL;
    series *end_series = NULL;
    series_seasons *new_seasons = NULL;
    series_seasons *aux_seasons = NULL;
    series_episodes *aux_episodes = NULL;
    series *aux_series = NULL;
    int opcion = 0;
    read_file_users(begin_user, end_user);
    read_file_movies(begin_movie, end_movie);
    read_file_series(begin_series, end_series);
    read_file_seasons(begin_series);
    if(begin_series != NULL){
        aux_series = begin_series;
    }
    do{
        cout << "UCABFLIX" << endl;
        cout << "1. Agregar usuario" << endl;
        cout << "2. Mostrar usuarios" << endl;
        cout << "3. Eliminar usuario" << endl;
        cout << "4. Agregar pelicula" << endl;
        cout << "5. Mostrar peliculas" << endl;
        cout << "6. Eliminar pelicula" << endl;
        cout << "7. Agregar serie" << endl;
        cout << "8. Mostrar series" << endl;
        cout << "9. Eliminar serie" << endl;
        cout << "10. Agregar temporada" << endl;
        cout << "11. Mostrar temporadas" << endl;
        cout << "12. Eliminar temporada" << endl;
        cout << "13. Agregar episodio" << endl;
        cout << "14. Mostrar episodios" << endl;
        cout << "15. Eliminar episodio" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 0:
                cout << "Saliendo..." << endl;
                save_users(begin_user);
                show_file_path("usuarios.txt");
                save_movies(begin_movie);
                show_file_path("movies.txt");
                save_series(begin_series);
                show_file_path("series.txt");
                save_seasons(begin_series);
                show_file_path("temporadas.txt");
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
                add_new_movie(begin_movie, end_movie);
                break;
            case 5:
                show_movies(begin_movie);
                enter();
                break;
            case 6:
                show_movies(begin_movie);
                delete_movie(begin_movie, end_movie);
                break;
            case 7:
                add_new_serie(begin_series, end_series);
                break;
            case 8:
                show_series(begin_series);
                enter();
                break;
            case 9:
                show_series(begin_series);
                delete_serie(begin_series, end_series);
                break;
            case 10:
                show_series(begin_series);
                add_new_season(begin_series);
                break;
            case 11:
                show_series(begin_series);
                show_seasons(begin_series);
                enter();
                break;
        }
    }while(opcion != 0);
    return 0;
}
