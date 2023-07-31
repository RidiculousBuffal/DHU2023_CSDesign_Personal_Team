#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
template<class T>
struct chainNode {
    T element;
    chainNode<T> *next;//下一个节点的指针
    chainNode<T> *fa;//上一个节点的指针
    T key;
    chainNode(T element, chainNode<T> *fa, chainNode<T> *next) {
        this->element = element;
        this->fa = fa;
        this->next = next;
    }

    chainNode(chainNode<T> *fa, chainNode<T> *next) {
        this->fa = fa;
        this->next = next;
    }
    chainNode()
    {
        next=NULL;
        fa=NULL;
    }
    chainNode(T key,T element)
    {
        this->key=key;
        this->element=element;
    }
};
class LRUCache{
private:
    unordered_map<int,chainNode<int>*>cache;
    chainNode<int>*head;
    chainNode<int>*tail;
    int size;
    int capacity;
public:
    LRUCache(int _capacity):capacity(_capacity),size(0)
    {
        head=new chainNode<int>();
        tail=new chainNode<int>();
        head->next=tail;
        tail->fa=head;
    }
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        chainNode<int>* node = cache[key];
        moveToHead(node);
        return node->element;
    }
    void put(int key, int element) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            chainNode<int>* node = new chainNode<int>(key, element);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                chainNode<int>* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 element，并移到头部
            chainNode<int>* node = cache[key];
            node->element = element;
            moveToHead(node);
        }
    }

    void addToHead(chainNode<int>* node) {
        node->fa = head;
        node->next = head->next;
        head->next->fa = node;
        head->next = node;
    }

    void removeNode(chainNode<int>* node) {
        node->fa->next = node->next;
        node->next->fa = node->fa;
    }

    void moveToHead(chainNode<int>* node) {
        removeNode(node);
        addToHead(node);
    }

    chainNode<int>* removeTail() {
        chainNode<int>* node = tail->fa;
        removeNode(node);
        return node;
    }


};

int main() {
    int capacity;
    cin>>capacity;
    LRUCache lru(capacity);
    string x;
    while(cin>>x)
    {
        if(x=="get")
        {
            int a;
            cin>>a;
            cout<<lru.get(a)<<endl;
        }
        else
        {
            int k,v;
            cin>>k>>v;
            lru.put(k,v);
        }
    }
    return 0;
}