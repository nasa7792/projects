/* ---------------------------------------------------------------------------------
 * Nalin Saxena
 *
 * original work- (functions MAX30102_init, MAX30102_WRITE_REGISTER,MAX30102_READ_REGISTER
 *                 MAX30102_Read_Temperature, MAX30102_Start_Temperature_Measurement,MAX30102_init_TEMPERATURE
 *                 MAX30102_read_fifo)
 *
 * ECEN 5613 - Fall 2024 - Prof. McClure
 * University of Colorado Boulder
 * Revised 10/12/24
 * File name : max_heart_sensor_driver.c
 *  --------------------------------------------------------------------------------
 *
 * This file contains function definitions related to communication with the max30102
 *
 * Attribution - the functions check_new_data,nextSample,getRed,getIR,available have been taken
 *               from the following github https://github.com/sparkfun/MAX30105_Particle_Sensor_Breakout/tree/master/Libraries/Arduino/src
 *               file name MAX30105.cpp. I would like to thank the original authours of the library Natahn Siedle and sparkfun developers.
   ---------------------------------------------------------------------------------*/



#include "max_heart_sensor_driver.h"
  #define I2C_BUFFER_LENGTH 32
#include <stdbool.h>
#include"delay.h"

typedef struct Record
{
 uint32_t red[STORAGE_SIZE];
 uint32_t IR[STORAGE_SIZE];
 uint8_t head;
 uint8_t tail;
} sense_struct; //This is our circular buffer of readings from the sensor

sense_struct sense;

void MAX30102_init(){
	I2C_init_config(); //initalize i2c

	    // Reset the sensor
	    MAX30102_WRITE_REGISTER(MODE_CONFIG_REG, 0x40); // Reset the device

	    //led brightness as 60
	    MAX30102_WRITE_REGISTER(LED1_PA_REG, 0x3c); //power set as 60
	    MAX30102_WRITE_REGISTER(LED2_PA_REG, 0x3c); // power set as 60

	    //led mode 3 both ir and red led are needed
	    MAX30102_WRITE_REGISTER(MODE_CONFIG_REG, 0x3); // spo2

	    //sample average as 4 and enable fifo rollover 0x50 0101 0000
	    MAX30102_WRITE_REGISTER(FIFO_CONFIG_REG, 0x50); //

	    //spo2 config adc range as 4096  samples as 100 led pulse as 411
	    MAX30102_WRITE_REGISTER(SPO2_CONFIG_REG, 0x27);

	    // FIFO pointers
	    MAX30102_WRITE_REGISTER(FIFO_READ_PTR, 0x00); // Reset FIFO write pointer
	    MAX30102_WRITE_REGISTER(FIFO_WR_PTR, 0x00); // Reset FIFO read pointer
}


void MAX30102_init_TEMPERATURE(){
    MAX30102_WRITE_REGISTER(MODE_CONFIG_REG, 0x40); // Reset the device

    // Configure for SpO₂ mode
    MAX30102_WRITE_REGISTER(MODE_CONFIG_REG, 0x03); // Heart rate + SpO₂ mode

    // LED Pulse Amplitude
    MAX30102_WRITE_REGISTER(LED1_PA_REG, 0x24); // Set RED LED pulse amplitude
    MAX30102_WRITE_REGISTER(LED2_PA_REG, 0x24); // Set IR LED pulse amplitude

    // SpO₂ Configuration
    MAX30102_WRITE_REGISTER(SPO2_CONFIG_REG, 0x27);
    // SPO2_ADC Range: 4096 nA (bit 5-6 = 01)
    // SPO2 Sample Rate: 100 Hz (bit 2-4 = 100)
    // LED Pulse Width: 411 µs (bit 0-1 = 11)

    // FIFO Configuration
    MAX30102_WRITE_REGISTER(FIFO_CONFIG_REG, 0x02);
    // FIFO_Average: No averaging, direct samples
}

void MAX30102_WRITE_REGISTER(uint8_t register_Address, uint8_t data){
	I2C_START_COMS();
	uint8_t write_masked_address=MAX30102_WRITE_ADDRESS;
	I2C_SEND_ADDRESS(write_masked_address); //same as AE
	I2C_WRITE_DATA(register_Address);
	I2C_WRITE_DATA(data);
	I2C_STOP_COMS();
}


