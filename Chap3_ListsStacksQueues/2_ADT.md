# 第二节思考题

> 详见 [Ch.3 L2 笔记](../../note/ch03-lists-stacks-queues.md#l2-vector-与-list-的底层实现-3435)

## Weiss 的 Vector::reserve 在 newCapacity < theSize 时直接 return，不允许缩小容量。如果我们要支持 shrink_to_fit（将 capacity 缩小到恰好等于 size），这个操作的时间复杂度是多少？它和 push_back的扩容合在一起看，是否存在某种操作序列会导致每次操作都是 O(N)？（提示：思考反复 shrink + grow 的场景）

```cpp
    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;

        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;
    }
```

若要实现缩小vector分配的内存长度为实际大小，我会选择新建theSize大小的一串内存，然后将旧数组移到新数组，然后销毁旧数组的内存空间。该操作的时间复杂度是O(N)。

但这样做会使得分配两倍内存毫无意义。比方说我们从theSize为N，theCapacity为N开始，执行push_back，仅对该步而非平均而言，时间复杂度为O(N)，此时在调用push_back会导致触发if分支进入shrink_to_fit，删减空闲分配内存，时间复杂度O(N)，在继续进行新一轮扩容，且时间复杂度为O(N)。这样每次push_back都是O(N)，从而使得这样的步骤为O(N)复杂度。

