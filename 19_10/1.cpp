#include <iostream>

struct Stud {
  const char * fst;
  const char * snd;
  int year;
  int dep;
};

const Stud ** resize(const Stud ** old, size_t & n, double coef = 1.75) {
  if (coef < 1) {
    throw std::invalid_argument("Invalid value of coef");
  }

  if (std::numeric_limits<size_t>::max() / coef < n) {
    throw std::logic_error("Overflow");
  }

  size_t newSIze = static_cast<size_t>(coef * n) + 1;
  const Stud ** res = new const Stud * [newSIze];

  for (size_t i = 0; i < n; ++i) {
    res[i] = old[i];
  }

  n = newSIze;
  delete [] old;

  return res;
}

const Stud ** stud_dep(const Stud * const * studs, size_t k, int dep, size_t & found) {
  size_t cur = 1;
  const Stud ** ans = new const Stud * [cur];

  for (size_t i = 0; i < k; ++i) {
    if (studs[i]->dep == dep) {
      ans[found] = studs[i];
      found++;
    }

    if (found == cur) {
      try {
        ans = resize(ans, cur);
      }
      catch (const std::bad_alloc & e) {
        delete [] ans;
        std::cerr << e.what() << '\n';
      }
      catch (const std::exception & e) {
        std::cerr << e.what() << '\n';
      }
    }
  }
}

size_t count_year(const Stud * const * studs, size_t k, int y) {
  size_t cnt = 0;
  for (size_t i = 0; i < k; ++i) {
    if (studs[i]->year == y) {
      cnt++;
    }
  }
  return cnt;
}

struct Subj {
  const char * name;
  size_t people, classes;
  const Stud * const * studs;
  const size_t * visited;
};

size_t max_visits (const Subj & sub, int y) {
  return count_year(sub.studs, sub.people, y) * sub.classes;
}

size_t visits(const Subj & sub, int y) {
  size_t res = 0;

}

const Stud ** dobsovs

int main() {
  // std::cout << count_year(&studs, 1, 2018) << std::endl;

  return 0;
}
