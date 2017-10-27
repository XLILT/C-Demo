#include <stdio.h>

template <class T>
class Deck {
private:
  T* arr; // array
  int n;  // size
  int rearcursor; // current pos of rear el
  int frontcursor; //...
public:
  Deck(int sz = 10);
  ~Deck();
  int size();

  T& getFront();
  T& getRear();

  void removeFront();
  void removeRear();

  void addFront(const T& elem);
  void addRear(const T& elem);

  bool empty();
};

template <class T> Deck<T>::Deck(int sz) {
  n = 0;
  T* arr = new T[sz];
  frontcursor = rearcursor = 0;
}

template <class T> Deck<T>::~Deck() {
  delete[] arr;
  arr = NULL;
}

int main()
{
  Deck<int> j(10);
}
