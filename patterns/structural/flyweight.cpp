#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

enum class Color { blue, white, yellow, orange, red };

struct Point { int x, y, z; };

struct StarType {  // flyweight
    int temperature;
    Color color;
};

class Star {
    public:
        Star(Point point, const StarType& type):
             point_{point}, type_{type} {}
        void collapse() {
            std::cout << "supernova\n";
        }
    private:
        Point point_;
        const StarType& type_;
};
using StarPtr = std::unique_ptr<Star>;

class MolecularCloud {
    public:
        StarPtr light(std::string kind, int t, Color c) {
            std::cout << "light a start: " << kind << "\n";
            Point p;  //  fill random

            auto it = cluster_.find(kind);
            if (it == end(cluster_)) {
                StarType type{t, c};
                cluster_.emplace(kind, type);
                return std::make_unique<Star>(p, type);
            } else {
                return std::make_unique<Star>(p, it->second);
            }
        }
    private:
        using StarCluster = std::unordered_map<std::string, const StarType&>;
        StarCluster cluster_;
};

int main() {
    MolecularCloud cloud;
    auto sun = cloud.light("G", 5500, Color::yellow);
    sun->collapse();

    auto sirius = cloud.light("A", 8000, Color::white);
}