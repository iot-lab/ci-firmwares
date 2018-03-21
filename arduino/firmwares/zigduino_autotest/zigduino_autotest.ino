/* Arduino autotest, inspired from the arduino librairy */
#define MAX_SIZE 255

char command_line[MAX_SIZE];
char command[MAX_SIZE];
char argument[MAX_SIZE];

void read_commandline(){
  int i=0;
  int j=0;
  boolean continu = true;
  boolean is_command = true;
  
  while(continu){
     while(Serial.available() <= 0){
      delay(0.5);
    }
    while(Serial.available() > 0){
      command_line[i] = Serial.read();
      if(is_command){
        command[j] = command_line[i];
      }
      else{
        argument[j] = command_line[i];
      }
      if(command_line[i] == '\n'){
        if(is_command){
          command[j] = '\0';
        }
        else{
          argument[j] = '\0';
        }
        command_line[i] = '\0';
        continu = false;
      }
      else if(command_line[i] == ' ' && is_command){
        command[j] = '\0';
        //for the ++ after
        j=-1;
        is_command = false;
      }
      i++;
      j++;
    }
  }
}

boolean contains(char *string_one, char *string_two){
  int i=0;
  while(string_two[i] != '\0'){
    if(string_one[i] != string_two[i]){
      return false;
    }
    i++;
  }
  return true;
}

void setup()
{
  /* Start serial port at 57600bps for Zigduino */
  Serial.begin(57600);
}

void loop()
{
  read_commandline();
    
  if(contains(command, "echo")){
    Serial.print(argument);
  }
  else if(contains(command, "get_time")){
    Serial.print("ACK get_time ");
    Serial.print(millis());
    Serial.print(" ticks_32khz");
  }
  else if(contains(command, "get_uid")){
    Serial.print("ACK get_uid ");
    Serial.print("05D8FF323632483343037109");
  }
  Serial.print('\n');
}
