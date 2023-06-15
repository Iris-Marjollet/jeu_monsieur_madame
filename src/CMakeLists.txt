
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} Ingredient.cpp Ingredient.h Pizza.cpp Pizza.h Kitchen.cpp Kitchen.h Preparation.cpp Preparation.h Facade.cpp Facade.h Storage.cpp Storage.h PizzaPool.cpp PizzaPool.h)
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC pugixml sfml-graphics)
