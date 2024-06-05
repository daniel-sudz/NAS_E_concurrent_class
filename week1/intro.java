class Foo {
    int order = 1; 
    public Foo() {
        
    }

    public void first(Runnable printFirst) throws InterruptedException {
        
        // printFirst.run() outputs "first". Do not change or remove this line.
        printFirst.run();
        order++;
    }

    public void second(Runnable printSecond) throws InterruptedException {
        
        // printSecond.run() outputs "second". Do not change or remove this line.
        synchronized (this) {
            while(order != 2) {
                notify();
                wait();
            }
            printSecond.run();
            order++;
            notify();
        }
    }

    public void third(Runnable printThird) throws InterruptedException {
        
        // printThird.run() outputs "third". Do not change or remove this line.
        synchronized (this) {
            while(order != 3) {
                notify();
                wait();
            }
            printThird.run();
        }
    }
