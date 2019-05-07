#include <memory>
#include <iostream>

class Phone {
    public:
        [[nodiscard]] virtual bool lock() noexcept = 0;
        [[nodiscard]] virtual bool unlock() = 0;
        virtual ~Phone() = default;
};
using PhonePtr = std::unique_ptr<Phone>;

class Tablet {
    public:
        [[nodiscard]] virtual bool lock() noexcept = 0;
        [[nodiscard]] virtual bool unlock() = 0;
        virtual ~Tablet() = default;
};
using TabletPtr = std::unique_ptr<Tablet>;

class Factory {
    public:
        virtual PhonePtr phone() const = 0;
        virtual TabletPtr tablet() const = 0;
        virtual ~Factory() = default;
};

class iPhone: public Phone {
    public:
        [[nodiscard]]
        bool lock() noexcept override
        {
            std::cout << "iPhone: locked\n";
            return true;
        }

        [[nodiscard]]
        bool unlock() override
        {
            std::cout << "iPhone: unlocked. FaceId is OK\n";
            return true;
        }
};

class iPad: public Tablet {
    public:
        [[nodiscard]]
        bool lock() noexcept override
        {
            std::cout << "iPad: locked\n";
            return true;
        }

        [[nodiscard]]
        bool unlock() override
        {
            std::cout << "iPad: unlocked. TouchId is OK\n";
            return true;
        }
};

class Galaxy: public Phone {
    public:
        [[nodiscard]]
        bool lock() noexcept override
        {
            std::cout << "Galaxy: locked.\n";
            return true;
        }

        [[nodiscard]]
        bool unlock() override
        {
            std::cout << "Galaxy: unlocked. Eyes are OK\n";
            return true;
        }
};

class MediaPad: public Tablet {
    public:
        [[nodiscard]]
        bool lock() noexcept override
        {
            std::cout << "MediaPad: locked.\n";
            return true;
        }

        [[nodiscard]]
        bool unlock() override
        {
            std::cout << "MediaPad: unlocked. PIN is OK\n";
            return true;
        }
};

class Apple: public Factory {
    public:
        PhonePtr phone() const override
        {
            std::cout << "Create iPhone\n";
            return std::make_unique<iPhone>();
        }

        TabletPtr tablet() const override
        {
            std::cout << "Create iPad\n";
            return std::make_unique<iPad>();
        }
};

class NoName: public Factory {
    public:
        PhonePtr phone() const override
        {
            std::cout << "Create Galaxy\n";
            return std::make_unique<Galaxy>();
        }

        TabletPtr tablet() const override
        {
            std::cout << "Create MediaPad\n";
            return std::make_unique<MediaPad>();
        }
};

int main() {
    const Factory& factory = NoName{};
    auto phone = factory.phone();
    if (phone->unlock())
        auto _ = phone->lock();

    auto tablet = factory.tablet();
    if (tablet->unlock())
        auto _ = tablet->lock();
}