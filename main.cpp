#include <iostream>

using namespace std;

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

public:

    Field(bool, bool, bool, bool, bool, bool, bool)
    {
        obstacle = false;
        small_food = false;
        big_food = false;
        poison = false;
        accelerate = false;
        slow_down = false;
        band = true;
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

    void place_accelerate()
    {
        accelerate = true;
    }

    void place_slow_down()
    {
        slow_down = true;
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

    bool whether_accelerate()
    {
        return accelerate;
    }

    bool whether_slow_down()
    {
        return slow_down;
    }
};

class area : protected Single_Area
{
    T[10][20]; // klasa area jest to klasa, ktora reprezentuje klase pojedynczego pola
               // w tablicy dwuwymiarowej
public:

    Board();
    void draw_borders(); // metoda rysujaca krawedzie
    void set_obstacles(int n, int r); // metoda rozmieszczajaca losowo przeszkody na planszy
    void set_single_food(bool place); // metoda rozmieszczajaca losowo pojedynczy przedmiot do zjedzenia
    void set_extra_items(bool place); // metoda rozmieszczajaca dodatkowe przedmioty do zjedzenia

};

main()
{
}
