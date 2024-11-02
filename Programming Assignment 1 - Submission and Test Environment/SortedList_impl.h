#ifndef SORTED_LIST_IMPL_H
#define SORTED_LIST_IMPL_H


template<class T>
SortedListNode<T>::SortedListNode(T* itemIn,
                                  SortedListNode* nextNodeIn,
                                  SortedListNode* prevNodeIn)
    : item(itemIn)
    , next(nextNodeIn)
    , prev(prevNodeIn)
{}

template<class T>
SortedList<T>::SortedList()
    : head(NULL)
    , back(NULL)
{}

template<class T>
SortedList<T>::SortedList(const SortedList& other)
    : head(NULL)
    , back(NULL)
{
    // TODO: Implement
    if(other.head!=NULL)
    {  
      T* i=new T(*other.head->item);         
      head=new SortedListNode<T>(i);
      SortedListNode<T>* current=head;
      SortedListNode<T>* othercp=other.head->next;
      back=head;
      while(othercp!=NULL)
      { 
        i=new T(*othercp->item);  
        current->next=new SortedListNode<T>(i);
        current->next->prev=current;
        back=current->next;
        current=current->next;
        othercp=othercp->next;
      }  
    }
}

template<class T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{
    if(this!=&other)
    {
        SortedListNode<T>* tmp;
        SortedListNode<T>* current=head;
        while (current!=NULL)
        {
            tmp=current;
            current=current->next;
            delete tmp->item;
            delete tmp;
            
        }
        back=NULL;
        
        
        if(other.head==NULL)
        {
            head=NULL;
            back=NULL;
        }
        else
        {   
            T *i=new T(*other.head->item);
            head=new SortedListNode<T>(i);
            current=head;
            SortedListNode<T>* othercp=other.head->next;
            //1->2->3->4
            //1<->2<->3<->4
            // 3

            //1
            //1
            back=head;
            while(othercp!=NULL)
            {   
                i=new T(*othercp->item);
                current->next=new SortedListNode<T>(i);
                current->next->prev=current;
                back=current->next;
                current=current->next;
                othercp=othercp->next;
            }
            back=current;
            back->next=NULL;

        }
        
        
    }
    return *this;
   
}

template<class T>
SortedList<T>::~SortedList()
{
    // TODO: Implement
    SortedListNode<T>* tmp=NULL;
    while(head!=NULL)
    {
        tmp=head;
        head=head->next;
        delete tmp->item;
        delete tmp;
    }
    back=NULL;
    head=NULL;
}

template<class T>
void SortedList<T>::InsertItem(T* i)
{
    if(head==NULL)
    {   //
        head=new SortedListNode<T>(i);
        back=head;
        return ;
        //1
    }
    else
    {   //1 

        if(*i < *head->item)
        {
            SortedListNode<T>* tmp=new SortedListNode<T>(i);
            tmp->next=head;
            head->prev=tmp;
            head=tmp;
            return;
        }
        else
        {   
        //1->2->4

        //1->2->2->4
        //       2
            
            //10<->20
            SortedListNode<T>* current=head;
            while(current->next && *current->next->item < *i)
            {   
                current=current->next;
            }
            if(current->next && *current->next->item==*i)
            {
               while(current->next && *current->next->item==*i)
               {
                   current=current->next;
               }
            }
            
            
            if(current->next==NULL)
            {
                current->next=new SortedListNode<T>(i);
                current->next->prev=current;
                back=current->next;
            }
            else
            {  
                //10<->20
                //     |
                
                //10<->10 ->20
                
                SortedListNode<T>* tmp=current->next;
                current->next=new SortedListNode<T>(i);
                current->next->prev=current;
                current->next->next=tmp;
                tmp->prev=current->next;
                
                /*
                SortedListNode<T>* tmp=new SortedListNode<T>(i);
                tmp->prev=current;
                tmp->next=current->next;
                current->next=tmp;
                tmp->next->prev=tmp;*/

            }
            

        }
        

    }
}

