#include "FCFSList.h"
#include "SortedList.h"
#include "Hospital.h"

#include <iostream>
class TestClass {
public:
    int id;         // ID of the item
    int priority;   // Priority of the item

    // Constructor
    TestClass(int id, int priority) : id(id), priority(priority) {}

    // Overload the < operator to compare priorities
    bool operator<(const TestClass& other) const {
        return priority < other.priority;
    }

    // Overload the << operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const TestClass& obj) {
        os << "ID: " << obj.id << ", Priority: " << obj.priority;
        return os;
    }
};

// These are the "secret" print files. Testers have these exact copies of these
// functions.
template<class T>
std::ostream& operator<<(std::ostream& stream, const FCFSList<T>& l)
{
    static const int MAX_PRINT = 100;

    if(l.head->next == NULL) stream << "Empty";
    //
    int printLimit = 0;
    for(const FCFSNode<T>* n = l.head->next; n != NULL; n = n->next)
    {
        stream << n->item;
        if(n->next != NULL) stream << " -> ";
        //
        printLimit++;
        if(printLimit == MAX_PRINT)
        {
            stream << std::endl << "***PrintLimitExceeded***" << std::endl;
            return stream;
        }
    }
    stream << std::endl;
    return stream;
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const FCFSList<T*>& l)
{
    static const int MAX_PRINT = 100;

    if(l.head->next == NULL) stream << "Empty";
    //
    int printLimit = 0;
    for(const FCFSNode<T*>* n = l.head->next; n != NULL; n = n->next)
    {
        stream << (*n->item);
        if(n->next != NULL) stream << " -> ";
        //
        printLimit++;
        if(printLimit == MAX_PRINT)
        {
            stream << std::endl << "***PrintLimitExceeded***" << std::endl;
            return stream;
        }
    }
    stream << std::endl;
    return stream;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const SortedList<T>& l)
{
    static const int MAX_PRINT = 100;

    stream << "Front to Back" << std::endl;
    if(l.head == NULL)
    {
        stream << "Empty" << std::endl;
    }
    else
    {
        int printLimit = 0;
        for(const SortedListNode<T>* n = l.head; n != NULL; n = n->next)
        {
            stream << *n->item;
            if(n->next != NULL) stream << " <-> ";
            //
            printLimit++;
            if(printLimit == MAX_PRINT)
            {
                stream << std::endl << "***PrintLimitExceeded***" << std::endl;
                return stream;
            }
        }
        stream << std::endl;
    }
    stream << "Back to Front" << std::endl;
    if(l.back == NULL)
    {
        stream << "Empty" << std::endl;
    }
    else
    {
        int printLimit = 0;
        for(const SortedListNode<T>* n = l.back; n != NULL; n = n->prev)
        {
            stream << *n->item;
            //
            if(n->prev != NULL) stream << " <-> ";
        }
        stream << std::endl;
        //
        printLimit++;
        if(printLimit == MAX_PRINT)
        {
            stream << std::endl << "***PrintLimitExceeded***" << std::endl;
            return stream;
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Hospital& h)
{
    stream << "***Reg Queue***" << std::endl;
    stream << h.regQueue << std::endl;

    stream << "***Exam Queue***" << std::endl;
    stream << h.examQueue << std::endl;

    stream << "***Events***" << std::endl;
    stream << h.eventQueue << std::endl;

    stream << "***Patients under Exam***" << std::endl;
    if(h.patientsInExam[0])
        stream << *(h.patientsInExam[0]) << std::endl;
    else
        stream << "Empty" << std::endl;
    stream << "--\n";
    if(h.patientsInExam[1])
        stream << *(h.patientsInExam[1]) << std::endl;
    else
        stream << "Empty" << std::endl;
    stream << "--";
    stream << std::endl;
    return stream;
}

// ========================= //
//           MAIN            //
// ========================= //
int main()
{
    // You can test using this main.
    /*
    FCFSList<int> newList;
    SortedList<Patient> newsorted;
    newList.Dequeue();
    newList.Enqueue(0);
    newList.Enqueue(3);
    //newList.Dequeue();
    newList.Enqueue(5);
    newList.Dequeue();

    FCFSList<Patient> newlist2,newlist3;
    
    newlist2.Enqueue(Patient(1,2));
    newlist2.Enqueue(Patient(3,4));
    newlist2.Enqueue(Patient(5,6));
    newlist3=newlist2;
    newlist3.Dequeue();

    //std::cout<<newsorted<<std::endl;
    std::cout << newlist3<<std::endl;
    std::cout << newlist2<<std::endl;

    */
   /*
   SortedList<Patient> newsorted;
   
   Patient *p1= new Patient(0,2);
   
   Patient* p2=new Patient(1,2);
   Patient* p3=new Patient(2,2);
   Patient* p4=new Patient(3,3);
   Patient* p5=new Patient(4,3);
   Patient* p6=new Patient(5,3);
   Patient* p7=new Patient(6,3);
   newsorted.InsertItem(p1);
  
   //newsorted.InsertItem(p2);
    newsorted.InsertItem(p3);
    newsorted.InsertItem(p4);
   newsorted.InsertItem(p5);
    newsorted.InsertItem(p6);
    newsorted.InsertItem(p7);
    SortedList<Patient> newsorted2;
    newsorted2=newsorted;
     Patient *p9=newsorted.RemoveFirstItem(3);
     newsorted.InsertItemPrior(p9);
   //newsorted.InsertItem(p8);
    //newsorted.InsertItem(p3);
     std::cout<<newsorted<<std::endl;
    newsorted.ChangePriorityOf(3,2);
    std::cout<<newsorted<<std::endl;
    //std::cout<<newsorted2;
    */
    Doctor d0(1);
   Doctor d1(3);
   Hospital hospital(d0,d1,2,20);
   hospital.AddPatient(1,2);
    hospital.AddPatient(2,3);
     hospital.AddPatient(3,0);

    std::cout<<hospital;
    EventResult eventresult1=hospital.DoSingleEventIteration();
    EventResult eventresult2=hospital.DoSingleEventIteration();
    EventResult eventresult3=hospital.DoSingleEventIteration();
    EventResult eventresult4=hospital.DoSingleEventIteration();
    EventResult eventresult5=hospital.DoSingleEventIteration();
    EventResult eventresult6=hospital.DoSingleEventIteration();
    EventResult eventresult7=hospital.DoSingleEventIteration();
    EventResult eventresult8=hospital.DoSingleEventIteration();
    EventResult eventresult9=hospital.DoSingleEventIteration();
    EventResult eventresult10=hospital.DoSingleEventIteration();
    EventResult eventresult11=hospital.DoSingleEventIteration();
    EventResult eventresult12=hospital.DoSingleEventIteration();
    EventResult eventresult13=hospital.DoSingleEventIteration();
    EventResult eventresult14=hospital.DoSingleEventIteration();
    EventResult eventresult15=hospital.DoSingleEventIteration();
    
    
    std::cout<<eventresult1;
    std::cout<<eventresult2;
    std::cout<<eventresult3;
    std::cout<<eventresult4;
    std::cout<<eventresult5;
    std::cout<<eventresult6;
    std::cout<<eventresult7;
    std::cout<<eventresult8;
    std::cout<<eventresult9;
    std::cout<<eventresult10;
    std::cout<<eventresult11;
    std::cout<<eventresult12;
    std::cout<<eventresult13;
    std::cout<<eventresult14;
    std::cout<<eventresult15;
    //std::cout<<eventresult4;
    //std::cout<<eventresult5;
     std::cout<<hospital;


}