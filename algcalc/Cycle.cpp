#include "Cycle.h"


Cycle::Cycle(vector<int> &v) { //here, given some vector, we put it into permutarion (map) form
	for (unsigned int i = 0; i < v.size(); i++) {
		cycleMap.insert(pair<int,int>(v.at(i), v.at((i + 1) % v.size()))); //neeed to use % for the last elem to work properly
	}//end for
}//end Cycle

Cycle::Cycle(map<int, int> v) {
	map<int, int>::iterator itr; //Creates a variable to iterate over the map
	for (itr = v.begin(); itr != v.end(); itr++) {
		cycleMap.insert(pair<int, int>(itr->first, itr->second));//initalizes our map after getting it from a member function. Is called in member functions, not main
	}//end for
}//end Cycle

void Cycle::permutation(vector<int>& v) {//so we want to convert some list like (3 2 1) into a permutation like (1 2 3)//(3 2 1)
	for (unsigned int i = 0; i < v.size(); i++) { //so we iterate over the entire range
		cycleMap[i+1] = v.at(i % v.size());//and assign the range value to whatever i we are on (domain member)
	}//end for
}//end Cycle

Cycle Cycle::raiseToPower(unsigned int num) {
	map<int, int> power; //create a new map with our result
	num %= cycleMap.size(); //we Need the mod of there power with the size of their map, based on way raising to a power repeats based on modularly based indicies
	if (num == 1) { //if they are raising to the first power, we just return their inputted cycle
		return Cycle(cycleMap);
	}//end if
	else if (num == 0) { //otherwise, if they raise to the 0'th power, return the identity
		return Cycle(power);
	}//end elif
	map<int, int>::iterator itr; //create an iterator
	for (itr = cycleMap.begin(); itr != cycleMap.end(); itr++) {
		int value = itr->second; //initalize  value to what our first iteration is originally mapping to
		for (unsigned int i = 0; i < num-1; i++) { //then iterate over the cycle as many times as they raise the power to, finding what value maps to each time
			value = cycleMap[value]; //value now equals what value maps to.
		}//end for
		power.insert(pair<int, int>(itr->first, value));//finlly, insert this new mapping into our power mapping, and repeat for the next element.
	}//end for
	return Cycle(power);//and then we send power to our default constructor to store in our private data member.
}//end raiseToPower
	
Cycle Cycle::compose(Cycle other) {
	map<int, int>::iterator itr; //iterator we use to iterate over map
	map<int, int> product; //map where we store the product
	for (itr = other.cycleMap.begin(); itr != other.cycleMap.end(); itr++) { //iterate over other
		int a = checker(other.checker(itr->first)); //so we need to check what what itr->first maps to in other, and then check what that maps to in our initalized vector in private
		if (a != itr->first) { //if it doesn't map to itself
			product.insert(pair<int, int>(itr->first, a)); //then insert it into our product
		}//end if
	}//end for
	for (itr = cycleMap.begin(); itr != cycleMap.end(); itr++) { //iterate over cycleMap
		if (itr->first == other.checker(itr->first)) {//check if itr->first maps to itself in other
			int a = checker(itr->first); //set some int = to what itr->first maps to in our private vector
			if (a != itr->first) { //as long as it doesnt map to itself, we can insert it
				product.insert(pair<int, int>(itr->first, a));

			}//end inner if
		}//end outter if
	}//end for
	return Cycle(product); //and then we send to our default constructor to convert to a cycle to return
}//end compose

