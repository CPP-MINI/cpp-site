#include <stdio.h>

struct Vehicle;

typedef const char* (*name_func_t)(const struct Vehicle* v);
typedef void (*beep_func_t)(const struct Vehicle*);
typedef float (*drive_func_t)(struct Vehicle*, float seconds);

struct Vehicle
{
    name_func_t f_name;
    beep_func_t f_beep;
    drive_func_t f_drive;

    float position;
};

struct Car
{
    struct Vehicle base;
    int cyllinders;
};

const char* car_name(const struct Vehicle* v)
{
    return "Car";
}

void car_beep(const struct Vehicle* v)
{
    struct Car* c = (struct Car*)v;
    if (c->cyllinders >= 8)
    {
        printf("beep beep\n");
    }
    else
    {
        printf("wrrrm!\n");
    }
}

float car_drive(struct Vehicle* v, float seconds)
{
    struct Car* c = (struct Car*)v;
    const float speed = 100.0 * c->cyllinders;
    c->base.position += seconds * speed;
    return c->base.position;
}

struct Car make_car(int cyllinders)
{
    struct Car c = {.base = {.f_name = car_name, .f_beep = car_beep, .f_drive = car_drive, .position = 0.0},
                    .cyllinders = cyllinders};
    return c;
}

struct Bike
{
    struct Vehicle base;
};

const char* bike_name(const struct Vehicle* v)
{
    return "Bike";
}

void bike_beep(const struct Vehicle* v)
{
    printf("ding!\n");
}

float bike_drive(struct Vehicle* v, float seconds)
{
    struct Bike* b = (struct Bike*)v;
    const float speed = 10.0;
    b->base.position += seconds * speed;
    return b->base.position;
}

struct Bike make_bike()
{
    struct Bike b = {.base = {.f_name = bike_name, .f_beep = bike_beep, .f_drive = bike_drive, .position = 0.0}};
    return b;
}

void race(struct Vehicle* v[], size_t num)
{
    const float step = 1.0f;
    const float distance = 1000.0f;

    for (float time = 0.0f; time < 100.0f; time += step)
    {
        for (size_t i = 0; i < num; i++)
        {
            if (v[i]->f_drive(v[i], step) >= distance)
            {
                printf("winner: %s\n", v[i]->f_name(v[i]));
                return;
            }
        }
    }
}

int main()
{
    struct Car c = make_car(6);
    printf("name = %s\n", car_name(&c));
    car_beep(&c);
    car_drive(&c, 3.0);

    struct Bike b = make_bike();
    printf("name = %s\n", bike_name(&b));
    bike_beep(&b);
    bike_drive(&b, 3.0);

    struct Vehicle* v[2] = {&c, &b};
    race(v, 2);

    return 0;
}
