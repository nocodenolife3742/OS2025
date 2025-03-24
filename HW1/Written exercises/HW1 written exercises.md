# HW1 written exercises

## Q1.14

> What is the purpose of interrupts? How does an interrupt differ from a trap? Can traps be generated intentionally by a user program? If so, for what purpose?

Interrupt 的目的是讓 CPU 能夠暫停執行目前的程式，去處理其他事件(像是I/O)，然後再回到原來的程式繼續執行。

trap 跟 interrupt 主要不同的地方在於 interrupt 從硬體產生，而 trap 從軟體產生(像是 division by zero 或是 invalid memory access 及 syscall)

trap 可以被 user program 刻意生成，通常用於通知 CPU ，告知程式發生錯誤，讓 CPU 介入處理。

## Q2.15
> What are the two models of interprocess communication? What are the strengths and weakness of the two approaches?

兩種 interprocess communication (IPC) 的模型是 shared memory 和 message passing。

shared memory 的優點是速度快，因為資料直接在記憶體中傳遞。缺點是需要處理同步問題，像是要避免兩個 process 同時寫入。

message passing 的優點是簡單且安全，不需要處理同步問題。缺點是它相較於 shared memory 需要更多的時間讀寫。

## Q2.19
> What is the main advantage of the microkernel approach to system design? How do user programs and system services interact in a microkernel architecture? What are the disadvantages of using the microkernel approach?

microkernel 的主要優點是可靠性高，因為大部分的系統服務運行在 user mode，kernel 的功能簡化，減少了錯誤影響整個系統的可能性。

在 microkernel 架構中，user program 和 system service 通過 IPC (interprocess communication) 進行互動。

缺點是效能較低，因為頻繁的資料交換會導致額外的開銷。

## Q3.14
> Give an example of a situation in which ordinary pipes are more suitable than named pipes and an example of a situation in which named pipes are more suitable than ordinary pipes.

ordinary pipes 比較適合 parent process 和 child process 之間的溝通，像是 fork() 出來的兩個 process 之間交換資料。

named pipes 比較適合沒有親緣關係的 process 之間的溝通，例如兩個獨立的程式需要交換資料。

## Q3.17
> What are the benefits and the disadvantages of each of the following? Consider both the system level and the programmer level a. Synchronous and asynchronous communication b. Automatic and explicit buffering c. Send by copy and send by reference d. Fixed-sized and variable-sized messages

a. Synchronous and asynchronous communication 
   - Synchronous:  
     優點是簡單且容易理解，因為發送方會等待接收方完成。缺點是可能導致 blocking，降低效能。  
   - Asynchronous:  
     優點是效能較高，因為發送方不需要等待。缺點是實現較為複雜，可能需要額外的機制避免資料產生衝突。

b. Automatic and explicit buffering
   - Automatic buffering:
     優點是實作層面上簡單。缺點是靈活性較低，可能導致不必要的資源浪費。  
   - Explicit buffering:  
     優點是靈活性高，程式設計師可以精確控制 buffer 的大小。缺點是實作較為複雜，容易出錯。

c. Send by copy and send by reference
   - Send by copy:  
     優點是安全，因為接收方無法修改原始資料。缺點是效能較低，因為需要複製資料。  
   - Send by reference:  
     優點是效能高，因為不需要複製資料。缺點是可能導致安全問題，因為接收方可以修改原始資料。

d. Fixed-sized and variable-sized messages
   - Fixed-sized:
     優點是實現簡單，因為傳遞的資料大小固定。缺點是可能導致資源浪費，因為未使用的空間會被浪費。  
   - Variable-sized:
     優點是資源利用率高，因為傳遞的資料大小可以根據需求調整。缺點是實現較為複雜，可能需要記憶體管理(像是可能需要用到 malloc() 或是其他向記憶體索取空間的函數)。
