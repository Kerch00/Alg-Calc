#include <iostream>
#include <vector>
#include "Cycle.h"
#include "group.h"
#include <stdexcept>
#include <limits>

//this is a pseduo "get" function for cycle. The real get is bascially the default constructor,
//but the user has to enter a vector to be passed to the constructor for most features, hence this function
//which returns a filled up vector, ready to be operated on
vector<int> getCycle() {
	int i = 0; //var we use to store into our vector
	int j = 0; //incramenter we need to tell whether to display the first message or nor
	vector<int> temp;// temporary vector which we will return
	std::cout << "Please enter your cycle below one number at a time, and enter \"0\" when you are done" << endl;
	while (true) {//so stop whenever they want to stop
		if (j == 0) {//if it's their first element, we give them a special message
			std::cout << "Please enter the first number in your cycle" << endl;
			j++;//and incrament j
		}//end if
		else {// else enter the default message 
			std::cout << "Please enter the next number in your cycle, or type \"0\" to stop" << endl;

		}//end else
		

		//input validation:
		while (true) {

			try {
				cin >> i; //get what they want
				cin.clear(); //clear cin buffer
				cin.ignore(1000, '\n'); //ignore all errors from cin
				if (i < 0) { //if the number is non positive, or they enter a string
					throw 20; //throw an exception
				}//end if
			}//end try					
			catch (int e) {//catch the exception

				std::cout << "Runtime Exception: " << "please enter a positive integer or 0" << endl;
				continue;
			}//end catch
			break;
		}//end while


		if (i != 0) {// if i isnt 0, we push i onto the vector
			temp.push_back(i);
		}//end if
		else {
			break; //otherwise break
		}//end else
	}//end while
	return temp;
}//end getCycle()

//literally the same function as above, except specified for when we need them to enter a permutation
vector<int> getPermutation() {
	int i = 0; //var we use to store into our vector
	int j = 1; //incramenter we need to tell user what mapping they are on
	vector<int> temp;// temporary vector which we will return
	std::cout << "Please enter the requested mappings below, or enter \"0\" if you have reached the end of your permutation: " << endl;
	while (true) {//so stop whenever they want to stop
		std::cout << "Please enter what " << j << " maps to:" << endl; //prompt the user for input
		
		//input validation
		while (true) {

			try {
				cin >> i; //get the mapping I need
				cin.clear(); //clear cin buffer
				cin.ignore(1000, '\n'); //ignore all errors from cin
				if (i < 0) { //if the number is non positive, or they enter a string
					throw 20; //throw an exception
				}//end if
			}//end try					
			catch (int e) {//catch the exception

				std::cout << "Runtime Exception: " << "please enter a positive integer or 0" << endl;
				continue;
			}//end catch
			break;
		}//end while

		if (i != 0) {// if i isnt 0, we push i onto the vector
			temp.push_back(i);
		}//end if
		else {
			break; //otherwise break
		}//end else
		j++;
	}//end while
	return temp;
}//end getPermutation()

