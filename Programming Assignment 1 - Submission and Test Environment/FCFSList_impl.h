#ifndef FCFS_LIST_IMPL_H
#define FCFS_LIST_IMPL_H

template<class T>
FCFSNode<T>::FCFSNode(const T& t, FCFSNode* node)
    : item(t)
    , next(node)
{}

// ============================ //
template<class T>
FCFSList<T>::FCFSList()
    : head(NULL)
{
    // Using a dummy node
    head = new FCFSNode<T>(T());
}

template<class T>
FCFSList<T>::FCFSList(const FCFSList& other)
{
   
    head=new FCFSNode<T>(T(),NULL);

    if (other.head->next!=NULL ) {   
        FCFSNode<T>* current=head;
        FCFSNode<T>* othercp=other.head->next;

        while (othercp!=NULL) {
            current->next=new FCFSNode<T>(othercp->item,NULL);
            current=current->next;
            othercp=othercp->next;
        }
    }
}

template<class T>
FCFSList<T>& FCFSList<T>::operator=(const FCFSList& other)
{
    if (this!=&other) {   
        
        FCFSNode<T>* current = head->next;
        while (current!=NULL) {
            FCFSNode<T>* tmp=current;
            current=current->next;
            delete tmp;
        }

       
        

        if (other.head->next!=NULL) { 
            current=head;
            FCFSNode<T>* othercp=other.head->next;

            while (othercp!=NULL) {
                current->next=new FCFSNode<T>(othercp->item,NULL);
                current=current->next;
                othercp=othercp->next;
            }
        }
    }
    return *this;
}

template<class T>
FCFSList<T>::~FCFSList()
{
    FCFSNode<T>* current=head;
    FCFSNode<T>* tmp=NULL;
    while (current!=NULL) {
        tmp=current;
        current=current->next;
        delete tmp;
    }
    head=NULL;
}

template<class T>
void FCFSList<T>::Enqueue(const T& item)
{
    // TODO: Implement
    FCFSNode<T>* current=head;
    //0->1
    while(current->next!=NULL)
    {
        current=current->next;
    }
    current->next=new FCFSNode<T>(item,NULL);
}

template<class T>
T FCFSList<T>::Dequeue()
{
    // TODO: Implement
    if(head->next==NULL)
    {
        return T();
    }
    else
    {   
        //0->1->
        FCFSNode<T>* newFirst=head->next->next;
        FCFSNode<T>* tmp=head->next;
        head->next=newFirst;
        T x=tmp->item;
        delete tmp;
        return x;
    }
    
    
}
template<class T>
bool FCFSList<T>::IsEmpty()const 
{
    if(head->next==NULL)return true;
    return false;
}

#endif