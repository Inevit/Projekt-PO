#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

class Single_Area
{
protected:

    bool obstacle; // zmienna logiczna przechowujaca przeszkode
    bool small_food; // zmienna logiczna przechowujaca male jedzenie
    bool big_food; // zmienna logiczna przechowujaca duze jedzenie
    bool poison; // zmienna logiczna przechowujaca trucizne
    bool accelerate; // zmienna logiczna przyspieszajaca ruch weza
    bool slow_down; // zmienna logiczna spowalniajaca ruch weza
    bool band; // zmienna logiczna okreslajaca czy jest banda
    bool head; // zmienna logiczna przypisujaca wartosc logiczna czy na danym polu jest glowa weza
    friend class Area_and_Snake;
    friend class Game;
    friend int main();

public:

    Single_Area()
    {
        obstacle = false;
        small_food = false;
        big_food = false;
        poison = false;
        accelerate = false;
        slow_down = false;
        band = false;
        head = false;
    }

    void place_obstacle()
    {
        obstacle = true;
    }

    void place_small_food()
    {
        small_food = true;
    }

    void place_big_food()
    {
        big_food = true;
    }

    void place_poison()
    {
        poison = true;
    }

    void place_band()
    {
        band = true;
    }

    bool whether_obstacle()
    {
        if(obstacle) return true;
        return false;
    }

    bool whether_small_food()
    {
        return small_food;
    }

    bool whether_big_food()
    {
        return big_food;
    }

    bool whether_poison()
    {
        return poison;
    }

    void place_head()
    {
        head = true;
    }

    void remove_head()
    {
        head = false;
    }

    void move_small_food()
    {
        small_food = false;
    }

    void move_big_food()
    {
        big_food = false;
    }

    void move_poison()
    {
        poison = false;
    }

    void draw_snake()
    {
        cout << "@";
    }
};

class Area_and_Snake : public Single_Area
{
    Single_Area **T; // utworzenie wskaznika na wskaznik tablicy
    int *tail_x; // sa to utworzone wskazniki, ktore beda dynamicznymi tablicami
    int *tail_y; // przechowujacymi polozenie kazdego elementu ogona weza
    int N;
    int M; // zmienne N, M przechowujace wymiary dynamicznej tablicy dwuwymiarowej
    int x_coordinate; // koordynata X glowy weza
    int y_coordinate; // koordynata Y glowy weza
    int step; // zmienna przechowujaca ile ruchow waz wykonal
    int length; // zmienna przechowujaca dlugosc weza
    friend class Game;

public:

    void draw_borders(); // metoda rysujaca krawedzie
    void set_obstacles(int n, int r); // metoda rozmieszczajaca losowo przeszkody na planszy
    void set_single_food(bool place); // metoda rozmieszczajaca losowo pojedynczy przedmiot do zjedzenia
    void set_extra_items(bool place); // metoda rozmieszczajaca dodatkowe przedmioty do zjedzenia

    Area_and_Snake()
    {
        length = 1;
        step = 0;

        cout << "Jakich wymiarow chcesz, by byla plansza? Podaj ilosc wierszy: ";
        cin >> N;
        cout << "Podaj ilosc kolumn: ";
        cin >> M;

        T = new Single_Area *[N]; // dynamiczne utworzenie wierszy tablicy

        for(int i = 0; i < N; i++) // dynamiczne utworzenie kolumn tablicy
        {
            T[i] = new Single_Area [M];
        }

        tail_x = new int [N*M];
        tail_y = new int [N*M]; // alokacja dwoch tablic dla przechowywania polozenia ogona weza

        x_coordinate = N/2;
        y_coordinate = M/2;
        T[x_coordinate][y_coordinate].place_head();
    }

    ~Area_and_Snake()
    {
        for(int i = 0; i < N; i++)
        {
            delete [] T[i];
        }

        delete [] T;
        delete [] tail_x;
        delete [] tail_y;
        T = NULL;
        tail_x = NULL;
        tail_y = NULL; // od teraz tablice za zdealokowane i wskazuja nigdzie
    }