template<class T>
void SortedList<T>::InsertItemPrior(T* i)
{
    // TODO: Implement
    SortedListNode<T>* newNode=new SortedListNode<T>(i);
    if(head==NULL)
    {
        head=back=newNode;
        return ;
    }
   
    if(*i < *head->item || *i == *head->item)
    {
        newNode->next=head;
        head->prev=newNode;
        head=newNode;
        return;
    }

    SortedListNode<T>* current=head->next;
    while(current && *current->item < *i )
    {
        current=current->next;
    }
     //10->11->12
     //      \ /
     if(current)
     {  
        newNode->prev=current->prev;
        newNode->next=current;
        SortedListNode<T>* prevNode=current->prev;
        prevNode->next=newNode;
        newNode->next->prev=newNode;

        
     }
     else
     {
        
        back->next=newNode;
        newNode->prev=back;
        back=newNode;
     }
}

template<class T>
T* SortedList<T>::RemoveFirstItem()
{
    // TODO: Implement
    if(head!=NULL)
    {   
        SortedListNode<T>* tmp=head;
        head=head->next;
        if(head==NULL)
        {
            back=NULL;
        }
        else
        {
            head->prev=NULL;
        }
        
        T *i=tmp->item;
        delete tmp;
        return i;
    }
    return NULL;
}

template<class T>
T* SortedList<T>::RemoveFirstItem(int priority)
{
    // TODO: Implement
    
    
    SortedListNode<T> *current=head,*tmp=NULL;
    while(current!=NULL)
    {
        if(*current->item==priority)
        {   
            //1<->2<->3<->4
            //1->2<->4
            tmp=current;
            
            if(current->prev!=NULL)
            {
                SortedListNode<T> *nextNode=current->next;
                SortedListNode<T>* prevNode=current->prev;
                prevNode->next=nextNode;
                nextNode->prev=prevNode;
                
            }
            else
            {
                //1<->2<->3
                //1
                if(current->next==NULL)
                {
                    head=back=NULL;
                }
                else
                {
                    
                    head=current->next;
                    head->prev=NULL;
                    
                }
            }
            break;
            
        }
        current=current->next;
    }
    if(tmp!=NULL)
    {
        T *i=tmp->item;
        
        delete tmp;
        return i;
    }
    return NULL;
   
}

template<class T>
T* SortedList<T>::RemoveLastItem(int priority)
{
    // TODO: Implement
    //1->2->2->3
    
    if(head!=NULL)
    {   
        
        SortedListNode<T>* current=back,*tmp=NULL;
        
        while(current!=NULL)
        {
            if(*current->item==priority)
            {
                
                //1->2->2->2->3
                //2->3
                //3->2
                
            
                  //1->2->
                    tmp=current;
                    if(current->prev==NULL)
                    {
                        
                        if(current->next==NULL)
                        {
                            head=back=NULL;
                        }
                        else
                        { //1->2->3
                            head=head->next;
                            head->prev=NULL;
                        }
                        
                    }
                    else
                    { //1->2->2->3
                        //1->2->3->4
                        if(current->next==NULL)
                        {
                            back=back->prev;
                            back->next=NULL;
                        }
                        else{
                        SortedListNode<T>* prevNode=current->prev;
                        SortedListNode<T>* nextNode=current->next;
                        prevNode->next=nextNode;
                        nextNode->prev=prevNode;
                        }
                        
                    }
                
                
                break;
                
                
                
            }
            current=current->prev;
        }
        if(tmp!=NULL)
        {
            T *i=tmp->item;
            delete tmp;
            return i;
        }
        
    }
    
    //1->2->3->4
    
    
    return NULL;
}

template<class T>
const T* SortedList<T>::FirstItem() const
{
    return (head) ? head->item : NULL;
}

template<class T>
const T* SortedList<T>::LastItem() const
{
    return (back) ? back->item : NULL;
}

template<class T>
bool SortedList<T>::IsEmpty() const
{
    return head == NULL;
}

