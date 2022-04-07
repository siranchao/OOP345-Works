// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant

#include <exception>
#include "process_data.h"
using namespace std::placeholders;

namespace sdds_ws9 {

	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data && num_threads > 0 && averages && variances && p_indices;
	}


	ProcessData::ProcessData(std::string filename, int n_threads) {
		std::ifstream ifs(filename, std::ios::in | std::ios::binary);
		if (ifs.is_open()) {
			ifs.read((char*)&total_items, sizeof(total_items));
			data = new int[total_items];
			for (int i = 0; i < total_items; i++) {
				ifs.read((char*)&data[i], sizeof(data[i]));
			}

			std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
			std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
				<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
				<< data[total_items - 1] << "]\n";

			// Following statements initialize the variables added for multi-threaded 
			//   computation
			num_threads = n_threads;
			averages = new double[num_threads] {};
			variances = new double[num_threads] {};
			p_indices = new int[num_threads + 1]{};
			for (int i = 0; i < num_threads + 1; i++) {
				p_indices[i] = i * (total_items / num_threads);
			}

		}
		else {
			throw std::invalid_argument("cannot open file");
		}
	}
	
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.

	int ProcessData::operator()(std::string fileName, double& avg, double& var) {
		int val = 0;
		auto computeAvg = std::bind(computeAvgFactor, _1, p_indices[1], total_items, _2);
		auto computeVar = std::bind(computeVarFactor, _1, p_indices[1], total_items, std::ref(avg), _2);
		
		//compute avg
		std::vector<std::thread> process1;
		for (int i = 0; i < num_threads; i++) {
			process1.push_back(std::thread(computeAvg, &data[p_indices[i]], std::ref(averages[i])));
		}
		for (auto& ele : process1) {
			ele.join();
		}
		for (int i = 0; i < num_threads; i++) {
			avg += averages[i];
		}

		//computer var
		std::vector<std::thread> process2;
		for (int i = 0; i < num_threads; i++) {
			process2.push_back(std::thread(computeVar, &data[p_indices[i]], std::ref(variances[i])));
		}
		for (auto& ele : process2) {
			ele.join();
		}
		for (int i = 0; i < num_threads; i++) {
			var += variances[i];
		}

		//write data
		std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
		if (ofs.is_open()) {
			ofs.write((const char*)&total_items, sizeof(total_items));
			for (int i = 0; i < total_items; i++) {
				ofs.write((const char*)&data[i], sizeof(data[i]));
			}
			val = 1;
		}
		else {
			throw std::invalid_argument("cannot open file");
		}
		return val;
	}




}