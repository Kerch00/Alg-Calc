#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
using namespace std;
class Cycle
{
public:
	/// <summary>
	/// This is the first default constructor which initializes our cycle map data structure
	/// We use a for loop to create a mapping between an element in a user generated cycle (v)
	/// and the eleemnt at the i+th indice. We must use mod size of the cycle, because otherwise
	///  the last element wouldn't function properly.
	/// </summary>
	/// <param name="v">The cycle the user enters</param>
	Cycle(vector<int> &v);
	/// <summary>
	/// This is the second default constructor which assigns the user entered cycle
	///  to a new cycle if they raise to a power of n, where n is the length of the cycle.
	/// </summary>
	/// <param name="v">the map that we are copying</param>
	Cycle(map<int, int> v);
	/// <summary>
	/// Takes in the range of a users permutation, and matches it to its domain elements making a permutation
	/// </summary>
	/// <param name="v">user entered range</param>
	void permutation(vector<int>& v);
	/// <summary>
	/// raises some user inputted cycle to some user inputted power
	/// </summary>
	/// <param name="num">the power that the user is rasing to</param>
	/// <returns></returns>
	Cycle raiseToPower(unsigned int num);
	/// <summary>
	/// composes 2 (and only 2) cycles
	/// </summary>
	/// <param name="other">other cycle not in default contstructor to compose with</param>
	/// <returns></returns>
	Cycle compose(Cycle other);
	/// <summary>
	/// this function creates one possible tranpositon factorization for any cycle
	/// </summary>
	/// <returns></returns>
	vector<vector<int>> transposition();
	/// <summary>
	/// This function checks the parity of any cycle
	/// </summary>
	void parity();
	/// <summary>
	/// this function takes a permutation, and decomposes it into cycles
	/// </summary>
	vector<Cycle> decompose();
	/// <summary>
	/// this function checks "what comes next" given some element in a cycle
	/// </summary>
	/// <param name="num">number who we are checking to see what it maps to</param>
	/// <returns></returns>
	int checker(int num);
	/// <summary>
	/// Basically the get function if we use the map version of cycle
	/// it is mainly for testing, since displaying as cycles is almost always preferred to
	/// displaying as a matrix permutation
	/// </summary>
	void display();
	/// <summary>
	/// The get function if we want to get the cycle version of some permutation
	/// </summary>
	void displayCycle();
	/// <summary>
	/// Just a function we need in the subgroup process. It lets us find the inverse of any cycle.
	/// </summary>
	/// <param name="v">vector we find the inverse of</param>
	/// <returns></returns>
	Cycle findInverses();
	/// <summary>
	/// A function that tells if some cycle is the identity. it just checks the size of cycle map
	/// and returns true if it is 0. Used for printing
	/// </summary>
	/// <returns>a bool indicating identity or not</returns>
	bool identity();
	/// <summary>
	/// This function takes some permutation, and generates the subgroup for it
	/// </summary>
	/// <returns>a vector of the subgroup elements</returns>
	vector<Cycle> generateSubGroups();

	friend bool operator==(const Cycle &c1, const Cycle &c2); //here we override the equality operator, and define our own for cycles
private:
	
	vector<vector<int>> cycleVector;//vector of vectors that I store cycles in
	map<int,int> cycleMap; //map where we store user cycles in, but in permutation form, not cycle form
	
};

