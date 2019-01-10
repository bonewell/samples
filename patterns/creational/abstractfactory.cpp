#include <memory>
#include <iostream>

class Device {
    public:
        [[nodiscard]] virtual bool lock() noexcept = 0;
        [[nodiscard]] virtual bool unlock() = 0;
        virtual ~Device() = default;
};
using MobileDevice = std::unique_ptr<Device>;

class Factory {
    public:
        virtual MobileDevice phone() const = 0;
        virtual MobileDevice tablet() const = 0;
        virtual ~Factory() = default;
};

class iPhone: public Device {
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

class iPad: public Device {
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

class Galaxy: public Device {
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

class MediaPad: public Device {
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
        MobileDevice phone() const override
        {
            std::cout << "Create iPhone\n";
            return MobileDevice{new iPhone{}};
        }

        MobileDevice tablet() const override
        {
            std::cout << "Create iPad\n";
            return MobileDevice{new iPad{}};
        }
};

class NoName: public Factory {
    public:
        MobileDevice phone() const override
        {
            std::cout << "Create Galaxy\n";
            return MobileDevice{new Galaxy{}};
        }

        MobileDevice tablet() const override
        {
            std::cout << "Create MediaPad\n";
            return MobileDevice{new MediaPad{}};
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