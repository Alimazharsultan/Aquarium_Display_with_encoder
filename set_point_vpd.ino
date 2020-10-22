void set_point_vpd() {
  Serial.println("Set vpd func");
  readchange();
  delay(500);

  if (0 <= counter && counter < 2)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 10%");
    vpds = 10;
  }
  if (2 <= counter && counter < 4)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 20%");
    vpds = 20;
  }

  if (4 <= counter && counter < 6)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 30%");
    vpds = 30;
  }
  if (6 <= counter && counter < 8)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 40%");
    vpds = 40;
  }
  if (8 <= counter && counter < 10)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 50%");
    vpds = 50;
  }
  if (10 <= counter && counter < 12)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 60%");
    vpds = 60;
  }
  if (12 <= counter && counter < 14)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 70%");
    vpds = 70;
  }
  if (14 <= counter && counter < 16)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 80%");
    vpds = 80;
  }
  if (16 <= counter && counter < 18)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 90%");
    vpds = 90;
  }
  if (18 <= counter && counter < 20)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" Set VPD = ");
    lcd.print(" 100%");
    vpds = 100;
  }

  //last_counter = counter;
  if (counter > 20)
  {
    counter = 0;
  }
  if (counter < 0)
  {
    counter = 20;
  }
  if (!digitalRead(button)) {
    if (vpds < actualvpd) {
      digitalWrite(relay, LOW);  //Turn on rley
      lcd.clear();
      lcd.setCursor(0, 2);
      lcd.print(" Turning on Humidifier");
      delay(500);
    } else {
      digitalWrite(relay, HIGH);  //Turn ff rley
      lcd.clear();
      lcd.setCursor(0, 2);
      lcd.print(" Turning off Humidifier");
      delay(500);
    }
    main_menu();
  }
  set_point_vpd();
}