vector<Cycle> Cycle::decompose() {
	map<int, int>::iterator itr;
	map<int, int>::iterator it;
	int a = 0;// storage variable
	int b = 0;//storage variable
	bool repeat = false; //continue loop or not variable
	vector<Cycle> decomp; //vector of cycles we use if we ae using deompose in other functions
	for (itr = cycleMap.begin(); itr != cycleMap.end(); itr++) { //so we begin by iterating over the map
		a = itr->first; //we store the first value of the domain in a
		b = itr->second; //store second value that domain maps to in b
		if (a == b) { //if a==b, we dont include in cycle, hence continue onto next pair
			continue;
		}//end if
		
		//so here we gonna check if the element has already been accounted for
		if (itr != cycleMap.begin()) { //if first itr, then obviously no repeats yet.
			for (unsigned int i = 0; i < cycleVector.size() && !repeat; i++) { //so first we find an element in the set of cycles to check
				for (unsigned int j = 0; j < cycleVector[i].size() && !repeat; j++) { //next, we check all elements in this cycle					
						repeat = cycleVector[i][j] == a || cycleVector[i][j] == b; //set if we find a match, set "repetition" to true
				}//end inner for
			}//end outer for
			if (repeat) {//if we have a repeat, set it to false, and continue to next itr
				repeat = false;
				continue;
			}//end if
		}//end if
			//finally, after we check if this is a repeast or not, we push a and b onto the newly formed cycle
			//in otherwords, we add the mapping a to b to the mapping. Our cycle rn is (a, b)
		vector<int> v; //the current " cycle"
		v.push_back(a);
		v.push_back(b);

		while (true) {//so now, we will iterate through the map looking for what b maps to, until b returns to a.
			 //begin by iterating over the whole map
			b = checker(b); //let b= what it maps to
			if (b == a) {//if we are back to the start, break
				break;
			}
			v.push_back(b);//push this new b onto our cycle. So now our cycle is (a,b, what b maps to).					
		}//end while
		cycleVector.push_back(v); //we add the current "cycle" onto our big "bunch" of cycles we can display
		decomp.push_back(Cycle(v));//also push it in cycle format onto a vector of cycles we can use for other methods
	}//end for (itr)
	return decomp;
	//after completion of this for, we have completed one full cycle: (a,b, what b maps to,...,what ever maps back to a).
	//and now we return to the original for, and start on the next pair, so (2,whatever), and push a new cycle (vector v) onto our "pile of vectors".
	//displayCycle();
}//end decompose

vector<vector<int>> Cycle::transposition() { //so here we find one possible transposition factorization (if the cycle is (1 2 3), we will make (13)(12) for example).
	map<int, int>::iterator itr; //decalre the iterator
	itr = cycleMap.begin(); //store the first element in itr
	int a = itr->first; //and assign the first element of the pair to a, and the second to b
	int b = itr->second;
	int length = 1; //length we will need for input validation
	vector<int> v; //vector we use as a "cycle" object later on
	//first we create the "cycle", aka push all mappings into vector notation
	v.push_back(a); //so first push a onto our initial vector
	while (b != a) { //while b is not a
		v.push_back(b); //push  b onto the vector
		b = checker(b); //let b equal whateevr b maps to
		length++; //add to the length ( we will use this for input validation later)
	}//end while
	if (cycleMap.size() != length) { //if the size of cycle map doesnt equal length, it means they entered multiple cycles
		cout << "Transposition called with a compund cycle" << endl; //so we throw them an error
		return cycleVector; //and return
	}//end if
	for (unsigned int i = length-1; i > 0; i--) { //otherwise, we are ready to push vectors of size 2 onto out vector of vectors. The mappins are ready
		vector<int> w;
		w.push_back(v.at(0)); //asll we do is push our element at the initial position , and make a cycle with it and the iths element
		w.push_back(v.at(i));
		cycleVector.push_back(w); //then we push this cycle of order 2 onto our "stack of cycles"
	}//end for
	displayCycle(); //call this to display in cycle form
	cout << endl; //formatting endl
	return cycleVector; //and return

} //end transpoition

void Cycle::parity() {
	transposition(); //we call transposition
	if (cycleVector.size() % 2 == 0) { //if there are an even number of tarnspositions
		cout << "even cycle" << endl; //then the cycle is even
	}//end if
	else { //otherwise it is odd
		cout << "odd cycle" << endl;
	}//end else
}

int Cycle::checker(int num) {
	map<int, int>::iterator itr =cycleMap.find(num); //so set the iterator equal to the "range" of the "domain" element we are interested in
	if (itr == cycleMap.end()) { //check if it is in the cycle. If not, return itself
		return num;
	}//end if
	return itr->second; //othrwise, return whatever it maps to.
}//end checker

void Cycle::display() { //this is to display a cycle in matrix/permutation form
	map <int, int>::iterator itr; //declare the iterator
	for (itr = cycleMap.begin(); itr != cycleMap.end(); itr++) { //iterate over the map

		cout << itr->first << " -> " << itr->second << endl; //basically just display the element, an arrowm and what it maps to
	}//end for
	cout << "n -> n" << endl <<endl; //this is here to indicate that we are only outputting the identity
}//end display