void MAX30102_READ_REGISTER(uint8_t register_Address, uint8_t *recv_buff, uint8_t recv_size){

	uint8_t write_masked_address=MAX30102_WRITE_ADDRESS; //write address
	uint8_t read_masked_address=MAX30102_READ_ADDRESS; //read address
	I2C_START_COMS(); //start i2c
	I2C_SEND_ADDRESS(write_masked_address); //first send slave address
	I2C_WRITE_DATA(register_Address); //send register address
	I2C_START_COMS(); //repeated start
	I2C_READ(read_masked_address,recv_buff,recv_size); //this should be slave with read
//	I2C_STOP_COMS(); this caused 2 hours of debugging
}

void MAX30102_Start_Temperature_Measurement() {
    MAX30102_WRITE_REGISTER(TEMP_CONFIG_REG, 0x01); // Start temperature conversion
    MAX30102_WRITE_REGISTER(DIE_TEMP_RDY_EN, 0x02); // Start temperature conversion
}


float MAX30102_Read_Temperature() {
    uint8_t temp_int, temp_frac;

    // Read the temperature integer part
    MAX30102_READ_REGISTER(TEMP_INT_REG, &temp_int, 1);

    // Read the temperature fractional part
    MAX30102_READ_REGISTER(TEMP_FRAC_REG, &temp_frac, 1);

    // Combine the integer and fractional parts
    float temperature = temp_int + (temp_frac * 0.0625);

    return temperature;
}

/*
 * Not original code
 * attribution mentioned in header
 * */
uint8_t MAX30102_get_Read_ptr(){
	uint8_t read_ptr;
 MAX30102_READ_REGISTER(FIFO_READ_PTR,&read_ptr,1);
	return read_ptr;
}

/*
 * Not original code
 * attribution mentioned in header
 * */
uint8_t MAX30102_get_WR_ptr(){
	uint8_t wr_ptr;
    MAX30102_READ_REGISTER(FIFO_WR_PTR,&wr_ptr,1);
	return wr_ptr;
}

/*
 * Not original code
 * attribution mentioned in header
 * */
uint8_t available(void)
{
  int8_t numberOfSamples = sense.head - sense.tail;
  if (numberOfSamples < 0) numberOfSamples += STORAGE_SIZE;

  return (numberOfSamples);
}

/*
 * Not original code
 * attribution mentioned in header
 * */
uint16_t check_new_data(){
	uint8_t writePointer=MAX30102_get_WR_ptr();
	uint8_t readPointer=MAX30102_get_Read_ptr();
	int numberOfSamples = 0;
	if(readPointer!=writePointer){
		 numberOfSamples = writePointer - readPointer;
		 if (numberOfSamples < 0) numberOfSamples += 32; //Wrap condition
		    //We now have the number of readings, now calc bytes to read
		    //For this example we are just doing Red and IR (3 bytes each)
		    int bytesLeftToRead = numberOfSamples * 2 * 3;
		    while (bytesLeftToRead > 0)
		     {
		       int toGet = bytesLeftToRead;
		       if (toGet > I2C_BUFFER_LENGTH)
		       {
		         //If toGet is 32 this is bad because we read 6 bytes (Red+IR * 3 = 6) at a time
		         //32 % 6 = 2 left over. We don't want to request 32 bytes, we want to request 30.
		         //32 % 9 (Red+IR+GREEN) = 5 left over. We want to request 27.

		         toGet = I2C_BUFFER_LENGTH - (I2C_BUFFER_LENGTH % (2 * 3)); //Trim toGet to be a multiple of the samples we need to read
		       }

		       bytesLeftToRead -= toGet;

		       //Request toGet number of bytes from sensor

		       while (toGet > 0)
		       {
		         sense.head++; //Advance the head of the storage struct
		         sense.head %= STORAGE_SIZE; //Wrap condition

		         uint32_t red_led,ir_led;

		         uint8_t fifo_data[6]; // To store 6 bytes of FIFO data (3 bytes for red, 3 bytes for IR)

		         // Read 6 bytes from FIFO_DATA register
		         MAX30102_READ_REGISTER(FIFO_DATA_REG, fifo_data, 6);

		         // Combine the bytes for red LED
		         red_led = ((uint32_t)fifo_data[0] << 16) | ((uint32_t)fifo_data[1] << 8) | fifo_data[2];
		         red_led &= 0x03FFFF; // Mask to 18 bits
		         sense.red[sense.head] = red_led;

		         // Combine the bytes for IR LED
		         ir_led = ((uint32_t)fifo_data[3] << 16) | ((uint32_t)fifo_data[4] << 8) | fifo_data[5];
		         ir_led &= 0x03FFFF; // Mask to 18 bits
		         sense.IR[sense.head] = ir_led;

		         toGet -= 2 * 3;
		       }

		     } //End while (bytesLeftToRead > 0)

		   } //End readPtr != writePtr

		   return (numberOfSamples); //Let the world know how much new data we found
	}


