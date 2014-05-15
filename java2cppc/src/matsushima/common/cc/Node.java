package matsushima.common.cc;

import java.util.AbstractSequentialList;
import java.util.Iterator;
import java.util.ListIterator;

/**
 * ノード。
 * 
 * @author  0.0.1.001 2010/05/20 matsushima
 * @version 0.0.1.001 2010/05/20 matsushima
 * @since   0.0.1.001 2010/05/20 matsushima
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
public class Node<E extends Node<E>> extends AbstractSequentialList<E> {

    /** 親ノード */
    public E parent;
    /** 最初の子ノード */
    public E child;
    /** 最後の子ノード */
    public E lastChild;
    /** 子ノードの数 */
    public int childCount;
    /** 次のノード */
    public E next;
    /** 前のノード */
    public E prev;

    /**
     * ノードを作成する。
     */
    public Node() {
    }

    /**
     * ノードを作成し、親に追加する。
     */
    public Node(final E parent) {
        if (null != parent) {
            parent.add(getThis());
        }
    }

    /**
     * 自ノードを E 型で返す。
     * 
     * @return
     */
    @SuppressWarnings("unchecked")
    private E getThis() {
        return (E)this;
    }

    /**
     * 親ノードを取得する。
     * 
     * @return 親ノード
     */
    public E getParent() {
        return parent;
    }

    /**
     * 最初の子ノードを取得する。
     * 
     * @return 最初の子ノード
     */
    public E getChild() {
        return child;
    }

    /**
     * 最後の子ノードを取得する。
     * 
     * @return 最後の子ノード
     */
    public E getLastChild() {
        return lastChild;
    }

    /**
     * 次のノードを取得する。
     * 
     * @return 次のノード
     */
    public E getNext() {
        return next;
    }

    /**
     * 前のノードを取得する。
     * 
     * @return 前のノード
     */
    public E getPrev() {
        return prev;
    }

    /**
     * 次の巡回ノードを取得する。
     * 
     * @return 次の巡回ノード
     */
    public E getTraceNext() {
        if (null != getChild()) {
            return getChild();
        } else if (null != getNext()) {
            return getNext();
        }
        return getParent().getNext();
    }

    /**
     * このコレクション中の要素の数を返します。
     * このコレクションに Integer.MAX_VALUE より多くの要素がある場合は、Integer.MAX_VALUE を返します。
     * 
     * @return コレクションの要素数
     */
    @Override
    public int size() {
        return childCount;
    }

    /**
     * コレクションの要素の反復子を返します。
     * 
     * @return このコレクションの要素の Iterator
     */
    @Override
    public Iterator<E> iterator() {
        return new ListItr();
    }

    /**
     * このリスト内の要素を適切な順序で繰り返し処理するリスト反復子を返します。
     * 
     * @param nodeIndex リスト反復子から (next メソッド呼び出しによって) 返される最初の要素のインデックス
     * @return リスト内の要素を適切な順序で繰り返し処理するリスト反復子
     */
    @Override
    public ListIterator<E> listIterator(int index) {
        return new ListItr(index);
    }

    /**
     * コレクションの要素の反復子を返します。
     * 
     * @return このコレクションの要素の Iterator
     */
    public Iterator<E> traceIterator() {
        return new TraceItr();
    }

    /**
     * 指定された要素がこのコレクションに格納されていることを保証します (任意のオペレーション)。
     * 
     * @param newChild
     * @return この呼び出しの結果、このコレクションが変更された場合は true
     */
    @Override
    public boolean add(final E newChild) {
        newChild.parent = getThis();
        return addNotSetParent(newChild);
    }

    /**
     * 指定された要素がこのコレクションに格納されていることを保証します (任意のオペレーション)。
     * 子ノードを追加するが、親ノードを設定しない。
     * 
     * @param newChild
     * @return この呼び出しの結果、このコレクションが変更された場合は true
     */
    public boolean addNotSetParent(final E newChild) {
        ++ childCount;
        if (null == child) {
            child = lastChild = newChild;
        } else {
            lastChild.next = newChild;
            newChild.prev = lastChild;
            lastChild = newChild;
        }
        return true;
    }

    /**
     * 子ノードを追加する。
     * 
     * @param oldChild
     * @param newChild
     */
    public void add(final E oldChild, final E newChild) {
        ++ childCount;
        newChild.parent = getThis();
        newChild.prev = oldChild;
        newChild.next = oldChild.next;
        if (null != newChild.prev) {
            newChild.prev.next = newChild;
        } else {
            child = newChild;
        }
        if (null != newChild.next) {
            newChild.next.prev = newChild;
        } else {
            lastChild = newChild;
        }
    }

    /**
     * このコレクションからすべての要素を削除します (任意のオペレーション)。
     * このメソッドが戻ると、コレクションは空になります。
     */
    @Override
    public void clear() {
        child = lastChild = null;
        childCount = 0;
    }

    /**
     * 子ノードを置き換える。
     * 
     * @param oldChild
     * @param newChild
     */
    public void set(final E oldChild, final E newChild) {
        newChild.parent = getThis();
        newChild.prev = oldChild.prev;
        newChild.next = oldChild.next;
        if (null != newChild.prev) {
            newChild.prev.next = newChild;
        } else {
            child = newChild;
        }
        if (null != newChild.next) {
            newChild.next.prev = newChild;
        } else {
            lastChild = newChild;
        }
    }

    /**
     * オブジェクトのコレクションで「全体順序付け」を行う比較関数です。
     *
     * @param <E>
     * @param <T>
     */
    public static interface Comparator<E, T> {

        /**
         * 順序付けのために 2 つの引数を比較します。
         * 
         * @param o1 比較対象の最初のオブジェクト
         * @param o2 比較対象の 2 番目のオブジェクト
         * @return 最初の引数が 2 番目の引数より小さい場合は負の整数、
         *          両方が等しい場合は 0、
         *          最初の引数が 2 番目の引数より大きい場合は正の整数
         */
        int compare(final E o, final T key);
    }

    /**
     * ノードを検索する。
     * 
     * @param <T> 比較対象の 2 番目のオブジェクトの型
     * @param o2 比較対象の 2 番目のオブジェクト
     * @param c オブジェクトのコレクションで「全体順序付け」を行う比較関数
     * @return
     */
    public <T> E find(Iterator<E> i, T key, Comparator<E, ? super T> c) {
        while (i.hasNext()) {
            E node = i.next();
            if (0 == c.compare(node, key)) {
                return node;
            }
        }
        return null;
    }

    /**
     * 巡回ノードでノードを検索する。
     * 
     * @param <T>
     * @param key
     * @param c
     * @return
     */
    public <T> E findTrace(T key, Comparator<E, ? super T> c) {
        for (E node = getThis(); null != node; node = node.getTraceNext()) {
            if (0 == c.compare(node, key)) {
                return node;
            }
        }
        return null;
    }

    /**
     * イテレータ。
     */
    private class ListItr implements ListIterator<E> {

        /**
         * イテレータが指し示すノード。
         */
        protected E node;

        /**
         * イテレータが指し示すノードのインデックス。
         */
        protected int nodeIndex;

        /**
         * イテレータを構築する。
         */
        protected ListItr() {
            node = getChild();
        }

        /**
         * イテレータを構築する。
         * 
         * @param nodeIndex
         */
        protected ListItr(int index) {
            if ((index < 0) || (index > size())) {
                throw new IndexOutOfBoundsException("index = " + index + ", size = " + size());
            }
            if (index < size() / 2) {
                node = getChild();
                for (int i = 0; i < index; ++ i) {
                    next();
                }
            } else {
                node = getLastChild();
                for (int i = size() - 1; i > index; -- i) {
                    previous();
                }
            }
            nodeIndex = index;
        }

        /**
         * リストを順方向にトラバースしたときに、リスト反復子がさらに要素を持っている場合に true を返します。
         * 
         * @return リストを順方向にたどったときに、リスト反復子がさらに要素を持っている場合は true
         */
        @Override
        public boolean hasNext() {
            return (null != node);
        }

        /**
         * リスト内の次の要素を返します。
         * 
         * @return リストの次の要素
         */
        @Override
        public E next() {
            E result = node;
            node = node.getNext();
            ++ nodeIndex;
            return result;
        }

        /**
         * リストを逆方向にトラバースしたときに、リスト反復子がさらに要素を持っている場合に true を返します。
         * 
         * @return リストを逆方向にたどったときに、リスト反復子がさらに要素を持っている場合は true
         */
        @Override
        public boolean hasPrevious() {
            return (null != node);
        }

        /**
         * リストの前の要素を返します。
         * 
         * @return リストの前の要素
         */
        @Override
        public E previous() {
            E result = node;
            node = node.getPrev();
            -- nodeIndex;
            return result;
        }

        /**
         * 次に next を呼び出したときに返されることになる要素のインデックスを返します。
         * リスト反復子がリストの末尾にある場合はリストのサイズを返します。
         * 
         * @return 次に next を呼び出したときに返されることになる要素のインデックス。
         * リスト反復子がリストの最後にある場合はリストのサイズ
         */
        @Override
        public int nextIndex() {
            return nodeIndex + 1;
        }

        /**
         * 次に previous を呼び出したときに返されることになる要素のインデックスを返します。
         * リスト反復子がリストの先頭にある場合は -1 を返します。
         * 
         * @return 次に previous を呼び出したときに返されることになる要素のインデックス。
         * リスト反復子がリストの先頭にある場合は -1
         */
        @Override
        public int previousIndex() {
            return nodeIndex - 1;
        }

        /**
         * UnsupportedOperationException
         */
        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }

        /**
         * next または previous から最後に返された要素を指定された要素で置き換えます (任意のオペレーション)。
         * 
         * @param e next または previous によって返される最後の要素と置換される要素
         */
        @Override
        public void set(E e) {
            node.getParent().set(node, e);
        }

        /**
         * 指定された要素をリストに挿入します (任意のオペレーション)。
         * 
         * @param e 挿入される要素
         */
        @Override
        public void add(E e) {
            node.getParent().add(node, e);
        }
    }

    /**
     * 巡回イテレータ。
     */
    private class TraceItr extends ListItr {

        /**
         * リスト内の次の要素を返します。
         * 
         * @return リストの次の要素
         */
        @Override
        public E next() {
            E result = node;
            node = node.getTraceNext();
            return result;
        }
    }
}
