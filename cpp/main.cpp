/*
  g++ -O3
*/

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> list{10000, 100000, 1000000, 10000000, 100000000};

  std::vector<std::vector<int>> results_seq(list.size()),
      results_bin(list.size());
  std::vector<int> sort_time;

  for (std::size_t n{}; n < list.size(); ++n) {
    int num = list[n];
    std::vector<int> vector;
    for (std::size_t i{}; i < num; ++i) {
      vector.push_back(rand() % num);
    }

    // Sequential
    std::cout << '\n' << "Sequential Search:" << '\n';
    for (std::size_t i{}; i < 5; ++i) {
      std::cout << '\n'
                << "Sequential search number " << i << " with " << num
                << " values:" << '\n';
      int key{rand() % num};

      std::cout << "Looking for: " << key << '\n';

      auto start = std::chrono::high_resolution_clock::now();
      auto find_result{std::find(vector.begin(), vector.end(), key)};
      if (find_result != vector.end()) {
        std::cout << "Number: " << key
                  << " found at position: " << find_result - vector.begin()
                  << '\n';
      } else {
        std::cout << "Number not found." << '\n';
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count();
      std::cout << "Duration of execution: " << duration << " microseconds"
                << '\n';
      results_seq[n].push_back(duration);
    }

    // Time taken to sort the vector
    std::cout << '\n' << "Sorting the vector for binary search..." << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(vector.begin(), vector.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();
    std::cout << "Duration of execution: " << duration << " ms" << '\n';
    sort_time.push_back(duration);

    // Binary
    std::cout << '\n' << "Binary Search:" << '\n';
    for (std::size_t i{}; i < 5; ++i) {
      std::cout << '\n'
                << "Binary search number " << i << " with " << num
                << " values:" << '\n';
      int key{rand() % num};

      std::cout << "Looking for " << key << '\n';

      auto start = std::chrono::high_resolution_clock::now();
      auto find_result{std::binary_search(vector.begin(), vector.end(), key)};
      if (find_result) {
        std::cout << "Number: " << key << " found" << '\n';
      } else {
        std::cout << "Number not found." << '\n';
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count();
      std::cout << "Duration of execution: " << duration << " microseconds"
                << '\n';
      results_bin[n].push_back(duration);
    }
  }

  std::cout << '\n'
            << "End of execution" << '\n'
            << "Sequential search time:" << '\n';
  for (std::size_t i{}; i < list.size(); ++i) {
    int num{list[i]};
    std::cout << '\n' << "List " << num << ":";
    int add{0};
    for (std::size_t ele : results_seq[i]) {
      std::cout << " " << ele << "micros";
      add += ele;
    }
    std::cout << " | Average time: " << add / list.size() << "micros";
  }

  std::cout << "\n\nBinary search time:" << '\n';
  for (std::size_t i{}; i < list.size(); ++i) {
    int num{list[i]};
    std::cout << '\n' << "List " << num << ":";
    int add{0};
    for (std::size_t ele : results_bin[i]) {
      std::cout << " " << ele << "micros";
      add += ele;
    }
    std::cout << " | Time taken to sort the vector: " << sort_time[i] << "ms";
    std::cout << " | Average time: " << add / list.size() << "micros";
  }
  std::cout << '\n';

  return 0;
}
