#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>

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
    double val;
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


std::vector<double> genFloatVector(int size){
	std::vector<double> output;
	for(int i = 0; i < size; i++){
		output.push_back((double(rand()%1000000)/10)-50000);
	}
	
	return output;
}

int main(){
	int start, end, interval;
	std::cout << "Enter start point: "; std::cin >> start;
	std::cout << "Enter end point: "; std::cin >> end;
	std::cout << "Enter interval: "; std::cin >> interval;
	
	
	for(int size = start; size <= end; size += interval){
		int time = 0;
		int iterations = 1;
		
		int startTime = 0;
		int endTime = 0;
		std::vector<double> arrayToSort = genFloatVector(size);
		
		startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			std::vector<double> quickSorted = quickSort(arrayToSort);
		endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		time += endTime-startTime;
		
		std::cout << "Sorting " << size << " items:" << std::endl;
		std::cout << "	Quick Sort Time: " << time << " μs" << std::endl;
	}
	return 0;
}