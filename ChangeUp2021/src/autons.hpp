#pragma once
#include "main.h"

void blueLeft(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl);

void blueRight(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl);

void redLeft(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl);

void redRight(std::shared_ptr<OdomChassisController> drive,
  std::shared_ptr<AsyncPositionController<double, double>> intakeControl,
  std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl,
  std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl);
