#include <Adafruit_CircuitPlayground.h>

using namespace std;

struct node {
  int constants[9];
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
    to_add->constants[0] = a1;
    to_add->constants[1] = a2;
    to_add->constants[2] = a3;
    to_add->constants[3] = b1;
    to_add->constants[4] = b2;
    to_add->constants[5] = b3;
    to_add->constants[6] = c1;
    to_add->constants[7] = c2;
    to_add->constants[8] = c3;
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
int color_ctrls[9];

int sum_range(int low, int high, int buffer[32]) {
  int sum = 0;
  for (int i = low; i < high; i++) sum += buffer[i];
  return sum;
}

void loop() {
  if (modes.head == NULL) {
    //           r  g  b       vol       rang
    modes.insert(0, 0, 10,   0, 0, 0,   4, 0, 0); //bi
    modes.insert(10, 0, 10,   2, 0, 0,   0, 4, 0); //arizona ice t
    modes.insert(0, 0, 0,   6, 0, 0,   -6, 0, 0); //blood
    modes.insert(0, 0, 0,   0, 0, 0,   0, 0, 5); //bluEQ
    modes.insert(2, 2, 6,   3, 3, 3,   6, 0, 0); //E&T
    modes.insert(1, 1, 1,   3, 2, 1,   1, 2, 3); //all the colors
    curr = modes.head;
  }

  CircuitPlayground.speaker.enable(false);
  CircuitPlayground.mic.fft(buf); //db ranges from 50-100 generally
  //this for loop transforms our buffer into 10 vals which will be brightness of the different leds
  int adjustment = 30;
  ranges[0] = buf[0] / 10 * adjustment;
  ranges[1] = buf[0] / 10 * adjustment;
  ranges[2] = buf[1] / 8 * adjustment; 
  ranges[3] = (buf[2] + buf[3]) / 13 * adjustment;
  ranges[4] = sum_range(4, 7, buf) / 15 * adjustment;
  ranges[5] = sum_range(7, 12, buf) / 20 * adjustment;
  ranges[6] = sum_range(12, 17, buf) / 15 * adjustment;
  ranges[7] = sum_range(17, 22, buf) / 14 * adjustment;
  ranges[8] = sum_range(22, 27, buf) / 12 * adjustment;
  ranges[9] = sum_range(27, 31, buf) / 12 * adjustment;

  val = CircuitPlayground.mic.soundPressureLevel(10); //db ranges from 50-100 generally
  val = (val - 50) * (val - 50)/10; //noise above silence 0-50 
  CircuitPlayground.setBrightness(val);

  if (CircuitPlayground.leftButton()) {
    curr = modes.get_left();
    memcpy(color_ctrls, curr->constants, sizeof(curr->constants));
    delay(600);
  }

  if (CircuitPlayground.rightButton()) {
    curr = modes.get_right();
    memcpy(color_ctrls, curr->constants, sizeof(curr->constants));
    delay(600);
  }
  int red, green, blue;
  for (i = 0; i < 10; i++) {
    red = color_ctrls[0] + (val * color_ctrls[3]) / 10 + ranges[i] * color_ctrls[6];
    green = color_ctrls[1] + (val * color_ctrls[4]) / 10 + ranges[i] * color_ctrls[7];
    blue = color_ctrls[2] + (val * color_ctrls[5]) / 10 + ranges[i] * color_ctrls[8];
    Serial.println(ranges[i]);
    CircuitPlayground.setPixelColor(i, red, green, blue);
  }
}