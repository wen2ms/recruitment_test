#include <iostream>
#include <list>
#include <map>
#include <memory>

class LRUCache {
  public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto it = cache_map_.find(key);
        if (it != cache_map_.end()) {
            lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
            return it->second->second;
        }
        return -1;
    }

    void put(int key, int value) {
        auto it = cache_map_.find(key);
        if (it != cache_map_.end()) {
            lru_list_.splice(lru_list_.begin(), lru_list_, it->second);
            it->second->second = value;
            return;
        }

        if (lru_list_.size() == capacity_) {
            int lru_key = lru_list_.back().first;
            lru_list_.pop_back();
            cache_map_.erase(lru_key);
        }
        lru_list_.push_front({key, value});
        cache_map_.insert({key, lru_list_.begin()});
    }

  private:
    int capacity_;
    std::list<std::pair<int, int>> lru_list_;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_map_;
};

int main() {
    std::shared_ptr<LRUCache> lru_cache(new LRUCache(2));

    lru_cache->put(1, 1);
    lru_cache->put(2, 2); 

    std::cout << lru_cache->get(1) << std::endl;

    lru_cache->put(3, 3); 
    
    std::cout << lru_cache->get(2) << std::endl;

    lru_cache->put(4, 4); 
    
    std::cout << lru_cache->get(1) << std::endl;
    std::cout << lru_cache->get(3) << std::endl;
    std::cout << lru_cache->get(4) << std::endl;

    return 0;
}