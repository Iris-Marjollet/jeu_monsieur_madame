#pragma once
#include "Ingredient.h"
#include <vector>
#include <map>
#include "Ingredient.h"
#include "Preparation.h"

using namespace std;

class Pizza {
private :
    int id;
    std::map< Ingredient, shared_ptr<bool>> ingredients;
    bool completed;
    sf::CircleShape dough;
    sf::CircleShape sauce;
    sf::CircleShape melted_cheese;
    vector<sf::CircleShape> pepperonis;
public:
    explicit Pizza(const std::vector< Ingredient>& ingr);
    std::vector<Preparation> getPreparations();
    friend std::ostream& operator<<(std::ostream& os, const Pizza& pizza);
    int addIngredient(Ingredient ingredient);
    void setDough(float screenWidth, sf::Vector2f circlePosition, float xVelocity, sf::Vector2f saucePosition, const sf::Texture& cooked_cheese, bool tomato, bool cheese, bool pepperoni);
    sf::CircleShape getDough();
    sf::CircleShape getSauce();
    sf::CircleShape getCheese();
    vector<sf::CircleShape> getPepperoni();
    void addTomato();

    static int id_count;
};

