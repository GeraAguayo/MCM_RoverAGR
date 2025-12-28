#ifndef Motors_H
#define Motors_H

class Motors{
  public:
    int current_map;
    Motors();
    void start();
    void forward(int MAP);
    void reverse(int MAP);
    void stop();
    void test_all_motors();
};

#endif