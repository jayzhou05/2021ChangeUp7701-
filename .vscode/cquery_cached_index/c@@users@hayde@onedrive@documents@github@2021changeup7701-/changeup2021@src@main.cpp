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
	ControllerButton AButton(ControllerDigital::right);
	std::vector<std::string> autonNames = {"none", "blue left", "blue right", "red left", "red right"};


	pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS: " + autonNames[autonChosen]);
	while(!autonSelected){
		if(rightButton.isPressed()){
			autonChosen++;
			pros::lcd::clear_line(2);
			pros::lcd::set_text(2, "PLEASE SELECT THE AUTONOMOUS: " + autonNames[autonChosen]);
		}
		if(leftButton.isPressed()){
			pros::lcd::clear_line(2);
			autonChosen--;
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

	//Chassis
	std::shared_ptr<OdomChassisController> drive =
			ChassisControllerBuilder()
					.withMotors(leftWheels, rightWheels)
					// Green gearset, 4 in wheel diam, 11.5 in wheel track
					.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
					.withOdometry() // use the same scales as the chassis (above)
    			.buildOdometry();
			drive->setMaxVelocity(600);

	switch(autonChosen)
	{
		case 0:

		break;
		case 1:
			blueLeft(drive);
			break;
		case 2:
			blueRight(drive);
			break;
		case 3:
			redLeft(drive);
			break;
		case 4:
			redRight(drive);
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
  // Motor Groups
	MotorGroup leftWheels({1, 2});
	MotorGroup rightWheels({-3, -4});

	// Chassis Controller Builder Integrated
	std::shared_ptr<ChassisController> drive =
	    ChassisControllerBuilder()
	        .withMotors(leftWheels, rightWheels)
	        // Green gearset, 4 in wheel diam, 11.5 in wheel track
	        .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
	        .build();


	while (true) {
			//for troubleshooting, analogs
			pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & ANALOG_LEFT_Y) >> 2,
			                 (pros::lcd::read_buttons() & ANALOG_LEFT_X) >> 1);

	    // Arcade drive with the left stick.
	    drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
	                              controller.getAnalog(ControllerAnalog::leftX));
	    //refresh time
	    pros::delay(10);
	}



}
