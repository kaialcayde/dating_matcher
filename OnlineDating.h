//  Created by Kai N. Alcayde on 7/12/21.
//

#ifndef OnlineDating_h
#define OnlineDating_h


#include <string>

typedef int OnlineType;


class OnlineDating
{
private:
    
    struct Node {
        OnlineType num;
        std::string m_firstname;
        std::string m_lastname;
        Node *next= nullptr;
        Node *previous = nullptr;
    };
    Node *head=nullptr;
    Node* NodeFinder(Node*p,const std::string firstName,const std::string lastName) const;
    int m_nummatches;
    
 public:
 OnlineDating(); // Create an empty OnlineDating list
 OnlineDating(const OnlineDating& rhs);     //copy constructor
 const OnlineDating& operator=(const OnlineDating& rhs);        //assignment operator
 ~OnlineDating();       //destructor

 bool noMatches() const; // Return true if the OnlineDating list
 // is empty, otherwise false.
    
 int howManyMatches() const; // Return the number of matches
 // on the OnlineDating list.
    
 bool makeMatch(const std::string& firstName, const std::string&
 lastName, const OnlineType & value);
// If the full name (both the first and last name) is not equal
// to any full name currently in the list then add it and return true
// Elements added according to their last name
// Elements with the same last name added according to their first names
// else, make no change to the list and return false 
	// (indicating name is already in the list).
    
    
 bool transformMatch(const std::string& firstName, const
std::string& lastName, const OnlineType & value);
// If full name equal to a full name currently in the list make that full name no longer map to the
// value it currently maps to, but instead map to the value of the third parameter
// return true in this case. Otherwise, make no change to the list and return false.



    
 bool makeOrTransform(const std::string& firstName, const
std::string& lastName, const OnlineType& value);
// If full name equal to a name currently in the list, then
// make that full name no longer map to the value it currently
// maps to, but instead map to value of the third parameter;
// return true. 
// If the full name is not equal to any full name currently in the 
// list then add it and return true. This function always returns true.
    
    
 bool blockPreviousMatch(const std::string& firstName, const
std::string& lastName);
// If the full name is equal to a full name currently in the
// list, remove the full name and value from the list and return true. 
// Else, make no change to the list and return false.
    
    
 bool someoneAmongMatches(const std::string& firstName, const
std::string& lastName) const;
// Return true if the full name is equal to a full name
// currently in the list, else false.
    
    
 bool lookAtMatches(const std::string& firstName, const
std::string& lastName, OnlineType& value) const;
// If the full name is equal to a full name currently in the list, 
// set value to the value in the list that that full name maps to, and return true. 
// Else, make no change to the value parameter of this function and return false.
    
    
 bool confirmMatch(int i, std::string& firstName, std::string&
lastName, OnlineType & value) const;
// If 0 <= i < size(), copy into firstName, lastName and value parameters the corresponding 
// information of the element at position i in the list and return true. 
// Else, leave the parameters unchanged and return false. 



// Exchange the contents of this list with the other one.
 // Exchange the contents of this list with the other one.
    
    
};


bool mergeMatches(const OnlineDating & odOne,
 const OnlineDating & odTwo,
 OnlineDating & odJoined);


void authenticateMatches (const std::string& fsearch,
 const std::string& lsearch,
 const OnlineDating& odOne,
 OnlineDating& odResult);

#endif
