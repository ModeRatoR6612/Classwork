#include <iostream>

constexpr size_t PLANAR_SIZE = 3;
int planarTypes[PLANAR_SIZE] = {1, 2, 3};

constexpr double PI = 3.14159265358979323846;

enum Color {RED, GREEN, BLUE};
Color makeColor(char c) {
  switch (c) {
    case 'R': return Color::RED;
    case 'G': return Color::GREEN;
    case 'B': return Color::BLUE;
    default: throw std::invalid_argument("invalid color");
  }
}

class Planar {
  public:
    virtual ~Planar() = default;

    virtual std::ostream& info(std::ostream& out) const = 0;
    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual int abs_sqr() const = 0;
};

class Colored {
public:
  virtual ~Colored() = default;

  virtual Color getColor() const = 0;
  virtual void setColor(Color color) = 0;
};

class Point: public Planar {
public:
  Point(int x, int y):
    x_(x), y_(y)
  {}
  virtual ~Point() override = default;

  virtual std::ostream& info(std::ostream& out) const override {
    return out << "Point";
  }
  virtual int x() const override { return x_; }
  virtual int y() const override { return y_; }
  virtual int abs_sqr() const override { return x_ * x_ + y_ * y_; }

private:
  int x_, y_;
};

Planar * clonePoint (std::istream & in) {
  int x = 0, y = 0;
  if (in >> x >> y) {
    return new Point(x, y);
  }
  return nullptr;
}

class Vector: public Planar {
public:
  Vector(Point x, Point y):
    a_(x), b_(y)
  {}
  virtual ~Vector() override = default;

  virtual std::ostream& info(std::ostream& out) const override {
    return out << "Vector";
  }
  virtual int x() const override { return b_.x() - a_.x(); }
  virtual int y() const override { return b_.y() - a_.y(); }
  virtual int abs_sqr() const override { return x() * x() + y() * y(); }
private:
  Point a_, b_;
};

Planar * cloneVector (std::istream & in) {
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
  if (in >> x1 >> y1 << x2) {
    return new Point(x, y);
  }
  return nullptr;
}

class ColoredPoint: public Planar, public Colored {
public:
  ColoredPoint(Point p, Color cl):
    p_(p), cl_(cl)
  {}
  virtual ~ColoredPoint() override = default;

  virtual std::ostream& info(std::ostream& out) const override {
    return out << "Colored Point";
  }
  virtual int x() const override {return p_.x();}
  virtual int y() const override {return p_.y();}
  virtual int abs_sqr() const override { return p_.abs_sqr(); }
  virtual Color getColor() const override {return cl_;}
  virtual void setColor(Color color) override {cl_ = color;}
private:
  Point p_;
  Color cl_;
};

class Brush: public Colored {
public:
  explicit Brush(Color color):
    cl_(color)
  {}

  ~Brush() override = default;

  virtual Color getColor() const override { return cl_; }
  virtual void setColor(Color color) override { cl_ = color; }
private:
  Color cl_;
};

// Planar * fabricPlanar(std::istream & in) {
//   int num = 0;
//   in >> num;
//   switch (num) {
//     case 1: return clonePoint(in);
//     case 2: return cloneVector(in);
//     case 3: return cloneColoredPoint(in);
//     case 4: return cloneBrush(in);
//     default: throw std::invalid_argument("invalid option");
//   }
// }

