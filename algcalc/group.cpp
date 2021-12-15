#include "Group.h"

Group<string>::Group(vector<string> set, map<pair<string, string>, string> userTab, char op){
	operation = op; //assign operation to users operation
	groupMembers = set; //assign groupMembers to users set
	table = userTab; //assign table to Users table.
	
}//end constructor

Group<int>::Group(int num) { //the default constructor for int mod group
	
	for (int i = 0; i < num; i++) {
		groupMembers.push_back(i); //we just set up the vector as 0,1,2...,num-1
	}
	operation = '+';//operation will be + since int mod
}

void Group<int>::setIntGroup() {
	vector<int> v;
	for (unsigned int i = 0; i < groupMembers.size()+1; i++) {
		group.push_back(v);//push on a new vector each row
		for (unsigned int j = 0; j < groupMembers.size()+1; j++) {
			if (i == 0 && j == 0) { //for the top left square set it to 0, we will replace in get function.
				group[i].push_back(0);
			}
			else if(i==0){//now we set up the rest of the top row
				group[i].push_back(groupMembers.at(j - 1));
			}
			else {//now we set up the rest of the table
				if (j == 0) {
					group[i].push_back(i - 1);//set up the vertical axis
				}
				else {//else just add in mod n
					int a;
					a = (groupMembers.at(i - 1) + groupMembers.at(j - 1)) % (groupMembers.size());
					group[i].push_back(a);
				}
			}
		}
	}


}

void Group<int>::getIntGroup() {
	for (unsigned int i = 0; i < groupMembers.size() + 1; i++) { //we just iterate over it twice
		for (unsigned int j = 0; j < groupMembers.size() + 1; j++) {
			if (i == 0 && j == 0) { //check to see if we are at the 0,0th indice (where the + should go)
				cout << operation << "\t";
			}
			else { //and if we arent, we just outpuut the group.
				cout << group[i][j] << "\t";
			}
		}
		cout << endl;
	}
}

void Group<string>::checkAbelian() {
	map <pair<string, string>, string>::iterator itr; //iterator we use over the map
	map <pair<string, string>, string>::iterator it; //iterator we use over the map for looking for second element
	bool isFalse = false; //bool I need for breaking
	for (itr = table.begin(); itr != table.end(); itr++) {// so we begin by iterating over the whole thing.
		for (it = table.begin(); it != table.end(); it++) {//then, we iterate again over the whole map
			if (itr->first.first == it->first.second) {//check if the first element in the pair of the outter for = the second elem of the pair in inner for
				if (itr->first.second == it->first.first) {//check if second element in the pair of the outer for = the first of the inner fors pair
					if (itr->second != it->second) {//finally, if both those are true (ie we have established that we are checking an commutative "pairing") then we check if what they both map to are the same
						abelian = false;//if its not, set association false, and we no longer need to check, since in an abelian  group all elems must commute.
						isFalse = true; //also set this to true so we can break out of the outer for.
						break;//break.
					}//end inner inner if
				}//end inner if
			}//end outer if
		}//end inner for
		if (isFalse) { //if commutation is false break.
			break;
		}//end if
	}//end outer for
	
}//end checkAbelian

void Group<string>::checkAssociative() {
	map <pair<string, string>, string>::iterator itr; //iterator we use over the map
	map <pair<string, string>, string>::iterator it; //iterator we use over the map for looking for second element
	map <pair<string, string>, string>::iterator itra; //iterator needed for finding (b+c) (is below)
	//the variables below follow the following naming convention: d=(a+b)+c, e=(b+c), and f=a+(b+c)
	string a = " ";
	string b = " ";
	string c = " ";
	string d = " ";
	string e = " ";
	string f = " ";
	bool isFalse = false;//similar to isabelian, need this to gt out of nested for loops
	for (itr = table.begin(); itr != table.end(); itr++) {
		a = itr->first.first; //so now we assign a
		b = itr->first.second;//and assign b
		for (unsigned int i = 0; i < groupMembers.size();i++) {
			c = groupMembers.at(i);//ok, so now we have a,b , and c
			//so right now, the thing is we have (a+b) (itr->second), but we dont have (b+c). Lets find it.
			for (itra = table.begin(); itra != table.end(); itra++) {//so we look for b+c
				if (itra->first.first == b && itra->first.second == c) {//if we find the pair b and c
					e = itra->second;//then let e=b+c
					break; //and break, we have e now.
				} //end if
			}//end for (itra)
			for (it = table.begin(); it != table.end(); it++) {//new for, we find d and f.
				if (it->first.first == itr->second && it->first.second==c) {//so if our pair in the map is (a+b) (ie itr->second), and c
					d = it->second; //so if we have (a+b)+c, let the result be d
				}//end if
				if (it->first.first == a && it->first.second == e) {//otherwise, if we cant find (a+b)+c, can we find a+(b+c)? Not an elif, because what if user enters the group e. We wanna make sure something isnt both d and f.
					f = it->second;//then the result is f.
				}//end if
			}//end for (it)
			if (d != f) {//Finally, we check, is (a+b)+c=a+(b+c)?
				associative = false;//if its not, the set isnt associative
				isFalse = true; //hence, we break everywhere
				break;
			}//end if
		}//end for(i)
		if (isFalse) {
			break;
		}//end if
	}//end for (itr)
	
}//end checkassoc

