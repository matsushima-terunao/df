#pragma once

#include <list>

/**
 * �m�[�h�B
 * 
 * @author  0.0.1.001 2010/05/20 matsushima
 * @author  0.0.1.001 2010/04/29 matsushima java2cppc
 * @author  0.0.2.002 2012/08/15 matsushima
 * 
 * $Id: Node.java,v 1.6 2010/05/23 18:36:44 matsushima Exp $
 * $Log: Node.java,v $
 * Revision 1.6  2010/05/23 18:36:44  matsushima
 * ����
 *
 * Revision 1.4  2010/05/22 17:05:04  matsushima
 * Node �� AbstractSequentialList �h��
 *
 * Revision 1.1  2010/05/21 16:56:49  matsushima
 * �m�[�h�̋��ʉ�
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
	 * �m�[�h���쐬���A�e�ɒǉ�����B
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
	 * �m�[�h��ǉ�����B
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
	 * �m�[�h��ǉ�����B
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
	 * �m�[�h���폜����B
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
	 * �c���[�����ǂ������̃m�[�h���擾����B
	 */
public:
	E* getTraceNext()
	{
		if (children.size() >= 1) // �q���������
		{
			return &children.front(); // �q���̐擪
		}
		else if (NULL != next) // �q�������Ȃ����
		{
			return next; // ���̌Z��
		}
		for (E* p = parent; NULL != p; p = p->parent) // �q���A���̌Z�킪���Ȃ���΁A�߂���
		{
			if (NULL != p->next)
			{
				return p->next; // ���̌Z��
			}
		}
		return NULL; // �����Ȃ�
	}

	/**
	 * �z���̎��̃m�[�h���擾����B
	 */
public:
	E* getTraceNext(Node<E>* node)
	{
		E* result = node->getTraceNext();
		if (result == node)
		{
			return NULL; // �����܂Ŗ߂����̂ŏI��
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
