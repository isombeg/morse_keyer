#define UNIT 300 //Time unit used for interpreting user input
#define INPUT_PIN 13 //Pin which takes electrical signals from morse code input

// Binary tree of characters arranged such that they are located by the pattern of dots
// and dashes corresponding to their respective morse codes
char* alpha = "  ETIANMSURWDKGOHVF L PJBXCYZQ  54 3   2       16       7   8 90";
unsigned long* starting_time = calloc(sizeof(unsigned long),1);

int* test_morsecode = calloc(sizeof(int),5);

char morseToAlpha(int* morse);
int* getMorse();
int changeChar(), changeWord(), readInput();
void record();

void setup() {
  //Initiating serial connection
  Serial.begin(9600);
  
  //Setting up input pin
  pinMode(INPUT_PIN, INPUT);
  
  delay(500);
  
  //Prompt user to begin inputting morse code
  Serial.println("Commencing recording process. Please begin inputting.\n");
}

void loop() {
  do{
    Serial.print(morseToAlpha(getMorse()));
  } while(!changeWord());
  Serial.println(" ...");
}

void record(){
  // Records and displays user input
  do{
    Serial.print(morseToAlpha(getMorse()));
  } while(!changeWord());
  Serial.println();
}

char morseToAlpha(int* morse){
  //Converts morse code input into alpha-numeric output
  int i = 1;
  
  while(*morse != 2){
    i = (*(morse++) == 0) ? 2*i : 2*i + 1;
  }
  return alpha[i];
}

int* getMorse(){
  int* morsecode = calloc(sizeof(int), 5);
  int i = 0;
  
  //Encoding signals within morsecode
  while(!changeChar() && i <= 4){
    morsecode[i++] = readInput();
  }

  //Encoding unsent signals as 2
  while(i <= 4){
    morsecode[i++] = 2;
  }
  
  return morsecode;
}

int changeChar(){
  unsigned long start_time = millis(), end_time;

  while(millis() - start_time < 3*UNIT){
    if(digitalRead(INPUT_PIN) == 1){
      *starting_time = millis();
      return 0;
    }
  }

  return 1;
}

int changeWord(){
  unsigned long start_time = millis(), end_time;

  while(millis() - start_time < 4*UNIT){
    if(digitalRead(INPUT_PIN) == 1){
      *starting_time = millis();
      return 0;
    }
  }

  return 1;
}

int readInput(){
  unsigned long end_time;
  
  while(digitalRead(INPUT_PIN) == 1);

  end_time = millis();
  
  if(end_time - *starting_time < 3*UNIT) return 0;
  else return 1;
}

