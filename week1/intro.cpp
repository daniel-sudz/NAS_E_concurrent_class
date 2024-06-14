class Foo {
public:
    mutex m;
    condition_variable cv;
    int turn = 1;
    
    Foo() {
    }

    void printn(function<void()>& printFunc, int n) {
        {
            unique_lock lk(m);
            cv.wait(lk, [this,n](){return turn == n;});
        }
        printFunc();
        {
            unique_lock lk(m);
            turn++;
        }
        cv.notify_all();
    }

    void first(function<void()> printFirst) {
        printn(printFirst,1);
    }

    void second(function<void()> printSecond) {
        printn(printSecond,2);
    }

    void third(function<void()> printThird) {
        printn(printThird,3);
    }
}