//this function provides a demo on groups and cycles
void demo() {
	string throwAway = " "; //variable we use to continue in the demo
	cout << endl;
	cout << "Welcome to the demo!" << endl;
	cout << "Groups:" << endl;
	cout << "\t Definitions:" << endl;
	cout << "\t \t algebraic structures- an algebraic structure is a set with an operation on it" << endl;
	cout << "\t \t Associative- The property that (a+b)+c=a+(b+c)" << endl;
	cout << "\t \t Comutative- The property that a+b=b+a" << endl;
	cout << "\t \t group- a group is a special type of alebraic structure such that its operation is associative, each" << endl;
	cout << "\t \t element has a unique inverse, and there exists one unique identity element" << endl;
	cout << "\t \t int mod group- a special type of group whose operation is modular addition, and whose elements are ints" << endl;
	cout << "\t \t abelian group- any group in which the operation is also commutative" << endl;
	cout << endl;
	cout << "\t Examples:" << endl;
	cout << "\t \t An example of a group is the mod 3 group, whose elements are {0,1,2}, and whose operation is +" << endl;
	cout << "\t \t Modular addition is clearly associative, and it is also commutative" << endl;
	cout << "\t \t The identity element of mod 3 is 0, since 0+anything and anything+0 equals that thing" << endl;
	cout << "\t \t Each element has a unique inverse too. 1 and 2 are inverses since 1+2, and 2+1 both equal 0, \n \t \t which is the identity" << endl;
	cout << "\t \t Meanwhile, 0 is its own inverse, since 0+0=0, and 0 is the identity" << endl;
	cout << "\t \t Hence, the set {0,1,2} is clearly an abelian group under the operation of modular addition" << endl;
	cout << "\t \t Since it is a group, we can generate a group table for it:" << endl <<endl;
	Group<int> group = Group<int>(3);
	group.setIntGroup();
	group.getIntGroup();
	cout << endl <<endl;
	cout << "\t \t So this is the group table for mod 3" << endl;
	cout << "\t \t You read it as \"element on the far left+element on the top=element they correspond to\"" << endl;
	cout << "\t \t For example, if we look at the 0 in row 2 column 2, it means \"0+0=0\"" << endl;
	cout << "This program allows you to make your own group tables, as well as see if some set is a group under some operation" << endl;
	cout << "Would you like to move onto the cycles demo? Enter anything below when you are ready." << endl;
	cin >> throwAway;
	cout << endl << endl << endl << endl << endl;
	cout << "Cycles: " << endl;
	cout << "\t Definitions: " << endl;
	cout << "\t \t permuation- A permutation is simply a way to rearrange something, in this case integers" << endl;
	cout << "\t \t cycle- A cycle is a special type of permutation" << endl;
	cout << "\t \t composition-composition is the operation we define on permutations/cycles" << endl;
	cout << "\t Examples:" << endl;
	cout << "\t \t In algebra, we write permutations like so: " << endl;
	cout << "\t \t (1 2 3 4 5)" << endl;
	cout << "\t \t (2 1 3 5 4)" << endl;
	cout << "\t \t This is a permutation in something called S_5, and essentially, the top row is the domain, \n \t \twhile the bottom is the range" << endl;
	cout << "\t \t So the above permutation says \"1 maps to 2, 2 maps to 1, 3 maps to itself, etc.\"" << endl;
	cout << "\t \t From that permutation we can get a cycle. We start with some number, let's say 1. 1 maps to 2, which \n \t \t maps back to 1. This is a cycle, we write it as (1 2), meaning 1 maps to 2, which maps back to 1." << endl;
	cout << "\t \t In a similar vein, (4 5) is also a cycle from the above permutation" << endl;
	cout << "\t \t So one thing we can do with cycles, is compose them" << endl;
	cout << "\t \t Suppose I had the cycles (1 2 3 4) and (3 2). Then their composition is:" << endl;
	cout << "\t \t (1 2 3 4)(3 2). To solve this, pick an element and see where it maps. 1 maps to only 2" << endl;
	cout << "\t \t ,so right now we have (1 2. Now find what 2 maps to. Notice, in the second cycle, 2 maps to 3, \n \t \t and 3 maps to 4 in the first cycle. Hence, 2 maps to 4, and we add this to our product" << endl;
	cout << "\t \t ,so now we have (1 2 4. Finally, we see 4 maps to 1, and we close off the result to ( 1 2 4)" << endl;
	cout << "\t \t As for the 3, well notice 3 just maps to itself, meaning we dont care about it" << endl;
	cout << "\t \t So this is cycle composition, and raising a cycle to a power is just composing the cycle n times" << endl;
	cout << "\t \t As we showed before, we can decompose a permutation into a product of cycles." << endl;
	cout << "\t \t So going back to our original permutation, its decomposition is simply (1 2)(4 5)" << endl;
	cout << "\t \t As it turns out, we can also decompose cycles into a product of cycles of length 2" <<endl;
	cout << "\t \t A cycle of length 2 is called a transposition, and there are infinitely many transposition \n \t \t decompositions for some cycle" << endl;
	cout << "\t \t However, we can use one possible transposition factorization to find the parity of some cycle" << endl;
	cout << "\t \t For example, (1 3 2)=(1 2)(1 3), and hecne it is even, because its factorizaion has \n \t \t 2 transpositions, which is an even number" << endl;
	cout << "\t \t Finally, we can also do something called generating a subgroup, but thats a bit beyond this demo" << endl;
	cout << "This program can do all of the above features. You can either input a cycle, or the range of a permutation" << endl;
	cout << "That finishes the demo. Type anything below to return to the calculator." << endl;
	cin >> throwAway;
	cout << endl;
}

