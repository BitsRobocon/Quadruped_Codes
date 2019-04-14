#include <math.h>
#include <Servo.h>

/* Some definitions

Origin is the point exactly (height of hip) distance below the hip joint and zero horizontal distance apart
 _________
   \    ------- ohm
    \ 
     \ _____________ theta
     /
    /
  ./

this full stop point defines the point in consideration at all times

*/

/////////////////////////////////////   defintitions       /////////////////////////////////////////////////////////////////////

#define ohmac1  90                //actual (physical) angle of femur with vertical at a particular time
#define ohmmot1 180                //value fed to motor (pos) for that femur angle
#define ohmac2 -90 
#define ohmmot2 15

#define thetaac1 180               //actual (physical) angle of tibia with femur at a particular time
#define thetaac2 0               //value fed to motor (pos) for that tibia angle
#define thetamot1 20
#define thetamot2 180


#define femur_length 185           // in cm
#define tibia_length 17           
#define h 25.1               // height of hip in cm

Servo kservo;        // create servo object to control a servo
Servo hservo;        // twelve servo objects can be created on most boards



void setup() {
  kservo.attach(8); 
  hservo.attach(9);// attaches the servo on pin 9 to the servo object
}
////////////////////////////////////    definitions over. functions defined      ///////////////////////////////////////////////////////


float find_ohm(float x, float y){              ////finds physical ohm for a given combination of x and y

	float magsquare= (pow((h-y),2)+pow(x,2));    // square of magnitude of the location of point wrt origin 
	float a= (pow((h-y),2)+pow(x,2)+pow(femur_length,2)-pow(tibia_length,2))/(2*femur_length*(pow(magsquare,0.5)));
	float b= (h-y)/pow(magsquare, 0.5);
	float angle = asin(a)-asin(b);
	return angle;
}               

float find_theta(float x, float ohm){            //finds physical theta for a given combination of x and y, or x and ohm
	float sinval = ((femur_length*sin(ohm)-x)/tibia_length);
	float angle= asin(sinval)-ohm;
	return angle;
}

float find_motor_ohm(float ohm_ac){              ////finds the motor pos of ohm for a given physical ohm
	float motor_ohm= ((ohmmot2-ohmmot1)/(ohmac2-ohmac1))*ohm_ac+ ohmac1;
	return motor_ohm;
}


float find_motor_theta(float theta_ac){          //finds the motor pos of theta for a given physical theta
	float motor_theta= ((thetamot2-thetamot1)/(thetaac2-thetaac1))*theta_ac+ thetaac1;
	return motor_theta;
}

float f(float x){ 
	float y = pow((36-pow(x,2)),0.5);                                 ///// define fx
	return y;
}


float complete_loop (){
	float x=6;
	float y = (f(x));
	delay(100);
	for (x=6; (x>-5.9);x-=0.1){  ////define the conditions
		y = f(x);
float		ohmac= find_ohm(x,y);
float		thetaac= find_theta(x, ohmac);         /////// give the output to the servos
		kservo.write(find_motor_theta(thetaac));
		hservo.write(find_motor_ohm(ohmac));
		delay(50);
	}
	for (x=-6; (x<5.9) ; x+=0.1){     /////////////define the conditions
		y=f(x);
float		ohmac= find_ohm(x,y);
float		thetaac= find_theta(x, ohmac);
		kservo.write(find_motor_theta(thetaac));
		hservo.write(find_motor_ohm(ohmac));
		delay(50);
	}


	//printf("The actual values of (ohm, theta) are (%f, %f)\n", ohm, theta);
	//printf("The motor pos values of (ohm, theta) are (%f,%f)\n",find_motor_ohm(ohm), find_motor_theta(theta) );

	return 0;
}

 void loop(){
//int main(){
	/*float x=0;
	float y=0;
    printf("Please enter x ");
	scanf(&x,"%f");
	printf("y: ");
	scanf(&y,"%f");
	printf("femur: ");
	scanf(&femur_length,"%f");
	printf("tibia: ");
	scanf(&tibia_length,"%f");
	printf("height of hip:");
	scanf(&height,"%f");
	
	
	float ohmac= find_ohm(x,y);     //physical values of ohm and theta derived for particular x and y
	float thetaac= find_theta(x, ohmac);
	printf("The actual values of (ohm, theta) are (%f, %f)\n", ohmac, thetaac);
	printf("The motor pos values of (ohm, theta) are (%f,%f)\n",find_motor_ohm(ohmac), find_motor_theta(thetaac) );

	*/

	complete_loop();
	


	return 0;

}
