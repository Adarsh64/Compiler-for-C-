#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include "tinyexpr.h"

std::regex istemp("^t[0-9]*$");
std::regex isid("^[A-Za-z][A-Za-z0-9_]*$");

char arr[][3] = {"+", "-", "*", "/", "*", "&", "|", "^", ">>", "<<", "==", ">=", "<=", "!=", ">", "<"};

std::vector<std::string> binary_operators(arr,arr+16);

void printicg(std::vector<std::string> list_of_lines,std::string message=""){
	
	//std::cout<<std::toupper(message);
	std::cout<<message<<std::endl;
	
	std::vector<std::string>::iterator i;
	
	for (i = list_of_lines.begin(); i < list_of_lines.end(); i++) 
        std::cout << *i << std::endl; 
	
}

bool isNumber(std::string s) 
{ 
    for (int i = 0; i < s.length(); i++) 
        if (std::isdigit(s[i]) == false) 
            return false; 
  
    return true; 
} 

	
	
std::string eval_wrap(std::string line){

		std::vector<std::string> result; 
		boost::split(result, line, boost::is_any_of(" "));
		if (result.size()!=5){
			std::cout<<"H1"<<std::endl;
			return line;
		}
		if (result[1] != "=" || (std::find(binary_operators.begin(), binary_operators.end(), result[3]) == binary_operators.end())){
			std::cout<<"H2"<<std::endl;
			return line;
		}
		std::cout<<"1:"<<isNumber(result[2])<<std::endl;
		std::cout<<"2:"<<isNumber(result[4])<<std::endl;
		std::cout<<result[4].c_str()<<std::endl;
		std::cout<<isNumber(result[4].c_str())<<std::endl;
		if (isNumber(result[2]) && isNumber(result[4])){
			std::cout<<"Entered"<<std::endl;
			std::string expr = result[2]+result[3]+result[4];
			std::string ret = result[0]+result[1]+std::to_string(te_interp(expr.c_str(),0));
			return ret;
		}
		
		if (isNumber(result[2]) || isNumber(result[4])){
			std::string op1,op2;
			op1 = (std::regex_match(result[2],isid)) ? "5" : result[2];
			op2 = (std::regex_match(result[4],isid)) ? "5" : result[4];
			std::cout<<op1<<op2<<std::endl;
			/*if(std::regex_match(result[2],isid)){
				std::cout<<"H3"<<std::endl;
				op1 = "5";
			}
			else{
				std::cout<<"H4"<<std::endl;
				op1 = result[2];
			}
			std::string ch = result[4];
			if(std::regex_match(ch.c_str(),isid)){
				std::cout<<"H5 "<< ch.c_str() <<std::endl;
				op2 = "5";
			}
			else{
				std::cout<<"H6 "<<ch.c_str()<<std::endl;
				op2 = result[4];
			}*/
			std::string op = result[3];
			std::string exprn = op1+op+op2;
			//std::cout<<exprn<<std::endl;
			int ans = int(te_interp(exprn.c_str(),0));
			//std::cout<<ans<<std::endl;
			if (ans == 0)
				return (result[0]+result[1]+"0");
			else if (ans == 5)
				if (std::regex_match(result[2],isid) && isNumber(result[4]))
					return result[0]+result[1]+result[2];
				else if (std::regex_match(result[4],isid) && isNumber(result[2]))
					return result[0]+result[1]+result[4];
			else if (ans == -5 && result[2] == "0")
				return result[0]+result[1]+"-"+result[4];
			return line;
		}
		
		return line;
}
		/*
		try : 
			result = int(eval(op1+op+op2))
			if result == 0 : #multiplication with 0
				return " ".join([tokens[0],tokens[1], "0"])
			elif result == 5 : #add zero, subtract 0, multiply 1, divide 1
				if isid(tokens[2]) and tokens[4].isNumber() :
					return " ".join([tokens[0], tokens[1], tokens[2]])
				elif isid(tokens[4]) and tokens[2].isNumber():
					return " ".join([tokens[0], tokens[1], tokens[4]])
			elif result == -5 and tokens[2] == "0" : # 0 - id
				return " ".join([tokens[0], tokens[1], "-"+tokens[4]])
			return " ".join(tokens)

		except NameError :
			return line
		except ZeroDivisionError :
			print("Division By Zero is undefined")
			quit()
	return line*/

