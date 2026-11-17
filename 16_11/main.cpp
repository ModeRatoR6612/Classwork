#include <iostream>

constexpr double PI = 3.14159265358979323846;

enum Color {RED, GREEN, BLUE};

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

  return 0;
}
