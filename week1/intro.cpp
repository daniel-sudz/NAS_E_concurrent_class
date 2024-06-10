class Foo {
public:
    mutex m;
    condition_variable cv;
    int turn = 1;
    
    Foo() {
    }

    void first(function<void()> printFirst) {
        printFirst();
        turn++;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock lk(m);
        cv.wait(lk, [this](){return turn == 2;});
        printSecond();
        turn++;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock lk(m);
        cv.wait(lk, [this](){return turn == 3;});
        printThird();
    }
}
