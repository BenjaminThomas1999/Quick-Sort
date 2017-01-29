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
std::vector<double> bubbleSort(std::vector<double> array){
	double tmp;
	int passCounter = 0;//counts how many times no swap is made
	while(passCounter < array.size()-1){//when no swaps are made over entire list, list is sorted
		for(int i = 0; i < array.size()-1; ++i){
			if(array[i]>array[i+1]){
				tmp = array[i+1];
				array[i+1] = array[i];
				array[i] = tmp;
				passCounter = 0;
			}
			else{
				passCounter++;
			}
		}
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
std::vector<double> merge(std::vector<double> firstHalf, std::vector<double> secondHalf){
	std::vector<double> combined;
	
	for(int i = firstHalf.size() + secondHalf.size(); i > 0;  i--){//merge two vectors
		if(!firstHalf.empty() && !secondHalf.empty() && firstHalf.back() > secondHalf.back() ){
			combined.push_back(firstHalf.back());
			firstHalf.pop_back();
		}
		else if(!firstHalf.empty() && !secondHalf.empty() && firstHalf.back() <= secondHalf.back() ){
			combined.push_back(secondHalf.back());
			secondHalf.pop_back();
		}
		else if(!firstHalf.empty() && secondHalf.empty()){
			combined.push_back(firstHalf.back());
			firstHalf.pop_back();
		}
		else if(firstHalf.empty() && !secondHalf.empty()){
			combined.push_back(secondHalf.back());
			secondHalf.pop_back();
		}
	}
	
	std::vector<double> revCombined;//reverse merged vectors. Vectors don't have pop_front and I didn't want to use lists.
	
	for(int i = 0; i < combined.size(); i++){
		revCombined.push_back(combined[combined.size()-i-1]);
	}
	return revCombined;
}

std::vector<double> mergeSort(std::vector<double> inputArray){//for example [9, 8, 1] as input
	if(inputArray.size() > 1){
		std::vector<double> firstHalf;
		std::vector<double> secondHalf;
		
		for(int i = 0; i < inputArray.size()/2; i++){//auto round the input array because size() returns int
			firstHalf.push_back(inputArray[i]);
		}//first half = [9, 8]
		
		for(int i = inputArray.size()/2; i < inputArray.size(); i++){
			secondHalf.push_back(inputArray[i]);
		}//second half = [1]
		
		return merge(mergeSort(firstHalf), mergeSort(secondHalf));
	}
	else{
		return inputArray;
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
		int mergeTimeSum = 0;
		int quickTimeSum = 0;
		int bubbleTimeSum = 0;
		int iterations = 10;
		for(int i = 0; i < iterations; i++){
			int startTime = 0;
			int endTime = 0;
			std::vector<double> arrayToSort = genFloatVector(size);
			
			startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
				std::vector<double> quickSorted = quickSort(arrayToSort);
			endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			quickTimeSum += endTime-startTime;
			
			startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
				std::vector<double> mergeSorted = mergeSort(arrayToSort);
			endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			mergeTimeSum += endTime-startTime;
			
			startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
				std::vector<double> bubbleSorted = bubbleSort(arrayToSort);
			endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			bubbleTimeSum += endTime-startTime;
			
			if(mergeSorted != quickSorted || quickSorted != bubbleSorted){
				std::cout << "Error: Sort error. \n\n";
				return -1;
			}
		}
		
		std::cout << "Sorting " << size << " items:" << std::endl;
		std::cout << "	Quick  Sort Time:   " << quickTimeSum/iterations << " μs" << std::endl;
		std::cout << "	Merge  Sort Time:   " << mergeTimeSum/iterations << " μs" << std::endl;
		std::cout << "	Bubble Sort Time:   " << bubbleTimeSum/iterations << " μs" << std::endl;
	}
	return 0;
}
