#include <string>
#include <iostream>

struct HomeTheater {
    std::string screen;
    std::string player;
    std::string sound;
};

class Builder {
    public:
        virtual void setScreen(std::string name) = 0;
        virtual void setSound(std::string name) = 0;
        virtual void setPlayer(std::string name) = 0;
        HomeTheater get()
        {
            return ht_;
        }
    protected:
        HomeTheater ht_;
};

class Setter {
    public:
        Setter(std::shared_ptr<Builder> b): b_{b}
        {
        }

        HomeTheater create(std::string screen,
                           std::string sound,
                           std::string player)
        {
            b_->setScreen(screen);
            b_->setSound(sound);
            b_->setPlayer(player);
            return b_->get();
        }
    private:
        std::shared_ptr<Builder> b_;
};

class HiFiBuilder: public Builder {
    public:
        void setScreen(std::string name) override
        {
            std::cout << "Set HiFi screen: " << name << "\n";
            ht_.screen = std::move(name);
        }

        void setSound(std::string name) override
        {
            std::cout << "Set HiFi sound: " << name << "\n";
            ht_.sound = std::move(name);
        }

        void setPlayer(std::string name) override
        {
            std::cout << "Set HiFi player: " << name << "\n";
            ht_.player = std::move(name);
        }
};

class HiEndBuilder: public Builder {
    public:
        void setScreen(std::string name) override
        {
            std::cout << "Set HiEnd screen: " << name << "\n";
            ht_.screen = std::move(name);
        }

        void setSound(std::string name) override
        {
            std::cout << "Set HiEnd sound: " << name << "\n";
            ht_.sound = std::move(name);
        }

        void setPlayer(std::string name) override
        {
            std::cout << "Set HiEnd player: " << name << "\n";
            ht_.player = std::move(name);
        }
};

int main() {
  std::shared_ptr<Builder> b{new HiFiBuilder{}};
  Setter s{b};
  auto hometheater = s.create("SONY", "AudioPro", "Technosonic");
}
