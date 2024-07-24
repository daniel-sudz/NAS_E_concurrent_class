class DiningPhilosophers {
public:
    typedef function<void()> fv;
    int N = 5;
    vector<mutex> locks = vector<mutex>(N);
    vector<condition_variable> cvs = vector<condition_variable>(N);
    vector<bool> taken = vector<bool>(N);

    DiningPhilosophers() {}

    void wait_and_mark(int idx, fv take) {
        {
            unique_lock lk(locks[idx]);
            cvs[idx].wait(lk, [this,idx](){return taken[idx]==false;});
            taken[idx] = true;
        }
        take();
    }

    void unmark_and_notify(int idx, fv put) {
        put();
        {
            unique_lock lk(locks[idx]);
            taken[idx] = false;
        }
        cvs[idx].notify_all();
    }

    void odd_philosopher(int n, fv pick_left, fv pick_right, fv eat, fv put_left, fv put_right) {
        int right = (n-1+N)%N;
        int left = n;
        wait_and_mark(right, pick_right);
        wait_and_mark(left, pick_left);
        eat();
        unmark_and_notify(left, put_left);
        unmark_and_notify(right, put_right);
    }
    void even_philosopher(int n, fv pick_left, fv pick_right, fv eat, fv put_left, fv put_right) {
        int right = (n-1+N)%N;
        int left = n;
        wait_and_mark(left, pick_left);
        wait_and_mark(right, pick_right);
        eat();
        unmark_and_notify(right, put_right);
        unmark_and_notify(left, put_left);
    }

    void wantsToEat(int n,
                    fv pick_left,
                    fv pick_right,
                    fv eat,
                    fv put_left,
                    fv put_right) {
        if(n%2 == 0) {
            even_philosopher(n,pick_left,pick_right,eat,put_left,put_right);
        }
        else {
            odd_philosopher(n,pick_left,pick_right,eat,put_left,put_right);
        }
    }
}
