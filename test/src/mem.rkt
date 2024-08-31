(export malloc free hb_coreDump HEAP_INIT)

#|=================HB implementations====================|#
(int (hb_setSize [int addr] [int size])
    (set int^(hb_toRealAddr addr) (+ size 8))
    0)

(int (hb_getSize [int addr])
    (- int^(hb_toRealAddr addr) 8))

(int (hb_setNext [int addr] [int nextAddr])
    (set int^(hb_toRealAddr (+ addr 4)) nextAddr))

(int (hb_getNext [int addr])
    int^(hb_toRealAddr (+ addr 4)))

(long (hb_toRealAddr [int addr])
    (+ addr (HEAP_HEAD)))

(int (hb_getEnd [int addr])
    (+ addr int^(hb_toRealAddr addr)))

(int (hb_coreDump [int addr1] [int addr2])  ;
    (int i) (set i addr1)
    (while (<= i addr2)
        (print i)
        (println (% long^(hb_toRealAddr i) 256))
        (set i (+ i 1))))

(int (hb_heapSize)
    (- (HEAP_END) (HEAP_HEAD)))

#|=====================malloc===========================|#

#| public function that allocates a region of space in heap |#
#| `size` - the size of usable data to be allocated |#
#| if enough space in heap, returns pointer to space in memory |#
#| if not enough space in heap, returns 0 |#
(long (malloc [int size])
    (long ret)
    (int node)      (int prev)
    (set ret (mlc_findRegion @node @prev size))
    
    (cond
        [(= ret -1)
            (set ret 0)]
        [1 (set ret (+ 8 (hb_toRealAddr (mlc_helper node prev size))))])
    ret)

#| the underlaying logic for process of block allocation in malloc |#
#| `size` - the size of usable data to be allocated |#
#| `node` - heap index to suitable area in memory |#
#| `prev` - heap index to area that points to node |#
#| allocates block of usable memory as `size` and returns heap index |#
(int (mlc_helper [int node] [int prev] [int size])
    ; node := the free block that has enough space to allocate size
    ; prev := the last free block that points to node
    
    ; (print node)    (println prev)

    (int oldSize)   (set oldSize (hb_getSize node))
    (int oldNext)   (set oldNext (hb_getNext node))

    ; change node to be the allocated block
    (hb_setSize node size)
    
    ; no need to change next

    ; see if there is enough space for a block afterwards
    ; spaceLeft = oldSize - size - 8 (account for header)
    (int spaceLeft) (set spaceLeft (- (- oldSize size) 8))
    #|
                   { |===|      <- node
                   { |   | } size
        oldSize    { |===|      <- newBlock
                   { |   | } spaceLeft
    |#
    
    (cond
        [(< 0 spaceLeft)    ; if extra space can fit more, we init this new free block
            (int newBlock)  (set newBlock (hb_getEnd node)) ; at the end of node
            (hb_setSize newBlock spaceLeft)
            (hb_setNext newBlock oldNext)
                            ; notice how the next free area is now spaceLeft (we want prev to point to this)
            (hb_setNext prev newBlock)
            ]
        [1                  ; if it cant fit anymore, then we set prev to point to whatever node was point to before
            ; we also allocate the entire block (so that the space doesnt get lost when the block is freed)
            (hb_setSize node oldSize)
            (hb_setNext prev oldNext)
            ])
    
    node)

#| searches linked list of free region in heap for suitable block that can fit size |#
#| `nodePtr` - address of an int that is set as heap index to suitable free region |#
#| `prevPtr` - address of an int that is set as heap index to free region pointing to node |#
#| if sucessful, returns 0 |#
#| if not enough room in heap, returns -1 |#
(int (mlc_findRegion [long nodePtr] [long prevPtr] [int size])
    
    (set int^nodePtr 0)
    (set int^prevPtr -1)
    (int ret)   (set ret 0)

    (while (and (= ret 0) (< (hb_getSize int^nodePtr) size))\
        (cond
            [(= int^nodePtr (hb_heapSize))
                (set ret -1)])
        (set int^prevPtr int^nodePtr)
        (set int^nodePtr (hb_getNext int^nodePtr)))
        
    ret)

#|=======================free==========================|#
(int (free [long addr])
    (int cur)   (set cur (- (- addr (HEAP_HEAD)) 8))  ; convert to heap index
    (int prev)  (int next)
    (fr_findNearByRegion @prev @next cur)

    ; we want the prev pointer to now point to here instead of next
    (hb_setNext prev cur)

    ; we want here to point to next
    (hb_setNext cur next)

    ; technically thats it, however we want to coalesce to prevent fragmentation
    0)

(int (fr_findNearByRegion [long prevPtr] [long nextPtr] [int pos])

    ; (print int^nextPtr) (print int^prevPtr) (print pos)
    
    (set int^nextPtr 0)
    (set int^prevPtr -1)
    
    (while (< int^nextPtr pos)
        (set int^prevPtr int^nextPtr)
        (set int^nextPtr (hb_getNext int^nextPtr)))
    0)

#|======================heap init======================|#
(int (HEAP_INIT)
    ; <- insert gp (heap pointer) initalization here
    (int hbDummy) (set hbDummy 0)
    (hb_setSize hbDummy 0)
    (int hbBlock) (set hbBlock (hb_getEnd hbDummy))
    (hb_setNext hbDummy hbBlock)
    (hb_setSize hbBlock (- (hb_heapSize) (* 2 8)))      ; assumes header is 8 bytes
    (hb_setNext hbBlock (hb_heapSize))
    0)

#|=======================debugging===================|#

(int (test)
    (hb_coreDump 0 32)
    (println (malloc 100))
    (long a) (set a (malloc 1))
    (println a)
    (println (malloc 1))
    (println (malloc 1))

    (free a)
    (hb_coreDump 0 32)
    (malloc 1)
    

    ; (println (- (hb_heapSize) hbBlock))
    (hb_coreDump 0 32)

    0)