std::ostream& print_abs_sqr(std::ostream& out, Planar * pl) {
class Circle: public Planar {
public:
  Circle(Point center, int radius):
    c_(center), r_(radius)
  {}


  virtual ~Circle() override = default;

  virtual std::ostream& info(std::ostream& out) const override {
    return out << "Circle";
  }

  virtual int x() const override {return c_.x();}
  virtual int y() const override {return c_.y();}
  virtual int abs_sqr() const override { return r_ * r_; }
  double sqr() const { return PI * r_ * r_; }

  void move(const Point &p) {
    c_ = p;
  }
  void resize(const int r) {
    r_ = r;
  }

private:
  Point c_;
  int r_;
};

class ColoredCircle: public Planar, public Colored {
public:
  ColoredCircle(Color color, Circle circle):
    cl_(color), circle_(circle)
  {}
  virtual ~ColoredCircle() override = default;

  virtual std::ostream& info(std::ostream& out) const override {
    return out << "ColoredCircle";
  }

  virtual int x() const override {return circle_.x();}
  virtual int y() const override {return circle_.y();}
  virtual int abs_sqr() const override { return circle_.abs_sqr(); }
  double sqr() const { return circle_.sqr(); }

  virtual Color getColor() const override { return cl_; }
  virtual void setColor(Color color) override { cl_ = color; }

  void move(const Point &p) { circle_.move(p); }
  void resize(const int r) { circle_.resize(r); }

private:
  Color cl_;
  Circle circle_;
};

std::ostream& print_abs_sqr (std::ostream& out, Planar * pl) {
  return pl->info(out) << ' ' << pl->abs_sqr();
}

void del(Planar * pls[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    delete pls[i];
  }
}


namespace fabric {
  class AbstractFabricPlanar {
  public:
    virtual ~AbstractFabricPlanar() = default;

    virtual Planar * create(std::istream& in) = 0;
  };

  class FabricPoint : public AbstractFabricPlanar {
    public:
      virtual Planar * create(std::istream& in) override {
        int x = 0, y = 0;
        if (in >> x >> y) {
          return new Point(x, y);
        }
        throw std::invalid_argument("Invalid input");
      }
      ~FabricPoint() override = default;
  };

  class FabricVector : public AbstractFabricPlanar {
  public:
    virtual Planar * create(std::istream& in) override {
      int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
      if (in >> x1 >> y1 << x2) {
        return new Vector(Point(x1, y1), Point(x2, y2));
      }
      throw std::invalid_argument("Invalid input");
    }
  };

  class FabricColoredPoint : public AbstractFabricPlanar {
    public:
      virtual Planar * create(std::istream& in) override {
        int x = 0 , y = 0;
        char ch = ' ';
        if (in >> x >> y >> ch) {
          return new ColoredPoint(Point(x, y), makeColor(ch));
        }
        throw std::invalid_argument("Invalid input");
      }
  };

  void delFabricsPlanar(AbstractFabricPlanar ** fabricsPlanar, const size_t size) {
    for (size_t j = 0; j < size; ++j) {
      delete fabricsPlanar[j];
    }
    delete[] fabricsPlanar;
  }

  AbstractFabricPlanar ** makeFabircs() {
    AbstractFabricPlanar ** fabricsPlanar = new AbstractFabricPlanar*[PLANAR_SIZE];
    size_t i = 0;

    try {
      fabricsPlanar[i++] = new FabricPoint();
      fabricsPlanar[i++] = new FabricVector();
      fabricsPlanar[i++] = new FabricColoredPoint();
    } catch (...) {
      delFabricsPlanar(fabricsPlanar, i);
      throw std::logic_error("Bad alloc");
    }
    return fabricsPlanar;
  }
}

int main() {
  constexpr size_t cap = 10;
  Planar * pls[cap];
  size_t size = 0;
  try {
    pls[size++] = new Point(1, 2);
    pls[size++] = new Point(3, 4);
    pls[size++] = new Vector(Point(1, 2), Point(3, 4));
    pls[size++] = new Vector(Point(3, 4), Point(1, 2));
    pls[size++] = new ColoredPoint(Point(1, 2), Color::RED);
    pls[size++] = new ColoredPoint(Point(3, 4), Color::GREEN);
    pls[size++] = new Circle(Point(1, 2), 1);
    pls[size++] = new ColoredCircle(Color::BLUE, Circle(Point(1, 2), 1));
  } catch (std::exception& e) {
    del(pls, size);
    std::cerr << e.what() << '\n';
    return 1;
  }

  for (size_t i = 0; i < cap; ++i) {
    print_abs_sqr(std::cout, pls[i]);
    std::cout << '\n';
  }

  del(pls, size);


  if (!(std::cin >> size)) {
    std::cerr << "Invalid input" << '\n';
    return 1;
  }

  Planar ** pls = nullptr;
  try {
    pls = new Planar * [size];
  } catch (...) {

  }

  return 0;
}
