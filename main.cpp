#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

void benchInserts() {
  std::vector<uint64_t> input(10'000'000);
  int n = 0;
  std::generate(input.begin(), input.end(), [&n]() { return n++; });
  std::unordered_map<uint64_t, uint64_t> map;
  map.reserve(10'000'000);
  map.max_load_factor(10000);

  std::cout << "Insert test: " << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  for (auto i = 0; i < 5'000'000; ++i) {
    map.emplace(input[i], input[i]);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto first5mm = std::chrono::duration_cast<std::chrono::microseconds>(
                      stop - start).count();

  start = std::chrono::high_resolution_clock::now();
  for (auto i = 5'000'000; i < 10'000'000; ++i) {
    map.emplace(input[i], input[i]);
  }
  stop = std::chrono::high_resolution_clock::now();
  auto second5mm = std::chrono::duration_cast<std::chrono::microseconds>(
                       stop - start).count();

  std::cout << "  Num buckets: " << map.bucket_count() << std::endl;
  std::cout << "  Load factor: " << map.load_factor() << std::endl;
  std::cout << "  Time to input 0-5mm: " << first5mm << " ms" << std::endl;
  std::cout << "  Time to input 5-10mm: " << second5mm << " ms" << std::endl;
}

void benchRemovals() {
  std::vector<uint64_t> input(10'000'000);
  int n = 0;
  std::generate(input.begin(), input.end(), [&n]() { return n++; });
  std::unordered_map<uint64_t, uint64_t> map;
  map.reserve(10'000'000);
  map.max_load_factor(10000);

  std::cout << "\nRemovals test: " << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  for (auto i = 0; i < 5'000'000; ++i) {
    map.emplace(input[i], input[i]);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto first5mm = std::chrono::duration_cast<std::chrono::microseconds>(
                      stop - start).count();

  start = std::chrono::high_resolution_clock::now();
  for (auto i = 0; i < 5'000'000; ++i) {
    map.erase(input[i]);
  }
  stop = std::chrono::high_resolution_clock::now();
  auto remove5mm = std::chrono::duration_cast<std::chrono::microseconds>(
                      stop - start).count();

  start = std::chrono::high_resolution_clock::now();
  for (auto i = 5'000'000; i < 10'000'000; ++i) {
    map.emplace(input[i], input[i]);
  }
  stop = std::chrono::high_resolution_clock::now();
  auto second5mm = std::chrono::duration_cast<std::chrono::microseconds>(
                       stop - start).count();

  std::cout << "  Num buckets: " << map.bucket_count() << std::endl;
  std::cout << "  Load factor: " << map.load_factor() << std::endl;
  std::cout << "  Time to input 0-5mm:  " << first5mm << " ms" << std::endl;
  std::cout << "  Time to remove 0-5mm: " << remove5mm << " ms" << std::endl;
  std::cout << "  Time to input 5-10mm: " << second5mm << " ms" << std::endl;
}

int main() {
  std::srand(0);
  benchInserts();
  benchRemovals();
return 0;
}
