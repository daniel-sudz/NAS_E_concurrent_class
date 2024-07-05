class FizzBuzz {
    private int n;
    private int i=1;

    public FizzBuzz(int n) {
        this.n = n;
    }

    private void gate(Runnable printer, Supplier<Boolean> condition) throws InterruptedException {
        synchronized (this) {
            while(!condition.get() && i<=n) {
                wait();
            }
            if(i > n) return;
        }
        printer.run();
        synchronized (this) {
            i++;
            notifyAll();
        }
        gate(printer, condition);
    }

    // printFizz.run() outputs "fizz".
    public void fizz(Runnable printFizz) throws InterruptedException {
       gate(printFizz, () -> i%3 == 0 && i%5 != 0); 
    }

    // printBuzz.run() outputs "buzz".
    public void buzz(Runnable printBuzz) throws InterruptedException {
       gate(printBuzz, () -> i%3 != 0 && i%5 == 0); 
    }

    // printFizzBuzz.run() outputs "fizzbuzz".
    public void fizzbuzz(Runnable printFizzBuzz) throws InterruptedException {
       gate(printFizzBuzz, () -> i%3 == 0 && i%5 == 0); 
    }

    // printNumber.accept(x) outputs "x", where x is an integer.
    public void number(IntConsumer printNumber) throws InterruptedException {
       gate(() -> {printNumber.accept(i);}, () -> i%3 != 0 && i%5 != 0); 
    }