void Group<string>::findIdentity() {
	map <pair<string, string>, string>::iterator itr; //iterator we use over the map
	int j = 0;//var we will use to check if multiple elems
	for (unsigned int i = 0; i < groupMembers.size();i++) {// so we begin by iterating over the whole thing.
		identityExists = true; //gotta initalize this uphere, since the bewlo code will probably make it false
		for (itr = table.begin(); itr != table.end(); itr++) {//then, we iterate again over the whole map
			if (itr->first.first == groupMembers.at(i)) {//so first, check if first elem in pair is our potential identity or not
				if (itr->second != itr->first.second) {// then check if the identity times whatever equals the whatever
					identityExists = false;//if our second elem of the pair doesnt map to itself at all for any pair, then this is not our identity
					break; //and we can break
				}//end inner if
			}//end outer if
			if (itr->first.second == groupMembers.at(i)) {//we also wanna check if the second elem of the pair is the potential identity
				if (itr->second != itr->first.first) {//so check if whatever times identity equals whatever
					identityExists = false;//if our second elem of the pair doesnt map to itself at all for any pair, then this is not our identity
					break; //and we can break
				}//end inenr if
			}//end outer if
		}//end inner for
		if (identityExists) {//so if after all that identiyExists isnt false
			identity = groupMembers.at(i);//then the groupmember is indeed the identity
			j =j+1;//and add 1 to j. Later, we will check if j is 0 1, or >1, to determine if identity exists, or why it doesn't
		}//end if

	}//end outer for
	//ok, so now we've "found any identities". Now we need j. The following switch isnt necessarily needed, it's just a saftey
	
	switch (j) {//we use a switch
	case 0://if j is 0
		identityExists = false;//there exists no identity
		break;
	case 1: //if j is 1, there exists one identity
		identityExists = true;
		break;
	default: //else, there are multiple identities
		identityCheck = true;
	}//end switch

	
}//end findIdentity

void Group<string>::checkInverses() {//so this will only be called after the identity has been established
	map <pair<string, string>, string>::iterator itr; //iterator we use over the map
	map <pair<string, string>, string>::iterator it;
	bool loop = false;//need this to know whether to continue or not
	for (unsigned int i = 0; i < groupMembers.size(); i++) {// so we begin by iterating over the whole set.
		if (i != 0) {//if i !=0, we gotta check if we've already included the elem with its pair inverse
			for (unsigned int k = 0; k < groupInverses.size(); k++) {//so iterate over groupInverses, checking.
				if (groupInverses.at(k).first == groupMembers.at(i) || groupInverses.at(k).second == groupMembers.at(i)) {//check if the current pair contains groupMembers.at(i) in it.
					loop = true;//so if we find it, break outta this loop, and continue to next i.
					break;
				}//end if

			}//end for

		}//end if
		if (loop) {//if our current elem already in the vector
			loop = false; //reinitlaize loop
			continue;// and continue
		}
		//now we actually find inverse pairings
		for (itr = table.begin(); itr != table.end(); itr++) {
			if (itr->first.first == groupMembers.at(i) && itr->second == identity) {//first we check if we've actually found an instance of groupMembers.at(i) or not. Also, we will check if this is an instance of our element mapping to the identity
				string it = table.find(make_pair(itr->first.second, groupMembers.at(i)))->second; //we set a variable equal to whatever the reverse of the above pairing maps to
				if (it == identity) {//check if in reverse the potential pair map to the identity or not
					groupInverses.push_back(make_pair(groupMembers.at(i), itr->first.second));//then store the inverses together
					break; //and break, becausee we have found inverses
				}//end if
				else {//otherwise, we dont have unique inverses for each element
					inverses = false; //we set inverses to false
					break; //and break
				}//end else
			}//end if
			
		}//end inner for
		if (!inverses) {//we check if we need to loop, or if the inverse property is invalid
			break; //if inverses is invalid, we break
		}//end if
	}//end outer for

}//end checkInverses

