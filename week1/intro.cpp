class Foo {
public:
    std::mutex two,three;
    Foo() {
        two.lock();
        three.lock();    
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        two.unlock();
    }

    void second(function<void()> printSecond) {
        lock_guard<mutex> guard(two);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        three.unlock();
    }

    void third(function<void()> printThird) {
        lock_guard<mutex> guard(three);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
}
