#include<iostream>
#include<stdlib.h>
#include<vector>

// Classes and Objects, Access Specifiers,Encapsulation, Class Abstraction, Constructor ,
// Inheritence and Polymorphism (function overloading) concepts of OOPS are used.
// Semaphores are used to resolve producer-consumer problem
// stl (vector) is used to implement buffer queue

using namespace std;

class class1 //**Base Class created.
{
protected: int empty, semaphore, full, r; //**Access Specifiers implemented. Encapsulation implemented becuase protected variables are accessable only to derived and base class. 
public: vector<int> buffer; int bufsize = 5;

		class1()//**Constructor to initialize private variables.
		{
			empty = 5;
			semaphore = 1;
			full = 0;
		}

		virtual int produceitem()  //** Polymorphism - virtual function defined in base class.
		{
			r = rand() % 100 + 1; //function will return random integer between 1 and 100
			return r;
		}


		void wait(int S) //wait function will decrease semaphore value
		{
			while (S >= 0)
			{
				S--;
			}
		}

		void signal(int S)//signal functon will increase semaphore value
		{
			S++;
		}

		void input_buffer_item(int item) //items randomly generated are added to buffer and function also checks if buffer is full.
		{
			if (buffer.size() < bufsize)
			{
				cout << "item " << item << " is produced." << endl;
				buffer.push_back(item);
				cout << "Buffer size:" << buffer.size() << endl;
			}

			else
			{
				cout << "Buffer is full" << endl;
			}

		}

		void consume_buffer_item() //items randomly generated are removed from buffer and function also checks if buffer is empty.
		{
			if (buffer.size() == 0)
			{
				cout << "Buffer is empty " << endl;
			}

			else
			{
				cout << "item " << buffer.back() << " is deleted" << endl;
				buffer.pop_back();
			}
		}

};

class produce_consume : public class1 //** Inheritence is implemented
{
	
public:
	int produceitem()  //** Polymorphism - function defined in derived class (function overloading).
	{
		r = rand() % 10 + 1; //function will return random integer between 1 and 10
		return r;
	}

	void producer(int item)// items are added to buffer after making sure that buffer is available for input operation.
    {
	 class1 obj;
	 //int item; 
	 //item = obj.produceitem();
	 wait(empty);
	 wait(semaphore);
	 input_buffer_item(item);
	 signal(semaphore);
	 signal(full);
    }  

	void consumer()// items are removed from buffer after making sure that buffer is available for consume operation.
	{
	 wait(full);
	 wait(semaphore);
	 consume_buffer_item();
	 signal(semaphore);
	 signal(empty);
	}

};

int main()
{
	
	int choice = 0, item;
	cout << "Enter choice" << endl;
	produce_consume obj1;
	class1 *obj2 = &obj1;
	while (choice != 3)
	{
		cout << "1. Produce 2. Consume 3. Exit" << endl;
		cin >> choice;
		if (choice == 1)//** Data Abstraction, only essential items are displayed.
		{
			item = obj2->produceitem();//**Base class object calls Derived class method. 
		    obj1.producer(item); 
		}
		else if (choice == 2)
		{
			 obj1.consumer(); 
		}
	}
	return 0;
}
