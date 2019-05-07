#include <iostream>

struct point;

struct polygon_link
{
  point* prev{nullptr};
  point* next{nullptr};
};

struct point
{
  int x, y;
  polygon_link link;
};

point* link(point* p1, point* p2)
{
  p1->link.next = p2;
  p2->link.prev = p1;
  return p2;
}

point* unlink(point* p)
{
  p->link.prev->link.next = p->link.next;
  p->link.next->link.prev = p->link.prev;
  point* prev = p->link.prev;
  p->link.prev = nullptr;
  p->link.next = nullptr;
  return prev;
}

void show(point* p)
{
  while (p != nullptr) {
    std::cout << "(" << p->x << ", " << p->y << ")\n";
    p = p->link.next;
  }
}

int main()
{
  point p1{1, 1};
  point p2{1, 2};
  point p3{2, 2};
  point p4{2, 3};

  point* p = link(link(link(&p1, &p2), &p3), &p4);
  show(&p1);

  std::cout << "---\n";

  p = unlink(&p3);
  show(&p1);

  return 0;
}
