class FooBar {
private:
    int n;
    mutex m;
    condition_variable cv;
    bool curFoo = true; 

public:
    FooBar(int n) {
        this->n = n;
    }

    void printorder(bool foo, function<void()>& func) {
        {
            unique_lock lk(m);
            cv.wait(lk, [this, foo](){return curFoo == foo; });
        }
        func();
        {
            unique_lock lk(m);
            curFoo = !curFoo;
        }
        cv.notify_one();
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            printorder(true, printFoo);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            printorder(false, printBar);
        }
    }
};