void Group<string>::checkGroup() {
	checkAssociative(); //first we see if the group is associative
	if (associative) {//if it is associative, then run identity
		findIdentity();
		if (identityExists) {//if identity exists then check inverses
			checkInverses();
			if (!inverses) {// if inverses exists, then we have a group, if it doesnt we dont, and isGroup is already initalized as true, so we just need to amke it false if needed
				isGroup = false;
			}//end inner if
		}//end outer if
		else {//otherwise we dont have a group
			isGroup = false;
		}
	}//end if
	else { //if its not associative, let isGroup be false
		isGroup = false;
	}//end else
}

void Group<string>::getGroup() {
	checkGroup();//so now check if we have a group or not
	if (isGroup) {// if its a group we now display it and relevant info
		checkAbelian(); //first we check if it is abelian

		cout << "Your set of elements: "; //here we display what they inputted
		for (unsigned int i = 0; i < groupMembers.size(); i++) {
			cout << groupMembers.at(i) << ", ";
		}//end for
		//and now we tell them it's a group
		cout << "is a group under the operation: " << operation << "." << endl;
		
		if (abelian) { //if it's abelian we tell them
			cout << "your group is abelian." << endl;
		}//end if
		else {//end else
			cout << "your group is not abelian." << endl;
		}
		//now we display the identity
		cout << "The identity element is: " << identity << endl;
		//now we tell them all the inverse pairs
		cout << "The inverse pairs are as follows: " << endl;
		for (unsigned int i = 0; i < groupInverses.size(); i++) {
			cout << groupInverses.at(i).first << " and " << groupInverses.at(i).second << " are inverses." << endl;
		}//end for
		
		//finally, we display the group table.
		//first we display the first row:
		cout << operation << "\t";
		for (unsigned int i = 0; i < groupMembers.size(); i++) {
			if (i == groupMembers.size() - 1) {//if we on the last elem of the row, we end the line
				cout << groupMembers.at(i) << endl;
			}//end if
			else {//otherwise display as normal
				cout << groupMembers.at(i) << "\t";
			}//end else
		}//end for 
		//now we display the rest of the table
		for (unsigned int i = 0; i < groupMembers.size(); i++) {
			cout << groupMembers.at(i) << "\t"; //first we display the element in column 1
			for (unsigned int j = 0; j < groupMembers.size(); j++) {//now we iterate through , outputting elements from our map
				if (j == groupMembers.size() - 1) { //if its the last elem, we need to new line
					cout << table.at(make_pair(groupMembers.at(i), groupMembers.at(j))) << endl;
				}//end if
				else { //otherwise just search the map for the correct element 
					cout << table.at(make_pair(groupMembers.at(i), groupMembers.at(j))) << "\t";
				}//end else
			}//end for

		}//end for
	}//end if
	else {//otherwise if its not a group, we say why it's not.
		if (!associative) { //so first, check if it isnt associative, this is the first fucntion we run in check, hence the first place for an error to occur
			cout << "Your set of elements: "; //here we display what they inputted
			for (unsigned int i = 0; i < groupMembers.size(); i++) {
				cout << groupMembers.at(i) << ", ";
			}//end for
			//and now we tell them it's not associative
			cout << "is not a group under the operation: " << operation << ", because all the elements do not associate" << endl;
		}//end if
		else if (!identityExists) {//otherwise, if the identity doesnt exist, we tell them this is why their set isnt a group
			cout << "Your set of elements: "; //here we display what they inputted
			for (unsigned int i = 0; i < groupMembers.size(); i++) {
				cout << groupMembers.at(i) << ", ";
			}//end for
			cout << "is not a group under " << operation << ", because it does not contain any identity elements." << endl;
		}//end elif
		else if (identityCheck) {//otherwise, if their are too many identities, we tell them this is why their set isnt a group
			cout << "Your set of elements: "; //here we display what they inputted
			for (unsigned int i = 0; i < groupMembers.size(); i++) {
				cout << groupMembers.at(i) << ", ";
			}//end for
			cout << "is not a group under " << operation << ", because it does not contain a unique identity element." << endl;
		}//end elif
		else {//otherwise, it wasn't a group because they didnt fulfill the inverse property
			cout << "Your set of elements: "; //here we display what they inputted
			for (unsigned int i = 0; i < groupMembers.size(); i++) {
				cout << groupMembers.at(i) << ", ";
			}//end for
			cout << "is not a group under the operation: " << operation << ", because each element in the set does not have a unique inverse" << endl;
		}//end inner else
	}//end outr else
}