    void set_small_food()
    {
        int n, m;
        srand(time(NULL));
        n = 1 + rand()%(N - 2 - 1 + 1); // losowanie liczby z przedzialu [1, N - 2] dla wiersza
        m = 1 + rand()%(M - 2 - 1 + 1); // losowanie liczby z przedzialu [1, M - 2] dla kolumny

        T[n][m].place_small_food();
    }

    void set_big_food()
    {
        int n, m;
        n = 1 + rand()%(N - 2 - 1 + 1); // losowanie liczby z przedzialu [1, N - 2] dla wiersza
        m = 1 + rand()%(M - 2 - 1 + 1); // losowanie liczby z przedzialu [1, M - 2] dla kolumny

        T[n][m].place_big_food();
    }

    void create_borders()
    {
        for (int i = 0; i < N; i++)
        {
            T[i][0].place_band();
            T[i][M - 1].place_band();
        }
        for (int i = 1; i < M; i++)
        {
            T[0][i].place_band();
            T[N - 1][i].place_band();
        }
    }

    void set_obstacles()
    {
        int n, m, p = 10;

        srand(time(NULL));

        for(int k = 0; k < p; k++)
        {
            n = 1 + rand()%(N - 2 - 1 + 1); // losowanie liczby z przedzialu [1, 8] dla wiersza
            m = 1 + rand()%(M - 2 - 1 + 1); // losowanie liczby z przedzialu [1, 19] dla kolumny
            T[n][m].place_obstacle();
        }
    }

    void increase_length()
    {
        length++;
    }

    void display()
    {
        for (int i = 0; i < N; i++)
        {
            cout << endl;
            for (int j = 0; j < M; j++)
            {
                if (T[i][j].band || T[i][j].obstacle) cout << "#";
                else if (T[i][j].small_food) cout << "o";
                else if(T[i][j].head) cout << "@";
                else cout << " ";
            }
        }
    }

    void move_snake(char key)
    {
            key = getch();

        /*step++;
        tail_x[step] = x_coordinate;
        tail_y[step] = y_coordinate;*/

        if(key == UP)
        {
            y_coordinate--;
            T[y_coordinate + length][x_coordinate].head = false;
            T[y_coordinate][x_coordinate].place_head();
        }
        if(key == DOWN)
        {
            y_coordinate++;
            T[y_coordinate - length][x_coordinate].head = false;
            T[y_coordinate][x_coordinate].place_head();
        }
        if(key == RIGHT)
        {

            x_coordinate++;
            T[y_coordinate][x_coordinate - length].head = false;
            T[y_coordinate][x_coordinate].place_head();
        }
        if(key == LEFT)
        {
            x_coordinate--;
            T[y_coordinate][x_coordinate + length].head = false;
            T[y_coordinate][x_coordinate].place_head();
        }

        if(T[y_coordinate][x_coordinate].head == T[y_coordinate][x_coordinate].small_food)
        {
            T[y_coordinate][x_coordinate].small_food = false;
            increase_length();
            set_small_food();
        }




        //T[tail_x[step]][tail_y[step]].remove_head();
    }
};

class Game
{
    bool defeat; // zmienna logiczna przechowujaca czy gracz przegral
    int n;
    int m; // zmienne pomocnicze n, m przechowujace aktualne pozycje glowy weza
    char key; // zmienna znakowa, ktora przechowuje typ wcisnietego klawisza

public:

    Game()
    {
        defeat = false;
    }

    void play(Area_and_Snake board)
    {

    }
};

main()
{
    Area_and_Snake board;
    char key;

    board.create_borders();
    board.set_small_food();
    board.display();

    while(true)
    {
        Sleep(20);
        board.move_snake(0);
        system("CLS");
        board.display();
    }
}
