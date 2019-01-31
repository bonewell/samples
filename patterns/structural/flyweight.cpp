#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

class Star {
    public:
        explicit Star(std::string name):
             name_{std::move(name)} {}
        void collapse() {
            std::cout << "supernova\n";
        }
    private:
        std::string name_;
};

class MolecularCloud {
    public:
        std::shared_ptr<Star> light(std::string name) {
            auto it = cluster_.find(name);
            if (it != end(cluster_)) {
                return it->second;
            } else {
                std::cout << "light a start: " << name << "\n";
                auto star = std::make_shared<Star>(name);
                cluster_[name] = star;
                return star;
            }
        }
    private:
        using StarCluster = std::unordered_map<std::string, std::shared_ptr<Star>>;
        StarCluster cluster_;
};

int main() {
    MolecularCloud cloud;
    auto sun = cloud.light("Sun");
    sun->collapse();

    auto sirius = cloud.light("Sirius");
}