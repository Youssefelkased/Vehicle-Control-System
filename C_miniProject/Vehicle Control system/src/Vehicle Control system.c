#include <stdio.h>
#include <stdlib.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 /*Set to 0 to turn off engine temperature control*/
typedef enum{
	OFF=0,ON
}state;

/*Functions declaration*/
void Display_menu();
void Display_Sensors_menu();
void display_Vehicle_State();

/*Variables declaration*/
int status,vehicle_speed,room_temperature=35,engine_temperature=90;
int ET_controller=OFF;//Engine Temperature controller is OFF
int AC=OFF; //AC OFF
char traffic_light;

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); setvbuf(stderr, NULL, _IONBF, 0);
	Display_menu();
	while(status==ON){Display_Sensors_menu();}

	return EXIT_SUCCESS;
}

void display_Vehicle_State(){/*Third function required*/
	if(status==ON)printf("\nEngine state is ON");
	else if(status==OFF)printf("\nEngine state is OFF");
	else if(status==3){printf("\nQuitting system");return;}

	if(AC==ON)printf("\nAC is ON\n");
	else printf("\nAC is OFF\n");

	printf("Vehicle speed is: %d KM\n",vehicle_speed);

	printf("Room temperature is: %d C\n",room_temperature);

	if(WITH_ENGINE_TEMP_CONTROLLER){/*Bonus requirement*/
		if(ET_controller==ON)printf("Engine temperature controller state is ON\n ");
		else printf("\nEngine temperature controller state is OFF\n ");

		printf("Engine Temperature is : %d C\n",engine_temperature);
	}
	else{printf("Engine temperature options are turned off!");
	}
}

void Display_menu(){/*First function required*/

	printf( "Enter desired state:\n ");
	printf( "Enter 1 to turn on the vehicle engine\n"
			" Enter 2 to turn off the vehicle engine\n"
			" Enter 3 to quit the system\n"
			" Enter 4 to display your vehicle state\n");

	scanf("%d",&status);

	if(status==1)printf("\nSystem state is: ON ");

	else if(status==2){
		printf("\nSystem state is: OFF ");
		Display_menu();
	}
	else if(status==3){		/*Exit system*/
		return;
	}
	else if(status==4){		/*Extra option if Vehicle state is needed*/
		display_Vehicle_State();
	}
}

void Display_Sensors_menu(){/*Second function required*/
	int sensors_status=OFF;
	printf( "\n\nEnter 1 to turn off the vehicle engine\n"
			"Enter 2 to set the traffic light color\n"
			"Enter 3 to set the room temperature\n"
			"Enter 4 to set the engine temperature\n");
	scanf("%d",&sensors_status);

	switch(sensors_status){
	case 1: Display_menu();break;	/*Turn off engine*/

	case 2: /*Vehicle speed control based on traffic light's data*/
		printf("\nEnter traffic light:");
		scanf(" %c",&traffic_light);

		switch(traffic_light){

		case'G': vehicle_speed=100;printf("\nVehicle speed is : %d KM\n",vehicle_speed); break;
		case'O': vehicle_speed=30;printf("\nVehicle speed is : %d KM\n",vehicle_speed);  break;
		case'R': vehicle_speed=0;printf("\nVehicle speed is : %d KM\n",vehicle_speed);  break;

		}
		if(vehicle_speed==30){	/*Condition 7-d*/

			if(AC==OFF) {AC=ON;}
			room_temperature*=(5/4)+1;
			printf("\nAdjusted room temperature to: %d C\n",room_temperature);

			if(WITH_ENGINE_TEMP_CONTROLLER){/*Bonus requirement*/
				if(ET_controller==OFF){ET_controller=ON;}
				engine_temperature*=(5/4)+1;
				printf("\nAdjusted engine temperature to: %d C\n",engine_temperature);
			}
			else{printf("\nEngine temperature options are turned off!\n");
			}
		}
		display_Vehicle_State();
		break;

		case 3: /*Room temperature control*/
			printf("\nEnter current room temperature\n");
			scanf("%d",&room_temperature);
			if (room_temperature<10 || room_temperature>30){AC=ON;room_temperature=20;
			printf("AC is turned on and room temperature is set to: %d C",room_temperature);}
			display_Vehicle_State();
			break;

		case 4: /*Engine temperature control*/
			if(WITH_ENGINE_TEMP_CONTROLLER){/*Bonus requirement*/

				printf("\nEnter current engine temperature\n");
				scanf("%d",&engine_temperature);
				if(engine_temperature<100 || engine_temperature>150){ET_controller=ON;engine_temperature=125;
				printf("Engine temperature controller is turned on and engine temperature is set to: %d C",engine_temperature);}
				display_Vehicle_State();
			}
			else{printf("\nEngine temperature options are turned off!\n");
			}
			break;
	}
}