template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority)
{
    // TODO: Implement
    //1->2-3->4;
    if(head==NULL)
    {
        return;
    }
    if(priority==newPriority)
    {
        return;
    }
    SortedListNode<T>* current=head;
    SortedListNode<T>* subListHead=NULL,*subListTail,*subListHead2;
    while(current)
    {   
        if(*current->item==priority)
        {   //1-2-2-4-5
            //1-2-2
            subListHead=current;
            subListHead->item->setPriority(newPriority);
            
            while(current->next && *current->next->item==priority)
            {   
                current->item->setPriority(newPriority);
                current=current->next;
            }
            current->item->setPriority(newPriority);
            subListTail=current;
            
            subListHead2=current->next;
            
            //1-1-1
            //1-1-2
            //1
            //1-2
            if(subListHead==head)
            {
                head=subListHead2;
                if(head==NULL)
                {
                    back=NULL;
                }
                else
                {
                    head->prev=NULL;
                }
            }
            //2-3-3-3
            //2-3
            //1-2-3-3-4
            else
            {
               subListHead->prev->next=subListHead2;
               if(subListHead2!=NULL)
               {
                   subListHead2->prev=subListHead->prev;
               }
               else
               {
                   back=subListHead->prev;
                   back->next=NULL;
                   
               }
               
               
            }
            
            
            
           
            //adding new linkedlist
            
            
            //1-2-3
            //1
         break;   
            
        }
        current=current->next;
    }
    if(subListHead==NULL)
    {
        return;
    }
    subListHead->prev=NULL;
    subListTail->next=NULL;
    
    current=head;
    if(head==NULL)
    {
        head=subListHead;
        head->prev=NULL;
        back=subListTail;
        subListTail->next=NULL;
    }
    
    while(current && *current->item < newPriority)
    {
        current=current->next;
    }
    if(current==NULL)
    {   
       back->next=subListHead;
       back=subListTail;
       back->next=NULL;
    }
    else
    {   if(*current->item==newPriority)
        {
            if(newPriority>priority)
            {
                //add to left
                //   2-2-3-3
                if(current==head)
                {   
                    subListTail->next=head;
                    head->prev=subListTail;
                    subListHead->prev=NULL;
                    head=subListHead;
                    
                }
                else
                {
                    //1-2-2-2-3
                    // 2-2
                    subListHead->prev=current->prev;
                    current->prev->next=subListHead;
                    //1-2-2 2-2-3
                    subListTail->next=current;
                    current->prev=subListTail;
                    
                }
            }
            else
            {
                //add to right
                
                //2-2-3
                //2-2-
                while(current->next && *current->next->item==newPriority)
                {
                    current=current->next;
                }
                
                if(current->next==NULL)
                {
                    //2-2-2->null
                    back->next=subListHead;
                    subListHead->prev=back;
                    back=subListTail;
                    back->next=NULL;
                }
                else
                {
                    //2-2-3-3
                    //   2-2
                    subListTail->next=current->next;
                    current->next->prev=subListTail;
                    subListHead->prev=current;
                    current->next=subListHead;
                    
                }
                
            }
        }
        else
        {
            if(current==head)
                {   
                    subListTail->next=head;
                    head->prev=subListTail;
                    subListHead->prev=NULL;
                    head=subListHead;
                    
                }
                else
                {
                    //1-2-2-2-3
                    // 2-2
                    subListHead->prev=current->prev;
                    current->prev->next=subListHead;
                    //1-2-2 2-2-3
                    subListTail->next=current;
                    current->prev=subListTail;
                    
                }
        }
        //1-3-4-6
        //4-4-4-5
        /*if(current==head)
        {   
            if(*current->item==newPriority)
            {
                if(newPriority>priority)
                {
                    //add to left
                    subListTail->next=head;
                    head->prev=subListTail;
                    subListHead->prev=NULL;
                    head=subListHead;
                }
                else
                {
                    //add to right
                     SortedListNode<T>*prevNode=current;
                     SortedListNode<T>*nextNode=current->next;
                    if(nextNode==NULL)
                    {
                        //1
                        head->next=subListHead;
                        subListHead->prev=head;
                        back=subListTail;
                        back->next=NULL;
                    }
                    else
                    {
                        //1-2
                        prevNode->next=subListHead;
                        subListHead->prev=head;
                        
                        subListTail->next=nextNode;
                        nextNode->prev=subListTail;
                    }
                   
                }
            }
            subListTail->next=head;
            head->prev=subListTail;
            subListHead->prev=NULL;
            head=subListHead;
        }
        else
        {   
            if(*current->item==newPriority)
            {
                //// 1-3-------4-6
                ////.    4---4
                SortedListNode<T>*prevNode;
                SortedListNode<T>*nextNode;
                if(newPriority>priority)
                {   //add to left
                    prevNode=current->prev;
                    nextNode=current; 
                    subListHead->prev=prevNode;
                    prevNode->next=subListHead;
            
                    subListTail->next=nextNode;
                    nextNode->prev=subListTail;
                }
                else
                {   //1->2->3->4
                    //1->2->3->4->5
                    prevNode=current;
                    nextNode=current->next;
                    if(nextNode==NULL)
                    {
                        prevNode->next=subListHead;
                        subListHead->prev=prevNode;
                        subListTail->next=nextNode;
                        back=subListTail;
                        back->next=NULL;
                    }
                    else
                    {
                        subListHead->prev=prevNode;
                        prevNode->next=subListHead;
            
                        subListTail->next=nextNode;
                        nextNode->prev=subListTail;
                        
                    }
                }
               
                
            }
            else
            {
              
               SortedListNode<T>*prevNode;
                SortedListNode<T>*nextNode;
                   //add to left
                prevNode=current->prev;
                nextNode=current; 
                subListHead->prev=prevNode;
                prevNode->next=subListHead;
            
                subListTail->next=nextNode;
                nextNode->prev=subListTail;
                
            }
        }
        */
    }
    
    

}

