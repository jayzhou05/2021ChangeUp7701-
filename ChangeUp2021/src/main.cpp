#include "main.h"
#include "autons.hpp"

int autonChosen = 0;
bool autonSelected = false;
// Master controller by default.
Controller controller;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello Hayden, good luck today!~ (^^)/");

	ControllerButton leftButton(ControllerDigital::left);
	ControllerButton rightButton(ControllerDigital::right);
	ControllerButton AButton(ControllerDigital::A);
	std::vector<std::string> autonNames = {"none", "blue left", "blue right", "red left", "red right"};


	pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS:");
	pros::lcd::set_text(3, autonNames[autonChosen]);
	while(!autonSelected){
		if(rightButton.isPressed()){
			if (autonChosen < 4) {
				autonChosen++;
			}
			pros::lcd::clear_line(2);
			pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS:");
			pros::lcd::set_text(3, autonNames[autonChosen]);
		}
		if(leftButton.isPressed()){
			pros::lcd::clear_line(2);
			if (autonChosen > 0) {
				autonChosen--;
			}
			pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS:");
			pros::lcd::set_text(3, autonNames[autonChosen]);
		}
		if(AButton.isPressed()){
			pros::lcd::clear_line(2);
			pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS:");
			pros::lcd::set_text(3, autonNames[autonChosen]);
			autonSelected = true;
		}
		pros::delay(200);
	}

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

	ControllerButton leftButton(ControllerDigital::left);
	ControllerButton rightButton(ControllerDigital::right);
	ControllerButton AButton(ControllerDigital::A);
	std::vector<std::string> autonNames = {"none", "blue left", "blue right", "red left", "red right"};


	pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS: " + autonNames[autonChosen]);
	while(!autonSelected){
		if(rightButton.isPressed()){
			if (autonChosen < 4) {
				autonChosen++;
			}
			pros::lcd::clear_line(2);
			pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS: " + autonNames[autonChosen]);
		}
		if(leftButton.isPressed()){
			pros::lcd::clear_line(2);
			if (autonChosen > 0) {
				autonChosen--;
			}
			pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS:" + autonNames[autonChosen]);
		}
		if(AButton.isPressed()){
			pros::lcd::clear_line(2);
			pros::lcd::set_text(2, "Autonomous selected:" + autonNames[autonChosen]);
			autonSelected = true;
		}
		pros::delay(100);
	}


}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// Motor Groups
	MotorGroup leftWheels({1, 2});
	MotorGroup rightWheels({-3, -4});
	MotorGroup intakeMotors({5,-6});
	Motor fEject(7);
	Motor bEject(8);

	//PID Values
	const double intakeskP = 0.001;
	const double intakeskI = 0.0001;
	const double intakeskD = 0.0001;

	const double fEjectkP = 0.001;
	const double fEjectkI = 0.0001;
	const double fEjectkD = 0.0001;

	const double bEjectkP = 0.001;
	const double bEjectkI = 0.0001;
	const double bEjectkD = 0.0001;


	//Chassis
	std::shared_ptr<OdomChassisController> drive =
			ChassisControllerBuilder()
					.withMotors(leftWheels, rightWheels)
					// Green gearset, 4 in wheel diam, 11.5 in wheel track
					.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
					.withOdometry() // use the same scales as the chassis (above)
    			.buildOdometry();
			drive->setMaxVelocity(600);


	std::shared_ptr<AsyncPositionController<double, double>> intakeControl =
	  AsyncPosControllerBuilder()
	    .withMotor(intakeMotors) // lift motor port 3
	    .withGains({intakeskP, intakeskI, intakeskD})
	    .build();

	std::shared_ptr<AsyncPositionController<double, double>> bEjectorControl =
		AsyncPosControllerBuilder()
			.withMotor(bEject) // lift motor port 3
			.withGains({bEjectkP, bEjectkI, bEjectkP})
			.build();

	std::shared_ptr<AsyncPositionController<double, double>> fEjectorControl =
		AsyncPosControllerBuilder()
			.withMotor(fEject) // lift motor port 3
			.withGains({fEjectkP, fEjectkI, fEjectkD})
			.build();

	switch(autonChosen)
	{
		case 0:

		break;
		case 1:
			blueLeft(drive, intakeControl, bEjectorControl, fEjectorControl);
			break;
		case 2:
			blueRight(drive, intakeControl, bEjectorControl, fEjectorControl);
			break;
		case 3:
			redLeft(drive, intakeControl, bEjectorControl, fEjectorControl);
			break;
		case 4:
			redRight(drive, intakeControl, bEjectorControl, fEjectorControl);
			break;
		default:
			break;
	}

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // Motor Groups + Indv. Motors
	MotorGroup leftWheels({1, 2});
	MotorGroup rightWheels({-3, -4});
	Motor lIntake(5);
	Motor rIntake(-6);
	Motor fEject(7);
	Motor bEject(8);

	// Chassis Controller Builder Integrated
	std::shared_ptr<ChassisController> drive =
	    ChassisControllerBuilder()
	        .withMotors(leftWheels, rightWheels)
	        // Green gearset, 4 in wheel diam, 11.5 in wheel track
	        .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
	        .build();

	//Controller Toggle Buttons
	ControllerButton intakeButton(ControllerDigital::L2);
	ControllerButton ejectorButton(ControllerDigital::R1);
	ControllerButton ejectorButtonSlow(ControllerDigital::L1);
	ControllerButton ejectorRevButton(ControllerDigital::B);

	//Toggle Values
	int intakeTog = 0;
	int ejectionTog = -1;
	int ejectReverseTog = -1;
	int ejectSlowTog = -1;

	while (true) {
			//for troubleshooting, analogs
			pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & ANALOG_LEFT_Y) >> 2,
			                 (pros::lcd::read_buttons() & ANALOG_LEFT_X) >> 1);

	    // Arcade drive with the left stick.
	    drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
	                              controller.getAnalog(ControllerAnalog::leftX));

			//Toggle Checks
			if(ejectorButton.isPressed()){
					ejectionTog *= -1;
			}
			if(ejectorButtonSlow.isPressed()){
					ejectSlowTog *= -1;
			}
			if(ejectorRevButton.isPressed()){
					ejectReverseTog *= -1;
			}


			//MOTOR CONTROLS---------------

			//Intakes
			if(intakeButton.isPressed()){ //When intakes buttons are held
					lIntake.moveVoltage(12000);
					rIntake.moveVoltage(12000);
			} else{
				lIntake.moveVoltage(0);
				rIntake.moveVoltage(0);
			}

			//Ejector
			if(ejectionTog == 1){ //When ejector is on
				  if(ejectReverseTog==-1){ //When not reversed
						if(ejectSlowTog==1){ //Not reversed Slow
							fEject.moveVoltage(7000);
							bEject.moveVoltage(7000);
						}else if(ejectSlowTog==-1){ //Not reversed Fast
							fEject.moveVoltage(12000);
							bEject.moveVoltage(12000);
						}
					}else if(ejectReverseTog==1){ //When reversed
						if(ejectSlowTog==1){ //Reversed slow
							fEject.moveVoltage(7000);
							bEject.moveVoltage(-7000);
						}else if(ejectSlowTog==-1){ //Reversed Fast
							fEject.moveVoltage(12000);
							bEject.moveVoltage(-12000);
						}
					}
			}else if(ejectionTog==-1){ //When ejector is off
				fEject.moveVoltage(0);
				bEject.moveVoltage(0);
			}

			/*
			//EJECTOR ANALOG CONTROLS

				fEject.moveVoltage(abs(94 * controller.getAnalog(ControllerAnalog::rightY)));
				bEject.moveVoltage(94 * controller.getAnalog(ControllerAnalog::rightY));

			*/
	    //refresh time
	    pros::delay(10);
	}



}
