using namespace std;
struct node {
	int a;
	int b;
	int c;
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
	void insert(int a_val, int b_val, int c_val) {
		node *to_add = new node();
		to_add->a = a_val;
		to_add->b = b_val;
		to_add->c = c_val;
		if (head == NULL) {
			to_add->next = to_add;
			head = to_add;
      spot = head;
			return;
		}
		else {
			node * second = head->next;
			head->next = to_add;
			to_add->next = second;
			return;
		}
	}
  node* get_next() {
    spot = spot->next;
  }
};