template<class T>
void SortedList<T>::Split(SortedList& listLeft,
                          SortedList& listRight,
                          int priority)
{
    assert(listLeft.head == NULL);
    assert(listRight.head == NULL);
    if(head==NULL)
    {
        return;
    }
    // TODO: Implement
   
    SortedListNode<T>* current=head;
    while(current && *current->item <priority)
    {   
        T *i=new T(*current->item);
        listLeft.InsertItem(i);
        current=current->next;
    }
    
    while(current)
    {   
        T *i=new T(*current->item);
        listRight.InsertItem(i);
        current=current->next;
    }
   
   
   SortedListNode<T>* tmp=NULL;
    while(head!=NULL)
    {
        tmp=head;
        head=head->next;
        delete tmp->item;
        delete tmp;
    }
   
    head=NULL;
    back=NULL;
    
}

template<class T>
SortedList<T> SortedList<T>::Merge(const SortedList& list0,
                                   const SortedList& list1)
{   
    SortedList<T> newSortedList;
    
   // TODO: Implement
   if(!list0.head) 
   {    
       newSortedList=list0;
       return newSortedList;
   }
   if(!list1.head)
   {
        newSortedList=list1;
        return newSortedList;
   }
   SortedListNode<T>* l0=list0.head;
   SortedListNode<T>* l1=list1.head;
   SortedListNode<T>* tmp;
   T *i;
   if(*list0.head->item < *list1.head->item ||*list0.head->item == *list1.head->item)
   {    
       i=new T(*list0.head->item);
       tmp=new SortedListNode<T>(i);
       l0=l0->next;
   }
   else
   {    
       i=new T(*list1.head->item);
       tmp=new SortedListNode<T>(i);
       l1=l1->next;
   }
   
   newSortedList.head=tmp;
   
    SortedListNode<T>* current=newSortedList.head;
    //SortedListNode<T>* l0=list0.head->next;
    //SortedListNode<T>* l1=list1.head->next;
    while(l0 && l1)
    {
        if(*l0->item < *l1->item ||*l0->item== *l1->item)
        {
             i=new T(*l0->item);
             tmp=new SortedListNode<T>(i);
             l0=l0->next;
        }
        else
        {
            i=new T(*l1->item);
            tmp=new SortedListNode<T>(i);
            l1=l1->next;
        }
        current->next=tmp;
        tmp->prev=current;
        current=tmp;
    }
   
   while (l0) {
        current->next = new SortedListNode<T>(new T(*l0->item));
        current->next->prev=current;
        current = current->next;
        l0 = l0->next;
    }

    // If there are remaining elements in list1
    while (l1) {
        current->next = new SortedListNode<T>(new T(*l1->item));
        current->next->prev=current;
        current = current->next;
        l1 = l1->next;
    }
    newSortedList.back=current;
    newSortedList.back->next=NULL;
   
   return newSortedList;
   
}

#endif