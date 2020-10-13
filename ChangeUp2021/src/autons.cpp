#include "main.h"


void blueLeft(std::shared_ptr<ChassisController> drive){
    drive->moveDistance(5_in);
}

void blueRight(std::shared_ptr<ChassisController> drive){
    drive->moveDistance(5_in);
}

void redLeft(std::shared_ptr<ChassisController> drive){
    drive->moveDistance(5_in);
}

void redRight(std::shared_ptr<ChassisController> drive){
    drive->moveDistance(5_in);
}
