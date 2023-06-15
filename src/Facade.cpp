#include "Facade.h"
#include <unordered_map>
#include <iostream>

Facade::Facade() {
    // Get the screen resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;

    // Create the SFML window with the screen size
    window.create(sf::VideoMode(screenWidth, screenHeight), "My Program");

    init();
}

void Facade::init(){

    score = 0; //Initialize the score

    //Create the ingredients
    Ingredient tomatoe("tomatoe");
    Ingredient cheese("cheese");
    Ingredient pepperoni("pepperoni");
    //Ingredients are all at the state "not added";
    Ingr tom = {tomatoe, false};
    Ingr che = {cheese, false};
    Ingr pep = {pepperoni, false};
    //ingredients is a map of the ingredients
    ingredients.insert(std::make_pair("tomatoe", tom));
    ingredients.insert(std::make_pair("cheese", che));
    ingredients.insert(std::make_pair("pepperoni", pep));

    //Create a pizza
    std::vector<Ingredient> pizzaIngredients = {tomatoe, cheese, pepperoni};
    Pizza pizza(pizzaIngredients);
    pizzas.push_back(pizza);

    //Fill preparations and storages
    int i = 0;
    for (const auto &ingredient: ingredients){
        Storage storage(ingredient.second.ingredient);
        Preparation preparation1(ingredient.second.ingredient, 1);
        Preparation preparation2(ingredient.second.ingredient, 2);
        storages.push_back(storage);
        preparations.push_back(preparation1);
        preparations.push_back(preparation2);
    }

    draw_init();

}

