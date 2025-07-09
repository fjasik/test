# Andy's questions

- What output would you expect from the following code:

```cpp
int global_count = 0;

int expensive_calculation() {
    return 1; // dummy implementation
}

void increment_100() {
    for (int i = 0; i < 100; i++){
        global_count += expensive_calculation();  
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(increment_100);
    }
    std::cout << global_count << std::endl;
}
```

- How could we fix it?
- Is it safe to read `global_count` like we are?
- Why do you think we have 10 threads each doing 100 things rather than 1000 threads each doing 1 thing?
- Is the following code deterministic? If not how could it be made so?

```cpp
std::atomic<int> global_count;

void maybe_increment_count() {
    if (global_count >= 5) {
        return;
    }
    global_count++;
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(maybe_increment_count);
    }

    for (const auto& thread : threads) {
        thead.join();
    }

    std::cout << global_count.load() << std::endl;
}
```

- Atomics have method `compare_exchange_weak` (will be explained). Can you fix `maybe_increment_count` using this?
