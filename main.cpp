#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>


template <typename T>
void parallelMax(const std::vector<T> &v, const unsigned int &threadId, std::vector<int> &maxV, const unsigned int &numThreads) {

  auto size = v.size();
  auto partitionSize = size / numThreads;
  int extra = 0;
  if (threadId == 1)
	extra = size % numThreads; // extra work done by 1st thread.

  auto b = v.begin() + (threadId - 1) * partitionSize;
  auto e = b + partitionSize;
  maxV[threadId] = *std::max_element(b, e);
}


template <typename T>
auto parallelSearch(const std::vector<T> &c, const unsigned int numThreads) {

  unsigned int maxThreads = std::thread::hardware_concurrency();
  if (numThreads > maxThreads)
	std::runtime_error("numThreads exceeds the max supported threads in this system.");

  std::thread threads[numThreads];
  std::vector<int> maxV(c.size(), 0);

  for (long long i = 0; i < numThreads; ++i) {
	threads[i] = std::thread(parallelMax<T>, std::ref(c), std::ref(i), std::ref(maxV), std::ref(numThreads));
  }
  for (long long i = 0; i < numThreads; ++i) {
	threads[i].join();
  }

  return *std::max_element(maxV.begin(), maxV.end());
}


int main() {
  std::vector<int> v { 10, 12, 14, 17, 20, 25, 10, 27, 3000, 2002, 235, 23, 523, 5, 23, 52, 3352, 35, 235,23, 5, 2, 35 };
  std::cout << parallelSearch(v, 3) << '\n';
  return 0;
}
