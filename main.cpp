// Kit Pollinger
//  210 - Lab - 22 | Upgrade the DLL Class

//210 - DLL DEMO-2 File fix
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList
{
private:
    struct Node
    {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(int value)
    {
        Node* newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void push_front(int value)
    {
       Node* newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insert_after(int value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }
       Node* newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value)
    {
        if (!head)
            return; // Empty list
        Node* temp = head;
        while (temp && temp->data != value){
            temp = temp->next;
        }
        if (!temp) {
            return; // Value not found
        }
        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Deleting the head
        }
        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }

    // Delete Position
    void delete_pos(int position)
    {
        if (!head || position < 0)
            return; // Empty list or invalid position
        
        Node* temp = head;
        for (int i = 0; i < position && temp; i++)
        {
            temp = temp->next;
        }
        if (!temp){
            return;
        }
        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Delete head
        }
        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Delete Tail
            delete temp;
        }
    }

    // New Method to delete head node
    void pop_front()
    {
        if (!head) 
            return; // Empty list
        Node* temp = head;
        head = head->next;
        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr; // List empty
            delete temp;
        }
    }

    //New Method to delete tail node
    void pop_back(){
        if (!tail)
            return; // Empty list
        Node* temp = tail;
        head = tail->prev;
        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr; // List empty
            delete temp;
        }
    }

    void print()
    {
       Node* current = head;
        if (!current)
            return;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    void print_reverse()
    {
        Node* current = tail;
        if (!current){
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    
    //Destructor
    ~DoublyLinkedList()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main()
{
    DoublyLinkedList list;
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "\nTesting pop_front(), pop_back(), delete_val(), and delete_pos():\n";

    list.pop_front();
    cout << "after pop_front(): ";
    list.print();

    list.pop_back();
    cout << "After pop_back(): ";
    list.print();

    list.delete_val(50); //Delete value testing
    cout << "After delete_val(50): ";
    list.print();

    list.delete_pos(2);
    cout << "After deletePost(2): ";
    list.print();

    //Destructor will be called automatically when 'list' goes out

    cout << "List forward: ";
    list.print();
    return 0;
}