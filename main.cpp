#include <iostream>
#include <vector>
#include <sstream>

template <typename T>
void outputArray(std::vector<T> input){
	for(int i = 0; i < input.size(); i++){
		std::cout << input[i];
		if(i != input.size()-1){
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}
std::vector<double> doubleVectorInput(){
	std::string inputString;
    getline(std::cin, inputString);
    std::vector<double> array;
    std::istringstream iss(inputString);
    float val;
    while(iss >> val){
        array.push_back(val);
    }
    return array;  	
}

std::vector<double> quickSort(std::vector<double> input){
	if(input.size() > 1){
		double first = input[0];
		std::vector<double> left;
		std::vector<double> right;
		std::vector<double> output;
		
		for(int i = input.size(); i > 1; i--){
			if(input.back() < first){
				left.push_back(input.back());
				input.pop_back();
			}
			else{
				right.push_back(input.back());
				input.pop_back();
			}
		}
		left = quickSort(left);
		right = quickSort(right);
		
		output.insert(output.end(), left.begin(), left.end());
		output.push_back(first);
		output.insert(output.end(), right.begin(), right.end());
		
		
		return output;
	}
	else{
		return input;
	}
}

int main(){
	std::cout << "Enter array to Sort: "; std::vector<double> array = doubleVectorInput();
	std::cout << std::endl;
	std::cout << "Sorted array: "; 
	std::vector<double> sorted = quickSort(array);
	outputArray(sorted);
	
	
	return 0;
}