#include "main.h"

void blueLeft(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl){
    drive->driveToPoint({1_ft, 1_ft});
}

void blueRight(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl){
    drive->driveToPoint({1_ft, 1_ft});
}

void redLeft(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl){
    drive->driveToPoint({1_ft, 1_ft});
}

void redRight(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl){
    drive->driveToPoint({1_ft, 1_ft});
}
