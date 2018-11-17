///////////////////////////////////////////////////////////////////////////////
// project2.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.hh"
#include "timer.hh"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list(string_vector & strings) {
  for (int i = 0; i < strings.size(); i++){
		if (rand()%2 == 0){ //clock seeded rand :D
			strings.insert(strings.begin(), strings[i]);
			strings.erase(strings.begin()+i+1);
			
		}
	}
  return;
}

//-----------------------------------------------------------------------------
void merge(string_vector & strings, size_t start, size_t mid, size_t end) {
	inplace_merge(strings.begin()+start, mid + strings.begin(), strings.end()); 
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings, size_t start, size_t end) {
  if (end - start > 1){
		mergesort(strings, start, (start + (end-start)/2));
		mergesort(strings, (start + (end-start)/2 ), end);
		merge(strings, start, (start + (end-start)/2), end);
	}
}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition(string_vector & strings, int start, int end) {
	string x = strings[start];
	int i = start - 1;
	int j = end + 1;
while(true)
{
	do{
		j--;
	}while(strings[j] > x);
	do{
		i++;
	}while(strings[i] < x);

	if (i < j){
	string temp = strings[i];
	strings[i] = strings[j];
	strings[j] = temp;
	}
	else{
		if (start == end) {return 0;}
		//if (start == 0 && end == 7) {return 4;}
		return j;
	}
}
  return 0;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings, int start, int end) {
	if ( start < end ){
		if (end - start < 2) return;
		int q = hoare_partition(strings, start, end);
		
		quicksort(strings,q+1, end);
		quicksort(strings,start, q);
	}
  return;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path) 
{
  //std::cout << "Loading words from [" << path << "]" << std::endl;
  words.clear();
  std::ifstream ifs(path.c_str());
  if (!ifs.is_open() || !ifs.good()) {
    //cout << "Failed to open [" << path << "]" << std::endl;
    return false;
  }
  int countWordsLoaded = 0;
  while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    words.push_back(lineBuffer);
    countWordsLoaded++;
  }
  //std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
  return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings) {
 Timer timer;
  if (strings.size() == 0) {
    return;
  }
  mergesort(strings, 0, strings.size()-1);
		

	cerr << "\nThe time elapsed for this merge was: " << timer.elapsed();
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings) {
Timer timer;
  if (strings.size() == 0) {
    return;
  }
  quicksort(strings, 0, strings.size() - 1);
cerr << "\nThe time elapsed for this quicksort was: " << timer.elapsed();
  return;
}

