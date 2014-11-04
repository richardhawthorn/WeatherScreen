/*************************************************** 

 Display the weather, received over serial from an 
 electric imp, on the sparkfun colour lcd shield
 https://www.sparkfun.com/products/retired/9363
 
***************************************************/
#include <ColorLCDShield.h>

LCDShield lcd;

int buttonPins[3] = {3, 4, 5};

int temps[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int rain[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int hours[8] = {0, 3, 6, 9, 12, 15, 18, 21};

int barWidth = 14;
int chartStart = 12;

char string1[30];
char string2[30];
char string3[30];
char percent = '%';

#define LABELCOL  GREEN  // Labels for the chart
#define RAINCOL  RED  // Rain bars
#define TEMPCOL  BLUE  // Temp line
#define HEADER  WHITE  // Header
#define HEADERLINE  WHITE  // Header line
#define TEXT  WHITE  // Text
#define GRIDCOL  SLATE  // Grid lines 
#define BACKGROUND  BLACK  // Grid lines 

String content = "";
char character;

//height of date labels
int charHeight = 57;

void setup()
{
  
  Serial.begin(115200);
  
  /* Set up the button pins as inputs, set pull-up resistor */
  for (int i=0; i<3; i++)
  {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
  }
  
  /* Initialize the LCD, set the contrast, clear the screen */
  lcd.init(PHILIPS);
  lcd.contrast(-63);
  lcd.clear(BLACK);
  
}

void loop()
{

    int rainMax = 0;
    int tempMax = -99;
    int tempMin = 99;
    
    //work out max values
    for (int i=0; i <= 7; i++){
       rainMax = max(rainMax, rain[i]);
       tempMax = max(tempMax, temps[i]);
       tempMin = min(tempMin, temps[i]);
    }
    
    //construc text
    sprintf(string1, "   Somerville");
    sprintf(string2, "Temp: %.1dc-%.1dc", tempMin, tempMax);
    sprintf(string3, "Rain: %.1d%s", rainMax, percent);

    //clear lcd
    lcd.clear(BACKGROUND);
    
    //output text
    lcd.setStr(string1, 1, 1, HEADER, BACKGROUND);
    lcd.setLine(20, 1, 20, 130, HEADERLINE);
    lcd.setStr(string2, 20, 1, TEXT, BACKGROUND);
    lcd.setStr(string3, 35, 1, TEXT, BACKGROUND);
    
    //draw grid and charts
    drawGrid();
    drawLines();
    drawLabels();
    
    //delay
    for (int i = 0; i < 10000; i++){
      delay(1);
    }
    
}

void serialEvent() {
  
  String content = "";
  char character;
  int i = 0;
  
  // Update arrays when we receive data
    while (Serial.available() > 0) {
      character = Serial.read();
      content.concat(character);
      
      Serial.println(character);
      
      if (character == ','){
        if (i < 8){
          rain[i] = content.toInt();
        } else if (i < 16) {
          temps[i-8] = content.toInt();
        } else {
          hours[i-16] = content.toInt();
        } 
   
        content = "";
        i++;
        
      }
        
    }
    
}

void printNum(int num, int pos){
  
  if (num == 0){
     pos = (pos * barWidth) + 7 + chartStart;
     lcd.setLine(charHeight, pos, charHeight+4, pos, LABELCOL);
     lcd.setLine(charHeight, pos+2, charHeight+4, pos+2, LABELCOL);
     lcd.setLine(charHeight, pos, charHeight, pos+2, LABELCOL);   
     lcd.setLine(charHeight+4, pos, charHeight+4, pos+2, LABELCOL);
  } 
  
  if (num == 3){
     pos = (pos * barWidth) + 7 + chartStart;
     lcd.setLine(charHeight, pos+2, charHeight+4, pos+2, LABELCOL);
     lcd.setLine(charHeight, pos, charHeight, pos+2, LABELCOL);   
     lcd.setLine(charHeight+2, pos, charHeight+2, pos+2, LABELCOL); 
     lcd.setLine(charHeight+4, pos, charHeight+4, pos+2, LABELCOL);
  } 
  
  if (num == 6){
     pos = (pos * barWidth) + 7 + chartStart;
     lcd.setLine(charHeight, pos, charHeight+4, pos, LABELCOL); 
     lcd.setLine(charHeight+2, pos, charHeight+2, pos+2, LABELCOL); 
     lcd.setLine(charHeight+2, pos+2, charHeight+4, pos+2, LABELCOL);
     lcd.setLine(charHeight+4, pos, charHeight+4, pos+2, LABELCOL);
  }
  
  if (num == 9){
     pos = (pos * barWidth) + 7 + chartStart;
     lcd.setLine(charHeight, pos+2, charHeight+4, pos+2, LABELCOL);
     lcd.setLine(charHeight, pos, charHeight, pos+2, LABELCOL);   
     lcd.setLine(charHeight+2, pos, charHeight+2, pos+2, LABELCOL); 
     lcd.setLine(charHeight, pos, charHeight+2, pos, LABELCOL); 
    
  }
  
  if (num == 12){
     pos = (pos * barWidth) + 6 + chartStart;
     lcd.setLine(charHeight, pos, charHeight + 4, pos, LABELCOL); 
     
     lcd.setLine(charHeight, pos+2, charHeight, pos+4, LABELCOL); 
     lcd.setLine(charHeight, pos+4, charHeight+2, pos+4, LABELCOL); 
     lcd.setLine(charHeight+2, pos+2, charHeight+2, pos+4, LABELCOL); 
     lcd.setLine(charHeight+2, pos+2, charHeight+4, pos+2, LABELCOL);
     lcd.setLine(charHeight+4, pos+2, charHeight+4, pos+4, LABELCOL);
  }
  
  if (num == 15){
     pos = (pos * barWidth) + 6 + chartStart;
     lcd.setLine(charHeight, pos, charHeight + 4, pos, LABELCOL); 
     
     lcd.setLine(charHeight, pos+2, charHeight, pos+4, LABELCOL); 
     lcd.setLine(charHeight, pos+2, charHeight+2, pos+2, LABELCOL); 
     lcd.setLine(charHeight+2, pos+2, charHeight+2, pos+4, LABELCOL); 
     lcd.setLine(charHeight+2, pos+4, charHeight+4, pos+4, LABELCOL);
     lcd.setLine(charHeight+4, pos+2, charHeight+4, pos+4, LABELCOL);
  }
  
  if (num == 18){
     pos = (pos * barWidth) + 6 + chartStart;
     lcd.setLine(charHeight, pos, charHeight + 4, pos, LABELCOL); 
     
     lcd.setLine(charHeight, pos+2, charHeight, pos+4, LABELCOL); 
     lcd.setLine(charHeight, pos+2, charHeight+4, pos+2, LABELCOL); 
     lcd.setLine(charHeight+2, pos+2, charHeight+2, pos+4, LABELCOL); 
     lcd.setLine(charHeight, pos+4, charHeight+4, pos+4, LABELCOL);
     lcd.setLine(charHeight+4, pos+2, charHeight+4, pos+4, LABELCOL);
  }
  
  if (num == 21){
     pos = (pos * barWidth) + 6 + chartStart;
     lcd.setLine(charHeight, pos, charHeight, pos+2, LABELCOL); 
     lcd.setLine(charHeight, pos+2, charHeight+2, pos+2, LABELCOL); 
     lcd.setLine(charHeight+2, pos, charHeight+2, pos+2, LABELCOL); 
     lcd.setLine(charHeight+2, pos, charHeight+4, pos, LABELCOL);
     lcd.setLine(charHeight+4, pos, charHeight+4, pos+2, LABELCOL);
     
     lcd.setLine(charHeight, pos+4, charHeight + 4, pos+4, LABELCOL);
  }
  
}

void drawGrid(){
  
  //draw the horizontal lines
  for (int i=60; i <= 130; i = i + 10){
    lcd.setLine(i, 1, i, 130, GRIDCOL);
  }
  
  //draw the vertical lines
  for (int i=chartStart; i <= 128; i = i + barWidth){
    lcd.setLine(60, i, 130, i, GRIDCOL);
  }
    
}

void drawLines(){
  
  //draw the chart bars and lines
  for (int i=0; i <= 7; i++){
    
    //draw the rain bar
    lcd.setRect(100, chartStart + (i * barWidth), 100 - round(rain[i] / 2.5), (i * barWidth) + barWidth + chartStart, RAINCOL, RAINCOL);
    
    //draw the temp line
    if (i < 7){
      lcd.setLine(100 - round(temps[i]), (i * barWidth) + round(barWidth / 2) + chartStart, 100 - round(temps[i + 1]), (i * barWidth) + round(barWidth * 1.5) + chartStart, TEMPCOL);
    }
    
    printNum(hours[i], i);
  }
}

void drawLabels(){
  
  int height = 58;
  int posLeft = 2;
  int posRight = 100;
  
  //100
  writeNum(1, height, posRight, RAINCOL);
  writeNum(0, height, posRight+3, RAINCOL);
  writeNum(0, height, posRight+6, RAINCOL);
  
  height = height + 10;
  
  //30
  writeNum(3, height, posLeft+3, TEMPCOL);
  writeNum(0, height, posLeft+7, TEMPCOL);
  
  height = height + 10;
  
  //20
  writeNum(2, height, posLeft+3, TEMPCOL);
  writeNum(0, height, posLeft+7, TEMPCOL);
  
  height = height + 10;
  
  //10
  writeNum(1, height, posLeft+3, TEMPCOL);
  writeNum(0, height, posLeft+7, TEMPCOL);
  
  height = height + 10;
  
  //0
  writeNum(0, height, posLeft+7, TEMPCOL);
  
  height = height + 10;
  
  //10
  writeMinus(height, posLeft, TEMPCOL);
  writeNum(1, height, posLeft+3, TEMPCOL);
  writeNum(0, height, posLeft+7, TEMPCOL);
  
  height = height + 10;
  
  //20
  writeMinus(height, posLeft, TEMPCOL);
  writeNum(2, height, posLeft+3, TEMPCOL);
  writeNum(0, height, posLeft+7, TEMPCOL);
}


void writeNum(int num, int height, int width, char col){
  
  if (num == 1){
    lcd.setLine(height+1, width, height+1, width, col); 
    lcd.setLine(height, width+1, height+4, width+1, col);
    lcd.setLine(height+4, width, height+4, width+2, col);
  }
  
  if (num == 2){
    lcd.setLine(height, width, height, width+2, col); 
    lcd.setLine(height, width+2, height+2, width+2, col); 
    lcd.setLine(height+2, width, height+2, width+2, col); 
    lcd.setLine(height+2, width, height+4, width, col);
    lcd.setLine(height+4, width, height+4, width+2, col);
  }
  
  if (num == 3){
    lcd.setLine(height, width, height, width+2, col); 
    lcd.setLine(height, width+2, height+2, width+2, col); 
    lcd.setLine(height+2, width, height+2, width+2, col); 
    lcd.setLine(height+2, width+2, height+4, width+2, col);
    lcd.setLine(height+4, width, height+4, width+2, col);
  }
  
  if (num == 4){
    lcd.setLine(height+2, width, height+2, width+2, col); 
    lcd.setLine(height, width+2, height+4, width+2, col);
    lcd.setLine(height+1, width+1, height+1, width+1, col);
  }
  
  if (num == 5){
     lcd.setLine(height, width, height, width+2, col); 
     lcd.setLine(height, width, height+2, width, col); 
     lcd.setLine(height+2, width, height+2, width+2, col); 
     lcd.setLine(height+2, width+2, height+4, width+2, col);
     lcd.setLine(height+4, width, height+4, width+2, col); 
  }
  
  if (num == 6){
     lcd.setLine(height, width, height+4, width, col); 
     lcd.setLine(height+2, width, height+2, width+2, col); 
     lcd.setLine(height+2, width+2, height+4, width+2, col);
     lcd.setLine(height+4, width, height+4, width+2, col); 
  }
  
  if (num == 7){
    lcd.setLine(height, width, height, width+2, col); 
    lcd.setLine(height, width+2, height+1, width+1, col);
    lcd.setLine(height+2, width+1, height+4, width+1, col);
  }
  
  if (num == 8){
     lcd.setLine(height, width, height+4, width, col); 
     lcd.setLine(height, width, height, width+2, col); 
     lcd.setLine(height+2, width, height+2, width+2, col); 
     lcd.setLine(height, width+2, height+4, width+2, col);
     lcd.setLine(height+4, width, height+4, width+2, col); 
  }
  
  if (num == 9){
     lcd.setLine(height, width, height+2, width, col); 
     lcd.setLine(height, width, height, width+2, col); 
     lcd.setLine(height+2, width, height+2, width+2, col); 
     lcd.setLine(height, width+2, height+4, width+2, col);
  }
  
  if (num == 0){
     lcd.setLine(height, width, height+4, width, col); 
     lcd.setLine(height, width, height, width+2, col); 
     lcd.setLine(height, width+2, height+4, width+2, col);
     lcd.setLine(height+4, width, height+4, width+2, col); 
  }
  
}

void writeMinus(int height, int width, int col){
 lcd.setLine(height+2, width, height+2, width+1, col);  
}

