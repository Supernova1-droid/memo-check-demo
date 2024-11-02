#include "Hospital.h"

#include <cassert>

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    int enumIndex = (r.type < 0 || r.type > InvalidEvent) ? InvalidEvent : r.type;
    s << "Time[" << r.timePoint << "]: ";
    switch(enumIndex)
    {
        case DoctorQueueCheck:
            s << "Doctor(" << r.patientIdOrDoctorIndex
              << ") checked the patient queue." << std::endl;
            break;
        case RegistrationQueueEntrance:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") " << "is registering." << std::endl;
            break;
        case RegistrationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") registeration is complete." << std::endl;
            break;
        case ExaminationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") examination is completed." << std::endl;
            break;
        case InvalidEvent:
        default:
            s << "Invalid Event!" << std::endl;
            break;
    }

    return s;
}

int Doctor::ExamTimeOf(const Patient& patient) const
{
    // TODO: Implement
    /*
     return baselineExaminationTime*( MAX_PATIENT_PRIORTIY-patient.getPriority()+1);*/
      int patientPriority = patient.getPriority(); // Assuming Patient has a getPriority() method
    
    // Calculate the examination time using the given formula
    int examTime = (MAX_PATIENT_PRIORTIY - patientPriority + 1) * baselineExaminationTime;

    return examTime;
}


Hospital::Hospital(const Doctor& d0,
                   const Doctor& d1,
                   int rTime, int docTime)
    : currentTime(0)
    , registrationTime(rTime)
    , doctorCheckTime(docTime)
{
    doctors[0] = d0;
    doctors[1] = d1;
    patientsInExam[0] = NULL;
    patientsInExam[1] = NULL;
    
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 0));
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 1));
}

Hospital::~Hospital()
{
    // TODO: Implement
    Patient* patient;
    while(!regQueue.IsEmpty())
    {
        patient=regQueue.Dequeue();
        delete patient;
    }
    
}

void Hospital::AddPatient(int id, int priority)
{
    // TODO: Implement
    if(priority>MAX_PATIENT_PRIORTIY)return;
    Patient *newPatient=new Patient(id,priority);
     
    Event *newevent=new Event(currentTime,RegistrationQueueEntrance,newPatient);
    //Event(int timePointIn, EventType type,
    //      const Patient* patient);
    eventQueue.InsertItem(newevent);
    regQueue.Enqueue(newPatient);
   
}

EventResult Hospital::DoSingleEventIteration()
{
    Event *currentEvent=eventQueue.RemoveFirstItem();
    if(currentEvent->getType()==InvalidEvent)
    {   
        delete currentEvent;  
        EventResult eventResult={InvalidEvent,-1,currentTime};
        return eventResult;
    }
    EventResult eventResult;
    
    
    //set time as cırrent time
    currentTime=currentEvent->getTimePoint();

    EventType type=currentEvent->getType();
    int patientIdOrDoctorIndex;

    eventResult.type=type;
    eventResult.timePoint=currentTime;

    if(type==RegistrationQueueEntrance)
    {
        if(currentEvent->getPatient())
        {
            patientIdOrDoctorIndex=currentEvent->getPatient()->getId();
            eventResult.patientIdOrDoctorIndex=patientIdOrDoctorIndex;
            //Push new event to queue event
            Event *regEnd=new Event(currentTime+registrationTime,RegistrationEnd,currentEvent->getPatient());
            eventQueue.InsertItem(regEnd);
        }
    }
    else if(type==RegistrationEnd)
    {
        if(currentEvent->getPatient())
        {
              patientIdOrDoctorIndex=currentEvent->getPatient()->getId();
            eventResult.patientIdOrDoctorIndex=patientIdOrDoctorIndex;
            Patient *patient=regQueue.Dequeue();
            examQueue.InsertItem(patient);        
        }
    }
    else if(type==DoctorQueueCheck)
    {   
        patientIdOrDoctorIndex=currentEvent->getDoctorIndex();
      //  std::cout<<patientIdOrDoctorIndex<<std::endl;;
          //if(patientIdOrDoctorIndex==0){ std::cout<<"Queuecheck"<<"  ";  }
          //if(currentTime==20){std::cout<<"time is 20"<<" ";}
        eventResult.patientIdOrDoctorIndex=patientIdOrDoctorIndex;
         Patient *patient;
        if(examQueue.FirstItem()!=NULL)
        {   
            patient=examQueue.RemoveFirstItem();
            patientsInExam[patientIdOrDoctorIndex]=patient;

            int examtime=doctors[patientIdOrDoctorIndex].ExamTimeOf(*patient);
            Event* examEnd=new Event(examtime+currentTime,ExaminationEnd,patient);
            eventQueue.InsertItem(examEnd);
        }
        else
        { //std::cout<<currentEvent->getDoctorIndex()<<"examend ";
           // if(currentEvent->getDoctorIndex()==0){std::cout<<"no patent in queue index0";}
            Event *check=new Event(currentTime+doctorCheckTime,DoctorQueueCheck,currentEvent->getDoctorIndex());
            eventQueue.InsertItem(check);
        }
    }
    else if(type==ExaminationEnd)
    {  //if(currentTime==25)std::cout<<currentEvent->getDoctorIndex()<<"examend ";
        if(currentEvent->getPatient())
        {
            int doctorIndex;//=currentEvent->getDoctorIndex();
            if(patientsInExam[0]==currentEvent->getPatient())
            {
                std::cout<<"jkdk<<<<<";
                doctorIndex=0;
            
            }
            else if(patientsInExam[1]==currentEvent->getPatient())
            {
                std::cout<<"lkd";
                doctorIndex=1;
            }


         
            patientsInExam[doctorIndex]=NULL;
            eventResult.patientIdOrDoctorIndex=currentEvent->getPatient()->getId();
            if(examQueue.FirstItem())
            {
                Patient *patient=examQueue.RemoveFirstItem();
                
                patientsInExam[doctorIndex]=patient;

                int examTime=doctors[doctorIndex].ExamTimeOf(*patient);
                Event *examEnd=new Event(examTime+currentTime,ExaminationEnd,patient);
                eventQueue.InsertItem(examEnd);

            }
            else
            {
               if(patientsInExam[0]==currentEvent->getPatient())
            {
                
                doctorIndex=0;
            
            }
            else if(patientsInExam[1]==currentEvent->getPatient())
            {
               
                doctorIndex=1;
            }
           
             eventResult.patientIdOrDoctorIndex=currentEvent->getPatient()->getId();
             Event *check=new Event(currentTime+doctorCheckTime,DoctorQueueCheck,doctorIndex);
             eventQueue.InsertItem(check);
            }
        }
    }
    else{
        eventResult.type=InvalidEvent;
    }

    delete currentEvent;

   


    



    return eventResult;
}