void Cycle::displayCycle() { //this displays a cycle in cycle form
	for (unsigned int i = 0; i < cycleVector.size(); i++) { 
		for (unsigned int j = 0; j < cycleVector[i].size(); j++) {
			if (j == 0) { //basically, if we are on the 0th elenment for some cycle, output a starting parenthesis with the element
				cout << "(" << cycleVector[i][j] << " ";
			}//end if
			else if (j == cycleVector[i].size() - 1) { //otherwise, if we are at the end of some cycle, output the ending parenthesis with the element
				cout << cycleVector[i][j] << ")";
			}//end elif
			else {
				cout << cycleVector[i][j] << " "; //else just output the element
			}//end else
		}//end inner for
	} //end outer for
}//end displayCycle

Cycle Cycle::findInverses() {
	map<int,int> inverse;  //initialize inverse to v
	if (cycleMap.size() <= 2) {//if the cycle has length 2, or less (identity), it is its own inverse
		return *this; //and so return itself
	}//end if
	//otherwise, we just reverse the eleemnts 
	for (map<int, int>::iterator itr = cycleMap.begin(); itr != cycleMap.end(); itr++) {
		inverse[itr->second] = itr->first;
	}//end for
	return Cycle(inverse); //and return the resulting cycle
	
}//end findInverses

vector<Cycle> Cycle::generateSubGroups() {
	vector<Cycle> generators = decompose();//first thing we need to do is get our group generators
	
	//We will use the following algorithm: First get the generators and all their inverses into a vector
	//then find all possible combinations among this new set of elements, and put any new elements onto the vector
	//then check if anything new was added, if it wasnt then we are done
	//If not, then find the inverses of the new elements, and add them to the vector too
	//and then rinse and repeat until we have everything 

	int t = generators.size()-1; //we initialize this variable which will serve as a counter to 1 less than cycle vector
	int newInitial=0; //variable we use to only go a certain amount back when we check for inverses. So if we've already checked inverses for 3 elements, when we loop back we dont want to include thsoe 3 elems in the inverse check, hence we start at s, not 0.
	
	while (true) {
		bool done = true; //bool we need to see if we break or not
		for (int i = t; i >= newInitial; i--) { //so basically, start at the last element of the vector of cycles, and check if it has a unique inverse
			Cycle inverse = generators.at(i).findInverses(); //first set some cycle equal to the inverse at i
			if (find(generators.begin(), generators.end(), inverse) == generators.end()) { 
				generators.push_back(inverse); //if find equals end, it means we didn't find the inverse, so we push it onto our set of cycles
				done = false; //and since we added something, the algorithm is not done
			}//end if

		}//end for
		newInitial = generators.size(); //assign s to the size of cycleVector after any inverses were added so we dont have to check them aagin 
		
		//ok, so at this point we have added any inverses. Now we need to go through and check every possible composition
		for (unsigned int k = 0; k < newInitial; k++) { //we use newInitial here, because as we add vectors to cycle vector, that will mess with its size, but we only care about the size of the vector before adding new stuff 
			for (unsigned int l = 0; l < newInitial; l++) {
				Cycle potential = generators.at(k).compose(generators.at(l)); //find the composition of the two vectors, and store in cycleMap
				if (find(generators.begin(), generators.end(), potential) == generators.end()) { //if we dont find it
					generators.push_back(potential); //push it onto our subgroup vector
					done = false;//and since we added something we aren't done
				}//end if
			}//end inner for
		}//end outer for

		t = generators.size()-1;//and make t the new size-1
		
		if (done) {//if we never incramented, break
			break;
		}//end if
	}//end while
	return generators;//and return the vector with our subgroup
}//end generateSubGroups

bool Cycle::identity() {
	if (cycleMap.size() == 0) {//if the cycleMap has nothing in it
		return true; //then we have the identity
	}//end if
	else {
		return false; //else we dont
	}//end else
}//end identity

bool operator==(const Cycle& c1, const Cycle& c2) {
	return c1.cycleMap == c2.cycleMap; //let the == for cycles be defined as checking if the cycles cycleMaps are equivalent
}//end oprator==