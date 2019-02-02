#include <string>
#include <iostream>
#include <memory>

class Builder {
    public:
        virtual void setScreen(double size) = 0;
        virtual void setSound(int power) = 0;
        virtual void setPlayer(std::string name) = 0;
};

struct Cinema {
    double screen;
    std::string projector;
    int sound;
};

class CinemaBuilder: public Builder {
    public:
        void setScreen(double size) override
        {
            std::cout << "Set screen: " << size << "\n";
            cinema_.screen = size;
        }

        void setSound(int power) override
        {
            std::cout << "Set sound: " << power << "\n";
            cinema_.sound = power;
        }

        void setPlayer(std::string name) override
        {
            std::cout << "Set player: " << name << "\n";
            cinema_.projector = std::move(name);
        }

        Cinema get()
        {
            return cinema_;
        }
    private:
        Cinema cinema_;
};

struct Blueprint {
    double screen;
    std::string projector;
    int sound;
};

class BlueprintBuilder: public Builder {
    public:
        void setScreen(double size) override
        {
            std::cout << "Draw screen: " << size << "\n";
            blueprint_.screen = size;
        }

        void setSound(int power) override
        {
            std::cout << "Draw sound: " << power << "\n";
            blueprint_.sound = power;
        }

        void setPlayer(std::string name) override
        {
            std::cout << "Draw player: " << name << "\n";
            blueprint_.projector = std::move(name);
        }

        Blueprint get()
        {
            return blueprint_;
        }
    private:
        Blueprint blueprint_;
};

class Director {
    public:
        Director(std::shared_ptr<Builder> b): b_{b} {}
        void make()
        {
            b_->setScreen(40);
            b_->setSound(1000);
            b_->setPlayer("SONY");
        }
    private:
        std::shared_ptr<Builder> b_;
};

int main() {
    auto engineer = std::make_shared<BlueprintBuilder>();
    Director{engineer}.make();
    auto blueprint = engineer.get();

    auto builder = std::make_shared<CinemaBuilder>();
    Director{builder}.make();
    auto cinema = builder.get();
}
