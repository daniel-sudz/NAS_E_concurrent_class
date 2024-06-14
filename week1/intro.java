class Foo {
    int order = 1; 
    public Foo() {
        
    }

    public void printn(Runnable printFunc, int n) throws InterruptedException {
        synchronized (this) {
            while(order != n) {
                wait();
            }
        }
        printFunc.run();
        synchronized (this) {
            order++;
            notifyAll();
        }
    }

    public void first(Runnable printFirst) throws InterruptedException {
        printn(printFirst, 1);
    }

    public void second(Runnable printSecond) throws InterruptedException {
        printn(printSecond, 2);
    }

    public void third(Runnable printThird) throws InterruptedException {
        printn(printThird, 3);
    }
