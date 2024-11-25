#include "unitTest.h"

int main(void) {
        int choose_Unit;
	obstacle_Location OL;
	bool DE;
	motor_Command MC;
	cleaner_Command CC;
	bool is_Backward;
	int mode;

    while (1) {
        printf("----------Units for test----------\n");
        printf("1.  FS_Interface\n");
        printf("2.  LS_Interface\n");
        printf("3.  RS_Interface\n");
        printf("4.  DS_Interface\n");
        printf("5.  Determine_OL\n");
        printf("6.  Determine_DE\n");
        printf("7.  Set_Cleaner_Command\n");
        printf("8.  Move_Forward\n");
        printf("9.  Turn_Left\n");
        printf("10. Turn Right\n");
        printf("11. Stop\n");
        printf("12. Move_Backward\n");
        printf("13. Controller\n");
        printf("14. EXIT PROGRAM\n");
        printf("choose the number(EXIT is 14): ");
        scanf("%d", &choose_Unit);
	printf("\n");
        
	switch (choose_Unit) {
	    case 1:
		printf("Front Sensor Input: %d\n", FS_Interface());	
	        break;
	    case 2:
		printf("Left Sensor Input: %d\n", LS_Interface());
		break;
	    case 3:
		printf("Right Sensor Input: %d\n", RS_Interface());
		break;
	    case 4:
		printf("Dust Sensor Input: %d\n", DS_Interface());
		break;
	    case 5:
		OL = determine_OL();
		printf("Obstacle Location(F, L, R) = {%d, %d, %d}\n", OL.F, OL.L, OL.R); 
		break;
	    case 6:
		printf("Dust Existence(D) = {%d}\n", determine_DE());   
		break;
	    case 7:
		printf("0 = ON, 1 = OFF, 2 = UP\n");
		printf("Input Cleaner Command(0, 1, 2): ");
		scanf("%d", &mode);
		CC = set_Cleaner_Command(mode);
		printf("Cleaner Command(ON, OFF, UP) = {%d, %d, %d}\n", CC.on, CC.off, CC.up);
		break;
	    case 8:
		MC = move_Forward();
		printf("Motor Command(F, L, R, B) = {%d, %d, %d, %d}\n", MC.F, MC.L, MC.R, MC.B);	
		break;
	    case 9:
		MC = turn_Right();
		printf("Motor Command(F, L, R, B) = {%d, %d, %d, %d}\n", MC.F, MC.L, MC.R, MC.B);			
	   	break;
	    case 10:
		MC = turn_Left();
		printf("Motor Command(F, L, R, B) = {%d, %d, %d, %d}\n", MC.F, MC.L, MC.R, MC.B);
		break;
	    case 11:
		MC = stop();
		printf("Motor Command(F, L, R, B) = {%d, %d, %d, %d}\n", MC.F, MC.L, MC.R, MC.B);
		break;
	    case 12:
		MC = move_Backward();
		printf("Motor Command(F, L, R, B) = {%d, %d, %d, %d}\n", MC.F, MC.L, MC.R, MC.B);
		break;
	    case 13:
           	printf("is_Backward value(0 or 1): ");
            	scanf("%d", &is_Backward);
            	printf("Dust Existence(D) value: ");
            	scanf("%d", &DE);
            	printf("Obstacle Location(F, L, R, B) value: ");
            	scanf("%d %d %d", &OL.F, &OL.L, &OL.R);

            	controller(is_Backward, OL, DE);
		break;
	    case 14:
		printf("Exit the program...\n");
	     	return 0;
	    default:
		printf("Please choose the correct number!\n");
        }    
    }
}

void controller(bool is_Backward, obstacle_Location OL, bool DE) {
    obstacle_Location obstacle_Location;
    bool dust_Existence;

    obstacle_Location = OL;
    dust_Existence = DE;

    if (!obstacle_Location.F && !is_Backward) {
        move_Forward();
        printf("Motor Command(F, L, R, B) = {1, 0, 0, 0}\n");
        if (dust_Existence) {
            printf("Cleaner Command(ON, OFF, UP) = {0, 0, 1}\n");
        } else {
            printf("Cleaner Command(ON, OFF, UP) = {1, 0, 0}\n");
        }
    } else if (!obstacle_Location.R) {
        turn_Right();
        printf("Motor Command(F, L, R, B) = {0, 0, 1, 0}\n");
        printf("Cleaner Command(ON, OFF, UP) = {0, 1, 0}\n");
    } else if (!obstacle_Location.L) {
        turn_Left();
        printf("Motor Command(F, L, R, B) = {0, 1, 0, 0}\n");
        printf("Cleaner Command(ON, OFF, UP) = {0, 1, 0}\n");
    } else {
        stop();
        printf("Motor Command(F, L, R, B) = {0, 0, 0, 0}\n");
        printf("Cleaner Command(ON, OFF, UP) = {0, 1, 0}\n");
        move_Backward();
        printf("Motor Command(F, L, R, B) = {0, 0, 0, 1}\n");
        is_Backward = true;
    }
}

obstacle_Location determine_OL(void) {
    obstacle_Location obstacle_Location;

    obstacle_Location.F = FS_Interface();
    obstacle_Location.L = LS_Interface();
    obstacle_Location.R = RS_Interface();

    return obstacle_Location;
}

bool determine_DE(void) {
    return DS_Interface();
}

bool FS_Interface(void) {
    double front_sensor_analog_input;
    printf("front sensor: ");
    scanf("%lf", &front_sensor_analog_input);
    bool front_sensor_input = front_sensor_analog_input > 50 ? true : false;

    return front_sensor_input;
}

bool LS_Interface(void) {
    double left_sensor_analog_input;
    printf("left sensor: ");
    scanf("%lf", &left_sensor_analog_input);
    bool left_sensor_input = left_sensor_analog_input > 50 ? true : false;

    return left_sensor_input;
}

bool RS_Interface(void) {
    double right_sensor_analog_input;
    printf("right sensor: ");
    scanf("%lf", &right_sensor_analog_input);
    bool right_sensor_input = right_sensor_analog_input > 50 ? true : false;

    return right_sensor_input;
}

bool DS_Interface(void) {
    double dust_sensor_analog_input;
    printf("dust sensor: ");
    scanf("%lf", &dust_sensor_analog_input);
    bool dust_sensor_input = dust_sensor_analog_input > 50 ? true : false;

    return dust_sensor_input;
}

motor_Command move_Forward(void) {
    motor_Command motor_Command;
    motor_Command.F = true;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command turn_Left(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = true;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command turn_Right(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = true;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command stop(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = false;

    Motor_Interface(motor_Command);

    return motor_Command;
}

motor_Command move_Backward(void) {
    motor_Command motor_Command;
    motor_Command.F = false;
    motor_Command.L = false;
    motor_Command.R = false;
    motor_Command.B = true;

    Motor_Interface(motor_Command);
    
    return motor_Command;
}

cleaner_Command set_Cleaner_Command(int set_num) {
    cleaner_Command cleaner_Command;

    if (set_num == ON) {
        cleaner_Command.on = true;
        cleaner_Command.off = false;
        cleaner_Command.up = false;
    } else if (set_num == OFF) {
        cleaner_Command.on = false;
        cleaner_Command.off = true;
        cleaner_Command.up = false;
    } else if (set_num == UP) {
        cleaner_Command.on = false;
        cleaner_Command.off = false;
        cleaner_Command.up = true;
    }

    return cleaner_Command;
}

void Motor_Interface(motor_Command motor_Command) {
	return;
}

void Cleaner_Interface(cleaner_Command cleaner_Command) {
	return;
}
