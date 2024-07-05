class FooBar {
    private int n;
    boolean curFoo = true;

    public FooBar(int n) {
        this.n = n;
    }

    public void printorder(boolean isFoo, Runnable func) throws InterruptedException {
        synchronized (this) {
            while(isFoo != curFoo) {
                wait();
            }
        }
        func.run();
        synchronized (this) {
            curFoo = !curFoo;
            notify();
        }
    }

    public void foo(Runnable printFoo) throws InterruptedException {
        for (int i = 0; i < n; i++) {
           printorder(true, printFoo); 
        }
    }

    public void bar(Runnable printBar) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            printorder(false, printBar);    
        }
    }
