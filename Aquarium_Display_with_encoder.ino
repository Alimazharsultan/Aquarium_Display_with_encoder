#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define clk 8
#define data 9
#define button 10
#define relay 11
int counter = 0;
int page = 1;
int Ready = 1;
int submenu = 0;
int last_counter = 0;
int State = 0;
int LastState = 0;
int pushed = 0;
int rb = 0;
float vpds = 0;
float actualvpd = 0;
unsigned long chrono = millis();
unsigned long offtime = 30000;
uint8_t arrow[8] = {0x0, 0x04 , 0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};
void setup() {
  lcd.init();                 //Init the LCD
  lcd.backlight();            //Activate backlight
  lcd.createChar(1, arrow);   //Create the arrow symbol
  lcd.home();                 //Home the LCD
  pinMode (clk, INPUT);
  pinMode (relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode (data, INPUT);
  pinMode (button, INPUT);
  LastState = digitalRead(clk);
  //Print the initial text. Delete these lines if you don't want that
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("(splash-boot screen)");
  lcd.setCursor(0, 1);
  lcd.print("VPD Controller ");
  lcd.setCursor(0, 2);
  lcd.print("Humidity ");
  lcd.setCursor(0, 3);
  lcd.print("Software Version 0.1");
  Serial.begin(9600);
}
void loop() {
  readchange(); //reset value of counter
  Serial.println("Inthe main loop");
  if ((millis() - chrono ) >= offtime) {
    lcd.clear();
    lcd.noBacklight();
  }
  if ((last_counter > counter) || (last_counter < counter)  || pushed) //Only print on the LCD when a step is detected or the button is pushed.
  {
    lcd.backlight();
    chrono = millis();
    Ready = 1;
    //First page of the menu
    if (submenu == 0) {
      if (0 <= counter && counter < 4) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("Actual Readings");
        lcd.setCursor(0, 1);
        lcd.print("Settings");
        lcd.setCursor(0, 2);
        lcd.print("Units");
        lcd.setCursor(0, 3);
        lcd.print("Aux");
        page = 1;
        if (pushed) {
          pushed = 0;
        }
      }
      if (4 <= counter && counter < 6) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Actual Readings");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("Settings");
        lcd.setCursor(0, 2);
        lcd.print("Units");
        lcd.setCursor(0, 3);
        lcd.print("Aux");
        page = 2;
        if (pushed)
        {
          pushed = 0;
        }

      }
      if (6 <= counter && counter < 8)
      {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Actual Readings");
        lcd.setCursor(0, 1);
        lcd.print("Settings");
        lcd.setCursor(0, 2);
        lcd.write(1);
        lcd.print("Units");
        lcd.setCursor(0, 3);
        lcd.print("Aux");
        page = 3;
        if (pushed)
        {
          pushed = 0;
        }

      }
      if (8 <= counter && counter < 10)
      {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Actual Readings");
        lcd.setCursor(0, 1);
        lcd.print("Settings");
        lcd.setCursor(0, 2);
        lcd.print("Units");
        lcd.setCursor(0, 3);
        lcd.write(1);
        lcd.print("Aux");
        page = 4;
        if (pushed)
        {
          pushed = 0;
        }

      }
    }//submenu = 0;
    //actual reading menu
    if (submenu == 1)
    {
      if (0 <= counter && counter < 2)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print(" act vpd kPa");
        lcd.setCursor(0, 1);
        lcd.print("act rh - %");
        lcd.setCursor(0, 2);
        lcd.print("leaf temp -C");
        lcd.setCursor(0, 3);
        lcd.print("amb temp -C");
        page = 1;
        pushed = 0;
      }
      if (2 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" act vpd kPa");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("act rh - %");
        lcd.setCursor(0, 2);
        lcd.print("leaf temp -C");
        lcd.setCursor(0, 3);
        lcd.print("amb temp -C");
        page = 2;
        pushed = 0;
      }

      if (4 <= counter && counter < 6)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" act vpd kPa");
        lcd.setCursor(0, 1);
        lcd.print("act rh - %");
        lcd.setCursor(0, 2);
        lcd.write(1);
        lcd.print("leaf temp -C");
        lcd.setCursor(0, 3);
        lcd.print("amb temp -C");
        page = 3;
        pushed = 0;
      }
      if (6 <= counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" act vpd kPa");
        lcd.setCursor(0, 1);
        lcd.print("act rh - %");
        lcd.setCursor(0, 2);
        lcd.print("leaf temp -C");
        lcd.setCursor(0, 3);
        lcd.write(1);
        lcd.print("amb temp -C");
        page = 4;
        pushed = 0;
      }
      if (8 <= counter && counter < 10)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print(" Air Pressure kPa");
        lcd.setCursor(0, 1);
        lcd.print("Aux Reading(CO2)ppm");
        lcd.setCursor(0, 2);
        lcd.print("DW point -C");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 5;
        pushed = 0;
      }
      if (10 <= counter && counter < 12)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Air Pressure kPa");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("Aux Reading(CO2)ppm");
        lcd.setCursor(0, 2);
        lcd.print("DW point -C");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 6;
        pushed = 0;
      }
      if (12 <= counter && counter < 14)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Air Pressure kPa");
        lcd.setCursor(0, 1);
        lcd.print("Aux Reading(CO2)ppm");
        lcd.setCursor(0, 2);
        lcd.write(1);
        lcd.print("DW point -C");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 7;
        pushed = 0;
      }
      if (14 <= counter && counter < 16)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Air Pressure kPa");
        lcd.setCursor(0, 1);
        lcd.print("Aux Reading(CO2)ppm");
        lcd.setCursor(0, 2);
        lcd.print("DW point -C");
        lcd.setCursor(0, 3);
        lcd.write(1);
        lcd.print("<<Back");
        page = 8;
        pushed = 0;
      }
    }//submenu = 1;
    //Settings menu
    if (submenu == 2)
    {
      if (0 <= counter && counter < 2)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("Setpoint vpd 1.0");
        lcd.setCursor(0, 1);
        lcd.print("Min rh 45%");
        lcd.setCursor(0, 2);
        lcd.print("Max rh 85% ");
        lcd.setCursor(0, 3);
        lcd.print("Hysteresis 3%");

        page = 1;
        pushed = 0;
      }

      if (2 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint vpd 1.0");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("Min rh 45%");
        lcd.setCursor(0, 2);
        lcd.print("Max rh 85% ");
        lcd.setCursor(0, 3);
        lcd.print("Hysteresis 3%");
        page = 2;
        pushed = 0;
      }

      if (4 <= counter && counter < 6)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint vpd 1.0");
        lcd.setCursor(0, 1);
        lcd.print("Min rh 45%");
        lcd.setCursor(0, 2);
        lcd.write(1);
        lcd.print("Max rh 85% ");
        lcd.setCursor(0, 3);
        lcd.print("Hysteresis 3%");
        page = 3;
        pushed = 0;
      }

      if (6 <= counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint vpd 1.0");
        lcd.setCursor(0, 1);
        lcd.print("Min rh 45%");
        lcd.setCursor(0, 2);
        lcd.print("Max rh 85% ");
        lcd.setCursor(0, 3);
        lcd.write(1);
        lcd.print("Hysteresis 3%");
        page = 4;
        pushed = 0;
      }

      if (8 <= counter && counter < 10)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print(" <<Back");
        page = 5;
        pushed = 0;
      }
    }//submenu = 2;
    //units menu
    if (submenu == 3)
    {
      if (0 <= counter && counter < 2)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("Units temp C/F");
        lcd.setCursor(0, 1);
        lcd.print("Units pressure");
        lcd.setCursor(0, 2);
        lcd.print("   kpa/hpa/mmg");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 1;
        pushed = 0;
      }
      if (2 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Units temp C/F");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("Units pressure");
        lcd.setCursor(0, 2);
        lcd.print("   kpa/hpa/mmg");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 2;
        pushed = 0;
      }
      if (4 <= counter && counter < 6)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Units temp C/F");
        lcd.setCursor(0, 1);
        lcd.print("Units pressure");
        lcd.setCursor(0, 2);
        lcd.print("kpa/hpa/mmg");
        lcd.setCursor(0, 3);
        lcd.write(1);
        lcd.print("<<Back");
        page = 3;
        pushed = 0;
      }
    }//submenu = 3;

    //Aux Menu
    if (submenu == 4)
    {
      if (0 <= counter && counter < 2)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write(1);
        lcd.print("ConnectCO2Sensor");
        lcd.setCursor(0, 1);
        lcd.print("Connect Data logger");
        lcd.setCursor(0, 2);
        lcd.print("ConnectC02controller");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 1;
        pushed = 0;
      }

      if (2 <= counter && counter < 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ConnectCO2Sensor");
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print("Connect Data logger");
        lcd.setCursor(0, 2);
        lcd.print("ConnectC02Controller");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 2;
        pushed = 0;
      }

      if (4 <= counter && counter < 6)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ConnectCO2Sensor");
        lcd.setCursor(0, 1);
        lcd.print("Connect Data logger");
        lcd.setCursor(0, 2);
        lcd.write(1);
        lcd.print("ConnectC02controller");
        lcd.setCursor(0, 3);
        lcd.print("<<Back");
        page = 3;
        pushed = 0;
      }

      if (6 <= counter && counter < 8)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Connect CO2Sensor");
        lcd.setCursor(0, 1);
        lcd.print("Connect Data logger");
        lcd.setCursor(0, 2);
        lcd.print("ConnectC02controller");
        lcd.setCursor(0, 3);
        lcd.write(1);
        lcd.print("<<Back");
        page = 4;
        pushed = 0;
      }
    }//submenu = 4;
  }//end of the MENU prints on the LCD
  last_counter = counter; //Save the value of the last state
  //Now we detect when we push the button
  if (!digitalRead(button))
  {
    if (submenu == 1)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        act_vpd();
      }
      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        act_rh();
      }
      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        leaf_temp();
      }
      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        amb_temp();
      }
      if (page == 5)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        air_pressure();
      }
      if (page == 6)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        aux_reading();
      }
      if (page == 7)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        DW_point();
      }
      if (page == 8)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        main_menu();
      }
    }//end of submenu 1

    if (submenu == 2)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Set Point Vpd");
        lcd.setCursor(0, 1);
        lcd.print("Selected");
        delay(500);
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        set_point_vpd();
      }
      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        min_rh();
      }
      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        max_rh();
      }
      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        Hysteresis();
      }
      if (page == 5)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        main_menu();
      }
    }//end of submenu 1
    if (submenu == 3)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 1;
        pushed = 0;
        Ready = 0;
        units_temp();
      }
      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        units_pres();
      }
      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        main_menu();
      }

    }//end of submenu 1
    if (submenu == 4)
    {
      if (page == 1)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        connect_CO2_sensor();
      }

      if (page == 2)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        connect_logger();
      }

      if (page == 3)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        connect_CO2_controller();
      }

      if (page == 4)
      {
        submenu = 0;
        counter = 0;
        pushed = 0;
        Ready = 0;
        main_menu();
      }
    }//end of submenu 1
    if (submenu == 0 && Ready == 1)
    {
      if (page == 1)
      {
        submenu = 1;
        counter = 0;
        pushed = 1;
        delay(500);
      }

      if (page == 2)
      {
        submenu = 2;
        counter = 0;
        pushed = 1; delay(500);
      }

      if (page == 3)
      {
        submenu = 3;
        counter = 0;
        pushed = 1; delay(500);
      }

      if (page == 4)
      {
        submenu = 4;
        counter = 0;
        pushed = 1; delay(500);
      }
    }//end of submenu 0

  }
  //Add limit for the counter. Each line of the menu has 5 points. Since my menu has 4 lines the maximum counter will be from 0 to 20
  //If you add more lines for the menu, increase this value
  if (counter > 20)
  {
    counter = 0;
  }
  if (counter < 0)
  {
    counter = 20;
  }

}