/*def fold_constants(list_of_lines) :
	"""
	Some expressions that can have a definite answer need not be waste run time resources :
	e.g.
	1. number + number, number - number etc.
	2. identifier + 0, identfier / 0, identifer - 0, identifier*0 and their commutatives
	3. identifier * 1, identifier / 1
	"""

	new_list_of_lines = []
	for line in list_of_lines :
		new_list_of_lines.append(eval_wrap(line))
	return new_list_of_lines*/
	
std::vector<std::string> fold_constants(std::vector<std::string> list_of_lines){

		std::vector<std::string> new_list_of_lines;
		std::vector<std::string>::iterator i;
	
		for (i = list_of_lines.begin(); i < list_of_lines.end(); i++){
			new_list_of_lines.push_back(eval_wrap(*i));
		}
		
		return new_list_of_lines;
}





std::vector<std::string> remove_dead_code(std::vector<std::string> list_of_lines){


	int num_lines = list_of_lines.size();
	std::set<std::string> temp_on_lhs;
	std::set<std::string> useful_temps;
	std::set<std::string> temps_to_remove;
	
	std::vector<std::string>::iterator i;
	
	for (i = list_of_lines.begin(); i < list_of_lines.end(); i++){ 
	
		std::vector<std::string> result; 
		boost::split(result, *i, boost::is_any_of(" ")); 
		
		if (std::regex_match(result[0],istemp))
			temp_on_lhs.insert(result[0]);
 
	
	}
	
	for (i = list_of_lines.begin(); i < list_of_lines.end(); i++){ 
	
		std::vector<std::string> result; 
		boost::split(result, *i, boost::is_any_of(" ")); 
		
		if (result.size()>=2)
			if (std::regex_match(result[1],istemp))
				useful_temps.insert(result[1]);
		if (result.size()>=3)
			if (std::regex_match(result[2],istemp))
				useful_temps.insert(result[2]);
		if (result.size()>=4)
			if (std::regex_match(result[3],istemp))
				useful_temps.insert(result[3]);
		if (result.size()>=5)
			if (std::regex_match(result[4],istemp))
				useful_temps.insert(result[4]);
	
	}
	
	std::set_difference(temp_on_lhs.begin(), temp_on_lhs.end(), useful_temps.begin(), useful_temps.end(), std::inserter(temps_to_remove, temps_to_remove.end()));
	
	std::vector<std::string> new_list_of_lines;
	
	for (i = list_of_lines.begin(); i < list_of_lines.end(); i++){ 
	
		std::vector<std::string> result; 
		boost::split(result, *i, boost::is_any_of(" ")); 
		
		if (std::find(temps_to_remove.begin(), temps_to_remove.end(), result[0]) == temps_to_remove.end())
			new_list_of_lines.push_back(*i);
	}
	
	if (num_lines==new_list_of_lines.size())
		return new_list_of_lines;
	return remove_dead_code(new_list_of_lines);
	
	
	
}


int main(){
	
	/*std::string ch = "a";
	std::cout<<std::regex_match(ch,isid)<<std::endl;
	std::cout<<isNumber("2")<<std::endl;*/
	
	
	
	std::ifstream in("f_output.txt");
	std::string str;
	std::vector<std::string> list_of_lines;
	std::vector<std::string> without_deadcode;
	std::vector<std::string> folded_constant;
	while (std::getline(in, str)) {
		list_of_lines.push_back(str);
		//std::cout << str << std::endl;
	}
	printicg(list_of_lines,"ICG");
	without_deadcode = remove_dead_code(list_of_lines);
	printicg(without_deadcode,"Optimized ICG after removing dead code");
	//folded_constant = fold_constants(without_deadcode);
	//printicg(folded_constant, "Optimized ICG after constant folding");
	
	//std::cout<<te_interp("20+5*3",0)<<std::endl;
	
	
	return 0;
}
