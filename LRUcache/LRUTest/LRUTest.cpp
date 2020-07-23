#include "pch.h"

#include <stdio.h>
#include <iostream>
#include <map>



using namespace std;

class LRUCache {

private:
	typedef struct Node {
		int key;
		int value;
		struct Node* preNode;
		struct Node* nextNode;
	}NODE;

	map<int, NODE*> m_cacheMap;
	NODE* m_headNode;
	NODE* m_tailNode;
	int m_MaxSize;
	int m_nCount;
	bool m_isFull;

public:
	LRUCache(int capacity) {
		m_MaxSize = capacity;
		m_headNode = nullptr;
		m_tailNode = nullptr;
		m_nCount = 0;
		m_isFull = false;
	}

	int get(int key) {
		if (m_cacheMap.find(key) == m_cacheMap.end()) {
			cout << -1 << endl;
			return -1;
		}
		update(key);
		cout << m_cacheMap[key]->value << endl;
		return m_cacheMap[key]->value;
	}

	void put(int key, int value) {
		if (m_headNode == nullptr && m_tailNode == nullptr) {
			addHeadNode(key, value);
		}
		else {
			add(key, value);
		}
		if (m_nCount != m_MaxSize) {
			m_nCount++;
		}
		if (m_nCount == m_MaxSize) {
			m_isFull = true;
		}
	}

	//链表更新
	void update(int key) {
		if (m_headNode == m_tailNode) {
			return;
		}
		if (m_cacheMap[key] == m_headNode && m_MaxSize >= 2) {
			m_cacheMap[key]->nextNode->preNode = nullptr;
			m_headNode = m_cacheMap[key]->nextNode;
			m_tailNode->nextNode = m_cacheMap[key];
			m_cacheMap[key]->preNode = m_tailNode;
			m_cacheMap[key]->nextNode = nullptr;
			m_tailNode = m_cacheMap[key];
		}
		else if(m_cacheMap[key] != m_tailNode && m_MaxSize > 2){
			m_cacheMap[key]->preNode->nextNode = m_cacheMap[key]->nextNode;
			m_cacheMap[key]->nextNode->preNode = m_cacheMap[key]->preNode;
			m_tailNode->nextNode = m_cacheMap[key];
			m_cacheMap[key]->preNode = m_tailNode;
			m_cacheMap[key]->nextNode = nullptr;
			m_tailNode = m_cacheMap[key];
		}
	}

	void add(int key, int value) {
		if (m_cacheMap.find(key) != m_cacheMap.end()) {
			eraseMap(key);
		}
		else {
			if (m_isFull) {
				deleteHead();
			}
		}
		if (m_headNode == nullptr && m_tailNode == nullptr) {
			addHeadNode(key, value);
		}
		else {
			addTail(key, value);
			m_cacheMap.insert(pair<int, NODE*>(key, m_tailNode));
		}
	}

	void eraseMap(int key) {
		if (m_cacheMap.find(key) != m_cacheMap.end()) {
			eraseNode(&(m_cacheMap[key]));
			m_cacheMap.erase(key);
		}
	}

	void eraseNode(NODE** node) {
		if (*node == m_headNode) {
			deleteHead();
		}
		else if (*node == m_tailNode) {
			m_tailNode = m_tailNode->preNode;
			delete m_tailNode->nextNode;
			m_tailNode->nextNode = nullptr;
		}
		else {
			(*node)->preNode->nextNode = (*node)->nextNode;
			(*node)->nextNode->preNode = (*node)->preNode;
			delete *node;
		}
		m_nCount--;
	}

	void addHeadNode(int key, int value) {
		NODE* node = new NODE();
		node->key = key;
		node->value = value;
		node->preNode = nullptr;
		node->nextNode = nullptr;
		m_headNode = node;
		m_tailNode = node;
		m_cacheMap.insert(pair<int, NODE*>(key, node));
	}

	void deleteHead() {
		m_cacheMap.erase(m_headNode->key);
		if (m_headNode->nextNode == nullptr) {
			delete m_headNode;
			m_headNode = nullptr;
			m_tailNode = nullptr;
		}
		else {
			m_headNode = m_headNode->nextNode;
			delete m_headNode->preNode;
			m_headNode->preNode = nullptr;
		}
	}

	//链表插值
	void addTail(int key, int value) {
		NODE* node = new NODE();
		node->key = key;
		node->value = value;
		m_tailNode->nextNode = node;
		node->preNode = m_tailNode;
		node->nextNode = nullptr;
		m_tailNode = node;
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int main()
{
	LRUCache lruCache(10);lruCache.put(10, 13);lruCache.put(3, 17);lruCache.put(6, 11);lruCache.put(10, 5);lruCache.put(9, 10);
	lruCache.get(13);lruCache.put(2, 19);lruCache.get(2);
	lruCache.get(3);
	lruCache.put(5, 25); 
	lruCache.get(8); 
	lruCache.put(9, 22); 
	lruCache.put(5, 5); 
	lruCache.put(1, 30); 
	lruCache.get(11); 
	lruCache.put(9, 12);
	lruCache.get(7); lruCache.get(5); lruCache.get(8); lruCache.get(9); lruCache.put(4, 30); lruCache.put(9, 3);
	lruCache.get(9); lruCache.get(10); lruCache.get(10); lruCache.put(6, 14); lruCache.put(3, 1); lruCache.get(3); lruCache.put(10, 11);

	lruCache.get(8); lruCache.put(2, 14); 
	lruCache.get(1); lruCache.get(5); lruCache.get(4); lruCache.put(11, 4); lruCache.put(12, 24);
	lruCache.put(5, 18); lruCache.get(13); lruCache.put(7, 23); lruCache.get(8); lruCache.get(12); lruCache.put(3, 27); lruCache.put(2, 12);
	lruCache.get(5); lruCache.put(2, 9); lruCache.put(13, 4); lruCache.put(8, 18); lruCache.put(1, 7); lruCache.get(6); lruCache.put(9, 29);
	lruCache.put(8, 21); lruCache.get(5); lruCache.put(6, 30); lruCache.put(1, 12); lruCache.get(10); lruCache.put(4, 15); lruCache.put(7, 22);
	lruCache.put(11, 26); lruCache.put(8, 17); lruCache.put(9, 29); lruCache.get(5); lruCache.put(3, 4); lruCache.put(11, 30); lruCache.get(12);
	lruCache.put(4, 29); lruCache.get(3); lruCache.get(9); lruCache.get(6); lruCache.put(3, 4); lruCache.get(1); lruCache.get(10); lruCache.put(3, 29);
	lruCache.put(10, 28);

	return 1;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