//For some reason the program was bugging, and wasnt working with using namespace std, so I had to use std::
int main() {
	string groupOrCycle = " "; //var we use to choose group or cycle calc, also lets us break out if the user wants to quit
	
	std::cout << "Welcome to the cycles and groups calculator!" << std::endl; //welcome message
	std::cout << "This calculator has several pieces of functionality, including: " << std::endl;
	std::cout << "1. Cycle composition and power raising" << std::endl;
	std::cout << "2. Permutation decomposition" << std::endl;
	std::cout << "3. Finding a transposition factorization and parity" << std::endl;
	std::cout << "4. Generating a subgroup given some permutation" << std::endl;
	std::cout << "5. Finding inverse cycles" << std::endl;
	std::cout << "6. Checking to see if a mapping of a set of elements makes a group" << std::endl;
	std::cout << "7. Checking for abelian groups" << std::endl;
	std::cout << "8. Generating interger mod groups, and groups of your choosing" << std::endl;
	do {//main program loop body
		std::cout << "Would you like to go to the group maker and generator, or the cycle and permutation calculator? \nEnter \"group\" for the former, and \"cycle\" for the latter. Alternatively, type \"quit\" to quit, or \n\"demo\" for a demo on groups and cycles" << std::endl;
		std::cin >> groupOrCycle; //we see where they want to go
		if (groupOrCycle == "quit") {//checks if they want to quit
			break;
		}//end if
		if (groupOrCycle != "group" && groupOrCycle != "cycle" && groupOrCycle != "demo") { //input validation
			std::cout << "Please enter \"demo,\" \"quit,\" \"group,\" or \"cycle.\" Make sure you pay attention to capitals." << endl;
			continue; //if they dont use a valid input, we send them back to the top
		}//end if
		//so at this point we are guaraunteed either "group," or "cycle", so we use an if else block.

		if (groupOrCycle == "group") {//if they entered group, take them to that section
			std::cout << "Would you like to see the table for an integer mod group, or make your own (if you make your own \n it will display information about the inverse, identity, and whether it's abelian as well)? Enter\n\"int\" for the former, and \"own\" for the latter. Alternatively, enter \"quit\" to quit." << std::endl; //here we prompt them to choose where in the group calc they want to go
			std::cin >> groupOrCycle; //we use the same var as before for simplicity.
			while (groupOrCycle != "own" && groupOrCycle != "int" && groupOrCycle != "quit") { //input validation
				std::cout << "Please enter \"quit,\" \"own,\" or \"int.\" Make sure you pay attention to capitals." << endl;
				cin >> groupOrCycle; //if they dont use a valid input, we send them back to the top
			}//end while
			if (groupOrCycle == "quit") {//if they enter quit we break
				break;
			}//end if
			else if (groupOrCycle == "int") {//else, we execute the int section
				std::cout << "What order of int mod group would you like?" << std::endl;
				int intGroupOrder; //group order number
				//everything in this while is just input management, ensuring they dont enter anything odd.
				while(true) {
					
					try {
						cin >> intGroupOrder; //input the number
						cin.clear(); //clear cin buffer
						cin.ignore(1000,'\n'); //ignore all errors from cin
						if (intGroupOrder <= 0) { //if the number is non positive, or they enter a string (because vs recgonizes a string in an int as 0)
							throw 20; //throw an exception
						}//end if
					}//end try					
					catch (int e) {//catch the exception

						std::cout << "Runtime Exception: " << "please enter a positive integer" << endl;
						continue;
					}//end catch
					break;
				}//end while
				//so if they got this far, we know they entered an proper int. Hence:
				Group<int> group = Group<int>(intGroupOrder); // we initialize the deafult constructor
				group.setIntGroup(); //set the group
				group.getIntGroup(); //and output it
			}//end elif
			else if(groupOrCycle =="own"){//else we execute the group section
				char operation ='*'; //users operation of choice
				vector<string> set; //users set of elements
				string temp; //temporary string we use
				map<pair<string, string>, string> group; // the users mapping
				std::cout << "First, enter a 1 character symbol for your operation (all subsequenet symbols will be ignored)" << endl;
				cin >> operation;

				std::cout << "Next, enter all of your group elements one by one. Type in \"done\" to stop" << endl;
				std::cout << "Please enter your first element: " << endl;
				cin >> temp;
				while (temp != "done") {
					set.push_back(temp);
					std::cout << "Enter your next element: " << endl;
					cin >> temp;
				}//end while
				std::cout << "Finally, you will need to enter all combinations of group elements. If you want to add a+b=c for instance,\n first input a, then b, then c. Ensure you include all pairings." << endl;
				string a; //the three variables we store their results in before putting into map.
				string b;
				string c;

				for (unsigned int i = 0; i < set.size() * set.size(); i++) {
					std::cout << "Please enter the first element being operated on (the a in a+b=c)" << endl;
					cin >> a;
					std::cout << "Now enter the other element being operated on (the b in a+b=c)" <<endl;
					cin >> b;
					std::cout << "Finally, enter the solution (the c in a+b=c)" << endl;
					cin >> c;
					pair<string, string> key = pair<string, string>(a, b);
					group[key] = c;
					std::cout << a << operation << b << "=" << c << " has been entered into your group." << endl;
				}//end for
				Group<string> group1 = Group<string>(set,group,operation);
				group1.getGroup();
			}//end elif
			else {//else, there was an unfroseen error
				std::cout << "Sorry, it seems we ran into an error. Please try again." << std::endl;
				break;
			}//end else
		}//end if
		else if (groupOrCycle == "cycle") {//else if they entered cycle, take them to cycle
			//and we display what features they can invoke
			std::cout << "which feature of the cycles calculator would you like to use?" << endl;
			std::cout << "type \"power\" for raising to a power" << endl;
			std::cout << "type \"compose\" for cycle composition" << endl;
			std::cout << "type \"parity\" for the parity of a cycle, as well as one possible transposition decomposition" << endl;
			std::cout << "type \"decompose\" to decompose a permutation into its disjoint factorization" << endl;
			std::cout << "type \"inverse\" to find an inverse for some cycle" << endl;
			std::cout << "type \"subgroup\" for generating the subgroup of a permutation" << endl;
			std::wcout << "Or enter \"quit\" to quit." << endl;
			cin >> groupOrCycle; //input what feature they want
			
			//input validate them below
			while (groupOrCycle != "power" && groupOrCycle != "compose" && groupOrCycle != "decompose" && groupOrCycle != "parity" && groupOrCycle != "inverse" && groupOrCycle != "subgroup" && groupOrCycle != "quit") {
				cout << "Please enter \"power,\" \"compose,\" \"parity,\" \"decompose,\" \"inverse,\" \"subgroup,\" or \"quit,\"." << endl;
				cin >> groupOrCycle;
			}//end while

			//ok so by now they have gone through input validation, and we can use a bunch of elifs since switch doesnt work on strings
			if (groupOrCycle == "quit") {//but first, we quit if they want to quit
				break;
			}//end if
			if (groupOrCycle == "power") {
				vector<int> powerCycle; //what we will raise to a power
				int power = 1; //the power they want to raise to
				powerCycle = getCycle(); //get the users inputs
				//now ask them what power they want to raise to
				std::cout << "What power would you like to raise your cycle to?" << endl;
				cin >> power; //get their input
				//and now we call our default constructor and power and display
				Cycle cycle = Cycle(powerCycle); //create a cycle for our vector
				Cycle cycle2 = cycle.raiseToPower(power); //raise the cycle to a power
				cycle2.decompose(); //decompose the result
				cycle2.displayCycle(); //display it
				cout << endl; //formatting endl
			}//end if
			else if (groupOrCycle == "compose") {
				vector<int> compose1; //the first cycle.
				vector<int> compose2; //the second cycle.
				std::cout << "Please enter the first of the cycles you want to compose (the a in (a)(b))" << endl;
				compose1 = getCycle(); //get user inputs for first cycle
				std::cout << "Now enter the cycle you wish to compose this cycle with (the b in (a)(b))" << endl; //prompt for second cycle
				compose2 = getCycle(); //get user inputs for second cycle
				Cycle cycle = Cycle(compose1); //initialize first vector as a cycle
				Cycle cycle2 = Cycle(compose2); //initialize second vector as a cycle

				Cycle cycle3 = cycle.compose(cycle2);//create a new cycle which stores the result of the composition
				cycle3.decompose();//decompose this composition
				cycle3.displayCycle();//display it
				cout << endl; //formatting cout
			}//end elif
			else if (groupOrCycle == "parity") {
				vector<int> parity; //what we want the parity of
				parity = getCycle();//get inputs
				Cycle cycle = Cycle(parity); //initialize the default constructor
				cycle.parity();//call the parity function, which also does the displaying
			}//end elif
			else if (groupOrCycle == "decompose") {
				vector<int> toDecompose; //cycle to decomp
				toDecompose = getPermutation(); //get inputs
				Cycle permutation = Cycle(toDecompose);//initialize the permutation as a cycle
				permutation.permutation(toDecompose); //convert the cycle to a permutation
				permutation.decompose(); //call decompose
				permutation.displayCycle();//display in cycle form
				cout << endl; //formatting cout
			}//end elif
			else if (groupOrCycle == "inverse") {
				vector<int> inverse; //vector we store the cycle in
				inverse = getCycle(); //get inputs
				Cycle cycle = Cycle(inverse); //initialize inverse as a cycle
				Cycle cycle2 = cycle.findInverses(); //findInverses returns a cycle, hence create a new cycle and set it equal to inverses
				cycle2.decompose(); //decompose our inverse
				cycle2.displayCycle(); //display the decomposed inverse
				cout << endl; //formatting endl
			}//end elif
			else if (groupOrCycle == "subgroup") {
				vector<int> perm1; //vector where we store the range of the permutation
				perm1 = getPermutation(); //get user inputs
				Cycle perm = Cycle(perm1); //initialize the perm as a cycle
				perm.permutation(perm1); //convert the perm to a perm
				vector<Cycle> subgroups = perm.generateSubGroups();//call the subgroup function
				for (unsigned int i = 0; i < subgroups.size(); i++) { //now we loop over and display
					if (i == 0) { //if we on the first iteration, there is a special display
						cout << "Subgroup: {";
					}//end if
					Cycle cycle = subgroups.at(i); //get the cycle at pos i in subgroups
					if (cycle.identity()) { //if it's the identity, print ()
						cout << "(), ";
					}//end if
					else { //else print like normal
						cycle.decompose();
						cycle.displayCycle();
						if (i != subgroups.size() - 1) { //make sure we aren't on the last element so we dont have a superflous comma
							cout << ", ";
						}//end if
					}//end else
				}//end for
				cout << "}" << endl;//and display the ending bracket
				cout << endl; //formatting endl
			}//end elif
			else {//else sonmething went wrong
				std::cout << "Sorry, it seems we ran into an error. Please try again." << std::endl;
				continue;
			}//end else
		}//end elif
	else if (groupOrCycle == "demo") {
		demo();//call the demo if they want the demo
		}//end elif
	else {//else, there was an unfroseen error
			std::cout << "Sorry, it seems we ran into an error. Please try again." << std::endl;
		}//end else
		
	} while (true); //end do while

	std::cout << "Thank you for using the program!" << endl; //thank the user for using the program

	return 0;
}


