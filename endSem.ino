// 7 Segment Display Digits from 0-9
// Common Anode
int sevenSegDisplay[10][7] = {{0, 0, 0, 0, 0, 0, 1},  // 0
                              {1, 0, 0, 1, 1, 1, 1},  // 1
                              {0, 0, 1, 0, 0, 1, 0},  // 2
                              {0, 0, 0, 0, 1, 1, 0},  // 3
                              {1, 0, 0, 1, 1, 0, 0},  // 4
                              {0, 1, 0, 0, 1, 0, 0},  // 5
                              {0, 1, 0, 0, 0, 0, 0},  // 6
                              {0, 0, 0, 1, 1, 1, 1},  // 7
                              {0, 0, 0, 0, 0, 0, 0},  // 8
                              {0, 0, 0, 0, 1, 0, 0}};  // 9



// Signal Pins (R, Y, G)
int signals[4][3] = {{13, 12, 11},
                     {10, 9, 8},
                     {7, 6, 5},
                     {4, 3, 2}};

// Timer Pins

int digit_once_pins[7] = {31, 32, 33, 34, 35, 36, 37};
int digit_tens_pins[7] = {22, 23, 24, 25, 26, 27, 28};



int GREEN_TIME = 2;
int YELLOW_TIME = 5;
int signal_timer;
int SELECTED_COLOR;

void setup() {
  for(int i=2; i<=52; i++) {
    pinMode(i, OUTPUT);
  } 
}

void updateTimer(int newTime) {
  signal_timer = newTime;
}

void changeSignal(int selectedSignal, int color) {
  for(int i=0; i<4; i++) {
    for(int j=0; j<3; j++) {
      digitalWrite(signals[i][j], 0);
    }
  }
  for(int i=0; i<4; i++) {
    digitalWrite(signals[i][0], 1);
  }
  digitalWrite(signals[selectedSignal-1][0], 0);
  digitalWrite(signals[selectedSignal-1][color], 1);
}

void setSignalTimer() {
//  int n = signal_timer;
  int k = 0;
  if(SELECTED_COLOR == 2) {
    k = YELLOW_TIME+1;
  }
  while(signal_timer >= k) {
    int d_once = signal_timer%10;
    int d_tens = signal_timer/10;
    for(int j=0; j<7; j++) {
      digitalWrite(digit_once_pins[j], sevenSegDisplay[d_once][j]);
      digitalWrite(digit_tens_pins[j], sevenSegDisplay[d_tens][j]);
    }
    signal_timer--;
    delay(1000);
  }

}

int density[] = {26, 5, 12, 18};
int setTimerBasedOnDensity(int i) {
  // minimum = 15sec
  // maximum = 60sec
  // If density very low then also timer for 15 sec, if density is too high then also timer for 60 sec.
  // 15sec, 30sec, 45sec, 60sec
  
  int _time = 15;
  if(density[i-1] <= 7) {
    _time = 15;
  } else if(density[i-1] > 7 && density[i-1] <= 14) {
    _time = 30;
  } else if(density[i-1] > 14 && density[i-1] <= 21) {
    _time = 45;
  } else {
    _time = 60;
  }
  
  return _time;
}

void loop() {
  int signalTime;
   
  for(int i=1; i<=4; i++) {
    // Signal i GREEN
    changeSignal(i, 2);
    SELECTED_COLOR = 2;
    signalTime = setTimerBasedOnDensity(i);
    updateTimer(signalTime);
    setSignalTimer();

    // Signal i YELLOW
    changeSignal(i, 1);
    SELECTED_COLOR = 1;
    setSignalTimer();
  }
}
