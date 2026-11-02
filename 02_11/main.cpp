#include <iostream>

class Ints {
public:
  Ints();
  Ints(size_t size, int value);
  Ints(Ints const& rhs);
  Ints & Ints::operator=(const Ints & rhs);
  ~Ints();

  void set(size_t id, int i);
  int get(size_t id);

  int getSafe(size_t id);
  void setSafe(size_t id, int i);

  Ints append(int i);
  Ints append(Ints b);

  static Ints unitializated_ints(size_t size);
private:
  size_t size;
  size_t capacity;
  int * data;
  int * resize(int * data);
};

Ints::Ints():
  size(0),
  data(nullptr)
{}

Ints::Ints(size_t size, int value):
  size(size), data(new int[size])
{
  for (size_t i = 0; i < size; i++) {
    data[i] = value;
  }
}

static Ints::Ints unitializated_ints(size_t size)
{
  Ints temp;
  temp.size = size;
  temp.data = new int[size];

  return temp;
}

Ints::Ints(Ints const& rhs):
  size(rhs.size), data(new int [size])
{
  for (size_t i = 0; i < size; i++) {
    data[i] = rhs.data[i];
  }
}

Ints & Ints::operator=(const Ints & rhs)
{
  if (this == &rhs) {
    return *this;
  }

  Ints temp(rhs);
  std::swap(size, temp.size);
  std::swap(data, temp.data);

  return *this;
}

Ints::~Ints() {
  delete [] data;
}

void Ints::set(size_t id, int i) {
  data[id] = i;
}

void Ints::setSafe(size_t id, int i) {
  if (id < size) {
    throw std::logic_error("Out of range");
  }

  set(id, i);
}

int Ints::get(size_t id) {
  return data[id];
}

int Ints::getSafe(size_t id) {
  if (id < size) {
    throw std::logic_error("Out of range");
  }
  return get(id);
}

Ints Ints::append(int i)
{
  Ints temp(*this);

  if (temp.capacity < temp.size + 1)
  {
    temp.data = resize(data);
  }

  temp.data[size] = i;
  ++temp.size;

  return temp;
}

int main() {
  Ints s;
  return 0;
}