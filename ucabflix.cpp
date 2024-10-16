#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "users.h"
#include "series.h"
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