void Facade::draw_init() {
    //movement
    float xVelocity = 3;
    // Get the screen resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;

    window.setFramerateLimit(60);
    sf::Vector2u windowSize = window.getSize();

    //Set up the score
    sf::Font font;
    if (!font.loadFromFile("resources/font.ttf")) {
        cout << "ERROR FONT DIDN'T LOAD";
    }
    sf::Text scoreText;
    sf::RectangleShape score_board;
    score_board.setSize(sf::Vector2f (400,100));
    score_board.setPosition(20,20);
    score_board.setFillColor(sf::Color::Black);
    score_board.setOutlineColor(sf::Color::White);
    score_board.setOutlineThickness(3);

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(40, 30);
    scoreText.setString("Your Score: " + std::to_string(score));

    //Set up the background
    sf::Texture background = loadTextureFromFile("resources/bois1.jpg");
    sf::Sprite sprite_background;
    sprite_background.setTexture(background);
    // Calculate the scale factors to fill the window
    float scaleX = static_cast<float>(window.getSize().x) / background.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / background.getSize().y;
    // Set the scale of the sprite to fill the window
    sprite_background.setScale(scaleX, scaleY);

    float scaleFactorJar = 0.9f*screenWidth/2500;

    //create the cheese jar
    sf::Texture cheese_jar = loadTextureFromFile("resources/storage_cheese.png");
    float positionCheese = 3.0f;
    //create the tomatoe jar
    sf::Texture tomatoe_jar = loadTextureFromFile("resources/storage_tomatoe.png");
    float positionTomatoe = 1.5f;
    //create the pepperoni jar
    sf::Texture pepperoni_jar = loadTextureFromFile("resources/storage_pepperoni.png");
    float positionPepperoni = 0;

    //Set up the storages
    sf::Sprite spriteTomatoe;
    sf::Sprite spriteCheese;
    sf::Sprite spritePepperoni;
    for(Storage& storage : storages) {
        if(storage.getIngredient().getlabel() == "tomatoe") {
            storage.setSprite(tomatoe_jar, scaleFactorJar, positionTomatoe, screenWidth, sprite_background, 0.0, 0.0);
            spriteTomatoe = storage.getSprite();
            cout << spriteTomatoe.getTextureRect().height << std::endl;
        }
        else if (storage.getIngredient().getlabel() == "cheese") {
            storage.setSprite(cheese_jar, scaleFactorJar, positionCheese, screenWidth, sprite_background, 0.0, 0.0);
            spriteCheese = storage.getSprite();
        }
        else if (storage.getIngredient().getlabel() == "pepperoni") {
            storage.setSprite(pepperoni_jar, scaleFactorJar, positionPepperoni, screenWidth, sprite_background, 0.0, 0.0);
            spritePepperoni = storage.getSprite();
        }
    }

    //create a pot
    sf::Texture pot = loadTextureFromFile("resources/pot.png");
    float scaleFactorPot = 0.2f*screenWidth/2500;
    float potLine = 20 + 1.2f * spriteTomatoe.getTextureRect().height*scaleFactorJar;
    //create a cutting board
    sf::Texture cut = loadTextureFromFile("resources/cutting_board.png");
    //create a grater
    sf::Texture grater = loadTextureFromFile("resources/grater.png");
    float scaleFactorGrater = 0.1f*screenWidth/2500;


    //Set up the preparations
    for(Preparation& preparation : preparations) {
        if(preparation.getIngredient().getlabel() == "tomatoe") {
            preparation.setSprite(pot, scaleFactorPot, positionTomatoe, screenWidth, spriteTomatoe, scaleFactorJar, potLine);
        }
        else if (preparation.getIngredient().getlabel() == "cheese") {
            cout << "Position cheese" << positionCheese << endl;
            preparation.setSprite(grater, scaleFactorGrater, positionCheese+1.5, screenWidth, spriteCheese, scaleFactorJar, potLine);
        }
        else if (preparation.getIngredient().getlabel() == "pepperoni") {
            preparation.setSprite(cut, scaleFactorPot, positionPepperoni, screenWidth, spritePepperoni, scaleFactorJar, potLine);
        }
    }


    //create a PIZZA
    //dough
    sf::CircleShape pizzaShape;
    sf::Vector2f circlePosition(0,5*screenHeight/10);
    //sauce
    sf::Vector2f saucePosition(200*screenWidth/2500-170*screenWidth/2500,5*screenHeight/10+200*screenWidth/2500-170*screenWidth/2500);
    //texture
    sf::Texture cooked_cheese = loadTextureFromFile("resources/cooked-cheese.png");
    pizzas[0].setDough(screenWidth, circlePosition, xVelocity, saucePosition,cooked_cheese, ingredients.at("tomatoe").added, ingredients.at("cheese").added, ingredients.at("pepperoni").added);

    //The game starts running
    bool isTouched = false; //to test if no object was touched
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();


            else if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    // Check for storage click
                    for (Storage &storage: storages) {
                        if (storage.getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            selected.emplace(storage);
                            selected_type = "storage";
                            isTouched = true;
                            break; // Exit the loop if a storage is clicked
                        }
                    }

                    for (Preparation &preparation: preparations) {
                        if (preparation.getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            cout << "WE ARE PREPARING ";
                            cout << preparation.getIngredient() << endl;
                            pizzas[0].getDough().setFillColor(sf::Color::Green);  //TO BE REMOVED
                            startCooking(preparation);
                            isTouched = true;
                            break; // Exit the loop if a preparation is clicked
                        }
                    }

                    for (Pizza &pizza: pizzas){
                        if (pizza.getDough().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            cout << "!!DOUGH HIT !!"<< endl;
                            int res = addIngredient(pizza);
                            score += res;
                        }
                        //if (pizza.getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
                    }

                    if (!isTouched){
                        selected.reset();
                        selected_type = "nothing";
                        cout << "!!!touched the back !!!: " << endl;
                    }
                }


            }
        }
        //physics
        if(circlePosition.x == screenWidth*0.65) {
            //we are at the end of the line
            //circlePosition = sf::Vector2f(0,5*screenHeight/10);
            //saucePosition = sf::Vector2f(200*screenWidth/2500-170*screenWidth/2500,5*screenHeight/10+200*screenWidth/2500-170*screenWidth/2500);
            pizzas[0].setDough(screenWidth, circlePosition, xVelocity,saucePosition,cooked_cheese,false,false,false );
            pizzas[0].invisible();
        }
        else {
            circlePosition.x += xVelocity;
            saucePosition.x += xVelocity;
            pizzas[0].setDough(screenWidth, circlePosition, xVelocity, saucePosition,cooked_cheese, ingredients.at("tomatoe").added, ingredients.at("cheese").added, ingredients.at("pepperoni").added) ;
        }

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(20,20));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(screenWidth*0.8,screenHeight*0.6);

        //render
        window.clear();


        window.draw(sprite_background);
        window.draw(rect);

        window.draw(score_board);
        scoreText.setString("Your Score: " + std::to_string(score));
        window.draw(scoreText);
        for(Storage& storage : storages) {
            storage.draw(window);
        }
        for(Preparation& preparation : preparations) {
            preparation.draw(window);
        }

        window.draw(pizzas[0].getDough());
        window.draw(pizzas[0].getSauce());
        window.draw(pizzas[0].getCheese());
        for (size_t i = 0; i<pizzas[0].getPepperoni().size(); i++) {
            window.draw(pizzas[0].getPepperoni()[i]);
        }

        window.display();

    }

}

void Facade::startCooking(Preparation preparation){
    cout << "START COOKING" << endl;
    if (selected.has_value()){ //is something selected
        cout << "Selected is the following: " << selected.value().getIngredient() << endl;
        if (selected_type == "storage"){  //if the last selected object is a storage
            if (selected.value().getIngredient() == preparation.getIngredient()){ //if the selected storage corresponds to the right ingredient
                selected.emplace(preparation);
                selected_type = "preparation";
                cout<< "SUCCESS" << preparation.getIngredient() << endl;

            }else{
                cout << "ERROR: you selected the wrong ingredient" << endl;
            }

        }else{
            cout << "ERROR: you didn't select a storage" << endl;
        }
    }else{
        cout << "ERROR: nothing was selected" << endl;
    }
}

int Facade::addIngredient(Pizza pizza){
    cout << 1 << endl;
    if (selected_type == "preparation") {
        cout << "test " << selected-> getIngredient() << endl;
        int res = pizza.addIngredient(selected->getIngredient());
        ingredients.at(selected->getIngredient().getlabel()).added = true;
        cout << "res result " << res;
        return res;
    }
    return 0;

}

sf::Texture Facade::loadTextureFromFile(const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        cout << "ERROR loading texture from file: " << filePath << std::endl;
    }
    return texture;
}

void pizzaGenerator(){

}




