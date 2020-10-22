void readchange() {
  Serial.println("Readchange function");
  rb = digitalRead(button);
  State = digitalRead(clk); // Reads the "current" state of the clock pin
  if (State != LastState) {
    if (digitalRead(data) != State) {
      counter ++;
    } else {
      counter --;
    }
    LastState = State; // Updates the previous state of the clock with the current state
  }
  Serial.println(counter);
}
