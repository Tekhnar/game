//
// Created by Mikhail Kaskov on 12.06.2020.
//

#include "models.h"
#include "objects.h"


void AutosimModel::createDefaultObjects () {
    Car* main_car = new Car;

//    settingsCar settings;
    createDefaultSettingsForCar (main_car);

    objects[numActiveObjects] = main_car;
    numActiveObjects++;

    this->main_car = main_car;

/*    Car* add_car = new Car;
    createDefaultSettingsForCar (add_car);
    add_car->position = sf::Vector2f (2.f, 2.5f);
    add_car->rotation_angle = 75.f;
    add_car->wheel[2].point->rotation_angle = 0.f;

    objects[numActiveObjects] = add_car;
    numActiveObjects++;*/
}

void AutosimModel::loadDefaultTextureInCar (Car* car) {
    car->texture.loadFromFile ("car.png");
    car->texture.setSmooth (true);
    car->sprite.setSize (sf::Vector2f(1.8, 4.2));
    car->sprite.setOrigin  (car->size_object / 2.0f);
    car->sprite.setTexture (&car->texture);

    for (auto &i : car->wheel) {
        i.point->size_object = sf::Vector2f();

        i.point->wheel_diameter = 0.63;
        i.point->size_object = sf::Vector2f(0.25, 0.60);
//        i.point->sprite.setOrigin (i.point->size_object / 2.0f);

        i.point->texture.loadFromFile ("tire.png");
        i.point->texture.setSmooth (true);

        i.point->sprite.setTexture (&i.point->texture);
    }
}

void AutosimModel::createDefaultSettingsForCar (Car* car) {
    car->size_object      = sf::Vector2f (1.9, 4.2);
    car->mass_of_car      = 150000.0;
    car->drag_coefficient = 0.15;

    car->wheel[0].is_rotating_wheel = 1;
    car->wheel[1].is_rotating_wheel = 1;
    car->wheel[2].is_rotating_wheel = 0;
    car->wheel[3].is_rotating_wheel = 0;

    car->wheel[0].is_pulling = true;
    car->wheel[1].is_pulling = true;
    car->wheel[2].is_pulling = true;
    car->wheel[3].is_pulling = true;


    loadDefaultTextureInCar (car);

//    float offset_right = 0.8;
//    float offset_front = 0.8;

    car->wheel[0].point->position = sf::Vector2f (-0.69, -1.28);
    car->wheel[1].point->position = sf::Vector2f ( 0.69, -1.28);
    car->wheel[2].point->position = sf::Vector2f (-0.69,  1.38);
    car->wheel[3].point->position = sf::Vector2f ( 0.69,  1.38);

//    car.name_file_texture_car   = "car.png";
//    car.name_file_texture_wheel = "tire.png";
}

void AutosimModel::calculationNewPositions (unsigned long long different_time, ManipulatorData &last_manipulator_data) {
    float last_cycle_time = static_cast<float> (different_time) / 1000000.f;

    ManipulatorData empty_manipulator { 0.f, 0.f, 0.f, 0.f };
    for (size_t i = 0; i <  numActiveObjects; i++) {
        if (objects[i] == main_car)
            objects[i]->calculationNewState (last_cycle_time, last_manipulator_data);
        else
            objects[i]->calculationNewState (last_cycle_time, empty_manipulator);
    }
}

void AutosimModel::createDefaultMap () {
    auto map = new BaseObject;

    if (!map->texture.loadFromFile ("map.png")) {
        printf ("Error in read texture for map!\n");
        exit (2);
    }
    map->size_object = sf::Vector2f(200.f, 200.f);

    map->texture.setSmooth (true);

    map->sprite.setTexture (&map->texture);
    objects[0] = map;
}

