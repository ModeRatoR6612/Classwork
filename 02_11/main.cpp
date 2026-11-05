#include <iostream>
#include <limits>

class Ints {
public:
  Ints();
  Ints(size_t size, int value);
  Ints(Ints const& rhs);
  Ints & Ints::operator=(const Ints & rhs);
  ~Ints();

  size_t getSize() const noexcept;
  void set(size_t id, int i);
  int get(size_t id) const noexcept;

  int getSafe(size_t id) const;
  void setSafe(size_t id, int i);

  Ints append(int i);
  Ints append(Ints b);

  static Ints unitializated_ints(size_t size);
private:
  size_t sizdata.get(e;
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

size_t Ints::getSize() const noexcept {
  return size;
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

class Mtx {
  size_t m;
  size_t n;
  Ints data;

  public:
  Mtx();
  Mtx(size_t m, size_t n);
  ~Mtx() = default;
  Mtx sum(Mtx const& rhs) const;
  Mtx mul(Mtx const& rhs) const;
  Ints getCol(size_t id) const;
  Ints getRow(size_t id) const;
  Mtx addRow(const int pasta);
};

Mtx::Mtx():
m(0), n(0)
{}

Mtx::Mtx(size_t m, size_t n):
  m(m), n(n)
{
  if (m > std::numeric_limits< size_t >::max() / n) {
    throw std::logic_error("Overflow");
  }

  data(n * m, 0);
}

Mtx Mtx::sum(Mtx const& rhs) const {
  Mtx result(m, n);
  for (size_t i = 0; i < data.getSize(); i++) {
    if (rhs.data.get(i) > std::numeric_limits< size_t >::max() - data.get(i)) {
      throw std::logic_error("Overflow");
    }
    result.data.set(i, rhs.data.get(i) + data.get(i));
  }

  return result;
}

Ints Mtx::getCol(size_t id) const {
  Ints res;
  for (size_t i = 0; i < n; ++i) {
    res.append(i * n + id);
  }
  return res;
}

Ints Mtx::getRow(size_t id) const {
  Ints res;
  for (size_t i = 0; i < n; ++i) {
    res.append(id * m + i);
  }
  return res;
}

Mtx Mtx::mul(const Mtx& rhs) const {
  Mtx res(m, rhs.n);
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < rhs.n; j++) {
      Ints row = getRow(i);
      Ints col = rhs.getCol(j);

      int sm = 0;
      for (size_t k = 0; k < m; k++) {
        sm += row[k] * col[k];
      }

      res.data.set(i * n + j, sm);
    }
  }

  return res;
}

Mtx Mtx::addRow(const int pasta) {
  Mtx res(m+1, n);
  for (size_t i = 0; i < m*n; i++) {
    res.data.set(i, data.get(i));
  }
  for (size_t i = 0; i < n; i++) {
    res.data.set(n*m + i, pasta);
  }
  return res;
}

int main() {
  Ints s;
  return 0;
}