/* BELOW ARE POTENTIAL TESTS FOR THE GROUP GENERATION PORTION
following info is klien 4
vector<string> klien = { "e","a","b" ,"c" };

char oper = '*';
map<pair<string, string>, string> test = {
	{pair<string,string> ("e","e"),"e"},
	{pair<string,string> ("e","a"),"a"},
	{pair<string,string> ("e","b"),"b"},
	{pair<string,string> ("e","c"),"c"},
	{pair<string,string> ("a","e"),"a"},
	{pair<string,string> ("a","a"),"e"},
	{pair<string,string> ("a","b"),"c"},
	{pair<string,string> ("a","c"),"b"},
	{pair<string,string> ("b","e"),"b"},
	{pair<string,string> ("b","a"),"c"},
	{pair<string,string> ("b","b"),"e"},
	{pair<string,string> ("b","c"),"a"},
	{pair<string,string> ("c","e"),"c"},
	{pair<string,string> ("c","a"),"b"},
	{pair<string,string> ("c","b"),"a"},
	{pair<string,string> ("c","c"),"e"}

};

group<string> group=group<string>(klien, test, oper);

group.getgroup();*/

////following info is mod 3
//vector<string> mod3 = { "0","1","2" };
//char oper2 = '+';
//map<pair<string, string>, string> test2 = {
//	{pair<string,string> ("0","0"),"0"},
//	{pair<string,string> ("0","1"),"1"},
//	{pair<string,string> ("0","2"),"2"},
//	{pair<string,string> ("1","0"),"1"},
//	{pair<string,string> ("1","1"),"2"},
//	{pair<string,string> ("1","2"),"0"},
//	{pair<string,string> ("2","0"),"2"},
//	{pair<string,string> ("2","1"),"0"},
//	{pair<string,string> ("2","2"),"1"}
//};
//



