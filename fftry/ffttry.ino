#include <Adafruit_CircuitPlayground.h>

using namespace std;

struct node {
	int constant_1;
	int constant_2;
	int constant_3;
  int range_1;
  int range_2;
  int range_3;
  int volume_1;
  int volume_2;
  int volume_3;
	node* next;
  node* prev;
};

class linked_list {
public:
    node* head;
    node* spot; 
	linked_list() {
    head = NULL;
    spot = NULL;
  }
	void insert(int a1, int a2, int a3, int b1, int b2, int b3, int c1, int c2, int c3) {
		node *to_add = new node();
		to_add->constant_1 = a1;
		to_add->constant_2 = a2;
		to_add->constant_3 = a3;
    to_add->range_1 = b1;
		to_add->range_2 = b2;
		to_add->range_3 = b3;
    to_add->volume_1 = c1;
    to_add->volume_2 = c2;
    to_add->volume_3 = c3;

		if (head == NULL) {
			to_add->next = to_add;
      to_add->prev = to_add;
      head = to_add;
      spot = head;
		}
		else {
			node* tail = head->prev;
      tail->next = to_add;
      to_add->prev = tail;
      to_add->next = head;
      head->prev = to_add;
	  }
  }
  node* get_right() {
    spot = spot->next;
    return spot;
  }

  node* get_left() {
    spot = spot->prev;
    return spot;
  }
};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

linked_list modes;
node* curr;
int val, num, i;
int ranges[10];
int buf[32];
int curr_mode[3] = {0, 0, 0};
int a1, a2, a3, b1, b2, b3, c1, c2, c3;

float power(float val, int pow) {
  int denom = 1;
  if (pow = 0) return 1;
  if (pow < 0) {
    for (int i = 0; i > pow; i--) denom *= val;
    return 1 / denom;
  }
  if (pow > 0) {
    for (int i = 0; i < pow; i++) denom *= val;
    return denom;
  }
}

void loop() {
  if (modes.head == NULL) {
    //           r  g  b    rangepow   volpow
    modes.insert(0, 0, 0,   1, 1, 1,   0, 0, 0);
    modes.insert(50, 0, 0,   1, 1, 1,   1, 1, 1);
    modes.insert(0, 50, 0,   1, 1, 1,   1, 1, 1);
    modes.insert(0, 0, 50,   1, 1, 1,   1, 1, 1);
    modes.insert(0, 0, 0,   1, 1, 1,   1, 1, 1);
    curr = modes.head;
  }

  CircuitPlayground.speaker.enable(false);
  CircuitPlayground.mic.fft(buf); //db ranges from 50-100 generally
  //this for loop transforms our buffer into 10 vals which will be brightness of the different leds
  ranges[0] = buf[0] / 12;
  ranges[1] = buf[0] / 10;
  ranges[2] = buf[1] / 8; 
  ranges[3] = (buf[2] + buf[3]) / 13;
  for (i = 4; i < 7; i++) num += buf[i];
  ranges[4] = num / 15;
  num = 0;
  for (i = 7; i < 12; i++) num += buf[i];
  ranges[5] = num / 20;
  num = 0;
  for (i = 12; i < 17; i++) num += buf[i];
  ranges[6] = num / 15;
  num = 0;
  for (i = 17; i < 22; i++) num += buf[i];
  ranges[7] = num / 10;
  num = 0;
  for (i = 22; i < 27; i++) num += buf[i];
  ranges[8] = num / 8;
  num = 0;
  for (i = 27; i < 31; i++) num += buf[i];
  ranges[9] = num / 8;
  num = 0;

  val = CircuitPlayground.mic.soundPressureLevel(10); //db ranges from 50-100 generally
  val = (val - 50) * (val - 50)/10; //noise above silence 0-50 
  CircuitPlayground.setBrightness(val);

  if (CircuitPlayground.leftButton()) {
    curr = modes.get_left();
    a1 = curr->constant_1;
		a2 = curr->constant_2;
		a3 = curr->constant_3;
    b1 = curr->range_1;
		b2 = curr->range_2;
		b3 = curr->range_3;
    c1 = curr->volume_1;
    c2 = curr->volume_2;
    c3 = curr->volume_3;
    delay(600);
  }

  if (CircuitPlayground.rightButton()) {
    curr = modes.get_right();
    a1 = curr->constant_1;
		a2 = curr->constant_2;
		a3 = curr->constant_3;
    b1 = curr->range_1;
		b2 = curr->range_2;
		b3 = curr->range_3;
    c1 = curr->volume_1;
    c2 = curr->volume_2;
    c3 = curr->volume_3;
    delay(600);
  }
  int red, green, blue;
  for (i = 0; i < 10; i++) {
    red = a1 + val * b1 + pow(ranges[i], c1);
    green = a2 + val * b2 + pow(ranges[i], c2);
    blue = a3 + val * b3 + pow(ranges[i], c3);
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }
}