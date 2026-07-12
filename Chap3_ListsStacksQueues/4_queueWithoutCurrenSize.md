# 第4课分析题

> 详见 [Ch.3 L4 笔记](../../note/ch03-lists-stacks-queues.md#l4-队列adt--weiss-37-pp112115)

## 队列的数组实现中，如果用方案 B（不维护 currentSize，仅用 front/back 关系），为什么队列最多只能放 capacity - 1 个元素？请解释"满"和"空"两种状态在方案 B 下如何被混淆。

不维护 currentSize时，空/满状态用front和back的相对位置判断，但若放满arr.size()，$front - back \equiv 1(\mod arr.size)$同时表示空和满的状态。具体来说：空状态时，队列被清空，即back被front超过一位，此时front在back后一位；满状态时，队列被填满，back追上front且不能重叠，此时front也在back后一位。这种现象在不减少size的环形队列中是必然存在的，因为front和back的相对位置有n种，但size有n+1，从而根据鸽巢原理，必然有无法通过front和back的相对位置分辨的size。