#include <LiquidCrystal.h> 
#include <Keypad.h> 

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {

  {'1','2','3','+'},

  {'4','5','6','-'},

  {'7','8','9','*'},

  {'c','0','=','/'}

};
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte rowPins[ROWS] = { 7, 6, 5, 4};
byte colPins[COLS] = { 3, 2, 1, 0 };

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


boolean presentValue = false;
boolean next = false;
boolean final = false;
String num1, num2;
int answer=0,c=0;
char op;
boolean cpAns=false;
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  lcd.print("  Calculator"    );
  delay(3000);
  lcd.clear();
}

void loop(){
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'))
  {
    if (presentValue != true)
    {
      if(cpAns==true)
      {
        num1=num1;
       int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
      }else if(cpAns==false){
        num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
      }
    }
    else 
    {
       
      num2 = num2 + key;
      int numLength=0;
       numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }

  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
     // lcd.setCursor(15,0);
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      answer = num1.toInt() + num2.toInt();
    }
    else if (op == '-'){
      answer = num1.toInt() - num2.toInt();
    }
    else if (op == '*'){
      answer = num1.toInt() * num2.toInt();
    }
    else if (op == '/'){
      if(num2.toInt()==0){
        answer=0;
      } 
      else{
        answer = num1.toInt() / num2.toInt();
      }
      
    }    
     
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(answer);
     // delay(3000);
      lcd.noAutoscroll();
      //lcd.clear();
      presentValue = false;
      final = false;
      num1 = String(answer);
      num2 = "";
      op = ' ';
      cpAns=true;
  }
  else if (key != NO_KEY && key == 'c'){
    lcd.clear();
    presentValue = false;
    cpAns=false;
    final = false;
    num1 = "";
    num2 = "";
    answer = 0;
    op = ' ';
  }
}