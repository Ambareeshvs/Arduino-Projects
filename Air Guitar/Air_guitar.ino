/*************************************************
* Public Constants
*************************************************/
//Defining the notes to the associated array
const int A_NOTE[]={ 55, 58, 110, 117, 220, 233 , 440 , 466 , 880, 932, 1760, 1865, 3520, 3729 };
const int B_NOTE[]={ 31, 62, 123, 247, 494, 988 , 1976, 3951  };
const int C_NOTE[]={ 33, 35, 65 , 69 , 131, 139 , 262 , 277 , 523, 554, 1047, 1109, 2093, 2217, 4186, 4435 };
const int D_NOTE[]={ 37, 39, 73 , 78 , 147, 156 , 294 , 311 , 587, 622, 1175, 1245, 2349, 2489, 4699, 4978 };
const int E_NOTE[]={ 41, 82, 165, 330, 659, 1319, 2637  };
const int F_NOTE[]={ 44, 46, 87 , 93 , 175, 185 , 349 , 370 , 698, 740, 1397, 1480, 2794, 2960 };
const int G_NOTE[]={ 49, 52, 98 , 104, 196, 208 , 392 , 415 , 784, 831, 1568, 1661, 3136, 3322 };
const int A_len=14, B_len=8, C_len=16, D_len=16, E_len=7, F_len=14, G_len=14;

//Defining pre-program constants
const int max_distance = 50;
const int min_distance = 10;

//Defining the pin confugration
const int speaker=2, trig=4, echo=3;
const int finger1=5, finger2=6, finger3=7, finger4=8; 

//Program variables
int distance = 0;
int code = 0;

//The tuneup() tunes the speaker to the required frequency. A delay of 120 milli seconds is made.
void tuneup(int note[], int note_len)
{
    int len = max_distance-min_distance;
    float gap = (len/note_len);
    int pos = (distance-min_distance)/gap;
    tone(speaker,note[pos]);
    delay(120);
}


void setup() 
{
    pinMode(finger1,INPUT_PULLUP);   pinMode(finger2,INPUT_PULLUP);
    pinMode(finger3,INPUT_PULLUP);   pinMode(finger4,INPUT_PULLUP);
    pinMode(trig,OUTPUT);     pinMode(echo,INPUT);
    pinMode(speaker,OUTPUT);
    tone(speaker,500);
    delay(1000);
    noTone(speaker);
    delay(1000);
    distance=0;   code=0;
    Serial.begin(9600);
    
}


void loop()
{
    //Reading the distance
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    int t=pulseIn(echo,HIGH);
    distance=(t*0.034)/2;
    Serial.print(distance);
    code=0; 
    
    
    if(distance>max_distance || distance<min_distance)
    {
        noTone(speaker); 
        return;
    }

    //read the fingers
    if(digitalRead(finger1)==LOW)
    {
        code=1;
    }
    if(digitalRead(finger2)==LOW)
    {
        code=code*10+2;
    }
    if(digitalRead(finger3)==LOW)
    {
        code=code*10+3;
    }
    if(digitalRead(finger4)==LOW)
    {
        code=code*10+4;
    }
  Serial.print("   ");
  Serial.println(code);
    //assign the musical note
    if(code==0 || code==1234)
    {
      tuneup(E_NOTE,E_len);
    }
    else if(code==1)
    {
      tuneup(A_NOTE,A_len);
    }
    else if(code==2)
    {
      tuneup(B_NOTE,B_len);
    }
    else if(code==3)
    {
      tuneup(C_NOTE,C_len);
    }
    else if(code==4)
    {
      tuneup(D_NOTE,D_len);
    }
    else if(code==12 ||code==13 ||code==14 ||code==23 ||code==24 ||code==34)
    {
      tuneup(F_NOTE,F_len);
    }
    else if(code==123 ||code==124 ||code==134 ||code==234)
    {
      tuneup(G_NOTE,G_len);
    }
}
