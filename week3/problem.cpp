class FizzBuzz {
private:
    int n;
    int i = 1;
    mutex m; 
    condition_variable cv; 

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    void gate(function<void()> func, function<bool()> condition) {
        {
            unique_lock lk(m);
            cv.wait(lk, [this,condition](){return condition() || i>n;});
            if(i > n) return;
        }
        func();
        {
            unique_lock lk(m);
            i++;
        }
        cv.notify_all();
        gate(func, condition);
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        gate(printFizz, [this](){return i%3==0 && i%5 != 0;});
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        gate(printBuzz, [this](){return i%3!=0 && i%5 == 0;});
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        gate(printFizzBuzz, [this](){return i%3==0 && i%5 == 0;});
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        gate([this,printNumber](){printNumber(i);}, [this](){return i%3!=0 && i%5 != 0;});
    }
}
