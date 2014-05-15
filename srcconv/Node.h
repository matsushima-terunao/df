#pragma once

#include <list>

/**
 * ノード。
 * 
 * @author  0.0.1.001 2010/05/20 matsushima
 * @author  0.0.1.001 2010/04/29 matsushima java2cppc
 * @author  0.0.2.002 2012/08/15 matsushima
 * 
 * $Id: Node.java,v 1.6 2010/05/23 18:36:44 matsushima Exp $
 * $Log: Node.java,v $
 * Revision 1.6  2010/05/23 18:36:44  matsushima
 * 検索
 *
 * Revision 1.4  2010/05/22 17:05:04  matsushima
 * Node の AbstractSequentialList 派生
 *
 * Revision 1.1  2010/05/21 16:56:49  matsushima
 * ノードの共通化
 *
 */
template<class E> class Node
{
public:
	std::list<E> children;
	E* parent;
	E* next;
	E* prev;

public:
	Node()
	{
		this->parent = NULL;
		this->next = NULL;
		this->prev = NULL;
	}

	/**
	 * ノードを作成し、親に追加する。
	 */
public:
	Node(E* parent)
	{
		if (NULL != parent)
		{
			parent->add(this);
		}
	}

	/**
	 * ノードを追加する。
	 */
public:
	E* add(E node)
	{
		node.parent = (E*)this;
		children.push_back(node);
		if (children.size() >= 2)
		{
			std::list<E>::iterator curr = children.end();
			-- curr;
			std::list<E>::iterator prev = children.end();
			-- prev;
			-- prev;
			curr->prev = &*prev;
			prev->next = &*curr;
		}
		return &children.back();
	}

	/**
	 * ノードを追加する。
	 */
public:
	void add(std::list<E> children)
	{
		for (std::list<E>::iterator it = children.begin(); it != children.end(); ++ it)
		{
			add(*it);
		}
	}

	/**
	 * ノードを削除する。
	 */
public:
	void remove(E* node)
	{
		for (std::list<E>::iterator it = children.begin(); it != children.end(); ++ it)
		{
			if (&*it == node)
			{
				if (NULL != it->prev)
				{
					it->prev->next = it->next;
				}
				if (NULL != it->next)
				{
					it->next->prev = it->prev;
				}
				children.erase(it);
				return;
			}
		}
	}

	/**
	 * ツリーをたどった次のノードを取得する。
	 */
public:
	E* getTraceNext()
	{
		if (children.size() >= 1) // 子供がいれば
		{
			return &children.front(); // 子供の先頭
		}
		else if (NULL != next) // 子供がいなければ
		{
			return next; // 次の兄弟
		}
		for (E* p = parent; NULL != p; p = p->parent) // 子供、次の兄弟がいなければ、戻って
		{
			if (NULL != p->next)
			{
				return p->next; // 次の兄弟
			}
		}
		return NULL; // もうない
	}

	/**
	 * 配下の次のノードを取得する。
	 */
public:
	E* getTraceNext(Node<E>* node)
	{
		E* result = node->getTraceNext();
		if (result == node)
		{
			return NULL; // 自分まで戻ったので終了
		}
		return result;
	}

public:
	std::string spc(int indent)
	{
		std::string s;
		char buf[10];
		sprintf_s(buf, "%d", indent);
		s.append(buf);
		for (int j = 0; j < indent; ++ j)
		{
			s.append(" ");
		}
		return s;
	}
};