bool safeCheck(uint16_t maxTimeToCheck)
{
  uint32_t markTime = millis();

  while(1)
  {
	if(millis() - markTime > maxTimeToCheck) return(false);

	if(check_new_data() == true) //We found new data!
	  return(true);

	delay(1);
  }
}


void MAX30102_read_fifo(uint32_t *red_led, uint32_t *ir_led) {
    uint8_t fifo_data[6]; // To store 6 bytes of FIFO data (3 bytes for red, 3 bytes for IR)

    // Read 6 bytes from FIFO_DATA register
    MAX30102_READ_REGISTER(FIFO_DATA_REG, fifo_data, 6);

    // Combine the bytes for red LED
    *red_led = ((uint32_t)fifo_data[0] << 16) | ((uint32_t)fifo_data[1] << 8) | fifo_data[2];
    *red_led &= 0x03FFFF; // Mask to 18 bits

    // Combine the bytes for IR LED
    *ir_led = ((uint32_t)fifo_data[3] << 16) | ((uint32_t)fifo_data[4] << 8) | fifo_data[5];
    *ir_led &= 0x03FFFF; // Mask to 18 bits
}

//Report the most recent red value
uint32_t getRed(void)
{
  //Check the sensor for new data for 250ms
	if(safeCheck(2500))
    return (sense.red[sense.head]);
  else
    return(0); //Sensor failed to find new data
}

uint32_t getIR(void)
{
  //Check the sensor for new data for 250ms
	if(safeCheck(2500))
    return (sense.IR[sense.head]);
  else
    return(0); //Sensor failed to find new data
}

//Advance the tail
void nextSample(void)
{
  if(available()) //Only advance the tail if new data is available
  {
    sense.tail++;
    sense.tail %= STORAGE_SIZE; //Wrap condition
  }
}
void acquire_max_30102_data(uint32_t num_ters,int8_t* heart_rate_status,int32_t* spo2_var,int32_t* heart_rate_var,int8_t* valid_spo2,bool *status)
{
	uint32_t irBuffer[100]; //infrared LED sensor data
	uint32_t redBuffer[100];  //red LED sensor data
	int32_t bufferLength;


	bufferLength=100;

	  for (uint8_t i = 0 ; i < bufferLength ; i++)
	  {
	    while (available() == false) //do we have new data?
	    	check_new_data(); //Check the sensor for new data

	    redBuffer[i] = getRed();
	    irBuffer[i] =  getIR();
	    nextSample(); //We're finished with this sample so move to next sample
	  }
	  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, spo2_var, valid_spo2, heart_rate_var, heart_rate_status);
	    if(*valid_spo2==1){
		    	*status=true;
		    return ;
		    }
	  while (--num_ters)
	  {
	    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
	    for (uint8_t i = 25; i < 100; i++)
	    {
	      redBuffer[i - 25] = redBuffer[i];
	      irBuffer[i - 25] = irBuffer[i];
	    }

	    //take 25 sets of samples before calculating the heart rate.
	    for (uint8_t i = 75; i < 100; i++)
	    {
	      while (available() == false) //do we have new data?
	    	  check_new_data(); //Check the sensor for new data



	      redBuffer[i] = getRed();
	      irBuffer[i] = getIR();
	     nextSample(); //We're finished with this sample so move to next sample

		    if(*valid_spo2==1){
			    	*status=true;
			    return ;
			    }
	   }
	    //After gathering 25 new samples recalculate HR and SP02

	    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, spo2_var, valid_spo2, heart_rate_var, heart_rate_status);
	  }

}


