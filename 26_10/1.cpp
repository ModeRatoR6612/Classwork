#include <algorithm>
#include <iostream>
#include <algorithm>

struct Eve {
  const char * event;
  int lvl;
  int src;
};

struct Journal {
  size_t k;
  const Eve * const * es;
  const int * ids;
  const int * par;
};

int maxlvl(const Eve * const * es, size_t k, int src) {
  int max_lvl = 0;
  size_t i = 0;
  while (es[i]->src != src && i < k) {
    i++;
  }
  if (i == k) throw std::logic_error("No src");
  max_lvl = es[i]->lvl;

  for (; i < k; ++i) {
    if (es[i]->src == src) {
      max_lvl = std::max(max_lvl, es[i]->lvl);
    }
  }
  return max_lvl;
}

const Eve ** expand(const Eve ** es, size_t old_size, size_t new_size) {
  if (new_size <= old_size) {
    throw std::logic_error("Incorrect new size");
  }

  const Eve ** res = new const Eve * [new_size];
  for (size_t i = 0; i < old_size; ++i) {
    res[i] = es[i];
  }
  return res;
}

const Eve ** highestExpand(size_t & res, const Eve * const * es, size_t k) {
  int max_lvl = es[0]->lvl;

  for (size_t i = 1; i < k; ++i) {
    max_lvl = std::max(max_lvl, es[i]->lvl);
  }

  size_t capacity = 2;
  const Eve ** res_es = new const Eve * [capacity];
  size_t size = 0;

  for (size_t i = 0; i < k; ++i) {
    if (es[i]->lvl == max_lvl) {
      if (size < capacity) {
        res_es[size++] = es[i];
      }
      else {
        try {
          const Eve ** res_new = expand(res_es, capacity, capacity*2);
          delete [] res_es;
          capacity *= 2;
        } catch (...) {
          delete [] res_es;
          throw;
        }
      }
    }
  }

  res = capacity;
  return res_es;
}

const Eve ** highest(size_t & res, const Eve * const * es, size_t k) {
  int max_lvl = es[0]->lvl;
  size_t count_max = 0;

  for (size_t i = 1; i < k; ++i) {
    if (es[i]->lvl > max_lvl) {
      max_lvl = es[i]->lvl;
      count_max = 1;
    }
    else if (es[i]->lvl == max_lvl) {
      count_max++;
    }
  }

  const Eve ** res_es = new const Eve * [count_max];
  size_t index = 0;
  for (size_t i = 0; i < k; ++i) {
    if (es[i]->lvl == max_lvl) {
      res_es[index++] = es[i];
    }
  }
  res = index;
  return res_es;
}

const Eve ** childs(size_t & res, int id, const Journal & jl) {
  size_t count = 0;
  for (size_t i = 0; i < jl.k; ++i) {
    if (jl.par[i] == id && jl.ids[i] != id) {
      count++;
    }
  }

  const Eve ** res_es = new const Eve * [count];
  size_t size = 0;

  for (size_t i = 0; i < jl.k; ++i) {
    if (jl.par[i] == id && jl.ids[i] != id) {
      res_es[size++] = jl.es[i];
    }
  }

  res = count;
  return res_es;
}



int main() {

  return 0;
}
