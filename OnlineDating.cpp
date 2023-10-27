//sorted alphabetically according to last name, then first name.
//  Created by Kai N. Alcayde on 7/12/21.
//

#include "OnlineDating.h"
#include <string>

//#include <iostream>

//constructor
// Create an empty OnlineDating list
OnlineDating::OnlineDating(){
    
    //all aspects of the list are currently nullptr
    head = nullptr;
    m_nummatches = 0;

}

// copy constructor
OnlineDating::OnlineDating(const OnlineDating& rhs)
{
    //work on implementation of previous
    //need to put in first and last names too
    if (rhs.head == nullptr)
    {
        head = nullptr;
        m_nummatches = 0;
    }
    else {
        head = new Node;
        head->num = rhs.head->num;
        head->m_firstname = rhs.head->m_firstname;
        head->m_lastname = rhs.head->m_lastname;
        
        head->previous = nullptr;
        
        Node *q = head;
        Node *p = rhs.head->next;
        while (p != nullptr) {
            q->next = new Node;
            
            
            
            //previous implementation
            q->previous = p->previous->previous;
            
            //last one is a little buggy?
            
            q->next->num = p->num;
            q->next->m_firstname = p->m_firstname;
            q->next->m_lastname = p->m_lastname;

            
            
            //edge case: last node
            if(p->next == nullptr)
            {
                q->next->previous = p->previous;
            }

            q->next->next = nullptr;
            p = p->next;
            q = q->next;
            
            m_nummatches += 1;
            
        }

    }
}

// assignment operator
const OnlineDating& OnlineDating::operator=(const OnlineDating& rhs)
{
    if (this == &rhs)
        return *this;
    
    OnlineDating temp = rhs;
    
    //trade this current list with a temp one, so it gets deleted. No random memory leak
    tradeMatches(temp);
    return *this;
}

