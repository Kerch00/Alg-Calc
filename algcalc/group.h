#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
using namespace std;
template<typename T> //I originally planned to let my private data structures use either ints or strings, but it wasn't working so I scrapped the idea, but kept the template for future endavours
class Group
{
public:
	/// <summary>
	/// This is the defaul constructor if the user wants to generate/create a group for anything other than mod n
	/// We use their unputs to initalize our own private variables of table, groupMembers, and operation
	/// </summary>
	/// <param name="set">set of elements they want to use in the group</param>
	/// <param name="table">map where they enter all mappings for their group</param>
	/// <param name="op">operation of thier group</param>
	Group(vector<string> set, map<pair<string, string>, string> table,char op);
	/// <summary>
	/// This is the default constructor for mod n groups. Just takes in a number, and initlaizes a vector to integers, and operation to +
	/// </summary>
	/// <param name="num">the degree of the mod group the user wants</param>
	Group(int num);
	/// <summary>
	/// Setter method for mod group, we just create a vector of vectors and fill it with the group using nested for loops
	/// </summary>
	void setIntGroup();
	/// <summary>
	/// the getter for the int group, essentially uses a double for loop to output the vector of vectors initalized in the setter
	/// </summary>
	void getIntGroup();
	/// <summary>
	/// This method checks whether the mapping the user entered is associative or not
	/// It uses several double for loops, and if else statements, and runs through each mapping
	/// individually. It then assigns private data member false if not associative
	/// </summary>
	void checkAssociative();
	/// <summary>
	/// If checkAssocicative comes out true, then we execute this function. This function makes use
	/// of nested for loops and if else statements as well in order to go through each element to check 
	/// if it is the identity or not. It also checks for multiple identies. If no identity is found,
	/// private data member identityExists is set false, and if too many exist, than member identityCheck is set true
	/// </summary>
	void findIdentity(); 
	/// <summary>
	/// This method checks to ensure the "each element has a unique inverse" property is upheld.
	/// we again use for loops and if elses, as well as built in standard library functions like find
	/// to find inverses for each element. If no inverse is found for any one element, we turn private data
	/// member inverses into false
	/// </summary>
	void checkInverses();
	/// <summary>
	/// This method simply uses an if else control sequence to check whether or not all three of the above
	/// functions returned true. It also only calls methods if the previous method returns true. For example,
	/// if checkAssociative turns associative to false, findIdentity and checkInverses will not be run.
	/// If all 3 are true, isGroup will be set to true
	/// </summary>
	void checkGroup();
	/// <summary>
	/// This method is very similar to checkAssociative. Same types of porgramming concpets used,
	/// except we check for commutativity, not associativity
	/// </summary>
	void checkAbelian();
	/// <summary>
	/// This method calls upon checkGroup, to see if the user entered a group or not. If they did,
	/// a control sequence is executed, which first calls upon checkAbelian, and then displays info about
	/// their group, such as the identity, the inverse element pairs, and the table. If isGroup is false,
	/// the reason why their potential group failed is outputted to them.
	/// </summary>
	void getGroup();
private:
	
	vector<T> groupMembers; //vector where group members are stored
	
	vector<pair<T, T>> groupInverses; //where we stote inverses

	char operation; // where we store the operation

	map <pair<T, T>, T> table;//where we store the group

	vector<vector<T>> group;//also where we store the group, this is for ease of disdplaying, table is for ease of calculations
	
	bool associative = true; //bool we change depending on if what they entter is associative or not

	bool abelian = true; //bool we change depending on if the group entered is abelian or not

	bool identityExists =true; //bool we change depending on whether or not there exists a clear identity element

	bool identityCheck = false;//essentially, it may be the case that the user enters two+ identities, in which case its obviously no longer a group. Hence, I add a seperate boolean for this, to tell them exactly why their set isn't a group

	string identity; //string where we keep the identity

	bool inverses = true; //bool we use to see if each element has an inverse

	bool isGroup = true;//bool we use to see whether or not we have a group or not

};

