#include "main.h"


void blueLeft(std::shared_ptr<OdomChassisController> drive){
    drive->driveToPoint({1_ft, 1_ft});
}

void blueRight(std::shared_ptr<OdomChassisController> drive){
    drive->driveToPoint({1_ft, 1_ft});
}

void redLeft(std::shared_ptr<OdomChassisController> drive){
    drive->driveToPoint({1_ft, 1_ft});
}

void redRight(std::shared_ptr<OdomChassisController> drive){
    drive->driveToPoint({1_ft, 1_ft});
}