//destructor
OnlineDating::~OnlineDating()
{
    Node *p;
    while (head != nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
}


// Return true if the OnlineDating list
// is empty, otherwise false.
bool OnlineDating::noMatches() const{
    
    if (head == nullptr)
        return true;
    else
        return false;
}

// Return the number of matches
// on the OnlineDating list.
int OnlineDating::howManyMatches() const{
    
    return m_nummatches;
}




// If the full name (both the first and last name) is not equal
// to any full name currently in the list then add it and return true
// Elements added according to their last name
// Elements with the same last name added according to their first names
// else, make no change to the list and return false 
	// (indicating name is already in the list).
bool OnlineDating::makeMatch(const std::string& firstName, const std::string&
               lastName, const OnlineType & value){
    
    std::string newPerson = firstName + lastName;
    std::string currentPerson;
    
    
    
    Node *p = head;
    Node* n = new Node;
    //create a new node with the corresponding match
    n->m_firstname = firstName;
    n->m_lastname = lastName;
    n->num = value;
    
    //special: if no matches in list
    if(howManyMatches() == 0)
    {
        //set the pointer's location in the list
        n->next = head;
        n->previous = nullptr;  //nothing before p, as is first match
        
        if(head !=nullptr)
            head->previous = n;
        
        head = n;
        
        
        m_nummatches += 1;
        return true;
    }
    

    
    //if not equal to any full name, add it and return true
    //IS THIS P OR P->NEXT
    while(p->next!=nullptr)
    {
        currentPerson = p->m_firstname + p->m_lastname;
        
        if(currentPerson != newPerson)
            p = p->next;
        else
            return false;       //name was already on the list
        
    }

    
    //if we went through the list, go back to the beginning
    if(p->next == nullptr)
    {
        while(p->previous != nullptr)
            p = p->previous;
    }
    
    
    
    //look through last names
    while(p!=nullptr)
    {
        
        //if same last name
        if(p->m_lastname == lastName)
        {
            while(p!=nullptr)
            {
                
                //if new match is alphabetically above current (first name)
                if(p->m_firstname > firstName)
                {
                    //set the pointer's location in the list
                    n->next = p;
                    if(p==head)    //case if p is head
                    {
                        n->previous = nullptr;  //nothing before p, as is first match
                        n->next = head;
                        head->previous = n;
                        head = n;
                        
                        
                        m_nummatches += 1;
                        return true;
                    }
                    
                    
                    else   //if in the middle of the list
                    {
                        p->previous->next = n;
                        n->previous = p->previous;
                        n->next = p;
                        p->previous = n;
                        
                        
                        m_nummatches += 1;
                        return true;
                    }

                }
//end of list
//there are some cases where p->m_firstname < firstName. So this is a special case
                else if(p->next == nullptr)     

//where end of the first names with same last name, and adding word is alphabetically below
                {
                    if(p->m_firstname < firstName)
                    {
                        //set the pointer's location in the list
                        n->next = nullptr;
                        n->previous = p;
                        p->next = n;
                        
                        
                        
                        m_nummatches+=1;
                        return true;
                    }
                    
                }
                
                
                else if(p->next!=nullptr)
                    p=p->next;      //iterate until it is alphabetically above current name
            }
        }
        
        
        //if new match is alphabetically above current (last name)
        if(p->m_lastname > lastName)
        {
            //set the pointer's location in the list
            
            
            n->next = p;
            if(p==head)    //case if p is head
            {
                n->previous = nullptr;  //nothing before p, as is first match
                n->next = head;
                head->previous = n;
                head = n;
                
                m_nummatches += 1;
                return true;
            }
            
            
            else   //if in the middle of the list
            {
                p->previous->next = n;
                n->previous = p->previous;
                n->next = p;
                p->previous = n;
                
                m_nummatches += 1;
                return true;
            }

        }
        
        if(p->next!=nullptr)
            p = p->next;    //iterate until it is alphabetically above current last name
        
        else                //then you reached the end of the list
        {
            p->next = n;
            n->previous = p;
            n->next = nullptr;
            
            
            m_nummatches += 1;
            return true;
        }
    }
    
    return true;
}
//need to consider last node case!! if p->next is nullptr






// If full name equal to a full name currently in the list make that full name no longer map to the
// value it currently maps to, but instead map to the value of the third parameter
// return true in this case. Otherwise, make no change to the list and return false.

bool OnlineDating::transformMatch(const std::string& firstName, const
                                  std::string& lastName, const OnlineType & value){
    
    Node*p = head;
    
    if(someoneAmongMatches(firstName, lastName))
    {
        Node *obj = NodeFinder(p, firstName, lastName);
        obj->num = value;
        return true;
    }
    
    else
        return false;
}






// If full name equal to a name currently in the list, then
// make that full name no longer map to the value it currently
// maps to, but instead map to value of the third parameter;
// return true. 
// If the full name is not equal to any full name currently in the 
// list then add it and return true. This function always returns true.

bool OnlineDating::makeOrTransform(const std::string& firstName, const
                                   std::string& lastName, const OnlineType& value){
    
    
    if(someoneAmongMatches(firstName, lastName))
    {
        transformMatch(firstName, lastName, value);
    }
    
    else
    {
        makeMatch(firstName, lastName, value);
    }
        
        
        
    return true;
    
}




// If the full name is equal to a full name currently in the
// list, remove the full name and value from the list and return true. 
// Else, make no change to the list and return false.

bool OnlineDating::blockPreviousMatch(const std::string& firstName, const
                                      std::string& lastName){
    
    
    Node*p = head;
    if(someoneAmongMatches(firstName, lastName))
    {
        
        //find the node
        Node *obj = NodeFinder(p, firstName, lastName);
        
        //only one node
        if(obj == head && obj->next == nullptr)
        {
            //go to end and delete
            head = nullptr;
            delete head;
        }
        
        //special case first node
        else if(obj == head)
        {
            obj->next->previous = nullptr;
            head = obj->next;
        }
        
        //special case last node
        else if(obj->next == nullptr)
        {
            obj->previous->next = nullptr;
        }
        
        //anywhere else
        //set links to ignore obj in list
        else
        {
        obj->next->previous = obj->previous;
        obj->previous->next = obj->next;
        }
        
        
        //delete obj
        obj = nullptr;      //prevent dangling pointer and error with destructor
        delete obj;
        
        //change total num of matches in list
        m_nummatches -= 1;
        
        return true;
    }
    
    else
        return false;
}









// Return true if the full name is equal to a full name
// currently in the list, else false.
bool OnlineDating::someoneAmongMatches(const std::string& firstName, const
                                       std::string& lastName) const{
    
    Node*p = head;
    
    //edge case: list is empty
    if(p == nullptr)
        return false;
    
    std::string newPerson = firstName + lastName;
    std::string currentPerson;
    //if not equal to any full name, add it and return true
    //IS THIS P OR P->NEXT
    while(p->next!=nullptr)
    {
        currentPerson = p->m_firstname + p->m_lastname;
        
        if(currentPerson != newPerson)
            p = p->next;
        else
            return true;       //name was already on the list
        
    }
    
    //edge case:end, when p->next == nullptr
    currentPerson = p->m_firstname + p->m_lastname;
    if(currentPerson == newPerson)
        return true;
    
    
    return false;
    
}





// If the full name is equal to a full name currently in the list, 
// set value to the value in the list that that full name maps to, and return true. 
// Else, make no change to the value parameter of this function and return false.

bool OnlineDating::lookAtMatches(const std::string& firstName, const std::string& lastName, OnlineType& value) const{
    
    
    
    //check if I "set value to the value in the list that that full name maps to"
    Node *p = head;
    
    //if there is a match
    if(someoneAmongMatches(firstName, lastName))
    {
        Node *obj = NodeFinder(p, firstName, lastName);
        
        value = obj->num;
        return true;
    }
    
    else
       return false;
}





// If 0 <= i < size(), copy into firstName, lastName and value parameters the corresponding 
// information of the element at position i in the list and return true. 
// Else, leave the parameters unchanged and return false. 

bool OnlineDating::confirmMatch(int i, std::string& firstName, std::string&
                  lastName, OnlineType & value) const{
    
    
    Node*p = head;
   
    if(i >= 0 && i < m_nummatches)
    {
        for(int j = 0; j < i ; j++)
            p = p->next;
        {
        
        lastName = p->m_lastname;
        firstName = p->m_firstname;
        value = p->num;
            
        }
        return true;
    }
    
    else
    {
        return false;
    }
 
}





// Exchange the contents of this list with the other one.
void OnlineDating::tradeMatches(OnlineDating& other){
    Node* temp = other.head;
    other.head = head;
    head = temp;
    
    //also exchange number of matches
    int nmatch = other.m_nummatches;
    other.m_nummatches = m_nummatches;
    m_nummatches = nmatch;
    
    return;
}







bool mergeMatches(const OnlineDating & odOne, const OnlineDating & odTwo, OnlineDating & odJoined){
    
    
    bool result = true;
    
    //odJoined might not be empty. So make it empty
    OnlineDating copy;
    odJoined.tradeMatches(copy);
        
    //double for loop, looking for matches
    for(int i = 0; i < odOne.howManyMatches() ; i++)
    {
        bool needToSkip = false;        //if val are not the same, must skip the iteraton
        
        std::string first;
        std::string last;
        OnlineType val;
        
        odOne.confirmMatch (i, first, last, val);
        
        
        for(int j = 0; j < odTwo.howManyMatches() ; j++)
        {

             std::string first2;
             std::string last2;
             OnlineType val2;
            
            odTwo.confirmMatch (j, first2, last2, val2);
            
            
            //if there is a match
            if(first==first2 && last == last2)
            {
                if(val != val2)     //if appears in both but different corresponding values
                {
                    result = false;
                    needToSkip = true;
                    
                }
                
                else if(val == val2)        //duplicate appears
                {
                    
                    break;
                    
                }
                
            }
            
            
            
            //need to check if there was a duplicate name in the second list
            if(odOne.someoneAmongMatches(first2, last2))
            {
                continue;
            }
            
            //if there is no match
            
            if(odJoined.someoneAmongMatches(first2, last2))                 //if it is already in OD skip
            {
                //do nothing
            }
            
            else            //add it in
            {
                odJoined.makeMatch(first2, last2, val2);
            }
            
        }
        
        
        if(needToSkip)      //skip current iteration if mismatched values
        {
            continue;
        }
        
        else
            odJoined.makeMatch(first, last, val);
        
        
    }

    return result;
}






void authenticateMatches (const std::string& fsearch, const std::string& lsearch, const OnlineDating& odOne, OnlineDating& odResult){

    
    //odResult might not be empty. So make it empty
    OnlineDating copy;
    odResult.tradeMatches(copy);
    
    //case where serach contains both fsearch and lsearch
    if(odOne.someoneAmongMatches(fsearch, lsearch))
    {
        for(int i = 0; i < odOne.howManyMatches() ; i++)
        {
        std::string first;
        std::string last;
        OnlineType val;
        odOne.confirmMatch (i, first, last, val);
            
        if(first == fsearch && last == lsearch)
        {
            odResult.makeMatch(first, last, val);
            return;
        }
            
        }
    }
    
    //special case: copying the entire list
    if(fsearch == "*" && lsearch == "*")
    {
        copy = odOne;
        odResult.tradeMatches(copy);
        return;
    }
    
    //if fsearch or lsearch (only one) is "*"
    for(int i = 0; i < odOne.howManyMatches() ; i++)
    {
        std::string first;
        std::string last;
        OnlineType val;
        odOne.confirmMatch (i, first, last, val);
        
        if(last == lsearch && fsearch == "*")               //if fsearch is "*"
        {
            odResult.makeMatch(first, last, val);
        }
        
        else if(first == fsearch && lsearch == "*")         //if lsearch is "*"
        {
            odResult.makeMatch(first, last, val);

        }
    }
        return;
    
}



OnlineDating::Node* OnlineDating::NodeFinder(Node*p, const std::string firstName,const std::string lastName )const{
    
    
    Node *copy = p;
    std::string desiredFullName = firstName + lastName;
    std::string currentFullName;
    
    //look for match, set node equal to it
    while(copy->next != nullptr)
    {
        currentFullName = copy->m_firstname + copy->m_lastname;
        
        if(currentFullName == desiredFullName)
        {
            return copy;
        }
        copy = copy->next;
    }
    
    
    
    
    return copy;
}




